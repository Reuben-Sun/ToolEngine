@echo off

set SHADER_DIR=../shaders/
set TARGET_DIR=../shaders/SPV/
set COMPILER_TOOL=C:/Programs/Vulkan/Bin/glslc.exe

%COMPILER_TOOL% %SHADER_DIR%shader.vert -o %TARGET_DIR%vert.spv
%COMPILER_TOOL% %SHADER_DIR%shader.frag -o %TARGET_DIR%frag.spv

pause