#pragma once

// Oriented rectangle vs. circle overlap test (retail 0x0041E4D0).
struct OrientedRectVec2 { float x, y; };

// --- 0x0041E4D0: rotated rectangle/circle overlap ---------------------------
struct OrientedRect {
	OrientedRectVec2 center;
	float angle;
	float width;
	float height;
};

int OrientedRect_IntersectsCircle(const OrientedRect* rect,
                                  const OrientedRectVec2* circle_center,
                                  float radius);
