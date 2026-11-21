// 0x00417870: prepare the running stage and its scheduler callbacks.
// This complete body matches all 1,009 retail bytes in the maintained native
// cluster. The public entry takes the UI context on the stack and returns
// 0 on success or -1 after notifying the worker and retiring callbacks.
// The private helper conventions come from their complete C++ bodies in
// build_support/layout/ltcg/stage_startup.json.
#include <string.h>
#include "th10/game/stage_startup.hpp"
#include "th10/game/stage_route.hpp"
#include "th10/game/title_draw.hpp"
#include "th10/game/score_file.hpp"
#include "th10/core/func_ctrl.hpp"

struct Game {
    CallbackPair callbacks;
    FrameTimerView clock;
    unsigned int configuration[13];
    unsigned int flags;
    int replay_mode;
};
typedef char Game_InitializeFlags[offsetof(Game, flags) == 0x58 ? 1 : -1];

struct AnimationWaitState { int primary_pending; int secondary_pending; };
#pragma pack(push, 4)
struct StageTiming {
    unsigned char unknown_00[0x24];
    double first;
    double second;
};
#pragma pack(pop)
typedef char StageTimingFirst[offsetof(StageTiming, first) == 0x24 ? 1 : -1];
typedef char StageTimingSecond[offsetof(StageTiming, second) == 0x2C ? 1 : -1];

extern "C" {
extern AnimationWaitState* g_sprt_ctrl;
extern FuncCtrl* g_func_ctrl;
extern EnemyCtrlTimerView* g_enemy_ctrl;
extern StageTiming* g_fps;
extern void* g_front;
extern const char g_replay_path[];
extern int g_stage_wait;
extern int g_screen_effects_frozen;
extern const double dbl_0;
__declspec(dllimport) void __stdcall Sleep(unsigned int);
__declspec(noinline) int* __stdcall SchedulerTask_Create(int callback);
void* __stdcall ReplayCreate(int replay_mode, const char* file);  // 0x00429610: ReplayManager_Create
void* __stdcall CreateStageState(const char* file, int option);   // 0x00402640: BackGround_Create
void* __stdcall CreateItems();                                    // 0x00414830: Front_Create (HUD)
void* __cdecl CreatePlayerResources();                            // 0x00425020: Player_Create
void* __stdcall CreateProjectiles();                              // 0x00406060: BulletManager_Create
void* __stdcall CreateEffects();                                  // 0x0041AED0: ItemManager_Create
void* __cdecl CreateScore();                                      // 0x0041C290: LaserManager_Create
void* __stdcall CreateTimerResources();                           // 0x00422360: Pause_Create
void* __cdecl Hint_Create();                                      // 0x00419090: Hint_Create
void* __cdecl CreateLargeResources();                             // 0x0042B660: SmollScore_Create
int __stdcall SetupScoreTask(void* task);                         // 0x00413A20: Front_ResetForStage
void* __stdcall CreateEnemies(const char* file);                  // 0x0040D6B0: EnemyCtrl_Create
void* __stdcall CreateBulletState();                              // 0x0040AF90: EffectManager_Create
void* __cdecl CreateFixedState();                                 // 0x004056B0: Bomb_Create
void* __stdcall CreatePlayer();                                   // 0x00408C90: Card_Create (spell card panel)
int __stdcall StopMusic();
int __stdcall LoadMusic(int slot, const char* file);
void __stdcall ReleaseAnimations(void* state);
void __stdcall CleanupAnimations(void* state);
int __fastcall Game_UpdateCallback(void* context);
int __fastcall StageDrawCallback(void* context);
}

#pragma code_seg(".text$00417870_fn")
extern "C" __declspec(noinline) int __stdcall Game_Initialize(Game* context) {
    context->flags |= 4;
    while (g_sprt_ctrl->primary_pending >= 0 || g_sprt_ctrl->secondary_pending >= 0) {
        if (g_application.status & 0x80)
            goto failed;
        Sleep(1);
    }
    g_game_speed = 1.0f;
    g_globals.reserved_44[1] = 0;
    g_globals.reserved_44[2] = 0;
    if (g_application.stage_reset) {
        if (g_globals.stage == 7)
            g_globals.difficulty = 4;
        ScoreManager* scores = reinterpret_cast<ScoreManager*>(g_score);
        const int shot = g_globals.character * 3 + g_globals.shot_type;
        const int difficulty = g_globals.difficulty;
        // A difficulty page occupies ten rank entries. Keep its byte origin
        // at the manager's prefix; the named offsets still describe the real
        // score-file fields and scalar memcpy avoids an overlapping type view.
        const unsigned char* page = reinterpret_cast<const unsigned char*>(scores) +
            shot * sizeof(ScoreRecordSection) +
            difficulty * sizeof(ScoreRankEntry[SCORE_RANKS_PER_DIFFICULTY]);
        const size_t rank_offset = offsetof(ScoreManager, records) + offsetof(ScoreRecordSection, ranks);
        memcpy(&g_globals.high_score, page + rank_offset, sizeof(g_globals.high_score));
        g_globals.high_score_continues = static_cast<signed char>(page[rank_offset + offsetof(ScoreRankEntry, continues)]);
        if (!(g_globals.flags & 8))
            g_globals.continues = 0;
        g_globals.score = 0;
        g_globals.SetGauge(50000);
        if (!(g_globals.flags & 0x10))
            g_globals.lives = 2;
        else
            g_globals.lives = g_globals.initial_lives == 0 ? 9 : g_globals.initial_lives - 1;
        g_globals.word_08 = g_globals.stage == 1 ? 0 : 80;
        g_globals.flags &= ~4u;
        if (context->replay_mode == 0) {
            // The play counter is the first word of this record's runtime tail.
            unsigned char* count_bytes = scores->records[g_globals.character * 3 + g_globals.shot_type].reserved_4c0;
            int plays;
            memcpy(&plays, count_bytes, sizeof(plays));
            if (plays < 99999) {
                ++plays;
                memcpy(count_bytes, &plays, sizeof(plays));
            }
        }
        g_globals.field_5c = 0;
        g_globals.rank = (static_cast<unsigned char>(g_globals.flags) & 8) ? -512 : 0;
    } else {
        if (g_globals.score > g_globals.high_score)
            g_globals.high_score = g_globals.score;
    }
    g_globals.gauge_decay = 9;
    {
        CallbackTask* task = reinterpret_cast<CallbackTask*>(SchedulerTask_Create(reinterpret_cast<int>(&Game_UpdateCallback)));
        unsigned int active_flags = task->flags & ~2u;
        task->context = context;
        task->flags = active_flags;
        FuncCtrl_RegisterPrimary(g_func_ctrl, reinterpret_cast<SchedulerTask*>(task), 10);
        context->callbacks.primary_task = reinterpret_cast<SchedulerCallback*>(task);
        task = reinterpret_cast<CallbackTask*>(SchedulerTask_Create(reinterpret_cast<int>(&StageDrawCallback)));
        task->flags &= ~2u;
        task->context = context;
        FuncCtrl_RegisterSecondary(g_func_ctrl, reinterpret_cast<SchedulerTask*>(task), 4);
        context->callbacks.secondary_task = reinterpret_cast<SchedulerCallback*>(task);
    }
    memcpy(context->configuration, g_application.configuration, sizeof(context->configuration));
    // The callback pair's second prefix word stores the stage kind.
    memcpy(context->callbacks.unknown_00 + sizeof(int), &g_stage_route_current->stage_kind, sizeof(int));
    if (!(g_globals.flags & 2)) {
        if (!ReplayCreate(context->replay_mode, g_replay_path)) goto failed;
        if (!CreateStageState(g_stage_route_current->stage_file, 0)) goto failed;
        if (!CreateItems()) goto failed;
        if (!CreatePlayerResources()) goto failed;
        if (!CreateProjectiles()) goto failed;
        if (!CreateEffects()) goto failed;
        if (!CreateScore()) goto failed;
        if (!CreateTimerResources()) goto failed;
        if (!Hint_Create()) goto failed;
        if (!CreateLargeResources()) goto failed;
    } else {
        reinterpret_cast<ReplayManager2*>(g_replay)->BeginStage();
        SetupScoreTask(g_front);
        if (!CreateStageState(g_stage_route_current->stage_file, 0)) goto failed;
    }
    if (!(g_globals.flags & 9)) {
        if (!CreateEnemies(g_stage_route_current->enemy_script_file)) goto failed;
    } else {
        g_enemy_ctrl->ResetTimer();
    }
    if (!CreateBulletState()) goto failed;
    if (!CreateFixedState()) goto failed;
    if (!CreatePlayer()) goto failed;
    if (!(g_globals.flags & 0x20)) {
        StopMusic();
        LoadMusic(0, g_stage_route_current->music_files[0]);
        LoadMusic(1, g_stage_route_current->music_files[1]);
    }
    g_fps->second = dbl_0;
    g_fps->first = dbl_0;
    context->clock.Set(0);
    while (g_stage_wait)
        Sleep(16);
    if (g_globals.reserved_44[0])
        g_globals.reserved_44[2] = 0;
    g_globals.reserved_44[0] = 0;
    CleanupAnimations(&g_application);
    context->flags &= ~4u;
    g_globals.flags &= ~11u;
    g_application.worker_running = 0;
    g_application.worker_stop_requested = 1;
    g_screen_effects_frozen = 0;
    context->callbacks.RetireCallbacks();
    return 0;
failed:
    context->flags |= 8;
    ReleaseAnimations(&g_application);
    g_application.worker_running = 0;
    g_application.worker_stop_requested = 1;
    if (context->callbacks.primary_task)
        context->callbacks.primary_task->flags_04 |= 2;
    if (context->callbacks.secondary_task)
        context->callbacks.secondary_task->flags_04 |= 2;
    return -1;
}
#pragma code_seg()
