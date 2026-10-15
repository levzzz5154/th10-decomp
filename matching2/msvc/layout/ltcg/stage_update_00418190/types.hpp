#pragma once
#define data_00491c10 stage_front_data_00491c10
#define data_0047770c stage_front_data_0047770c
#define data_00474c40 stage_front_data_00474c40
#define g_ascii_manager stage_front_data_004776e0
#define data_00477704 stage_front_data_00477704
#define g_player stage_front_data_00477834
#define data_00477838 stage_front_data_00477838
#define data_0047783c stage_front_data_0047783c
#define data_00476f78 stage_front_data_00476f78
#define data_00491fc4 stage_front_data_00491fc4
#define data_00491fb8 stage_front_data_00491fb8
#define data_00492590 stage_front_data_00492590
#include "front_view.hpp"
#undef data_00491c10
#undef data_0047770c
#undef data_00474c40
#undef g_ascii_manager
#undef data_00477704
#undef g_player
#undef data_00477838
#undef data_0047783c
#undef data_00476f78
#undef data_00491fc4
#undef data_00491fb8
#undef data_00492590
#define data_00491c10 stage_hud_data_00491c10
#define data_0047770c stage_hud_data_0047770c
#define data_00474c40 stage_hud_data_00474c40
#define g_ascii_manager stage_hud_data_004776e0
#define data_00477704 stage_hud_data_00477704
#define g_player stage_hud_data_00477834
#define data_00477838 stage_hud_data_00477838
#define data_0047783c stage_hud_data_0047783c
#define data_00476f78 stage_hud_data_00476f78
#define data_00491fc4 stage_hud_data_00491fc4
#define data_00491fb8 stage_hud_data_00491fb8
#define data_00492590 stage_hud_data_00492590
#define GameStateField5c_0042a6a0 HudField5cChecked
#include "hud_view.hpp"
#undef GameStateField5c_0042a6a0
#undef data_00491c10
#undef data_0047770c
#undef data_00474c40
#undef g_ascii_manager
#undef data_00477704
#undef g_player
#undef data_00477838
#undef data_0047783c
#undef data_00476f78
#undef data_00491fc4
#undef data_00491fb8
#undef data_00492590
#include "th10/platform/worker.hpp"
#define data_00491c10 stage_quad_data_00491c10
#define data_0047770c stage_quad_data_0047770c
#define data_00474c40 stage_quad_data_00474c40
#define g_ascii_manager stage_quad_data_004776e0
#define data_00477704 stage_quad_data_00477704
#define g_player stage_quad_data_00477834
#define data_00477838 stage_quad_data_00477838
#define data_0047783c stage_quad_data_0047783c
#define data_00476f78 stage_quad_data_00476f78
#define data_00491fc4 stage_quad_data_00491fc4
#define data_00491fb8 stage_quad_data_00491fb8
#define data_00492590 stage_quad_data_00492590
// 0x00404450 (214 bytes): enable the stage's three tasks, then start one
// animation script for every quad of every stage object and remember which
// entity each quad got.
#include "th10/game/entity.hpp"

struct AnimationResource_0043e710;
void __stdcall Entity_StartScript_00404f30(AnimationResource_0043e710* resource,
                                           Entity* entity, int script);

struct StageTask_00404450 {
    int priority;
    unsigned int flags;                 // +0x04, bit 1: enabled
};

// One drawable piece of a stage object; the list ends at a negative type.
struct StageQuad_00404450 {
    short type;                         // +0x00
    short size;                         // +0x02, bytes to the next quad
    short script;                       // +0x04
    short entity_index;                 // +0x06, filled in here
};

struct StageObject_00404450 {
    unsigned char reserved_00[3];
    unsigned char active;               // +0x03
    unsigned char reserved_04[0x18];
    StageQuad_00404450 quads[1];        // +0x1c
};

struct StageFile_00404450 {
    short object_count;
};

struct Stage_00404450 {
    unsigned char reserved_0000[8];
    StageTask_00404450* update_task;            // +0x08
    StageTask_00404450* draw_task;              // +0x0c
    StageFile_00404450* file;                   // +0x10
    StageObject_00404450** objects;             // +0x14
    unsigned char reserved_0018[4];
    int initial_value_1c;                       // +0x1c
    unsigned char reserved_0020[0x4c - 0x20];
    int value_4c;                               // +0x4c
    unsigned char reserved_0050[0x178 - 0x50];
    AnimationResource_0043e710* animation;      // +0x178
    Entity* quad_entities;                      // +0x17c
    unsigned char reserved_0180[0x2a40 - 0x180];
    StageTask_00404450* after_draw_task;        // +0x2a40
};

#undef data_00491c10
#undef data_0047770c
#undef data_00474c40
#undef g_ascii_manager
#undef data_00477704
#undef g_player
#undef data_00477838
#undef data_0047783c
#undef data_00476f78
#undef data_00491fc4
#undef data_00491fb8
#undef data_00492590
#define data_00491c10 stage_fade_data_00491c10
#define data_0047770c stage_fade_data_0047770c
#define data_00474c40 stage_fade_data_00474c40
#define g_ascii_manager stage_fade_data_004776e0
#define data_00477704 stage_fade_data_00477704
#define g_player stage_fade_data_00477834
#define data_00477838 stage_fade_data_00477838
#define data_0047783c stage_fade_data_0047783c
#define data_00476f78 stage_fade_data_00476f78
#define data_00491fc4 stage_fade_data_00491fc4
#define data_00491fb8 stage_fade_data_00491fb8
#define data_00492590 stage_fade_data_00492590
#include "th10/game/background_fade.hpp"
#include "th10/render/screen_effect_controller.hpp"
extern "C" float data_00476f78;
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
#undef data_00491c10
#undef data_0047770c
#undef data_00474c40
#undef g_ascii_manager
#undef data_00477704
#undef g_player
#undef data_00477838
#undef data_0047783c
#undef data_00476f78
#undef data_00491fc4
#undef data_00491fb8
#undef data_00492590
#define data_00491c10 stage_start_data_00491c10
#define data_0047770c stage_start_data_0047770c
#define data_00474c40 stage_start_data_00474c40
#define g_ascii_manager stage_start_data_004776e0
#define data_00477704 stage_start_data_00477704
#define g_player stage_start_data_00477834
#define data_00477838 stage_start_data_00477838
#define data_0047783c stage_start_data_0047783c
#define data_00476f78 stage_start_data_00476f78
#define data_00491fc4 stage_start_data_00491fc4
#define data_00491fb8 stage_start_data_00491fb8
#define data_00492590 stage_start_data_00492590
// 0x004045B0: start the background's "active" mode, initialising its timer
// record to defaults while the record's initialised flag is still clear.
//
// Retail: 8B 88 2C 2A 00 00        mov ecx,[eax+0x2A2C]
//         F6 C1 01                 test cl,1
//         75 2B                    jne done
//         33 D2                    xor edx,edx
//         83 C9 01                 or ecx,1
//         89 90 20 2A 00 00        mov [eax+0x2A20],edx
//         C7 80 1C 2A 00 00 C1 BD F0 FF  mov [eax+0x2A1C],0xFFF0BDC1
//         89 90 24 2A 00 00        mov [eax+0x2A24],edx
//         C7 80 28 2A 00 00 78 6F 47 00  mov [eax+0x2A28],0x476F78
//         89 88 2C 2A 00 00        mov [eax+0x2A2C],ecx
//  done:  C7 80 20 2A 00 00 3C 00 00 00  mov [eax+0x2A20],60
//         C7 80 24 2A 00 00 00 00 70 42  mov [eax+0x2A24],60.0f
//         C7 80 1C 2A 00 00 3B 00 00 00  mov [eax+0x2A1C],59
//         83 88 18 2A 00 00 04     or  [eax+0x2A18],4
//         C3                       ret
// The manager pointer arrives in EAX, so the mode switch is compiled as a
// native LTCG cluster.
// The background owns this fade timer at +0x2A1C.

#include "th10/game/background_fade.hpp"

#undef data_00491c10
#undef data_0047770c
#undef data_00474c40
#undef g_ascii_manager
#undef data_00477704
#undef g_player
#undef data_00477838
#undef data_0047783c
#undef data_00476f78
#undef data_00491fc4
#undef data_00491fb8
#undef data_00492590
#define data_00491c10 stage_bullet_data_00491c10
#define data_0047770c stage_bullet_data_0047770c
#define data_00474c40 stage_bullet_data_00474c40
#define g_ascii_manager stage_bullet_data_004776e0
#define data_00477704 stage_bullet_data_00477704
#define g_player stage_bullet_data_00477834
#define data_00477838 stage_bullet_data_00477838
#define data_0047783c stage_bullet_data_0047783c
#define data_00476f78 stage_bullet_data_00476f78
#define data_00491fc4 stage_bullet_data_00491fc4
#define data_00491fb8 stage_bullet_data_00491fb8
#define data_00492590 stage_bullet_data_00492590
// 0x00405ED0 - Re-arm the bullet pool: retire the pool's animation resource,
// zero the whole slot array, rewind the free-slot cursor, and set the state
// word back to 5.
#include <string.h>

#include "th10/render/animation_resource_removal.hpp"

extern "C" AnimationManager* data_00491c10;

struct BulletPool {
    unsigned char reserved_000[0x10];
    unsigned int* cursor;
    unsigned char reserved_014[0x60 - 0x14];
    unsigned int slots[0xF82BC];
    void* animation;

    __declspec(noinline) void Reset();
};

#undef data_00491c10
#undef data_0047770c
#undef data_00474c40
#undef g_ascii_manager
#undef data_00477704
#undef g_player
#undef data_00477838
#undef data_0047783c
#undef data_00476f78
#undef data_00491fc4
#undef data_00491fb8
#undef data_00492590
#define data_00491c10 stage_pause_data_00491c10
#define data_0047770c stage_pause_data_0047770c
#define data_00474c40 stage_pause_data_00474c40
#define g_ascii_manager stage_pause_data_004776e0
#define data_00477704 stage_pause_data_00477704
#define g_player stage_pause_data_00477834
#define data_00477838 stage_pause_data_00477838
#define data_0047783c stage_pause_data_0047783c
#define data_00476f78 stage_pause_data_00476f78
#define data_00491fc4 stage_pause_data_00491fc4
#define data_00491fb8 stage_pause_data_00491fb8
#define data_00492590 stage_pause_data_00492590
// Complete pause timer/animation reset, 0x00424D90..0x00424EA0.
// Source declaration is ordinary C++; native LTCG selects the observed ESI
// owner and plain RET. The active-count dependency below is the complete
// genuine 77-byte routine at 0x00413790, not an abbreviated ABI anchor.
#include <stddef.h>
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

struct PauseFrameTimer_00424d90 {
    int previous;
    int current;
    float elapsed;
    const float* speed;
    unsigned int flags;
};
struct PauseState_00424d90 {
    unsigned char reserved_000[0x458];
    int state;
    unsigned char reserved_45c[4];
    PauseFrameTimer_00424d90 timers[3];
    unsigned char reserved_49c[0x329c-0x49c];
    int animation_handle;
};
typedef char PauseFrameTimerSize[sizeof(PauseFrameTimer_00424d90)==0x14?1:-1];
typedef char PauseResetTimerOffset[offsetof(PauseState_00424d90,timers)==0x460?1:-1];
typedef char PauseResetHandleOffset[offsetof(PauseState_00424d90,animation_handle)==0x329c?1:-1];

struct PauseAnimationRecord_00413790 {
    unsigned int flags;
    unsigned char reserved_004[0x3ac-4];
};
typedef ScoreHud_00417040 PauseAnimationCountManager_00413790;
#undef data_00491c10
#undef data_0047770c
#undef data_00474c40
#undef g_ascii_manager
#undef data_00477704
#undef g_player
#undef data_00477838
#undef data_0047783c
#undef data_00476f78
#undef data_00491fc4
#undef data_00491fb8
#undef data_00492590
#define data_00491c10 stage_enemy_data_00491c10
#define data_0047770c stage_enemy_data_0047770c
#define data_00474c40 stage_enemy_data_00474c40
#define g_ascii_manager stage_enemy_data_004776e0
#define data_00477704 stage_enemy_data_00477704
#define g_player stage_enemy_data_00477834
#define data_00477838 stage_enemy_data_00477838
#define data_0047783c stage_enemy_data_0047783c
#define data_00476f78 stage_enemy_data_00476f78
#define data_00491fc4 stage_enemy_data_00491fc4
#define data_00491fb8 stage_enemy_data_00491fb8
#define data_00492590 stage_enemy_data_00492590
// 0x00409F90: remove every enemy. Retires the four enemy animation files,
// destroys each enemy in the list, zeroes the counters and lets both manager
// tasks run again. The manager arrives on the stack.
#include "th10/game/enemy_manager_clear_00409f90.hpp"

#undef data_00491c10
#undef data_0047770c
#undef data_00474c40
#undef g_ascii_manager
#undef data_00477704
#undef g_player
#undef data_00477838
#undef data_0047783c
#undef data_00476f78
#undef data_00491fc4
#undef data_00491fb8
#undef data_00492590
#define data_00491c10 stage_chain_data_00491c10
#define data_0047770c stage_chain_data_0047770c
#define data_00474c40 stage_chain_data_00474c40
#define g_ascii_manager stage_chain_data_004776e0
#define data_00477704 stage_chain_data_00477704
#define g_player stage_chain_data_00477834
#define data_00477838 stage_chain_data_00477838
#define data_0047783c stage_chain_data_0047783c
#define data_00476f78 stage_chain_data_00476f78
#define data_00491fc4 stage_chain_data_00491fc4
#define data_00491fb8 stage_chain_data_00491fb8
#define data_00492590 stage_chain_data_00492590
// Variant A: member with the container walk, head cached in a local.
extern "C" void __cdecl entry_free_004524a1(void* memory);

struct LinkedNode_00417770 {
    virtual void Slot0();
    virtual void Slot1();
    virtual void Slot2();
    virtual void Slot3();
    virtual void Release();
    virtual void Slot5(void* arg);

    LinkedNode_00417770* prev;
    LinkedNode_00417770* next;
    int state;
};

struct ScoreChain_00417770 {
    unsigned char reserved_000[0x18];
    LinkedNode_00417770* head;

    __declspec(noinline) void ReleaseChain();
};

#undef data_00491c10
#undef data_0047770c
#undef data_00474c40
#undef g_ascii_manager
#undef data_00477704
#undef g_player
#undef data_00477838
#undef data_0047783c
#undef data_00476f78
#undef data_00491fc4
#undef data_00491fb8
#undef data_00492590
#define data_00491c10 stage_replay_data_00491c10
#define data_0047770c stage_replay_data_0047770c
#define data_00474c40 stage_replay_data_00474c40
#define g_ascii_manager stage_replay_data_004776e0
#define data_00477704 stage_replay_data_00477704
#define g_player stage_replay_data_00477834
#define data_00477838 stage_replay_data_00477838
#define data_0047783c stage_replay_data_0047783c
#define data_00476f78 stage_replay_data_00476f78
#define data_00491fc4 stage_replay_data_00491fc4
#define data_00491fb8 stage_replay_data_00491fb8
#define data_00492590 stage_replay_data_00492590
// 0x0042A450..0x0042A696: close the current stage in the replay manager.
//
// The manager's tasks are paused for the frame. While recording, the stage's
// input pages are restarted and the stage record takes the game counters
// (unless the configuration word is set), the boss gauge, the player's state
// block and the four values of each player option. During playback the same
// player state is put back from the record instead; with shot type 5 an
// option's fourth value restarts from its first.
//
// The manager arrives in EBX (the compiler's own convention).
#include "th10/game/replay_stage_finish_0042a450.hpp"

#undef data_00491c10
#undef data_0047770c
#undef data_00474c40
#undef g_ascii_manager
#undef data_00477704
#undef g_player
#undef data_00477838
#undef data_0047783c
#undef data_00476f78
#undef data_00491fc4
#undef data_00491fb8
#undef data_00492590
#define data_00491c10 stage_spawn_data_00491c10
#define data_0047770c stage_spawn_data_0047770c
#define data_00474c40 stage_spawn_data_00474c40
#define g_ascii_manager stage_spawn_data_004776e0
#define data_00477704 stage_spawn_data_00477704
#define g_player stage_spawn_data_00477834
#define data_00477838 stage_spawn_data_00477838
#define data_0047783c stage_spawn_data_0047783c
#define data_00476f78 stage_spawn_data_00476f78
#define data_00491fc4 stage_spawn_data_00491fc4
#define data_00491fb8 stage_spawn_data_00491fb8
#define data_00492590 stage_spawn_data_00492590
// 0x0040CFB0..0x0040D1F1: create an enemy.
//
// The record is allocated and bound to the named script entry, takes its
// position, life, score, drop item, two flags and eight script variables from
// the spawn description, and runs its script up to the first wait. Enemies
// flagged for boss-style drops swap the two power item kinds for their large
// forms. The death sound alternates with the creation count, the death effect
// follows the enemy kind the script chose, and the enemy joins the end of the
// manager's list. The switch tables follow the body.
//
// The spawn description arrives in EAX.
#include "enemy_spawn.hpp"
#include <string.h>

#undef data_00491c10
#undef data_0047770c
#undef data_00474c40
#undef g_ascii_manager
#undef data_00477704
#undef g_player
#undef data_00477838
#undef data_0047783c
#undef data_00476f78
#undef data_00491fc4
#undef data_00491fb8
#undef data_00492590
#define data_00491c10 stage_requests_data_00491c10
#define data_0047770c stage_requests_data_0047770c
#define data_00474c40 stage_requests_data_00474c40
#define g_ascii_manager stage_requests_data_004776e0
#define data_00477704 stage_requests_data_00477704
#define g_player stage_requests_data_00477834
#define data_00477838 stage_requests_data_00477838
#define data_0047783c stage_requests_data_0047783c
#define data_00476f78 stage_requests_data_00476f78
#define data_00491fc4 stage_requests_data_00491fc4
#define data_00491fb8 stage_requests_data_00491fb8
#define data_00492590 stage_requests_data_00492590
#include "th10/render/resource_registrar_0043e460.hpp"

#undef data_00491c10
#undef data_0047770c
#undef data_00474c40
#undef g_ascii_manager
#undef data_00477704
#undef g_player
#undef data_00477838
#undef data_0047783c
#undef data_00476f78
#undef data_00491fc4
#undef data_00491fb8
#undef data_00492590
#define data_00491c10 stage_sched_data_00491c10
#define data_0047770c stage_sched_data_0047770c
#define data_00474c40 stage_sched_data_00474c40
#define g_ascii_manager stage_sched_data_004776e0
#define data_00477704 stage_sched_data_00477704
#define g_player stage_sched_data_00477834
#define data_00477838 stage_sched_data_00477838
#define data_0047783c stage_sched_data_0047783c
#define data_00476f78 stage_sched_data_00476f78
#define data_00491fc4 stage_sched_data_00491fc4
#define data_00491fb8 stage_sched_data_00491fb8
#define data_00492590 stage_sched_data_00492590
// 0x00405410: store a scheduler value into the record whose address arrives in
// EAX, initialising the record to its defaults while its "initialised" flag is
// still clear.
//
// Retail: 8B 48 10           mov ecx,[eax+0x10]
//         F6 C1 01           test cl,1
//         56                 push esi
//         8B 74 24 08        mov esi,[esp+8]      ; value
//         75 1B              jne done
//         33 D2              xor edx,edx
//         83 C9 01           or ecx,1
//         89 50 04           mov [eax+4],edx
//         C7 00 C1 BD F0 FF  mov [eax],0xFFF0BDC1
//         89 50 08           mov [eax+8],edx
//         C7 40 0C 78 6F 47 00  mov [eax+0xC],0x476F78
//         89 48 10           mov [eax+0x10],ecx
//  done:  DB 44 24 08        fild dword [esp+8]
//         89 70 04           mov [eax+4],esi
//         4E                 dec esi
//         89 30              mov [eax],esi
//         D9 58 08           fstp dword [eax+8]
//         5E                 pop esi
//         C2 04 00           ret 4
// The record pointer arrives in EAX while the value stays on the stack, so the
// setter is compiled as a native LTCG cluster.
// Carved out of src/game/player.cpp (asm_Player_SetSchedulerValue_00405410).

struct PlayerSchedulerRecord {
    int field_00;    // 0x00 value, stored one below the raw value
    int field_04;    // 0x04 value
    float field_08;  // 0x08 value converted to float
    int field_0C;    // 0x0C default marker
    int flags_10;    // 0x10 initialised flag

    __declspec(noinline) void SetSchedulerValue(int value);
};

#undef data_00491c10
#undef data_0047770c
#undef data_00474c40
#undef g_ascii_manager
#undef data_00477704
#undef g_player
#undef data_00477838
#undef data_0047783c
#undef data_00476f78
#undef data_00491fc4
#undef data_00491fb8
#undef data_00492590
#define data_00491c10 stage_input_data_00491c10
#define data_0047770c stage_input_data_0047770c
#define data_00474c40 stage_input_data_00474c40
#define g_ascii_manager stage_input_data_004776e0
#define data_00477704 stage_input_data_00477704
#define g_player stage_input_data_00477834
#define data_00477838 stage_input_data_00477838
#define data_0047783c stage_input_data_0047783c
#define data_00476f78 stage_input_data_00476f78
#define data_00491fc4 stage_input_data_00491fc4
#define data_00491fb8 stage_input_data_00491fb8
#define data_00492590 stage_input_data_00492590
// 0x0040AC90. Publish the requested input mode on a state object, unless the
// object's +0x3CC flag word has bit 0x1000 set, in which case the mode is
// forced to 2. Retail passes the object in EAX and the mode on the stack, and
// the callee pops it:
//
//   L_0040ac90: mov  ecx,[eax+3CCh]        ; 8b 88 cc 03 00 00
//               test ch,10h                ; f6 c5 10
//               jne  L_0040aca8            ; 75 0d
//               mov  ecx,[esp+4]           ; 8b 4c 24 04
//               mov  [eax+390h],ecx        ; 89 88 90 03 00 00
//               ret  4                     ; c2 04 00
//   L_0040aca8: mov  dword ptr [eax+390h],2
//               ret  4
//
// Every retail caller loads the object from a fixed global (0x00491C28) into
// EAX and pushes a literal mode, which is the shape the synthetic caller in
// layout/ltcg/set_input_mode.json reproduces. The body was carved out of
// src/game/eclview/score.cpp, where the same offsets are used by other state code.

struct InputState {
    unsigned char unknown_0000[0x390];
    int           mode_390;              // +0x390, selected input mode
    unsigned char unknown_0394[0x3CC - 0x394];
    unsigned int  flags_3CC;             // +0x3CC, bit 0x1000 forces mode 2
};

__declspec(noinline) void SetInputMode(InputState* state, int mode);

#undef data_00491c10
#undef data_0047770c
#undef data_00474c40
#undef g_ascii_manager
#undef data_00477704
#undef g_player
#undef data_00477838
#undef data_0047783c
#undef data_00476f78
#undef data_00491fc4
#undef data_00491fb8
#undef data_00492590
#define data_00491c10 stage_decay_data_00491c10
#define data_0047770c stage_decay_data_0047770c
#define data_00474c40 stage_decay_data_00474c40
#define g_ascii_manager stage_decay_data_004776e0
#define data_00477704 stage_decay_data_00477704
#define g_player stage_decay_data_00477834
#define data_00477838 stage_decay_data_00477838
#define data_0047783c stage_decay_data_0047783c
#define data_00476f78 stage_decay_data_00476f78
#define data_00491fc4 stage_decay_data_00491fc4
#define data_00491fb8 stage_decay_data_00491fb8
#define data_00492590 stage_decay_data_00492590
// 0x00418A00..0x00418A40 (65 bytes): ScoreState::DecayGauge
//
// The gauge is raised by SetGauge/AddGauge and then runs down again. Two
// stages do that: while the gauge timer at +0x14 still has frames on it the
// timer is advanced by -1.0f, and once it has run out the gauge itself bleeds
// off by the decay step at +0x10, one step per frame, with the gauge held at
// the 5000 floor the other gauge updates use and the step held at 18.
//
// Retail, in order:
//     8B 48 18        mov ecx,[eax+18h]      ; gauge_timer.current
//     85 C9           test ecx,ecx
//     56              push esi
//     7E 0F           jle decay
//     68 00 00 80 BF  push 0BF800000h        ; -1.0f
//     8D 70 14        lea esi,[eax+14h]      ; &gauge_timer
//     E8 .. .. .. ..  call FrameTimer::Advance
//     5E C3           pop esi / ret
//  decay:
//     8B 48 0C        mov ecx,[eax+0Ch]      ; gauge
//     BE 88 13 00 00  mov esi,5000
//     3B CE           cmp ecx,esi
//     7E 1C           jle done
//     8B 50 10        mov edx,[eax+10h]      ; gauge_decay
//     2B CA           sub ecx,edx
//     83 FA 12        cmp edx,18
//     89 48 0C        mov [eax+0Ch],ecx
//     7D 07           jge skip
//     C7 40 10 12 00 00 00  mov [eax+10h],18
//  skip:
//     39 70 0C        cmp [eax+0Ch],esi
//     7D 03           jge done
//     89 70 0C        mov [eax+0Ch],esi
//  done:
//     5E C3           pop esi / ret
//
// The receiver arrives in EAX and the nested timer in ESI. Neither is a
// register an MSVC convention can express, so this source is compiled in the
// native-LTCG link that also carries FrameTimer::Advance
// (see layout/ltcg/frame_timer.json): the whole-program pass selects EAX for
// the gauge record and ESI for the timer the advance call is handed.
#include "th10/game/score.hpp"

#undef data_00491c10
#undef data_0047770c
#undef data_00474c40
#undef g_ascii_manager
#undef data_00477704
#undef g_player
#undef data_00477838
#undef data_0047783c
#undef data_00476f78
#undef data_00491fc4
#undef data_00491fb8
#undef data_00492590

__declspec(noinline) void __stdcall Stage_StartQuadScripts_00404450(Stage_00404450* stage);
