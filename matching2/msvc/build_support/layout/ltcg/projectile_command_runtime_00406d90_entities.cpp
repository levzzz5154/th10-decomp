// Compiler context only; this translation unit is never selected as recovered
// game code. It is the first context input of the equivalent 0x00406D90 model
// (build_support/contexts/equivalent/game/context/
// projectile_spawn_cell_start_script.cpp) with one section per compiled body
// instead of one merged section, so each body can be anchored at its retail
// address: the script loader 0x0043E710, the entity initialiser stand-in
// 0x00401DE0 and the script starter 0x00404F30.
#include <string.h>
#include "th10/game/entity.hpp"

// 0x0043E710: the animation script loader, object in EAX, resource in ECX and
// index in EBX (the section sorts after the sound queue's 0x0043DD10).
#define code_seg(name) code_seg(".text$zz_0043e710")
#include "../../../src/core/sprtanim/animation_object_load_script.cpp"
#undef code_seg

// 0x00401DE0 takes the entity in EDX; the stand-in hides its register kill set
// behind an external call, as in the starter's cluster.
extern "C" void __cdecl EntityInitTail_00404f30(Entity* entity);

#pragma code_seg(".text$00401de0_fn")
__declspec(noinline) void __fastcall Entity_Init(void* unused, Entity* entity) {
    (void)unused;
    memset(entity, 0, sizeof(Entity));
    EntityInitTail_00404f30(entity);
}
#pragma code_seg()

// 0x00404F30: reinitialise an animation object and start a script on it.
#define code_seg(name) code_seg(".text$00404f30_fn")
#include "../../../src/game/background/entity_start_script.cpp"
#undef code_seg
