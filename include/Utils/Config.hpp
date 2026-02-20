#pragma once
#include <string>
#include <fstream>
#include <sstream>

namespace Config {
    constexpr int WINDOW_WIDTH = 1280;
    constexpr int WINDOW_HEIGHT = 720;
    constexpr const char* WINDOW_TITLE = "Top-Down Shooter";
    
    constexpr float PLAYER_SPEED = 200.0f;
    constexpr float PLAYER_MAX_HEALTH = 100.0f;
    constexpr float PLAYER_RADIUS = 20.0f;
    
    constexpr float ENEMY_SPEED = 100.0f;
    constexpr float ENEMY_HEALTH = 50.0f;
    constexpr float ENEMY_RADIUS = 25.0f;
    constexpr float BOSS_HEALTH_MULTIPLIER = 3.0f;
    
    constexpr float PROJECTILE_SPEED = 400.0f;
    constexpr float PROJECTILE_RADIUS = 5.0f;
    
    constexpr float PICKUP_RADIUS = 30.0f;
    constexpr float PICKUP_RANGE = 60.0f;
    
    class Settings {
    public:
        float volume;
        bool fullscreen;
        
        Settings() : volume(0.5f), fullscreen(false) {}
        
        void save(const std::string& filename = "settings.cfg");
        void load(const std::string& filename = "settings.cfg");
    };
    
    extern Settings settings;
}