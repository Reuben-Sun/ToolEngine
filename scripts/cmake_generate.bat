@echo off

set SOURCE_DIR=../engine/
set BUILD_DIR=../build/

cmake -S %SOURCE_DIR% -B %BUILD_DIR% -G "Visual Studio 16 2019"
cmake --build %BUILD_DIR%

pause
