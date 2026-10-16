#pragma once
#include <stddef.h>

#include "th10/game/player.hpp"  // g_player, destroyed by 0x00424ED0 (Player::~Player)
#include "th10/game/score.hpp"
#include "th10/game/score_archive.hpp"
#include "th10/render/resource_registrar.hpp"

// 0x00417C80: release the per-session manager state and every global object
// the running session allocated. This header carries the object views and
// global bindings the teardown body needs.

// The twelve-byte position record handed to the animation manager (the same
// record 0x00448D50 fills into the object at +0x340). Identical to the local
// definition in the lazy-animation-fetch recovery; the cluster driver defines
// TH10_MANAGER_TEARDOWN_SHARED_TYPES_EXTERNAL when the co-compiled
// lazy-fetch source already brought these declarations into the unit.
#ifndef TH10_MANAGER_TEARDOWN_SHARED_TYPES_EXTERNAL
struct AnimationPosition {
    float x;
    float y;
    float z;
};

// The game thread object; only the animation fields the teardown touches are
// described. Identical to the local definition in the lazy-animation-fetch
// recovery, so both spellings can co-compile in one whole-program unit.
struct GameThread6 {
    unsigned char reserved_0000[0x8994];
    void* animation_resource;                       // +0x8994
    unsigned char reserved_8998[0x89A4 - 0x8998];
    void* animation_handle;                         // +0x89A4
    __declspec(noinline) void* EnsureAnimationResource(float x, float y);
};

// The animation manager's positioned-primary creation, recovered at
// 0x00448D50; the cluster carries its compiled body as an ABI anchor.
void** __stdcall AnimationManager_CreatePositionedPrimary(
    void* resource, void** out, int index,
    const AnimationPosition* position);
#endif

// An owned animation slot of the side panel.
struct PanelSlot {
    // 0x004136C0: hand the slot's animation back to the manager.
    __declspec(noinline) void Release();
};

// The side panel's stage-owned parts; the teardown releases the stage parts
// on the replay/recovery path.
struct FrontStagePartsView {
    unsigned char reserved_0000[0x9E80];
    int stage_state;                                // +0x9E80
    unsigned char reserved_9e84[0x9EB8 - 0x9E84];
    PanelSlot* stage_slot;                 // +0x9EB8
    void* stage_buffer;                             // +0x9EBC

    // 0x00414570: give back everything loaded for the stage.
    __declspec(noinline) void ReleaseStageParts();
};

extern "C" {

// Game flags (bit 0x2 marks a replay/recovery session; bit 0x1 the stage end;
// bit 0x8 the practice fail counter).
extern unsigned int g_globals_flags;
// Requested application mode (10 = stage 4, 0xB extra stage, 4/0xF stage 1,
// 0xD practice, 0xE/0xF ...).
extern int g_main_state;
// Shared score-animation speed, reset to 1.0 for the next run.
extern float g_score_default_speed;
// The run's score record; the capped fail counter sits at +0x50.
extern struct ScoreState g_globals;
// The score archive; flushed first so the run's record file is written.
extern struct ScoreArchive* g_score;
// The game thread.
extern GameThread6* g_ascii_manager;
// Stage file pointers; equality marks the stage-end state.
extern void* g_globals_stage;
extern void* g_globals_stage_shown;
// Game states (destroyed with 0x00402440).
extern void* g_background;
extern void* g_background_prev;
// The pause-menu manager (released by 0x00422220).
extern void* g_pause;
// The side panel / item manager object.
extern FrontStagePartsView* g_front;
// The bullet manager (destroyed by 0x00405F70).
extern void* g_bullet_manager;
// The native effect manager (destroyed by 0x0041ADF0); its element storage
// at +0x14 is wiped on the replay path.
extern void* g_item_manager;
// The score-extended object (released by 0x0041C1C0).
extern void* g_laser_manager;
// The resource state (released by 0x00418EE0).
extern void* g_hint;
// The effect manager (destroyed by 0x0042B570).
extern void* g_smoll_score;
// The replay manager / pending block (destroyed by 0x004294A0).
extern void* g_replay;
// The enemy manager (cleared by 0x00409F90 or destroyed by 0x0040D530).
extern struct EnemyCtrl* g_enemy_ctrl;
// The bullet-manager release (0x0040AF00).
extern void* g_effect;
// The recovery pair state (released by 0x00405620).
extern void* g_bomb;
// The spell-card manager (Card; destroyed by 0x00408AF0).
extern void* g_card;
// The one scheduler both removals go through.
extern struct FuncCtrl* g_func_ctrl;
// The shared animation resource name and the manager that re-registers it.
extern char str_dummy[];
extern struct AnimationManager9 g_sound_manager;
// Extra-content flag byte for the resource index choice.
extern unsigned char g_sound_flags;
// The published manager-state pointer, cleared with the state.
extern void* g_game;
// Post-teardown markers: the frame gate and the next-mode bias.
extern int g_screen_effects_frozen;
extern int g_main_clear_color;

}
