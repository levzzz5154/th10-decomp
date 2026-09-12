// 0x0042A450 - Capture or restore the per-slot game-state snapshot.
//
// The retail body is one function with two mirrored halves. Mode 0 gathers the
// live game state into the owner's snapshot for the active slot; mode 1 pushes
// a stored record back into the live state. The two halves use exactly
// inverted index maps, which is the strongest evidence for the shared record
// layout modelled below.
#include "th10/game/slot_snapshot.hpp"

#include <cstring>

namespace {

// Retail offsets, in dwords, into the live state and the snapshot.
//
// The live state stores four records with a 38-dword stride starting at
// 0x32E0. The snapshot stores the same four records with a 2-dword stride
// starting at 0x158, using fixed sub-offsets. Capture reads live[base + k] for
// k in {-3,-2,-1,0,1,2,3,4} and writes snapshot[base + m] for m in
// {-9,-8,-1,0,7,8,15,16}; restore performs the identical mapping in reverse.
const int kLiveRecordBase = 0x32E0 / 4;    // 3256
const int kLiveRecordStride = 38;
const int kSnapshotRecordBase = 0x158 / 4; // 86
const int kSnapshotRecordStride = 2;
const int kRecordCount = 4;
const int kRecordFields = 8;

const int kLiveFieldOffsets[kRecordFields] = {-3, -2, -1, 0, 1, 2, 3, 4};
const int kSnapshotFieldOffsets[kRecordFields] = {-9, -8, -1, 0, 7, 8, 15, 16};

// The trailing 66-dword block copied wholesale in both directions.
const int kBulkLiveOffset = 0x436C;
const int kBulkSnapshotOffset = 0x2C;
const unsigned int kBulkBytes = 0x108;  // 66 dwords

// Scalars mirrored alongside the bulk block.
const int kLiveTailOffset = 0x4474;
const int kSnapshotTailOffset = 0x1BC;

// Counters the restore half zeroes once the records are back in place.
const int kClearedLiveOffsets[4] = {0x332C, 0x33C4, 0x345C, 0x34F4};

unsigned int* DwordsAt(unsigned char* base, int byte_offset) {
    return (unsigned int*)(base + byte_offset);
}

void MarkDirty(unsigned int* object) {
    // Retail sets bit 1 of the flags word at +4, and skips null objects.
    if (object != 0) {
        object[1] |= 2u;
    }
}

}  // namespace

void SlotSnapshot_Run(SlotSnapshotOwner* owner, const SlotSnapshotEnv* env,
                      const SlotSnapshotHooks* hooks) {
    // The three tracked objects are marked dirty before any mode dispatch, so
    // even the fall-through mode performs this much work.
    MarkDirty(owner->dirty_a);
    MarkDirty(owner->dirty_b);
    MarkDirty(owner->dirty_c);

    unsigned char* live = env->live;
    const int slot = env->slot;

    if (owner->mode == 0) {
        unsigned char* snapshot = owner->snapshots[slot];

        hooks->prepare_slot(hooks->context, slot, owner);
        owner->summary = hooks->capture_summary(hooks->context, slot, owner);

        // The default block is stamped in only when the suppression flag is
        // clear; a replay or continued run keeps whatever it already had.
        if (env->suppress_defaults == 0) {
            const SlotSnapshotDefaults* defaults = env->defaults;
            *DwordsAt(snapshot, 0x00C) = defaults->field_0c;
            // Retail stores this one as a 16-bit value, leaving +0x012 alone.
            *(unsigned short*)(snapshot + 0x010) = defaults->field_10;
            *DwordsAt(snapshot, 0x014) = defaults->field_14;
            *DwordsAt(snapshot, 0x018) = defaults->field_18;
            *DwordsAt(snapshot, 0x01C) = defaults->field_1c;
            *DwordsAt(snapshot, 0x020) = defaults->field_20;
            *DwordsAt(snapshot, 0x1B4) = defaults->field_1b4;
        }

        *DwordsAt(snapshot, 0x024) = *DwordsAt(live, 0x3CC);
        *DwordsAt(snapshot, 0x028) = *DwordsAt(live, 0x3D0);

        std::memcpy(snapshot + kBulkSnapshotOffset, live + kBulkLiveOffset,
                    kBulkBytes);

        const unsigned int* live_records = (const unsigned int*)live;
        unsigned int* snapshot_records = (unsigned int*)snapshot;
        for (int record = 0; record < kRecordCount; ++record) {
            const int live_base = kLiveRecordBase + record * kLiveRecordStride;
            const int snapshot_base =
                kSnapshotRecordBase + record * kSnapshotRecordStride;
            for (int field = 0; field < kRecordFields; ++field) {
                snapshot_records[snapshot_base + kSnapshotFieldOffsets[field]] =
                    live_records[live_base + kLiveFieldOffsets[field]];
            }
        }

        *DwordsAt(snapshot, 0x1B8) = env->defaults->field_1b8;

        owner->active_slot = slot;
        // Retail re-reads the slot pointer here rather than reusing the local.
        *DwordsAt(owner->snapshots[slot], kSnapshotTailOffset) =
            *DwordsAt(live, kLiveTailOffset);
    } else if (owner->mode == 1) {
        unsigned char* record_base = owner->records[slot].record;
        owner->active_slot = slot;

        hooks->restore_scores(hooks->context, live, record_base + 0x24);

        std::memcpy(live + kBulkLiveOffset, record_base + kBulkSnapshotOffset,
                    kBulkBytes);
        *DwordsAt(live, kLiveTailOffset) =
            *DwordsAt(record_base, kSnapshotTailOffset);

        hooks->refresh_derived(hooks->context, live);

        // The same record map as the capture half, driven the other way.
        unsigned int* live_records = (unsigned int*)live;
        const unsigned int* stored_records = (const unsigned int*)record_base;
        // Retail folds the shot selection into one comparison; type 1 with
        // variant 2 is the only pair that reaches 5.
        const bool duplicate_last_pair =
            (env->shot_type * 3 + env->shot_variant) == 5;
        for (int record = 0; record < kRecordCount; ++record) {
            const int live_base = kLiveRecordBase + record * kLiveRecordStride;
            const int stored_base =
                kSnapshotRecordBase + record * kSnapshotRecordStride;
            for (int field = 0; field < kRecordFields; ++field) {
                live_records[live_base + kLiveFieldOffsets[field]] =
                    stored_records[stored_base + kSnapshotFieldOffsets[field]];
            }
            if (duplicate_last_pair) {
                // The final pair is re-sourced from the first pair instead.
                live_records[live_base + kLiveFieldOffsets[6]] =
                    stored_records[stored_base + kSnapshotFieldOffsets[0]];
                live_records[live_base + kLiveFieldOffsets[7]] =
                    stored_records[stored_base + kSnapshotFieldOffsets[1]];
            }
        }

        for (int index = 0; index < 4; ++index) {
            *DwordsAt(live, kClearedLiveOffsets[index]) = 0;
        }

        hooks->commit_restore(hooks->context, live);
    }

    owner->pending = 0;
}
