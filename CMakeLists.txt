cmake_minimum_required(VERSION 3.19)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

project(oke_oyibo)

add_subdirectory(library/raylib/)

file(GLOB oke_oyibo_SRC
    "src/**/*.h"
    "src/**/*.cpp"
    "src/**/**/*.h"
    "src/**/**/*.cpp"
    "src/main.cpp"
    "library/imgui/examples/imgui_impl_glfw.cpp"
    "library/imgui/examples/imgui_impl_opengl3.cpp"
    "library/imgui/imgui.cpp"
    "library/imgui/imgui_draw.cpp"
    "library/imgui/imgui_widgets.cpp"
)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_CUSTOM="library/raylib/src/external/glad.h")

include_directories("src/")
include_directories(".")
include_directories("library/entt/src/")
include_directories("library/imgui/")
include_directories("library/imgui/examples")
include_directories("library/raylib/src/external/glfw/include")

add_executable(oke_oyibo ${oke_oyibo_SRC})
set_property(TARGET oke_oyibo PROPERTY CXX_STANDARD 20)

target_link_libraries(oke_oyibo raylib)
