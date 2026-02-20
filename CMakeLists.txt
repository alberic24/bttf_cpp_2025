cmake_minimum_required(VERSION 3.10)
project(TopDownShooter)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Source files
set(SOURCES
    src/main.cpp
    src/Core/Game.cpp
    src/Core/GameScene.cpp
    src/Core/ResourceManager.cpp
    src/Components/Transform.cpp
    src/Components/Health.cpp
    src/Components/Collider.cpp
    src/Entities/Player.cpp
    src/Entities/Enemy.cpp
    src/Entities/Projectile.cpp
    src/Entities/Explosion.cpp
    src/Weapons/Pistol.cpp
    src/Weapons/FireballLauncher.cpp
    src/Weapons/WeaponPickup.cpp
    src/Systems/CollisionSystem.cpp
    src/Systems/PhysicsSystem.cpp
    src/UI/Button.cpp
    src/UI/HUD.cpp
    src/UI/MainMenu.cpp
    src/UI/SettingsMenu.cpp
    src/Utils/Config.cpp
    src/Utils/Math.cpp
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link SFML
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system sfml-audio)

# Compiler warnings
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Copy resources if needed
# file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR})