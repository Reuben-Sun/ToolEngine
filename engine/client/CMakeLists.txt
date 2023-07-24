add_executable(client main.cpp)
target_link_libraries(client PRIVATE core)
target_link_libraries(client PRIVATE imgui)
target_link_libraries(client PRIVATE glfw)