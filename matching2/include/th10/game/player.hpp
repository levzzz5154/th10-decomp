// =============================================================================
// player.hpp - Small player collision/update object used by 0x00405750..5AC0
// =============================================================================
#pragma once

struct Player {
    unsigned char unknown000[0x14];
    unsigned char timer[0x14];       // +0x14
    int activeState;                 // +0x28
    int animationHandle;             // +0x2C
    float position[3];               // +0x30
    float collisionRadius;           // +0x3C
    float secondaryRadius;           // +0x40
    int focusedCollision;            // +0x44
};

int Player_Init(Player* player);
int Player_HitTest(Player* player, const float* position);
int Player_Update(Player* player);
int Player_Draw(Player* player);
