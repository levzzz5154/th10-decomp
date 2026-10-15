// 0x00428F60..0x0042949F: ReplayManager_004296f0::Start — the replay
// runtime's bootstrap, recovered as an equivalent C++ body (see the layout
// named in build_support/regions.json's equivalent_recoveries).
//
// Mode 0 builds the recording runtime: it publishes the manager, drops the
// current stage's old input pools, appends a fresh 0x6284-byte page,
// allocates the replay file header (magic "t10r", version 5, capacity
// 0x100), the 0x64-byte configuration block and the current stage's
// 0x1C4-byte record, fills the record from the running game state, and
// registers the three scheduler callback nodes that drive the recorder
// (input tick at priority 0x0B, frame tick at 0x1B on the primary
// scheduler, the draw-side tick at 5 on the secondary one). Mode 1 reads
// the named replay back in, restores the configuration, the generator
// seed, the score state and the stage's input list, and registers the same
// three nodes with the active stage cleared. Mode 2 only validates that
// the file loads; any other mode reports success untouched.
//
// The entry has no ordinary prototype: the factory at 0x00429610 homes the
// receiver in EBX, the mode in EAX and the path in ECX. That agreement only
// exists inside a native /LTCG link, so this body is measured with the
// replay manager start cluster's compiler context (the driver and the
// factory compiled beside it); the loader, the two pool helpers, the
// configuration defaults, the frame timer and the secondary scheduler
// registration are stand-in bodies in that context whose calls bake to the
// real retail addresses.
#include <string.h>
#include "th10/game/replay_manager_create_004296f0.hpp"
#include "th10/game/replay_stage_begin_0042a6a0.hpp"
#include "th10/game/replay_pool_append_0042aa50.hpp"
#include "th10/game/linked_pool_append.hpp"
#include "th10/game/large_initialization_state_00421f00.hpp"
#include "th10/game/score.hpp"

void* __cdecl operator new(unsigned int size);

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

// The replay file loader; compiled in the context link with the real
// loader's register convention (receiver in ESI, path pushed on the stack).
int ReplayManager_LoadFile_00428f60(ReplayManager_004296f0* manager, const char* replay_path);

// The running game's profile/front state; its +0x24 block mirrors the
// configuration block's +0x14..+0x48.
extern "C" void* g_game;

// The frame countdown timer embedded at the head of the score state: the
// retail body addresses it with the containing object's base (the timer
// fields start at +0x14).
struct EmbeddedTimerState_0042a930 {
    unsigned char unknown_00[0x14];
    int target_14;
    int current_18;
    float previous_1c;
    float* speed_20;
    unsigned int flags_24;

    __declspec(noinline) void SetCountdown(int frames);
};

// The 0x24-byte replay file header written by the recording bootstrap.
struct ReplayFileHeader_00428f60 {
    unsigned int magic;                    // +0x00: "t10r"
    unsigned short version;                // +0x04: 5
    unsigned char reserved_06[0x0A];
    unsigned int capacity;                 // +0x10: 0x100 recorded inputs
    unsigned char reserved_14[0x10];

    ReplayFileHeader_00428f60() {
        memset(this, 0, sizeof(*this));
        magic = 0x72303174;
        version = 5;
        capacity = 0x100;
    }
};
typedef char ReplayFileHeaderSize_00428f60[
    sizeof(ReplayFileHeader_00428f60) == 0x24 ? 1 : -1];

// The 0x64-byte configuration block the bootstrap allocates: the profile
// mirror at +0x14, the run setup the stage restore reads back, and the
// continues count at +0x60.
struct ReplayConfigBlock_00428f60 {
    unsigned char reserved_00[0x14];
    unsigned char profile_mirror[0x34];    // +0x14: 13 dwords from the profile
    unsigned char reserved_48[8];
    int character;                         // +0x50
    int shot_type;                         // +0x54
    int difficulty;                        // +0x58
    unsigned char reserved_5c[4];
    int continues;                         // +0x60

    ReplayConfigBlock_00428f60() {
        GameConfig_InitializeDefaults(0, (GameConfig*)((char*)this + 0x14));
        memset(this, 0, sizeof(*this));
    }
};
typedef char ReplayConfigBlockSize_00428f60[
    sizeof(ReplayConfigBlock_00428f60) == 0x64 ? 1 : -1];

// The 0x24-byte scheduler callback node. The flag word is read before it is
// written, so the heap-owned clear is a load/mask/store rather than a single
// memory read-modify-write; the barrier keeps the mask next to its store
// instead of letting the scheduler hoist it onto the load.
struct SchedulerCallbackTask_00428f60 {
    int priority;                          // +0x00
    unsigned int flags;                    // +0x04, bit 0 = heap owned
    void* on_tick;                         // +0x08
    void* on_register;                     // +0x0C
    void* on_remove;                       // +0x10
    void* link_task;                       // +0x14
    void* link_next;                       // +0x18
    void* link_previous;                   // +0x1C
    void* context;                         // +0x20

    SchedulerCallbackTask_00428f60();
};

typedef char SchedulerCallbackTaskSize_00428f60[
    sizeof(SchedulerCallbackTask_00428f60) == 0x24 ? 1 : -1];

inline SchedulerCallbackTask_00428f60::SchedulerCallbackTask_00428f60() {
    unsigned int previous = flags;
    on_tick = 0;
    on_register = 0;
    on_remove = 0;
    priority = 0;
    _ReadWriteBarrier();
    flags = previous & ~1u;
    link_task = this;
    link_next = 0;
    link_previous = 0;
}

// Both callback nodes of each mode are built by the same sequence: construct,
// publish the callback and the context, and force bit 0 on with bit 1 off.
static __forceinline SchedulerCallbackTask_00428f60* BuildCallbackNode_00428f60(
        void* callback, ReplayManager_004296f0* manager) {
    SchedulerCallbackTask_00428f60* node = new SchedulerCallbackTask_00428f60;
    unsigned int flags = node->flags;
    node->on_tick = callback;
    node->on_register = 0;
    node->on_remove = 0;
    node->context = manager;
    node->flags = (flags & ~2u) | 1u;
    return node;
}

#pragma code_seg(".text$00428f60_fn")
__declspec(noinline) int ReplayManager_004296f0::Start(int start_mode, const char* replay_path) {
    mode = start_mode;
    if (start_mode == 0) {
        // Recording: publish the manager, drop the stage's old pools, append
        // a fresh page, then build header, configuration and stage record.
        int stage = data_00474c40.stage;
        data_00477838 = this;
        ClearStage(stage);
        current_pool = (ReplayPoolLink_0042aa50*)((PoolOwner_0042aa50*)this)->AppendPage(data_00474c40.stage);

        ReplayFileHeader_00428f60* file_header = new ReplayFileHeader_00428f60;
        header = (ReplayHeader_004296f0*)file_header;

        ReplayConfigBlock_00428f60* config = new ReplayConfigBlock_00428f60;
        summary = (ReplaySummary_004296f0*)config;

        ReplayStage_0042a6a0* stage_record = new ReplayStage_0042a6a0;
        stage_data[data_00474c40.stage] = (ReplayStageData_004296f0*)stage_record;
        stage_record = (ReplayStage_0042a6a0*)stage_data[data_00474c40.stage];

        ((ReplayConfigBlock_00428f60*)summary)->character = data_00474c40.character;
        ((ReplayConfigBlock_00428f60*)summary)->shot_type = data_00474c40.shot_type;
        ((ReplayConfigBlock_00428f60*)summary)->difficulty = data_00474c40.difficulty;
        if (g_game)
            memcpy(((ReplayConfigBlock_00428f60*)summary)->profile_mirror,
                   (char*)g_game + 0x24, 0x34);

        // The flag word's heap-owned bit follows the configuration word's low
        // bit, and the boss-gauge counters only clear while the configuration
        // word is set. The barriers keep each store next to its load the way
        // retail schedules them, and the gauge test re-reads the configuration
        // word through its retail address so the compare is a fresh memory
        // read (the parity line above consumed the loaded copy).
        stage_record->stage = (short)data_00474c40.stage;
        _ReadWriteBarrier();
        stage_record->seed = data_004918b0.seed;
        _ReadWriteBarrier();
        int config_word = data_00491fc4;
        data_004918b0.generation = 0;
        _ReadWriteBarrier();
        stage_record->flag = stage_record->flag ^ ((stage_record->flag ^ config_word) & 1);
        _ReadWriteBarrier();
        if (*(int *)0x00491FC4 != 0) {  // fresh read; see the note above
            stage_record->player_position.x = 0;
            stage_record->player_position.y = 0;
        }
        stage_record->score = data_00474c40.score;
        stage_record->word_10 = data_00474c40.word_08;
        stage_record->gauge = data_00474c40.gauge;
        stage_record->gauge_frame = data_00474c40.gauge_timer.current;
        stage_record->field_1c = data_00474c40.field_30;
        stage_record->field_20 = data_00474c40.field_58;
        stage_record->continues = data_00474c40.continues;
        ((ReplayConfigBlock_00428f60*)summary)->continues = data_00474c40.continues;

        SchedulerTask* update =
            (SchedulerTask*)BuildCallbackNode_00428f60((void*)0x0042A3D0, this);
        FuncCtrl_RegisterPrimary((FuncCtrl*)g_func_ctrl, update, 0x0B);
        update_task = update;

        SchedulerTask* trailing =
            (SchedulerTask*)BuildCallbackNode_00428f60((void*)0x0042A3E0, this);
        FuncCtrl_RegisterPrimary((FuncCtrl*)g_func_ctrl, trailing, 0x1B);
        trailing_task = trailing;

        SchedulerTask* draw =
            (SchedulerTask*)BuildCallbackNode_00428f60((void*)0x0042A430, this);
        FuncCtrl_RegisterSecondary((FuncCtrl*)g_func_ctrl, draw, 5);
        draw_task = draw;

        reserved_1d0 = (unsigned int)data_00474c40.stage;
        return 0;
    }
    if (start_mode == 1) {
        // Play back: load the file, mirror the configuration back into the
        // profile, rewind the stage's input list and restore the run state.
        data_00477838 = this;
        if (ReplayManager_LoadFile_00428f60(this, replay_path))
            return -1;

        memcpy((char*)g_game + 0x24, (char*)summary + 0x14, 0x34);

        // Each node is nine dwords. The rewind goes through the dword view of
        // the node array: retail addresses the cursor and count stores through
        // the scaled stage index (ebx+edx*4+disp) and only materialises the
        // node pointer for the cursor_end pair, so the array view keeps that
        // shape (the layout records the two stores' refolded encodings).
        const int stage = data_00474c40.stage;
        unsigned int (*node_view)[9] = (unsigned int (*)[9])nodes;
        node_view[stage][1] = node_view[stage][0];
        ReplayStage_0042a6a0* stage_record =
            (ReplayStage_0042a6a0*)node_view[stage][4];
        node_view[stage][5] = 0;
        ReplayNode_0042a6a0* current = (ReplayNode_0042a6a0*)(node_view + stage);
        current->cursor_end = current->inputs_end;

        data_00474c40.character = ((ReplayConfigBlock_00428f60*)summary)->character;
        data_00474c40.shot_type = ((ReplayConfigBlock_00428f60*)summary)->shot_type;
        data_00474c40.difficulty = ((ReplayConfigBlock_00428f60*)summary)->difficulty;

        data_004918b0.seed = stage_record->seed;
        _ReadWriteBarrier();
        data_004918b0.generation = 0;
        _ReadWriteBarrier();
        data_00474c40.score = stage_record->score;
        data_00474c40.word_08 = stage_record->word_10;
        ((ScoreState*)0x00474C40)->SetGauge(stage_record->gauge * 10);
        ((EmbeddedTimerState_0042a930*)0x00474C40)->SetCountdown(stage_record->gauge_frame);
        data_00474c40.field_30 = stage_record->field_1c;
        data_00474c40.field_58 = stage_record->field_20;
        data_00474c40.continues = stage_record->continues;
        data_00474c40.field_5c =
            ((ReplayNode_0042a6a0*)nodes)[data_00474c40.stage].stage->field_1b8;

        SchedulerTask* update =
            (SchedulerTask*)BuildCallbackNode_00428f60((void*)0x0042A3D0, this);
        FuncCtrl_RegisterPrimary((FuncCtrl*)g_func_ctrl, update, 0x0B);
        update_task = update;

        SchedulerTask* trailing =
            (SchedulerTask*)BuildCallbackNode_00428f60((void*)0x0042A3E0, this);
        FuncCtrl_RegisterPrimary((FuncCtrl*)g_func_ctrl, trailing, 0x1B);
        trailing_task = trailing;

        SchedulerTask* draw =
            (SchedulerTask*)BuildCallbackNode_00428f60((void*)0x0042A430, this);
        FuncCtrl_RegisterSecondary((FuncCtrl*)g_func_ctrl, draw, 5);
        draw_task = draw;

        reserved_1d0 = 0xFFFFFFFFu;
        return 0;
    }
    if (start_mode == 2) {
        // Validate: the file only has to load.
        if (ReplayManager_LoadFile_00428f60(this, replay_path))
            return -1;
    }
    return 0;
}
#pragma code_seg()
