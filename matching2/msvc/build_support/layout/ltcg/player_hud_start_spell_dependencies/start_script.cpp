// Compiler context only: the real script starter 0x00404F30, so the pass sees
// the callee's body and gives its callers the private register convention.
// Never selected from this cluster.
#include <string.h>
#include "th10/game/entity_script_start.hpp"

// 0x00401DE0 takes the entity in EDX and nothing else. This stand-in keeps the
// entry register and hides the register kill set behind an external call.
extern "C" void __cdecl EntityInitTail_00404f30(Entity* entity);

#pragma code_seg(".text$00401de0_fn")
__declspec(noinline) void __fastcall Entity_Init(void* unused, Entity* entity) {
    (void)unused;
    memset(entity, 0, sizeof(Entity));
    EntityInitTail_00404f30(entity);
}
#pragma code_seg()

#define code_seg(name) code_seg(".text$00404f30_fn")
#include "../../../../src/game/background/entity_start_script.cpp"
