// Compiler context only; never selected as recovered game code.
#include "th10/game/sprite_region_bind_00424480.hpp"
#include "../../src/game/pause/sprite_region_bind_00424480.cpp"

#pragma inline_depth(0)
#pragma code_seg(".text$0040a000_context")
extern "C" int __stdcall SpriteRegionBindContext(SpriteRegion_00424480** regions,
        const AnimationHandle_00424480* handles, int count) {
    int total = 0;
    for (int index = 0; index < count; ++index)
        total += regions[index]->BindToAnimation(handles[index], 32, 16, 384, 448);
    return total;
}
#pragma code_seg()
#pragma inline_depth()
