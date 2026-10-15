// Compiler context only: the real handle lookup, so the pass derives its
// register arguments.
#include "th10/game/sprite_region_bind_00424480.hpp"

#pragma code_seg(".text$004491c0_fn")
AnimationObject_00424480* AnimationLists_00424480::Find(AnimationHandle_00424480 handle) {
    if (!handle.value)
        return 0;
    for (AnimationObject_00424480* node = primary; node != 0; node = node->next)
        if (*reinterpret_cast<unsigned int*>(node->object) == handle.value)
            return node->object;
    for (AnimationObject_00424480* node = secondary; node != 0; node = node->next)
        if (*reinterpret_cast<unsigned int*>(node->object) == handle.value)
            return node->object;
    return 0;
}
#pragma code_seg()
