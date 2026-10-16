#pragma once

// Animation object and resource record views used by ConfigureFromResource
// (0x0043E5A0).
struct AnimationObject3;

struct Resource2 {
    unsigned char reserved[0x200];

    __declspec(noinline) int ConfigureObject(AnimationObject3* object, int index);
};

struct Matrix4x42 {
    float values[4][4];

    __forceinline void SetIdentity();
};

struct AnimationObject3 {
    unsigned char reserved_0000[0x04C];
    float width;                                       // +0x04C
    float height;                                      // +0x050
    unsigned char reserved_054[0x23C - 0x054];
    Matrix4x42 block_a;                        // +0x23C
    Matrix4x42 block_copy;                     // +0x27C
    Matrix4x42 block_b;                        // +0x2BC
    unsigned char reserved_2fc[0x308 - 0x2FC];
    Resource2* resource;                       // +0x308
    unsigned char reserved_30c[0x384 - 0x30C];
    unsigned short record_index;                       // +0x384
    unsigned char reserved_386[0x394 - 0x386];
    unsigned char* record;                             // +0x394
};

__forceinline void Matrix4x42::SetIdentity() {
    values[3][2] = 0.0f;
    values[3][1] = 0.0f;
    values[3][0] = 0.0f;
    values[2][3] = 0.0f;
    values[2][1] = 0.0f;
    values[2][0] = 0.0f;
    values[1][3] = 0.0f;
    values[1][2] = 0.0f;
    values[1][0] = 0.0f;
    values[0][3] = 0.0f;
    values[0][2] = 0.0f;
    values[0][1] = 0.0f;
    values[3][3] = 1.0f;
    values[2][2] = 1.0f;
    values[1][1] = 1.0f;
    values[0][0] = 1.0f;
}
