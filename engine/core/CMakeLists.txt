file(GLOB_RECURSE HEADERS "include/*/*.h")
file(GLOB_RECURSE SOURCES "*src/*/*.cpp")
set(ALL_FILES ${HEADERS} ${SOURCES})

add_library(core STATIC ${ALL_FILES})

target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${ALL_FILES})

find_package(Vulkan REQUIRED)
target_link_libraries(core PUBLIC ${Vulkan_LIBRARIES})  
target_include_directories(core PUBLIC ${Vulkan_INCLUDE_DIR})