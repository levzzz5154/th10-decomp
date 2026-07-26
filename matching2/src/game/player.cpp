// =============================================================================
// player.cpp - Player entity update, collision, and management
// Functions: 0x00405860 (Player_Init), 0x00405750 (Player_Update),
//            0x004059F0 (Player_HitTest), 0x00405AC0 (Player_Draw),
//            0x00405B60 (Player_AdjustPower)
// =============================================================================
#include "th10/game/entity.hpp"
#include "th10/game/game_state.hpp"
#include "th10/game/player.hpp"
#include "th10/game/scheduler.hpp"
#include "th10/math/timer.hpp"
#include "th10/render/animation_manager.hpp"

extern void* g_pGameStateManager;
extern uint32_t DAT_004776f4;    // player game state ptr
extern uint32_t DAT_004776ec;    // live 0x48-byte player runtime
extern uint32_t DAT_00491be4;    // scheduler device
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
extern float    _DAT_00470b40;   // right gameplay bound
extern float    _DAT_00470b3c;   // left gameplay bound
extern float    _DAT_00470b04;   // lower gameplay bound
extern float    _DAT_00470b38;   // upper gameplay bound
extern uint32_t DAT_00476f78;     // timer sentinel

// 0x004045B0 - Arm the player's startup scheduler and set its first value.
void Player_ArmSchedulerValue(void* scheduler, int) {
    uint8_t* bytes = (uint8_t*)scheduler;
    uint32_t flags = *(uint32_t*)(bytes + 0x2a2c);
    if ((flags & 1) == 0) {
        *(uint32_t*)(bytes + 0x2a20) = 0;
        *(uint32_t*)(bytes + 0x2a1c) = 0xFFF0BDC1;
        *(uint32_t*)(bytes + 0x2a24) = 0;
        *(uint32_t*)(bytes + 0x2a28) = (uint32_t)&DAT_00476f78;
        *(uint32_t*)(bytes + 0x2a2c) = flags | 1;
    }
    *(uint32_t*)(bytes + 0x2a20) = 0x3c;
    *(uint32_t*)(bytes + 0x2a24) = 0x42700000;
    *(uint32_t*)(bytes + 0x2a1c) = 0x3b;
    *(uint32_t*)(bytes + 0x2a18) |= 4;
}

void EnemyManager_CheckPlayerCollision(
    void* gameState, const float* position, float radius,
    int allowEffect, int focused) {
    if (gameState == nullptr || position == nullptr)
        return;
    auto* entry = static_cast<unsigned char*>(gameState) + 0x60;
    for (int index = 0; index < 2000; ++index, entry += 0x7f0) {
        const unsigned short phase =
            *reinterpret_cast<unsigned short*>(entry + 0x446);
        if (phase == 0 || phase == 3)
            continue;
        if (focused != 0 &&
            *reinterpret_cast<int*>(entry + 4) != 0)
            continue;
        const float dx =
            *reinterpret_cast<float*>(entry + 0x3b4) - position[0];
        const float dy =
            *reinterpret_cast<float*>(entry + 0x3b8) - position[1];
        const float combined =
            *reinterpret_cast<float*>(entry + 0x3f0) *
                _DAT_00470b0c + radius;
        if (dx * dx + dy * dy > combined * combined)
            continue;

        if (phase != 1 && phase != 2)
            continue;
        *reinterpret_cast<unsigned short*>(entry + 0x30c) = 1;
        *reinterpret_cast<unsigned short*>(entry + 0x446) = 3;
        const float x = *reinterpret_cast<float*>(entry + 0x3b4);
        const float y = *reinterpret_cast<float*>(entry + 0x3b8);
        const bool outside =
            x + 8.0f > _DAT_00470b40 ||
            x - 8.0f < _DAT_00470b3c ||
            y + 8.0f > _DAT_00470b04 ||
            y - 8.0f < _DAT_00470b38;
        if (outside) {
            *reinterpret_cast<unsigned int*>(entry) |= 8u;
        } else {
            auto* timer =
                reinterpret_cast<FrameTimer*>(entry + 0x3f8);
            Timer_Reset(timer);
        }
        // Retail optionally emits kind-8 feedback here through 0x0041BB00.
        // The collision and lifetime transition do not depend on allocation
        // succeeding (the item pool silently drops a full-pool request).
        (void)allowEffect;
    }
}
void ItemManager_CollectNearPlayer(
    void* itemManager, const float* position, float radius, int allowEffect);
void Player_UpdatePowerDisplay(int major_digits, int major_value, int minor_digits);
void Player_ClearPowerDisplayFlags(void);

// 0x00405410 - Arm a scheduler node and store its integer/float value.
void Player_SetSchedulerValue(void* scheduler, int value) {
    uint8_t* bytes = (uint8_t*)scheduler;
    uint32_t flags = *(uint32_t*)(bytes + 0x10);
    if ((flags & 1) == 0) {
        *(uint32_t*)(bytes + 0x04) = 0;
        *(uint32_t*)(bytes + 0x00) = 0xFFF0BDC1;
        *(uint32_t*)(bytes + 0x08) = 0;
        *(uint32_t*)(bytes + 0x0C) =
            (uint32_t)(unsigned long)&DAT_00476f78;
        *(uint32_t*)(bytes + 0x10) = flags | 1;
    }
    *(uint32_t*)(bytes + 0x04) = (uint32_t)value;
    *(uint32_t*)(bytes + 0x00) = (uint32_t)(value - 1);
    *(float*)(bytes + 0x08) = (float)value;
}

// 0x00405500 - Clear transient player flags once the startup timer expires.
void Player_ClearExpiredFlags(Player* player) {
    uint8_t* bytes = (uint8_t*)player;
    if (*(int*)(bytes + 0x3738) < 0x3C) return;
    const uint32_t mask = 0xFFFFFFFDu;
    *(uint32_t*)(bytes + 0x378C) &= mask;
    *(uint32_t*)(bytes + 0x3790) = 0;
    *(uint32_t*)(bytes + 0x0AD4) &= mask;
    *(uint32_t*)(bytes + 0x0E80) &= mask;
    *(uint32_t*)(bytes + 0x15D8) &= mask;
    *(uint32_t*)(bytes + 0x1984) &= mask;
    *(uint32_t*)(bytes + 0x1D30) &= mask;
    *(uint32_t*)(bytes + 0x20DC) &= mask;
    *(uint32_t*)(bytes + 0x2488) &= mask;
}
// ============================================================================
// 0x00405860 - Player_Init (start a new frame/player life)
// player = player object (contains position, power, state at various offsets)
// Returns 0 on success, -1 if already active
//
// Ghidra decompilation:
//   if (player+0x28 != 0): return -1  (already active)
//   player+0x28 = 1  (mark active)
//   Initialize scheduler at +0x24 (if not already)
//   Set timer: +0x18=0, +0x1C=0, +0x14=0xFFFFFFFF
//   Set hitbox: +0x3C=32.0f (0x42000000), +0x40=4.0f (0x40800000)
//   Copy position from DAT_00477834 (+0x3C0..+0x3C8)
//   Load sprite handle from player state
//   Set +0x2C = sprite handle
//   Calculate power display: Player_UpdatePowerDisplay(power/20, power/20, (power%20)*100/20)
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

    // Calculate power display
    int power = (int)DAT_00474c48;
    int powerMajor = power / 0x14;
    int powerMinor = (power % 0x14) * 100 / 0x14;
    Player_UpdatePowerDisplay(powerMajor, powerMajor, powerMinor);

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
//     Call AnimationManager_SetPosition (0x004492F0, animation update)
//     Call Player_Draw (0x00405AC0)
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
                ((*(int*)(playerState + 0x3788) < 0x5D ||
                  *(int*)(playerState + 0x3788) > 0x60) &&
                 *(int*)(playerState + 0x3788) != 0x6D)) {
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
        FrameTimer_Tick((FrameTimer*)player->timer);
    }
    return 1;
}

// ============================================================================
// 0x00405AC0 - Player_Draw: Render the player sprite
// The retail body received the player in ESI; the clean interface uses a
// normal typed argument.
// Calls EnemyManager_CheckPlayerCollision (0x00408100) with hitbox radius and flags.
//
// Ghidra decompilation:
//   if (player+0x28 != 0):
//     Determine focus state
//     EnemyManager_CheckPlayerCollision(hitbox, ~flags & 1, focused)
//     ScoreRecords_CopyVectorAndEvaluate (0x0041C800)
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
namespace {

void PlayerManager_SetModeTimer(void* manager, int frames,
                                unsigned int mode_bit) {
    unsigned char* bytes = (unsigned char*)manager;
    unsigned int* timer_flags = (unsigned int*)(bytes + 0x2A2C);
    if ((*timer_flags & 1u) == 0) {
        *(int*)(bytes + 0x2A20) = 0;
        *(int*)(bytes + 0x2A1C) = (int)0xFFF0BDC1u;
        *(int*)(bytes + 0x2A24) = 0;
        *(uint32_t*)(bytes + 0x2A28) =
            (uint32_t)(unsigned long)&DAT_00476f78;
        *timer_flags |= 1u;
    }
    *(int*)(bytes + 0x2A20) = frames;
    *(float*)(bytes + 0x2A24) = (float)frames;
    *(int*)(bytes + 0x2A1C) = frames - 1;
    *(unsigned int*)(bytes + 0x2A18) |= mode_bit;
}

}  // namespace

// 0x00404530 - Create the stage-entry overlay and arm the 30-frame player
// transition. The callback keeps the overlay factory as an honest boundary;
// the timer block itself is an exact reconstruction.
void PlayerManager_ArmIntroTimer(void* manager,
                                 void (*create_overlay)(void)) {
    if (create_overlay != 0)
        create_overlay();
    if (manager != 0)
        PlayerManager_SetModeTimer(manager, 30, 2u);
}

// 0x004045B0 - Arm the companion 60-frame player mode.
void PlayerManager_StartMode(void* manager) {
    if (manager != 0)
        PlayerManager_SetModeTimer(manager, 60, 4u);
}

namespace {

int __fastcall PlayerRuntime_UpdateCallback(void* owner) {
    return Player_Update((Player*)owner);
}

int __fastcall PlayerRuntime_DrawCallback(void*) {
    return 1;
}

}  // namespace

// 0x004055C0 - Publish the live player runtime and install its retail update
// and draw callback pair. Both nodes are scheduler-owned (flag bit 1 set).
int PlayerRuntime_Initialize(void* player) {
    if (player == 0 || DAT_00491be4 == 0)
        return -1;
    DAT_004776ec = (uint32_t)(unsigned long)player;
    SchedulerCallback* update =
        SchedulerCallback_Create(PlayerRuntime_UpdateCallback);
    if (update == 0)
        return -1;
    update->flags |= 2u;
    update->owner = player;
    Scheduler_RegisterPrimary(update, 0, (void*)DAT_00491be4);
    *(SchedulerCallback**)((unsigned char*)player + 8) = update;

    SchedulerCallback* draw =
        SchedulerCallback_Create(PlayerRuntime_DrawCallback);
    if (draw == 0) {
        Scheduler_Remove(update, (void*)DAT_00491be4);
        *(SchedulerCallback**)((unsigned char*)player + 8) = 0;
        DAT_004776ec = 0;
        return -1;
    }
    draw->flags |= 2u;
    draw->owner = player;
    Scheduler_RegisterSecondary(draw, 0, (void*)DAT_00491be4);
    *(SchedulerCallback**)((unsigned char*)player + 12) = draw;
    return 0;
}

// 0x00405620 - Unregister both owned callbacks and clear the retail player
// publication slot.
void PlayerRuntime_Destroy(void* player) {
    if (player == 0)
        return;
    SchedulerCallback** update =
        (SchedulerCallback**)((unsigned char*)player + 8);
    SchedulerCallback** draw =
        (SchedulerCallback**)((unsigned char*)player + 12);
    if (DAT_00491be4 != 0) {
        if (*update != 0)
            Scheduler_Remove(*update, (void*)DAT_00491be4);
        if (*draw != 0)
            Scheduler_Remove(*draw, (void*)DAT_00491be4);
    }
    *update = 0;
    *draw = 0;
    DAT_004776ec = 0;
}
