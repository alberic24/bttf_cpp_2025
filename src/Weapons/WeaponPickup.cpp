#include "Weapons/WeaponPickup.hpp"
#include "Utils/Config.hpp"

WeaponPickup::WeaponPickup(float x, float y, WeaponType type)
    : transform(x, y), collider(Config::PICKUP_RADIUS, ColliderType::Pickup),
      weaponType(type), pickedUp(false), shape(Config::PICKUP_RADIUS) {
    
    shape.setOrigin(Config::PICKUP_RADIUS, Config::PICKUP_RADIUS);
    shape.setPosition(x, y);
    
    if (type == WeaponType::Pistol) {
        shape.setFillColor(sf::Color(100, 100, 255, 200));
    } else {
        shape.setFillColor(sf::Color(255, 100, 50, 200));
    }
    
    shape.setOutlineThickness(2.0f);
    shape.setOutlineColor(sf::Color::White);
}

WeaponPickup::~WeaponPickup() {}

void WeaponPickup::draw(sf::RenderWindow& window) {
    if (!pickedUp) {
        window.draw(shape);
    }
}