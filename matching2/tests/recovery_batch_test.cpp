// Host-side tests for the July recovery batch:
//   0x00442FE0  AnimationManager_AppendQuadVertices
//   0x0044DBF0  ArchiveCursor_Open
//   0x00418B80  ScoreGauge_SetTargetTenthAndDisableTimer
//   0x00418A90  Score_IncrementCounterClampedNine
//   0x00418C40  GameConfig_InitializeDefaults
//   0x00418D40  StageTipManager_Construct
//   0x0041A120  StageTip_Create
//   0x0043CC40  Platform_StopSoundWorkers

#include "th10/game/archive_cursor_open.hpp"
#include "th10/game/game_config_defaults.hpp"
#include "th10/game/score_timer_leaves.hpp"
#include "th10/game/stage_tips.hpp"
#include "th10/platform/sound_worker.hpp"
#include "th10/render/quad_vertex_append.hpp"

#include <cassert>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include "th10/game/scheduler.hpp"
// Scheduler and difficulty globals reached by the runtime initializers in the
// TUs this test links. The PE32 build resolves them through the retail .data
// aliasing and the real scheduler; the host test build supplies inert storage.
unsigned int DAT_00491be4;
unsigned char DAT_00491d6a;
static SchedulerCallback g_test_callbacks[16];
static int g_test_callback_count;
SchedulerCallback* SchedulerCallback_Create(SchedulerFunction function) {
    if (g_test_callback_count >= 16) return 0;
    SchedulerCallback* c = &g_test_callbacks[g_test_callback_count++];
    *c = SchedulerCallback{}; c->function = function; return c;
}
int Scheduler_RegisterPrimary(SchedulerCallback*, int, void*) { return 0; }
int Scheduler_RegisterSecondary(SchedulerCallback*, int, void*) { return 0; }
void Scheduler_Remove(SchedulerCallback*, void*) {}

// ---------------------------------------------------------------------------
// Retail globals referenced by the reconstructions.

float DAT_00476f78 = 1.0f;      // default timer speed sentinel
int32_t DAT_00474c7c = 0;       // difficulty setting
int32_t DAT_00474c84 = 0;       // tip display mode
int32_t DAT_00474c88 = 111;     // display value while mode == 0
int32_t DAT_00474c8c = 222;     // display value while mode != 0
uint32_t DAT_00474e88 = 0x11111111u;
uint32_t DAT_00474e8c = 0x22222222u;
uint32_t DAT_00474e90 = 0x33333333u;
uint32_t DAT_00474e94 = 0x44444444u;
uint16_t DAT_00474e98 = 0x5555u;
extern StageTipManager* DAT_00477814;  // defined in stage_tip_manager.cpp

extern "C" {
int32_t DAT_004977a4 = 0;  // shared archive header offset
}

// ---------------------------------------------------------------------------
// Win32 stubs for the archive-cursor open path.

namespace {

struct CreateFileCall {
    const char* path;
    uint32_t access;
    uint32_t share;
    uint32_t disposition;
    uint32_t flags;
    int count;
};

CreateFileCall g_create_file_call;
void* g_create_file_result;
void* g_seek_handle;
int g_seek_offset;
int g_seek_count;

}  // namespace

extern "C" {

void* CreateFileA(const char* path, uint32_t access, uint32_t share,
                  void* security, uint32_t disposition, uint32_t flags,
                  void* template_file) {
    assert(security == 0 && template_file == 0);
    g_create_file_call.path = path;
    g_create_file_call.access = access;
    g_create_file_call.share = share;
    g_create_file_call.disposition = disposition;
    g_create_file_call.flags = flags;
    ++g_create_file_call.count;
    return g_create_file_result;
}

int SetFilePointer(void* handle, int distance, long* distance_high,
                   int method) {
    assert(distance_high == 0 && method == 0);
    g_seek_handle = handle;
    g_seek_offset = distance;
    ++g_seek_count;
    return 0;
}

}  // extern "C"

// ---------------------------------------------------------------------------
// 0x00442FE0 - quad staging append.

static void TestQuadVertexAppend() {
    QuadRenderVertex source[4];
    for (unsigned int vertex = 0; vertex < 4; ++vertex) {
        for (unsigned int word = 0; word < 7; ++word) {
            source[vertex].words[word] = vertex * 0x100u + word;
        }
    }
    QuadRenderVertex buffer[8];
    memset(buffer, 0xEE, sizeof(buffer));
    QuadVertexStaging staging;
    staging.cursor = buffer;
    staging.quad_count = 41;

    const unsigned int result =
        AnimationManager_AppendQuadVertices(&staging, source);
    assert(result == 0);

    const int expected_order[6] = {0, 1, 2, 1, 2, 3};
    for (int slot = 0; slot < 6; ++slot) {
        assert(memcmp(&buffer[slot], &source[expected_order[slot]],
                      sizeof(QuadRenderVertex)) == 0);
    }
    // One 28-byte vertex beyond the six written slots stays untouched.
    for (unsigned int word = 0; word < 7; ++word) {
        assert(buffer[6].words[word] == 0xEEEEEEEEu);
    }
    assert(staging.cursor == buffer + 6);
    assert(staging.quad_count == 42);
}

// ---------------------------------------------------------------------------
// 0x0044DBF0 - archive cursor open.

namespace {

struct OpenCursorFixture {
    uint8_t bytes[0x98];

    int32_t& bytes_remaining() { return *reinterpret_cast<int32_t*>(bytes + 0x08); }
    int32_t& remaining_copy()  { return *reinterpret_cast<int32_t*>(bytes + 0x2c); }
    int32_t& stored_mode()     { return *reinterpret_cast<int32_t*>(bytes + 0x78); }
    int32_t& mode_flag()       { return *reinterpret_cast<int32_t*>(bytes + 0x7c); }
    uint32_t& file_handle32()  { return *reinterpret_cast<uint32_t*>(bytes + 0x8c); }
};

struct OpenSectionFixture {
    int32_t pad_00[4];
    int32_t base_offset;
    int32_t pad_14;
    int32_t write_offset;
    int32_t section_length;
};

}  // namespace

static void TestArchiveCursorOpenIgnoresOtherModes() {
    OpenCursorFixture cursor;
    memset(cursor.bytes, 0xAB, sizeof(cursor.bytes));
    g_create_file_call.count = 0;

    const uint32_t result = ArchiveCursor_Open(cursor.bytes, 2, "unused", 0);
    assert(result == 0);
    assert(cursor.stored_mode() == 2);
    assert(cursor.mode_flag() == 0);
    assert(g_create_file_call.count == 0);
}

static void TestArchiveCursorOpenRejectsNullPath() {
    OpenCursorFixture cursor;
    memset(cursor.bytes, 0, sizeof(cursor.bytes));
    g_create_file_call.count = 0;

    const uint32_t result = ArchiveCursor_Open(cursor.bytes, 1, 0, 0);
    assert(result == 0x80070057u);
    assert(cursor.stored_mode() == 1);
    assert(g_create_file_call.count == 0);
}

static void TestArchiveCursorOpenReportsFailedOpen() {
    OpenCursorFixture cursor;
    memset(cursor.bytes, 0, sizeof(cursor.bytes));
    g_create_file_call.count = 0;
    g_create_file_result = reinterpret_cast<void*>(~static_cast<uintptr_t>(0));

    const uint32_t result = ArchiveCursor_Open(cursor.bytes, 1, "th10.dat", 0);
    assert(result == 0x80004005u);
    assert(g_create_file_call.count == 1);
    assert(g_create_file_call.access == 0x80000000u);
    assert(g_create_file_call.share == 1u);
    assert(g_create_file_call.disposition == 3u);
    assert(g_create_file_call.flags == 0x8000080u);
}

static void TestArchiveCursorOpenSeeksToSectionBase() {
    OpenCursorFixture cursor;
    memset(cursor.bytes, 0, sizeof(cursor.bytes));
    OpenSectionFixture section;
    memset(&section, 0, sizeof(section));
    section.base_offset = 0x1000;
    section.section_length = 0x420;

    g_create_file_call.count = 0;
    g_create_file_result = reinterpret_cast<void*>(0x1234);
    g_seek_count = 0;
    DAT_004977a4 = 0x10;

    const uint32_t result =
        ArchiveCursor_Open(cursor.bytes, 1, "th10.dat", &section);
    assert(result == 0);
    assert(cursor.stored_mode() == 1);
    assert(cursor.mode_flag() == 0);
    assert(g_create_file_call.count == 1);
    assert(strcmp(g_create_file_call.path, "th10.dat") == 0);
    assert(cursor.file_handle32() == 0x1234u);
    assert(g_seek_count == 1);
    assert(g_seek_handle == reinterpret_cast<void*>(0x1234));
    assert(g_seek_offset == 0x1000 + 0x10);
    assert(cursor.bytes_remaining() == 0x420);
    assert(cursor.remaining_copy() == 0x420);
    DAT_004977a4 = 0;
}

// ---------------------------------------------------------------------------
// 0x00418B80 / 0x00418A90 - score timer leaves.

static void TestScoreGaugeSetTargetTenth() {
    ScoreGaugeTimedValue state;
    memset(&state, 0, sizeof(state));

    ScoreGauge_SetTargetTenthAndDisableTimer(&state, 1234);
    assert(state.target_tenth == 123);
    assert((state.timer.flags & 1u) != 0);
    assert(state.timer.speed == &DAT_00476f78);
    assert(state.timer.current == 0);
    assert(state.timer.previous == 0);
    assert(state.timer.target == -1);

    // Post-init call: fields reset without re-running the sentinel setup.
    state.timer.current = 5;
    state.timer.previous = 7;
    state.timer.target = 55;
    float other_speed = 2.0f;
    state.timer.speed = &other_speed;
    ScoreGauge_SetTargetTenthAndDisableTimer(&state, -50);
    assert(state.target_tenth == -5);
    assert(state.timer.current == 0);
    assert(state.timer.previous == 0);
    assert(state.timer.target == -1);
    assert(state.timer.speed == &other_speed);
}

static void TestScoreIncrementClamped() {
    int counter = 0;
    Score_IncrementCounterClampedNine(&counter);
    assert(counter == 1);
    counter = 8;
    Score_IncrementCounterClampedNine(&counter);
    assert(counter == 9);
    Score_IncrementCounterClampedNine(&counter);
    assert(counter == 9);
}

// ---------------------------------------------------------------------------
// 0x00418C40 - configuration defaults.

static void TestGameConfigDefaults() {
    GameConfigRecord config;
    memset(&config, 0xFF, sizeof(config));

    GameConfig_InitializeDefaults(&config);
    assert(config.signature == 0x00100003u);
    assert(config.preset_words[0] == 0x11111111u);
    assert(config.preset_words[1] == 0x22222222u);
    assert(config.preset_words[2] == 0x33333333u);
    assert(config.preset_words[3] == 0x44444444u);
    assert(config.preset_half == 0x5555u);
    assert(config.threshold_16 == 600);
    assert(config.threshold_18 == 600);
    assert(config.byte_1a == 0);
    assert(config.flag_1b == 1);
    assert(config.flag_1c == 1);
    assert(config.byte_1d == 0);
    assert(config.byte_1e == 0);
    assert(config.mode_1f == 2);
    assert(config.volume_20 == 100);
    assert(config.volume_21 == 0x50);
    assert(config.byte_22 == 0);
    for (unsigned int index = 0; index < sizeof(config.reserved_23); ++index) {
        assert(config.reserved_23[index] == 0);
    }
    assert(config.flags_30 == 0x100u);
}

// ---------------------------------------------------------------------------
// 0x00418D40 / 0x0041A120 - stage-tip manager and tip creation.

namespace {

unsigned char g_tip_storage[2][0x100];
int g_tip_allocations;

void* AllocateTip(uint32_t size) {
    assert(size == 0x88);
    assert(g_tip_allocations < 2);
    return g_tip_storage[g_tip_allocations++];
}

}  // namespace

static void TestStageTipManagerConstruct() {
    StageTipManager manager;
    memset(&manager, 0xCD, sizeof(manager));
    DAT_00477814 = 0;

    StageTipManager* result = StageTipManager_Construct(&manager);
    assert(result == &manager);
    assert(DAT_00477814 == &manager);
    assert(manager.flags == 2u);
    for (int index = 0; index < 16; ++index) {
        assert(manager.lists[index].owner == (StageTip*)&manager);
        assert(manager.lists[index].next == 0);
        assert(manager.lists[index].previous == 0);
    }
    for (unsigned int index = 0; index < 5; ++index) {
        assert(manager.reserved_04[index] == 0);
    }
    for (unsigned int index = 0; index < 0x34; ++index) {
        assert(manager.reserved_D8[index] == 0);
    }
}

static void TestStageTipCreate() {
    StageTipManager manager;
    StageTipManager_Construct(&manager);
    g_tip_allocations = 0;

    DAT_00474c7c = 2;   // difficulty -> sentinel 10
    DAT_00474c84 = 0;   // mode 0 -> DAT_00474c88
    const float first_position[3] = {1.5f, -2.5f, 3.0f};

    StageTip* first =
        StageTip_Create(&manager, first_position, "MARISA STOLE THE", AllocateTip);
    assert(first == (StageTip*)g_tip_storage[0]);
    assert(manager.lists[10].next == &first->node);
    assert(first->node.previous == &manager.lists[10]);
    assert(first->node.next == 0);
    assert(first->node.owner == first);
    assert(first->x == 1.5f && first->y == -2.5f && first->z == 3.0f);
    assert(strcmp(first->name, "MARISA STOLE THE") == 0);
    assert(first->duration == 300);
    assert(first->selection == 0x1E);
    assert(first->scale == 1.0f);
    assert(first->state == -1);
    assert(first->display_zero == 0);
    assert(first->display_mode == 0);
    assert(first->display_value == 111);
    // Untouched difficulty chains stay empty.
    assert(manager.lists[8].next == 0 && manager.lists[11].next == 0);

    // Second tip appends at the tail; nonzero mode selects the other value.
    DAT_00474c84 = 7;
    const float second_position[3] = {0.0f, 0.0f, 0.0f};
    char long_text[0x50];
    memset(long_text, 'A', sizeof(long_text));
    long_text[sizeof(long_text) - 1] = 0;

    StageTip* second =
        StageTip_Create(&manager, second_position, long_text, AllocateTip);
    assert(second == (StageTip*)g_tip_storage[1]);
    assert(first->node.next == &second->node);
    assert(second->node.previous == &first->node);
    assert(second->node.next == 0);
    assert(second->display_mode == 7);
    assert(second->display_value == 222);
    // The 0x40-byte text copy truncates without a forced terminator.
    for (int index = 0; index < 0x40; ++index) {
        assert(second->name[index] == 'A');
    }

    // Allocation failure returns null and leaves the chain untouched.
    StageTip* failed = StageTip_Create(&manager, first_position, "x", 0);
    assert(failed == 0);
    assert(second->node.next == 0);

    DAT_00474c7c = 0;
    DAT_00474c84 = 0;
}

// ---------------------------------------------------------------------------
// 0x0043CC40 - sound worker shutdown.

namespace {

int g_wait_calls;
int g_sleep_calls;
int g_close_calls;
void* g_closed_handles[2];
int g_timeouts_remaining;

unsigned int WaitStub(void* handle, unsigned int milliseconds) {
    assert(handle != 0);
    assert(milliseconds == 100);
    ++g_wait_calls;
    if (g_timeouts_remaining > 0) {
        --g_timeouts_remaining;
        return 0x102u;
    }
    return 0;
}

void SleepStub(unsigned int milliseconds) {
    assert(milliseconds == 1);
    ++g_sleep_calls;
}

void CloseStub(void* handle) {
    assert(g_close_calls < 2);
    g_closed_handles[g_close_calls++] = handle;
}

}  // namespace

static void TestSoundWorkerShutdown() {
    SoundWorkerState state;
    state.worker_thread = reinterpret_cast<void*>(0x1111);
    state.companion_thread = reinterpret_cast<void*>(0x2222);
    state.reserved_5220 = 0xDEAD;
    state.stop_requested = 0;

    g_wait_calls = 0;
    g_sleep_calls = 0;
    g_close_calls = 0;
    g_timeouts_remaining = 3;  // three timeout polls before signaled

    const unsigned int result =
        Platform_StopSoundWorkers(&state, WaitStub, SleepStub, CloseStub);
    assert(result == 0);
    assert(state.stop_requested == 1);
    // 3 timeouts + 2 signaled completions.
    assert(g_wait_calls == 5);
    assert(g_sleep_calls == 3);
    assert(g_close_calls == 2);
    assert(g_closed_handles[0] == reinterpret_cast<void*>(0x1111));
    assert(g_closed_handles[1] == reinterpret_cast<void*>(0x2222));
    assert(state.worker_thread == 0);
    assert(state.companion_thread == 0);
    assert(state.reserved_5220 == 0xDEAD);

    // A cleared primary handle is a no-op.
    g_wait_calls = 0;
    g_close_calls = 0;
    state.stop_requested = 0;
    const unsigned int noop =
        Platform_StopSoundWorkers(&state, WaitStub, SleepStub, CloseStub);
    assert(noop == 0);
    assert(state.stop_requested == 0);
    assert(g_wait_calls == 0);
    assert(g_close_calls == 0);
}

// ---------------------------------------------------------------------------

int main() {
    TestQuadVertexAppend();
    TestArchiveCursorOpenIgnoresOtherModes();
    TestArchiveCursorOpenRejectsNullPath();
    TestArchiveCursorOpenReportsFailedOpen();
    TestArchiveCursorOpenSeeksToSectionBase();
    TestScoreGaugeSetTargetTenth();
    TestScoreIncrementClamped();
    TestGameConfigDefaults();
    TestStageTipManagerConstruct();
    TestStageTipCreate();
    TestSoundWorkerShutdown();
    printf("recovery_batch_test: all tests passed\n");
    return 0;
}
