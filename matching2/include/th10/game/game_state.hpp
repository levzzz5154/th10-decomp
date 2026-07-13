// =============================================================================
// game_state.hpp - Game state types
// =============================================================================
#pragma once
#include "th10/game/entity.hpp"

// ============================================================================
// GameState - 0x2B64 bytes
// Per-game-state object (menu, playing, pause, etc.)
// Created by FUN_00402640, destroyed by FUN_00402440
//
// Layout:
// +0x000: flags (bit 1 = constructed)
// +0x004: entity slot array 1 (8 entities * 0x3AC = 0x1D60 bytes) at +0x180
// +0x180: 8 Entity slots (player, enemies, etc.)
// +0x1F08: 3 Entity slots (secondary objects)
// +0x008: render target 1 handle
// +0x00C: render target 2 handle
// +0x010: allocated buffer 1
// +0x038..0x048: scheduler chain (timer)
// +0x180..0x3AC*8: entity array (8 entities)
// +0x1EE0: frame counter (float as int)
// +0x1EE8: color value (0x808080)
// +0x1F08..0x3AC*3: entity array (3 entities)
// +0x2A0C: update counter
// +0x2A10: skip counter
// +0x2A14: draw counter
// +0x2A18: state flags
// +0x2A30: difficulty/type
// +0x2A34: state change counter
// +0x2A40: render target 3 handle
// +0x2A44: allocated buffer 2
// +0x2A4C: 0x46 dwords = render config (copied from DAT_00491d7c)
// +0x2A70: normalized direction vector
// +0x2B34..0x2B44: temp vectors
// ============================================================================
struct GameState {
    uint32_t  flags;             // +0x000
    uint8_t   pad_004[0x180 - 4];
    Entity    entities[8];       // +0x180 (8 * 0x3AC = 0x1D60)
    uint8_t   pad_1EE0[0x1F08 - 0x180 - sizeof(Entity) * 8];
    Entity    entities2[3];      // +0x1F08 (3 * 0x3AC = 0xB04)
    uint8_t   pad_22B4[0x2B64 - 0x1F08 - sizeof(Entity) * 3];
};
// sizeof(GameState) should be 0x2B64

// ============================================================================
// GameThread - 0x89AC bytes (0x226B dwords)
// Main game object, contains all game state
// Created by FUN_00401440, destroyed by FUN_00401260
//
// Layout:
// +0x000: vtable pointer
// +0x004: flags (bit 1 = constructed)
// +0x008: render target handle (D3D texture/surface)
// +0x00C: timer/callback handle 1
// +0x010: timer/callback handle 2
// +0x014..0x374: Entity (0x3AC bytes) — primary entity
// +0x03C0..0x72C: Entity (0x3AC bytes) — secondary entity
// +0x1C6*4: allocated buffer (freed in destructor)
// +0xDB*4: allocated buffer (freed in destructor)
// +0x31C: animation resource handle (ascii.anm)
// +0x6C8: animation resource handle (text.anm)
// +0x8994: ascii.anm resource ptr
// +0x8998: capture.anm resource ptr
// +0x899C: text.anm resource ptr
// +0x89A8: callback handle 3
// +0x89AC total
// ============================================================================
struct GameThread {
    void*     vtable;            // +0x000
    uint32_t  flags;             // +0x004
    void*     renderTarget;      // +0x008
    void*     callback1;         // +0x00C
    void*     callback2;         // +0x010
    uint8_t   pad_014[0x89AC - 0x014];
};
// sizeof(GameThread) should be 0x89AC

GameThread* GameThread_Construct(GameThread* gameThread);
int GameThread_Init(GameThread* gameThread);
void GameThread_Destroy(GameThread* gameThread);
GameThread* GameThread_Create();

GameState* GameState_Construct(GameState* state);
int GameState_Init(void* manager, GameState* state, int stateId);
void GameState_Destroy(GameState* state);
GameState* GameState_Create(void* manager, int stateId);
