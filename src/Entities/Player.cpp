#include "Entities/Player.hpp"
#include "Entities/Projectile.hpp"
#include "Weapons/Pistol.hpp"
#include "Weapons/FireballLauncher.hpp"
#include "Core/ResourceManager.hpp"
#include "Utils/Config.hpp"
#include "Utils/Math.hpp"
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>

Player::Player(float x, float y)
    : transform(x, y), health(Config::PLAYER_MAX_HEALTH),
      collider(Config::PLAYER_RADIUS, ColliderType::Player),
      currentWeaponIndex(0), shootPressed(false) {
    
    texture = &ResourceManager::getInstance().getTexture("player");
    sprite.setTexture(*texture);
    
    sf::Vector2u texSize = texture->getSize();
    sprite.setOrigin(texSize.x / 2.0f, texSize.y / 2.0f);
    
    float scale = (Config::PLAYER_RADIUS * 2.0f) / texSize.x;
    sprite.setScale(scale, scale);
    
    sprite.setPosition(x, y);
    
    weapons.push_back(std::make_unique<Pistol>());
    currentWeapon = weapons[0].get();
}

Player::~Player() {}

void Player::handleInput(sf::RenderWindow& window, float dt) {
    float moveX = 0.0f, moveY = 0.0f;
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
        moveY -= 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
        moveY += 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
        moveX -= 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        moveX += 1.0f;
    }
    
    Math::normalize(moveX, moveY);
    transform.move(moveX * Config::PLAYER_SPEED * dt, moveY * Config::PLAYER_SPEED * dt);
    
    transform.x = std::max(Config::PLAYER_RADIUS, std::min(transform.x, Config::WINDOW_WIDTH - Config::PLAYER_RADIUS));
    transform.y = std::max(Config::PLAYER_RADIUS, std::min(transform.y, Config::WINDOW_HEIGHT - Config::PLAYER_RADIUS));
    
    sprite.setPosition(transform.x, transform.y);
    
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    float angle = Math::angle(transform.x, transform.y, static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    transform.setRotation(Math::radToDeg(angle));
    sprite.setRotation(transform.rotation);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
        currentWeapon->reload();
    }
}
void Player::update(float dt, std::vector<Projectile*>& projectiles, sf::RenderWindow& window) {
    bool wantsToShoot = sf::Mouse::isButtonPressed(sf::Mouse::Left) || 
                        sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
    
    printf("wantsToShoot=%d shootPressed=%d canFire=%d ammo=%d\n",
        wantsToShoot, shootPressed, currentWeapon->canFire(), currentWeapon->getCurrentAmmo());
    
    if (wantsToShoot) {
        if (!shootPressed && currentWeapon->canFire()) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            printf("FIRING at target %.1f %.1f from %.1f %.1f\n", 
                (float)mousePos.x, (float)mousePos.y, transform.x, transform.y);
            currentWeapon->fire(transform.x, transform.y, 
                static_cast<float>(mousePos.x), static_cast<float>(mousePos.y), projectiles);
            printf("Projectiles after fire: %zu\n", projectiles.size());
        }
        shootPressed = true;
    } else {
        shootPressed = false;
    }
    
    // Changement d'arme (Tab ou B)
    static bool switchPressed = false;
    bool wantsToSwitch = sf::Keyboard::isKeyPressed(sf::Keyboard::Tab);
    
    if (wantsToSwitch && !switchPressed) {
        switchWeapon();
        switchPressed = true;
    } else if (!wantsToSwitch) {
        switchPressed = false;
    }
    
    currentWeapon->update(dt);
}

void Player::switchWeapon() {
    if (weapons.size() > 1) {
        currentWeaponIndex = (currentWeaponIndex + 1) % weapons.size();
        currentWeapon = weapons[currentWeaponIndex].get();
    }
}

void Player::pickupWeapon(WeaponType type) {
    // Vérifier si on a déjà cette arme
    for (const auto& weapon : weapons) {
        if (weapon->getType() == type) {
            weapon->reload(); // Recharger si on a déjà
            return;
        }
    }
    
    // Ajouter nouvelle arme
    if (type == WeaponType::Pistol) {
        weapons.push_back(std::make_unique<Pistol>());
    } else if (type == WeaponType::FireballLauncher) {
        weapons.push_back(std::make_unique<FireballLauncher>());
    }
    
    currentWeaponIndex = weapons.size() - 1;
    currentWeapon = weapons[currentWeaponIndex].get();
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}