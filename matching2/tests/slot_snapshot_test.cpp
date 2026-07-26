// Focused semantic tests for the per-slot game-state snapshot (0x0042A450).
#include "th10/game/slot_snapshot.hpp"

#include <cassert>
#include <cstring>

namespace {

const int kLiveSize = 0x4600;
const int kRecordSize = 0x200;
const int kSlots = 3;

unsigned char g_live[kLiveSize];
unsigned char g_snapshots[kSlots][kRecordSize];
unsigned char* g_snapshot_table[kSlots];
SlotSnapshotRecordSlot g_record_table[kSlots];

unsigned int g_object_a[4];
unsigned int g_object_b[4];
unsigned int g_object_c[4];

SlotSnapshotDefaults g_defaults;

int g_prepare_calls;
int g_prepare_slot_seen;
int g_summary_calls;
int g_restore_calls;
unsigned char* g_restore_block_seen;
int g_refresh_calls;
int g_commit_calls;
// Retail refreshes derived state before the record loop and commits after the
// counters are cleared, so the order matters.
unsigned int g_live_tail_at_refresh;
unsigned int g_cleared_at_commit;

void PrepareSlot(void* context, int slot, SlotSnapshotOwner* owner) {
    (void)context;
    (void)owner;
    ++g_prepare_calls;
    g_prepare_slot_seen = slot;
}

int CaptureSummary(void* context, int slot, SlotSnapshotOwner* owner) {
    (void)context;
    (void)owner;
    ++g_summary_calls;
    return 0x5000 + slot;
}

void RestoreScores(void* context, unsigned char* live,
                   unsigned char* record_block) {
    (void)context;
    (void)live;
    ++g_restore_calls;
    g_restore_block_seen = record_block;
}

void RefreshDerived(void* context, unsigned char* live) {
    (void)context;
    ++g_refresh_calls;
    g_live_tail_at_refresh = *(unsigned int*)(live + 0x4474);
}

void CommitRestore(void* context, unsigned char* live) {
    (void)context;
    ++g_commit_calls;
    g_cleared_at_commit = *(unsigned int*)(live + 0x332C);
}

SlotSnapshotHooks MakeHooks() {
    g_prepare_calls = 0;
    g_prepare_slot_seen = -1;
    g_summary_calls = 0;
    g_restore_calls = 0;
    g_restore_block_seen = 0;
    g_refresh_calls = 0;
    g_commit_calls = 0;
    g_live_tail_at_refresh = 0;
    g_cleared_at_commit = 0xFFFFFFFFu;

    SlotSnapshotHooks hooks;
    hooks.context = 0;
    hooks.prepare_slot = PrepareSlot;
    hooks.capture_summary = CaptureSummary;
    hooks.restore_scores = RestoreScores;
    hooks.refresh_derived = RefreshDerived;
    hooks.commit_restore = CommitRestore;
    return hooks;
}

SlotSnapshotOwner MakeOwner(int mode) {
    std::memset(g_object_a, 0, sizeof(g_object_a));
    std::memset(g_object_b, 0, sizeof(g_object_b));
    std::memset(g_object_c, 0, sizeof(g_object_c));
    for (int index = 0; index < kSlots; ++index) {
        g_snapshot_table[index] = g_snapshots[index];
        g_record_table[index].record = g_snapshots[index];
        for (int field = 0; field < 8; ++field) {
            g_record_table[index].reserved[field] = 0;
        }
    }

    SlotSnapshotOwner owner;
    owner.dirty_a = g_object_a;
    owner.dirty_b = g_object_b;
    owner.dirty_c = g_object_c;
    owner.mode = mode;
    owner.snapshots = g_snapshot_table;
    owner.records = g_record_table;
    owner.summary = -1;
    owner.active_slot = -1;
    owner.pending = 0x1234;
    return owner;
}

SlotSnapshotEnv MakeEnv(int slot, int suppress_defaults) {
    g_defaults.field_0c = 0x0C0C0C0Cu;
    g_defaults.field_10 = 0xBEEF;
    g_defaults.field_14 = 0x14141414u;
    g_defaults.field_18 = 0x18181818u;
    g_defaults.field_1c = 0x1C1C1C1Cu;
    g_defaults.field_20 = 0x20202020u;
    g_defaults.field_1b4 = 0xB4B4B4B4u;
    g_defaults.field_1b8 = 0xB8B8B8B8u;

    SlotSnapshotEnv env;
    env.live = g_live;
    env.slot = slot;
    env.suppress_defaults = suppress_defaults;
    env.shot_type = 0;
    env.shot_variant = 0;
    env.defaults = &g_defaults;
    return env;
}

// Fills the live block with a distinct value per dword so any misrouted copy
// shows up as a mismatched marker.
void SeedLive() {
    std::memset(g_live, 0, sizeof(g_live));
    unsigned int* words = (unsigned int*)g_live;
    for (int index = 0; index < kLiveSize / 4; ++index) {
        words[index] = 0x10000000u + (unsigned int)index;
    }
}

void ClearSnapshots() {
    std::memset(g_snapshots, 0, sizeof(g_snapshots));
}

unsigned int LiveWord(int byte_offset) {
    return *(unsigned int*)(g_live + byte_offset);
}

unsigned int SnapWord(int slot, int byte_offset) {
    return *(unsigned int*)(g_snapshots[slot] + byte_offset);
}

const int kLiveFields[8] = {-3, -2, -1, 0, 1, 2, 3, 4};
const int kSnapFields[8] = {-9, -8, -1, 0, 7, 8, 15, 16};

// --- Tests -------------------------------------------------------------------

void TestDirtyBitsAlwaysSet() {
    SlotSnapshotHooks hooks = MakeHooks();
    // Mode 2 is neither capture nor restore: only the dirty bits and the
    // pending word are touched.
    SlotSnapshotOwner owner = MakeOwner(2);
    SlotSnapshotEnv env = MakeEnv(0, 0);
    SeedLive();
    ClearSnapshots();

    g_object_a[1] = 1u;
    g_object_b[1] = 4u;
    g_object_c[1] = 0u;

    SlotSnapshot_Run(&owner, &env, &hooks);

    // Bit 1 is OR-ed in, leaving other bits alone.
    assert(g_object_a[1] == 3u);
    assert(g_object_b[1] == 6u);
    assert(g_object_c[1] == 2u);
    assert(owner.pending == 0);
    // No hook runs and no state moves for an unrecognized mode.
    assert(g_prepare_calls == 0 && g_summary_calls == 0);
    assert(g_restore_calls == 0 && g_commit_calls == 0);
    assert(owner.active_slot == -1);
    assert(SnapWord(0, 0x024) == 0);
}

void TestNullObjectsAreSkipped() {
    SlotSnapshotHooks hooks = MakeHooks();
    SlotSnapshotOwner owner = MakeOwner(2);
    SlotSnapshotEnv env = MakeEnv(0, 0);
    owner.dirty_a = 0;
    owner.dirty_b = 0;
    owner.dirty_c = 0;
    // Must not fault; retail null-checks each object independently.
    SlotSnapshot_Run(&owner, &env, &hooks);
    assert(owner.pending == 0);
}

void TestCaptureWritesDefaultsAndScalars() {
    SlotSnapshotHooks hooks = MakeHooks();
    SlotSnapshotOwner owner = MakeOwner(0);
    SlotSnapshotEnv env = MakeEnv(1, 0);
    SeedLive();
    ClearSnapshots();

    SlotSnapshot_Run(&owner, &env, &hooks);

    assert(g_prepare_calls == 1 && g_prepare_slot_seen == 1);
    assert(g_summary_calls == 1);
    assert(owner.summary == 0x5001);
    assert(owner.active_slot == 1);
    assert(owner.pending == 0);

    // Defaults land in the active slot's snapshot only.
    assert(SnapWord(1, 0x00C) == 0x0C0C0C0Cu);
    assert(*(unsigned short*)(g_snapshots[1] + 0x010) == 0xBEEF);
    // The 16-bit store must leave the neighbouring half-word untouched.
    assert(*(unsigned short*)(g_snapshots[1] + 0x012) == 0);
    assert(SnapWord(1, 0x014) == 0x14141414u);
    assert(SnapWord(1, 0x018) == 0x18181818u);
    assert(SnapWord(1, 0x01C) == 0x1C1C1C1Cu);
    assert(SnapWord(1, 0x020) == 0x20202020u);
    assert(SnapWord(1, 0x1B4) == 0xB4B4B4B4u);
    assert(SnapWord(1, 0x1B8) == 0xB8B8B8B8u);
    assert(SnapWord(0, 0x00C) == 0);

    // Two scalars are pulled straight out of the live block.
    assert(SnapWord(1, 0x024) == LiveWord(0x3CC));
    assert(SnapWord(1, 0x028) == LiveWord(0x3D0));

    // The 0x108-byte bulk block is mirrored verbatim.
    assert(std::memcmp(g_snapshots[1] + 0x2C, g_live + 0x436C, 0x108) == 0);
    // The tail scalar is copied after the record loop.
    assert(SnapWord(1, 0x1BC) == LiveWord(0x4474));
}

void TestCaptureSuppressedDefaults() {
    SlotSnapshotHooks hooks = MakeHooks();
    SlotSnapshotOwner owner = MakeOwner(0);
    SlotSnapshotEnv env = MakeEnv(0, 1);
    SeedLive();
    ClearSnapshots();

    SlotSnapshot_Run(&owner, &env, &hooks);

    // With the suppression flag set the default block is skipped entirely...
    assert(SnapWord(0, 0x00C) == 0);
    assert(SnapWord(0, 0x014) == 0);
    assert(SnapWord(0, 0x1B4) == 0);
    // ...but 0x1B8 is written unconditionally, after the record loop.
    assert(SnapWord(0, 0x1B8) == 0xB8B8B8B8u);
    // And the live-sourced fields still transfer.
    assert(SnapWord(0, 0x024) == LiveWord(0x3CC));
    assert(SnapWord(0, 0x1BC) == LiveWord(0x4474));
}

void TestCaptureRecordMap() {
    SlotSnapshotHooks hooks = MakeHooks();
    SlotSnapshotOwner owner = MakeOwner(0);
    SlotSnapshotEnv env = MakeEnv(0, 1);
    SeedLive();
    ClearSnapshots();

    SlotSnapshot_Run(&owner, &env, &hooks);

    const unsigned int* live_words = (const unsigned int*)g_live;
    const unsigned int* snap_words = (const unsigned int*)g_snapshots[0];
    // Four records, 38-dword live stride, 2-dword snapshot stride.
    for (int record = 0; record < 4; ++record) {
        const int live_base = 3256 + record * 38;
        const int snap_base = 86 + record * 2;
        for (int field = 0; field < 8; ++field) {
            assert(snap_words[snap_base + kSnapFields[field]] ==
                   live_words[live_base + kLiveFields[field]]);
        }
    }
    // The first record's lowest slot sits exactly where the bulk block ends,
    // so the two writes abut without overlapping.
    assert(snap_words[86 - 9] == live_words[3256 - 3]);
    assert((86 - 9) * 4 == 0x2C + 0x108);
}

void TestRestoreIsTheInverseOfCapture() {
    SlotSnapshotHooks hooks = MakeHooks();
    SlotSnapshotEnv env = MakeEnv(2, 1);
    SeedLive();
    ClearSnapshots();

    // Capture into slot 2...
    SlotSnapshotOwner capture_owner = MakeOwner(0);
    SlotSnapshot_Run(&capture_owner, &env, &hooks);

    unsigned char expected[kLiveSize];
    std::memcpy(expected, g_live, sizeof(expected));

    // ...scribble over every live field the restore half owns...
    unsigned int* live_words = (unsigned int*)g_live;
    for (int record = 0; record < 4; ++record) {
        const int live_base = 3256 + record * 38;
        for (int field = 0; field < 8; ++field) {
            live_words[live_base + kLiveFields[field]] = 0xDEADBEEFu;
        }
    }
    std::memset(g_live + 0x436C, 0xCC, 0x108);
    *(unsigned int*)(g_live + 0x4474) = 0xDEADBEEFu;

    // ...and restore it.
    hooks = MakeHooks();
    SlotSnapshotOwner restore_owner = MakeOwner(1);
    SlotSnapshot_Run(&restore_owner, &env, &hooks);

    assert(g_restore_calls == 1);
    assert(g_restore_block_seen == g_snapshots[2] + 0x24);
    assert(g_refresh_calls == 1 && g_commit_calls == 1);
    assert(restore_owner.active_slot == 2);
    assert(restore_owner.pending == 0);
    // Capture-only hooks stay untouched on the restore path.
    assert(g_prepare_calls == 0 && g_summary_calls == 0);

    // Every record field round-trips exactly.
    const unsigned int* expected_words = (const unsigned int*)expected;
    for (int record = 0; record < 4; ++record) {
        const int live_base = 3256 + record * 38;
        for (int field = 0; field < 8; ++field) {
            assert(live_words[live_base + kLiveFields[field]] ==
                   expected_words[live_base + kLiveFields[field]]);
        }
    }
    assert(std::memcmp(g_live + 0x436C, expected + 0x436C, 0x108) == 0);
    assert(LiveWord(0x4474) == *(unsigned int*)(expected + 0x4474));

    // The four counters are zeroed by the restore half.
    assert(LiveWord(0x332C) == 0);
    assert(LiveWord(0x33C4) == 0);
    assert(LiveWord(0x345C) == 0);
    assert(LiveWord(0x34F4) == 0);
}

void TestRestoreHookOrdering() {
    SlotSnapshotHooks hooks = MakeHooks();
    SlotSnapshotEnv env = MakeEnv(0, 1);
    SeedLive();
    ClearSnapshots();

    // Seed a recognizable tail value into the stored record.
    *(unsigned int*)(g_snapshots[0] + 0x1BC) = 0xA5A5A5A5u;

    SlotSnapshotOwner owner = MakeOwner(1);
    SlotSnapshot_Run(&owner, &env, &hooks);

    // refresh_derived runs after the bulk block and tail scalar are in place.
    assert(g_live_tail_at_refresh == 0xA5A5A5A5u);
    // commit_restore runs after the counters have been cleared.
    assert(g_cleared_at_commit == 0);
}

void TestShotSelectionDuplicatesLastPair() {
    SlotSnapshotHooks hooks = MakeHooks();
    SlotSnapshotEnv env = MakeEnv(0, 1);
    SeedLive();
    ClearSnapshots();

    // Fill the stored record with markers so the duplication is visible.
    unsigned int* stored = (unsigned int*)g_snapshots[0];
    for (int index = 0; index < kRecordSize / 4; ++index) {
        stored[index] = 0x20000000u + (unsigned int)index;
    }

    // Shot type 1 / variant 2 is the only combination that reaches 5.
    env.shot_type = 1;
    env.shot_variant = 2;
    SlotSnapshotOwner owner = MakeOwner(1);
    SlotSnapshot_Run(&owner, &env, &hooks);

    const unsigned int* live_words = (const unsigned int*)g_live;
    for (int record = 0; record < 4; ++record) {
        const int live_base = 3256 + record * 38;
        const int snap_base = 86 + record * 2;
        // The first six fields keep their normal sources.
        for (int field = 0; field < 6; ++field) {
            assert(live_words[live_base + kLiveFields[field]] ==
                   stored[snap_base + kSnapFields[field]]);
        }
        // The last pair is re-sourced from the first pair instead.
        assert(live_words[live_base + 3] == stored[snap_base - 9]);
        assert(live_words[live_base + 4] == stored[snap_base - 8]);
    }

    // Any other combination leaves the last pair alone.
    SeedLive();
    hooks = MakeHooks();
    env.shot_type = 0;
    env.shot_variant = 5;  // sums to 5 only if the type weight were ignored
    SlotSnapshotOwner plain = MakeOwner(1);
    // 0 * 3 + 5 == 5, so this pair does duplicate; the weighting is on type.
    SlotSnapshot_Run(&plain, &env, &hooks);
    assert(live_words[3256 + 3] == stored[86 - 9]);

    SeedLive();
    hooks = MakeHooks();
    env.shot_type = 1;
    env.shot_variant = 0;  // 3, not 5
    SlotSnapshotOwner normal = MakeOwner(1);
    SlotSnapshot_Run(&normal, &env, &hooks);
    assert(live_words[3256 + 3] == stored[86 + 15]);
    assert(live_words[3256 + 4] == stored[86 + 16]);
}

}  // namespace

int main() {
    TestDirtyBitsAlwaysSet();
    TestNullObjectsAreSkipped();
    TestCaptureWritesDefaultsAndScalars();
    TestCaptureSuppressedDefaults();
    TestCaptureRecordMap();
    TestRestoreIsTheInverseOfCapture();
    TestRestoreHookOrdering();
    TestShotSelectionDuplicatesLastPair();
    return 0;
}
