// =============================================================================
// player.cpp - Player entity update, collision, and management
// Functions: 0x00405860 (Player_Init), 0x00405750 (Player_Update),
//            0x004059F0 (Player_HitTest), 0x00405AC0 (Player_Draw),
//            0x00405B60 (Player_AdjustPower)
// =============================================================================
#include "th10/game/entity.hpp"
#include "th10/game/game_state.hpp"
#include "th10/game/player.hpp"

extern void* g_pGameStateManager;
extern uint32_t DAT_004776f4;    // player game state ptr
extern uint32_t DAT_004776f0;    // another game state
extern uint32_t DAT_00477704;    // global config
extern uint32_t DAT_00477834;    // player position source
extern uint32_t DAT_0047781c;    // item manager
extern uint32_t DAT_00474c48;    // player power level
extern uint32_t DAT_00474c68;    // player character (0=Reimu, 1=Marisa)
extern int32_t  DAT_00474c98;    // player speed adjustment
extern float    _DAT_00470afc;   // 1.0f
extern float    _DAT_00470d34;   // alt speed
extern float    _DAT_00470b0c;   // focused speed
extern float    _DAT_00470b48;   // render-space Y offset
extern float    _DAT_00470b4c;   // render-space X offset
extern uint32_t DAT_00476f78;     // timer sentinel

void PlayerTimer_Tick(void* timer);
void* AnimationManager_Find(void* manager, int animationHandle);
void AnimationManager_SetPosition(
    void* manager, int animationHandle, const float* position);
void EnemyManager_CheckPlayerCollision(
    void* gameState, const float* position, float radius,
    int allowEffect, int focused);
void ItemManager_CollectNearPlayer(
    void* itemManager, const float* position, float radius, int allowEffect);
void FUN_0043dd10(void);
void FUN_0043e5a0(int handle, int idx);
void FUN_004054b0(int val1, int val2, int val3);
void FUN_00405500(void);
int PlayerAnimation_Create(
    void* resource, void* scratch, int animationIndex,
    const float* position);

// ============================================================================
// 0x00405860 - Player_Init (start a new frame/player life)
// param_1 = player object (contains position, power, state at various offsets)
// Returns 0 on success, -1 if already active
//
// Ghidra decompilation:
//   if (param_1+0x28 != 0): return -1  (already active)
//   param_1+0x28 = 1  (mark active)
//   Initialize scheduler at +0x24 (if not already)
//   Set timer: +0x18=0, +0x1C=0, +0x14=0xFFFFFFFF
//   Set hitbox: +0x3C=32.0f (0x42000000), +0x40=4.0f (0x40800000)
//   Copy position from DAT_00477834 (+0x3C0..+0x3C8)
//   Load sprite handle from player state
//   Set +0x2C = sprite handle
//   Calculate power display: FUN_004054b0(power/20, power/20, (power%20)*100/20)
//   Adjust speed: DAT_00474c98 -= 0x80; clamp to [-0x400, 0x400]
//   Check if player is slow (grazing mode): set +0x44
// ============================================================================
int Player_Init(Player* player) {
    int* words = (int*)player;
    if (player->activeState != 0) {
        return -1;
    }
    player->activeState = 1;

    // Initialize scheduler chain if needed
    if ((words[9] & 1) == 0) {  // +0x24
        words[6] = 0;           // +0x18
        words[5] = 0xFFF0BDC1;  // +0x14
        words[7] = 0;           // +0x1C
        words[8] = (int)&DAT_00476f78;
        words[9] |= 1;
    }
    words[6] = 0;
    words[7] = 0;
    words[5] = 0xFFFFFFFF;

    // Set hitbox sizes
    player->collisionRadius = 32.0f;
    player->secondaryRadius = 4.0f;

    // Copy position from global
    int src = DAT_00477834;
    player->position[0] = *(float*)(src + 0x3C0);
    player->position[1] = *(float*)(src + 0x3C4);
    player->position[2] = *(float*)(src + 0x3C8);

    int animationIndex;
    int inputState = *(int*)(DAT_004776f4 + 0x3788);
    if (((*(uint8_t*)(DAT_004776f4 + 0x378C) & 1) != 0 &&
         inputState >= 0x5D && inputState <= 0x60) || inputState == 0x6D) {
        animationIndex = 0x1B9;
    } else {
        animationIndex = (DAT_00474c68 != 0 ? 7 : 0) + 0x190;
    }

    uint32_t animationScratch[3];
    player->animationHandle = PlayerAnimation_Create(
        *(void**)(DAT_004776f0 + 0x3E0B50), animationScratch,
        animationIndex, player->position);

    // Initialize sprite
    FUN_0043dd10();

    // Calculate power display
    int power = (int)DAT_00474c48;
    int powerMajor = power / 0x14;
    int powerMinor = (power % 0x14) * 100 / 0x14;
    FUN_004054b0(powerMajor, powerMajor, powerMinor);

    // Adjust speed
    DAT_00474c98 -= 0x80;
    if (DAT_00474c98 < 0x401) {
        if (DAT_00474c98 < -0x400) {
            DAT_00474c98 = -0x400;
        }
    } else {
        DAT_00474c98 = 0x400;
    }

    // Check grazing mode
    int playerState = DAT_004776f4;
    if ((*(uint8_t*)(playerState + 0x378C) & 1) != 0 &&
        *(int*)(playerState + 0x3738) > 0x3B) {
        player->focusedCollision = 1;
        return 0;
    }
    player->focusedCollision = 0;
    return 0;
}

// ============================================================================
// 0x004059F0 - Player_HitTest: Check collision between player and bullets
// The retail ABI used ECX for the player and EAX for the tested position. Both
// are explicit in the clean interface.
// Returns: 0 = no hit, 3/5/0x10/0x21/0x26 = different hit types
//
// Ghidra decompilation:
//   if (player+0x28 == 0): return 0  (not active)
//   dx = bullet[0] - player+0x30
//   dy = bullet[1] - player+0x34
//   if (dx*dx + dy*dy < hitbox^2):
//     if (player+0x44 == 0):  // not focused
//       if (grazing): return 3
//       else: return 5 or 0x21 (based on difficulty)
//     else:  // focused
//       if (grazing): return 0x26
//       else: return 0x1A or 0x1D
//   else: check for graze distance
// ============================================================================
int Player_HitTest(Player* player, const float* bulletPos) {
    if (player->activeState == 0) {
        return 0;
    }

    int result = 0;
    float dx = bulletPos[0] - player->position[0];
    float dy = bulletPos[1] - player->position[1];
    float hitbox = player->collisionRadius;

    if (dx * dx + dy * dy < hitbox * hitbox) {
        // Direct hit
        if (player->focusedCollision == 0) {
            if ((*(uint8_t*)(DAT_004776f4 + 0x378C) & 1) != 0) {
                return 3;
            }
        } else {
            if ((*(uint8_t*)(DAT_004776f4 + 0x378C) & 1) != 0) {
                return 0x26;
            }
        }
        return ((-(uint32_t)(*(int*)(DAT_00477704 + 0x10) != 0)) & 0x21) + 5;
    }

    // Graze check
    if ((*(uint8_t*)(DAT_004776f4 + 0x378C) & 1) == 0) {
        if (*(int*)(DAT_00477704 + 0x10) != 0 && player->focusedCollision == 0) {
            result = (uint32_t)(DAT_00474c68 == 0) * 4 + 0x10;
        }
    } else if (player->focusedCollision == 1) {
        return (-(uint32_t)(DAT_00474c68 != 0) & 0xFFFFFFFD) + 0x1A;
    }

    return result;
}

// ============================================================================
// 0x00405750 - Player_Update: Update player state for this frame
// The retail callback wrapper copied ECX into EDI before entering this body;
// the clean interface receives the player normally.
// Handles movement, collision, timer ticking
//
// Ghidra decompilation:
//   if (player+0x28 == 1):
//     Play sound, update timer
//     Adjust speed based on character/focus state
//     Call FUN_004492F0 (animation update)
//     Call FUN_00405AC0 (draw)
//   Call Timer_Tick (advance frame timer)
// ============================================================================
int Player_Update(Player* player) {
    void* mgr = g_pGameStateManager;

    if (player->activeState != 0) {
        if (player->activeState == 1) {
            uint8_t* animation = (uint8_t*)AnimationManager_Find(
                mgr, player->animationHandle);
            if (animation == 0) {
                player->animationHandle = 0;
                player->activeState = 0;
                return 1;
            }

            // Determine speed based on character and focus state
            float speedAdjust;
            int playerState = DAT_004776f4;
            if ((*(uint8_t*)(playerState + 0x378C) & 1) == 0 ||
                (*(int*)(playerState + 0x3788) < 0x5D || *(int*)(playerState + 0x3788) > 0x60) &&
                *(int*)(playerState + 0x3788) != 0x6D) {
                if (DAT_00474c68 == 0) {
                    speedAdjust = player->position[1] - _DAT_00470afc;
                } else {
                    speedAdjust = player->position[1] - _DAT_00470d34;
                }
            } else {
                speedAdjust = player->position[1] - _DAT_00470b0c;
            }
            player->position[1] = speedAdjust;

            float renderPosition[3] = {
                player->position[0] + _DAT_00470b4c,
                player->position[1] + _DAT_00470b48,
                player->position[2]
            };
            AnimationManager_SetPosition(
                mgr, player->animationHandle, renderPosition);
            player->collisionRadius = *(float*)(animation + 0x40);
            Player_Draw(player);
        }
        PlayerTimer_Tick(player->timer);
    }
    return 1;
}

// ============================================================================
// 0x00405AC0 - Player_Draw: Render the player sprite
// The retail body received the player in ESI; the clean interface uses a
// normal typed argument.
// Calls FUN_00408100 with hitbox radius and flags
//
// Ghidra decompilation:
//   if (player+0x28 != 0):
//     Determine focus state
//     FUN_00408100(hitbox, ~flags & 1, focused)
//     FUN_0041C800()
// ============================================================================
int Player_Draw(Player* player) {
    if (player->activeState != 0) {
        int playerState = DAT_004776f4;
        int focused;
        float hitbox = player->collisionRadius;

        if ((*(uint8_t*)(playerState + 0x378C) & 1) == 0 ||
            *(int*)(playerState + 0x3788) < 0x5D ||
            *(int*)(playerState + 0x3788) > 0x60) {
            if (*(int*)(playerState + 0x3788) != 0x6D) {
                focused = 1;
            } else {
                focused = 0;
            }
        } else {
            focused = 0;
        }

        int allowEffect = ~*(uint32_t*)(playerState + 0x378C) & 1;
        EnemyManager_CheckPlayerCollision(
            (void*)DAT_004776f0, player->position, hitbox,
            allowEffect, focused);
        ItemManager_CollectNearPlayer(
            (void*)DAT_0047781c, player->position, hitbox, allowEffect);
    }
    return 0;
}
