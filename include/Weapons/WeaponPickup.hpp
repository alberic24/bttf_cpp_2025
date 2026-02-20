#pragma once
#include "IWeapon.hpp"
#include "Components/Transform.hpp"
#include "Components/Collider.hpp"
#include <SFML/Graphics.hpp>

class WeaponPickup {
public:
    WeaponPickup(float x, float y, WeaponType type);
    ~WeaponPickup();
    
    void draw(sf::RenderWindow& window);
    
    Transform transform;
    Collider collider;
    WeaponType weaponType;
    bool pickedUp;
    
    sf::CircleShape shape;
};