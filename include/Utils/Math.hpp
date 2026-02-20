#pragma once
#include <cmath>

namespace Math {
    constexpr float PI = 3.14159265358979323846f;
    
    inline float distance(float x1, float y1, float x2, float y2) {
        float dx = x2 - x1;
        float dy = y2 - y1;
        return std::sqrt(dx * dx + dy * dy);
    }
    
    inline float angle(float x1, float y1, float x2, float y2) {
        return std::atan2(y2 - y1, x2 - x1);
    }
    
    inline float radToDeg(float rad) {
        return rad * 180.0f / PI;
    }
    
    inline float degToRad(float deg) {
        return deg * PI / 180.0f;
    }
    
    inline void normalize(float& x, float& y) {
        float length = std::sqrt(x * x + y * y);
        if (length > 0.0f) {
            x /= length;
            y /= length;
        }
    }
}