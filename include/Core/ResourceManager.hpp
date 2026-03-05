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
    sf::Music& getGameplayMusic();
    sf::Sound& getPistolSound();
    sf::Sound& getFireballSound();
    sf::Sound& getExplosionSound();
    
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
    sf::Music gameplayMusic;
    sf::SoundBuffer pistolBuffer;
    sf::SoundBuffer fireballBuffer;
    sf::SoundBuffer explosionBuffer;
    sf::Sound pistolSound;
    sf::Sound fireballSound;
    sf::Sound explosionSound;
};