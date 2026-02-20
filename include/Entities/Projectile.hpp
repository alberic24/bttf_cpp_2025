#pragma once
#include "Components/Transform.hpp"
#include "Components/Collider.hpp"
#include <SFML/Graphics.hpp>

class Projectile {
public:
    Projectile(float x, float y, float angle, float speed, float damage, bool isAoE = false);
    
    void update(float dt);
    void draw(sf::RenderWindow& window);
    
    Transform transform;
    Collider collider;
    
    float velocityX, velocityY;
    float damage;
    bool active;
    bool isAoE;        
    float aoeRadius;
    bool fromPlayer = false;
    
private:
    sf::Sprite sprite;
    sf::Texture* texture;
};