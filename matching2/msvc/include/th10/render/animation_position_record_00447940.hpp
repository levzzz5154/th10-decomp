#pragma once

// One sprite of an ANM file as the renderer keeps it: the pixel rectangle on
// its texture plus the derived UV bounds and scale factors.
struct AnimationPositionRecord_00447940 {
    unsigned int header[2];
    float left;          // +0x08
    float top;
    float right;
    float bottom;
    float textureHeight; // +0x18
    float textureWidth;
    float u0;            // +0x20
    float v0;
    float u1;
    float v1;
    float scaleY;        // +0x30
    float scaleX;
    float width;         // +0x38
    float height;
    unsigned int reserved40;
};
struct AnimationPositionManager_00447940 {
    unsigned char padding[0x118];
    AnimationPositionRecord_00447940* records;
};
typedef char PositionRecordSize_00447940[(sizeof(AnimationPositionRecord_00447940) == 0x44) ? 1 : -1];

// 0x00447940
__declspec(noinline) void CopyPositionRecord_00447940(
    int index, AnimationPositionManager_00447940* manager,
    const AnimationPositionRecord_00447940* source);
