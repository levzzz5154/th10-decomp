// =============================================================================
// player.cpp - Player entity update, collision, and management
// Functions: 0x00405860 (Player_Init), 0x00405750 (Player_Update),
//            0x004059F0 (Player_HitTest), 0x00405AC0 (Player_Draw),
//            0x00405B60 (Player_AdjustPower)
// =============================================================================
#include "th10/entity.hpp"
#include "th10/game_state.hpp"

extern void* g_pGameStateManager;
extern uint32_t DAT_004776f4;    // player game state ptr
extern uint32_t DAT_004776f0;    // another game state
extern uint32_t DAT_00477704;    // global config
extern uint32_t DAT_00477834;    // player position source
extern uint32_t DAT_00474c48;    // player power level
extern uint32_t DAT_00474c68;    // player character (0=Reimu, 1=Marisa)
extern int32_t  DAT_00474c98;    // player speed adjustment
extern float    _DAT_00470afc;   // 1.0f
extern float    _DAT_00470d34;   // alt speed
extern float    _DAT_00470b0c;   // focused speed
extern void*    PTR_LAB_0046d0c0;

void Timer_Tick(void);
void FUN_00408100(float radius, int flags, int param3);
void FUN_0041c800(void);
int FUN_004491c0(int param1, int mgr, int param3);
void FUN_004492f0(int param1, int mgr, int param3);
void FUN_0043dd10(void);
void FUN_0043e5a0(int handle, int idx);
void FUN_004054b0(int val1, int val2, int val3);
void FUN_00405500(void);
uint32_t* FUN_00448db0(void* param);
void FUN_00405ac0(void);

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
int Player_Init(int* player) {
    if (player[0xA] != 0) {  // +0x28
        return -1;
    }
    player[0xA] = 1;  // mark active

    // Initialize scheduler chain if needed
    if ((player[9] & 1) == 0) {  // +0x24
        player[6] = 0;           // +0x18
        player[5] = 0xFFF0BDC1;  // +0x14
        player[7] = 0;           // +0x1C
        player[8] = (int)&PTR_LAB_0046d0c0;  // +0x20 = sentinel? actually &DAT_00476f78
        player[9] |= 1;
    }
    player[6] = 0;
    player[7] = 0;
    player[5] = 0xFFFFFFFF;

    // Set hitbox sizes
    *(float*)(player + 0xF) = 32.0f;   // +0x3C = 0x42000000
    *(float*)(player + 0x10) = 4.0f;   // +0x40 = 0x40800000

    // Copy position from global
    int src = DAT_00477834;
    player[0xC] = *(int*)(src + 0x3C0);  // +0x30
    player[0xD] = *(int*)(src + 0x3C4);  // +0x34
    player[0xE] = *(int*)(src + 0x3C8);  // +0x38

    // Load sprite handle
    uint32_t* spriteHandle = (uint32_t*)FUN_00448db0(*(void**)(DAT_004776f0 + 0x3E0B50));
    player[0xB] = *spriteHandle;  // +0x2C

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
        player[0x11] = 1;  // +0x44 = focused
        return 0;
    }
    player[0x11] = 0;
    return 0;
}

// ============================================================================
// 0x004059F0 - Player_HitTest: Check collision between player and bullets
// param_1 (ECX) = player object
// EAX = bullet/entity position (in_EAX)
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
int __fastcall Player_HitTest(int* player) {
    // EAX = bullet position (in_EAX — non-standard)
    float* bulletPos = (float*)player;  // placeholder — actually from EAX

    if (player[0xA] == 0) {  // +0x28
        return 0;
    }

    int result = 0;
    float dx = bulletPos[0] - *(float*)(player + 0xC);  // +0x30
    float dy = bulletPos[1] - *(float*)(player + 0xD);  // +0x34
    float hitbox = *(float*)(player + 0xF);              // +0x3C

    if (dx * dx + dy * dy < hitbox * hitbox) {
        // Direct hit
        if (player[0x11] == 0) {  // +0x44, not focused
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
        if (*(int*)(DAT_00477704 + 0x10) != 0 && player[0x11] == 0) {
            result = (uint32_t)(DAT_00474c68 == 0) * 4 + 0x10;
        }
    } else if (player[0x11] == 1) {
        return (-(uint32_t)(DAT_00474c68 != 0) & 0xFFFFFFFD) + 0x1A;
    }

    return result;
}

// ============================================================================
// 0x00405750 - Player_Update: Update player state for this frame
// param_1 (ECX) = unused, EAX = player state, EDI = player object
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
int __fastcall Player_Update(int param_1) {
    // EDI = player object (unaff_EDI — non-standard)
    int player = 0;  // from EDI
    void* mgr = g_pGameStateManager;

    if (*(int*)(player + 0x28) != 0) {
        if (*(int*)(player + 0x28) == 1) {
            int iVar4 = FUN_004491c0(param_1, (int)mgr, *(int*)(player + 0x2C));
            if (iVar4 == 0) {
                *(uint32_t*)(player + 0x2C) = 0;
                *(uint32_t*)(player + 0x28) = 0;
                return 1;
            }

            // Determine speed based on character and focus state
            float speedAdjust;
            int playerState = DAT_004776f4;
            if ((*(uint8_t*)(playerState + 0x378C) & 1) == 0 ||
                (*(int*)(playerState + 0x3788) < 0x5D || *(int*)(playerState + 0x3788) > 0x60) &&
                *(int*)(playerState + 0x3788) != 0x6D) {
                if (DAT_00474c68 == 0) {
                    speedAdjust = *(float*)(player + 0x34) - _DAT_00470afc;
                } else {
                    speedAdjust = *(float*)(player + 0x34) - _DAT_00470d34;
                }
            } else {
                speedAdjust = *(float*)(player + 0x34) - _DAT_00470b0c;
            }
            *(float*)(player + 0x34) = speedAdjust;

            FUN_004492f0(*(uint32_t*)(player + 0x38), (int)mgr, *(int*)(player + 0x2C));
            *(uint32_t*)(player + 0x3C) = *(uint32_t*)(iVar4 + 0x40);
            FUN_00405ac0();
        }
        Timer_Tick();
    }
    return 1;
}

// ============================================================================
// 0x00405AC0 - Player_Draw: Render the player sprite
// ESI = player object (unaff_ESI)
// Calls FUN_00408100 with hitbox radius and flags
//
// Ghidra decompilation:
//   if (player+0x28 != 0):
//     Determine focus state
//     FUN_00408100(hitbox, ~flags & 1, focused)
//     FUN_0041C800()
// ============================================================================
int Player_Draw(void) {
    // ESI = player (unaff_ESI — non-standard)
    int player = 0;  // from ESI

    if (*(int*)(player + 0x28) != 0) {
        int playerState = DAT_004776f4;
        int focused;
        float hitbox = *(float*)(player + 0x3C);

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

        FUN_00408100(hitbox, ~*(uint32_t*)(playerState + 0x378C) & 1, focused);
        FUN_0041c800();
    }
    return 0;
}
