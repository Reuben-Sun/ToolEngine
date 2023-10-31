# Tool Engine

一个基于C++20 Modules的简易Vulkan渲染器

## 拉取

本项目使用 Submodule 和 Git LFS，拉取项目后还需

```
git submodule init
git submodule update
git lfs pull
```

## 构建

[![Build Windows](https://github.com/Reuben-Sun/ToolEngine/actions/workflows/build_windows.yml/badge.svg)](https://github.com/Reuben-Sun/ToolEngine/actions/workflows/build_windows.yml) 

- 需要 Vulkan
- 需要cmake 3.21以上的版本（`.ixx`和`.cppm`支持）
- 仅支持MSVC（使用了C++20 Modules）
- 需要Visual Studio 2022 17.5即以上版本，且安装**适用于v143生成工具的C++模块（x64/x86 - 实验性）**

## 运行

- 运行 scripts 下的 `cmake_generate_2022`生成项目
- 用 Visual Studio 22打开 ToolEngine.sln
- 设 client 为启动项目，运行

## 宏伟蓝图

我想简单聊几句我对这个项目的远景，以激励自己能坚持将这个项目做下去。

几乎每个引擎图形程序员，都会有自己搓的小轮子，用来学习和实践自己的想法和技术，但这些小引擎大多销声匿迹，尽管他们做了很多很厉害的功能。尽管做这些项目中的成长是货真价实的，但还是令人感到遗憾，自己的心血除了用作试验田和让他人参考学习，没有任何生态位。

我感觉这也是很多做商业自研引擎公司所面临的窘境，面对强大、经受考验、用户极多的UE和Unity，自研引擎在代码稳定性、功能、效果上都有所欠缺。而且与硬件不同，游戏引擎的对象一般是商业用户，他们是渴望盈利的，他们倾向使用一个稳定好用、好招人、价格便宜的引擎，他们往往不会仅仅因为UE有的功能你都有而选择你。

做好一个程序员，需要有好的认知能力。游戏引擎是一个极其复杂的东西，我个人是绝无可能敲出一个可堪一用的项目，于是我想先从工具开始，做一个我自己可能愿意用的3D查看器，我不需要电脑里安装一些付费的DCC软件，就可以**打开**一个模型文件（不是导入），并对其做一些小操作。

- [ ] 替代Windows的3D查看器，实现双击打开一个fbx、gltf、usd模型
  - [ ] 注册到Windows右键菜单
  - [ ] 查看模型的基本信息，比如有多少的顶点、三角面，采用何种映射方式
  - [ ] 查看模型是否有多套UV，并画出UV的样式
  - [ ] 支持导出为其他类型的模型
  - [ ] 支持Simplygon自动简面
  - [ ] 支持简单修改模型的material参数
- [ ] 工作室like的模型预览
  - [ ] 基于物理的渲染
  - [ ] 工作室级的光照，类似选角界面的三个可调节光源（镜头光、边缘光、顶光）
  - [ ] 查看模型参数是否符合PBR规范
  - [ ] 查看贴图纹素是否合理
  - [ ] 光追预览+截图
- [ ] 实现PBR效果烘焙到一个Unlit basemap上
- [ ] 实现贴图压缩，比如PNG压缩为DDS、修改编码格式、伽马矫正、生成Mipmap等

## 参考

[Vulkan Tutorial](https://vulkan-tutorial.com/Introduction)

[Vulkan Tutorial Github](https://github.com/Overv/VulkanTutorial/blob/main/code/00_base_code.cpp)

[Vulkan Sample](https://github.com/KhronosGroup/Vulkan-Samples/tree/main)

[Cherno's Hazel](https://www.youtube.com/playlist?list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT)

[Vulakn Render Graph](https://github.com/asc-community/VulkanAbstractionLayer)

[glTF Tutorials](https://github.khronos.org/glTF-Tutorials/gltfTutorial/)

[Piccolo](https://github.com/BoomingTech/Piccolo)