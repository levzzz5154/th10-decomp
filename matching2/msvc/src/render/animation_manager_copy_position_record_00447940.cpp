// Copy an animation position record and derive UV bounds and scale factors.
// The native LTCG context supplies index EAX, manager EDX, and source EBX.
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

#pragma code_seg(".text$01copy")
__declspec(noinline) void CopyPositionRecord_00447940(int index, AnimationPositionManager_00447940* manager, const AnimationPositionRecord_00447940* source) {
    manager->records[index] = *source;
    manager->records[index].u0 = manager->records[index].left / manager->records[index].textureWidth;
    manager->records[index].u1 = manager->records[index].right / manager->records[index].textureWidth;
    manager->records[index].v0 = manager->records[index].top / manager->records[index].textureHeight;
    manager->records[index].v1 = manager->records[index].bottom / manager->records[index].textureHeight;
    manager->records[index].scaleX = (manager->records[index].right - manager->records[index].left) / source->width;
    manager->records[index].scaleY = (manager->records[index].bottom - manager->records[index].top) / source->height;
}
#pragma code_seg()
