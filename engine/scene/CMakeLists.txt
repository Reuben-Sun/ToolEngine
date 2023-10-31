file(GLOB_RECURSE HEADERS "*.ixx" "include/*/*.ixx")
file(GLOB_RECURSE SOURCES "*.cppm" "src/*/*.cppm")
set(ALL_FILES ${HEADERS} ${SOURCES})

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${ALL_FILES})

add_library(scene STATIC ${ALL_FILES})
target_link_libraries(scene PRIVATE imgui)
target_link_libraries(scene PUBLIC core)
target_link_libraries(scene PUBLIC EnTT)
target_link_libraries(scene PRIVATE tbb)
target_include_directories(scene PRIVATE ${TBB_Headers})
target_include_directories(scene PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


