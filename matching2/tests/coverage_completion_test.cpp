#include "th10/app/main_tasks.hpp"
#include "th10/game/manager_factories.hpp"
#include "th10/game/message_manager_init.hpp"
#include "th10/game/stage_tips.hpp"
#include "th10/platform/midi_sequencer.hpp"
#include "th10/render/anm_distance_color.hpp"

#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <cstring>

// Retail globals consumed by the linked manager/scheduler/entity sources.
uint32_t DAT_00491be4 = 0;
uint32_t DAT_004776f4 = 0;
uint32_t DAT_0047770c = 0;
uint32_t DAT_00492274 = 0;
unsigned char DAT_0049231c = 0;
float DAT_00470b04 = 0.0f;
float DAT_00470b0c = 1.0f;
float DAT_00470b38 = 448.0f;
float DAT_00470b3c = 192.0f;
float DAT_00470b40 = -192.0f;
float DAT_00470b5c = 384.0f;

extern "C" void* operator_new(uint32_t size) {
    return std::malloc(size);
}
extern "C" void _free(void* memory) {
    std::free(memory);
}
extern "C" void __stdcall EnterCriticalSection(void*) {}
extern "C" void __stdcall LeaveCriticalSection(void*) {}

namespace {

int calls[4];
int call_count;
int busy;
int mode_result;

void Advance(void*) { calls[call_count++] = 1; }
void Poll(void*) { calls[call_count++] = 2; }
int Busy(void*) {
    calls[call_count++] = 3;
    return busy;
}
int Apply(void*) {
    calls[call_count++] = 4;
    return mode_result;
}

void ResetCalls() {
    std::memset(calls, 0, sizeof(calls));
    call_count = 0;
}

void TestMainInputTask() {
    int mode = 0;
    MainInputTaskHooks hooks = {
        nullptr, &mode, Advance, Poll, Busy, Apply,
    };
    MainInputTaskState state = {-1, nullptr, 0};
    mode_result = 7;
    ResetCalls();
    assert(MainInputTask_Run(&state, &hooks) == 7);
    assert(mode == 3);
    assert(call_count == 4);
    assert(calls[0] == 1 && calls[1] == 2 &&
           calls[2] == 3 && calls[3] == 4);

    state.replay_handle = &state;
    mode = 9;
    busy = 1;
    ResetCalls();
    assert(MainInputTask_Run(&state, &hooks) == 4);
    assert(mode == 9 && call_count == 3);

    busy = 0;
    state.callback_result = 2;
    ResetCalls();
    assert(MainInputTask_Run(&state, &hooks) == 4);
    assert(call_count == 3);
    state.callback_result = 5;
    assert(MainInputTask_Run(&state, &hooks) == 1);
}

void TestStageTipInitialize() {
    StageTip tip;
    std::memset(&tip, 0xA5, sizeof(tip));
    assert(StageTip_Initialize(nullptr, &tip) == &tip);
    assert(tip.x == 0.0f && tip.y == 0.0f && tip.z == 0.0f);
    assert(tip.node.owner == &tip);
    assert(tip.node.next == nullptr && tip.node.previous == nullptr);
    assert(tip.duration == 300);
    assert(tip.selection == -1);
    assert(tip.scale == 1.0f);
    assert(tip.state == -1);
    assert(tip.name[0] == '\0');
}

int update_kind;
int draw_kind;
int update_priority;
void* seen_queue;
void* seen_owner;
void* finished_task;

void* CreateUpdate(void*, int kind, int priority, void* owner) {
    update_kind = kind;
    update_priority = priority;
    seen_owner = owner;
    return reinterpret_cast<void*>(0x10);
}
void* CreateDraw(void*, int kind, void* queue, void* owner) {
    draw_kind = kind;
    seen_queue = queue;
    seen_owner = owner;
    return reinterpret_cast<void*>(0x20);
}
void SetFinish(void*, void* task) { finished_task = task; }

void TestAsciiManagerInitialize() {
    const int expected_update[9] = {
        kAsciiUpdateBasic, kAsciiUpdateMode1, kAsciiUpdateMode2,
        kAsciiUpdateBasic, kAsciiUpdateMode4, kAsciiUpdateMode2,
        kAsciiUpdateMode6, kAsciiUpdateMode6, kAsciiUpdateMode8,
    };
    const int expected_draw[9] = {
        kAsciiDrawMode0, -1, kAsciiDrawMode2, kAsciiDrawMode2,
        kAsciiDrawMode4, kAsciiDrawMode0, kAsciiDrawMode6,
        kAsciiDrawMode7, -1,
    };
    const float speed = 1.0f;
    AsciiManagerInitHooks hooks = {
        nullptr, &speed, CreateUpdate, CreateDraw, SetFinish,
    };
    for (int mode = 0; mode < 9; ++mode) {
        AsciiManagerInitState state = {};
        update_kind = draw_kind = -1;
        seen_queue = seen_owner = finished_task = nullptr;
        void* queue = reinterpret_cast<void*>(0x30);
        assert(AsciiManager_Initialize(
                   &state, queue, mode, 41, 42, 43, 44, &hooks) == 43);
        assert(update_kind == expected_update[mode]);
        assert(update_priority == 14);
        assert(draw_kind == expected_draw[mode]);
        assert(state.update_task == reinterpret_cast<void*>(0x10));
        assert(state.draw_task ==
               (expected_draw[mode] < 0 ? nullptr
                                        : reinterpret_cast<void*>(0x20)));
        assert(seen_owner == &state);
        if (expected_draw[mode] >= 0)
            assert(seen_queue == queue);
        assert(finished_task == state.update_task);
        assert(state.mode == mode && state.argument_4 == 41);
        assert(state.argument_5 == 42 && state.argument_6 == 43);
        assert(state.argument_7 == 44);
        assert(state.timer_target == -1);
        assert(state.timer_current == 0 && state.timer_previous == 0);
        assert(state.timer_speed == &speed);
        assert((state.timer_flags & 1u) != 0);
        assert(state.color == (mode == 3 ? 255 : 0));
    }
    AsciiManagerInitState state = {};
    assert(AsciiManager_Initialize(
               &state, nullptr, 9, 0, 0, 0, 0, &hooks) == -1);
}

int midi_allocations;
int midi_releases;
void* MidiAllocate(void*, uint32_t size) {
    ++midi_allocations;
    return std::malloc(size == 0 ? 1 : size);
}
void MidiRelease(void*, void* memory) {
    ++midi_releases;
    std::free(memory);
}

void TestMidiFileLoad() {
    const uint8_t image[] = {
        'M', 'T', 'h', 'd', 0, 0, 0, 6, 0, 1, 0, 2, 0x01, 0xE0,
        'M', 'T', 'r', 'k', 0, 0, 0, 4, 0, 0x90, 60, 64,
        'M', 'T', 'r', 'k', 0, 0, 0, 3, 0, 0xFF, 0x2F,
    };
    MidiFileState state = {};
    MidiFileMemory memory = {nullptr, MidiAllocate, MidiRelease};
    midi_allocations = midi_releases = 0;
    assert(MidiFile_Load(
               &state, image, sizeof(image), 7, &memory) == 0);
    assert(state.format == 1 && state.track_count == 2);
    assert(state.division == 0x1E0);
    assert(state.source_slot == 7);
    assert(state.tempo_microseconds == 1000000);
    assert(state.tracks[0].active == 1 &&
           state.tracks[0].data_size == 4);
    assert(state.tracks[1].data_size == 3);
    assert(std::memcmp(state.tracks[0].data, image + 22, 4) == 0);
    assert(std::memcmp(state.tracks[1].data, image + 34, 3) == 0);

    // Reload first releases both payloads and the table. A truncated second
    // image then leaves the state empty.
    assert(MidiFile_Load(
               &state, image, sizeof(image) - 1, 8, &memory) == -1);
    assert(state.tracks == nullptr && state.track_count == 0);
    assert(midi_releases == midi_allocations);
    const uint8_t bad_header[14] = {};
    assert(MidiFile_Load(
               &state, bad_header, sizeof(bad_header), 0, &memory) == -1);
}

int midi_events;
int midi_volume_updates;
int midi_rewinds;
void ProcessMidiEvent(void*, MidiPlaybackState*, MidiPlaybackTrack* track) {
    ++midi_events;
    track->next_event_time += 5;
    if (midi_events == 3)
        track->active = 0;
}
void ApplyMidiVolumes(void*, int delta) {
    assert(delta == 0);
    ++midi_volume_updates;
}
void RewindMidi(void*, MidiPlaybackState* state) {
    ++midi_rewinds;
    state->tick = 0;
}

void TestMidiPlaybackTick() {
    MidiPlaybackTrack tracks[2] = {};
    tracks[0].active = 1;
    tracks[0].next_event_time = 0;
    MidiPlaybackState state = {};
    state.track_count = 2;
    state.tracks = tracks;
    state.time_numerator = 1;
    state.time_divisor = 1;
    state.fade_active = 1;
    state.fade_duration = 4;
    state.fade_position = 1;
    state.fade_volume_step = 128;
    MidiPlaybackHooks hooks = {
        nullptr, ProcessMidiEvent, ApplyMidiVolumes, RewindMidi,
    };
    midi_events = midi_volume_updates = midi_rewinds = 0;
    assert(MidiPlayback_Tick(&state, &hooks) == 1);
    assert(midi_events == 1);
    assert(state.tick == 1);
    assert(state.fade_position == 2);
    assert(state.fade_volume_step == 96);
    assert(midi_volume_updates == 1);

    // At tick 1 the time is 1000, so the active track drains until the hook
    // retires it. The following frame observes no active tracks and rewinds.
    assert(MidiPlayback_Tick(&state, &hooks) == 1);
    assert(midi_events == 3 && tracks[0].active == 0);
    assert(MidiPlayback_Tick(&state, &hooks) == 0);
    assert(midi_rewinds == 1 && state.tick == 0);

    state.fade_position = state.fade_duration;
    state.tick = 9;
    assert(MidiPlayback_Tick(&state, &hooks) == 4);
    assert(state.fade_volume == 0.0f);
    assert(state.tick == 9);
}

int anm_draw_calls;
int ValidateAnm(void*, const AnmVmState*) { return 0; }
int RejectAnm(void*, const AnmVmState*) { return 1; }
int DrawAnm(void*, const AnmVmState*, int mode) {
    assert(mode == 2);
    ++anm_draw_calls;
    return 17;
}

void TestAnmDistanceColor() {
    AnmVmState vm = {};
    vm.color[0] = 40;
    vm.color[1] = 80;
    vm.color[2] = 120;
    vm.color[3] = 200;
    vm.color2[0] = 10;
    vm.color2[1] = 20;
    vm.color2[2] = 30;
    vm.color2[3] = 40;
    uint32_t output[4] = {};
    AnmDistanceColorEnv env = {};
    env.near_distance = 5.0f;
    env.far_distance = 15.0f;
    env.far_color = 0xFF000000u;
    env.output_colors = output;
    env.validate = ValidateAnm;
    env.draw = DrawAnm;
    anm_draw_calls = 0;
    assert(AnmVm_DrawDistanceColored(&vm, &env) == 17);
    for (uint32_t value : output)
        assert(value == 0xC8785028u);
    assert(anm_draw_calls == 1);

    // Alternate color, per-channel tint, and halfway distance fade.
    vm.flags = 0x8000;
    vm.position[0] = 10.0f;
    env.tint_enabled = 1;
    env.tint[0] = 128;
    env.tint[1] = 64;
    env.tint[2] = 128;
    env.tint[3] = 128;
    assert(AnmVm_DrawDistanceColored(&vm, &env) == 17);
    // tinted BGRA = 10,10,30,40; halfway toward black and alpha zero:
    // BGR = 5,5,15 and alpha = 20.
    for (uint32_t value : output)
        assert(value == 0x140F0505u);

    vm.position[0] = 15.0f;
    assert(AnmVm_DrawDistanceColored(&vm, &env) == -1);
    env.validate = RejectAnm;
    vm.position[0] = 0.0f;
    assert(AnmVm_DrawDistanceColored(&vm, &env) == -1);
}

int message_task_kind[2];
int message_task_priority[2];
int message_task_count;
int message_indicator_calls;
int message_missing_calls;
const char* loaded_message_path;
void* MessageTask(void*, int kind, int priority, void* owner) {
    assert(owner != nullptr);
    message_task_kind[message_task_count] = kind;
    message_task_priority[message_task_count++] = priority;
    return reinterpret_cast<void*>(
        static_cast<uintptr_t>(message_task_count));
}
void* MessageIndicator(void*, float x, float y, int script) {
    assert(x == 464.0f && y == 352.0f && script == 6);
    ++message_indicator_calls;
    return reinterpret_cast<void*>(0x50);
}
void* MessageLoad(void*, const char* path) {
    loaded_message_path = path;
    return std::strcmp(path, "m8.msg") == 0
               ? reinterpret_cast<void*>(0x60) : nullptr;
}
void* MessageParser(void*, void* resource) {
    assert(resource == reinterpret_cast<void*>(0x60));
    return reinterpret_cast<void*>(0x70);
}
void MessageMissing(void*) { ++message_missing_calls; }

void TestMessageManagerInitialize() {
    const char* names[13] = {
        "m0.msg", "m1.msg", "m2.msg", "m3.msg", "m4.msg", "m5.msg",
        "m6.msg", "m7.msg", "m8.msg", "m9.msg", "m10.msg", "m11.msg",
        "m12.msg",
    };
    unsigned char seen[13] = {};
    unsigned char special_seen = 0;
    void* indicator = nullptr;
    MessageManagerInitEnv env = {
        nullptr, 0, 2, 0, 2, seen, &special_seen, names, MessageTask,
        &indicator, MessageIndicator, MessageLoad, MessageParser,
        MessageMissing,
    };
    MessageManagerState state = {};
    message_task_count = message_indicator_calls = message_missing_calls = 0;
    assert(MessageManager_Initialize(&state, &env) == 0);
    assert(state.message_index == 8);
    assert(state.first_seen_flags == 3);
    assert(seen[8] == 1 && special_seen == 1);
    assert(message_task_count == 2);
    assert(message_task_kind[0] == 0 && message_task_priority[0] == 28);
    assert(message_task_kind[1] == 1 && message_task_priority[1] == 6);
    assert(message_indicator_calls == 1);
    assert(state.resource == reinterpret_cast<void*>(0x60));
    assert(state.parser == reinterpret_cast<void*>(0x70));
    assert(std::strcmp(loaded_message_path, "m8.msg") == 0);

    // An existing indicator is reused, and a missing ordinary-stage resource
    // reports the retail error path.
    state = {};
    env.character = 0;
    env.stage = 1;
    env.power = 1;
    assert(MessageManager_Initialize(&state, &env) == -1);
    assert(message_indicator_calls == 1);
    assert(message_missing_calls == 1);
    assert(state.message_index == 1);
}

} // namespace

int main() {
    TestMainInputTask();
    TestStageTipInitialize();
    TestAsciiManagerInitialize();
    TestMidiFileLoad();
    TestMidiPlaybackTick();
    TestAnmDistanceColor();
    TestMessageManagerInitialize();
    return 0;
}
