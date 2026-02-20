#pragma once
#include "Components/Transform.hpp"
#include "Components/Health.hpp"
#include "Components/Collider.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

class Projectile;

class Enemy {
public:
    Enemy(float x, float y, bool isBoss = false);
    
    void update(float dt, float playerX, float playerY, std::vector<Projectile*>& projectiles);
    void draw(sf::RenderWindow& window);
    
    Transform transform;
    Health health;
    Collider collider;
    
    bool isBoss;
    float shootCooldown;
    float shootTimer;
    
private:
    sf::Sprite sprite;
    sf::Texture* texture;
    void shootAtPlayer(float playerX, float playerY, std::vector<Projectile*>& projectiles);
};