#include "Entities/Projectile.hpp"
#include "Core/ResourceManager.hpp"
#include "Utils/Config.hpp"
#include <cmath>
#include "Utils/Math.hpp"

Projectile::Projectile(float x, float y, float angle, float speed, float damage, bool isAoE)
    : transform(x, y, angle), collider(Config::PROJECTILE_RADIUS, ColliderType::Projectile),
      damage(damage), active(true), isAoE(isAoE), aoeRadius(80.0f) {
    
    velocityX = std::cos(angle) * speed;
    velocityY = std::sin(angle) * speed;
    
    texture = &ResourceManager::getInstance().getTexture(isAoE ? "fireball" : "bullet");
    sprite.setTexture(*texture);
    
    sf::Vector2u texSize = texture->getSize();
    sprite.setOrigin(texSize.x / 2.0f, texSize.y / 2.0f);
    
    float size = isAoE ? 16.0f : 8.0f;
    float scale = size / texSize.x;
    sprite.setScale(scale, scale);
    
    sprite.setPosition(x, y);
    sprite.setRotation(Math::radToDeg(angle));
    
    if (isAoE) {
        collider.radius = 8.0f;
    }
}

void Projectile::update(float dt) {
    transform.move(velocityX * dt, velocityY * dt);
    sprite.setPosition(transform.x, transform.y);
}

void Projectile::draw(sf::RenderWindow& window) {
    if (active) {
        window.draw(sprite);
    }
}