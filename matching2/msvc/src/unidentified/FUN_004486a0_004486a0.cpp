// 0x004486A0..0x004486AE: render animation bucket 4 for the task's manager.
#include "th10/render/quad_batch.hpp"

// The derived view adds no fields: the retail manager remains at offset zero.
struct AnimationManagerBucket4_004486A0 : AnimationManager_00442F50 {
    __declspec(noinline) int RenderBucket4();
};

#pragma code_seg(".text$01slot4")
int AnimationManagerBucket4_004486A0::RenderBucket4() {
    return RenderBucket(4);
}
#pragma code_seg()
