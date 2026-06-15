cmake_minimum_required(VERSION 3.11)
project(Attain-Moksha CXX C)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Download and configure Raylib automatically
include(FetchContent)
FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/5.0.tar.gz
)
FetchContent_MakeAvailable(raylib)

# Create your game executable
add_executable(${PROJECT_NAME} main.cpp)

# Link Raylib to your game
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)