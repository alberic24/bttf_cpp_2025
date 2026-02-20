#pragma once

enum class ColliderType {
    Player,
    Enemy,
    Projectile,
    Wall,
    Pickup
};

class Collider {
public:
    float radius;
    ColliderType type;
    bool active;
    
    Collider(float radius, ColliderType type);
    
    bool checkCollision(const Collider& other, float x1, float y1, float x2, float y2) const;
};