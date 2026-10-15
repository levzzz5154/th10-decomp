#pragma once

// Shared model for the coupled stage-front runtime members:
//   0x00414900  FrontHudUpdate_00414900   - the scheduler callback body that
//                                           ticks every front animation bank,
//                                           drives the boss gauge, the score
//                                           digits, the stage banner notices
//                                           and the end-of-stage bonus.
//   0x00415E90  FrontScriptTick_00415e90  - the front script opcode walker the
//                                           update drives once per frame.
// Both receive the stage-front runtime (the object behind 0x0047770C) as their
// single stack argument and return an int in EAX.
//
// The lookup/tree/pool types come from the pause-initializer graph header and
// the creation graph header so the anchor bodies compiled for this pair link
// against the same symbols.

#include "th10/game/player.hpp"
#include "th10/game/pause_initializer_00422ab0.hpp"
#include "th10/render/animation_object_0043e5a0.hpp"

// ---------------------------------------------------------------------------
// Globals the pair reads and writes (not already declared by the pause graph).
// ---------------------------------------------------------------------------
extern "C" unsigned char g_input;              // raw input edges
extern "C" unsigned char data_00474e62;              // secondary input edges
extern "C" unsigned short data_00474c48;             // graze counter (word)
extern "C" unsigned int data_00474c40;               // score state object
extern "C" unsigned int data_00474c4c;               // current score
extern "C" unsigned int data_00474c68;               // sequence mode select
extern "C" unsigned int data_00474c6c;               // sequence stage number
extern "C" unsigned int data_00474c70;               // sequence rank bonus
extern "C" unsigned int data_00474c74;               // sequence clear mode
extern "C" unsigned int data_00474c7c;               // difficulty
extern "C" unsigned int data_00474c84;               // stage progress counter
extern "C" unsigned int data_00474c8c;               // progress echo
extern "C" unsigned char data_00474ca0;              // clear flags (bit 0x10)
extern "C" unsigned char data_00491c28;              // input mode state object
extern "C" unsigned int data_00491fb8;               // front mode word
extern "C" void* g_card;                      // game state arena
extern "C" void* data_00477704;                      // sequence record
extern "C" void* g_pause_menu;                      // clear state object
extern "C" void* data_00477838;                      // replay state record
extern "C" void* data_0047783c;                      // notice table
extern "C" void* data_00477848;                      // bgm state record
extern "C" short data_004749ce[];                    // sound priority table
extern "C" float data_00470afc;                      // 1.0f
extern "C" float data_00470b04;                      // gauge threshold (slow)
extern "C" float data_00470b3c;                      // boss fade window high
extern "C" float data_00470b40;                      // boss fade window low
extern "C" float data_00470b5c;                      // gauge threshold (slow 2)
extern "C" float data_00470bc8;                      // gauge open threshold
extern "C" float data_00470c28;                      // gauge close threshold
extern "C" float data_00470bdc;                      // banner close threshold
extern "C" float data_00470ce8;                      // boss alpha scale
extern "C" double data_00470cf0;                     // boss alpha epsilon
extern "C" float data_00470cf8;                      // gauge ramp step
extern "C" double data_00470d00;                     // banner open threshold
extern "C" float data_00470d08;                      // banner close threshold 2
extern "C" double data_00470d10;                     // banner open threshold 2

// The music/sound request table the queue helper posts through (0x00492590).
extern "C" SoundQueue data_00492590;

extern "C" float data_00470b4c;                      // boss anchor offset
extern "C" int __stdcall AnmVm_Run_0043ee30(void* vm);          // 0x0043EE30
extern "C" void __cdecl FrontFree_004524a1(void* block);        // 0x004524A1

// The stage-front runtime (0x0047770C). Offsets per retail accesses.
struct FrontHudRuntime {
    int sequence_counter;                    // +0x0000, sequence frame counter
    unsigned char pad_0004[0x18 - 0x04];
    unsigned char frame_ramp_18[0x2C - 0x18]; // +0x0018, embedded frame ramp
    unsigned char pad_002c[0x30 - 0x2C];
    int scheduler_value;                     // +0x0030, sequence scheduler value
    unsigned char pad_0034[0x40 - 0x34];
    unsigned int slot_base;                  // +0x0040 handle slot
    unsigned int slot_stage;                 // +0x0044 handle slot
    unsigned int slot_banner;                // +0x0048 handle slot
    unsigned int slot_text_a;                // +0x004C handle slot
    unsigned int slot_text_b;                // +0x0050 handle slot
    unsigned int slot_extra;                 // +0x0054 handle slot
    unsigned char pad_0058[0x5C - 0x58];
    const unsigned char* script_cursor;      // +0x005C, opcode stream pointer
    float position_stage[3];                 // +0x0060, banner position triple
    float position_extra[3];                 // +0x006C, secondary triple
    int sequence_timer;                      // +0x0078
    unsigned int sequence_flags;             // +0x007C (bit 0 = skip hold)
    int text_phase;                          // +0x0080
    int slot_selector;                       // +0x0084
    int text_params[10];                     // +0x0088, per-slot text params
    unsigned char pad_00b0[0x4980 - 0xB0];

    // One front animation object; 23 of them live contiguously here (stride
    // 0x3AC). 0-8 primary, 9-12 stage, 13-14 banner, 15 gauge, 16-20 score
    // digits, 21 total, 22 boss.
    struct BankObject {
        unsigned char pad_0000[0x2FF];
        unsigned char alpha_2ff;             // +0x2FF (boss fade alpha)
        unsigned char pad_0300[4];
        unsigned short stop_frame;           // +0x304
        unsigned char pad_0306[0x340 - 0x306];
        float y_340;                         // +0x340
        float height_344;                    // +0x344
        unsigned char pad_0348[0x3AC - 0x348];
    };
    BankObject objects[23];                  // +0x4980..0x9DF4

    unsigned char pad_9df4[0x9E14 - 0x9DF4];
    int stage_text_id_9e14;                  // +0x9E14
    unsigned char pad_9e18[0x9E24 - 0x9E18];
    int pending_id_9e24;                     // +0x9E24
    int boss_ids_9e28[10];                   // +0x9E28
    unsigned char pad_9e50[0x9E60 - 0x9E50];
    int boss_frame_9e60;                     // +0x9E60
    int boss_frame_prev_9e64;                // +0x9E64
    float boss_frame_acc_9e68;               // +0x9E68
    const float* boss_speed_9e6c;            // +0x9E6C
    unsigned char pad_9e70[0x9E80 - 0x9E70];
    void* alternate_resource_9e80;           // +0x9E80
    float gauge_disp_9e84;                   // +0x9E84
    float gauge_ratio_9e88;                  // +0x9E88
    int gauge_value_9e8c;                    // +0x9E8C
    int boss_id_count_9e90;                  // +0x9E90
    unsigned char pad_9e94[0x9EB4 - 0x9E94];
    unsigned int flags_9eb4;                 // +0x9EB4
    void* sequence_9eb8;                     // +0x9EB8, script runtime record
    unsigned char pad_9ebc[0x9EC0 - 0x9EBC];
    int script_pos_9ec0;                     // +0x9EC0
    int script_marked_9ec4;                  // +0x9EC4
    void* resource_9ec8;                     // +0x9EC8
    int banner_timer_9ecc;                   // +0x9ECC
};

typedef char FrontBankBase[offsetof(FrontHudRuntime, objects) == 0x4980 ? 1 : -1];
typedef char FrontFlagsOffset[offsetof(FrontHudRuntime, flags_9eb4) == 0x9EB4 ? 1 : -1];

// The recovered pair: the update and the script walker it drives.
__declspec(noinline) int __stdcall FrontHudUpdate_00414900(
    FrontHudRuntime* front);
struct ResultDispatcherState;
extern "C" __declspec(noinline) int __stdcall ResultDispatcher_00415e90(
    ResultDispatcherState* front);
