// 0x00401DE0 takes the entity in EDX and nothing else, and no retail caller
// relies on EDX surviving it. The recovered body (src/game/
// entity_initialize.cpp) would tell this link that EDX is preserved,
// so this stand-in keeps the entry register and hides the register kill set
// behind an external call. It only fixes the call's shape.
#include <string.h>
#include "th10/game/entity.hpp"

extern "C" void __cdecl EntityInitTail_00404f30(Entity* entity);

#pragma code_seg(".text$f00401de0F")
__declspec(noinline) void __fastcall Entity_Init(void* unused, Entity* entity) {
    (void)unused;
    memset(entity, 0, sizeof(Entity));
    EntityInitTail_00404f30(entity);
}
#pragma code_seg()
