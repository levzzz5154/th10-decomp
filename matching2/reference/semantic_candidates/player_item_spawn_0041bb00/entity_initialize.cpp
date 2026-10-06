// Stand-in for 0x00401DE0: keeps the entry register and hides the register
// kill set behind an external call, as retail's callers see it.
#include <string.h>
#include "th10/game/entity.hpp"
extern "C" void __cdecl EntityInitTail_00404f30(Entity* entity);
#pragma code_seg(".text$130entityinit")
__declspec(noinline) void __fastcall Entity_Init(void* unused, Entity* entity) {
    (void)unused;
    memset(entity, 0, sizeof(Entity));
    EntityInitTail_00404f30(entity);
}
#pragma code_seg()
