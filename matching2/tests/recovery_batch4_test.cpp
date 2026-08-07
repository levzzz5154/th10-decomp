#include "th10/game/particle_seed.hpp"
#include "th10/game/stage_tips.hpp"

#include <cassert>
#include <cstdint>
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

int32_t DAT_00474c7c;
int32_t DAT_00474c84;
int32_t DAT_00474c88;
int32_t DAT_00474c8c;
uint32_t* DAT_00477834;  // player block (stage_tip_manager.cpp host path)

static unsigned char g_tip_storage[4][sizeof(StageTip)];
static int g_allocations;

static void* AllocateTip(std::uint32_t size) {
    // Retail allocates the 0x88 record; the host StageTip struct carries
    // host-side members, so the semantic create allocates sizeof.
    assert(size == sizeof(StageTip));
    assert(g_allocations < 4);
    return g_tip_storage[g_allocations++];
}

static std::uint32_t g_random_value;
static std::uint32_t NextRandom() { return g_random_value++; }

static void TestParticleSeedCombine() {
    ParticleSeed left = {{1, 2, 3, 4, 5, 6}, {0, 0, 0, 0}};
    ParticleSeed right = {{-2, 4, 0.5f, -8, 10, 12}, {0, 0, 0, 0}};
    ParticleSeed output = {};
    g_random_value = 0x123456feu;
    ParticleSeed_Combine(&output, &left, &right, NextRandom);
    assert(output.values[0] == -1.0f);
    assert(output.values[1] == 6.0f);
    assert(output.values[2] == 3.5f);
    assert(output.values[3] == -4.0f);
    assert(output.values[4] == 15.0f);
    assert(output.values[5] == 18.0f);
    assert(output.random[0] == 0xfe);
    assert(output.random[1] == 0xff);
    assert(output.random[2] == 0x00);
    assert(output.random[3] == 0x01);
}

static void TestUrgentStageTip() {
    StageTipManager manager;
    DAT_00474c7c = 1;
    DAT_00474c84 = 0;
    DAT_00474c88 = 17;
    DAT_00474c8c = 23;
    g_allocations = 0;
    StageTipManager_Construct(&manager);

    const float first_position[3] = {1, 2, 3};
    StageTip* first = StageTip_Create(
        &manager, first_position, "existing", AllocateTip);
    first->selection = 2;

    const float alert_position[3] = {4, 5, 6};
    StageTip* alert = StageTip_CreateUrgent(
        &manager, alert_position, "alert", AllocateTip);
    assert(first->selection == 1);
    assert(alert != 0);
    assert(alert->duration == 240); // default 300 minus 60
    assert(alert->selection == 30);
    assert(alert->display_mode == 90);
    assert(static_cast<std::uint32_t>(alert->state) == 0xffff8080u);

    // Every positive selection in the active list is decremented; zero stays.
    first->selection = 0;
    StageTip_CreateUrgent(&manager, alert_position, "second", AllocateTip);
    assert(first->selection == 0);
    assert(alert->selection == 29);
}

// Host path of StageTipRuntime_Update (retail 0x00419650): the runtime
// wrapper drives the recovered StageFocus_UpdateFade over the manager's
// retail focus-slot fields instead of aborting on a missing binding. The
// registered primary scheduler callback is the wrapper, so the test runs
// it through the callback Initialize registered.
static void TestStageTipFocusWiring() {
    static unsigned char player_block[0x3C8];
    std::memset(player_block, 0, sizeof(player_block));
    *(float*)(player_block + 0x3C0) = 100.0f;  // player x (camera anchor)
    *(float*)(player_block + 0x3C4) = 50.0f;   // player y
    DAT_00477834 = (uint32_t*)player_block;

    StageTipManager manager;
    DAT_00474c7c = 0;
    DAT_00474c84 = 0;
    DAT_00474c88 = 17;
    DAT_00474c8c = 23;
    DAT_00491be4 = 1;  // scheduler device token required by Initialize
    DAT_00491d6a = 0;  // skip the two startup tip spawns
    StageTipManager_Construct(&manager);

    unsigned char* bytes = (unsigned char*)&manager;
    // Retail focus slot 0: handle +0xDC, x/y/z +0x104/+0x108/+0x10C,
    // half-width +0x17C.
    *(uint32_t*)(bytes + 0xDC) = 0x1234u;
    *(float*)(bytes + 0x104) = 300.0f;
    *(float*)(bytes + 0x108) = 300.0f;
    *(float*)(bytes + 0x10C) = 0.0f;
    *(float*)(bytes + 0x17C) = 40.0f;

    assert(StageTipRuntime_Initialize(&manager) == 0);
    assert(g_test_callback_count >= 1);
    SchedulerCallback* update = &g_test_callbacks[0];  // primary = update
    assert(update->function(update->owner) == 1);

    // The recovery advanced the counters and wrote them back to the retail
    // offsets; the slot geometry survives the round trip.
    assert(*(uint32_t*)(bytes + 0x10) == 1);
    assert(*(uint32_t*)(bytes + 0x14) == 1);
    assert(*(float*)(bytes + 0x104) == 300.0f);
    // No entity lists are wired: the retail lookup fails and the handle is
    // cleared, exactly like retail's not-found path.
    assert(*(uint32_t*)(bytes + 0xDC) == 0);

    // A display-mode change (manager +0xD8 vs DAT_00474c84) resets the
    // secondary counter before the increment; the +0xD8 snapshot itself is
    // only read by the retail body (written at tip spawn), so it survives.
    *(uint32_t*)(bytes + 0xD8) = 5;
    assert(update->function(update->owner) == 1);
    assert(*(uint32_t*)(bytes + 0x10) == 2);
    assert(*(uint32_t*)(bytes + 0x14) == 1);      // reset to 0, then +1
    assert(*(int32_t*)(bytes + 0xD8) == 5);       // snapshot untouched

    DAT_00491be4 = 0;
    DAT_00477834 = 0;
}

int main() {
    TestParticleSeedCombine();
    TestUrgentStageTip();
    TestStageTipFocusWiring();
    return 0;
}
