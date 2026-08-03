#include "th10/game/player.hpp"

typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
extern uint32_t DAT_00476f78;

static void ResetPlayerSchedulerLink(unsigned char* bytes,
                                     unsigned int flagOffset,
                                     unsigned int nextOffset,
                                     unsigned int previousOffset,
                                     unsigned int timeOffset) {
    if ((*(uint32_t*)(bytes + flagOffset) & 1u) == 0) {
        *(uint32_t*)(bytes + nextOffset) = 0;
        *(uint32_t*)(bytes + previousOffset) = 0xFFF0BDC1;
        *(uint32_t*)(bytes + timeOffset) = 0;
        *(uint32_t*)(bytes + timeOffset + 4) =
            (uint32_t)(unsigned long)&DAT_00476f78;
        *(uint32_t*)(bytes + flagOffset) |= 1u;
    }
    *(uint32_t*)(bytes + nextOffset) = 0;
    *(uint32_t*)(bytes + timeOffset) = 0;
    *(uint32_t*)(bytes + previousOffset) = 0xFFFFFFFF;
}

// 0x00405BE0 - Reset both player scheduler links to their inactive sentinels.
#ifdef _MSC_VER
__declspec(naked) void Player_ResetSchedulerLinksRetail() {
    __asm {
        xor edx, edx
        mov word ptr [eax+446h], dx
        mov ecx, [eax+408h]
        test cl, 1
        jnz loc_405C1D
        or ecx, 1
        mov [eax+3FCh], edx
        mov dword ptr [eax+3F8h], 0FFF0BDC1h
        mov [eax+400h], edx
        mov dword ptr [eax+404h], 476F78h
        mov [eax+408h], ecx
loc_405C1D:
        mov [eax+3FCh], edx
        mov [eax+400h], edx
        mov dword ptr [eax+3F8h], 0FFFFFFFFh
        mov ecx, [eax+41Ch]
        test cl, 1
        jnz loc_405C67
        or ecx, 1
        mov [eax+410h], edx
        mov dword ptr [eax+40Ch], 0FFF0BDC1h
        mov [eax+414h], edx
        mov dword ptr [eax+418h], 476F78h
        mov [eax+41Ch], ecx
loc_405C67:
        mov [eax+410h], edx
        mov [eax+414h], edx
        mov dword ptr [eax+40Ch], 0FFFFFFFFh
        ret
    }
}
#endif

void Player_ResetSchedulerLinks(void* player) {
    unsigned char* bytes = (unsigned char*)player;
    *(uint16_t*)(bytes + 0x446) = 0;
    ResetPlayerSchedulerLink(bytes, 0x408, 0x3FC, 0x3F8, 0x400);
    ResetPlayerSchedulerLink(bytes, 0x41C, 0x410, 0x40C, 0x414);
}
