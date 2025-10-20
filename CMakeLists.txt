cmake_minimum_required(VERSION 3.10)
project(FireWorksShow)

set(CMAKE_CXX_STANDARD 17)

# set(CMAKE_BUILD_TYPE Debug)


add_compile_options(-march=native -O3)
add_compile_options(-msse4.1)


include_directories("${CMAKE_SOURCE_DIR}")

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Add your source files
add_executable(FireWorksShow
    core/firework.cpp
    core/fireworkshow.cpp
    src/main.cpp
)

# Link SFML libraries here
target_link_libraries(FireWorksShow
    sfml-graphics
    sfml-window
    sfml-system
)