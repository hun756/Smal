#!/bin/bash

set -e

BUILD_TYPE=${BUILD_TYPE:-Release}
BUILD_TESTS=${BUILD_TESTS:-ON}
BUILD_EXAMPLES=${BUILD_EXAMPLES:-ON}
BUILD_BENCHMARKS=${BUILD_BENCHMARKS:-OFF}
BUILD_DOCS=${BUILD_DOCS:-OFF}

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

print_status() {
    echo -e "${GREEN}[INFO]${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

print_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

show_help() {
    echo "Usage: $0 [OPTIONS]"
    echo ""
    echo "Options:"
    echo "  -t, --build-type TYPE    Build type (Debug|Release) [default: Release]"
    echo "  -j, --jobs N            Number of parallel jobs for make [default: auto]"
    echo "  --no-tests              Don't build tests"
    echo "  --no-examples           Don't build examples"
    echo "  --with-benchmarks       Build benchmarks"
    echo "  --with-docs             Build documentation"
    echo "  --clean                 Clean build directory before building"
    echo "  --install               Install after building"
    echo "  --help                  Show this help message"
    echo ""
}

CLEAN=false
INSTALL=false
JOBS=""

while [[ $# -gt 0 ]]; do
    case $1 in
        -t|--build-type)
            BUILD_TYPE="$2"
            shift 2
            ;;
        -j|--jobs)
            JOBS="$2"
            shift 2
            ;;
        --no-tests)
            BUILD_TESTS=OFF
            shift
            ;;
        --no-examples)
            BUILD_EXAMPLES=OFF
            shift
            ;;
        --with-benchmarks)
            BUILD_BENCHMARKS=ON
            shift
            ;;
        --with-docs)
            BUILD_DOCS=ON
            shift
            ;;
        --clean)
            CLEAN=true
            shift
            ;;
        --install)
            INSTALL=true
            shift
            ;;
        --help)
            show_help
            exit 0
            ;;
        *)
            print_error "Unknown option: $1"
            show_help
            exit 1
            ;;
    esac
done

if [[ "$BUILD_TYPE" != "Debug" && "$BUILD_TYPE" != "Release" ]]; then
    print_error "Invalid build type: $BUILD_TYPE. Must be Debug or Release."
    exit 1
fi

if [[ -z "$JOBS" ]]; then
    if command -v nproc &> /dev/null; then
        JOBS=$(nproc)
    elif command -v sysctl &> /dev/null; then
        JOBS=$(sysctl -n hw.ncpu)
    else
        JOBS=4
    fi
fi

print_status "Build Configuration:"
echo "  Build Type: $BUILD_TYPE"
echo "  Tests: $BUILD_TESTS"
echo "  Examples: $BUILD_EXAMPLES"
echo "  Benchmarks: $BUILD_BENCHMARKS"
echo "  Documentation: $BUILD_DOCS"
echo "  Parallel Jobs: $JOBS"
echo ""

BUILD_DIR="build"
if [[ "$CLEAN" == true ]]; then
    print_status "Cleaning build directory..."
    rm -rf "$BUILD_DIR"
fi

mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

print_status "Configuring with CMake..."
cmake .. \
    -DCMAKE_BUILD_TYPE="$BUILD_TYPE" \
    -DBUILD_TESTS="$BUILD_TESTS" \
    -DBUILD_EXAMPLES="$BUILD_EXAMPLES" \
    -DBUILD_BENCHMARKS="$BUILD_BENCHMARKS" \
    -DBUILD_DOCS="$BUILD_DOCS"

print_status "Building..."
cmake --build . --config "$BUILD_TYPE" -j "$JOBS"

if [[ "$BUILD_TESTS" == "ON" ]]; then
    print_status "Running tests..."
    ctest --build-config "$BUILD_TYPE" --output-on-failure -j "$JOBS"
fi

if [[ "$INSTALL" == true ]]; then
    print_status "Installing..."
    cmake --install . --config "$BUILD_TYPE"
fi

print_status "Build completed successfully!"

echo ""
echo "Next steps:"
echo "  • Run the demo: ./$BUILD_DIR/small_vec_demo"
if [[ "$BUILD_EXAMPLES" == "ON" ]]; then
    echo "  • Try examples: ./$BUILD_DIR/examples/example_basic"
fi
if [[ "$BUILD_BENCHMARKS" == "ON" ]]; then
    echo "  • Run benchmarks: ./$BUILD_DIR/benchmarks/benchmark_performance"
fi
if [[ "$BUILD_TESTS" == "ON" ]]; then
    echo "  • Run specific test: ./$BUILD_DIR/tests/test_small_vec"
fi
