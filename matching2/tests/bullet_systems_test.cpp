#include "th10/app/fps_counter.hpp"
#include "th10/game/ascii_overlay_callbacks.hpp"
#include "th10/game/bullet_manager.hpp"
#include "th10/game/enemy_grid_scan.hpp"
#include "th10/game/enemy_lifecycle.hpp"
#include "th10/game/key_config.hpp"
#include "th10/game/main_menu_dispatch.hpp"
#include "th10/game/manager_factories.hpp"
#include "th10/game/music_room.hpp"
#include "th10/game/player_motion.hpp"
#include "th10/game/replay_progress.hpp"
#include "th10/platform/sound_event_queue.hpp"
#include "th10/platform/sound_stream_thread.hpp"
#include "th10/render/anm_pending_service.hpp"
#include "th10/render/rect_fan_draw.hpp"
#include "th10/script/script_text_reader.hpp"
#include "th10/util/scalars.hpp"

#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <cstring>

// Retail globals consumed by the linked manager/scheduler/entity sources.
uint32_t DAT_00491be4 = 0;
uint32_t DAT_00492274 = 0;
uint32_t DAT_004776f4 = 0;
uint32_t DAT_0047770c = 0;
uint32_t DAT_00477810 = 0;
uint32_t DAT_00474e36 = 0;
uint32_t DAT_00491ff4 = 0;
uint32_t DAT_00474ca0 = 0;
uint32_t DAT_00476f78 = 0;
unsigned char DAT_0049231c = 0;
void* g_pGameStateManager = 0;
float DAT_00470b04 = 0.0f;
float DAT_00470b0c = 1.0f;
float _DAT_00470b64 = 1.01f;
float _DAT_00470b68 = 0.99f;
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

int* ResourceManager_FindResource(int, void*, const char*) {
    return 0;
}

// --- Shared scaffolding ------------------------------------------------------

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

static float g_clock_control;

static PlayerDeathClock MakeClock(int frame, float timer) {
    PlayerDeathClock clock;
    clock.previous = -1;
    clock.frame = frame;
    clock.timer = timer;
    clock.control = &g_clock_control;
    return clock;
}

// --- 0x004073E0 EnemyGrid_ScanCells --------------------------------------------

static float g_atan_y;
static float g_atan_x;
static float ArcTangent(float delta_y, float delta_x) {
    g_atan_y = delta_y;
    g_atan_x = delta_x;
    return 0.25f;
}

static int g_cells_visited;
static float g_cell_angle;
static int g_abort_after;
static int VisitCell(int column, int row, float aim_angle, void* context) {
    (void)column;
    (void)row;
    (void)context;
    g_cell_angle = aim_angle;
    ++g_cells_visited;
    return g_abort_after != 0 && g_cells_visited >= g_abort_after ? 1 : 0;
}

static int g_events_recorded;
static void RecordEvent(void) { ++g_events_recorded; }

static void TestEnemyGridScanCells() {
    g_cells_visited = 0;
    g_abort_after = 0;
    g_events_recorded = 0;
    int result = EnemyGrid_ScanCells(10.0f, 8.0f, 4.0f, 5.0f, 3, 2, 0x200u,
                                     ArcTangent, VisitCell, 0, RecordEvent);
    assert(result == 0);
    assert(g_cells_visited == 6);
    assert(g_atan_y == 3.0f && g_atan_x == 6.0f);
    assert(g_cell_angle == 0.25f);
    assert(g_events_recorded == 1);

    // Coincident player: quarter-turn fallback. Abort stops the scan early.
    g_cells_visited = 0;
    g_abort_after = 2;
    EnemyGrid_ScanCells(4.0f, 5.0f, 4.0f, 5.0f, 3, 2, 0, ArcTangent,
                        VisitCell, 0, RecordEvent);
    assert(g_cells_visited == 2);
    assert(g_cell_angle == 1.5707964f);
    assert(g_events_recorded == 1);
}

// --- Manager factories -----------------------------------------------------------

static int g_constructed;
static void* Construct(void* memory) {
    ++g_constructed;
    return memory;
}

static int g_initialize_result;
static int Initialize(void) { return g_initialize_result; }

static int g_destroyed;
static void Destroy(void* manager) {
    (void)manager;
    ++g_destroyed;
}

static void TestConstructedFactories() {
    g_initialize_result = 0;
    g_constructed = 0;
    void* manager = PlayerManager_Create(Allocate, Construct, Initialize,
                                         Destroy, FreeMemory);
    assert(manager != 0);
    assert(g_constructed == 1);
    FreeMemory(manager);

    manager = ItemManager_Create(Allocate, Construct, Initialize, Destroy,
                                 FreeMemory);
    assert(manager != 0);
    FreeMemory(manager);

    // Initializer failure destroys and frees.
    g_initialize_result = -1;
    g_destroyed = 0;
    g_free_count = 0;
    manager = PlayerManager_Create(Allocate, Construct, Initialize, Destroy,
                                   FreeMemory);
    assert(manager == 0);
    assert(g_destroyed == 1);
    assert(g_free_count == 1);
}

static void* g_slots_constructed;
static int g_slots_stride;
static int g_slots_count;
static void ConstructSlots(void* slots, int stride, int count) {
    g_slots_constructed = slots;
    g_slots_stride = stride;
    g_slots_count = count;
}

static void TestPooledFactories() {
    void* global_slot = 0;
    g_initialize_result = 0;
    void* manager = BulletManager_Create(Allocate, ConstructSlots,
                                         &global_slot, Initialize, Destroy,
                                         FreeMemory);
    assert(manager != 0);
    assert(global_slot == manager);
    assert(g_slots_constructed == (Word*)manager + 0x18);
    assert(g_slots_stride == 0x7F0 && g_slots_count == 0x7D1);
    assert(((Word*)manager)[0] == 0);
    assert(((Word*)manager)[0xF82D4] == 0);
    FreeMemory(manager);

    manager = EffectManager_Create(Allocate, ConstructSlots, &global_slot,
                                   Initialize, Destroy, FreeMemory);
    assert(manager != 0);
    assert(g_slots_constructed == (Word*)manager + 5);
    assert(g_slots_stride == 0x3F0 && g_slots_count == 0x896);
    assert((((Word*)manager)[0] & 2u) != 0);
    assert(global_slot == manager);
    FreeMemory(manager);

    g_initialize_result = -1;
    g_destroyed = 0;
    g_free_count = 0;
    manager = EffectManager_Create(Allocate, ConstructSlots, &global_slot,
                                   Initialize, Destroy, FreeMemory);
    assert(manager == 0);
    assert(g_destroyed == 1 && g_free_count == 1);
}

static const char* g_script_seen;
static int InitializeScript(const char* script_path) {
    g_script_seen = script_path;
    return g_initialize_result;
}

static void TestStageManagerCreateFromScript() {
    g_initialize_result = 0;
    void* manager = StageManager_CreateFromScript(
        "stage3.std", Allocate, ConstructSlots, InitializeScript, Destroy,
        FreeMemory);
    assert(manager != 0);
    assert(g_script_seen != 0 && std::strcmp(g_script_seen, "stage3.std") == 0);
    assert(g_slots_constructed == (Word*)manager + 0x28);
    assert(g_slots_stride == 0x24 && g_slots_count == 8);
    for (int index = 0; index < 0xB5; ++index) {
        assert(((Word*)manager)[index] == 0);
    }
    FreeMemory(manager);
}

// --- 0x0040E6A0 EnemyList_MarkDeadForCapture -------------------------------------

static void* g_notified[4];
static int g_notify_count;
static void Notify(void* handler) { g_notified[g_notify_count++] = handler; }

static void TestEnemyListMarkDeadForCapture() {
    static int handler_a, handler_b;
    void* handlers[2] = {&handler_a, &handler_b};

    CaptureEnemy plain = {0, 0, 1};          // unprotected, has drop
    CaptureEnemy shielded = {0x4000u, 0, 0}; // protected state
    CaptureEnemy marked = {0x4080u, -1, 0};  // protected but marked, no drop

    CaptureNode third = {&marked, 0};
    CaptureNode second = {&shielded, &third};
    CaptureNode first = {&plain, &second};

    PlayerDeathClock clock = MakeClock(5, 5.0f);
    g_clock_control = 1.0f;
    g_notify_count = 0;
    EnemyList_MarkDeadForCapture(&first, handlers, Notify, &clock, 0.5f, 1.5f,
                                 1.0f, TruncateFloat);
    assert(g_notify_count == 1);
    assert(g_notified[0] == &handler_b);
    assert((plain.flags & 0x20000u) != 0);
    assert((shielded.flags & 0x20000u) == 0);
    assert((marked.flags & 0x20000u) != 0);
    assert(clock.previous == 5 && clock.frame == 6 && clock.timer == 6.0f);

    // Fast control path re-derives the frame by truncation.
    g_clock_control = 4.0f;
    clock = MakeClock(6, 6.25f);
    EnemyList_MarkDeadForCapture(0, handlers, Notify, &clock, 0.5f, 1.5f, 1.0f,
                                 TruncateFloat);
    assert(clock.timer == 10.25f && clock.frame == 10);
}

// --- 0x004223F0 MainMenu_DispatchState --------------------------------------------

static int g_menu_opened;
static void OpenGameMenu(void* context) {
    (void)context;
    ++g_menu_opened;
}

static int g_pause_ran;
static void RunPauseMenu(void* context) {
    (void)context;
    ++g_pause_ran;
}

static int g_sub_ran;
static void RunSubMenu(void* context) {
    (void)context;
    ++g_sub_ran;
}

static void TestMainMenuDispatchState() {
    PlayerDeathClock clock = MakeClock(1, 1.0f);
    g_clock_control = 1.0f;
    g_menu_opened = 0;
    g_pause_ran = 0;
    g_sub_ran = 0;

    int result = MainMenu_DispatchState(0, 0, 0, 1, 1, 0x1E, OpenGameMenu,
                                        RunPauseMenu, RunSubMenu, &clock,
                                        0.5f, 1.5f, 1.0f, TruncateFloat);
    assert(result == 1);
    assert(g_menu_opened == 1);
    assert(clock.frame == 2);

    // Too-early frame, missing input, or config suppression keep the demo.
    MainMenu_DispatchState(0, 0, 0, 1, 1, 0x1D, OpenGameMenu, RunPauseMenu,
                           RunSubMenu, &clock, 0.5f, 1.5f, 1.0f,
                           TruncateFloat);
    MainMenu_DispatchState(0, 0, 1, 1, 1, 0x1E, OpenGameMenu, RunPauseMenu,
                           RunSubMenu, &clock, 0.5f, 1.5f, 1.0f,
                           TruncateFloat);
    assert(g_menu_opened == 1);

    MainMenu_DispatchState(0, 3, 0, 0, 0, 0, OpenGameMenu, RunPauseMenu,
                           RunSubMenu, &clock, 0.5f, 1.5f, 1.0f,
                           TruncateFloat);
    assert(g_pause_ran == 1);
    MainMenu_DispatchState(0, 0xD, 0, 0, 0, 0, OpenGameMenu, RunPauseMenu,
                           RunSubMenu, &clock, 0.5f, 1.5f, 1.0f,
                           TruncateFloat);
    assert(g_sub_ran == 1);
}

// --- 0x00430250 KeyConfig_ReassignSlot ----------------------------------------------

static int g_changed_slot;
static int g_change_count;
static void OnChanged(int slot_index) {
    g_changed_slot = slot_index;
    ++g_change_count;
}

static void* g_sound_block_seen;
static int g_sound_index;
static int g_sounds_played;
static void PlaySound(void* sound_block, int index) {
    g_sound_block_seen = sound_block;
    g_sound_index = index;
    ++g_sounds_played;
}

static void TestKeyConfigReassignSlot() {
    short slots[5] = {10, 20, 30, 40, 50};
    static int sound_block;
    g_change_count = 0;
    g_sounds_played = 0;

    // Assigning slot 2 the key held by slot 0 swaps the two bindings.
    KeyConfig_ReassignSlot(slots, 2, 10, OnChanged, &sound_block, PlaySound);
    assert(slots[2] == 10);
    assert(slots[0] == 30);
    assert(slots[1] == 20 && slots[3] == 40 && slots[4] == 50);
    assert(g_change_count == 1 && g_changed_slot == 2);
    assert(g_sounds_played == 1);
    assert(g_sound_block_seen == &sound_block && g_sound_index == 0);

    // Re-assigning the same key is a no-op.
    KeyConfig_ReassignSlot(slots, 2, 10, OnChanged, &sound_block, PlaySound);
    assert(g_change_count == 1 && g_sounds_played == 1);
}

// --- 0x00447700 AnmArchive_ServicePending -------------------------------------------

static AnmPendingEntry* g_advanced_entry;
static int g_advance_result;
static int Advance(void* context, AnmPendingEntry* entry) {
    (void)context;
    g_advanced_entry = entry;
    return g_advance_result;
}

static int g_discarded;
static void Discard(AnmPendingEntry* entry) {
    (void)entry;
    ++g_discarded;
}

static void TestAnmArchiveServicePending() {
    AnmPendingEntry* pending =
        (AnmPendingEntry*)std::malloc(sizeof(AnmPendingEntry));
    pending->script = 0;
    pending->pending = 1;
    AnmPendingEntry resumable = {0x1234, 0};
    AnmPendingEntry idle = {0, 0};

    AnmPendingEntry* slots[4] = {0, pending, &idle, &resumable};
    g_discarded = 0;
    g_free_count = 0;
    g_advance_result = 1;
    int result = AnmArchive_ServicePending(0, slots, 4, Advance, Discard,
                                           FreeMemory);
    assert(result == 0);
    assert(g_discarded == 1 && g_free_count == 1);
    assert(slots[1] == 0);
    assert(g_advanced_entry == &resumable);

    // A failed advance reports -1.
    g_advance_result = 0;
    AnmPendingEntry* slots2[1] = {&resumable};
    result = AnmArchive_ServicePending(0, slots2, 1, Advance, Discard,
                                       FreeMemory);
    assert(result == -1);
}

// --- 0x00447AE0 AsciiOverlay_FormatShadowed ------------------------------------------

static void* g_font_seen;
static int g_centered_offset;
static Word g_submit_color;
static Word g_submit_shadow;
static void Submit(void* font_page, int centered_offset, Word color,
                   Word shadow_flag) {
    g_font_seen = font_page;
    g_centered_offset = centered_offset;
    g_submit_color = color;
    g_submit_shadow = shadow_flag;
}

static void TestAsciiOverlayFormatShadowed() {
    char buffer[128];
    static int font_page;
    Word dirty = 0;
    AsciiOverlay_FormatShadowed(buffer, sizeof(buffer), 0, &font_page, 3u,
                                &dirty, 0xFF00FF00u, Submit, "%d pts", 1500);
    assert(std::strcmp(buffer, "1500 pts") == 0);
    assert(g_font_seen == &font_page);
    assert(g_centered_offset == (0x11 - 1) * 8 / 2);
    assert(g_submit_color == 0xFF00FF00u);
    assert(g_submit_shadow == 1u);  // only bit 0 survives
    assert(dirty == 1u);

    // A non-zero column byte overrides the default width.
    AsciiOverlay_FormatShadowed(buffer, sizeof(buffer), 9, &font_page, 0u,
                                &dirty, 0u, Submit, "ab");
    assert(g_centered_offset == (9 - 1) * 2 / 2);
    assert(g_submit_shadow == 0u);
}

// --- 0x00404450 BulletManager_ActivateSprites ----------------------------------------

static int g_sprites_registered;
static void* g_sprite_pool_seen;
static void RegisterSprite(void* pool) {
    g_sprite_pool_seen = pool;
    ++g_sprites_registered;
}

static void TestBulletManagerActivateSprites() {
    // One bank with two records, one bank with one record.
    unsigned char bank_a_storage[0x1C + 3 * sizeof(BulletSpriteRecord)];
    unsigned char bank_b_storage[0x1C + 2 * sizeof(BulletSpriteRecord)];
    std::memset(bank_a_storage, 0, sizeof(bank_a_storage));
    std::memset(bank_b_storage, 0, sizeof(bank_b_storage));
    BulletSpriteBank* bank_a = (BulletSpriteBank*)bank_a_storage;
    BulletSpriteBank* bank_b = (BulletSpriteBank*)bank_b_storage;

    bank_a->records[0].id = 7;
    bank_a->records[0].stride = sizeof(BulletSpriteRecord);
    bank_a->records[1].id = 8;
    bank_a->records[1].stride = sizeof(BulletSpriteRecord);
    bank_a->records[2].id = -1;
    bank_b->records[0].id = 9;
    bank_b->records[0].stride = sizeof(BulletSpriteRecord);
    bank_b->records[1].id = -1;

    short bank_count = 2;
    BulletSpriteBank* banks[2] = {bank_a, bank_b};
    BulletSchedulerNode update = {0}, draw = {0}, overlay = {0};
    static int pool, pool_base;

    BulletHost host;
    host.bank_count = &bank_count;
    host.banks = banks;
    host.update = &update;
    host.draw = &draw;
    host.overlay = &overlay;
    host.sprite_pool = &pool;
    host.cursor = 0;
    host.pool_base = &pool_base;

    g_sprites_registered = 0;
    BulletManager_ActivateSprites(&host, RegisterSprite);
    assert(update.flags == 2u && draw.flags == 2u && overlay.flags == 2u);
    assert(bank_a->active == 1 && bank_b->active == 1);
    assert(g_sprites_registered == 3);
    assert(g_sprite_pool_seen == &pool);
    assert(bank_a->records[0].assigned == 0);
    assert(bank_a->records[1].assigned == 1);
    assert(bank_b->records[0].assigned == 2);
    assert(host.cursor == &pool_base);
}

// --- 0x004076A0 Player_DeathShrink -----------------------------------------------------

static float ApproachZero(float value, float step) {
    if (value > step) return value - step;
    return 0.0f;
}

static float g_hitbox_radius;
static float g_hitbox_y;
static int g_hitbox_moves;
static void MoveHitbox(void* hitbox, float radius, float y) {
    (void)hitbox;
    g_hitbox_radius = radius;
    g_hitbox_y = y;
    ++g_hitbox_moves;
}

static void TestPlayerDeathShrink() {
    PlayerDeathClock clock = MakeClock(3, 3.0f);
    g_clock_control = 1.0f;
    float radius = 10.0f;
    float fall_y = 100.0f;
    Word status = 0xFFu;
    g_hitbox_moves = 0;

    Player_DeathShrink(&clock, 8, &radius, &fall_y, 2.0f, 3.0f, 1.0f, &status,
                       0, ApproachZero, MoveHitbox, 0.5f, 1.5f, 1.0f,
                       TruncateFloat);
    assert(radius == 8.0f);
    assert(fall_y == 103.0f);
    assert(g_hitbox_moves == 1);
    assert(g_hitbox_radius == 8.0f && g_hitbox_y == 103.0f);
    assert(status == 0xFFu);
    assert(clock.frame == 4);

    // Past the deadline the shrink bit clears and nothing moves.
    clock = MakeClock(8, 8.0f);
    Player_DeathShrink(&clock, 8, &radius, &fall_y, 2.0f, 3.0f, 1.0f, &status,
                       0, ApproachZero, MoveHitbox, 0.5f, 1.5f, 1.0f,
                       TruncateFloat);
    assert(g_hitbox_moves == 1);
    assert(status == (0xFFu & ~0x20u));
}

// --- 0x0040D750 EnemyList_TickInterpolators ---------------------------------------------

static int g_interp_result;
static int g_interp_steps;
static int StepInterpolator(void* interpolator) {
    (void)interpolator;
    ++g_interp_steps;
    return g_interp_result;
}

static InterpEnemy* g_retired_enemy;
static int g_retire_mode;
static int g_retired_count;
static void Retire(InterpEnemy* enemy, int mode) {
    g_retired_enemy = enemy;
    g_retire_mode = mode;
    ++g_retired_count;
}

static void TestEnemyListTickInterpolators() {
    static int interp_a, interp_b;
    InterpEnemy running = {0x400u, &interp_a};
    InterpEnemy captured = {0x20000u | 0x400u, &interp_b};

    InterpNode second = {&captured, 0};
    InterpNode first = {&running, &second};

    PlayerDeathClock clock = MakeClock(2, 2.0f);
    g_clock_control = 1.0f;
    g_interp_result = 0;
    g_interp_steps = 0;
    g_retired_count = 0;
    int result = EnemyList_TickInterpolators(&first, StepInterpolator, Retire,
                                             &clock, 0.5f, 1.5f, 1.0f,
                                             TruncateFloat);
    assert(result == 1);
    assert(g_interp_steps == 1);  // captured enemy skips the step
    assert((running.flags & 0x400u) == 0);
    assert(g_retired_count == 1);  // captured enemy retires
    assert(g_retired_enemy == &captured && g_retire_mode == 1);
    assert(clock.frame == 3);

    // An unfinished interpolator also retires the enemy.
    running.flags = 0x400u;
    InterpNode solo = {&running, 0};
    g_interp_result = 1;
    g_retired_count = 0;
    EnemyList_TickInterpolators(&solo, StepInterpolator, Retire, &clock, 0.5f,
                                1.5f, 1.0f, TruncateFloat);
    assert(g_retired_count == 1 && g_retired_enemy == &running);
}

// --- 0x00415DB0 ReplayStage_LoadEntry ---------------------------------------------------

static void* g_payload_seen;
static void* ConstructNode(void* memory, void* payload) {
    g_payload_seen = payload;
    return memory;
}

static void TestReplayStageLoadEntry() {
    static char archive[64];
    *(int*)(archive + 4 + 2 * 8) = 40;  // entry 2 payload at +40

    void* current = 0;
    int stage = 2;
    int frame = 55;
    void* node = ReplayStage_LoadEntry(archive, 2, &current, Allocate,
                                       ConstructNode, &stage, &frame);
    assert(node != 0);
    assert(current == node);
    assert(*(int*)node == 2);
    assert(g_payload_seen == archive + 40);
    assert(stage == 3);
    assert(frame == 0);  // stage changed: frame counter reset

    // Reloading the same stage keeps the frame counter.
    frame = 55;
    void* node2 = ReplayStage_LoadEntry(archive, 2, &current, Allocate,
                                        ConstructNode, &stage, &frame);
    assert(frame == 55);
    assert(stage == 3);
    FreeMemory(node);
    FreeMemory(node2);
}

// --- 0x0043DD10 SoundQueue_QueueEvent ----------------------------------------------------

static void TestSoundQueueQueueEvent() {
    int ids[12];
    int counts[12];
    static int stamps[12][128];
    int volumes[32];
    for (int index = 0; index < 12; ++index) {
        ids[index] = -1;
        counts[index] = 0;
    }
    std::memset(volumes, 0, sizeof(volumes));

    SoundQueue_QueueEvent(ids, counts, stamps, volumes, 7, 90, 1000);
    assert(ids[0] == 7);
    assert(counts[0] == 1);
    assert(stamps[0][0] == 1000);
    assert(volumes[7] == 90);

    // The same sound appends to its slot; a new sound claims the next slot.
    SoundQueue_QueueEvent(ids, counts, stamps, volumes, 7, 90, 1001);
    assert(counts[0] == 2 && stamps[0][1] == 1001);
    SoundQueue_QueueEvent(ids, counts, stamps, volumes, 9, 60, 1002);
    assert(ids[1] == 9 && counts[1] == 1 && stamps[1][0] == 1002);
    assert(volumes[9] == 60);

    // A full slot ring rejects further stamps.
    counts[0] = 0x80;
    SoundQueue_QueueEvent(ids, counts, stamps, volumes, 7, 90, 1003);
    assert(counts[0] == 0x80);
}

// --- 0x004450E0 Renderer_DrawRectFan ------------------------------------------------------

static int g_flushes;
static void Flush(void) { ++g_flushes; }

static int g_blend_sets;
static void SetBlendRenderState(void) { ++g_blend_sets; }

static int g_world_commits;
static void CommitWorld(void) { ++g_world_commits; }

static int g_bound_stage;
static int g_bound_value;
static void BindShader(int stage, int handle) {
    g_bound_stage = stage;
    g_bound_value = handle;
}

static int g_stage_value = -1;
static void SetTextureStage(int stage, int value) {
    assert(stage == 0xE);
    g_stage_value = value;
}

static int g_sampler_states;
static void SetSamplerState(int stage, int state, int value) {
    assert(stage == 0);
    assert(state == 6 || state == 3);
    assert(value == 0);
    ++g_sampler_states;
}

static int g_draw_type;
static const void* g_draw_vertices;
static int g_draw_stride;
static void DrawFan(int primitive_type, const void* vertices, int stride) {
    g_draw_type = primitive_type;
    g_draw_vertices = vertices;
    g_draw_stride = stride;
}

static void TestRendererDrawRectFan() {
    Byte blend = 0;
    int bound = 5;
    static float vertices[4 * 7];
    g_flushes = 0;
    g_blend_sets = 0;
    g_world_commits = 0;
    g_sampler_states = 0;

    int result = Renderer_DrawRectFan(4, Flush, &blend, SetBlendRenderState,
                                      CommitWorld, 9, &bound, BindShader,
                                      SetTextureStage, SetSamplerState,
                                      DrawFan, vertices);
    assert(result == 0);
    assert(g_flushes == 2);  // pending flush + pre-draw flush
    assert(g_blend_sets == 1 && blend == 3);
    assert(g_world_commits == 1);
    assert(bound == 9 && g_bound_stage == 0 && g_bound_value == 9);
    assert(g_stage_value == 0);
    assert(g_sampler_states == 2);
    assert(g_draw_type == 6);
    assert(g_draw_vertices == vertices);
    assert(g_draw_stride == 0x1C);

    // Matching state skips the redundant blend/bind work.
    g_flushes = 0;
    g_blend_sets = 0;
    g_bound_value = -1;
    Renderer_DrawRectFan(0, Flush, &blend, SetBlendRenderState, CommitWorld,
                         9, &bound, BindShader, SetTextureStage,
                         SetSamplerState, DrawFan, vertices);
    assert(g_flushes == 1);
    assert(g_blend_sets == 0);
    assert(g_bound_value == -1);
}

// --- 0x004135D0 FpsCounter_Render -----------------------------------------------------------

static int g_average_updates;
static void UpdateAverage(void) { ++g_average_updates; }

static const char* g_printed_format;
static void PrintOverlay(const char* format) { g_printed_format = format; }

static void TestFpsCounterRender() {
    Word color = 0;
    int accumulator = 10;
    static int game_thread;
    g_average_updates = 0;
    g_printed_format = 0;

    // Low fps prints in red; the color restores to white afterwards.
    Word seen_color = 0;
    (void)seen_color;
    int result = FpsCounter_Render(UpdateAverage, 1, &game_thread, 30.0f,
                                   55.0f, 58.0f, &color, PrintOverlay,
                                   &accumulator, 2);
    assert(result == 1);
    assert(g_average_updates == 1);
    assert(g_printed_format != 0 &&
           std::strcmp(g_printed_format, "%2.1ffps") == 0);
    assert(color == 0xFFFFFFFFu);
    assert(accumulator == 13);

    // Shutdown state skips the overlay but still accumulates.
    g_printed_format = 0;
    FpsCounter_Render(UpdateAverage, 0xE, &game_thread, 30.0f, 55.0f, 58.0f,
                      &color, PrintOverlay, &accumulator, 0);
    assert(g_printed_format == 0);
    assert(accumulator == 14);
}

// --- 0x00426520 ParameterFile_LoadAndRelocate -------------------------------------------------------

static Byte g_track_file[0x200];
static Byte* g_load_result_data;
static Byte* LoadTrackFile(unsigned int* size_out, int bank) {
    assert(bank == 0);
    *size_out = sizeof(g_track_file);
    return g_load_result_data;
}

static void TestMusicRoomLoadTrackList() {
    std::memset(g_track_file, 0, sizeof(g_track_file));
    *(Half*)(g_track_file + 2) = 1;          // one entry
    *(float*)(g_track_file + 0x10) = 4.0f;
    *(float*)(g_track_file + 0x14) = 8.0f;
    *(int*)(g_track_file + 0x110) = 0x140;         // payload offset

    // One record at +0x140, terminated by a negative id at +0x174.
    Byte* record = g_track_file + 0x140;
    record[0] = 1;
    *(int*)(record + 0x24) = 1;
    *(int*)(record + 0x28) = 0;
    *(int*)(record + 0x2C) = 2;
    *(int*)(record + 0x30) = 1;
    g_track_file[0x140 + 0x34] = 0x80;  // negative id terminates

    static const Word table_a[3] = {0xA0, 0xA1, 0xA2};
    static const Word table_b[3] = {0xB0, 0xB1, 0xB2};
    static const Word table_c[3] = {0xC0, 0xC1, 0xC2};
    static const Word table_d[3] = {0xD0, 0xD1, 0xD2};

    Byte* slot = 0;
    g_load_result_data = g_track_file;
    int result = ParameterFile_LoadAndRelocate(&slot, LoadTrackFile, 0.5f,
                                               table_a, table_b, table_c,
                                               table_d);
    assert(result == 0);
    assert(slot == g_track_file);
    assert(*(float*)(g_track_file + 0x18) == 2.0f);
    assert(*(float*)(g_track_file + 0x1C) == 4.0f);
    assert(*(Byte**)(g_track_file + 0x110) == g_track_file + 0x140);
    assert(*(Word*)(record + 0x24) == 0xA1);
    assert(*(Word*)(record + 0x28) == 0xB0);
    assert(*(Word*)(record + 0x2C) == 0xC2);
    assert(*(Word*)(record + 0x30) == 0xD1);

    // A missing file reports -1.
    g_load_result_data = 0;
    result = ParameterFile_LoadAndRelocate(&slot, LoadTrackFile, 0.5f,
                                           table_a, table_b, table_c,
                                           table_d);
    assert(result == -1);
    assert(slot == 0);
}

// --- 0x0043C410 AsciiManager_OnDraw ---------------------------------------------------------

static int g_draw_all_calls;
static void DrawAll(void) { ++g_draw_all_calls; }

static void TestAsciiManagerOnDraw() {
    g_draw_all_calls = 0;
    assert(AsciiManager_OnDraw(DrawAll) == 1);
    assert(g_draw_all_calls == 1);
}

// --- 0x0043D690 SoundStream_StartThread --------------------------------------------------------

static int g_stop_calls;
static void StopPrevious(void) { ++g_stop_calls; }

static int g_event_storage;
static void* CreateEventHandle(void) { return &g_event_storage; }

static int g_thread_storage;
static void* g_thread_argument_seen;
static void* CreateWorkerThread(void* argument, unsigned int* thread_id_out) {
    g_thread_argument_seen = argument;
    *thread_id_out = 42;
    return &g_thread_storage;
}

static unsigned int g_stream_bytes;
static void* g_stream_event;
static int g_open_result;
static int OpenStream(unsigned int buffer_bytes, void* event_handle) {
    g_stream_bytes = buffer_bytes;
    g_stream_event = event_handle;
    return g_open_result;
}

static void TestSoundStreamStartThread() {
    char name_buffer[64];
    static int device, format;
    void* event_slot = 0;
    void* thread_slot = 0;
    unsigned int thread_id = 0;
    static int argument;

    g_stop_calls = 0;
    g_open_result = 0;
    int result = SoundStream_StartThread(
        "bgm01.wav", name_buffer, &device, &format, StopPrevious, 4000, 16,
        CreateEventHandle, &event_slot, CreateWorkerThread, &argument,
        &thread_slot, &thread_id, OpenStream);
    assert(result == 0);
    assert(std::strcmp(name_buffer, "bgm01.wav") == 0);
    assert(g_stop_calls == 1);
    assert(event_slot == &g_event_storage);
    assert(thread_slot == &g_thread_storage);
    assert(thread_id == 42);
    assert(g_thread_argument_seen == &argument);
    // (4000*16 & 0x3FFFFFFF) >> 2 = 16000; rounded down to align 16 = 16000.
    assert(g_stream_bytes == 16000u);
    assert(g_stream_event == &g_event_storage);

    // No format block: immediate failure before any teardown.
    g_stop_calls = 0;
    result = SoundStream_StartThread(
        "bgm02.wav", name_buffer, &device, 0, StopPrevious, 4000, 16,
        CreateEventHandle, &event_slot, CreateWorkerThread, &argument,
        &thread_slot, &thread_id, OpenStream);
    assert(result == -1);
    assert(g_stop_calls == 0);
    assert(std::strcmp(name_buffer, "bgm02.wav") == 0);

    // A failing open reports -1.
    g_open_result = -5;
    result = SoundStream_StartThread(
        "bgm03.wav", name_buffer, &device, &format, StopPrevious, 4000, 16,
        CreateEventHandle, &event_slot, CreateWorkerThread, &argument,
        &thread_slot, &thread_id, OpenStream);
    assert(result == -1);
}

// --- 0x00404F30 BulletSlot_Construct ------------------------------------------------------------

static void* g_base_seen;
static void* g_base_slot_seen;
static void BaseInit(void* base, void* slot) {
    g_base_seen = base;
    g_base_slot_seen = slot;
}

static void* g_timer_seen;
static void InitTimer(void* timer) { g_timer_seen = timer; }

static void TestBulletSlotConstruct() {
    BulletSlot slot;
    std::memset(&slot, 0xFF, sizeof(slot));
    static int base, timer;

    BulletSlot_Construct(&slot, 12, &base, BaseInit, &timer, InitTimer);
    assert(g_base_seen == &base && g_base_slot_seen == &slot);
    for (int index = 0; index < 9; ++index) assert(slot.motion[index] == 0);
    assert(slot.scale_a == 0x10 && slot.scale_b == 0x10);
    assert(slot.id == 12);
    assert(g_timer_seen == &timer);
}

// --- 0x00405300 BulletManager_SelectShotType ----------------------------------------------------

static int g_refreshes;
static void Refresh(void) { ++g_refreshes; }

static void* g_device_seen;
static void* g_palette_seen;
static void UploadPalette(void* device, void* palette) {
    g_device_seen = device;
    g_palette_seen = palette;
}

static void TestBulletManagerSelectShotType() {
    static char shot_table[3 * 0x118];
    void* active = 0;
    int current = -1;
    static int device;
    g_refreshes = 0;

    BulletManager_SelectShotType(&active, shot_table, 0x118, 2, Refresh,
                                 &device, UploadPalette, 0xCC, &current);
    assert(active == shot_table + 2 * 0x118);
    assert(g_refreshes == 1);
    assert(g_device_seen == &device);
    assert(g_palette_seen == shot_table + 2 * 0x118 + 0xCC);
    assert(current == 2);
}

// --- 0x00419F40 ScriptText_NextLine --------------------------------------------------------------

static char* FindChar(char* text, char wanted) {
    return (char*)std::strchr(text, wanted);
}

static int g_post_processed;
static void PostProcess(void) { ++g_post_processed; }

static void TestScriptTextNextLine() {
    char text[] = "# only a comment\n\nvalue = 3 # trailing\ntail";
    char line[32];
    char* cursor = text;
    unsigned int remaining = (unsigned int)std::strlen(text);
    g_post_processed = 0;

    // Comment-only and blank lines are consumed until real content appears.
    cursor = ScriptText_NextLine(line, sizeof(line), cursor, &remaining,
                                 FindChar, PostProcess);
    assert(std::strcmp(line, "value = 3 ") == 0);
    assert(g_post_processed >= 2);  // ran for the skipped lines too
    assert(std::strcmp(cursor, "tail") == 0);
    assert(remaining == 4);

    // No newline left: the tail is copied and the count drains.
    cursor = ScriptText_NextLine(line, sizeof(line), cursor, &remaining,
                                 FindChar, PostProcess);
    assert(std::strcmp(line, "tail") == 0);
    assert(remaining == 0);
}

int main() {
    TestEnemyGridScanCells();
    TestConstructedFactories();
    TestPooledFactories();
    TestStageManagerCreateFromScript();
    TestEnemyListMarkDeadForCapture();
    TestMainMenuDispatchState();
    TestKeyConfigReassignSlot();
    TestAnmArchiveServicePending();
    TestAsciiOverlayFormatShadowed();
    TestBulletManagerActivateSprites();
    TestPlayerDeathShrink();
    TestEnemyListTickInterpolators();
    TestReplayStageLoadEntry();
    TestSoundQueueQueueEvent();
    TestRendererDrawRectFan();
    TestFpsCounterRender();
    TestMusicRoomLoadTrackList();
    TestAsciiManagerOnDraw();
    TestSoundStreamStartThread();
    TestBulletSlotConstruct();
    TestBulletManagerSelectShotType();
    TestScriptTextNextLine();
    return 0;
}
