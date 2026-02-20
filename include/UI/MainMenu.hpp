#pragma once
#include "Button.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

enum class MenuAction {
    None,
    StartGame,
    Settings,
    Quit
};

class MainMenu {
public:
    MainMenu(sf::Font& font);
    
    MenuAction update(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    
private:
    sf::Font& font;
    sf::Text title;
    sf::Sprite backgroundSprite;     
    sf::Texture* backgroundTexture;  
    std::vector<std::unique_ptr<Button>> buttons;
    MenuAction currentAction;
};