#pragma once

class Transform {
public:
    float x, y;
    float rotation; // en degrés
    
    Transform(float x = 0.0f, float y = 0.0f, float rotation = 0.0f);
    
    void setPosition(float x, float y);
    void move(float dx, float dy);
    void setRotation(float angle);
};