// 0x00417870: prepare the running stage and its scheduler callbacks.
// This complete body matches all 1,009 retail bytes in the maintained native
// cluster. The public entry takes the UI context on the stack and returns
// 0 on success or -1 after notifying the worker and retiring callbacks.
// The private helper conventions come from their complete C++ bodies in
// layout/ltcg/stage_startup_00417870.json.
#include <string.h>
#include "th10/game/stage_startup_00417870.hpp"
#include "th10/game/title_menu_draw.hpp"
#include "th10/game/score_file.hpp"
#include "th10/game/scheduler.hpp"
#include "../../layout/ltcg/stage_startup_00417870/callback_task.hpp"
#include "../../layout/ltcg/stage_startup_00417870/path_reset.cpp"
#include "../../layout/ltcg/stage_startup_00417870/set_clock.cpp"
#include "../../layout/ltcg/stage_startup_00417870/retire_callbacks.cpp"

struct StageStartup_00417870 {
    CallbackPair callbacks;
    PlayerSchedulerRecord clock;
    unsigned int configuration[13];
    unsigned int flags;
    int replay_mode;
};
typedef char StageStartupFlags[offsetof(StageStartup_00417870, flags) == 0x58 ? 1 : -1];

struct AnimationWaitState_00417870 { int primary_pending; int secondary_pending; };
struct StageResources_00417870 {
    int stage_kind;
    const char* stage_file;
    unsigned int unknown_08;
    const char* enemy_file;
    const char* music[2];
};
#pragma pack(push, 4)
struct StageTiming_00417870 {
    unsigned char unknown_00[0x24];
    double first;
    double second;
};
#pragma pack(pop)
typedef char StageTimingFirst[offsetof(StageTiming_00417870, first) == 0x24 ? 1 : -1];
typedef char StageTimingSecond[offsetof(StageTiming_00417870, second) == 0x2C ? 1 : -1];

extern "C" {
extern AnimationWaitState_00417870* data_00491c10;
extern Scheduler* data_00491be4;
extern StageResources_00417870* data_00477848;
extern PathState_00417800* data_00477704;
extern StageTiming_00417870* data_00477708;
extern void* data_0047770c;
extern const char data_00477710[];
extern int data_00494518;
extern int data_004918a4;
extern const double data_00470b70;
__declspec(dllimport) void __stdcall Sleep(unsigned int);
__declspec(noinline) int* __stdcall SchedulerCallback_Create_00449ed0(int callback);
void* __stdcall ReplayCreate(int replay_mode, const char* file);
void* __stdcall CreateStageState(const char* file, int option);
void* __stdcall CreateItems();
void* __cdecl CreatePlayerResources();
void* __stdcall CreateProjectiles();
void* __stdcall CreateEffects();
void* __cdecl CreateScore();
void* __stdcall CreateTimerResources();
void* __cdecl CreateStageTips();
void* __cdecl CreateLargeResources();
int __stdcall SetupScoreTask(void* task);
void* __stdcall CreateEnemies(const char* file);
void* __stdcall CreateBulletState();
void* __cdecl CreateFixedState();
void* __stdcall CreatePlayer();
int __stdcall StopMusic();
int __stdcall LoadMusic(int slot, const char* file);
void __stdcall ReleaseAnimations(void* state);
void __stdcall CleanupAnimations(void* state);
int __fastcall StageUpdateCallback(void* context);
int __fastcall StageDrawCallback(void* context);
}

#pragma code_seg(".text$00417870_fn")
extern "C" __declspec(noinline) int __stdcall StageStartup(StageStartup_00417870* context) {
    context->flags |= 4;
    while (data_00491c10->primary_pending >= 0 || data_00491c10->secondary_pending >= 0) {
        if (data_00491c28.status & 0x80)
            goto failed;
        Sleep(1);
    }
    data_00476f78 = 1.0f;
    data_00474c40.reserved_44[1] = 0;
    data_00474c40.reserved_44[2] = 0;
    if (data_00491c28.stage_reset) {
        if (data_00474c40.stage == 7)
            data_00474c40.difficulty = 4;
        ScoreManager* scores = reinterpret_cast<ScoreManager*>(data_0047783c);
        const int shot = data_00474c40.character * 3 + data_00474c40.shot_type;
        const int difficulty = data_00474c40.difficulty;
        // A difficulty page occupies ten rank entries. Keep its byte origin
        // at the manager's prefix; the named offsets still describe the real
        // score-file fields and scalar memcpy avoids an overlapping type view.
        const unsigned char* page = reinterpret_cast<const unsigned char*>(scores) +
            shot * sizeof(ScoreRecordSection) +
            difficulty * sizeof(ScoreRankEntry[SCORE_RANKS_PER_DIFFICULTY]);
        const size_t rank_offset = offsetof(ScoreManager, records) + offsetof(ScoreRecordSection, ranks);
        memcpy(&data_00474c40.high_score, page + rank_offset, sizeof(data_00474c40.high_score));
        data_00474c40.high_score_continues = static_cast<signed char>(page[rank_offset + offsetof(ScoreRankEntry, continues)]);
        if (!(data_00474c40.flags & 8))
            data_00474c40.continues = 0;
        data_00474c40.score = 0;
        data_00474c40.SetGauge(50000);
        if (!(data_00474c40.flags & 0x10))
            data_00474c40.lives = 2;
        else
            data_00474c40.lives = data_00474c40.initial_lives == 0 ? 9 : data_00474c40.initial_lives - 1;
        data_00474c40.word_08 = data_00474c40.stage == 1 ? 0 : 80;
        data_00474c40.flags &= ~4u;
        if (context->replay_mode == 0) {
            // The play counter is the first word of this record's runtime tail.
            unsigned char* count_bytes = scores->records[data_00474c40.character * 3 + data_00474c40.shot_type].reserved_4c0;
            int plays;
            memcpy(&plays, count_bytes, sizeof(plays));
            if (plays < 99999) {
                ++plays;
                memcpy(count_bytes, &plays, sizeof(plays));
            }
        }
        data_00474c40.field_5c = 0;
        data_00474c40.field_58 = (static_cast<unsigned char>(data_00474c40.flags) & 8) ? -512 : 0;
    } else {
        if (data_00474c40.score > data_00474c40.high_score)
            data_00474c40.high_score = data_00474c40.score;
    }
    data_00474c40.gauge_decay = 9;
    {
        CallbackTask* task = reinterpret_cast<CallbackTask*>(SchedulerCallback_Create_00449ed0(reinterpret_cast<int>(&StageUpdateCallback)));
        unsigned int active_flags = task->flags & ~2u;
        task->context = context;
        task->flags = active_flags;
        Scheduler_RegisterPrimary(data_00491be4, reinterpret_cast<SchedulerTask*>(task), 10);
        context->callbacks.primary_task = reinterpret_cast<SchedulerCallback*>(task);
        task = reinterpret_cast<CallbackTask*>(SchedulerCallback_Create_00449ed0(reinterpret_cast<int>(&StageDrawCallback)));
        task->flags &= ~2u;
        task->context = context;
        Scheduler_RegisterSecondary(data_00491be4, reinterpret_cast<SchedulerTask*>(task), 4);
        context->callbacks.secondary_task = reinterpret_cast<SchedulerCallback*>(task);
    }
    memcpy(context->configuration, data_00491c28.configuration, sizeof(context->configuration));
    // The callback pair's second prefix word stores the stage kind.
    memcpy(context->callbacks.unknown_00 + sizeof(int), &data_00477848->stage_kind, sizeof(int));
    if (!(data_00474c40.flags & 2)) {
        if (!ReplayCreate(context->replay_mode, data_00477710)) goto failed;
        if (!CreateStageState(data_00477848->stage_file, 0)) goto failed;
        if (!CreateItems()) goto failed;
        if (!CreatePlayerResources()) goto failed;
        if (!CreateProjectiles()) goto failed;
        if (!CreateEffects()) goto failed;
        if (!CreateScore()) goto failed;
        if (!CreateTimerResources()) goto failed;
        if (!CreateStageTips()) goto failed;
        if (!CreateLargeResources()) goto failed;
    } else {
        reinterpret_cast<ReplayManager_0042a6a0*>(data_00477838)->BeginStage();
        SetupScoreTask(data_0047770c);
        if (!CreateStageState(data_00477848->stage_file, 0)) goto failed;
    }
    if (!(data_00474c40.flags & 9)) {
        if (!CreateEnemies(data_00477848->enemy_file)) goto failed;
    } else {
        data_00477704->Reset();
    }
    if (!CreateBulletState()) goto failed;
    if (!CreateFixedState()) goto failed;
    if (!CreatePlayer()) goto failed;
    if (!(data_00474c40.flags & 0x20)) {
        StopMusic();
        LoadMusic(0, data_00477848->music[0]);
        LoadMusic(1, data_00477848->music[1]);
    }
    data_00477708->second = data_00470b70;
    data_00477708->first = data_00470b70;
    context->clock.SetSchedulerValue(0);
    while (data_00494518)
        Sleep(16);
    if (data_00474c40.reserved_44[0])
        data_00474c40.reserved_44[2] = 0;
    data_00474c40.reserved_44[0] = 0;
    CleanupAnimations(&data_00491c28);
    context->flags &= ~4u;
    data_00474c40.flags &= ~11u;
    data_00491c28.worker_running = 0;
    data_00491c28.worker_stop_requested = 1;
    data_004918a4 = 0;
    context->callbacks.RetireCallbacks();
    return 0;
failed:
    context->flags |= 8;
    ReleaseAnimations(&data_00491c28);
    data_00491c28.worker_running = 0;
    data_00491c28.worker_stop_requested = 1;
    if (context->callbacks.primary_task)
        context->callbacks.primary_task->flags_04 |= 2;
    if (context->callbacks.secondary_task)
        context->callbacks.secondary_task->flags_04 |= 2;
    return -1;
}
#pragma code_seg()
