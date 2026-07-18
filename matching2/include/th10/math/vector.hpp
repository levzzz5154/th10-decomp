#pragma once

struct Vector2 {
    float x;
    float y;

    void SetPolar(float angle, float length);
};

void Vector2_SetPolar(Vector2* destination, float angle, float length);
