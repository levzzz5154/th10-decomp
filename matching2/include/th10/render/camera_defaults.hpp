#pragma once

// 0x004216F0 - Reset the render-side camera and viewport globals to the
// retail defaults: two look-at camera blocks (position (0,0,1000), origin
// target, +Y up, fov pi/6) and two viewports (the 640x480 full window and
// the 384x448 playfield at (32,16), both with the 0..1 depth range).
void Camera_ResetDefaults();
