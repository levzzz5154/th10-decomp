// Focused semantic tests for the stage slot constructor at 0x00415B00.
#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>

#include "th10/game/entity_region_sweep.hpp"
#include "th10/game/stage_slot_state.hpp"

// math_utils.cpp declares this shared time scale as extern.
unsigned int DAT_00476f78 = 0x3F800000u;

namespace {

const int kEntries = ENTITY_REGION_SWEEP_COUNT;
const int kStride = ENTITY_REGION_SWEEP_STRIDE;
const int kHandleA = 101;
const int kHandleB = 202;

std::vector<unsigned int> g_vm_a;
std::vector<unsigned int> g_vm_b;
std::vector<unsigned char> g_record_a;
std::vector<unsigned char> g_record_b;

int g_allocate_calls;
int g_script_calls;
void* g_script_archive;
int g_script_indices[4];
unsigned int* g_script_vms[4];
int g_register_calls;
bool g_find_fails;
int g_find_calls;
int g_activate_calls;
float* g_activate_region;
std::vector<unsigned char*> g_activated;
int g_release_calls;
std::vector<StageEffectNode*> g_released;
int g_flush_calls;

unsigned int* AllocateVm(void* game_state) {
    (void)game_state;
    return (g_allocate_calls++ == 0) ? g_vm_a.data() : g_vm_b.data();
}

void InitScript(void* archive, unsigned int* vm, int index) {
    g_script_archive = archive;
    if (g_script_calls < 4) {
        g_script_indices[g_script_calls] = index;
        g_script_vms[g_script_calls] = vm;
    }
    ++g_script_calls;
}

int RegisterVm(void* game_state, unsigned int* vm) {
    (void)game_state;
    ++g_register_calls;
    return (vm == g_vm_a.data()) ? kHandleA : kHandleB;
}

unsigned char* FindVm(void* game_state, int handle) {
    (void)game_state;
    ++g_find_calls;
    if (g_find_fails) return 0;
    if (handle == kHandleA) return g_record_a.data();
    if (handle == kHandleB) return g_record_b.data();
    return 0;
}

void ActivateEntry(void* context, float* region, unsigned char* entry) {
    (void)context;
    ++g_activate_calls;
    g_activate_region = region;
    g_activated.push_back(entry);
}

void ReleaseEffect(StageEffectNode* node) {
    ++g_release_calls;
    g_released.push_back(node);
    // Retail reads the next pointer before releasing, so scribbling here must
    // not disturb the walk.
    node->next = (StageEffectNode*)0xDEADBEEF;
}

void FlushMessageHost(void* context) {
    (void)context;
    ++g_flush_calls;
}

struct Fixture {
    std::vector<unsigned char> pool;
    std::vector<void*> resources;
    StageSlotState slot;
    StageSlotInitHooks hooks;
    int definition;
    int archive;
    int game_state;
};

unsigned char* Entry(Fixture& f, int index) {
    return f.pool.data() + 96 + (size_t)index * kStride;
}

void SetState(Fixture& f, int index, short state) {
    *(short*)(Entry(f, index) + ENTITY_REGION_ENTRY_STATE) = state;
}

void Reset(Fixture& f) {
    f.pool.assign(96 + (size_t)kEntries * kStride, 0);
    f.resources.assign(STAGE_SLOT_ARCHIVE_INDEX + 4, 0);
    f.resources[STAGE_SLOT_ARCHIVE_INDEX] = &f.archive;

    g_vm_a.assign(256, 0);
    g_vm_b.assign(256, 0);
    g_record_a.assign(1024, 0);
    g_record_b.assign(1024, 0);

    // Fill the slot with garbage so the memset is observable.
    std::memset(&f.slot, 0xFF, sizeof(f.slot));

    g_allocate_calls = 0;
    g_script_calls = 0;
    g_script_archive = 0;
    g_register_calls = 0;
    g_find_fails = false;
    g_find_calls = 0;
    g_activate_calls = 0;
    g_activate_region = 0;
    g_activated.clear();
    g_release_calls = 0;
    g_released.clear();
    g_flush_calls = 0;

    f.hooks.context = 0;
    f.hooks.pool_object = f.pool.data();
    f.hooks.resource_object = f.resources.data();
    f.hooks.game_state = &f.game_state;
    f.hooks.allocate_vm = AllocateVm;
    f.hooks.init_script = InitScript;
    f.hooks.register_vm = RegisterVm;
    f.hooks.find_vm = FindVm;
    f.hooks.activate_entry = ActivateEntry;
    f.hooks.effect_list = 0;
    f.hooks.release_effect = ReleaseEffect;
    f.hooks.flush_message_host = FlushMessageHost;
}

// All three timers reduce to the shared reset leaf; none is left holding the
// -999999 sentinel it briefly writes.
void TestThreeTimersAreReset() {
    Fixture f;
    Reset(f);
    StageSlotState_Init(&f.slot, &f.definition, &f.hooks);

    const FrameTimer* timers[3] = {&f.slot.timer_a, &f.slot.timer_b,
                                   &f.slot.timer_c};
    for (int i = 0; i < 3; ++i) {
        assert(timers[i]->previous == -1);
        assert(timers[i]->current == 0);
        assert(timers[i]->elapsed == 0.0f);
        assert(timers[i]->speed == (const float*)&DAT_00476f78);
        assert((timers[i]->flags & 1u) != 0);
    }
}

// The memset clears the whole 0x90-byte block, which is what makes the three
// preceding flag clears dead.
void TestBlockIsFullyCleared() {
    Fixture f;
    Reset(f);
    StageSlotState_Init(&f.slot, &f.definition, &f.hooks);

    assert(f.slot.id == 0);
    assert(f.slot.reserved_40[0] == 0);
    assert(f.slot.reserved_40[1] == 0);
    assert(f.slot.reserved_40[2] == 0);
    assert(f.slot.reserved_54 == 0);
    assert(f.slot.field_58 == 0);
    assert(f.slot.reserved_78[0] == 0);
    assert(f.slot.reserved_78[1] == 0);
    assert(f.slot.field_80 == 0);
    assert(f.slot.field_84 == 0);
}

// The definition pointer and the trailing constant block.
void TestDefinitionAndConstants() {
    Fixture f;
    Reset(f);
    StageSlotState* returned =
        StageSlotState_Init(&f.slot, &f.definition, &f.hooks);

    assert(returned == &f.slot);
    assert(f.slot.definition == &f.definition);
    assert(f.slot.radius == 8.0f);
    assert(f.slot.region[0] == 25.0f);
    assert(f.slot.region[1] == 0.0f);
    assert(f.slot.region[2] == 0.0f);
    assert(f.slot.color_a == 0x00F8F08Fu);
    assert(f.slot.color_b == 0x008088FFu);
}

// Two VMs are built from the archive carried by the resource object, each
// forced to script 15 with the high control flag set.
void TestTwoVmsAreBuilt() {
    Fixture f;
    Reset(f);
    StageSlotState_Init(&f.slot, &f.definition, &f.hooks);

    assert(g_allocate_calls == 2);
    assert(g_register_calls == 2);
    assert(g_script_calls == 2);
    assert(g_script_archive == &f.archive);
    assert(g_script_indices[0] == 0);
    assert(g_script_indices[1] == 1);
    assert(g_script_vms[0] == g_vm_a.data());
    assert(g_script_vms[1] == g_vm_b.data());

    assert((g_vm_a[215] & (unsigned int)STAGE_SLOT_VM_FLAG) != 0);
    assert((g_vm_b[215] & (unsigned int)STAGE_SLOT_VM_FLAG) != 0);
    assert(g_vm_a[8] == (unsigned int)STAGE_SLOT_VM_SCRIPT);
    assert(g_vm_b[8] == 15u);

    assert(f.slot.vm_handle_a == kHandleA);
    assert(f.slot.vm_handle_b == kHandleB);
}

// The control flag is folded in rather than overwriting the existing word.
void TestVmFlagIsOredIntoControlWord() {
    Fixture f;
    Reset(f);
    g_vm_a.assign(256, 0);
    g_vm_b.assign(256, 0);
    g_vm_a[215] = 0x00000055u;
    g_vm_b[215] = 0x000000AAu;
    StageSlotState_Init(&f.slot, &f.definition, &f.hooks);

    assert(g_vm_a[215] == (0x00000055u | 0x40000000u));
    assert(g_vm_b[215] == (0x000000AAu | 0x40000000u));
}

// Both records get the same byte written to two adjacent fields.
void TestRecordsAreStamped() {
    Fixture f;
    Reset(f);
    StageSlotState_Init(&f.slot, &f.definition, &f.hooks);

    assert(g_find_calls == 4);
    assert(g_record_a[STAGE_SLOT_RECORD_FIELD_A] == 16);
    assert(g_record_a[STAGE_SLOT_RECORD_FIELD_B] == 16);
    assert(g_record_b[STAGE_SLOT_RECORD_FIELD_A] == 16);
    assert(g_record_b[STAGE_SLOT_RECORD_FIELD_B] == 16);
    assert(g_record_a[STAGE_SLOT_RECORD_FIELD_B + 1] == 0);
}

// A failed lookup clears the stored handle.
void TestFailedLookupClearsHandle() {
    Fixture f;
    Reset(f);
    g_find_fails = true;
    StageSlotState_Init(&f.slot, &f.definition, &f.hooks);

    assert(f.slot.vm_handle_a == 0);
    assert(f.slot.vm_handle_b == 0);
    assert(g_find_calls == 4);
}

// The pool sweep uses the same skip rule and stride as the region sweep at
// 0x00408210, and hands the region pointer through unchanged.
void TestPoolSweepSkipRule() {
    Fixture f;
    Reset(f);
    SetState(f, 0, 0);
    SetState(f, 1, 3);
    SetState(f, 2, 1);
    SetState(f, 3, 2);
    SetState(f, 4, 4);
    SetState(f, kEntries - 1, 5);
    StageSlotState_Init(&f.slot, &f.definition, &f.hooks);

    assert(g_activate_calls == 4);
    assert(g_activated[0] == Entry(f, 2));
    assert(g_activated[1] == Entry(f, 3));
    assert(g_activated[2] == Entry(f, 4));
    assert(g_activated[3] == Entry(f, kEntries - 1));
    assert(g_activate_region == f.slot.region);
    assert(g_activate_region[0] == 25.0f);
}

// An all-idle pool activates nothing.
void TestPoolSweepIgnoresIdlePool() {
    Fixture f;
    Reset(f);
    StageSlotState_Init(&f.slot, &f.definition, &f.hooks);
    assert(g_activate_calls == 0);
}

// The teardown walk releases every node except those of kind 1, and reads the
// next pointer before releasing so the walk survives node reuse.
void TestEffectListTeardown() {
    Fixture f;
    Reset(f);
    StageEffectNode nodes[4];
    std::memset(nodes, 0, sizeof(nodes));
    for (int i = 0; i < 3; ++i) nodes[i].next = &nodes[i + 1];
    nodes[3].next = 0;
    nodes[0].kind = 0;
    nodes[1].kind = 1; // skipped
    nodes[2].kind = 2;
    nodes[3].kind = 1; // skipped
    f.hooks.effect_list = &nodes[0];

    StageSlotState_Init(&f.slot, &f.definition, &f.hooks);

    assert(g_release_calls == 2);
    assert(g_released[0] == &nodes[0]);
    assert(g_released[1] == &nodes[2]);
}

// The message host flush always runs, exactly once, at the very end.
void TestMessageHostIsFlushed() {
    Fixture f;
    Reset(f);
    StageSlotState_Init(&f.slot, &f.definition, &f.hooks);
    assert(g_flush_calls == 1);
}

} // namespace

int main() {
    TestThreeTimersAreReset();
    TestBlockIsFullyCleared();
    TestDefinitionAndConstants();
    TestTwoVmsAreBuilt();
    TestVmFlagIsOredIntoControlWord();
    TestRecordsAreStamped();
    TestFailedLookupClearsHandle();
    TestPoolSweepSkipRule();
    TestPoolSweepIgnoresIdlePool();
    TestEffectListTeardown();
    TestMessageHostIsFlushed();
    std::printf("STAGE_SLOT_STATE_PASS\n");
    return 0;
}
