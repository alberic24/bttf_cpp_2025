#include "Components/Health.hpp"
#include <algorithm>

Health::Health(float max) : current(max), maximum(max) {}

void Health::damage(float amount) {
    current = std::max(0.0f, current - amount);
}

void Health::heal(float amount) {
    current = std::min(maximum, current + amount);
}

bool Health::isAlive() const {
    return current > 0.0f;
}

float Health::getPercentage() const {
    return (maximum > 0.0f) ? (current / maximum) : 0.0f;
}