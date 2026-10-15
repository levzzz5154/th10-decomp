// 0x00417C80 (1105 bytes): release the per-session manager state.
//
// The manager state block the game thread owns (published at 0x00477810)
// arrives as the one stack argument. The body first flushes the score
// archive, resets the shared run flags and the score-animation speed, and
// lets the requested application mode decide how the game thread's animation
// handle is retired. It then splits on the replay flag (bit 0x2 of the run
// flags): a replay/recovery session only releases the side panel's stage
// parts, hands the second game state to the first slot, clears the active
// flag on the task records the pause menu, bullet manager and replay manager
// still publish, and wipes the native effect manager's element storage. A
// normal session destroys every per-session manager object and hands it back
// to the heap. Afterwards the enemy manager is either cleared in place (run
// still active, flag bits 0 or 3) or destroyed, the bullet-manager release,
// recovery pair and player manager go, and the state's two scheduler tasks
// are unhooked under the scheduler lock. Finally the published state pointer
// dies, the shared animation resource is re-registered for the next run
// (unless replay bits 0x22 remain), and the frame gate and next-mode bias
// markers are written.
//
// Retail hands several callees their receiver in a register no MSVC
// declaration names: the score archive reaches Save in EBX, the game thread
// reaches EnsureAnimationResource in ESI, the positioned-primary creation
// gets the position record in EDI, the enemy manager reaches Destroy in EAX,
// the score record reaches IncrementCappedCount in EAX, the resource
// registrar takes the manager in EAX and the name in EDX, and the side panel
// reaches ReleaseStageParts in EBX. Only a native /LTCG link that can see the
// callees' bodies assigns those registers, so the region is compiled in the
// cluster build_support/layout/ltcg/manager_state_release.json, whose driver and
// anchor sources carry a compiled body for each of them, placed at the retail
// address and never exported as recovered code.
#include "th10/game/manager_teardown_00417c80.hpp"
#include "th10/game/enemy_ctrl.hpp"
#include "th10/core/func_ctrl.hpp"
#include "th10/platform/thread_sync.hpp"
#include <string.h>

extern "C" void __cdecl crt_free_startup(void* memory);

// The stack-argument destroy callees, each spelled with its fixed retail
// prototype (receiver at [ESP+4], RET 4).
extern "C" void __stdcall BackGround_Destroy(void* state);
extern "C" void __stdcall Manager_Release(void* manager);
extern "C" void __stdcall Front_Destroy(void* manager);
extern "C" void __stdcall StageManager_Destroy(void* manager);
extern "C" void __stdcall BulletManager_Destroy(void* manager);
extern "C" void __stdcall ItemManager_Destroy(void* manager);
extern "C" void __stdcall ScoreExtendedObject_DestroyRetail(void* object);
extern "C" void __stdcall ResourceCleanup_00418ee0(void* state);
extern "C" void __stdcall EffectManager_Destroy(void* manager);
extern "C" void __stdcall ManagerOwned_Destroy(void* manager);
extern "C" void __stdcall EnemyCtrl_Clear_00409f90(void* manager);
extern "C" void __stdcall BulletManager_Release(void* manager);
extern "C" void __stdcall Bomb_Release(void* state);
extern "C" void __stdcall Card_Destroy_00408af0(void* manager);

// The manager state block: two scheduler tasks the game thread registered.
struct Game {
    unsigned char reserved_000[8];
    SchedulerTask* task_008;                        // +0x08
    SchedulerTask* task_00C;                        // +0x0C
};

// A task-holder record whose active flag sits at +4.
struct TaskFlagRecord {
    unsigned char reserved_000[4];
    unsigned int flags_004;                         // +0x04
};

// The pause-menu and bullet managers publish two records each, at +8 and +0xC.
struct TaskPairOwner {
    unsigned char reserved_000[8];
    TaskFlagRecord* node_008;              // +0x08
    TaskFlagRecord* node_00C;              // +0x0C
};

// The replay manager publishes one record at +0x1CC and one at +0xC.
struct ReplayTaskPairOwner {
    unsigned char reserved_000[0x0C];
    TaskFlagRecord* node_00C;              // +0x0C
    unsigned char reserved_010[0x1CC - 0x10];
    TaskFlagRecord* node_1CC;              // +0x1CC
};

#pragma code_seg(".text$9release")
extern "C" __declspec(noinline)
void __stdcall Game_Destroy(Game* state) {
    // The score archive owns the run's record file; flush it first. Retail
    // hands the archive over in EBX.
    g_score->Save();

    g_globals_flags &= ~3u;
    g_score_default_speed = 1.0f;

    // The replay-session flag; the branch below reads it back.
    unsigned char replay_bit = 2;

    if (g_main_state == 10) {
        // Retail runs the animation fetch inline in this first mode arm (the
        // only inlined Ensure instance) and out of line everywhere else. The
        // handle is reached through the loaded game-thread value, so the
        // handle's address is materialized ahead of the creation call.
        void** handle_slot = &g_ascii_manager->animation_handle;
        AnimationPosition_00448d50 position;
        position.x = 480.0f;
        position.y = 392.0f;
        position.z = 0.0f;
        if (*handle_slot == 0) {
            void* slot_handle;
            void** slot = AnimationManager_CreatePositionedPrimary(
                g_ascii_manager->animation_resource, &slot_handle, 6, &position);
            *handle_slot = *slot;
        }
        if (g_globals_stage_shown == g_globals_stage)
            g_globals_flags |= 1u;
    } else if (g_main_state == 0xB) {
        GameThread_0040c540* thread = g_ascii_manager;
        thread->EnsureAnimationResource(224.0f, 416.0f);
        g_globals_flags |= replay_bit;
    } else if (g_main_state == 4) {
        GameThread_0040c540* thread = g_ascii_manager;
        thread->EnsureAnimationResource(480.0f, 392.0f);
    } else if (g_main_state == 0xF) {
        GameThread_0040c540* thread = g_ascii_manager;
        thread->EnsureAnimationResource(480.0f, 392.0f);
    } else if (g_main_state == 0xD) {
        GameThread_0040c540* thread = g_ascii_manager;
        thread->EnsureAnimationResource(480.0f, 392.0f);
        if (g_globals_stage_shown != g_globals_stage) {
            g_globals.IncrementCappedCount();
            g_globals_flags |= 8u;
        }
        g_globals_flags |= 1u;
    }

    if (!(g_globals_flags & replay_bit)) {
        // Full teardown of every per-session manager object.
        if (g_main_state != 0xE && g_main_state != 0xF) {
            void* replay_manager = g_replay;
            if (replay_manager) {
                ManagerOwned_Destroy(replay_manager);
                crt_free_startup(replay_manager);
            }
        }
        void* pending_state = g_background;
        if (pending_state) {
            BackGround_Destroy(pending_state);
            crt_free_startup(pending_state);
        }
        void* current_state = g_background_prev;
        if (current_state) {
            BackGround_Destroy(current_state);
            crt_free_startup(current_state);
        }
        void* pause_menu = g_pause;
        if (pause_menu) {
            Manager_Release(pause_menu);
            crt_free_startup(pause_menu);
        }
        void* items = g_front;
        if (items) {
            Front_Destroy(items);
            crt_free_startup(items);
        }
        void* stage = g_player;
        if (stage) {
            StageManager_Destroy(stage);
            crt_free_startup(stage);
        }
        void* bullets = g_bullet_manager;
        if (bullets) {
            BulletManager_Destroy(bullets);
            crt_free_startup(bullets);
        }
        void* native_effects = g_item_manager;
        if (native_effects) {
            ItemManager_Destroy(native_effects);
            crt_free_startup(native_effects);
        }
        void* score_extended = g_laser_manager;
        if (score_extended) {
            ScoreExtendedObject_DestroyRetail(score_extended);
            crt_free_startup(score_extended);
        }
        void* resource_state = g_hint;
        if (resource_state) {
            ResourceCleanup_00418ee0(resource_state);
            crt_free_startup(resource_state);
        }
        void* effects = g_smoll_score;
        if (effects) {
            EffectManager_Destroy(effects);
            crt_free_startup(effects);
        }
    } else {
        // Replay/recovery teardown: the side panel's stage parts go back, the
        // second game state moves into the first slot, and the task records
        // the surviving managers publish lose their active flag.
        FrontStagePartsView* panel = g_front;
        panel->ReleaseStageParts();
        void* retired_state = g_background_prev;
        if (retired_state) {
            BackGround_Destroy(retired_state);
            crt_free_startup(retired_state);
        }
        g_background_prev = g_background;

        TaskPairOwner* pause = (TaskPairOwner*)g_pause;
        if (pause->node_008) pause->node_008->flags_004 &= ~2u;
        if (pause->node_00C) pause->node_00C->flags_004 &= ~2u;
        TaskPairOwner* bullet = (TaskPairOwner*)g_bullet_manager;
        if (bullet->node_008) bullet->node_008->flags_004 &= ~2u;
        if (bullet->node_00C) bullet->node_00C->flags_004 &= ~2u;
        ReplayTaskPairOwner* replay =
            (ReplayTaskPairOwner*)g_replay;
        if (replay->node_1CC) replay->node_1CC->flags_004 &= ~2u;
        if (replay->node_00C) replay->node_00C->flags_004 &= ~2u;
        // The native effect manager's element storage is wiped for the next
        // run; the wipe covers 0x873A8 dwords from +0x14.
        memset((char*)g_item_manager + 0x14, 0, 0x873A8 * 4);
    }

    // 0x00417F80: with the run still active (flag bits 0 or 3) the enemy
    // manager is cleared in place; otherwise it is destroyed and freed.
    if (g_globals_flags & 9u) {
        EnemyCtrl_Clear_00409f90(g_enemy_ctrl);
    } else {
        EnemyCtrl* enemies = g_enemy_ctrl;
        if (enemies) {
            enemies->Destroy();
            crt_free_startup(enemies);
        }
    }
    void* bullet_release = g_effect;
    if (bullet_release) {
        BulletManager_Release(bullet_release);
        crt_free_startup(bullet_release);
    }
    void* recovery_pair = g_bomb;
    if (recovery_pair) {
        Bomb_Release(recovery_pair);
        crt_free_startup(recovery_pair);
    }
    void* players = g_card;
    if (players) {
        Card_Destroy_00408af0(players);
        crt_free_startup(players);
    }

    // Unhook the manager state's two scheduler tasks under the scheduler lock.
    FuncCtrl* scheduler = g_func_ctrl;
    SchedulerTask* primary = state->task_008;
    if (primary) {
        EnterCriticalSection(&g_thread_synchronization.critical_sections[0]);
        ++g_thread_synchronization.scheduler_lock_depth;
        FuncCtrl_RemoveTask(primary, scheduler);
        LeaveCriticalSection(&g_thread_synchronization.critical_sections[0]);
        --g_thread_synchronization.scheduler_lock_depth;
    }
    SchedulerTask* secondary = state->task_00C;
    if (secondary) {
        EnterCriticalSection(&g_thread_synchronization.critical_sections[0]);
        ++g_thread_synchronization.scheduler_lock_depth;
        FuncCtrl_RemoveTask(secondary, scheduler);
        LeaveCriticalSection(&g_thread_synchronization.critical_sections[0]);
        --g_thread_synchronization.scheduler_lock_depth;
    }

    // The published manager-state pointer dies with the state.
    g_game = 0;
    if (!(g_globals_flags & 0x22u)) {
        // Re-register the shared animation resource for the next run; the
        // resource index is 4 when the extra-content flag is set. Retail
        // hands the registrar its manager in EAX and the name in EDX.
        g_sound_manager.RegisterResource(
            str_dummy, (g_sound_flags & 0x10u) ? 4 : 3, 0);
    }

    // The frame gate opens for the next scene and the mode bias records
    // whether the stage-end flag was still set. Keep the dword view: the
    // narrower byte load makes the emitted epilogue exceed the region and
    // previously caused the return instruction to be cut off.
    g_screen_effects_frozen = 1;
    g_main_clear_color = (g_globals_flags & 1) ? 0 : -0x1000000;
}
#pragma code_seg()
