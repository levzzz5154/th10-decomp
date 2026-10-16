// Compiler context only; never selected as recovered game code.
#include "th10/game/sprite_region_bind.hpp"
#include "../../../src/game/pause/sprite_region_bind.cpp"

#pragma inline_depth(0)
#pragma code_seg(".text$0040a000_context")
extern "C" int __stdcall SpriteRegionBindContext(SpriteRegion** regions,
        const AnimationHandle8* handles, int count) {
    int total = 0;
    for (int index = 0; index < count; ++index)
        total += regions[index]->BindToAnimation(handles[index], 32, 16, 384, 448);
    return total;
}
#pragma code_seg()
#pragma inline_depth()
