file(GLOB_RECURSE HEADERS "include/*/*.h" "include/*/*.ixx")
file(GLOB_RECURSE SOURCES "*src/*/*.cpp" "src/*/*.cppm")
set(ALL_FILES ${HEADERS} ${SOURCES})

add_library(core STATIC ${ALL_FILES})

target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${ALL_FILES})

target_link_libraries(core PUBLIC OptickCore)
target_link_libraries(core PUBLIC glm)
target_link_libraries(core PUBLIC tinygltf)
target_link_libraries(core PUBLIC glfw)
target_link_libraries(core PUBLIC lua)
target_link_libraries(core PUBLIC spdlog)

find_package(Vulkan REQUIRED)
target_link_libraries(core PUBLIC ${Vulkan_LIBRARIES})  
target_include_directories(core PUBLIC ${Vulkan_INCLUDE_DIR})

if(MSVC)
    target_compile_options(core PUBLIC "/Zc:preprocessor")
    target_compile_options(core PUBLIC "/std:c++latest")
    target_compile_options(core PUBLIC "/experimental:module")
endif()
