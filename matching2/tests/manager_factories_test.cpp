#include "th10/game/boss_overlays.hpp"
#include "th10/game/bullet_manager.hpp"
#include "th10/game/enemy_lifecycle.hpp"
#include "th10/game/manager_factories.hpp"
#include "th10/game/player_motion.hpp"
#include "th10/game/stage_background.hpp"
#include "th10/game/weather_pool.hpp"
#include "th10/platform/midi_worker.hpp"
#include "th10/platform/sound_float_forward.hpp"
#include "th10/render/anm_texture_upload.hpp"
#include "th10/render/render_stage_select.hpp"
#include "th10/script/ecl_vm_children.hpp"
#include "th10/util/legacy_string_funclets.hpp"
#include "th10/util/scalars.hpp"

#include <cassert>
#include <cstdlib>
#include <cstring>

// --- Test scaffolding --------------------------------------------------------

static int g_allocation_count;
static void* Allocate(unsigned int size) {
    ++g_allocation_count;
    return std::malloc(size);
}

static int g_free_count;
static void FreeMemory(void* memory) {
    ++g_free_count;
    std::free(memory);
}

static long long TruncateFloat(float value) { return (long long)value; }

// --- LegacyString funclets ----------------------------------------------------

static unsigned int g_requested_allocation;
static char g_growth_buffer[64];
static void* GrowthAllocate(unsigned int size) {
    g_requested_allocation = size;
    return g_growth_buffer;
}

static int g_rethrow_count;
static void CountRethrow(void) { ++g_rethrow_count; }

static char* g_freed_text;
static void CaptureFreedText(void* memory) { g_freed_text = (char*)memory; }

static void TestLegacyStringFunclets() {
    g_requested_allocation = 0;
    void* buffer = LegacyString_GrowthCatchAllocate(31, GrowthAllocate);
    assert(buffer == g_growth_buffer);
    assert(g_requested_allocation == 32);
    assert(LegacyString_GrowthCatchAllocate(31, 0) == 0);

    static char heap_text[32];
    LegacyStringPayload text;
    text.storage.heap_text = heap_text;
    text.length = 20;
    text.capacity = 31;
    g_freed_text = 0;
    g_rethrow_count = 0;
    LegacyString_AssignCatchRelease(&text, CaptureFreedText, CountRethrow);
    assert(g_freed_text == heap_text);
    assert(g_rethrow_count == 1);
    assert(text.capacity == 0xF);
    assert(text.length == 0);
    assert(text.storage.inline_text[0] == '\0');

    // Inline strings must not release their storage.
    LegacyStringPayload inline_text;
    inline_text.storage.inline_text[0] = 'a';
    inline_text.length = 1;
    inline_text.capacity = 0xF;
    g_freed_text = 0;
    LegacyString_AssignCatchRelease(&inline_text, CaptureFreedText,
                                    CountRethrow);
    assert(g_freed_text == 0);
    assert(g_rethrow_count == 2);
}

// --- Forward leaves -------------------------------------------------------------

static double g_forwarded_double;
static void CaptureDouble(double value) { g_forwarded_double = value; }

static float* g_wrapped_axis;
static float g_wrapped_delta;
static void CaptureWrap(float* axis, float delta) {
    g_wrapped_axis = axis;
    g_wrapped_delta = delta;
}

static void TestForwardLeaves() {
    Sound_ForwardFloatAsDouble(0.5f, CaptureDouble);
    assert(g_forwarded_double == 0.5);

    float axis = 3.0f;
    Player_ForwardAxisWrap(&axis, 2.0f, CaptureWrap);
    assert(g_wrapped_axis == &axis);
    assert(g_wrapped_delta == 2.0f);
}

// --- Player wrap leaves ---------------------------------------------------------

static int g_probe_result;
static int Probe(void) { return g_probe_result; }

static float g_wrap_pan;
static int g_wrap_sounds;
static void PlayWrapSound(float pan) {
    g_wrap_pan = pan;
    ++g_wrap_sounds;
}

static int g_wrap_effects;
static void SpawnWrapEffect(void) { ++g_wrap_effects; }

static void TestPlayerWrap() {
    g_probe_result = 1;
    g_wrap_sounds = 0;
    g_wrap_effects = 0;

    // Above the high bound: fold down across extent + margin.
    float axis = 250.0f;
    unsigned int flags = 0;
    Player_WrapHorizontal(&axis, 384.0f, -192.0f, 192.0f, 16.0f, Probe,
                          PlayWrapSound, 0, SpawnWrapEffect, 0, &flags);
    assert(axis == 250.0f - 400.0f);
    assert(g_wrap_sounds == 1);
    assert(g_wrap_pan == -1.0f);
    assert(g_wrap_effects == 1);
    assert(flags == 0x100000u);

    // Below the low bound: fold up. Armed focus keeps the pose flag.
    axis = -260.0f;
    flags = 0;
    Player_WrapVertical(&axis, 448.0f, -224.0f, 224.0f, 16.0f, Probe,
                        PlayWrapSound, -1, SpawnWrapEffect, 2, &flags);
    assert(axis == 448.0f + -260.0f + 16.0f);
    assert(g_wrap_effects == 1);  // disarmed slot spawns nothing
    assert(flags == 0);

    // Inside the field: nothing wraps but the pose flag still toggles.
    axis = 10.0f;
    flags = 0x200000u;
    Player_WrapVertical(&axis, 448.0f, -224.0f, 224.0f, 16.0f, Probe,
                        PlayWrapSound, 0, SpawnWrapEffect, 0, &flags);
    assert(axis == 10.0f);
    assert(flags == 0);

    // A closed probe suppresses the wrap entirely.
    g_probe_result = 0;
    axis = 250.0f;
    int wrapped = Player_WrapAxisCore(&axis, 384.0f, -192.0f, 192.0f, 16.0f,
                                      Probe, PlayWrapSound, 0,
                                      SpawnWrapEffect);
    assert(wrapped == 0);
    assert(axis == 250.0f);
}

// --- Frame-timer leaves ----------------------------------------------------------

static void TestEffectPoolUpdateDrops() {
    static RainDrop drops[3];
    std::memset(drops, 0, sizeof(drops));
    static float slow_control = 1.0f;   // inside (0.5, 1.5)
    static float fast_control = 4.0f;   // outside the span

    drops[0].active = 1;
    drops[0].position = 100.0f;
    drops[0].frame = 3.0f;
    drops[0].timer = 3.0f;
    drops[0].control = &slow_control;

    drops[1].active = 0;  // retired slots must not move
    drops[1].position = 50.0f;
    drops[1].control = &fast_control;

    drops[2].active = 1;
    drops[2].position = 10.0f;
    drops[2].frame = 60.0f;
    drops[2].timer = 59.5f;
    drops[2].control = &fast_control;

    int result = EffectPool_UpdateDrops(drops, 3, 2.0f, 0.5f, 0.5f, 1.5f, 1.0f,
                                        TruncateFloat);
    assert(result == 1);

    // Slot 0: sank by gravity, frame advanced by one, timer gained one step.
    assert(drops[0].position == 99.0f);
    assert(drops[0].previous_frame == 3.0f);
    assert(drops[0].frame == 4.0f);
    assert(drops[0].timer == 4.0f);
    assert(drops[0].active == 1);

    // Slot 1: untouched.
    assert(drops[1].position == 50.0f);

    // Slot 2: absorbed the control value, retruncated, and retired past 0x3C.
    assert(drops[2].position == 9.0f);
    assert(drops[2].timer == 63.5f);
    assert(drops[2].frame == 63.0f);
    assert(drops[2].active == 0);
}

static int g_trail_count;
static void EmitTrail(void) { ++g_trail_count; }

static void TestPlayerAnimationAdvanceFrame() {
    static float control = 1.0f;
    PlayerFrameTimer timer;
    timer.previous = 0;
    timer.frame = 5;
    timer.timer = 5.0f;
    timer.control = &control;
    unsigned int flags = 0;

    g_trail_count = 0;
    PlayerAnimation_AdvanceFrame(&timer, &flags, 0.5f, 1.5f, 1.0f, 0x11,
                                 EmitTrail, TruncateFloat);
    assert(g_trail_count == 1);
    assert(flags == 0);
    assert(timer.previous == 5);
    assert(timer.frame == 6);
    assert(timer.timer == 6.0f);

    // Past the trail limit the pose flag toggles; a fast control retruncates.
    control = 4.0f;
    timer.frame = 0x12;
    timer.timer = 18.25f;
    PlayerAnimation_AdvanceFrame(&timer, &flags, 0.5f, 1.5f, 1.0f, 0x11,
                                 EmitTrail, TruncateFloat);
    assert(g_trail_count == 1);
    assert(flags == 1);
    assert(timer.previous == 0x12);
    assert(timer.timer == 22.25f);
    assert(timer.frame == 22);
}

// --- ECL child-VM leaves -----------------------------------------------------------

static void* g_started_vm;
static float* g_started_argument;
static void CaptureStart(void* active_vm, float* argument) {
    g_started_vm = active_vm;
    g_started_argument = argument;
}

static int g_tick_calls;
static int g_tick_failures_from;
static int Tick(EclOwner* owner, float delta) {
    (void)owner;
    (void)delta;
    ++g_tick_calls;
    return g_tick_calls >= g_tick_failures_from ? 1 : 0;
}

static void TestEclChildVmLeaves() {
    EclOwner owner;
    std::memset(&owner, 0, sizeof(owner));
    EclChildVm root;
    std::memset(&root, 0, sizeof(root));
    root.difficulty_mask = 3;
    owner.active_vm = &root;
    owner.root_vm = &root;
    owner.anchor.vm = &root;

    float argument = 2.5f;
    g_allocation_count = 0;
    EclChildVm* first =
        EclVm_SpawnChild(&owner, (void*)0x1234, &argument, Allocate,
                         CaptureStart);
    assert(first != 0);
    assert(g_allocation_count == 2);
    assert(first->script == (void*)0x1234);
    assert(first->owner == &owner);
    assert(first->difficulty_mask == 3);
    assert(first->instruction_offset == 0);
    assert(first->wait_counter == 0);
    assert(owner.anchor.next != 0);
    assert(owner.anchor.next->vm == first);
    assert(owner.anchor.next->previous == &owner.anchor);
    assert(g_started_vm == &root);
    assert(g_started_argument == &argument);

    EclChildVm* second =
        EclVm_SpawnChild(&owner, (void*)0x5678, &argument, Allocate,
                         CaptureStart);
    assert(owner.anchor.next->vm == second);
    assert(owner.anchor.next->next->vm == first);
    assert(owner.anchor.next->next->previous == owner.anchor.next);

    // Tick: the root succeeds, then both children retire and are freed.
    g_tick_calls = 0;
    g_tick_failures_from = 2;  // calls 2 and 3 report completion
    g_free_count = 0;
    int result = EclVm_TickChildren(&owner, 1.0f, Tick, FreeMemory);
    assert(result == 0);
    assert(g_tick_calls == 3);
    assert(g_free_count == 4);  // two VMs and two links
    assert(owner.anchor.next == 0);
    assert(owner.active_vm == &root);

    // A failing root tick aborts the frame with -1.
    g_tick_calls = 0;
    g_tick_failures_from = 1;
    result = EclVm_TickChildren(&owner, 1.0f, Tick, FreeMemory);
    assert(result == -1);
}

// --- Manager lifecycle leaves --------------------------------------------------------

static int g_initialize_result;
static int InitializeScript(void* script_name) {
    (void)script_name;
    return g_initialize_result;
}

static int g_destroy_count;
static void Destroy(void* manager) {
    (void)manager;
    ++g_destroy_count;
}

static void TestEnemyManagerCreate() {
    void* global_slot = 0;
    g_initialize_result = 0;
    g_free_count = 0;
    void* manager = EnemyManager_Create((void*)"stage1.ecl", Allocate,
                                        &global_slot, InitializeScript,
                                        Destroy, FreeMemory);
    assert(manager != 0);
    assert(global_slot == manager);
    assert((((Word*)manager)[0] & 2u) != 0);
    for (int index = 1; index < 0x1A; ++index) {
        assert(((Word*)manager)[index] == 0);
    }
    FreeMemory(manager);

    // A failed script initializer destroys and frees the half-built manager.
    g_initialize_result = -1;
    g_destroy_count = 0;
    g_free_count = 0;
    manager = EnemyManager_Create((void*)"stage1.ecl", Allocate, &global_slot,
                                  InitializeScript, Destroy, FreeMemory);
    assert(manager == 0);
    assert(g_destroy_count == 1);
    assert(g_free_count == 1);
}

static int g_ascii_initialized;
static void InitializeAscii(void* manager) {
    (void)manager;
    ++g_ascii_initialized;
}

static void TestAsciiManagerCreate() {
    g_ascii_initialized = 0;
    void* manager = AsciiManager_Create(Allocate, InitializeAscii);
    assert(manager != 0);
    assert(g_ascii_initialized == 1);
    assert((((Word*)manager)[0] & 2u) != 0);
    for (int index = 1; index < 0x11; ++index) {
        assert(((Word*)manager)[index] == 0);
    }
    FreeMemory(manager);
}

static void* g_constructed_slots;
static int g_constructed_stride;
static int g_constructed_count;
static void ConstructSlots(void* slots, int stride, int count) {
    g_constructed_slots = slots;
    g_constructed_stride = stride;
    g_constructed_count = count;
}

static int g_stage_initialize_result;
static const char* g_stage_path;
static int InitializeStage(void* manager, const char* stage_path) {
    (void)manager;
    g_stage_path = stage_path;
    return g_stage_initialize_result;
}

static void TestStageManagerCreate() {
    g_stage_initialize_result = 0;
    void* manager = StageManager_Create("stage1.std", Allocate, ConstructSlots,
                                        InitializeStage, Destroy, FreeMemory);
    assert(manager != 0);
    assert(g_constructed_slots == (Word*)manager + 0x28);
    assert(g_constructed_stride == 0x24);
    assert(g_constructed_count == 8);
    assert(((Word*)manager)[4] == 2);
    assert(g_stage_path != 0 && std::strcmp(g_stage_path, "stage1.std") == 0);
    FreeMemory(manager);

    g_stage_initialize_result = -1;
    g_destroy_count = 0;
    g_free_count = 0;
    manager = StageManager_Create("stage2.std", Allocate, ConstructSlots,
                                  InitializeStage, Destroy, FreeMemory);
    assert(manager == 0);
    assert(g_destroy_count == 1);
    assert(g_free_count == 1);
}

static const Byte g_effect_table[4] = {1, 2, 3, 4};
static const Byte* LoadEffectTable(unsigned int* size_out) {
    *size_out = sizeof(g_effect_table);
    return g_effect_table;
}

static void* g_shared_block_seen;
static void InitializeShared(void* shared_block) {
    g_shared_block_seen = shared_block;
}

static void* g_pools_seen[7];
static int g_pools_initialized;
static void InitializePool(void* pool) {
    g_pools_seen[g_pools_initialized++] = pool;
}

static int g_finalized;
static void Finalize(void) { ++g_finalized; }

static void TestEffectManagerInitializePools() {
    static Word words[64];
    for (int index = 0; index < 64; ++index) words[index] = 0xFFFFFFFFu;
    static Byte pools[7 * 16];
    const Byte* table_slot = 0;
    g_pools_initialized = 0;
    g_finalized = 0;
    EffectManager_InitializePools(words, 64, LoadEffectTable, &table_slot,
                                  InitializeShared, words + 8, InitializePool,
                                  pools, 16, 7, Finalize);
    for (int index = 0; index < 64; ++index) assert(words[index] == 0);
    assert(table_slot == g_effect_table);
    assert(g_shared_block_seen == words + 8);
    assert(g_pools_initialized == 7);
    for (int index = 0; index < 7; ++index) {
        assert(g_pools_seen[index] == pools + index * 16);
    }
    assert(g_finalized == 1);
}

// --- Scheduler registration leaves -----------------------------------------------

static SchedulerCallbackNode g_nodes[4];
static void* g_node_callbacks[4];
static int g_nodes_created;
static SchedulerCallbackNode* CreateNode(void* callback) {
    g_nodes[g_nodes_created].flags = 0xFFFFFFFFu;
    g_nodes[g_nodes_created].owner = 0;
    g_node_callbacks[g_nodes_created] = callback;
    return &g_nodes[g_nodes_created++];
}

static int g_update_enqueued;
static void EnqueueUpdate(void* queue) {
    (void)queue;
    ++g_update_enqueued;
}

static int g_draw_enqueued;
static void EnqueueDraw(void* queue) {
    (void)queue;
    ++g_draw_enqueued;
}

static void* g_reset_timer_block;
static void ResetTimer(void* timer_block) { g_reset_timer_block = timer_block; }

static int g_preload_stamp;
static int g_preload_argument;
static void Preload(int frame_stamp, int argument) {
    g_preload_stamp = frame_stamp;
    g_preload_argument = argument;
}

static void TestEffectManagerOnRegister() {
    ManagerRegistration manager;
    std::memset(&manager, 0, sizeof(manager));
    static int timer_block;
    g_nodes_created = 0;
    g_update_enqueued = 0;
    g_draw_enqueued = 0;
    int result = EffectManager_OnRegister(
        &manager, 77, (void*)0x11, (void*)0x22, CreateNode, EnqueueUpdate,
        EnqueueDraw, 0, ResetTimer, &timer_block, Preload);
    assert(result == 0);
    assert(manager.frame_stamp == 77);
    assert(manager.stored_stamp == 77);
    assert(manager.update == &g_nodes[0]);
    assert(manager.draw == &g_nodes[1]);
    assert(g_node_callbacks[0] == (void*)0x11);
    assert(g_node_callbacks[1] == (void*)0x22);
    assert((g_nodes[0].flags & 2u) == 0);
    assert((g_nodes[1].flags & 2u) == 0);
    assert(g_nodes[0].owner == &manager);
    assert(g_update_enqueued == 1);
    assert(g_draw_enqueued == 1);
    assert(g_reset_timer_block == &timer_block);
    assert(g_preload_stamp == 77);
    assert(g_preload_argument == 0xC4);
}

static void* g_mounted_state;
static int g_mounted_bank;
static const char* g_mounted_name;
static void* g_mount_result;
static void* MountAnimation(int bank, void* state, const char* name) {
    g_mounted_bank = bank;
    g_mounted_state = state;
    g_mounted_name = name;
    return g_mount_result;
}

static int g_errors_reported;
static void ReportError(const char* message, const char* argument) {
    (void)message;
    (void)argument;
    ++g_errors_reported;
}

static void TestBulletManagerLeaves() {
    ManagerRegistration manager;
    std::memset(&manager, 0, sizeof(manager));
    void* animation_slot = 0;
    void* cursor = 0;
    static Word pool[8];
    unsigned short state_word = 0;
    static int state_manager;
    static int animation;

    g_mount_result = &animation;
    g_nodes_created = 0;
    g_update_enqueued = 0;
    g_draw_enqueued = 0;
    int result = BulletManager_OnRegister(
        &manager, &animation_slot, MountAnimation, &state_manager, ReportError,
        "mount failed", "bullet.anm", &cursor, pool, &state_word, (void*)0x11,
        (void*)0x22, CreateNode, EnqueueUpdate, EnqueueDraw, 0);
    assert(result == 0);
    assert(animation_slot == &animation);
    assert(g_mounted_bank == 7);
    assert(g_mounted_state == &state_manager);
    assert(std::strcmp(g_mounted_name, "bullet.anm") == 0);
    assert(cursor == pool);
    assert(state_word == 5);
    assert(g_update_enqueued == 1 && g_draw_enqueued == 1);

    // A failed mount reports the error and aborts.
    g_mount_result = 0;
    g_errors_reported = 0;
    result = BulletManager_OnRegister(
        &manager, &animation_slot, MountAnimation, &state_manager, ReportError,
        "mount failed", "bullet.anm", &cursor, pool, &state_word, (void*)0x11,
        (void*)0x22, CreateNode, EnqueueUpdate, EnqueueDraw, 0);
    assert(result == -1);
    assert(g_errors_reported == 1);

    // Pool reset: rebind, zero, re-arm.
    for (int index = 0; index < 8; ++index) pool[index] = 0xFFFFFFFFu;
    cursor = 0;
    state_word = 0;
    BulletManager_ResetPool(0, 0, 0, pool, 8, &cursor, pool, &state_word);
    for (int index = 0; index < 8; ++index) assert(pool[index] == 0);
    assert(cursor == pool);
    assert(state_word == 5);
}

// --- Enemy, boss, and UI leaves ------------------------------------------------------

static float NormalizeAngle(float angle, float quarter_turn) {
    (void)quarter_turn;
    return angle - 6.2831855f;
}

static int g_dirty_marks;
static void MarkDirty(void* state) {
    (void)state;
    ++g_dirty_marks;
}

static void TestEnemyListSyncHitboxes() {
    HitboxEnemy second;
    std::memset(&second, 0, sizeof(second));
    second.position.x = 10.0f;
    second.position.y = 20.0f;
    second.position.z = 30.0f;

    HitboxEnemy first;
    std::memset(&first, 0, sizeof(first));
    first.position.x = 1.0f;
    first.position.y = 2.0f;
    first.position.z = 3.0f;
    first.flags = 0x8000000u;
    first.facing_angle = 7.0f;
    first.next = &second;

    g_dirty_marks = 0;
    int result = EnemyList_SyncHitboxes(&first, 100.0f, 200.0f, NormalizeAngle,
                                        MarkDirty, 0);
    assert(result == 1);
    assert(first.hitbox.x == 101.0f);
    assert(first.hitbox.y == 202.0f);
    assert(first.hitbox.z == 3.0f);
    assert(first.sprite_angle == 7.0f - 6.2831855f);
    assert((first.flags & 4u) != 0);
    assert(second.hitbox.x == 110.0f);
    assert(second.hitbox.y == 220.0f);
    assert((second.flags & 4u) == 0);  // no pending-rotation flag
    assert(g_dirty_marks == 2);
}

static void TestBossSyncOverlayPositions() {
    BossVec3 position = {5.0f, 6.0f, 7.0f};
    BossVec3 primary = {0, 0, 0};
    BossVec3 secondary = {0, 0, 0};
    float sprite_angle = 0.0f;
    unsigned int sprite_flags = 0;

    g_dirty_marks = 0;
    Boss_SyncOverlayPositions(&position, 7.0f, 1.0f, 0.0f, 100.0f, 200.0f,
                              &primary, &sprite_angle, &sprite_flags,
                              &secondary, NormalizeAngle, MarkDirty, 0);
    assert(primary.x == 105.0f && primary.y == 206.0f && primary.z == 7.0f);
    assert(sprite_angle == 7.0f - 6.2831855f);
    assert(sprite_flags == 4u);
    assert(secondary.x == 0.0f);  // marker != sentinel
    assert(g_dirty_marks == 1);

    Boss_SyncOverlayPositions(&position, 7.0f, 0.0f, 0.0f, 100.0f, 200.0f,
                              &primary, &sprite_angle, &sprite_flags,
                              &secondary, NormalizeAngle, MarkDirty, 0);
    assert(secondary.x == 105.0f && secondary.y == 206.0f);
    assert(g_dirty_marks == 3);
}

static int g_gauge_released;
static void ReleaseGauge(void) { ++g_gauge_released; }

static int g_marker_released_index;
static void ReleaseMarker(int marker_index) {
    g_marker_released_index = marker_index;
}

static void* g_popup_zone_seen;
static int g_popup_count_seen;
static void SpawnPopup(void* zone, int count) {
    g_popup_zone_seen = zone;
    g_popup_count_seen = count;
}

static int* g_flushed_counter;
static void FlushPopups(int* count) { g_flushed_counter = count; }

static int g_stage_timer_frames;
static void SetStageTimer(int frames) { g_stage_timer_frames = frames; }

static void TestBossUiReleaseIndicators() {
    int popup_count = 3;
    static int popup_zone;
    g_gauge_released = 0;
    g_marker_released_index = -1;
    int result = BossUi_ReleaseIndicators(0, 1, 2, &popup_count, &popup_zone,
                                          ReleaseGauge, ReleaseMarker,
                                          SpawnPopup, FlushPopups,
                                          SetStageTimer);
    assert(result == 1);
    assert(g_gauge_released == 1);
    assert(g_marker_released_index == 2);
    assert(g_popup_zone_seen == &popup_zone);
    assert(g_popup_count_seen == 3);
    assert(g_flushed_counter == &popup_count);
    assert(popup_count == 0);
    assert(g_stage_timer_frames == 10);

    // Disarmed slots and empty popups do nothing.
    g_gauge_released = 0;
    g_marker_released_index = -1;
    g_popup_count_seen = -1;
    BossUi_ReleaseIndicators(-1, -1, 2, &popup_count, &popup_zone,
                             ReleaseGauge, ReleaseMarker, SpawnPopup,
                             FlushPopups, SetStageTimer);
    assert(g_gauge_released == 0);
    assert(g_marker_released_index == -1);
    assert(g_popup_count_seen == -1);
}

// --- Render and platform leaves --------------------------------------------------------

static int g_camera_applied;
static void ApplyCamera(void) { ++g_camera_applied; }

static const void* g_viewport_seen;
static void SetViewport(const void* viewport) { g_viewport_seen = viewport; }

static void TestGameThreadSelectRenderStage() {
    static RenderStage stages[3];
    RenderStage* active = 0;
    int active_index = -1;
    g_camera_applied = 0;
    GameThread_SelectRenderStage(stages, 2, &active, &active_index,
                                 ApplyCamera, SetViewport);
    assert(active == &stages[2]);
    assert(active_index == 2);
    assert(g_camera_applied == 1);
    assert(g_viewport_seen == stages[2].viewport);
}

static int g_release_previous_count;
static void* g_released_handle;
static void ReleasePrevious(void* handle) {
    g_released_handle = handle;
    ++g_release_previous_count;
}

static void* MountTexture(int bank, void* state, const char* name) {
    g_mounted_bank = bank;
    g_mounted_state = state;
    g_mounted_name = name;
    return g_mount_result;
}

static void TestStageBackgroundRebindTexture() {
    static char name_buffer[64];
    std::memset(name_buffer, 'x', sizeof(name_buffer));
    void* slot_table[8] = {0};
    unsigned int busy_flags = 0xFFFFFFFFu;
    int pending = 55;
    static int state_manager;
    static int handle;
    static int previous;

    g_mount_result = &handle;
    g_release_previous_count = 0;
    int result = StageBackground_RebindTexture(
        "stgbg.anm", name_buffer, 3, slot_table, &busy_flags, &state_manager,
        MountTexture, &previous, ReleasePrevious, &pending);
    assert(result == 0);
    assert(std::strcmp(name_buffer, "stgbg.anm") == 0);
    assert(g_mounted_bank == 3 + 0x1D);
    assert(g_mounted_state == &state_manager);
    assert(g_mounted_name == name_buffer);
    assert(slot_table[3] == &handle);
    assert((busy_flags & 4u) == 0);
    assert(g_release_previous_count == 1);
    assert(g_released_handle == &previous);
    assert(pending == 0);
}

static int g_entries_loaded;
static int g_load_result;
static int g_loaded_x;
static int g_loaded_y;
static AnmArchiveEntry* g_loaded_entry;
static int LoadEntry(void* context, AnmCursorOwner* owner, int offset_x,
                     int offset_y, AnmArchiveEntry* entry) {
    (void)context;
    (void)owner;
    ++g_entries_loaded;
    g_loaded_x = offset_x;
    g_loaded_y = offset_y;
    g_loaded_entry = entry;
    return g_load_result;
}

static void TestAnmArchiveAdvanceScriptCursor() {
    // Chain of three entries laid out back to back.
    static AnmArchiveEntry entries[3];
    std::memset(entries, 0, sizeof(entries));
    entries[0].width = 32;
    entries[0].height = 16;
    entries[0].next_offset = (int)sizeof(AnmArchiveEntry);
    entries[1].width = 64;
    entries[1].height = 8;
    entries[1].next_offset = (int)sizeof(AnmArchiveEntry);
    entries[2].width = 128;
    entries[2].height = 4;
    entries[2].next_offset = 0;

    AnmCursorOwner owner;
    owner.entries = entries;
    owner.cursor = 2;

    // Cursor 2 loads entry index 1 at the offsets accumulated past entry 0.
    g_entries_loaded = 0;
    g_load_result = 0;
    AnmCursorOwner* result =
        AnmArchive_AdvanceScriptCursor(0, &owner, LoadEntry);
    assert(result == &owner);
    assert(g_entries_loaded == 1);
    assert(g_loaded_entry == &entries[1]);
    assert(g_loaded_x == 32);
    assert(g_loaded_y == 16);
    assert(owner.cursor == 3);

    // A failed load resets the cursor and reports null.
    owner.cursor = 2;
    g_load_result = -1;
    result = AnmArchive_AdvanceScriptCursor(0, &owner, LoadEntry);
    assert(result == 0);
    assert(owner.cursor == 0);

    // Walking off the end of the chain wraps the cursor back to zero.
    owner.cursor = 9;
    g_load_result = 0;
    g_entries_loaded = 0;
    result = AnmArchive_AdvanceScriptCursor(0, &owner, LoadEntry);
    assert(result == &owner);
    assert(owner.cursor == 0);
    assert(g_entries_loaded == 0);
}

static const unsigned int g_format_table[8] = {0x15, 0x14, 9, 3, 8, 5, 0, 7};
static const unsigned int g_pitch_table[8] = {4, 2, 4, 2, 2, 2, 4, 3};

static unsigned int g_created_format;
static int g_create_result;
static int CreateTexture(unsigned int format) {
    g_created_format = format;
    return g_create_result;
}

static int g_surface_storage;
static int GetSurface(void** surface_out) {
    *surface_out = &g_surface_storage;
    return 0;
}

static const Byte* g_uploaded_pixels;
static unsigned int g_uploaded_format;
static unsigned int g_uploaded_pitch;
static int LoadSurface(void* surface, const Byte* pixels,
                       unsigned int source_format, unsigned int pitch) {
    (void)surface;
    g_uploaded_pixels = pixels;
    g_uploaded_format = source_format;
    g_uploaded_pitch = pitch;
    return 0;
}

static int g_surface_released;
static void ReleaseSurface(void* surface) {
    (void)surface;
    ++g_surface_released;
}

static int g_texture_released;
static void ReleaseTexture(void) { ++g_texture_released; }

static int g_borders_repaired;
static void RepairBorders(void) { ++g_borders_repaired; }

static int g_file_loads;
static int LoadSurfaceFromFile(void* surface) {
    (void)surface;
    ++g_file_loads;
    return 0;
}

static void TestAnmTextureLeaves() {
    AnmImage image;
    std::memset(&image, 0, sizeof(image));
    image.format = 2;  // source format 9, pitch 4
    image.width = 16;
    image.height = 8;
    static Byte pixels[16];
    unsigned int slot_pitch = 0;

    // The 16-bit fallback downgrades format index 0 (0x15) to index 5.
    g_create_result = 0;
    g_surface_released = 0;
    int result = AnmTexture_CreateAndUpload(
        &image, pixels, 0, 1, g_format_table, g_pitch_table, &slot_pitch,
        CreateTexture, GetSurface, LoadSurface, ReleaseSurface,
        ReleaseTexture);
    assert(result == 0);
    assert(g_created_format == g_format_table[5]);
    assert(g_uploaded_pixels == pixels);
    assert(g_uploaded_format == 9);
    assert(g_uploaded_pitch == 16u * 4u);
    assert(slot_pitch == g_pitch_table[5]);
    assert(g_surface_released == 1);

    // A failed creation releases the texture argument and reports -1.
    g_create_result = -1;
    g_texture_released = 0;
    result = AnmTexture_CreateAndUpload(
        &image, pixels, 2, 0, g_format_table, g_pitch_table, &slot_pitch,
        CreateTexture, GetSurface, LoadSurface, ReleaseSurface,
        ReleaseTexture);
    assert(result == -1);
    assert(g_texture_released == 1);

    // Raw upload into an existing texture repairs borders afterwards.
    g_surface_released = 0;
    g_borders_repaired = 0;
    slot_pitch = 0;
    result = AnmTexture_UploadSurface(
        &image, pixels, 1, 0, 1, g_format_table, g_pitch_table, &slot_pitch,
        GetSurface, LoadSurfaceFromFile, LoadSurface, ReleaseSurface,
        RepairBorders);
    assert(result == 0);
    assert(g_uploaded_format == 9);
    assert(slot_pitch == g_pitch_table[3]);  // 0x14 downgrades to index 3
    assert(g_surface_released == 1);
    assert(g_borders_repaired == 1);

    // File-backed images upload through the file-in-memory path.
    g_file_loads = 0;
    result = AnmTexture_UploadSurface(
        &image, pixels, 2, 1, 0, g_format_table, g_pitch_table, &slot_pitch,
        GetSurface, LoadSurfaceFromFile, LoadSurface, ReleaseSurface,
        RepairBorders);
    assert(result == 0);
    assert(g_file_loads == 1);
    assert(slot_pitch == g_pitch_table[2]);
}

// --- MIDI worker loop --------------------------------------------------------------

static MidiWorker g_midi_worker;
static MidiWorker* g_midi_slot;
static unsigned int g_wait_script[8];
static int g_wait_calls;
static unsigned int WaitScript(void) { return g_wait_script[g_wait_calls++]; }

static unsigned int g_message_script[8];
static int g_message_count;
static int g_message_cursor;
static int PeekMessageScript(unsigned int* message_out) {
    if (g_message_cursor >= g_message_count) return 0;
    *message_out = g_message_script[g_message_cursor++];
    return 1;
}

static int g_serviced;
static void ServiceWorker(MidiWorker* worker) {
    ++g_serviced;
    assert(worker->busy == 1);
}

static void TestMidiWorkerMessageLoop() {
    // Event signal services the streaming worker, then a 0x12 message quits.
    g_midi_worker.streaming = 1;
    g_midi_worker.busy = 0;
    g_midi_slot = &g_midi_worker;
    g_wait_calls = 0;
    g_wait_script[0] = 0;  // service
    g_wait_script[1] = 1;  // drain messages, hit quit
    g_message_script[0] = 7;
    g_message_script[1] = 0x12;
    g_message_count = 2;
    g_message_cursor = 0;
    g_serviced = 0;
    int result = MidiWorker_MessageLoop(&g_midi_slot, WaitScript,
                                        PeekMessageScript, ServiceWorker);
    assert(result == 0);
    assert(g_serviced == 1);
    assert(g_midi_worker.busy == 0);
    assert(g_wait_calls == 2);

    // A cleared worker slot ends the loop after one wait.
    g_midi_slot = 0;
    g_wait_calls = 0;
    g_wait_script[0] = 0;
    result = MidiWorker_MessageLoop(&g_midi_slot, WaitScript,
                                    PeekMessageScript, ServiceWorker);
    assert(result == 0);
    assert(g_wait_calls == 1);
}

int main() {
    TestLegacyStringFunclets();
    TestForwardLeaves();
    TestPlayerWrap();
    TestEffectPoolUpdateDrops();
    TestPlayerAnimationAdvanceFrame();
    TestEclChildVmLeaves();
    TestEnemyManagerCreate();
    TestAsciiManagerCreate();
    TestStageManagerCreate();
    TestEffectManagerInitializePools();
    TestEffectManagerOnRegister();
    TestBulletManagerLeaves();
    TestEnemyListSyncHitboxes();
    TestBossSyncOverlayPositions();
    TestBossUiReleaseIndicators();
    TestGameThreadSelectRenderStage();
    TestStageBackgroundRebindTexture();
    TestAnmArchiveAdvanceScriptCursor();
    TestAnmTextureLeaves();
    TestMidiWorkerMessageLoop();
    return 0;
}
