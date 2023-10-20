# Tool Engine

## 拉取

本项目使用 Submodule 和 Git LFS，拉取项目后还需

```
git submodule init
git submodule update
git lfs pull
```

## 构建 运行

[![Build Windows](https://github.com/Reuben-Sun/ToolEngine/actions/workflows/build_windows.yml/badge.svg)](https://github.com/Reuben-Sun/ToolEngine/actions/workflows/build_windows.yml) 

- 需要 Vulkan、cmake
- 根据 VS 版本运行 scripts 下的 `cmake_generate_20xx`
- 用 Visual Studio 打开 ToolEngine.sln
- 设 client 为启动项目，运行

## 参考

[Vulkan Tutorial](https://vulkan-tutorial.com/Introduction)

[Vulkan Tutorial Github](https://github.com/Overv/VulkanTutorial/blob/main/code/00_base_code.cpp)

[Vulkan Sample](https://github.com/KhronosGroup/Vulkan-Samples/tree/main)

[Cherno's Hazel](https://www.youtube.com/playlist?list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT)

[Vulakn Render Graph](https://github.com/asc-community/VulkanAbstractionLayer)

[glTF Tutorials](https://github.khronos.org/glTF-Tutorials/gltfTutorial/)