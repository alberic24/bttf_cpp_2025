#pragma once

class Health {
public:
    float current;
    float maximum;
    
    Health(float max = 100.0f);
    
    void damage(float amount);
    void heal(float amount);
    bool isAlive() const;
    float getPercentage() const;
};