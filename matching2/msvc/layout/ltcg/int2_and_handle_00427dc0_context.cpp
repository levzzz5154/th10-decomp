#include "../../src/game/player/int2_add_00427dc0.cpp"
#include "th10/render/animation_handle.hpp"
#pragma code_seg(".text$03context")
extern "C" int __stdcall Int2HandleContext(Int2* out, const Int2* left, const Int2* right, AnimationHandle* handle, int count) {
    int valid = 0;
    for (int i = 0; i < count; ++i) { out[i] = left[i] + right[i]; valid += handle[i].Validate(); }
    return valid;
}
#pragma code_seg()
