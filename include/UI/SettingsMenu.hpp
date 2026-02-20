#pragma once
#include "Button.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

class SettingsMenu {
public:
    SettingsMenu(sf::Font& font, sf::RenderWindow* window); 
    
    bool update(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    
private:
    sf::Font& font;
    sf::RenderWindow* gameWindow;
    sf::Text title;
    sf::Text volumeText;
    sf::Text fullscreenText;
    
    std::unique_ptr<Button> backButton;
    std::unique_ptr<Button> volumeUpButton;
    std::unique_ptr<Button> volumeDownButton;
    std::unique_ptr<Button> fullscreenToggle;
    
    void updateTexts();
    void applyFullscreen();
};