#include "Entities/Enemy.hpp"
#include "Entities/Projectile.hpp"
#include "Core/ResourceManager.hpp"
#include "Utils/Config.hpp"
#include "Utils/Math.hpp"
#include <cmath>

Enemy::Enemy(float x, float y, bool isBoss)
    : transform(x, y), 
      health(isBoss ? Config::ENEMY_HEALTH * Config::BOSS_HEALTH_MULTIPLIER : Config::ENEMY_HEALTH),
      collider(Config::ENEMY_RADIUS, ColliderType::Enemy),
      isBoss(isBoss),
      shootCooldown(isBoss ? 1.0f : 2.0f),
      shootTimer(0.0f) {
    
    texture = &ResourceManager::getInstance().getTexture(isBoss ? "boss" : "enemy");
    sprite.setTexture(*texture);
    
    sf::Vector2u texSize = texture->getSize();
    sprite.setOrigin(texSize.x / 2.0f, texSize.y / 2.0f);
    
    float radius = isBoss ? Config::ENEMY_RADIUS * 1.5f : Config::ENEMY_RADIUS;
    float scale = (radius * 2.0f) / texSize.x;
    sprite.setScale(scale, scale);
    
    sprite.setPosition(x, y);
    
    if (isBoss) {
        collider.radius = Config::ENEMY_RADIUS * 1.5f;
    }
}

void Enemy::update(float dt, float playerX, float playerY, std::vector<Projectile*>& projectiles) {
    float dx = playerX - transform.x;
    float dy = playerY - transform.y;
    Math::normalize(dx, dy);
    
    transform.move(dx * Config::ENEMY_SPEED * dt, dy * Config::ENEMY_SPEED * dt);
    sprite.setPosition(transform.x, transform.y);
    
    shootTimer += dt;
    if (shootTimer >= shootCooldown) {
        shootAtPlayer(playerX, playerY, projectiles);
        shootTimer = 0.0f;
    }
}

void Enemy::shootAtPlayer(float playerX, float playerY, std::vector<Projectile*>& projectiles) {
    float angle = Math::angle(transform.x, transform.y, playerX, playerY);
    
    if (isBoss) {
        for (int i = -1; i <= 1; i++) {
            float spreadAngle = angle + i * Math::degToRad(15.0f);
            projectiles.push_back(new Projectile(
                transform.x, transform.y, 
                spreadAngle, 
                Config::PROJECTILE_SPEED * 0.8f, 
                15.0f, 
                false
            ));
        }
    } else {
        projectiles.push_back(new Projectile(
            transform.x, transform.y, 
            angle, 
            Config::PROJECTILE_SPEED * 0.7f, 
            10.0f, 
            false
        ));
    }
}

void Enemy::draw(sf::RenderWindow& window) {
    window.draw(sprite);
    
    // Barre de vie
    if (health.getPercentage() < 1.0f) {
        float barWidth = collider.radius * 2.0f;
        float barHeight = 5.0f;
        float barY = transform.y - collider.radius - 10.0f;
        
        sf::RectangleShape healthBar(sf::Vector2f(barWidth, barHeight));
        healthBar.setPosition(transform.x - collider.radius, barY);
        healthBar.setFillColor(sf::Color::Red);
        
        sf::RectangleShape healthBarFill(sf::Vector2f(barWidth * health.getPercentage(), barHeight));
        healthBarFill.setPosition(transform.x - collider.radius, barY);
        healthBarFill.setFillColor(sf::Color::Green);
        
        window.draw(healthBar);
        window.draw(healthBarFill);
    }
}