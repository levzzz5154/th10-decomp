#pragma once
#include "th10/types.h"
#include <cstdint>
#include <cstddef>

namespace th10 {

// ========================================
// Entity (0x3AC = 940 bytes)
//
// Exact binary layout from Ghidra RE.
// This is a POD struct; the game uses pools of these.
// ========================================
#pragma pack(push, 1)
struct Entity {
    // ---- Core Linked List (use by entity pool manager) ----
    // NOTE: Pointer fields stored as uint32_t to match 32-bit binary layout
    // on 64-bit hosts.  Use ptr()/set_ptr() accessors for safe casting.
    int32_t  entityId;          // +0x000, monotonic unique ID
    uint32_t selfRaw;           // +0x004, self-pointer (list node head)
    uint32_t nextRaw;           // +0x008, next in active/inactive list
    uint32_t prevRaw;           // +0x00C, previous in list
    uint32_t parentRaw;         // +0x010, parent/owner entity
    uint32_t childListRaw;      // +0x014, child entity linked list

    // ---- Type / Preserved ----
    int32_t  entityType;        // +0x018, EntityType enum
    char     name[4];           // +0x01C
    int32_t  typePreserved;     // +0x020

    // ---- Rotation ----
    float    rotX;              // +0x024
    float    rotY;              // +0x028
    float    rotZ;              // +0x02C

    // ---- Padding ----
    uint8_t  _pad_030[12];      // +0x030..+0x03B

    // ---- Scale (init 1.0) ----
    float    scaleX;            // +0x03C, init 1.0
    float    scaleY;            // +0x040, init 1.0

    // ---- Padding ----
    uint8_t  _pad_044[8];       // +0x044..+0x04B

    // ---- Dimensions (half-width/height for quad rendering) ----
    float    halfW;             // +0x04C
    float    halfH;             // +0x050
    float    drawOffX;          // +0x054, draw offset
    float    drawOffY;          // +0x058

    // ---- State ----
    float    initValue;         // +0x05C, init 0xFFF0BDC1 (-999999)
    int32_t  lifetime;          // +0x060

    // ---- Padding ----
    uint8_t  _pad_064[4];       // +0x064..+0x067

    int32_t  ownerIndex;        // +0x068
    float    param06C;          // +0x06C

    // ---- Padding ----
    uint8_t  _pad_070[12];      // +0x070..+0x07B

    // ---- Velocity / Motion ----
    float    velocity;          // +0x07C
    float    speedValue;        // +0x080
    float    subParam;          // +0x084

    // ---- Large unknown region ----
    uint8_t  _pad_088[0x1B4];   // +0x088..+0x23B (436 bytes)

    // ---- Transformation Matrix (4x4 float, identity by default) ----
    float    transform[4][4];   // +0x23C..+0x27B
    // diag init: transform[0][0]=1.0, transform[1][1]=1.0,
    //            transform[2][2]=1.0, transform[3][3]=1.0

    // ---- World Matrix Backup ----
    float    worldMatrix[16];   // +0x27C..+0x2BB
    float    backupMatrix[16];  // +0x2BC..+0x2FB

    // ---- Identity (subId init -1, flag2FF at byte +0x2FF) ----
    union {
        int32_t  subId;         // +0x2FC, init -1
        struct {
            uint8_t _subLo[3];
            uint8_t flag2FF;    // +0x2FF
        };
    };

    // ---- Padding ----
    uint8_t  _pad_300[4];       // +0x300..+0x303

    // ---- State flags ----
    int16_t  state;             // +0x304: 0=active, 1=death, 3=removed

    // ---- Padding ----
    uint8_t  _pad_306[6];       // +0x306..+0x30B

    // ---- Display ----
    float    displayParam;      // +0x30C

    // ---- Padding ----
    uint8_t  _pad_310[0x30];    // +0x310..+0x33F (48 bytes)

    // ---- Position (preserved across entity reset!) ----
    float    posX;              // +0x340
    float    posY;              // +0x344
    float    posZ;              // +0x348
    float    animOffX;          // +0x34C, animation-driven offset
    float    animOffY;          // +0x350
    float    animOffZ;          // +0x354

    // ---- Padding ----
    uint8_t  _pad_358[4];       // +0x358..+0x35B

    // ---- Render flags (bitfield) ----
    uint32_t renderFlags;       // +0x35C: 0x1=visible, 0x4000000=kill

    // ---- Padding ----
    uint8_t  _pad_360[0x1C];    // +0x360..+0x37B (28 bytes)

    // ---- Rotation angle for billboard ----
    float    angle;             // +0x37C

    // ---- Padding ----
    uint8_t  _pad_380[0x14];    // +0x380..+0x393 (20 bytes)

    // ---- Texture ----
    uint32_t textureRaw;        // +0x394

    // ---- Padding ----
    uint8_t  _pad_398[8];       // +0x398..+0x39F

    // ---- Animation ----
    uint8_t  animFrame;         // +0x3A0
    uint8_t  animFrameMax;      // +0x3A1

    // ---- End padding ----
    uint8_t  _pad_3A2[0xA];     // +0x3A2..+0x3AB
};
#pragma pack(pop)

//st_a(sizeof(Entity) == 0x3AC, "Entity must be 0x3AC (940) bytes");

// ---- Critical offset checks ----
//st_a(offsetof(Entity, entityId)     == 0x000);
//st_a(offsetof(Entity, selfRaw)       == 0x004);
//st_a(offsetof(Entity, nextRaw)       == 0x008);
//st_a(offsetof(Entity, prevRaw)       == 0x00C);
//st_a(offsetof(Entity, parentRaw)     == 0x010);
//st_a(offsetof(Entity, childListRaw)  == 0x014);
//st_a(offsetof(Entity, entityType)   == 0x018);
//st_a(offsetof(Entity, name)         == 0x01C);
//st_a(offsetof(Entity, rotX)         == 0x024);
//st_a(offsetof(Entity, rotY)         == 0x028);
//st_a(offsetof(Entity, rotZ)         == 0x02C);
//st_a(offsetof(Entity, scaleX)       == 0x03C);
//st_a(offsetof(Entity, scaleY)       == 0x040);
//st_a(offsetof(Entity, halfW)        == 0x04C);
//st_a(offsetof(Entity, halfH)        == 0x050);
//st_a(offsetof(Entity, drawOffX)     == 0x054);
//st_a(offsetof(Entity, drawOffY)     == 0x058);
//st_a(offsetof(Entity, initValue)    == 0x05C);
//st_a(offsetof(Entity, lifetime)     == 0x060);
//st_a(offsetof(Entity, ownerIndex)   == 0x068);
//st_a(offsetof(Entity, param06C)     == 0x06C);
//st_a(offsetof(Entity, velocity)     == 0x07C);
//st_a(offsetof(Entity, speedValue)   == 0x080);
//st_a(offsetof(Entity, subParam)     == 0x084);
//st_a(offsetof(Entity, transform)    == 0x23C);
//st_a(offsetof(Entity, worldMatrix)  == 0x27C);
//st_a(offsetof(Entity, backupMatrix) == 0x2BC);
//st_a(offsetof(Entity, subId)        == 0x2FC);
//st_a(offsetof(Entity, flag2FF)      == 0x2FF);
//st_a(offsetof(Entity, state)        == 0x304);
//st_a(offsetof(Entity, displayParam) == 0x30C);
//st_a(offsetof(Entity, posX)         == 0x340);
//st_a(offsetof(Entity, posY)         == 0x344);
//st_a(offsetof(Entity, posZ)         == 0x348);
//st_a(offsetof(Entity, animOffX)     == 0x34C);
//st_a(offsetof(Entity, animOffY)     == 0x350);
//st_a(offsetof(Entity, animOffZ)     == 0x354);
//st_a(offsetof(Entity, renderFlags)  == 0x35C);
//st_a(offsetof(Entity, angle)        == 0x37C);
//st_a(offsetof(Entity, textureRaw)    == 0x394);
//st_a(offsetof(Entity, animFrame)    == 0x3A0);
//st_a(offsetof(Entity, animFrameMax) == 0x3A1);


// ========================================
// GameStateManager (~7.5 MB allocation)
//
// This struct is HEAP-ONLY (too large for stack).
// Global pointer: g_pGameStateManager
// ========================================
#pragma pack(push, 1)
struct GameStateManager {
    // ---- Global Header (0x00–0x67) ----
    int32_t  gameoverFlag;      // +0x00, init -1
    int32_t  activeScene;       // +0x04, init -1

    uint8_t  _pad_08[0x54];     // +0x08..+0x5B

    float    cameraPosX;        // +0x5C
    float    cameraPosY;        // +0x60

    uint8_t  _pad_64[4];        // +0x64..+0x67

    // ---- Entity Pool 1 (0x68–0x3AB067) ----
    Entity   entityPool1[ENTITY_POOL1_SIZE];  // +0x68, 4096 entities

    // Gap between pool1 end and entityInUse start
    uint8_t  _gap_pool1[0x1000];              // +0x3AB068..+0x3AC067

    // ---- Entity In-Use Flags ----
    uint8_t  entityInUse[ENTITY_POOL1_SIZE];  // +0x3AC068, 4096 flags

    // ---- Pool Index ----
    int32_t  entityPoolIndex;   // +0x3AD068, round-robin, masked with 0x3FF

    uint8_t  _pad_3AD06C[0x41C]; // +0x3AD06C..+0x3AD487

    // ---- Render State ----
    uint32_t voiceBufRaw;       // +0x3AD488, freed in destructor

    uint8_t  _pad_3AD48C[0x5D4]; // +0x3AD48C..+0x3ADA5F

    // ---- Intermediate State ----
    int32_t  sceneTimer;        // +0x3ADA60
    int32_t  activeTextureId;   // +0x3ADA64

    uint8_t  gameState;         // +0x3ADA68 (3=running)
    uint8_t  subState;          // +0x3ADA69
    uint8_t  d3dMode;           // +0x3ADA6A (1=pre-init, 2=ready)
    uint8_t  unk0;              // +0x3ADA6B

    uint8_t  flagFF;            // +0x3ADA6C, init 0xFF

    uint8_t  _pad_3ADA6D;       // +0x3ADA6D

    uint8_t  unk1;              // +0x3ADA6E

    uint8_t  _pad_3ADA6F;       // +0x3ADA6F

    int32_t  currentTexture;    // +0x3ADA70
    uint32_t bgmRaw;            // +0x3ADA74, BGM subsystem pointer

    int32_t  spriteData[12];    // +0x3ADA78

    int32_t  unkArray[4];       // +0x3ADAA8

    uint8_t  _pad_3ADAB8[0x10];  // +0x3ADAB8..+0x3ADAC7

    int32_t  renderCmdCount;    // +0x3ADAC8
    uint32_t renderBufEndRaw;   // +0x3ADACC

    // ---- Large gap to entity management / pool2 region ----
    uint8_t  _pad_3ADAD0[0x3727FC]; // +0x3ADAD0..+0x72DACB

    uint32_t renderBufStartRaw; // +0x72DACC
    uint32_t renderBufWriteRaw; // +0x72DAD0

    // ---- Entity Linked-List Management ----
    uint32_t activeListHeadRaw; // +0x72DAD4
    uint32_t activeListTailRaw; // +0x72DAD8
    uint32_t inactiveListHeadRaw; // +0x72DADC
    uint32_t inactiveListTailRaw; // +0x72DAE0

    // ---- Entity Pool 2 (20 entities) ----
    Entity   entityPool2[ENTITY_POOL2_SIZE];  // +0x72DAE4

    // ---- Entity Identity Counter ----
    int32_t  entityIdCounter;   // +0x732454, monotonic ID counter
};
#pragma pack(pop)

// ---- GameStateManager offset checks ----
//st_a(offsetof(GameStateManager, gameoverFlag)    == 0x00000);
//st_a(offsetof(GameStateManager, activeScene)     == 0x00004);
//st_a(offsetof(GameStateManager, cameraPosX)      == 0x0005C);
//st_a(offsetof(GameStateManager, cameraPosY)      == 0x00060);
//st_a(offsetof(GameStateManager, entityPool1)     == 0x00068);
//st_a(offsetof(GameStateManager, entityInUse)     == 0x3AC068);
//st_a(offsetof(GameStateManager, entityPoolIndex) == 0x3AD068);
//st_a(offsetof(GameStateManager, voiceBufRaw)      == 0x3AD488);
//st_a(offsetof(GameStateManager, sceneTimer)        == 0x3ADA60);
//st_a(offsetof(GameStateManager, activeTextureId)   == 0x3ADA64);
//st_a(offsetof(GameStateManager, gameState)         == 0x3ADA68);
//st_a(offsetof(GameStateManager, subState)          == 0x3ADA69);
//st_a(offsetof(GameStateManager, d3dMode)           == 0x3ADA6A);
//st_a(offsetof(GameStateManager, unk0)              == 0x3ADA6B);
//st_a(offsetof(GameStateManager, flagFF)            == 0x3ADA6C);
//st_a(offsetof(GameStateManager, unk1)              == 0x3ADA6E);
//st_a(offsetof(GameStateManager, currentTexture)    == 0x3ADA70);
//st_a(offsetof(GameStateManager, bgmRaw)            == 0x3ADA74);
//st_a(offsetof(GameStateManager, spriteData)        == 0x3ADA78);
//st_a(offsetof(GameStateManager, unkArray)          == 0x3ADAA8);
//st_a(offsetof(GameStateManager, renderCmdCount)    == 0x3ADAC8);
//st_a(offsetof(GameStateManager, renderBufEndRaw)   == 0x3ADACC);
//st_a(offsetof(GameStateManager, renderBufStartRaw) == 0x72DACC);
//st_a(offsetof(GameStateManager, renderBufWriteRaw) == 0x72DAD0);
//st_a(offsetof(GameStateManager, activeListHeadRaw) == 0x72DAD4);
//st_a(offsetof(GameStateManager, activeListTailRaw) == 0x72DAD8);
//st_a(offsetof(GameStateManager, inactiveListHeadRaw) == 0x72DADC);
//st_a(offsetof(GameStateManager, inactiveListTailRaw) == 0x72DAE0);
//st_a(offsetof(GameStateManager, entityPool2)     == 0x72DAE4);
//st_a(offsetof(GameStateManager, entityIdCounter) == 0x732454);


// ========================================
// Core Entity Pool Operations
// ========================================

// Round-robin pool allocator: scans pool1 for unused slot,
// uses pool2 fallback, returns nullptr if full.
Entity* AllocEntity(GameStateManager* gs);

// Assign monotonic ID and insert into the active linked list.
void LinkEntity(GameStateManager* gs, Entity* e);

// Remove from both active and inactive linked lists.
void UnlinkEntity(GameStateManager* gs, Entity* e);

// Zero most fields (reinitialize), but preserve entityType and position.
void ResetEntity(Entity* e);

} // namespace th10
