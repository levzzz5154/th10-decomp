// Focused semantic tests for the rectangular region sweep at 0x00408210.
#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>

#include "th10/game/entity_region_sweep.hpp"

namespace {

const int kEntries = ENTITY_REGION_SWEEP_COUNT;
const int kStride = ENTITY_REGION_SWEEP_STRIDE;

// Palette tables sized exactly like the retail globals.
unsigned int g_small[16];
unsigned int g_medium[8];
unsigned int g_large[4];

struct Harness {
    std::vector<unsigned char> pool;
    std::vector<unsigned char> records;
    std::vector<unsigned char> descriptors;
    EntityRegionSweepOwner owner;
    EntityRegionSweepPalettes palettes;
    EntityRegionSweepHooks hooks;
};

int g_effects_spawned;
int g_animations_created;
int g_last_script;
void* g_last_archive;
float g_last_position[2];
int g_handle_value;
unsigned char* g_record;

void SpawnEffect(void* context, float* position) {
    (void)context;
    ++g_effects_spawned;
    g_last_position[0] = position[0];
    g_last_position[1] = position[1];
}

const int* CreateAnimation(void* context, float* position, void* archive,
                           int script_index) {
    (void)context;
    (void)position;
    ++g_animations_created;
    g_last_archive = archive;
    g_last_script = script_index;
    return &g_handle_value;
}

unsigned char* FindAnimation(void* context, int animation_id) {
    (void)context;
    assert(animation_id == g_handle_value);
    return g_record;
}

unsigned char* Entry(Harness& h, int index) {
    return h.pool.data() + (size_t)index * kStride;
}

void SetEntry(Harness& h, int index, short state, float x, float y,
              float size_x, float size_y) {
    unsigned char* e = Entry(h, index);
    *(short*)(e + ENTITY_REGION_ENTRY_STATE) = state;
    *(float*)(e + ENTITY_REGION_ENTRY_POSITION) = x;
    *(float*)(e + ENTITY_REGION_ENTRY_POSITION + 4) = y;
    *(float*)(e + ENTITY_REGION_ENTRY_SIZE) = size_x;
    *(float*)(e + ENTITY_REGION_ENTRY_SIZE + 4) = size_y;
}

void SetDescriptor(Harness& h, int index, float radius, short sprite) {
    unsigned char* d = h.descriptors.data() + (size_t)index * 64;
    *(float*)(d + ENTITY_REGION_DESCRIPTOR_RADIUS) = radius;
    *(unsigned char**)(Entry(h, index) + ENTITY_REGION_ENTRY_DESCRIPTOR) = d;
    *(short*)(Entry(h, index) + ENTITY_REGION_ENTRY_SPRITE) = sprite;
}

void Reset(Harness& h) {
    h.pool.assign((size_t)kEntries * kStride, 0);
    h.records.assign(1024, 0);
    h.descriptors.assign((size_t)kEntries * 64, 0);

    std::memset(&h.owner, 0, sizeof(h.owner));
    h.owner.entries = h.pool.data();
    h.owner.center[0] = 100.0f;
    h.owner.center[1] = 200.0f;
    h.owner.center[2] = 300.0f;
    h.owner.extent[0] = 20.0f; // half extent 10 -> x in [90, 110]
    h.owner.extent[1] = 40.0f; // half extent 20 -> y in [180, 220]
    h.owner.extent[2] = 2.0f;
    h.owner.animation_archive = (void*)0x1234;

    for (int i = 0; i < 16; ++i) g_small[i] = 0xA0000000u + (unsigned)i;
    for (int i = 0; i < 8; ++i) g_medium[i] = 0xB0000000u + (unsigned)i;
    for (int i = 0; i < 4; ++i) g_large[i] = 0xC0000000u + (unsigned)i;
    h.palettes.small_radius = g_small;
    h.palettes.medium_radius = g_medium;
    h.palettes.large_radius = g_large;

    h.hooks.context = 0;
    h.hooks.spawn_effect = SpawnEffect;
    h.hooks.create_animation = CreateAnimation;
    h.hooks.find_animation = FindAnimation;

    g_effects_spawned = 0;
    g_animations_created = 0;
    g_last_script = 0;
    g_last_archive = 0;
    g_handle_value = 0x5150;
    g_record = h.records.data();
}

unsigned int Flags(Harness& h, int index) {
    return *(unsigned int*)(Entry(h, index) + ENTITY_REGION_ENTRY_FLAGS);
}

unsigned int RecordColor(Harness& h) {
    return *(unsigned int*)(h.records.data() + ENTITY_REGION_RECORD_COLOR);
}

// States 0 and 3 are the two skipped values; everything else participates.
void TestSkippedStates() {
    Harness h;
    Reset(h);
    SetEntry(h, 0, 0, 100.0f, 200.0f, 4.0f, 4.0f);
    SetEntry(h, 1, 3, 100.0f, 200.0f, 4.0f, 4.0f);
    SetEntry(h, 2, 1, 100.0f, 200.0f, 4.0f, 4.0f);
    SetEntry(h, 3, 2, 100.0f, 200.0f, 4.0f, 4.0f);
    SetEntry(h, 4, 4, 100.0f, 200.0f, 4.0f, 4.0f);

    assert(EntityRegionSweep_Run(&h.owner, 0, &h.palettes, &h.hooks) == 0);
    assert(Flags(h, 0) == 0);
    assert(Flags(h, 1) == 0);
    assert(Flags(h, 2) == ENTITY_REGION_SWEEP_HIT_FLAG);
    assert(Flags(h, 3) == ENTITY_REGION_SWEEP_HIT_FLAG);
    assert(Flags(h, 4) == ENTITY_REGION_SWEEP_HIT_FLAG);
    assert(g_animations_created == 3);
}

// The overlap test is inclusive: touching edges count as a hit.
void TestOverlapIsInclusiveOnEdges() {
    Harness h;
    Reset(h);
    // Region x in [90, 110]. A zero-sized entry exactly on each edge hits.
    SetEntry(h, 0, 1, 90.0f, 200.0f, 0.0f, 0.0f);
    SetEntry(h, 1, 1, 110.0f, 200.0f, 0.0f, 0.0f);
    // Just outside on either side misses.
    SetEntry(h, 2, 1, 89.9f, 200.0f, 0.0f, 0.0f);
    SetEntry(h, 3, 1, 110.1f, 200.0f, 0.0f, 0.0f);
    // Region y in [180, 220].
    SetEntry(h, 4, 1, 100.0f, 180.0f, 0.0f, 0.0f);
    SetEntry(h, 5, 1, 100.0f, 220.0f, 0.0f, 0.0f);
    SetEntry(h, 6, 1, 100.0f, 179.9f, 0.0f, 0.0f);
    SetEntry(h, 7, 1, 100.0f, 220.1f, 0.0f, 0.0f);

    EntityRegionSweep_Run(&h.owner, 0, &h.palettes, &h.hooks);
    assert(Flags(h, 0) == ENTITY_REGION_SWEEP_HIT_FLAG);
    assert(Flags(h, 1) == ENTITY_REGION_SWEEP_HIT_FLAG);
    assert(Flags(h, 2) == 0);
    assert(Flags(h, 3) == 0);
    assert(Flags(h, 4) == ENTITY_REGION_SWEEP_HIT_FLAG);
    assert(Flags(h, 5) == ENTITY_REGION_SWEEP_HIT_FLAG);
    assert(Flags(h, 6) == 0);
    assert(Flags(h, 7) == 0);
}

// Both the region and the entry are expanded by half their size.
void TestEntrySizeExpandsTheHitBox() {
    Harness h;
    Reset(h);
    // Centre 120 is 10 past the region's right edge, but a size of 20 gives a
    // half-extent of 10, so the entry's left edge lands exactly on 110.
    SetEntry(h, 0, 1, 120.0f, 200.0f, 20.0f, 0.0f);
    SetEntry(h, 1, 1, 120.0f, 200.0f, 19.0f, 0.0f);
    EntityRegionSweep_Run(&h.owner, 0, &h.palettes, &h.hooks);
    assert(Flags(h, 0) == ENTITY_REGION_SWEEP_HIT_FLAG);
    assert(Flags(h, 1) == 0);
}

// The third axis is halved but never tested; an entry far away in z still hits.
void TestSweepIgnoresThirdAxis() {
    Harness h;
    Reset(h);
    h.owner.extent[2] = 0.0f;
    h.owner.center[2] = 1.0e6f;
    SetEntry(h, 0, 1, 100.0f, 200.0f, 0.0f, 0.0f);
    EntityRegionSweep_Run(&h.owner, 0, &h.palettes, &h.hooks);
    assert(Flags(h, 0) == ENTITY_REGION_SWEEP_HIT_FLAG);
}

// The effect hook fires only when the caller asks for it; the animation is
// always created.
void TestEffectIsOptional() {
    Harness h;
    Reset(h);
    SetEntry(h, 0, 1, 100.0f, 200.0f, 0.0f, 0.0f);
    EntityRegionSweep_Run(&h.owner, 0, &h.palettes, &h.hooks);
    assert(g_effects_spawned == 0);
    assert(g_animations_created == 1);

    Reset(h);
    SetEntry(h, 0, 1, 101.0f, 202.0f, 0.0f, 0.0f);
    EntityRegionSweep_Run(&h.owner, 1, &h.palettes, &h.hooks);
    assert(g_effects_spawned == 1);
    assert(g_animations_created == 1);
    assert(g_last_position[0] == 101.0f);
    assert(g_last_position[1] == 202.0f);
    assert(g_last_script == ENTITY_REGION_SWEEP_SCRIPT);
    assert(g_last_archive == (void*)0x1234);
}

// Palette selection uses strict greater-than, so the thresholds themselves
// fall into the lower band.
void TestPaletteSelectionThresholds() {
    Harness h;

    Reset(h);
    SetEntry(h, 0, 1, 100.0f, 200.0f, 0.0f, 0.0f);
    SetDescriptor(h, 0, 16.0f, 5);
    EntityRegionSweep_Run(&h.owner, 0, &h.palettes, &h.hooks);
    assert(RecordColor(h) == g_small[5]);

    Reset(h);
    SetEntry(h, 0, 1, 100.0f, 200.0f, 0.0f, 0.0f);
    SetDescriptor(h, 0, 16.1f, 3);
    EntityRegionSweep_Run(&h.owner, 0, &h.palettes, &h.hooks);
    assert(RecordColor(h) == g_medium[3]);

    Reset(h);
    SetEntry(h, 0, 1, 100.0f, 200.0f, 0.0f, 0.0f);
    SetDescriptor(h, 0, 32.0f, 2);
    EntityRegionSweep_Run(&h.owner, 0, &h.palettes, &h.hooks);
    assert(RecordColor(h) == g_medium[2]);

    Reset(h);
    SetEntry(h, 0, 1, 100.0f, 200.0f, 0.0f, 0.0f);
    SetDescriptor(h, 0, 32.1f, 1);
    EntityRegionSweep_Run(&h.owner, 0, &h.palettes, &h.hooks);
    assert(RecordColor(h) == g_large[1]);
}

// A null descriptor skips the tint but still creates the animation, marks the
// flag and clears the timer.
void TestNullDescriptorSkipsTint() {
    Harness h;
    Reset(h);
    SetEntry(h, 0, 1, 100.0f, 200.0f, 0.0f, 0.0f);
    *(unsigned int*)(Entry(h, 0) + ENTITY_REGION_ENTRY_TIMER) = 0x777;
    EntityRegionSweep_Run(&h.owner, 0, &h.palettes, &h.hooks);
    assert(RecordColor(h) == 0);
    assert(g_animations_created == 1);
    assert(Flags(h, 0) == ENTITY_REGION_SWEEP_HIT_FLAG);
    assert(*(unsigned int*)(Entry(h, 0) + ENTITY_REGION_ENTRY_TIMER) == 0);
}

// Existing flag bits survive; only bit 3 is added. The timer is cleared only
// for entries that actually hit.
void TestFlagIsOredAndTimerClearedOnlyOnHit() {
    Harness h;
    Reset(h);
    SetEntry(h, 0, 1, 100.0f, 200.0f, 0.0f, 0.0f);
    *(unsigned int*)(Entry(h, 0) + ENTITY_REGION_ENTRY_FLAGS) = 0x21u;
    *(unsigned int*)(Entry(h, 0) + ENTITY_REGION_ENTRY_TIMER) = 0x99;

    // A live entry well outside the region.
    SetEntry(h, 1, 1, 1000.0f, 200.0f, 0.0f, 0.0f);
    *(unsigned int*)(Entry(h, 1) + ENTITY_REGION_ENTRY_FLAGS) = 0x21u;
    *(unsigned int*)(Entry(h, 1) + ENTITY_REGION_ENTRY_TIMER) = 0x99;

    EntityRegionSweep_Run(&h.owner, 0, &h.palettes, &h.hooks);
    assert(Flags(h, 0) == (0x21u | ENTITY_REGION_SWEEP_HIT_FLAG));
    assert(*(unsigned int*)(Entry(h, 0) + ENTITY_REGION_ENTRY_TIMER) == 0);
    assert(Flags(h, 1) == 0x21u);
    assert(*(unsigned int*)(Entry(h, 1) + ENTITY_REGION_ENTRY_TIMER) == 0x99);
}

// The sweep walks the whole pool, including the very last entry.
void TestSweepCoversTheEntirePool() {
    Harness h;
    Reset(h);
    SetEntry(h, kEntries - 1, 1, 100.0f, 200.0f, 0.0f, 0.0f);
    EntityRegionSweep_Run(&h.owner, 0, &h.palettes, &h.hooks);
    assert(Flags(h, kEntries - 1) == ENTITY_REGION_SWEEP_HIT_FLAG);
    assert(g_animations_created == 1);
}

} // namespace

int main() {
    TestSkippedStates();
    TestOverlapIsInclusiveOnEdges();
    TestEntrySizeExpandsTheHitBox();
    TestSweepIgnoresThirdAxis();
    TestEffectIsOptional();
    TestPaletteSelectionThresholds();
    TestNullDescriptorSkipsTint();
    TestFlagIsOredAndTimerClearedOnlyOnHit();
    TestSweepCoversTheEntirePool();
    std::printf("ENTITY_REGION_SWEEP_PASS\n");
    return 0;
}
