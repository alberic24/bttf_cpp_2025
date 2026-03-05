#pragma once
#include <SFML/Graphics.hpp>

class Player;

class HUD {
public:
    HUD(sf::Font& font);
    
    void draw(sf::RenderWindow& window, Player* player, int score);
    
private:
    sf::Font& font;
    sf::Text healthText;
    sf::Text ammoText;
    sf::Text weaponText;
    sf::Text scoreText;
    sf::RectangleShape healthBar;
    sf::RectangleShape healthBarBg;
};