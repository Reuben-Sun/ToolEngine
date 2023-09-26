# 引擎框架

## client

### main

程序运行的入口函数，通过调用framework中的静态函数来运行整个程序

### framework

程序的真正入口，有多个静态函数构成，其中包括一个run函数，来创建window

## core

### render

### rhi

### window

包含窗口基类和GLFW窗口类
#### glfw_window

继承自window，通过glfw来实现window中定义的函数，拥有一个窗口句柄GLFWwindow *handle

通过创建platform对象来创建窗口

### file

### logic

## scene

### application
- ExitCode initialize
- ExitCode main_loop
  - void update
    - draw
- void terminate



