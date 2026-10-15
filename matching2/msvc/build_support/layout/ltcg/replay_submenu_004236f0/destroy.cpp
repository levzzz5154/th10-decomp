#include "th10/game/replay_submenu_004236f0/state.hpp"
// 0x004297B0: destroy a platform resource after releasing the resources it
// owns. Retail passes the resource pointer in ESI and keeps it live across
// both calls (test esi,esi / push esi / call 0x004294A0 / push esi /
// call operator delete / pop ecx / ret).
#pragma code_seg(".text$02l")
void __stdcall SubPlatformResource_Destroy(PlatformResource* resource) {
    if (resource) {
        ReplayManager_Destroy_004294a0(resource);
        asm_free_004524a1(resource);
    }
}
#pragma code_seg()
