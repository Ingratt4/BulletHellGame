cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(main src/main.cpp "src/Player.cpp" "src/Headers/Player.h" "src/Headers/Gun.h" "src/Gun.cpp" "src/TextureManager.cpp" "src/TileMap.cpp" "src/Headers/TileMap.h")
target_link_libraries(main PRIVATE SFML::Graphics)
