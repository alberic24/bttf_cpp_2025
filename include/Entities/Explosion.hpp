#pragma once
#include <SFML/Graphics.hpp>

class Explosion {
public:
    Explosion(float x, float y, float radius);
    
    void update(float dt);
    void draw(sf::RenderWindow& window);
    
    bool isFinished() const { return finished; }
    
private:
    sf::CircleShape shape;
    float x, y;
    float maxRadius;
    float currentRadius;
    float lifetime;
    float timer;
    bool finished;
};