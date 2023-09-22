@echo off

set SHADER_DIR=../engine/shaders/
set TARGET_DIR=../engine/shaders/spv/
set COMPILER_TOOL="C:/Program Files/Vulkan/Bin/glslc.exe"

%COMPILER_TOOL% %SHADER_DIR%shader.vert -o %TARGET_DIR%vert.spv
%COMPILER_TOOL% %SHADER_DIR%shader.frag -o %TARGET_DIR%frag.spv

pause