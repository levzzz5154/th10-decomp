#include "th10/render/camera_defaults.hpp"

#include <cstring>

// Primary 3D camera block (0x00491E94..0x00491EDC).
extern float DAT_00491e94;  // position.x
extern float DAT_00491e98;  // position.y
extern float DAT_00491e9c;  // position.z (1000)
extern float DAT_00491ea0;  // look-at target.x
extern float DAT_00491ea4;  // look-at target.y
extern float DAT_00491ea8;  // look-at target.z
extern float DAT_00491eac;  // up.x
extern float DAT_00491eb0;  // up.y (1)
extern float DAT_00491eb4;  // up.z
extern float DAT_00491ed0;  // rotation.x
extern float DAT_00491ed4;  // rotation.y
extern float DAT_00491ed8;  // rotation.z
extern float DAT_00491edc;  // field of view (pi/6)

// Background camera block (0x00491D7C..0x00491DC4).
extern float DAT_00491d7c;  // position.x
extern float DAT_00491d80;  // position.y
extern float DAT_00491d84;  // position.z (1000)
extern float DAT_00491d88;  // look-at target.x
extern float DAT_00491d8c;  // look-at target.y
extern float DAT_00491d90;  // look-at target.z
extern float DAT_00491d94;  // up.x
extern float DAT_00491d98;  // up.y (1)
extern float DAT_00491d9c;  // up.z
extern float DAT_00491db8;  // rotation.x
extern float DAT_00491dbc;  // rotation.y
extern float DAT_00491dc0;  // rotation.z
extern float DAT_00491dc4;  // field of view (pi/6)

// Full-window viewport (0x00491F60..0x00491F78, D3DVIEWPORT9 shape).
extern unsigned int DAT_00491f60;  // x
extern unsigned int DAT_00491f64;  // y
extern unsigned int DAT_00491f68;  // width (640)
extern unsigned int DAT_00491f6c;  // height (480)
extern float DAT_00491f70;         // min z
extern float DAT_00491f74;         // max z (1)
extern unsigned int DAT_00491f78;  // apply flag (1)

// Playfield viewport (0x00491E48..0x00491E60, D3DVIEWPORT9 shape).
extern unsigned int DAT_00491e48;  // x (32)
extern unsigned int DAT_00491e4c;  // y (16)
extern unsigned int DAT_00491e50;  // width (384)
extern unsigned int DAT_00491e54;  // height (448)
extern float DAT_00491e58;         // min z
extern float DAT_00491e5c;         // max z (1)
extern unsigned int DAT_00491e60;  // apply flag (0)

namespace {

// Retail stores the field of view as the raw dword 0x3F060A92 (pi/6);
// reproduce the exact bit pattern instead of trusting decimal rounding.
float BitsToFloat(unsigned int bits) {
    float value;
    memcpy(&value, &bits, sizeof(value));
    return value;
}

}  // namespace

// 0x004216F0 - Reset every camera and viewport global to the retail
// defaults. Store order follows the retail function; both cameras sit at
// (0, 0, 1000) looking at the origin with a +Y up vector, zero rotation,
// and a pi/6 field of view. The full-window viewport is marked for
// re-apply (flag 1) while the playfield viewport flag is cleared.
void Camera_ResetDefaults() {
    const float kFov = BitsToFloat(0x3F060A92u);

    DAT_00491e94 = 0.0f;
    DAT_00491e98 = 0.0f;
    DAT_00491e9c = 1000.0f;
    DAT_00491ea0 = 0.0f;
    DAT_00491ea4 = 0.0f;
    DAT_00491ea8 = 0.0f;
    DAT_00491eac = 0.0f;
    DAT_00491eb0 = 1.0f;
    DAT_00491eb4 = 0.0f;
    DAT_00491ed0 = 0.0f;
    DAT_00491ed4 = 0.0f;
    DAT_00491ed8 = 0.0f;

    DAT_00491d7c = 0.0f;
    DAT_00491d80 = 0.0f;
    DAT_00491d88 = 0.0f;
    DAT_00491d90 = 0.0f;
    DAT_00491d84 = 1000.0f;
    DAT_00491d98 = 1.0f;

    DAT_00491edc = kFov;

    DAT_00491f60 = 0;
    DAT_00491f64 = 0;
    DAT_00491f68 = 640;
    DAT_00491f6c = 480;
    DAT_00491f70 = 0.0f;
    DAT_00491f74 = 1.0f;
    DAT_00491f78 = 1;

    DAT_00491d8c = 0.0f;
    DAT_00491d94 = 0.0f;
    DAT_00491d9c = 0.0f;
    DAT_00491dc4 = kFov;

    DAT_00491e48 = 32;
    DAT_00491e4c = 16;
    DAT_00491e50 = 384;
    DAT_00491e54 = 448;
    DAT_00491e58 = 0.0f;
    DAT_00491e5c = 1.0f;
    DAT_00491e60 = 0;

    DAT_00491db8 = 0.0f;
    DAT_00491dbc = 0.0f;
    DAT_00491dc0 = 0.0f;
}
