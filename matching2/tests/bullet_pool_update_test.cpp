// =============================================================================
// bullet_pool_update_test.cpp - Host tests for the 0x004065C0 bullet-pool
// update sweep (BulletPool_UpdateSweep) and its scheduler arm
// (BulletPool_UpdateCallback through BulletPoolRuntime_Initialize).
//
// Fixture layout mirrors the retail 0x3E0B54-byte pool record: payload
// records at +0x60, stride 0x7F0; per-record bookkeeping at payload+0x3F8..
// +0x464 (counter copy, counter, value float, drive pointer) and
// payload+0x446..+0x460 (active WORD, node link, row dword).  The six
// head/tail lists are retail-width dwords (heads +20+4*row, tails
// +44+4*row) holding 32-bit record pointers, so the pool is mapped at a
// low address (below 4 GiB) where the pointers round-trip losslessly -
// the suite's 32-bit-retail-pointer fixture convention.
// =============================================================================
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include "th10/game/bullet_manager.hpp"
#include "th10/game/enemy_lifecycle.hpp"
#include "th10/game/scheduler.hpp"

#include <sys/mman.h>
#include <unistd.h>

#include <cassert>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

// Globals referenced by src/game/bullet_manager.cpp.
void* g_pGameStateManager = (void*)0x12345678;
unsigned int DAT_00491be4 = 0;
uint32_t DAT_00476f78 = 0x3F800000u;  // 1.0f as bits (frame-scale sentinel)
extern "C" {
unsigned long dword_477810 = 0;
}

static int g_mock_resource = 0;
int* ResourceManager_FindResource(int, void*, const char*) {
    return &g_mock_resource;
}

// Draw-edge leaves (retail 0x004067A0 walks EnemyList_SyncHitboxes); the
// update sweep under test never reaches them, but the link needs them.
int EnemyList_SyncHitboxes(HitboxEnemy*, float, float,
                           float (*)(float, float), void (*)(void*), void*) {
    return 0;
}
float Angle_NormalizeSum(float angle, float) { return angle; }

// Scheduler machinery: capture the callbacks the pool runtime registers so
// the tests can drive the real update arm through the scheduler entry point.
static SchedulerCallback g_stub_update_callback = {};
static SchedulerCallback g_stub_draw_callback = {};
static SchedulerFunction g_captured_update = 0;
static SchedulerFunction g_captured_draw = 0;
SchedulerCallback* SchedulerCallback_Create(SchedulerFunction function) {
    if (g_captured_update == 0) {
        g_captured_update = function;
        return &g_stub_update_callback;
    }
    g_captured_draw = function;
    return &g_stub_draw_callback;
}
int Scheduler_RegisterPrimary(SchedulerCallback*, int, void*) { return 0; }
int Scheduler_RegisterSecondary(SchedulerCallback*, int, void*) { return 0; }
void Scheduler_Remove(SchedulerCallback*, void*) {}
SchedulerCallbackNode* Scheduler_RegisterOwnedCallback(
    void*, void*, SchedulerCallbackNode* (*)(void*), void (*)(void*), void*) {
    return 0;
}

// --- Fixture ---------------------------------------------------------------

static const int kSlotCount = 2000;
static const int kSlotStride = 0x7F0;
static const int kPoolSize = 0x3E0B54;

// Map the pool below 4 GiB so 32-bit record pointers round-trip losslessly
// through the retail dword list slots.  Candidates follow the repo's
// low-region fixture convention (MAP_FIXED_NOREPLACE, fallback bases).
static const unsigned long kLowBases[] = {
    0x08000000UL, 0x04000000UL, 0x10000000UL, 0x20000000UL,
};

static unsigned char* MakePool() {
    const long page = sysconf(_SC_PAGESIZE);
    const size_t size = (kPoolSize + page - 1) / page * page;
    for (unsigned long base : kLowBases) {
        void* region = mmap((void*)(uintptr_t)base, size,
                            PROT_READ | PROT_WRITE,
                            MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED_NOREPLACE,
                            -1, 0);
        if (region != MAP_FAILED) {
            std::memset(region, 0, size);
            return (unsigned char*)region;
        }
    }
    return 0;
}

static unsigned char* Payload(unsigned char* pool, int index) {
    return pool + 0x60 + index * kSlotStride;
}

static uint32_t Handle(unsigned char* pool, int index) {
    return (uint32_t)(uintptr_t)Payload(pool, index);
}

static uint32_t HeadSlot(unsigned char* pool, int row) {
    return *(uint32_t*)(pool + 0x14 + 4 * row);
}
static uint32_t TailSlot(unsigned char* pool, int row) {
    return *(uint32_t*)(pool + 0x2C + 4 * row);
}

static float g_default_drive = 1.0f;  // ramp path (0.99 < drive < 1.01)

static void Activate(unsigned char* pool, int index, int row) {
    unsigned char* p = Payload(pool, index);
    *(unsigned short*)(p + 0x446) = 1;  // active WORD
    *(int*)(p + 0x460) = row;           // row dword
    *(void**)(p + 0x404) = &g_default_drive;  // drive pointer
}

// Per-bullet check twin (retail sub_406240 stand-in): reports alive except
// for the payload named by g_drop_payload.
static const void* g_drop_payload = 0;
static int g_hook_calls = 0;
static int HookAlive(void* bullet) {
    ++g_hook_calls;
    return bullet == g_drop_payload ? 1 : 0;
}

int main() {
    // --- Hook path: row routing, count, ramp/damp, 2000-slot sweep --------
    unsigned char* pool = MakePool();
    if (pool == 0) {
        std::printf("SKIP: no low-address mapping available\n");
        return 0;
    }
    dword_477810 = 0;
    g_drop_payload = 0;
    g_hook_calls = 0;
    float drive_ramp = 0.995f;   // in (0.99, 1.01): ramp
    float drive_damp = 0.5f;     // <= 0.99: damp
    float drive_hi = 1.01f;      // >= 1.01: damp (real gate, no NaN filter)
    float drive_lo = 0.99f;      // <= 0.99: damp
    float drive_one = 1.0f;      // in (0.99, 1.01): ramp
    Activate(pool, 0, 0);
    *(float*)(Payload(pool, 0) + 0x400) = 100.0f;
    *(void**)(Payload(pool, 0) + 0x404) = &drive_ramp;
    Activate(pool, 1, 3);
    *(float*)(Payload(pool, 1) + 0x400) = 10.0f;
    *(void**)(Payload(pool, 1) + 0x404) = &drive_damp;
    Activate(pool, 2, 5);
    *(float*)(Payload(pool, 2) + 0x400) = 20.0f;
    *(void**)(Payload(pool, 2) + 0x404) = &drive_hi;
    Activate(pool, 3, 0);
    *(float*)(Payload(pool, 3) + 0x400) = 5.0f;
    *(void**)(Payload(pool, 3) + 0x404) = &drive_lo;
    *(int*)(Payload(pool, 3) + 0x3FC) = 7;  // pre-set counter
    Activate(pool, kSlotCount - 1, 2);     // last slot of the sweep
    *(float*)(Payload(pool, kSlotCount - 1) + 0x400) = 0.0f;
    *(void**)(Payload(pool, kSlotCount - 1) + 0x404) = &drive_one;

    BulletPoolUpdateEnv env = {};
    env.update_bullet = HookAlive;
    assert(BulletPool_UpdateSweep(pool, &env) == 1);
    assert(g_hook_calls == 5);

    // Count + head/tail routing per row (retail dword slots).
    assert(*(int*)(pool + 0x5C) == 5);
    assert(HeadSlot(pool, 0) == Handle(pool, 0) &&
           TailSlot(pool, 0) == Handle(pool, 3));
    assert(HeadSlot(pool, 3) == Handle(pool, 1) &&
           TailSlot(pool, 3) == Handle(pool, 1));
    assert(HeadSlot(pool, 5) == Handle(pool, 2) &&
           TailSlot(pool, 5) == Handle(pool, 2));
    assert(HeadSlot(pool, 2) == Handle(pool, kSlotCount - 1) &&
           TailSlot(pool, 2) == Handle(pool, kSlotCount - 1));
    assert(HeadSlot(pool, 1) == 0 && TailSlot(pool, 1) == 0);
    assert(HeadSlot(pool, 4) == 0 && TailSlot(pool, 4) == 0);

    // Node links: row 0 chains slot0 -> slot3, last node link cleared.
    assert(*(uint32_t*)(Payload(pool, 0) + 0x44C) == Handle(pool, 3));
    assert(*(uint32_t*)(Payload(pool, 3) + 0x44C) == 0);
    assert(*(uint32_t*)(Payload(pool, 1) + 0x44C) == 0);

    // Ramp (drive 0.995): value +1.0, counter +1, copy = old counter.
    assert(*(int*)(Payload(pool, 0) + 0x3F8) == 0);
    assert(*(int*)(Payload(pool, 0) + 0x3FC) == 1);
    assert(*(float*)(Payload(pool, 0) + 0x400) == 100.0f + 1.0f);
    // Damp (drive 0.5): value += drive, counter = (int)value.
    assert(*(int*)(Payload(pool, 1) + 0x3F8) == 0);
    assert(*(int*)(Payload(pool, 1) + 0x3FC) == (int)(10.0f + 0.5f));
    assert(*(float*)(Payload(pool, 1) + 0x400) == 10.0f + 0.5f);
    // Damp at the 1.01 boundary (the >= arm is a real gate here).
    assert(*(int*)(Payload(pool, 2) + 0x3F8) == 0);
    assert(*(int*)(Payload(pool, 2) + 0x3FC) == (int)(20.0f + 1.01f));
    assert(*(float*)(Payload(pool, 2) + 0x400) == 20.0f + 1.01f);
    // Damp at the 0.99 boundary; the copy takes the old counter (7).
    assert(*(int*)(Payload(pool, 3) + 0x3F8) == 7);
    assert(*(int*)(Payload(pool, 3) + 0x3FC) == (int)(5.0f + 0.99f));
    assert(*(float*)(Payload(pool, 3) + 0x400) == 5.0f + 0.99f);
    // Ramp (drive 1.0) on the last swept slot.
    assert(*(int*)(Payload(pool, kSlotCount - 1) + 0x3F8) == 0);
    assert(*(int*)(Payload(pool, kSlotCount - 1) + 0x3FC) == 1);
    assert(*(float*)(Payload(pool, kSlotCount - 1) + 0x400) == 1.0f);
    munmap(pool, kPoolSize);

    // --- Hook drops a bullet: excluded from the lists and the count -------
    pool = MakePool();
    assert(pool != 0);
    Activate(pool, 0, 0);
    Activate(pool, 1, 0);
    g_drop_payload = Payload(pool, 1);
    g_hook_calls = 0;
    env = {};
    env.update_bullet = HookAlive;
    assert(BulletPool_UpdateSweep(pool, &env) == 1);
    assert(g_hook_calls == 2);
    assert(*(int*)(pool + 0x5C) == 1);
    assert(HeadSlot(pool, 0) == Handle(pool, 0) &&
           TailSlot(pool, 0) == Handle(pool, 0));
    assert(*(uint32_t*)(Payload(pool, 0) + 0x44C) == 0);
    munmap(pool, kPoolSize);

    // --- UI-manager capture path admits slots with the hook elided --------
    pool = MakePool();
    assert(pool != 0);
    Activate(pool, 0, 1);
    Activate(pool, 1, 4);
    unsigned char ui[0x100];
    std::memset(ui, 0, sizeof(ui));
    *(unsigned int*)(ui + 88) = 2 | 0x400;
    dword_477810 = (unsigned long)(uintptr_t)ui;
    env = {};
    env.update_bullet = 0;  // elided: capture path is the only admission
    assert(BulletPool_UpdateSweep(pool, &env) == 1);
    assert(*(int*)(pool + 0x5C) == 2);
    assert(HeadSlot(pool, 1) == Handle(pool, 0) &&
           TailSlot(pool, 1) == Handle(pool, 0));
    assert(HeadSlot(pool, 4) == Handle(pool, 1) &&
           TailSlot(pool, 4) == Handle(pool, 1));
    // The capture path short-circuits the check entirely: a hook that would
    // drop slot 0 is never consulted.
    g_hook_calls = 0;
    g_drop_payload = Payload(pool, 0);
    env.update_bullet = HookAlive;
    assert(BulletPool_UpdateSweep(pool, &env) == 1);
    assert(g_hook_calls == 0);
    assert(*(int*)(pool + 0x5C) == 2);
    // Capture flags incomplete (bit 0x400 clear) + elided hook: no admission.
    *(unsigned int*)(ui + 88) = 2;
    env.update_bullet = 0;
    assert(BulletPool_UpdateSweep(pool, &env) == 1);
    assert(*(int*)(pool + 0x5C) == 0);
    assert(HeadSlot(pool, 1) == 0 && HeadSlot(pool, 4) == 0);
    dword_477810 = 0;
    munmap(pool, kPoolSize);

    // --- Elided hook + no capture state: every active slot is skipped -----
    pool = MakePool();
    assert(pool != 0);
    Activate(pool, 0, 0);
    Activate(pool, 5, 2);
    env = {};
    env.update_bullet = 0;
    assert(BulletPool_UpdateSweep(pool, &env) == 1);
    assert(*(int*)(pool + 0x5C) == 0);
    assert(HeadSlot(pool, 0) == 0 && TailSlot(pool, 0) == 0 &&
           HeadSlot(pool, 2) == 0);
    munmap(pool, kPoolSize);

    // --- Scheduler arm: the wrapper runs the sweep (no MissingEdge) -------
    pool = MakePool();
    assert(pool != 0);
    Activate(pool, 0, 0);
    DAT_00491be4 = 0x1234;
    dword_477810 = 0;
    g_captured_update = 0;
    g_captured_draw = 0;
    assert(BulletPoolRuntime_Initialize(pool) == 0);
    assert(g_captured_update != 0 && g_captured_draw != 0);
    // Default env: hook null, no capture state -> the arm admits nothing and
    // does not abort on the missing edge.
    assert(g_captured_update(pool) == 1);
    assert(*(int*)(pool + 0x5C) == 0);
    // Inject the per-bullet twin through the env setter and re-run the arm.
    g_hook_calls = 0;
    g_drop_payload = 0;
    env = {};
    env.update_bullet = HookAlive;
    BulletPoolRuntime_SetUpdateEnv(&env);
    assert(g_captured_update(pool) == 1);
    assert(g_hook_calls == 1);
    assert(*(int*)(pool + 0x5C) == 1);
    assert(HeadSlot(pool, 0) == Handle(pool, 0) &&
           TailSlot(pool, 0) == Handle(pool, 0));
    // Clearing the env elides the check again.
    BulletPoolRuntime_SetUpdateEnv(0);
    assert(g_captured_update(pool) == 1);
    assert(*(int*)(pool + 0x5C) == 0);
    assert(HeadSlot(pool, 0) == 0);
    munmap(pool, kPoolSize);

    // --- BulletPool_RetireSlot (retail sub_405BE0) frees a slot ----------
    pool = MakePool();
    assert(pool != 0);
    Activate(pool, 0, 0);
    Activate(pool, 1, 3);
    unsigned char* p0 = Payload(pool, 0);
    // Pre-seed both clock words and the armed bits so the leaf must rewind
    // them.
    *(int*)(p0 + 0x3F8) = 0x76543210;
    *(int*)(p0 + 0x3FC) = 7;
    *(float*)(p0 + 0x400) = 123.0f;
    *(void**)(p0 + 0x404) = &g_default_drive;
    *(uint32_t*)(p0 + 0x408) = 0;
    *(int*)(p0 + 0x40C) = 0x11111111;
    *(int*)(p0 + 0x410) = 9;
    *(int*)(p0 + 0x414) = 9;
    *(void**)(p0 + 0x418) = &g_default_drive;
    *(uint32_t*)(p0 + 0x41C) = 0;
    BulletPool_RetireSlot(p0);
    assert(*(unsigned short*)(p0 + 0x446) == 0);
    assert(*(int*)(p0 + 0x3F8) == (int)0xFFF0BDC1);
    assert(*(int*)(p0 + 0x3FC) == 0);
    assert(*(float*)(p0 + 0x400) == 0.0f);
    assert((uint32_t)(uintptr_t)(
        *reinterpret_cast<void**>(p0 + 0x404)) ==
           (uint32_t)(uintptr_t)(void*)&DAT_00476f78);
    assert((*(uint32_t*)(p0 + 0x408) & 1u) != 0);
    assert(*(int*)(p0 + 0x40C) == (int)0xFFFFFFFF);
    assert(*(int*)(p0 + 0x410) == 0);
    assert(*(int*)(p0 + 0x414) == 0);
    assert((uint32_t)(uintptr_t)(
        *reinterpret_cast<void**>(p0 + 0x418)) ==
           (uint32_t)(uintptr_t)(void*)&DAT_00476f78);
    assert((*(uint32_t*)(p0 + 0x41C) & 1u) != 0);
    // The freed word makes the sweep skip the slot; the other slot remains.
    env = {};
    env.update_bullet = HookAlive;
    g_drop_payload = 0;
    g_hook_calls = 0;
    assert(BulletPool_UpdateSweep(pool, &env) == 1);
    assert(*(int*)(pool + 0x5C) == 1);
    assert(HeadSlot(pool, 3) == Handle(pool, 1) &&
           TailSlot(pool, 3) == Handle(pool, 1));
    assert(HeadSlot(pool, 0) == 0);
    munmap(pool, kPoolSize);

    return 0;
}
