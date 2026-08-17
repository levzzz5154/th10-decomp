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

void Player_ResetSchedulerLinks(void* player) {
    unsigned char* bytes = (unsigned char*)player;
    *(uint16_t*)(bytes + 0x446) = 0;
    ResetPlayerSchedulerLink(bytes, 0x408, 0x3FC, 0x3F8, 0x400);
    ResetPlayerSchedulerLink(bytes, 0x41C, 0x410, 0x40C, 0x414);
}
