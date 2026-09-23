// 0x00448600..0x0044860E: render animation bucket 1 for the task's manager.
// This zero-data derived view gives the slot-specific task a distinct C++ entry
// while keeping its manager base at offset zero.
#include "th10/render/quad_batch.hpp"

struct AnimationManagerBucket1_00448600 : AnimationManager_00442F50 {
    __declspec(noinline) int RenderBucket1();
};

#pragma code_seg(".text$01slot1")
int AnimationManagerBucket1_00448600::RenderBucket1() {
    return RenderBucket(1);
}
#pragma code_seg()
