cmake_minimum_required(VERSION 3.14)
project(MyRaylibProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fetch Raylib from GitHub
include(FetchContent)
FetchContent_Declare(
  raylib
  URL https://github.com/raysan5/raylib/archive/refs/tags/5.0.tar.gz
)

FetchContent_MakeAvailable(raylib)

add_executable(MyRaylibProject main.cpp)

# Link Raylib to the executable
target_link_libraries(MyRaylibProject PRIVATE raylib)

# Copy textures to the build directory
add_custom_command(TARGET MyRaylibProject POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/textures
        $<TARGET_FILE_DIR:MyRaylibProject>/textures)
