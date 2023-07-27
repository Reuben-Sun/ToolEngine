add_executable(client main.cpp client_framework.h client_framework.cpp)
target_link_libraries(client PRIVATE core)
target_link_libraries(client PRIVATE imgui)
target_link_libraries(client PRIVATE glfw)
target_link_libraries(client PRIVATE scene)
target_link_libraries(client PRIVATE tbb)
target_include_directories(client PRIVATE ${TBB_Headers})

add_custom_command(TARGET client POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:OptickCore>
    $<TARGET_FILE_DIR:client>
)