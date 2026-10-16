#pragma once
#include <string.h>
#include <stddef.h>
#include "th10/math/timer.hpp"

// One 0x3AC-byte sprite of the spell-card manager's pools; built by 0x00402050
// and destroyed by 0x00401FF0.
struct CardSprite {
    unsigned char storage[0x3AC];

    __declspec(noinline) CardSprite();
    __declspec(noinline) ~CardSprite();
};

// The manager's frame timer starts out unregistered.
struct CardTimer : FrameTimer {
    CardTimer() { flags &= ~1u; }
};

// The 0x37B0-byte spell-card manager, as its constructor lays it out.
struct Card {
    unsigned int flags;
    unsigned char reserved_0004[0x10 - 0x04];
    CardSprite sprites_0010[2];
    unsigned char reserved_0768[0x778 - 0x768];
    CardSprite sprites_0778[8];
    CardSprite sprites_24d8[5];
    CardTimer frame_timer;
    unsigned char reserved_3748[0x37B0 - 0x3748];

    __declspec(noinline) Card();    // 0x00408910
};
typedef char CardSize[sizeof(Card) == 0x37B0 ? 1 : -1];
typedef char CardTimerOffset[offsetof(Card, frame_timer) == 0x3734 ? 1 : -1];

extern "C" Card* g_card;
