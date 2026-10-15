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
extern PlatformWorker stage_worker_00492254;
extern unsigned int stage_status_00491ff4;
extern unsigned int stage_transition_mask_00474e30;
extern unsigned char stage_config_00491d78;
extern unsigned int stage_game_flags_00474ca0;
extern int stage_result_00491fb8;
extern Stage_00404450 *stage_quads_004776e8;
extern BackGround *stage_fade_004776e4;
extern BackGround *stage_mode_004776e8;
extern BulletPool *stage_bullets_004776f0;
extern PauseState_00424d90 *stage_player_00477834;
extern EnemyCtrlClearView *stage_enemies_00477704;
extern EnemyCtrlSpawnView *stage_spawn_manager_00477704;
extern ScoreChain_00417770 *stage_chain_0047781c;
extern ReplayManager_0042a6a0 *stage_replay_00477838;
extern unsigned char *stage_effects_00477818;
extern StageTaskPair *stage_tasks_00477830;
extern StageTaskPair *stage_items_004776fc;
extern StageTaskPair *stage_lasers_004776ec;
extern StageTaskPair *stage_popups_00477840;
extern StageTaskPair *stage_large_004776f4;
extern StageTaskPair *stage_timer_tasks_00477814;
extern int stage_frames_00474c88;
extern int stage_other_frames_00474c8c;
extern StageThreadAnimations *stage_thread_004776e0;
extern StageAssets *stage_assets_00477848;
extern StageScoreManager *stage_scores_0047783c;
extern InputState stage_application_00491c28;
extern ScoreState stage_gauge_00474c40;
extern const char str_main[];
extern const char str_dummy[];
void __stdcall StageDestroyGameState(void *state);
}
void __cdecl operator delete(void *object);
int __stdcall Music_Play(int track, int heard_index);
extern "C" AnimationManager_0043e460 stage_requests_00492590;

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
            stage_worker_00492254.Stop();
            stage_result_00491fb8 = ((~(stage_status_00491ff4 >> 12)) & 1) | 2;
            return 1;
        }
        Stage_StartQuadScripts_00404450(stage_quads_004776e8);
        if (stage_fade_004776e4) {
            stage_fade_004776e4->BeginFade();
            stage_mode_004776e8->StartMode();
            context->flags |= 0x800;
            reinterpret_cast<AnimationHandle *>(&stage_front_g_front->caption)
                ->StopAtFrame1();
        } else {
            context->flags &= ~0x800u;
            stage_bullets_004776f0->Reset();
            ReplayPauseReset_00424d90(stage_player_00477834);
            memset(stage_effects_00477818 + 0x14, 0, 0x873a8 * 4);
            stage_enemies_00477704->Clear();
            stage_chain_0047781c->ReleaseChain();
            stage_frames_00474c88 = 0;
            stage_other_frames_00474c8c = 0;
            stage_replay_00477838->FinishStage();
            EnemySpawn_0040cfb0 spawn;
            memset(&spawn, 0, sizeof(spawn));
            spawn.Create(stage_spawn_manager_00477704, str_main);
            stage_front_g_front->Initialize();
            stage_tasks_00477830->PauseOptional();
            TaskPair(stage_player_00477834)->PauseRequired();
            PlayerRefresh_00426f70(reinterpret_cast<Player*>(stage_player_00477834));
            TaskPair(stage_bullets_004776f0)->PauseOptional();
            TaskPair(stage_enemies_00477704)->PauseOptional();
            TaskPair(stage_effects_00477818)->PauseOptional();
            TaskPair(stage_chain_0047781c)->PauseOptional();
            stage_items_004776fc->PauseRequired();
            stage_lasers_004776ec->PauseOptional();
            stage_popups_00477840->PauseRequired();
            StageTaskPair *large = stage_large_004776f4;
            large->PauseOptional();
            (*reinterpret_cast<Game_UpdateTask **>(reinterpret_cast<unsigned char *>(large) +
                                                   0x37ac))
                ->flags |= 2;
            stage_timer_tasks_00477814->PauseOptional();

            if (!(stage_game_flags_00474ca0 & 0x20))
                Music_Play(0, stage_assets_00477848->music_index);
            stage_thread_004776e0->first.StopAtFrame1();
            stage_thread_004776e0->second.StopAtFrame1();
            stage_thread_004776e0->second.value = 0;
        }
    } else if (frame == 30 && (context->flags & 0x800)) {
        context->flags &= ~0x800u;
        stage_bullets_004776f0->Reset();
        ReplayPauseReset_00424d90(stage_player_00477834);
        memset(stage_effects_00477818 + 0x14, 0, 0x873a8 * 4);
        stage_enemies_00477704->Clear();
        stage_chain_0047781c->ReleaseChain();
        stage_frames_00474c88 = 0;
        stage_other_frames_00474c8c = 0;
        stage_replay_00477838->FinishStage();
        EnemySpawn_0040cfb0 spawn;
        memset(&spawn, 0, sizeof(spawn));
        spawn.Create(stage_spawn_manager_00477704, str_main);
        stage_front_g_front->Initialize();
        stage_tasks_00477830->PauseOptional();
        TaskPair(stage_player_00477834)->PauseRequired();
        PlayerRefresh_00426f70(reinterpret_cast<Player*>(stage_player_00477834));
        TaskPair(stage_bullets_004776f0)->PauseOptional();
        TaskPair(stage_enemies_00477704)->PauseOptional();
        TaskPair(stage_effects_00477818)->PauseOptional();
        TaskPair(stage_chain_0047781c)->PauseOptional();
        stage_items_004776fc->PauseRequired();
        stage_lasers_004776ec->PauseOptional();
        stage_popups_00477840->PauseRequired();
        StageTaskPair *large = stage_large_004776f4;
        large->PauseOptional();
        (*reinterpret_cast<Game_UpdateTask **>(reinterpret_cast<unsigned char *>(large) + 0x37ac))
            ->flags |= 2;
        stage_timer_tasks_00477814->PauseOptional();
        if (stage_config_00491d78 & 0x10)
            stage_requests_00492590.RegisterResource(str_dummy, 4, 0);
        else
            stage_requests_00492590.RegisterResource(str_dummy, 3, 0);
        Music_Play(0, stage_assets_00477848->music_index);
        stage_thread_004776e0->second.StopAtFrame1();
        stage_thread_004776e0->second.value = 0;
        reinterpret_cast<PlayerSchedulerRecord *>(&context->timer)->SetSchedulerValue(0);
    }
    // Read the shared pointer again for disposal. The original callback also
    // checks it before both destruction and deallocation.
    if (stage_fade_004776e4 && (stage_fade_004776e4->flags & 8)) {
        BackGround *fade = stage_fade_004776e4;
        if (fade) {
            StageDestroyGameState(fade);
            operator delete(fade);
        }
    }
    if (context->flags & 4) {
        context->flags |= 0x80;
        return 1;
    }
    stage_worker_00492254.Stop();
    if (stage_game_flags_00474ca0 & 0x20) {
        if ((stage_transition_mask_00474e30 & 0x160b) || (context->flags & 0x70))
            stage_result_00491fb8 = (stage_status_00491ff4 & 0x1000) ? 2 : 4;
        int elapsed = context->timer.current;
        if (elapsed == 0xb7c)
            Screen_Create(43, 5, 60, 0, 0, 0);
        else if (elapsed == 3000)
            SetInputMode(&stage_application_00491c28, 4);
    }
    stage_hud_g_front->Update();
    if (context->flags & 0x10)
        return 3;
    if (context->flags & 0x20)
        return 3;
    if (context->flags & 0x40)
        return 3;
    if (stage_replay_00477838->mode != 1) {
        int shot = 3 * stage_front_data_00474c40.character + stage_front_data_00474c40.shot_type;
        int *played = &stage_scores_0047783c->records[shot].frames;
        if (*played < 215999999)
            ++*played;
    }
    if (stage_enemies_00477704->field_10 == 0 &&
        *reinterpret_cast<int *>(reinterpret_cast<unsigned char *>(stage_front_g_front) +
                                 0x9eb8) == 0 &&
        context->timer.current >= 90)
        stage_gauge_00474c40.DecayGauge();
    ++stage_frames_00474c88;
    ++stage_other_frames_00474c8c;
    context->timer.Tick();
    return 1;
}
#pragma code_seg()
