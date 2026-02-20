#include "Components/Transform.hpp"

Transform::Transform(float x, float y, float rotation)
    : x(x), y(y), rotation(rotation) {}

void Transform::setPosition(float x, float y) {
    this->x = x;
    this->y = y;
}

void Transform::move(float dx, float dy) {
    x += dx;
    y += dy;
}

void Transform::setRotation(float angle) {
    rotation = angle;
}