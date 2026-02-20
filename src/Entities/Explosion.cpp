#include "Entities/Explosion.hpp"

Explosion::Explosion(float x, float y, float radius)
    : x(x), y(y), maxRadius(radius), currentRadius(0.0f),
      lifetime(0.5f), timer(0.0f), finished(false), shape(radius) {
    
    shape.setOrigin(radius, radius);
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color(255, 100, 0, 150));
    shape.setOutlineThickness(2.0f);
    shape.setOutlineColor(sf::Color(255, 200, 0, 200));
}

void Explosion::update(float dt) {
    timer += dt;
    
    if (timer >= lifetime) {
        finished = true;
        return;
    }
    
    float progress = timer / lifetime;
    currentRadius = maxRadius * progress;
    shape.setRadius(currentRadius);
    shape.setOrigin(currentRadius, currentRadius);
    
    sf::Color color = shape.getFillColor();
    color.a = static_cast<sf::Uint8>(150 * (1.0f - progress));
    shape.setFillColor(color);
}

void Explosion::draw(sf::RenderWindow& window) {
    if (!finished) {
        window.draw(shape);
    }
}