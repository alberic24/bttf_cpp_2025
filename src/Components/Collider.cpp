#include "Components/Collider.hpp"
#include "Utils/Math.hpp"

Collider::Collider(float radius, ColliderType type)
    : radius(radius), type(type), active(true) {}

bool Collider::checkCollision(const Collider& other, float x1, float y1, float x2, float y2) const {
    if (!active || !other.active) return false;
    
    float dist = Math::distance(x1, y1, x2, y2);
    return dist < (radius + other.radius);
}