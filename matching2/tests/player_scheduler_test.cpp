#include "th10/game/player.hpp"

#include <cassert>
#include <cstring>

unsigned int DAT_00476f78;

int main() {
    unsigned char storage[0x500] = {};
    *(unsigned int*)(storage + 0x408) = 0;
    *(unsigned int*)(storage + 0x41C) = 0;
    *(unsigned short*)(storage + 0x446) = 9;
    Player_ResetSchedulerLinks(storage);
    assert(*(unsigned short*)(storage + 0x446) == 0);
    assert(*(unsigned int*)(storage + 0x3FC) == 0);
    assert(*(unsigned int*)(storage + 0x400) == 0);
    assert(*(unsigned int*)(storage + 0x3F8) == 0xFFFFFFFF);
    assert(*(unsigned int*)(storage + 0x410) == 0);
    assert(*(unsigned int*)(storage + 0x414) == 0);
    assert(*(unsigned int*)(storage + 0x40C) == 0xFFFFFFFF);
    return 0;
}
