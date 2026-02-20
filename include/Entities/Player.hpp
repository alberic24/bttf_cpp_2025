#pragma once
#include "Components/Transform.hpp"
#include "Components/Health.hpp"
#include "Components/Collider.hpp"
#include "Weapons/IWeapon.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

class Projectile;

class Player {
public:
    Player(float x, float y);
    ~Player();
    
    void handleInput(sf::RenderWindow& window, float dt);
    void update(float dt, std::vector<Projectile*>& projectiles, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    
    void switchWeapon();
    void pickupWeapon(WeaponType type);
    
    Transform transform;
    Health health;
    Collider collider;
    
    IWeapon* getCurrentWeapon() const { return currentWeapon; }
    
private:
    sf::Sprite sprite;
    sf::Texture* texture;
    std::vector<std::unique_ptr<IWeapon>> weapons;
    IWeapon* currentWeapon;
    int currentWeaponIndex;
    
    bool shootPressed;
};