@echo off

set SHADER_DIR=src/
set TARGET_DIR=spv/
set COMPILER_TOOL=glslc.exe

%COMPILER_TOOL% %SHADER_DIR%shader.vert -o %TARGET_DIR%vert.spv
%COMPILER_TOOL% %SHADER_DIR%shader.frag -o %TARGET_DIR%frag.spv

pause