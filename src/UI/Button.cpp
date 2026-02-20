#include "UI/Button.hpp"
#include <SFML/Window/Mouse.hpp>

Button::Button(float x, float y, float width, float height, const std::string& text, sf::Font& font)
    : shape(sf::Vector2f(width, height)), label(text, font, 24), wasPressed(false) {
    
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color(70, 70, 70));
    shape.setOutlineThickness(2.0f);
    shape.setOutlineColor(sf::Color::White);
    
    sf::FloatRect textBounds = label.getLocalBounds();
    label.setPosition(
        x + (width - textBounds.width) / 2.0f - textBounds.left,
        y + (height - textBounds.height) / 2.0f - textBounds.top
    );
    label.setFillColor(sf::Color::White);
}

void Button::setPosition(float x, float y) {
    shape.setPosition(x, y);
    
    sf::FloatRect textBounds = label.getLocalBounds();
    sf::FloatRect shapeBounds = shape.getGlobalBounds();
    label.setPosition(
        x + (shapeBounds.width - textBounds.width) / 2.0f - textBounds.left,
        y + (shapeBounds.height - textBounds.height) / 2.0f - textBounds.top
    );
}

void Button::draw(sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::FloatRect bounds = shape.getGlobalBounds();
    
    if (bounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
        shape.setFillColor(sf::Color(100, 100, 100));
    } else {
        shape.setFillColor(sf::Color(70, 70, 70));
    }
    
    window.draw(shape);
    window.draw(label);
}

bool Button::isClicked(sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::FloatRect bounds = shape.getGlobalBounds();
    
    bool mouseOver = bounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    bool mousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
    
    if (mouseOver && mousePressed && !wasPressed) {
        wasPressed = true;
        if (onClick) onClick();
        return true;
    }
    
    if (!mousePressed) {
        wasPressed = false;
    }
    
    return false;
}

void Button::setCallback(std::function<void()> callback) {
    onClick = callback;
}