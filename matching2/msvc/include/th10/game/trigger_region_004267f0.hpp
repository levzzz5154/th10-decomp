#ifndef TH10_GAME_TRIGGER_REGION_004267F0_HPP
#define TH10_GAME_TRIGGER_REGION_004267F0_HPP
#include <stddef.h>
#include "th10/math/oriented_rect_contact.hpp"
#include "th10/game/player.hpp"

struct TriggerDialogue_004267f0 {
    unsigned char reserved_000[0x9EB8];
    int active;                         // +0x9EB8
};

extern "C" {
extern TriggerDialogue_004267f0* data_0047770c;
}

#endif
