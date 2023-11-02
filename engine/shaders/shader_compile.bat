@echo off

set SHADER_DIR=src/
set TARGET_DIR=spv/

glslangValidator -V -S vert %SHADER_DIR%shader.vert -o %TARGET_DIR%vert.spv
glslangValidator -V -S frag %SHADER_DIR%shader.frag -o %TARGET_DIR%frag.spv

pause