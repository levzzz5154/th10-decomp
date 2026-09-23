// 0x00448610..0x0044861E: render animation bucket 2 for the task's manager.
#include "th10/render/quad_batch.hpp"

// The derived view adds no fields: the retail manager remains at offset zero.
struct AnimationManagerBucket2_00448610 : AnimationManager_00442F50 {
    __declspec(noinline) int RenderBucket2();
};

#pragma code_seg(".text$01slot2")
int AnimationManagerBucket2_00448610::RenderBucket2() {
    return RenderBucket(2);
}
#pragma code_seg()
