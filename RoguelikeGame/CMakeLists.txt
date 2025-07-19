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

add_executable(main src/main.cpp "src/Player.cpp" "src/Headers/Player.h" "src/TextureManager.cpp" "src/TileMap.cpp" "src/Headers/TileMap.h" "src/Headers/Enemy.h" "src/Enemy.cpp" "src/Headers/BulletManager.h" "src/Headers/Bullet.h" "src/BulletManager.cpp" "src/Headers/EnemyManager.h" "src/EnemyManager.cpp" "src/Headers/HealthManager.h" "src/Headers/Button.h" "src/Button.cpp")
target_link_libraries(main PRIVATE SFML::Graphics)
