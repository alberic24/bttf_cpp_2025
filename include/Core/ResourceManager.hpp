#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include <string>

class ResourceManager {
public:
    static ResourceManager& getInstance();
    
    sf::Font& getFont();
    sf::Texture& getTexture(const std::string& name);
    sf::Music& getMenuMusic();
    sf::Sound& getPistolSound();
    sf::Sound& getFireballSound();
    
private:
    ResourceManager();
    ~ResourceManager() = default;
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
    
    void loadTextures();
    void loadSounds();
    
    sf::Font defaultFont;
    std::map<std::string, sf::Texture> textures;
    sf::Music menuMusic;
    sf::SoundBuffer pistolBuffer;
    sf::SoundBuffer fireballBuffer;
    sf::Sound pistolSound;
    sf::Sound fireballSound;
};