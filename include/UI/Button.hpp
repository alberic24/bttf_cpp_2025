#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <functional>

class Button {
public:
    Button(float x, float y, float width, float height, const std::string& text, sf::Font& font);
    
    void draw(sf::RenderWindow& window);
    bool isClicked(sf::RenderWindow& window);
    void setCallback(std::function<void()> callback);
    void setPosition(float x, float y);
    
private:
    sf::RectangleShape shape;
    sf::Text label;
    std::function<void()> onClick;
    bool wasPressed;
};