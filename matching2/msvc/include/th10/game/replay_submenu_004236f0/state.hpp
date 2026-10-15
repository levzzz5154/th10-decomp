#ifndef TH10_GAME_REPLAY_SUBMENU_004236F0_STATE_HPP
#define TH10_GAME_REPLAY_SUBMENU_004236F0_STATE_HPP

#include <stddef.h>
#include "th10/game/menu_cursor.hpp"
#include "th10/game/name_entry_prepare_00423570.hpp"
#include "th10/game/replay_manager_create_004296f0.hpp"

// ---------------------------------------------------------------------------
// Scoped views of the private-ABI helpers co-compiled inside this cluster.
// The bodies live in layout/ltcg/replay_submenu_004236f0/ and are anchored at
// their retail addresses; these declarations only name them for the caller.
// ---------------------------------------------------------------------------

struct AnimationScriptId {
    int value;
};

// 0x00405410 scheduler value record (receiver in EAX).
struct SubSchedulerRecord_004236f0 {
    int field_00;
    int field_04;
    float field_08;
    int field_0C;
    int flags_10;
    __declspec(noinline) void SetSchedulerValue(int value);
};

// 0x0040ACE0 key-repeat state (this in ECX, mask in EAX).
struct KeyRepeatState {
    unsigned char unknown_00[4];
    unsigned short pressed;         // +0x04 (0x00474E34)
    unsigned short unknown_06;      // +0x06 (0x00474E36)
    __declspec(noinline) int InputMaskActive(unsigned short mask);
};

// 0x0040AC90 input mode publisher (state in EAX, mode on the stack).
struct InputState {
    unsigned char unknown_0000[0x390];
    int mode_390;
    unsigned char unknown_0394[0x3CC - 0x394];
    unsigned int flags_3CC;
};
__declspec(noinline) void SubSetInputMode_004236f0(InputState* state, int mode);

// 0x00421F60 frame-maximum snapshot record.
struct GameStateFrameState {
    unsigned char unknown_0000[0x9E78];
    int frame_value;               // +0x9E78
};
__declspec(noinline) int __stdcall SubUpdateFrameMaximum_004236f0(GameStateFrameState* state);

// The menu cursor co-compiled bodies (0x0044BE20/0x0044BE70/0x0044BEA0);
// identical layout to the shared MenuCursor, scoped so the maintained
// definitions stay untouched.
struct SubmenuCursor_004236f0 {
    int selection;                       // +0x00
    int previous_selection;              // +0x04, saved by menu input handlers
    int item_count;                      // +0x08
    int selection_history[16];           // +0x0C
    int item_count_history[16];          // +0x4C
    int history_depth;                   // +0x8C
    int disabled_items[16];              // +0x90
    int wrap;                            // +0xD0
    int disabled_count;                  // +0xD4

    __declspec(noinline) void PushSelection();
    __declspec(noinline) void PopSelection();
    __declspec(noinline) int Advance(int delta);
};

// The sound queue body co-compiled at 0x0043DC90 (this in ECX, sound id in
// EDI, request on the stack).
struct SubSoundQueue_004236f0 {
    char reserved[0x408];
    int priorities[134];
    int sound_ids[12];
    int counts[12];
    int requests[12][128];
    __declspec(noinline) int Queue(int sound_id, int request);
};

struct SubRef4_004236f0;

// The animation views: 0x00449470 variable stop frame, 0x004497D0 child
// lookup returning the four-byte reference, 0x004243F0 stop frame 6 on the
// reference, 0x0040C4D0 stop frame 3, 0x00409E50 stop frame 1.
struct SubHandle4_004236f0 {
    unsigned int value;
    __declspec(noinline) void SetStopFrame(short frame);
    __declspec(noinline) void StopAtFrame1();
    __declspec(noinline) void StopAtFrame3();
    __declspec(noinline) SubRef4_004236f0 FindChildRef(int script_id);
};

struct SubRef4_004236f0 {
    int value;
    SubRef4_004236f0(int value) : value(value) {}
    __declspec(noinline) void StopAtFrame6();
};

// The flagged/cleared animation nodes (0x00449590/0x004495E0).
struct SubAnimNode_004236f0 {
    SubAnimNode_004236f0* field_000;   // +0x000
    SubAnimNode_004236f0* field_004;   // +0x004
    unsigned char pad_008[0x0C];
    SubAnimNode_004236f0* field_014;   // +0x014
    SubAnimNode_004236f0* field_018;   // +0x018
    unsigned char pad_01c[0x340];
    unsigned int flags_35c;            // +0x35C
    __declspec(noinline) void SetFlag();
    __declspec(noinline) void ClearFlag();
};

// 0x00423510 resets the whole result-screen record the submenu dispatch owns.
struct SubTimedState_004236f0 {
    unsigned char unknown_00[0x04];
    int state;                                 // +0x04
    unsigned char unknown_08[0x08];
    int timer_previous;                        // +0x10
    int timer_current;                         // +0x14
    int timer_elapsed;                         // +0x18
    float* timer_speed;                        // +0x1C
    unsigned int timer_flags;                  // +0x20
    unsigned char unknown_24[0x1B0];
    SubHandle4_004236f0 handle_1d4;            // +0x1D4
    SubHandle4_004236f0 handle_1d8;            // +0x1D8
    unsigned char unknown_1dc[0xE4];
    float speed;                               // +0x2C0
    __declspec(noinline) void InitializeTimedState();
};

// 0x004297B0: release + delete a platform resource (receiver in ESI).
struct PlatformResource;
__declspec(noinline) void __stdcall SubPlatformResource_Destroy_004236f0(
    PlatformResource* resource);

// 0x0040AD20: clamp a selection against the keyboard grid length.
__declspec(noinline) unsigned int __fastcall UpdateBoundedCounter(
    unsigned int requested, unsigned int* counter);

// The private-ABI replay serializer at 0x00429B60 (asm region): the manager
// arrives in ECX, the target path in EDX and the name on the stack.
extern "C" void __fastcall asm_FUN_00429b60_00429b60(
    void* manager, void* path, const char* name);

// The deleting-destructor call at 0x004294A0 pops its one stack argument
// (receiver on the stack, RET 4), so the body binds through this stdcall
// alias (coff_aliases maps it onto ??1ReplayManager_004296f0@@QAE@XZ).
extern "C" void __stdcall ReplayManager_Destroy_004294a0(void* manager);

// CRT shims (maintained regions).
extern "C" int __cdecl asm_sprintf_00452ae8(char* destination, const char* format, ...);
extern "C" unsigned int __cdecl asm_FID_conflict___time32_00452b71(unsigned int* output);
extern "C" void __cdecl asm_free_004524a1(void* memory);

// ---------------------------------------------------------------------------
// Globals (all bound by the maintained symbol table).
// ---------------------------------------------------------------------------

extern "C" KeyRepeatState data_00474e30;        // 0x00474E30
extern "C" unsigned int data_00474e36;          // 0x00474E36 (repeat word)
extern "C" unsigned int g_globals_flags;          // 0x00474CA0 (ranking gate bit 0x10)
extern "C" int g_globals_character;
extern "C" int g_globals_shot_type;
extern "C" int g_globals_difficulty;
extern "C" int g_globals_stage;
extern "C" GameStateFrameState* g_front;  // 0x0047770C
extern "C" InputState g_application;            // 0x00491C28
extern "C" int data_00491fb8;                   // 0x00491FB8 launch mode latch
extern "C" SubSoundQueue_004236f0 g_sound_manager; // 0x00492590 sound queue
extern "C" float g_game_speed;                 // 0x00476F78 shared game speed

// ---------------------------------------------------------------------------
// The result-screen record (the retail `this`, one stack argument, RET 4).
// ---------------------------------------------------------------------------

struct SubmenuState_004236f0 {
    unsigned char unknown_000[0x04];
    int state;                                   // +0x04
    unsigned char unknown_008[0x08];
    SubSchedulerRecord_004236f0 timer;           // +0x10 (+0x14 transition timer)
    SubmenuCursor_004236f0 rows;                 // +0x24 (selection/previous/count 25 or 3, wrap +0xF4)
    SubmenuCursor_004236f0 list;                 // +0xFC (grid cursor / name length, wrap +0x1CC)
    SubHandle4_004236f0 background;              // +0x1D4 task handle
    unsigned char unknown_1d8[0x1E0 - 0x1D8];
    int name_length;                             // +0x1E0 typed name length
    int extra_cleared;                           // +0x1E4 finished extra stage
    int no_entry;                                // +0x1E8 score missed the table
    void* handles[25];                           // +0x1EC replay managers per slot
    unsigned char unknown_250[0x2B4 - 0x250];
    char name[8];                                // +0x2B4 typed name
};

typedef char SubmenuStateTimerOffset_004236f0[offsetof(SubmenuState_004236f0, timer) == 0x10 ? 1 : -1];
typedef char SubmenuStateRowsOffset_004236f0[offsetof(SubmenuState_004236f0, rows) == 0x24 ? 1 : -1];
typedef char SubmenuStateListOffset_004236f0[offsetof(SubmenuState_004236f0, list) == 0xFC ? 1 : -1];
typedef char SubmenuStateBackgroundOffset_004236f0[offsetof(SubmenuState_004236f0, background) == 0x1D4 ? 1 : -1];
typedef char SubmenuStateHandlesOffset_004236f0[offsetof(SubmenuState_004236f0, handles) == 0x1EC ? 1 : -1];
typedef char SubmenuStateNameOffset_004236f0[offsetof(SubmenuState_004236f0, name) == 0x2B4 ? 1 : -1];

// The replay header fields the result screen writes (time and difficulty slot).
struct ReplayHeaderView_004236f0 {
    unsigned char unknown_00[0x0C];
    unsigned int saved_time;                    // +0x0C
    unsigned char unknown_10[0x5C - 0x10];
    int difficulty_slot;                         // +0x5C
};

#endif
