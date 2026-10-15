#pragma once

// Shared model for the coupled stage-front runtime members:
//   0x00414900  FrontHudUpdate   - the scheduler callback body that
//                                           ticks every front animation bank,
//                                           drives the boss gauge, the score
//                                           digits, the stage banner notices
//                                           and the end-of-stage bonus.
//   0x00415E90  FrontScriptTick  - the front script opcode walker the
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
extern "C" unsigned char g_input_keys_secondary;              // secondary input edges
extern "C" unsigned short g_globals_power;
extern "C" unsigned int g_globals;               // score state object
extern "C" unsigned int g_globals_gauge;
extern "C" unsigned int g_globals_character;
extern "C" unsigned int g_globals_shot_type;
extern "C" unsigned int g_globals_lives;
extern "C" unsigned int g_globals_difficulty;
extern "C" unsigned int g_globals_stage;
extern "C" unsigned int g_stage_progress;               // stage progress counter
extern "C" unsigned int g_stage_progress_echo;               // progress echo
extern "C" unsigned char g_globals_flags;              // clear flags (bit 0x10)
extern "C" unsigned char g_application;              // input mode state object
extern "C" unsigned int g_main_state;               // front mode word
extern "C" void* g_card;                      // game state arena
extern "C" void* g_enemy_ctrl;                      // sequence record
extern "C" void* g_pause;                      // clear state object
extern "C" void* g_replay;                      // replay state record
extern "C" void* g_score;                      // notice table
extern "C" void* g_stage_route_current;                      // bgm state record
extern "C" short g_sound_priority[];                    // sound priority table
extern "C" float flt_1;                      // 1.0f
extern "C" float flt_0;                      // gauge threshold (slow)
extern "C" float flt_192;                      // boss fade window high
extern "C" float flt_neg192;                      // boss fade window low
extern "C" float flt_neg64;                      // gauge threshold (slow 2)
extern "C" float flt_64;                      // gauge open threshold
extern "C" float flt_80;                      // gauge close threshold
extern "C" float flt_416;                      // banner close threshold
extern "C" float flt_neg2_984375;                      // boss alpha scale
extern "C" double dbl_64;                     // boss alpha epsilon
extern "C" float flt_0_025;                      // gauge ramp step
extern "C" double dbl_neg112;                     // banner open threshold
extern "C" float flt_400;                      // banner close threshold 2
extern "C" double dbl_neg128;                     // banner open threshold 2

// The music/sound request table the queue helper posts through (0x00492590).
extern "C" SoundQueue g_sound_manager;

extern "C" float flt_224;                      // boss anchor offset
extern "C" int __stdcall AnmVm_Run(void* vm);          // 0x0043EE30
extern "C" void __cdecl FrontFree(void* block);        // 0x004524A1

// The stage-front runtime (0x0047770C). Offsets per retail accesses.
struct FrontUpdateView {
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

typedef char FrontBankBase[offsetof(FrontUpdateView, objects) == 0x4980 ? 1 : -1];
typedef char FrontFlagsOffset[offsetof(FrontUpdateView, flags_9eb4) == 0x9EB4 ? 1 : -1];

// The recovered pair: the update and the script walker it drives.
__declspec(noinline) int __stdcall FrontHudUpdate(
    FrontUpdateView* front);
struct ResultDispatcherState;
extern "C" __declspec(noinline) int __stdcall ResultDispatcher_00415e90(
    ResultDispatcherState* front);
