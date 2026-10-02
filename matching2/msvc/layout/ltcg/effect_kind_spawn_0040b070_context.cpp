// Compiler context only; never selected as recovered game code.
#include "th10/game/effect_kind_spawn_0040b070.hpp"
#include "../../src/game/effect_kind_spawn_0040b070.cpp"

#pragma inline_depth(0)
#pragma code_seg(".text$0040a000_context")
extern "C" int __stdcall EffectKindSpawnContext(
        const int* kinds, EffectFileOwner_0040b070** owners, AnimationHandle_0040b070* outs,
        void** arguments, int count) {
    for (int index = 0; index < count; ++index) {
        outs[index] = owners[index]->SpawnEffect(arguments[index], kinds[index]);
    }
    return count;
}
#pragma code_seg()
#pragma inline_depth()
