// 0x00418190: complete stage callback, all 1,544 retail bytes.
// The native cluster co-compiles full helpers to derive their register ABIs.
// The callback itself keeps its public stdcall context and RET4.
#include "../../../build_support/layout/ltcg/stage_update_00418190/types.hpp"
#include <stddef.h>
#include <string.h>

struct Game {
    unsigned char reserved_00[0x10];
    FrameTimer timer;
    unsigned char configuration[0x58 - 0x24];
    unsigned int flags;
};
struct Game_UpdateTask {
    int priority;
    unsigned int flags;
};
struct StageTaskPair {
    unsigned char reserved_00[8];
    Game_UpdateTask *update;
    Game_UpdateTask *draw;
    __forceinline void PauseOptional() {
        if (update)
            update->flags |= 2;
        if (draw)
            draw->flags |= 2;
    }
    __forceinline void PauseRequired() {
        update->flags |= 2;
        draw->flags |= 2;
    }
};
struct StageThreadAnimations {
    unsigned char reserved_00[0x89a0];
    AnimationHandle first;
    AnimationHandle second;
};
struct StageAssets {
    unsigned char reserved_00[0x24];
    int music_index;
};
struct StageScoreRecord {
    unsigned char reserved_00[0x4cc];
    int frames;
    unsigned char reserved_4d0[0x437c - 0x4d0];
};
struct StageScoreManager {
    StageScoreRecord records[6];
};
extern "C" {
extern PlatformWorker stage_worker;
extern unsigned int stage_status;
extern unsigned int stage_transition_mask;
extern unsigned char stage_config;
extern unsigned int stage_game_flags;
extern int stage_result;
extern Stage_00404450 *stage_quads;
extern BackGround *stage_fade;
extern BackGround *stage_mode;
extern BulletPool *stage_bullets;
extern PauseState_00424d90 *stage_player;
extern EnemyCtrlClearView *stage_enemies;
extern EnemyCtrlSpawnView *stage_spawn_manager;
extern ScoreChain *stage_chain;
extern ReplayManager_0042a6a0 *stage_replay;
extern unsigned char *stage_effects;
extern StageTaskPair *stage_tasks;
extern StageTaskPair *stage_items;
extern StageTaskPair *stage_lasers;
extern StageTaskPair *stage_popups;
extern StageTaskPair *stage_large;
extern StageTaskPair *stage_timer_tasks;
extern int stage_frames;
extern int stage_other_frames;
extern StageThreadAnimations *stage_thread;
extern StageAssets *stage_assets;
extern StageScoreManager *stage_scores;
extern InputState stage_application;
extern ScoreState stage_gauge;
extern const char str_main[];
extern const char str_dummy[];
void __stdcall StageDestroyGameState(void *state);
}
void __cdecl operator delete(void *object);
int __stdcall Music_Play(int track, int heard_index);
extern "C" AnimationManager_0043e460 stage_requests;

typedef char StageContextTimerOffset[offsetof(Game, timer) == 0x10 ? 1 : -1];
typedef char StageContextFlagsOffset[offsetof(Game, flags) == 0x58 ? 1 : -1];
typedef char StageRecordStride[sizeof(StageScoreRecord) == 0x437c ? 1 : -1];

__forceinline StageTaskPair *TaskPair(void *object) {
    return reinterpret_cast<StageTaskPair *>(object);
}
#pragma code_seg(".text$00418190_fn")
extern "C" __declspec(noinline) int __stdcall Game_Update(Game *context) {
    int frame = context->timer.current;
    if (frame == 0) {
        if (context->flags & 8) {
            stage_worker.Stop();
            stage_result = ((~(stage_status >> 12)) & 1) | 2;
            return 1;
        }
        Stage_StartQuadScripts(stage_quads);
        if (stage_fade) {
            stage_fade->BeginFade();
            stage_mode->StartMode();
            context->flags |= 0x800;
            reinterpret_cast<AnimationHandle *>(&stage_front_g_front->caption)
                ->StopAtFrame1();
        } else {
            context->flags &= ~0x800u;
            stage_bullets->Reset();
            ReplayPauseReset(stage_player);
            memset(stage_effects + 0x14, 0, 0x873a8 * 4);
            stage_enemies->Clear();
            stage_chain->ReleaseChain();
            stage_frames = 0;
            stage_other_frames = 0;
            stage_replay->FinishStage();
            EnemySpawn_0040cfb0 spawn;
            memset(&spawn, 0, sizeof(spawn));
            spawn.Create(stage_spawn_manager, str_main);
            stage_front_g_front->Initialize();
            stage_tasks->PauseOptional();
            TaskPair(stage_player)->PauseRequired();
            PlayerRefresh_00426f70(reinterpret_cast<Player*>(stage_player));
            TaskPair(stage_bullets)->PauseOptional();
            TaskPair(stage_enemies)->PauseOptional();
            TaskPair(stage_effects)->PauseOptional();
            TaskPair(stage_chain)->PauseOptional();
            stage_items->PauseRequired();
            stage_lasers->PauseOptional();
            stage_popups->PauseRequired();
            StageTaskPair *large = stage_large;
            large->PauseOptional();
            (*reinterpret_cast<Game_UpdateTask **>(reinterpret_cast<unsigned char *>(large) +
                                                   0x37ac))
                ->flags |= 2;
            stage_timer_tasks->PauseOptional();

            if (!(stage_game_flags & 0x20))
                Music_Play(0, stage_assets->music_index);
            stage_thread->first.StopAtFrame1();
            stage_thread->second.StopAtFrame1();
            stage_thread->second.value = 0;
        }
    } else if (frame == 30 && (context->flags & 0x800)) {
        context->flags &= ~0x800u;
        stage_bullets->Reset();
        ReplayPauseReset(stage_player);
        memset(stage_effects + 0x14, 0, 0x873a8 * 4);
        stage_enemies->Clear();
        stage_chain->ReleaseChain();
        stage_frames = 0;
        stage_other_frames = 0;
        stage_replay->FinishStage();
        EnemySpawn_0040cfb0 spawn;
        memset(&spawn, 0, sizeof(spawn));
        spawn.Create(stage_spawn_manager, str_main);
        stage_front_g_front->Initialize();
        stage_tasks->PauseOptional();
        TaskPair(stage_player)->PauseRequired();
        PlayerRefresh_00426f70(reinterpret_cast<Player*>(stage_player));
        TaskPair(stage_bullets)->PauseOptional();
        TaskPair(stage_enemies)->PauseOptional();
        TaskPair(stage_effects)->PauseOptional();
        TaskPair(stage_chain)->PauseOptional();
        stage_items->PauseRequired();
        stage_lasers->PauseOptional();
        stage_popups->PauseRequired();
        StageTaskPair *large = stage_large;
        large->PauseOptional();
        (*reinterpret_cast<Game_UpdateTask **>(reinterpret_cast<unsigned char *>(large) + 0x37ac))
            ->flags |= 2;
        stage_timer_tasks->PauseOptional();
        if (stage_config & 0x10)
            stage_requests.RegisterResource(str_dummy, 4, 0);
        else
            stage_requests.RegisterResource(str_dummy, 3, 0);
        Music_Play(0, stage_assets->music_index);
        stage_thread->second.StopAtFrame1();
        stage_thread->second.value = 0;
        reinterpret_cast<PlayerSchedulerRecord *>(&context->timer)->SetSchedulerValue(0);
    }
    // Read the shared pointer again for disposal. The original callback also
    // checks it before both destruction and deallocation.
    if (stage_fade && (stage_fade->flags & 8)) {
        BackGround *fade = stage_fade;
        if (fade) {
            StageDestroyGameState(fade);
            operator delete(fade);
        }
    }
    if (context->flags & 4) {
        context->flags |= 0x80;
        return 1;
    }
    stage_worker.Stop();
    if (stage_game_flags & 0x20) {
        if ((stage_transition_mask & 0x160b) || (context->flags & 0x70))
            stage_result = (stage_status & 0x1000) ? 2 : 4;
        int elapsed = context->timer.current;
        if (elapsed == 0xb7c)
            Screen_Create(43, 5, 60, 0, 0, 0);
        else if (elapsed == 3000)
            SetInputMode(&stage_application, 4);
    }
    stage_hud_g_front->Update();
    if (context->flags & 0x10)
        return 3;
    if (context->flags & 0x20)
        return 3;
    if (context->flags & 0x40)
        return 3;
    if (stage_replay->mode != 1) {
        int shot = 3 * stage_front_data.character + stage_front_data.shot_type;
        int *played = &stage_scores->records[shot].frames;
        if (*played < 215999999)
            ++*played;
    }
    if (stage_enemies->field_10 == 0 &&
        *reinterpret_cast<int *>(reinterpret_cast<unsigned char *>(stage_front_g_front) +
                                 0x9eb8) == 0 &&
        context->timer.current >= 90)
        stage_gauge.DecayGauge();
    ++stage_frames;
    ++stage_other_frames;
    context->timer.Tick();
    return 1;
}
#pragma code_seg()
