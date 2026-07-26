// =============================================================================
// slot_snapshot.hpp - Per-slot game-state snapshot capture/restore
// Retail function: 0x0042A450
//
// The owner drives one of two directions per call. Mode 0 captures the live
// game state into the owner's snapshot for the active slot; mode 1 restores a
// previously captured record back into the live state. Any other mode only
// marks the three tracked objects dirty and clears the pending word.
// =============================================================================
#ifndef TH10_GAME_SLOT_SNAPSHOT_HPP
#define TH10_GAME_SLOT_SNAPSHOT_HPP

// Retail default block at 0x00474C44..0x00474C9C, written into a freshly
// captured snapshot when the suppression flag (0x00491FC4) is clear.
struct SlotSnapshotDefaults {
    unsigned int field_0c;   // 0x00474C44 -> snapshot +0x00C
    unsigned short field_10; // 0x00474C48 -> snapshot +0x010 (16-bit store)
    unsigned int field_14;   // 0x00474C4C -> snapshot +0x014
    unsigned int field_18;   // 0x00474C58 -> snapshot +0x018
    unsigned int field_1c;   // 0x00474C70 -> snapshot +0x01C
    unsigned int field_20;   // 0x00474C98 -> snapshot +0x020
    unsigned int field_1b4;  // 0x00474C90 -> snapshot +0x1B4
    unsigned int field_1b8;  // 0x00474C9C -> snapshot +0x1B8
};

// The globals this function reads. Retail reaches each one directly.
struct SlotSnapshotEnv {
    unsigned char* live;         // 0x00477834: live game-state block
    int slot;                    // 0x00474C7C: active slot index
    int suppress_defaults;       // 0x00491FC4: non-zero skips the defaults
    int shot_type;               // 0x00474C68
    int shot_variant;            // 0x00474C6C
    const SlotSnapshotDefaults* defaults;
};

// One entry of the restore table at owner +0xB0. Retail strides this table by
// 0x24 bytes and only dereferences its leading pointer.
struct SlotSnapshotRecordSlot {
    unsigned char* record;
    int reserved[8];  // retail +0x04..+0x23
};

// The owner fields touched by 0x0042A450, with their retail offsets.
struct SlotSnapshotOwner {
    unsigned int* dirty_a;              // +0x008: flags word lives at +4
    unsigned int* dirty_c;              // +0x00C
    unsigned int* dirty_b;              // +0x1CC
    int mode;                           // +0x010: 0 captures, 1 restores
    unsigned char** snapshots;          // +0x01C: one pointer per slot
    SlotSnapshotRecordSlot* records;    // +0x0B0: restore table
    int summary;                        // +0x09C: capture_summary result
    int active_slot;                    // +0x1D0
    int pending;                        // +0x1C8: always cleared on exit
};

// The four retail helpers called around the block copies.
struct SlotSnapshotHooks {
    void* context;
    void (*prepare_slot)(void* context, int slot,
                         SlotSnapshotOwner* owner);            // 0x0042AB20
    int (*capture_summary)(void* context, int slot,
                           SlotSnapshotOwner* owner);          // 0x0042AA50
    void (*restore_scores)(void* context, unsigned char* live,
                           unsigned char* record_block);       // 0x00428E10
    void (*refresh_derived)(void* context, unsigned char* live);  // 0x00426F70
    void (*commit_restore)(void* context, unsigned char* live);   // 0x00424D90
};

// 0x0042A450.
void SlotSnapshot_Run(SlotSnapshotOwner* owner, const SlotSnapshotEnv* env,
                      const SlotSnapshotHooks* hooks);

#endif  // TH10_GAME_SLOT_SNAPSHOT_HPP
