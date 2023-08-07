# Tool Engine

## Todo

### Runtime

- [ ] Vulkan基础框架
- [ ] ImGui界面框架
- [ ] FBX SDK
- [ ] GLTF文件格式
- [ ] 骨骼动画、Blendshape动画


### Editor

> 最近发现ImGui也能做出不错的界面，就不用Qt之类的Editor框架了

- [ ] Simplygon模型减面
- [ ] 双击FBX打开引擎
- [ ] 模型拖入引擎

### 进阶目标

- [ ] Vulkan Ray Query
- [ ] Restir GI
- [ ] Speedtree
- [ ] Apex
- [ ] DLSS

## Render框架

刚刚看了[Vulkan官方样例](https://github.com/KhronosGroup/Vulkan-Samples/tree/main)，深感框架的重要性，于是我想先搭建一个看的顺眼的框架

### main

程序运行的入口函数，通过调用framework中的静态函数来运行整个程序

### framework

程序的真正入口，有多个静态函数构成，其中包括一个run函数，来创建window

### window

类似于官方样例中`window`的作用，是窗口基类，存储了一些窗口参数，并定义了一些虚函数

值得留意的函数有：

- VkSurfaceKHR create_surface
- void process_events
- void close() 
- std::vector<const char *> get_required_surface_extensions()
- Mode get_window_mode()

### glfw_window

继承自window，通过glfw来实现window中定义的函数，拥有一个窗口句柄GLFWwindow *handle

通过创建platform对象来创建窗口

### platform/application

管理渲染窗口的生命周期，每个函数都有一个返回值ExitCode，用于判断当前函数是否成功执行，此外还有一个public的变量app_requested，这个变量将决定当前platform是否还被需要（可能是和窗口大小调整有关？）

函数有

- ExitCode initialize
- ExitCode main_loop
  - void update
    - draw
- void terminate

成员有

- Timer

### render

platform中的draw就是render的函数，这个类似于官方样例中`vulkan_sanple`

这个类中有

- Instance
- Device
- RenderContext
- RenderPipeline
- Scene
- imgui
- ...

可以说，这个就是整个vulkan执行的核心函数，这些成员是对vulkan中相关接口的封装

