#pragma once

// 0x0044C5D0 - Build a 2D vector from an angle and a radius:
// out = { cos(angle) * radius, sin(angle) * radius }.
void Vector2_FromAngle(float* out, float angle, float radius);
