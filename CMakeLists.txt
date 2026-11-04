cmake_minimum_required(VERSION 3.16)

project(GolfTest LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(OPENGL_VERSION "2.1" CACHE STRING "" FORCE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

include(FetchContent)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.5
)

FetchContent_MakeAvailable(raylib)

add_executable(GolfTest main.cpp "GolfClubs.h" "GolfClubs.cpp" "BallPhysics.h" "BallPhysics.cpp" "Swing.h" "Swing.cpp" "Course.h" "Course.cpp" "GameUI.h" "GameUI.cpp" )

target_link_libraries(GolfTest PRIVATE raylib)

set_target_properties(GolfTest PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)
