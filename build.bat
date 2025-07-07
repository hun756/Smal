@echo off
setlocal enabledelayedexpansion

set BUILD_TYPE=Release
setlocal enabledelayedexpansion

set BUILD_TYPE=Release
set BUILD_TESTS=ON
set BUILD_EXAMPLES=ON
set BUILD_BENCHMARKS=OFF
set BUILD_DOCS=OFF
set CLEAN=false
set INSTALL=false
set JOBS=4

:parse_args
if "%~1"=="" goto end_parse_args

if "%~1"=="-t" (
    set BUILD_TYPE=%~2
    shift
    shift
    goto parse_args
)
if "%~1"=="--build-type" (
    set BUILD_TYPE=%~2
    shift
    shift
    goto parse_args
)
if "%~1"=="-j" (
    set JOBS=%~2
    shift
    shift
    goto parse_args
)
if "%~1"=="--jobs" (
    set JOBS=%~2
    shift
    shift
    goto parse_args
)
if "%~1"=="--no-tests" (
    set BUILD_TESTS=OFF
    shift
    goto parse_args
)
if "%~1"=="--no-examples" (
    set BUILD_EXAMPLES=OFF
    shift
    goto parse_args
)
if "%~1"=="--with-benchmarks" (
    set BUILD_BENCHMARKS=ON
    shift
    goto parse_args
)
if "%~1"=="--with-docs" (
    set BUILD_DOCS=ON
    shift
    goto parse_args
)
if "%~1"=="--clean" (
    set CLEAN=true
    shift
    goto parse_args
)
if "%~1"=="--install" (
    set INSTALL=true
    shift
    goto parse_args
)
if "%~1"=="--help" (
    goto show_help
)

echo Unknown option: %~1
goto show_help

:end_parse_args

if not "%BUILD_TYPE%"=="Debug" if not "%BUILD_TYPE%"=="Release" (
    echo ERROR: Invalid build type: %BUILD_TYPE%. Must be Debug or Release.
    exit /b 1
)

echo Build Configuration:
echo   Build Type: %BUILD_TYPE%
echo   Tests: %BUILD_TESTS%
echo   Examples: %BUILD_EXAMPLES%
echo   Benchmarks: %BUILD_BENCHMARKS%
echo   Documentation: %BUILD_DOCS%
echo   Parallel Jobs: %JOBS%
echo.

set BUILD_DIR=build
if "%CLEAN%"=="true" (
    echo Cleaning build directory...
    if exist "%BUILD_DIR%" rmdir /s /q "%BUILD_DIR%"
)

if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"
cd "%BUILD_DIR%"

echo Configuring with CMake...
cmake .. ^
    -DCMAKE_BUILD_TYPE=%BUILD_TYPE% ^
    -DBUILD_TESTS=%BUILD_TESTS% ^
    -DBUILD_EXAMPLES=%BUILD_EXAMPLES% ^
    -DBUILD_BENCHMARKS=%BUILD_BENCHMARKS% ^
    -DBUILD_DOCS=%BUILD_DOCS%

if errorlevel 1 (
    echo ERROR: CMake configuration failed!
    exit /b 1
)

echo Building...
cmake --build . --config %BUILD_TYPE% -j %JOBS%

if errorlevel 1 (
    echo ERROR: Build failed!
    exit /b 1
)

if "%BUILD_TESTS%"=="ON" (
    echo Running tests...
    ctest --build-config %BUILD_TYPE% --output-on-failure -j %JOBS%
    if errorlevel 1 (
        echo ERROR: Tests failed!
        exit /b 1
    )
)

if "%INSTALL%"=="true" (
    echo Installing...
    cmake --install . --config %BUILD_TYPE%
    if errorlevel 1 (
        echo ERROR: Installation failed!
        exit /b 1
    )
)

echo Build completed successfully!
echo.
echo Next steps:
echo   • Run the demo: .\%BUILD_DIR%\%BUILD_TYPE%\small_vec_demo.exe
if "%BUILD_EXAMPLES%"=="ON" (
    echo   • Try examples: .\%BUILD_DIR%\examples\%BUILD_TYPE%\example_basic.exe
)
if "%BUILD_BENCHMARKS%"=="ON" (
    echo   • Run benchmarks: .\%BUILD_DIR%\benchmarks\%BUILD_TYPE%\benchmark_performance.exe
)
if "%BUILD_TESTS%"=="ON" (
    echo   • Run specific test: .\%BUILD_DIR%\tests\%BUILD_TYPE%\test_small_vec.exe
)

goto end

:show_help
echo Usage: %0 [OPTIONS]
echo.
echo Options:
echo   -t, --build-type TYPE    Build type (Debug^|Release) [default: Release]
echo   -j, --jobs N            Number of parallel jobs for make [default: 4]
echo   --no-tests              Don't build tests
echo   --no-examples           Don't build examples
echo   --with-benchmarks       Build benchmarks
echo   --with-docs             Build documentation
echo   --clean                 Clean build directory before building
echo   --install               Install after building
echo   --help                  Show this help message
echo.
exit /b 0

:end
endlocal