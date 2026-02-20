#include "Core/ResourceManager.hpp"
#include "Utils/Config.hpp"
#include <iostream>

ResourceManager& ResourceManager::getInstance() {
    static ResourceManager instance;
    return instance;
}

ResourceManager::ResourceManager() {
    if (!defaultFont.loadFromFile("assets/OpenSans-Regular.ttf")) {
        if (!defaultFont.loadFromFile("../assets/OpenSans-Regular.ttf")) {
            if (!defaultFont.loadFromFile("src/assets/OpenSans-Regular.ttf")) {
                std::cerr << "Warning: Could not load OpenSans font. Using default SFML font." << std::endl;
            }
        }
    } else {
        std::cout << "✓ Font loaded successfully!" << std::endl;
    }
    
    loadTextures();
    
    if (menuMusic.openFromFile("assets/menu_music.ogg") || 
        menuMusic.openFromFile("../assets/menu_music.ogg") ||
        menuMusic.openFromFile("src/assets/menu_music.ogg")) {
        menuMusic.setLoop(true);
        menuMusic.setVolume(Config::settings.volume * 100);
        std::cout << "✓ Menu music loaded successfully!" << std::endl;
    }
}

void ResourceManager::loadTextures() {
    std::vector<std::string> basePaths = {"assets/", "../assets/", "src/assets/"};
    
    std::map<std::string, std::string> textureFiles = {
        {"player", "player.png"},
        {"enemy", "enemy1.png"},
        {"boss", "enemy4.png"},
        {"bullet", "bullet.png"},
        {"fireball", "fireball.png"},
        {"menu_background", "slide-d'acceuil.png"}
    };
    
    for (const auto& [name, file] : textureFiles) {
        bool loaded = false;
        for (const auto& basePath : basePaths) {
            if (textures[name].loadFromFile(basePath + file)) {
                std::cout << "✓ Loaded texture: " << name << std::endl;
                loaded = true;
                break;
            }
        }
        if (!loaded) {
            std::cerr << "✗ Failed to load texture: " << name << std::endl;
        }
    }
}

sf::Font& ResourceManager::getFont() {
    return defaultFont;
}

sf::Texture& ResourceManager::getTexture(const std::string& name) {
    return textures[name];
}

sf::Music& ResourceManager::getMenuMusic() {
    return menuMusic;
}