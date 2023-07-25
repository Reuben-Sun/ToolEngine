#file(GLOB_RECURSE HEADERS "*.h")
#file(GLOB_RECURSE SOURCES ".cpp")
#set(ALL_FILES ${HEADERS} ${SOURCES})

#add_library(scene STATIC ${ALL_FILES})
add_library(scene STATIC scene_view.h scene_view.cpp)

target_include_directories(scene PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
