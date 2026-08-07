// Host-side tests for the second mass-recovery batch.
#include <cassert>

// Render/effect chain globals (pool_constructors + render leaves).
extern "C" {
unsigned long dword_491C10 = 0;   // animation manager
unsigned long dword_491C30 = 0;   // D3D device
unsigned long dword_491D78 = 0;   // view flags
unsigned long dword_492378 = 0;   // alpha-blend latch
unsigned long dword_477834 = 0;   // player position
}
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "th10/game/bullet_anim_release.hpp"
#include "th10/game/effect_manager_destroy.hpp"
#include "th10/game/effect_indicator_slots.hpp"
#include "th10/game/enemy_drop_sweep.hpp"
#include "th10/game/faith_gauge.hpp"
#include "th10/game/game_ui_create.hpp"
#include "th10/game/object_factories.hpp"
#include "th10/game/player_reset.hpp"
#include "th10/game/score_file.hpp"
#include "th10/game/score_queue.hpp"
#include "th10/game/stats_task.hpp"
#include "th10/game/task_registration.hpp"
#include "th10/game/version_list.hpp"
#include "th10/platform/joystick_probe.hpp"
#include "th10/platform/sound_dummy.hpp"
#include "th10/platform/sound_leaves.hpp"
#include "th10/platform/sound_stream_start.hpp"
#include "th10/render/anm_handle_release.hpp"
#include "th10/render/render_state_sync.hpp"

// ---------------------------------------------------------------------------
// Retail globals consumed by the recovered sources (test-provided).
// ---------------------------------------------------------------------------

// Camera defaults (0x004216F0).
float DAT_00491d7c, DAT_00491d80, DAT_00491d84, DAT_00491d88, DAT_00491d8c,
    DAT_00491d90, DAT_00491d94, DAT_00491d98, DAT_00491d9c, DAT_00491db8,
    DAT_00491dbc, DAT_00491dc0, DAT_00491dc4;
unsigned int DAT_00491e48, DAT_00491e4c, DAT_00491e50, DAT_00491e54;
float DAT_00491e58, DAT_00491e5c;
unsigned int DAT_00491e60;
float DAT_00491e94, DAT_00491e98, DAT_00491e9c, DAT_00491ea0, DAT_00491ea4,
    DAT_00491ea8, DAT_00491eac, DAT_00491eb0, DAT_00491eb4, DAT_00491ed0,
    DAT_00491ed4, DAT_00491ed8, DAT_00491edc;
unsigned int DAT_00491f60, DAT_00491f64, DAT_00491f68, DAT_00491f6c;
float DAT_00491f70, DAT_00491f74;
unsigned int DAT_00491f78;

// Score file (0x0042ACB0 / 0x00421FA0).
extern const char DAT_0046e858[9] = "AAAAAAAA";
extern const char DAT_004743bf[32] = "BCDEFGHIJKLMNOPQRSTUVWXYZabcde";
int32_t DAT_00474c74;
int32_t DAT_00474c44;
int32_t DAT_00474c7c;
uint8_t DAT_00474c90;
uint8_t DAT_0046e354[9];
double DAT_00470b44;

// Game config defaults (0x0041A120 dependencies).
uint32_t DAT_00474e88 = 0x11111111u;
uint32_t DAT_00474e8c = 0x22222222u;
uint32_t DAT_00474e90 = 0x33333333u;
uint32_t DAT_00474e94 = 0x44444444u;
uint16_t DAT_00474e98 = 0x5555u;

// Misc scale constants.
float DAT_00470b00 = 1.0f;
float DAT_00470b98 = 4294967296.0f;

// Rank table (0x004175E0).
uint32_t DAT_00474788[0x180];

// Shared unit timer speed.
float DAT_00476f78 = 1.0f;
// D3D/script stubs for the animation-manager sections the ui_final TU
// keeps alive in this link set (mirror of the archive/bullet_manager TUs).
// Host stand-in for the Windows-only AnimationObject_ExecuteScript (the
// animation-manager sections this link set keeps alive reference it; the
// retail twin lives in all_source_anm_runtime.cpp).
struct AnimationObject;
int AnimationObject_ExecuteScript(AnimationObject*) { return 0; }
// The remaining animation-manager externs this link set reaches (host
// stand-ins; the retail twins live in all_source_anm_runtime.cpp and the
// game globals blob).
float _DAT_00470b60 = 1.0f;   // flt_470B60 (animation scale)
float _DAT_00470b4c = 0.0f;   // flt_470B4C (render-space X offset)
float _DAT_00470b48 = 0.0f;   // flt_470B48 (render-space Y offset)
struct AnimationObject;
void AnimationObject_Render(void*, AnimationObject*) {}

void* g_pD3DDevice = (void*)1;
extern "C" int __stdcall D3DXCreateTexture(
    void*, unsigned int, unsigned int, unsigned int, unsigned int,
    unsigned int, unsigned int, void* output) {
    *(void**)output = 0;
    return 0;
}

// The ui_final runtime globals (the 0x00415AE0 wiring pulled the TU in).
int32_t DAT_00474c68 = 0;
int32_t DAT_00474c6c = 0;
int32_t DAT_00474c4c = 0;
int32_t DAT_00474c84 = 0;
int32_t DAT_00474c8c = 0;
int32_t DAT_00474c70 = 0;
int32_t DAT_00474ca0 = 0;
int32_t DAT_00474e5c = 0;
int32_t DAT_00474e62 = 0;
int32_t DAT_00474c40 = 0;
int32_t DAT_00474c48 = 0;
void* DAT_004776f4 = 0;
int32_t DAT_00477704 = 0;
int32_t DAT_00477830 = 0;
int32_t DAT_00491fb8 = 0;
int32_t DAT_00491ff4 = 0;
int32_t DAT_00491c28 = 0;

// The 0x0042B9A0 sweep constants (retail float values).
float _DAT_00470b0c = 0.5f;
float _DAT_00470afc = 1.0f;
float _DAT_00470b68 = 0.99f;
float _DAT_00470b64 = 1.01f;

// Scheduler globals.
uint32_t DAT_00491be4 = 0x51AB;
uint32_t DAT_00492274;
uint8_t DAT_0049231c;
void* g_pGameThread = 0;
void* g_pGameStateManager = 0;

// Motion/entity constants the linked pool-constructor and entity sources
// reach; the batch-2 tests do not exercise them.
float DAT_00470b04 = 0.0f;
float DAT_00470b0c = 1.0f;
float DAT_00470b38 = 448.0f;
float DAT_00470b3c = 192.0f;
float DAT_00470b40 = -192.0f;
float DAT_00470b5c = 384.0f;

// Flags and latches.
uint8_t DAT_00491d6a;
uint8_t DAT_00491d78;
uint32_t DAT_004918a4;
uint32_t DAT_00491bec;
uint32_t DAT_00477824, DAT_00477828, DAT_0047782c;

// Published progress block for Sound_PlayDummy.
uint8_t* DAT_0047783c;

// Joystick capabilities buffer.
uint8_t DAT_004918b8[0x194];

// Vtable images.
const void* PTR_LAB_0046da10;
const void* PTR_FUN_004703e4;
const void* PTR_FUN_004705d4;

// Globals defined by the recovered sources.
extern uint32_t* DAT_00477834;  // player block (player_reset.cpp)
extern uint32_t* DAT_0047781c;  // score manager (object_factories.cpp)
extern uint8_t* DAT_00477708;   // stats manager (stats_task.cpp)
extern uint32_t* DAT_00477840;  // effect manager (pool_constructors.cpp)
extern uint32_t* DAT_00477810;  // game UI manager (game_ui_create.cpp)
extern uint32_t* DAT_0047770c;  // entity block pool (pool_constructors.cpp)

// ---------------------------------------------------------------------------
// CRT / Win32 shims.
// ---------------------------------------------------------------------------

static int g_enterCount, g_leaveCount, g_freeCount;

static std::vector<uint8_t> g_archivePayload;
static int g_archiveDecryptCount;
static int g_archiveFreeCount;

static void ArchiveDecrypt(uint8_t*, uint32_t, uint8_t key, uint8_t step,
                           uint32_t) {
    // Retail 0x0042B030 calls sub_44B0D0 with key 172 and step 53; the 16 is
    // the block size the hook fixes.
    assert(key == 172 && step == 53);
    ++g_archiveDecryptCount;
}

static void ArchiveDecompress(const uint8_t*, uint32_t, uint8_t* destination,
                              uint32_t destination_size) {
    assert(destination_size == g_archivePayload.size());
    memcpy(destination, g_archivePayload.data(), destination_size);
}

static void* ArchiveAllocate(uint32_t size) {
    return calloc(1, size);
}

static void ArchiveFree(void* memory) {
    ++g_archiveFreeCount;
    free(memory);
}

static void StoreU16(uint8_t* out, uint16_t value) {
    memcpy(out, &value, sizeof(value));
}

static void StoreU32(uint8_t* out, uint32_t value) {
    memcpy(out, &value, sizeof(value));
}

static uint32_t SumBytes(const uint8_t* bytes, uint32_t size) {
    uint32_t sum = 0;
    for (uint32_t index = 0; index < size; ++index) sum += bytes[index];
    return sum;
}

static void TestScoreArchiveLoadSections() {
    g_archivePayload.assign(kScoreFileBytes + kScoreStatsBytes, 0);
    uint8_t* cr = g_archivePayload.data();
    StoreU16(cr, 0x5243);
    StoreU32(cr + 8, kScoreFileBytes);
    StoreU32(cr + 12, 2);
    cr[0x20] = 0xA5;
    StoreU32(cr + 4, SumBytes(cr + 8, kScoreFileBytes - 8));
    uint8_t* st = cr + kScoreFileBytes;
    StoreU16(st, 0x5453);
    StoreU32(st + 8, kScoreStatsBytes);
    st[0x20] = 0x5A;
    StoreU32(st + 4, SumBytes(st + 8, kScoreStatsBytes - 8));

    uint8_t* packed = static_cast<uint8_t*>(calloc(1, 0x20));
    StoreU32(packed, 0x30314854);
    StoreU16(packed + 8, 3);
    StoreU32(packed + 0x10, 8);
    StoreU32(packed + 0x14,
             static_cast<uint32_t>(g_archivePayload.size()));
    std::vector<uint8_t> score_slots(kScoreFileBytes * 3, 0);
    std::vector<uint8_t> stats(kScoreStatsBytes, 0);
    ScoreArchiveLoadState state = {
        packed, 0, score_slots.data(), stats.data(),
    };
    ScoreArchiveLoadHooks hooks = {
        &ArchiveDecrypt, &ArchiveDecompress, &ArchiveAllocate, &ArchiveFree,
    };
    g_archiveDecryptCount = 0;
    assert(ScoreArchive_LoadSections(&state, &hooks) == 0);
    assert(g_archiveDecryptCount == 1);
    assert(score_slots[kScoreFileBytes * 2 + 0x20] == 0xA5);
    assert(stats[0x20] == 0x5A);
    free(state.unpacked);
    free(state.packed);

    packed = static_cast<uint8_t*>(calloc(1, 12));
    state = {packed, 0, score_slots.data(), stats.data()};
    g_archiveFreeCount = 0;
    assert(ScoreArchive_LoadSections(&state, &hooks) == 0);
    assert(g_archiveFreeCount == 1);
    uint32_t signature = 0;
    uint16_t version = 0;
    uint32_t seed = 0;
    memcpy(&signature, state.packed, sizeof(signature));
    memcpy(&version, state.packed + 8, sizeof(version));
    memcpy(&seed, state.packed + 0x0C, sizeof(seed));
    assert(signature == 0x30314854 && version == 3 && seed == 0x100);
    free(state.packed);
}

extern "C" void EnterCriticalSection(void* critical_section) {
    (void)critical_section;
    ++g_enterCount;
}

extern "C" void LeaveCriticalSection(void* critical_section) {
    (void)critical_section;
    ++g_leaveCount;
}

extern "C" void _free(void* memory) {
    ++g_freeCount;
    free(memory);
}

extern "C" void* operator_new(uint32_t size) {
    return calloc(1, size);
}

int* ResourceManager_FindResource(int, void*, const char*) {
    return 0;
}

// ---------------------------------------------------------------------------
// Tests.
// ---------------------------------------------------------------------------

static int g_flushCount;
static uint32_t g_lastRenderState[2];
static int g_renderStateCount;
static uint32_t g_samplerLog[4][3];
static int g_samplerCount;

static void TestRenderStateSync() {
    g_flushCount = 0;
    g_renderStateCount = 0;
    g_samplerCount = 0;
    RenderStateCache cache;
    cache.blend_mode = 0xFF;
    cache.filter_mode = -1;
    cache.sync_counter = 0;
    auto flush = [] { ++g_flushCount; };
    auto set_rs = [](uint32_t id, uint32_t value) {
        g_lastRenderState[0] = id;
        g_lastRenderState[1] = value;
        ++g_renderStateCount;
    };
    auto set_ss = [](uint32_t stage, uint32_t id, uint32_t value) {
        g_samplerLog[g_samplerCount][0] = stage;
        g_samplerLog[g_samplerCount][1] = id;
        g_samplerLog[g_samplerCount][2] = value;
        ++g_samplerCount;
    };
    AnmManager_SyncEntityRenderState(&cache, 0, flush, set_rs, set_ss);
    assert(cache.blend_mode == 0 && cache.filter_mode == 0);
    assert(cache.sync_counter == 1);
    assert(g_flushCount == 2);
    assert(g_renderStateCount == 1);
    assert(g_lastRenderState[0] == 0x14 && g_lastRenderState[1] == 6);
    assert(g_samplerCount == 2);
    assert(g_samplerLog[0][0] == 0 && g_samplerLog[0][1] == 5 &&
           g_samplerLog[0][2] == 2);
    assert(g_samplerLog[1][1] == 6 && g_samplerLog[1][2] == 2);

    // Blend 1 + sign bit -> SetRenderState(0x14, 2), point filtering.
    AnmManager_SyncEntityRenderState(&cache, 0x80000010u, flush, set_rs,
                                     set_ss);
    assert(cache.blend_mode == 1 && cache.filter_mode == 1);
    assert(cache.sync_counter == 2);
    assert(g_lastRenderState[1] == 2);
    assert(g_samplerCount == 4 && g_samplerLog[3][2] == 1);

    // No change -> no calls, counter still advances.
    const int flushes = g_flushCount;
    AnmManager_SyncEntityRenderState(&cache, 0x80000010u, flush, set_rs,
                                     set_ss);
    assert(g_flushCount == flushes && cache.sync_counter == 3);
}

static int g_stopCount;

static void TestBulletAnimRelease() {
    g_stopCount = 0;
    AnmHandleObject child;
    memset(&child, 0, sizeof(child));
    AnmHandleNode childNode = {&child, 0};
    AnmHandleObject a;
    memset(&a, 0, sizeof(a));
    a.handle_value = 5;
    a.children = &childNode;
    AnmHandleObject b;
    memset(&b, 0, sizeof(b));
    b.handle_value = 7;
    b.solo = 1;
    AnmHandleObject bChild;
    memset(&bChild, 0, sizeof(bChild));
    AnmHandleNode bChildNode = {&bChild, 0};
    b.children = &bChildNode;
    AnmHandleNode worldNode = {&a, 0};
    AnmHandleNode uiNode = {&b, 0};
    AnmHandleLists lists = {&worldNode, &uiNode};
    BulletManagerShutdown state;
    memset(&state, 0, sizeof(state));
    state.handles[0] = 5;
    state.handles[1] = 7;
    state.handles[3] = 9;  // no match anywhere
    BulletManager_ReleaseAnimHandles(&state, &lists, [] { ++g_stopCount; });
    assert((a.flags & 0x4000000u) != 0);
    assert((child.flags & 0x4000000u) != 0);   // propagated (not solo)
    assert((b.flags & 0x4000000u) != 0);
    assert((bChild.flags & 0x4000000u) == 0);  // blocked (solo)
    for (int i = 0; i < 5; ++i) {
        assert(state.handles[i] == 0);
    }
    assert(state.timer_vtable == &PTR_FUN_004703e4);
    assert(g_stopCount == 2);
}


struct TestWatchVm {
    uint32_t flags;
    float angle;
    int layer;
    int script;
};
static TestWatchVm g_watch_vms[4];
static int g_watch_alloc_count;
static int g_watch_callback_argument;
static int g_watch_sound_id;
static float g_watch_sound_stamp;

static void TestEffectWatchSpawn() {
    EffectWatchManager manager;
    memset(&manager, 0, sizeof(manager));
    manager.player_position[0] = 100.0f;
    manager.player_position[1] = 50.0f;
    manager.player_position[2] = 2.0f;
    manager.sources[2].x_hundredths = 1234;
    manager.sources[2].y_hundredths = -500;
    manager.animation_owner = (void*)0x1234;

    EffectWatchDescriptor descriptor = {};
    descriptor.offset_x = 4.0f;
    descriptor.offset_y = -2.0f;
    descriptor.angle = 0.5f;
    descriptor.radius = 10.0f;
    descriptor.source_index = 2;
    descriptor.mode = 3;
    descriptor.script_index = 7;
    descriptor.sound_id = 9;
    descriptor.callback = [](EffectWatchManager*, EffectWatchSlot*, int arg) {
        g_watch_callback_argument = arg;
    };

    g_watch_alloc_count = 0;
    g_watch_callback_argument = -1;
    g_watch_sound_id = -1;
    g_watch_sound_stamp = 0.0f;
    memset(g_watch_vms, 0, sizeof(g_watch_vms));
    g_watch_vms[0].flags = 0x08000000u;
    EffectWatchEnvironment env = {};
    env.normalize_angle = [](float angle) { return angle; };
    env.set_polar = [](float out[3], float angle, float radius) {
        out[0] = angle * radius;
        out[1] = radius;
        out[2] = 77.0f;
    };
    env.allocate_vm = [](void*) -> void* {
        return &g_watch_vms[g_watch_alloc_count++];
    };
    env.prepare_vm = [](void*, void* vm, int layer, uint32_t flags_or,
                        void* owner, int script) {
        assert(owner == (void*)0x1234);
        TestWatchVm* typed = (TestWatchVm*)vm;
        typed->layer = layer;
        typed->flags |= flags_or;
        typed->script = script;
    };
    env.register_vm = [](void*, void* vm) {
        return (int32_t)(((TestWatchVm*)vm - g_watch_vms) + 100);
    };
    env.find_vm = [](void*, int32_t handle) -> void* {
        return &g_watch_vms[handle - 100];
    };
    env.get_vm_flags = [](void*, void* vm) {
        return ((TestWatchVm*)vm)->flags;
    };
    env.set_vm_angle_and_flags = [](void*, void* vm, float angle,
                                    uint32_t flags_or) {
        TestWatchVm* typed = (TestWatchVm*)vm;
        typed->angle = angle;
        typed->flags |= flags_or;
    };
    env.queue_sound = [](void*, int16_t id, float stamp) {
        g_watch_sound_id = id;
        g_watch_sound_stamp = stamp;
    };

    assert(EffectWatch_SpawnFromDescriptor(&manager, &descriptor, 77, &env) == 0);
    EffectWatchSlot& slot = manager.slots[0];
    assert(slot.active == 1 && slot.descriptor == &descriptor);
    assert(slot.timer.target == -1 && slot.timer.current == 0 &&
           slot.timer.previous == 0 && slot.timer.flags == 1);
    assert(slot.timer.speed == &DAT_00476f78);
    assert(manager.exclusive_active[2] == 1);
    assert(slot.origin[0] > 11.33f && slot.origin[0] < 11.35f);
    assert(slot.origin[1] == -17.0f && slot.origin[2] == 0.0f);
    assert(slot.polar[2] == 0.0f);
    assert(slot.primary_handle == 100 && slot.secondary_handle == 101);
    assert(g_watch_vms[0].layer == 15 && g_watch_vms[0].script == 12);
    assert((g_watch_vms[0].flags & 0x40000004u) == 0x40000004u);
    assert(g_watch_vms[0].angle == descriptor.angle);
    assert(g_watch_vms[1].script == 0x10);
    assert(g_watch_callback_argument == 77);
    assert(g_watch_sound_id == 9 && g_watch_sound_stamp == slot.origin[0]);

    // Mode 3 suppresses a second spawn for the same source.
    assert(EffectWatch_SpawnFromDescriptor(&manager, &descriptor, 88, &env) == 0);
    assert(g_watch_alloc_count == 2 && manager.slots[1].active == 0);

    // A non-exclusive player-origin descriptor reuses the next free slot and
    // does not allocate the secondary animation or queue a negative sound.
    descriptor.source_index = 0;
    descriptor.mode = 0;
    descriptor.sound_id = -1;
    descriptor.callback = 0;
    assert(EffectWatch_SpawnFromDescriptor(&manager, &descriptor, 0, &env) == 0);
    assert(manager.slots[1].active == 1);
    assert(manager.slots[1].secondary_handle == 0);
    assert(g_watch_alloc_count == 3);
}

static void TestPlayerReset() {
    std::vector<uint32_t> block(kPlayerBlockDwords, 0xABABABABu);
    // Retail returns the state pointer (0x004246C0: a1 in eax).
    assert(Player_ResetAndPublish(block.data()) == block.data());
    for (uint32_t word : block) {
        assert(word == 0);
    }
    assert(DAT_00477834 == block.data());
}

static uint32_t* g_constructedBase;
static int g_destroyCount;
static int g_initResult;

static void TestObjectFactories() {
    // Success path publishes and zeroes.
    g_initResult = 0;
    g_destroyCount = 0;
    uint32_t* state = ScoreManager_CreateAndInit(
        [](uint32_t size) {
            void* memory = malloc(size);
            memset(memory, 0xEE, size);
            return memory;
        },
        [](uint32_t* base) { g_constructedBase = base; },
        [](uint32_t*) { return g_initResult; }, [](uint32_t*) { ++g_destroyCount; });
    assert(state != 0);
    assert(g_constructedBase == state + 4);
    for (int i = 0; i < 0x117; ++i) {
        assert(state[i] == 0);
    }
    assert(DAT_0047781c == state);
    free(state);

    // Failed init tears down.
    g_initResult = 1;
    const int freed = g_freeCount;
    state = ScoreManager_CreateAndInit(
        [](uint32_t size) { return malloc(size); }, [](uint32_t*) {},
        [](uint32_t*) { return g_initResult; }, [](uint32_t*) { ++g_destroyCount; });
    assert(state == 0);
    assert(g_destroyCount == 1);
    assert(g_freeCount == freed + 1);

    // Enemy slot factory: failed init also frees.
    const int freed2 = g_freeCount;
    uint32_t* slot = EnemySlot_CreateAndInit(
        [](uint32_t size) { return malloc(size); },
        [](uint32_t* memory) { return memory; }, [] { return 1; },
        [](uint32_t*) { ++g_destroyCount; });
    assert(slot == 0 && g_destroyCount == 2 && g_freeCount == freed2 + 1);
}

static void TestVersionList() {
    const char* text = "th10v 1 2\nth10w 3 4\n";
    VersionList list;
    list.text = text;
    list.length = (int32_t)strlen(text);
    assert(VersionList_Match(&list, "th10v", 1, 2) == 0);
    assert(VersionList_Match(&list, "th10w", 3, 4) == 0);
    assert(VersionList_Match(&list, "th10w", 3, 5) == -1);
    assert(VersionList_Match(&list, "th10x", 1, 2) == -1);
    assert(VersionList_Match(&list, "debug", 9, 9) == 0);
    VersionList missing;
    missing.text = 0;
    missing.length = 0;
    assert(VersionList_Match(&missing, "th10v", 1, 2) == 0);
}

static ScorePopupNode g_popupNode;
static int g_attachCount;

static void TestScoreQueue() {
    ScorePopupNode head;
    memset(&head, 0, sizeof(head));
    ScorePopupQueue queue = {&head, 0, 0};
    memset(&g_popupNode, 0, sizeof(g_popupNode));
    g_attachCount = 0;
    const uint32_t id = ScoreQueue_Push(
        &queue, 0, [](uint32_t) { return (void*)&g_popupNode; },
        [](void* memory) { return (ScorePopupNode*)memory; },
        [](void* memory) { return (ScorePopupNode*)memory; },
        [](ScorePopupNode*) { ++g_attachCount; });
    assert(id == 1);
    assert(g_popupNode.id == 1);
    assert(g_popupNode.prev == &head);
    assert(head.next == &g_popupNode);
    assert(queue.tail == &g_popupNode && queue.count == 1);
    assert(g_attachCount == 1);

    // Unknown kind just advances the id.
    const uint32_t id2 = ScoreQueue_Push(
        &queue, 7, [](uint32_t) { return (void*)&g_popupNode; },
        [](void* memory) { return (ScorePopupNode*)memory; },
        [](void* memory) { return (ScorePopupNode*)memory; },
        [](ScorePopupNode*) { ++g_attachCount; });
    assert(id2 == 2 && queue.count == 1 && g_attachCount == 1);

    // Full queue rejects.
    queue.count = 0x100;
    assert(ScoreQueue_Push(&queue, 0, 0, 0, 0, 0) == 0);
}

static uint32_t g_registeredToken;
static int g_allocIndex;
static uint32_t g_managerBlock[0x23];
static StatsTaskNode g_statsNode;

static void TestStatsTask() {
    g_registeredToken = 0;
    g_allocIndex = 0;
    memset(g_managerBlock, 0xCC, sizeof(g_managerBlock));
    memset(&g_statsNode, 0, sizeof(g_statsNode));
    g_statsNode.flags = 0x10;
    uint32_t* manager = GameplayStats_CreateAndRegister(
        [](uint32_t size) {
            return g_allocIndex++ == 0 ? (size == 0x8C ? (void*)g_managerBlock : (void*)0)
                                       : (size == 0x24 ? (void*)&g_statsNode : (void*)0);
        },
        [](uint32_t token) { g_registeredToken = token; }, (void*)0x1234);
    assert(manager == g_managerBlock);
    assert(manager[0] == 2);
    for (int i = 1; i < 0x23; ++i) {
        if (i == 3) {
            continue;
        }
        assert(manager[i] == 0);
    }
    assert(DAT_00477708 == (uint8_t*)manager);
    assert(g_statsNode.self == &g_statsNode);
    assert(g_statsNode.owner == manager);
    assert(g_statsNode.callback == (void*)0x1234);
    assert(g_statsNode.flags == 0x13);
    assert(g_registeredToken == DAT_00491be4);
    assert(manager[3] == (uint32_t)(uintptr_t)&g_statsNode);
}

static void* g_releasedTasks[2];
static int g_releaseCount;

static void TestEffectManagerDestroy() {
    g_releaseCount = 0;
    g_enterCount = 0;
    g_leaveCount = 0;
    DAT_0049231c = 0;
    DAT_00477840 = (uint32_t*)0x5678;
    EffectManagerTasks state;
    state.update_task = (void*)0x11;
    state.render_task = (void*)0x22;
    state.buffer = malloc(16);
    const int freed = g_freeCount;
    EffectManager_ReleaseTasks(&state, [](void* task, uint32_t token) {
        assert(token == DAT_00491be4);
        g_releasedTasks[g_releaseCount++] = task;
    });
    assert(g_releaseCount == 2);
    assert(g_releasedTasks[0] == (void*)0x11 && g_releasedTasks[1] == (void*)0x22);
    assert(g_enterCount == 2 && g_leaveCount == 2);
    assert(DAT_0049231c == 0);
    assert(DAT_00477840 == 0);
    assert(state.buffer == 0);
    assert(g_freeCount == freed + 1);
}

static int g_playMode;
static int g_playValue;
static int g_playCount;

static void TestSoundLeaves() {
    g_playCount = 0;
    const uint32_t result = Sound_PlayRandomVoice(
        [] { return (uint64_t)0x100000005ull; },
        [](const char* name, int32_t mode, int32_t value) {
            assert(name[0] == '\0');
            g_playMode = mode;
            g_playValue = value;
            ++g_playCount;
        });
    assert(result == 0 && g_playCount == 1);
    assert(g_playMode == 5 && g_playValue == 5);

    static void** g_releasedObject;
    void* object = (void*)0xABCD;
    SoundBuffer_DestructBase(&object,
                             [](void** target) { g_releasedObject = target; });
    assert(object == (void*)&PTR_FUN_004705d4);
    assert(g_releasedObject == &object);
}

static int g_spawnCount;
static int g_soundCount;

static void TestEnemyDropSweep() {
    g_spawnCount = 0;
    g_soundCount = 0;
    std::vector<uint8_t> manager(0x3C0 + 0x96 * 0x3F0, 0);
    auto set_slot = [&](int index, int32_t active, int32_t kind) {
        uint8_t* slot = manager.data() + 0x3C0 + index * 0x3F0;
        memcpy(slot + 0x30, &active, 4);
        memcpy(slot + 0x34, &kind, 4);
    };
    set_slot(0, 1, 4);
    set_slot(1, 1, 2);  // wrong kind, skipped
    set_slot(2, 1, 1);
    set_slot(3, 0, 1);  // inactive, skipped
    const uint32_t result = Enemy_SweepPendingDrops(
        manager.data(),
        [](uint8_t*, int32_t kind, int32_t id, float angle, float speed) {
            assert(kind == 9 && id == -1);
            assert(angle < -1.57f && angle > -1.58f);
            assert(speed > 2.19f && speed < 2.21f);
            ++g_spawnCount;
        },
        [] { ++g_soundCount; });
    assert(result == 0);
    assert(g_spawnCount == 2 && g_soundCount == 2);
    int32_t active0, active1;
    memcpy(&active0, manager.data() + 0x3C0 + 0x30, 4);
    memcpy(&active1, manager.data() + 0x3C0 + 0x3F0 + 0x30, 4);
    assert(active0 == 0 && active1 == 1);
}

static int g_resetCount;
static int g_afterResetCount;
static int g_volumeSteps;
static uint32_t g_playArgs[3];

static void TestSoundStreamStart() {
    SoundStream state;
    memset(&state, 0, sizeof(state));
    // Device guard.
    assert(SoundStream_Start(&state, 0, 0, 0, 0, 0, 0, 0, 0, 0) ==
           (int32_t)0x800401F0);
    state.device = 1;
    // Missing buffer.
    assert(SoundStream_Start(&state, 0, 0, 0,
                             [](uint32_t) { return (void*)0; }, 0, 0, 0, 0,
                             0) == (int32_t)0x80004005);
    // Success with reset branch.
    g_resetCount = 0;
    g_afterResetCount = 0;
    g_volumeSteps = 0;
    state.fade_mode = 9;
    state.fade_count = 9;
    state.fade_wait = 9;
    state.stop_flag = 9;
    const int32_t result = SoundStream_Start(
        &state, 2, 0x111, 0x222, [](uint32_t) { return (void*)0x77; },
        [] { return 0; },
        [](void* buffer) {
            assert(buffer == (void*)0x77);
            ++g_resetCount;
            return 0;
        },
        [] { ++g_afterResetCount; }, [] { ++g_volumeSteps; },
        [](void* buffer, uint32_t reserved, uint32_t arg1, uint32_t arg2) {
            assert(buffer == (void*)0x77 && reserved == 0);
            g_playArgs[1] = arg1;
            g_playArgs[2] = arg2;
            return 42;
        });
    assert(result == 42);
    assert(g_resetCount == 1 && g_afterResetCount == 1 && g_volumeSteps == 1);
    assert(state.fade_mode == 0 && state.fade_count == 0 &&
           state.fade_wait == 0);
    assert(state.started == 1 && state.stop_flag == 0);
    assert(state.play_arg1 == 0x111 && state.play_arg2 == 0x222);
    assert(g_playArgs[1] == 0x111 && g_playArgs[2] == 0x222);
}

static SchedulerCallback g_callbackPool[8];
static int g_callbackIndex;
static int g_primaryRegs;
static int g_secondaryRegs;
static uint32_t g_tipLog[2][2];
static int g_tipCount;

static SchedulerCallback* CreateCallback(SchedulerFunction function) {
    SchedulerCallback* callback = &g_callbackPool[g_callbackIndex++];
    memset(callback, 0, sizeof(*callback));
    callback->flags = 0xFF;
    callback->function = function;
    return callback;
}

static void RegisterPrimary(SchedulerCallback* callback, uint32_t token) {
    assert(token == DAT_00491be4);
    assert((callback->flags & 2u) == 0);
    ++g_primaryRegs;
}

static void RegisterSecondary(SchedulerCallback* callback, uint32_t token) {
    assert(token == DAT_00491be4);
    assert((callback->flags & 2u) == 0);
    ++g_secondaryRegs;
}

static int StubProc(void*) { return 0; }

static void TestTaskRegistration() {
    int owner = 0;

    // Stage tips (0x00418E30).
    g_callbackIndex = 0;
    g_primaryRegs = 0;
    g_secondaryRegs = 0;
    g_tipCount = 0;
    DAT_00491d6a = 1;
    TaskPairSlots slots;
    uint32_t counter = 55;
    assert(StageTip_RegisterTasks(
               &owner, &slots, &counter, CreateCallback, RegisterPrimary,
               RegisterSecondary, StubProc, StubProc,
               [](void*, uint32_t text, int32_t slot) {
                   g_tipLog[g_tipCount][0] = text;
                   g_tipLog[g_tipCount][1] = (uint32_t)slot;
                   ++g_tipCount;
               }) == 0);
    assert(slots.update_task == &g_callbackPool[0]);
    assert(slots.render_task == &g_callbackPool[1]);
    assert(slots.update_task->owner == &owner);
    assert(counter == 0);
    assert(g_primaryRegs == 1 && g_secondaryRegs == 1);
    assert(g_tipCount == 2);
    assert(g_tipLog[0][0] == 0x0046D6D8u && g_tipLog[0][1] == 0);
    assert(g_tipLog[1][0] == 0x0046D6C4u && g_tipLog[1][1] == 1);

    // Timed pair (0x00422150).
    g_callbackIndex = 0;
    TimedTaskState timed;
    memset(&timed, 0, sizeof(timed));
    assert(TimedTask_RegisterPair(&owner, &timed, CreateCallback,
                                  RegisterPrimary, RegisterSecondary, StubProc,
                                  StubProc) == 0);
    assert(timed.timer.flags == 1);
    assert(timed.timer.speed == &DAT_00476f78);
    assert(timed.timer.target == -1);
    assert(timed.timer.current == 0 && timed.timer.previous == 0);

    // Score display (0x0041C120): missing resource fails.
    static int errorCount = 0;
    int32_t* resourceSlot = (int32_t*)0x1;
    ScorePopupNode head;
    ScorePopupNode* tail = 0;
    assert(ScoreDisplay_RegisterTasks(
               &owner, &slots, &resourceSlot, &tail, &head,
               [](int32_t slot, const char* name) {
                   assert(slot == 7 && strcmp(name, "bullet.anm") == 0);
                   return (int32_t*)0;
               },
               [] { ++errorCount; }, CreateCallback, RegisterPrimary,
               RegisterSecondary, StubProc, StubProc) == -1);
    assert(resourceSlot == 0 && errorCount == 1);
    // Success wires the queue tail to the sentinel head.
    g_callbackIndex = 0;
    static int32_t resource = 7;
    assert(ScoreDisplay_RegisterTasks(
               &owner, &slots, &resourceSlot, &tail, &head,
               [](int32_t, const char*) { return &resource; }, [] {},
               CreateCallback, RegisterPrimary, RegisterSecondary, StubProc,
               StubProc) == 0);
    assert(resourceSlot == &resource && tail == &head);

    // Front UI (0x00413980): failed sprite setup aborts.
    g_callbackIndex = 0;
    assert(FrontAnm_RegisterTasks(
               &owner, &slots, &resourceSlot,
               [](int32_t slot, const char* name) {
                   assert(slot == 6 && strcmp(name, "front.anm") == 0);
                   return &resource;
               },
               [] {}, [](void*) { return 1; }, CreateCallback, RegisterPrimary,
               RegisterSecondary, StubProc, StubProc) == -1);
    assert(FrontAnm_RegisterTasks(
               &owner, &slots, &resourceSlot,
               [](int32_t, const char*) { return &resource; }, [] {},
               [](void*) { return 0; }, CreateCallback, RegisterPrimary,
               RegisterSecondary, StubProc, StubProc) == 0);

    // Title screen (0x0042CAA0).
    g_callbackIndex = 0;
    DAT_004918a4 = 9;
    TitleInitState title;
    memset(&title, 0, sizeof(title));
    assert(Title_RegisterTasks(
               &owner, &title,
               [](int32_t slot, const char* name) {
                   if (slot == 0x19) {
                       assert(strcmp(name, "title.anm") == 0);
                   } else {
                       assert(slot == 0x1A &&
                              strcmp(name, "title_v.anm") == 0);
                   }
                   return &resource;
               },
               [] {}, CreateCallback, RegisterPrimary, RegisterSecondary,
               StubProc, StubProc) == 0);
    assert(title.ready_flag == 1 && DAT_004918a4 == 0);
    assert(title.title_resource == &resource &&
           title.title_v_resource == &resource);
}

static int g_dummyLog[4][2];
static int g_dummyCount;

static void TestSoundDummy() {
    std::vector<uint8_t> progress(0x1D892 + 8, 0);
    DAT_0047783c = progress.data();
    DAT_00491d78 = 0x10;
    g_dummyCount = 0;
    assert(Sound_PlayDummy((void*)0x1, 0x99, 3,
                           [](void*, const char* name, int32_t mode,
                              uint32_t value) {
                               assert(strcmp(name, "dummy") == 0);
                               g_dummyLog[g_dummyCount][0] = mode;
                               g_dummyLog[g_dummyCount][1] = (int)value;
                               ++g_dummyCount;
                           }) == 0);
    assert(g_dummyCount == 2);
    assert(g_dummyLog[0][0] == 4 && g_dummyLog[0][1] == 0);
    assert(g_dummyLog[1][0] == 2 && g_dummyLog[1][1] == 0x99);
    assert(progress[0x1D892 + 3] == 1);

    // Without bit 4 only the argument cue plays.
    DAT_00491d78 = 0;
    g_dummyCount = 0;
    Sound_PlayDummy((void*)0x1, 0x7, 1,
                    [](void*, const char*, int32_t mode, uint32_t) {
                        g_dummyLog[g_dummyCount][0] = mode;
                        ++g_dummyCount;
                    });
    assert(g_dummyCount == 1 && g_dummyLog[0][0] == 2);
}

static int g_evictCount;
static void* g_spawnLog[2];

static void TestGameUiCreate() {
    g_evictCount = 0;
    uint32_t* state = GameUi_CreateAndPublish(
        [](uint32_t size) {
            void* memory = malloc(size);
            memset(memory, 0xEE, size);
            return memory;
        },
        [] { ++g_evictCount; },
        [](void* start, void* argument) {
            g_spawnLog[0] = start;
            g_spawnLog[1] = argument;
        },
        (void*)0xBEEF, 0xDEADu);
    assert(state != 0);
    for (int i = 0; i < 0x16; ++i) {
        assert(state[i] == 0);
    }
    assert(state[0x16] == 4);
    assert(state[0x17] == 0xDEADu);
    assert(DAT_00477810 == state);
    assert(g_evictCount == 1);
    assert(g_spawnLog[0] == (void*)0xBEEF && g_spawnLog[1] == 0);
    free(state);
}

static int g_posCalls;
static int g_missingReports;

static void TestJoystickProbe() {
    // Both devices missing -> report + 1.
    g_posCalls = 0;
    g_missingReports = 0;
    assert(Joystick_Probe(
               [](uint32_t, JoystickProbeInfo* info) {
                   assert(info->size == 0x34 && info->flags == 0xFF);
                   ++g_posCalls;
                   return 1u;
               },
               [](uint32_t, void*, uint32_t) { return 0u; },
               [] { ++g_missingReports; }) == 1);
    assert(g_posCalls == 2 && g_missingReports == 1);

    // Device 0 present -> capabilities captured, low half masked.
    g_posCalls = 0;
    assert(Joystick_Probe(
               [](uint32_t, JoystickProbeInfo*) {
                   ++g_posCalls;
                   return 0u;
               },
               [](uint32_t id, void* caps, uint32_t size) {
                   assert(id == 0 && caps == DAT_004918b8 && size == 0x194);
                   return 0x00020001u;
               },
               [] { ++g_missingReports; }) == 0x00020000u);
    assert(g_posCalls == 1 && g_missingReports == 1);
}

static int g_gaugeReleases;
static uint32_t g_releasedHandle;
static uint32_t g_spawnedHandle = 0x77;
static uint32_t g_spawnResource;

static void TestFaithGauge() {
    std::vector<uint8_t> manager(0xA000, 0);
    DAT_0047770c = (uint32_t*)manager.data();
    const uint32_t oldHandle = 0x55;
    memcpy(manager.data() + 0x9E18, &oldHandle, 4);
    const uint32_t resource = 0x66;
    memcpy(manager.data() + 0x9EC8, &resource, 4);

    // Saturated gauge rejects.
    int16_t level = 100;
    assert(!FaithGauge_Add(&level, 5, 0, 0, 0));
    assert(level == 100);

    // Crossing 100 clamps and swaps the celebration animation.
    level = 95;
    g_gaugeReleases = 0;
    const bool crossed = FaithGauge_Add(
        &level, 10, (void*)0x1,
        [](void*, uint32_t handle) {
            g_releasedHandle = handle;
            ++g_gaugeReleases;
        },
        [](uint32_t resource_token, int32_t script, int32_t layer) {
            assert(script == 0x49 && layer == 0xF);
            g_spawnResource = resource_token;
            return (const uint32_t*)&g_spawnedHandle;
        });
    assert(level == 100);
    assert(crossed);  // (100-10)/20 == 4 != 100/20 == 5
    assert(g_gaugeReleases == 1 && g_releasedHandle == 0x55);
    assert(g_spawnResource == 0x66);
    uint32_t newHandle;
    memcpy(&newHandle, manager.data() + 0x9E18, 4);
    assert(newHandle == 0x77);

    // Small add without boundary crossing.
    level = 10;
    assert(!FaithGauge_Add(&level, 5, 0, 0, 0));
    assert(level == 15);
}

static AnmObject g_trackedObjects[3];
static AnmObject g_trackedChild;
static AnmChildNode g_trackedChildNode;

static AnmObject* ResolveTracked(uint32_t handle) {
    if (handle == 0xA1) {
        return &g_trackedObjects[0];
    }
    if (handle == 0xA2) {
        return &g_trackedObjects[1];
    }
    return 0;
}

static void TestAnmHandleRelease() {
    memset(g_trackedObjects, 0, sizeof(g_trackedObjects));
    memset(&g_trackedChild, 0, sizeof(g_trackedChild));
    g_trackedChildNode.object = &g_trackedChild;
    g_trackedChildNode.next = 0;
    g_trackedObjects[0].children = &g_trackedChildNode;
    g_trackedObjects[1].solo = 1;
    DAT_00477824 = 0xA1;
    DAT_00477828 = 0xA2;
    DAT_0047782c = 0xA3;  // unresolved
    DAT_00491bec = 5;
    uint32_t phase = 1;
    Anm_ReleaseTrackedHandles(&phase, ResolveTracked);
    assert(phase == 2);
    assert(g_trackedObjects[0].sprite_word == 2);
    assert(g_trackedChild.sprite_word == 2);
    assert(g_trackedObjects[1].sprite_word == 2);
    assert(DAT_00477824 == 0 && DAT_00477828 == 0 && DAT_0047782c == 0);
    assert(DAT_00491bec == 0);

    // Phase gate: nothing happens at phase 2, latch still clears.
    DAT_00477824 = 0xA1;
    g_trackedObjects[0].sprite_word = 0;
    DAT_00491bec = 3;
    Anm_ReleaseTrackedHandles(&phase, ResolveTracked);
    assert(phase == 2 && DAT_00477824 == 0xA1);
    assert(g_trackedObjects[0].sprite_word == 0);
    assert(DAT_00491bec == 0);
}

int main() {
    TestScoreArchiveLoadSections();
    TestRenderStateSync();
    TestBulletAnimRelease();
    TestEffectWatchSpawn();
    TestPlayerReset();
    TestObjectFactories();
    TestVersionList();
    TestScoreQueue();
    TestStatsTask();
    TestEffectManagerDestroy();
    TestSoundLeaves();
    TestEnemyDropSweep();
    TestSoundStreamStart();
    TestTaskRegistration();
    TestSoundDummy();
    TestGameUiCreate();
    TestJoystickProbe();
    TestFaithGauge();
    TestAnmHandleRelease();
    printf("recovery_batch2_test: all tests passed\n");
    return 0;
}
