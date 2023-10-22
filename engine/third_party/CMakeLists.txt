project(third_party LANGUAGES C CXX)
set(THIRDPARTY_LIBRARIES)

### mandatory dependencies
# vulkan
find_package(Vulkan REQUIRED)

# GLFW
if (NOT TARGET glfw)
  set(GLFW_USE_HYBRID_HPG OFF)
  set(GLFW_VULKAN_STATIC OFF)
  set(GLFW_BUILD_DOCS OFF)
  set(GLFW_BUILD_EXAMPLES OFF)
  set(GLFW_BUILD_TESTS OFF)
  set(GLFW_INSTALL OFF)
  set(BUILD_SHARED_LIBS OFF)
  add_subdirectory(glfw)
  set_property(TARGET glfw PROPERTY FOLDER "ThirdParty")
endif()

# imgui
set(IMGUI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/imgui" )
set(IMGUI_FILES
    "${IMGUI_DIR}/imgui.cpp"
    "${IMGUI_DIR}/imgui_demo.cpp"
    "${IMGUI_DIR}/imgui_draw.cpp"
    "${IMGUI_DIR}/imgui_tables.cpp"
    "${IMGUI_DIR}/imgui_widgets.cpp"
    "${IMGUI_DIR}/imconfig.h"
    "${IMGUI_DIR}/imgui.h"
    "${IMGUI_DIR}/imgui_internal.h"
    "${IMGUI_DIR}/imstb_rectpack.h"
    "${IMGUI_DIR}/imstb_textedit.h"
    "${IMGUI_DIR}/imstb_truetype.h"
    "${IMGUI_DIR}/backends/imgui_impl_vulkan.cpp")

if (NOT TARGET imgui)
  add_library(imgui STATIC ${IMGUI_FILES})
  target_include_directories(imgui PUBLIC ${IMGUI_DIR})
  target_link_libraries(imgui PUBLIC ${Vulkan_LIBRARIES})
  target_include_directories(imgui PUBLIC ${Vulkan_INCLUDE_DIRS})
  set_property(TARGET imgui PROPERTY FOLDER "ThirdParty")
endif()

set(IMGUI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/imgui" PARENT_SCOPE)

# tbb
if(NOT TARGET tbb)
  set(TBB_TEST OFF)
  set(TBB_EXAMPLES OFF)
  set(TBBMALLOC_BUILD OFF)
  set(BUILD_SHARED_LIBS ON)
  add_subdirectory(tbb)
  set_property(TARGET tbb PROPERTY FOLDER "ThirdParty")
  set(TBB_Headers "${CMAKE_CURRENT_SOURCE_DIR}/tbb/include" PARENT_SCOPE)
endif()

# optick
set(OPTICK_INSTALL_TARGETS OFF)
set(OPTICK_USE_VULKAN ON)
add_subdirectory(Optick)
set_property(TARGET OptickCore PROPERTY FOLDER "ThirdParty")

# glm
if(NOT TARGET glm)
  add_subdirectory(glm)
  set_property(TARGET glm PROPERTY FOLDER "ThirdParty")
endif()

# tiny gltf
if(NOT TARGET tinygltf)
  add_subdirectory(tinygltf)
  set_property(TARGET tinygltf PROPERTY FOLDER "ThirdParty")
endif()

# lua
if(NOT TARGET lua)
  set(LUA_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lua)
  file(GLOB_RECURSE LUA_SOURCES ${LUA_DIR}/*.c)
  list(FILTER LUA_SOURCES EXCLUDE REGEX "lua.c$")
  list(FILTER LUA_SOURCES EXCLUDE REGEX "onelua.c$")

  add_library(lua STATIC ${LUA_SOURCES})
  target_include_directories(lua PUBLIC ${LUA_DIR})
  set_property(TARGET lua PROPERTY FOLDER "ThirdParty")
endif()