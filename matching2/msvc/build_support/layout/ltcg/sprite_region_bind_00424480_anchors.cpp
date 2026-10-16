// Compiler context only: the real handle lookup, so the pass derives its
// register arguments.
#include "th10/game/sprite_region_bind.hpp"

#pragma code_seg(".text$004491c0_fn")
AnimationObject2* AnimationLists5::Find(AnimationHandle8 handle) {
    if (!handle.value)
        return 0;
    for (AnimationObject2* node = primary; node != 0; node = node->next)
        if (*reinterpret_cast<unsigned int*>(node->object) == handle.value)
            return node->object;
    for (AnimationObject2* node = secondary; node != 0; node = node->next)
        if (*reinterpret_cast<unsigned int*>(node->object) == handle.value)
            return node->object;
    return 0;
}
#pragma code_seg()
