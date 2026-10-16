// Copy an animation position record and derive UV bounds and scale factors.
// The native LTCG context supplies index EAX, manager EDX, and source EBX.
#include "th10/render/animation_position_record.hpp"

#ifndef COPY_POSITION_RECORD_SECTION
#define COPY_POSITION_RECORD_SECTION ".text$01copy"
#endif
#pragma code_seg(COPY_POSITION_RECORD_SECTION)
__declspec(noinline) void CopyPositionRecord2(int index, AnimationPositionManager* manager, const AnimationPositionRecord* source) {
    manager->records[index] = *source;
    manager->records[index].u0 = manager->records[index].left / manager->records[index].textureWidth;
    manager->records[index].u1 = manager->records[index].right / manager->records[index].textureWidth;
    manager->records[index].v0 = manager->records[index].top / manager->records[index].textureHeight;
    manager->records[index].v1 = manager->records[index].bottom / manager->records[index].textureHeight;
    manager->records[index].scaleX = (manager->records[index].right - manager->records[index].left) / source->width;
    manager->records[index].scaleY = (manager->records[index].bottom - manager->records[index].top) / source->height;
}
#pragma code_seg()
