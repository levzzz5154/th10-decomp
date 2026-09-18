// 0x00418D40..0x00418E2C (237 bytes): StageTipManager_Construct
//
// Zeroes the 0x1A8-byte stage-tip manager, raises its +0x00 flag, points each
// of its sixteen 12-byte records back at the manager, and publishes the
// finished manager through data_00477814.
//
// Retail receives the manager in EDX - a register no MSVC convention assigns -
// and the dead leading slot the fastcall declaration introduces is dropped by
// the whole-program pass, so this source is compiled inside the same native-LTCG
// link as the two functions that consume its result (see
// layout/ltcg/bullet_manager_load_scripts_0040ae70.json).
//
// The record stores are the part that took several waves.  A record's three
// stores must be split so that the owner store lands in its own inlined body:
// with a single three-store helper the pass schedules a record's owner store
// *after* that record's two zero stores (69 bytes from retail's schedule), and
// with the owners written as plain statements the pass groups all thirty-two
// zero stores in front of all sixteen owners (143 bytes).  Kept apart this way
// the pass emits the stores in exactly the source order, so the sixteen owners
// and zero pairs below are written in retail's order - including the two owner
// pairs retail hoists (records 0/1 and 8/9), which share one inlined body so the
// pair is emitted owner,owner before the pair's four zero stores.
#include <string.h>

struct StageTipRecord_00418d40 {
    void* owner;
    unsigned int unknown_04;
    unsigned int unknown_08;
};

struct StageTipManager_00418d40 {
    unsigned int flags;
    unsigned char pad_004[0x18 - 0x04];
    StageTipRecord_00418d40 records[16];
    unsigned char pad_0D8[0x1A8 - 0xD8];
};

extern "C" StageTipManager_00418d40* data_00477814;

static void SetOwner_00418d40(StageTipRecord_00418d40* record,
                             StageTipManager_00418d40* owner) {
    record->owner = owner;
}

static void SetOwnerPair_00418d40(StageTipRecord_00418d40* record,
                                 StageTipManager_00418d40* owner) {
    record[0].owner = owner;
    record[1].owner = owner;
}

static void ClearRecord_00418d40(StageTipRecord_00418d40* record) {
    record->unknown_04 = 0;
    record->unknown_08 = 0;
}

extern "C" __declspec(noinline) StageTipManager_00418d40* __fastcall
Construct_00418d40(int unused, StageTipManager_00418d40* manager);
#pragma code_seg(".text$00d_cxctor")
extern "C" __declspec(noinline) StageTipManager_00418d40* __fastcall
Construct_00418d40(int unused, StageTipManager_00418d40* manager) {
    memset(manager, 0, sizeof(StageTipManager_00418d40));
    manager->flags |= 2;
    SetOwnerPair_00418d40(&manager->records[0], manager);
    ClearRecord_00418d40(&manager->records[0]);
    ClearRecord_00418d40(&manager->records[1]);
    SetOwner_00418d40(&manager->records[2], manager);
    ClearRecord_00418d40(&manager->records[2]);
    SetOwner_00418d40(&manager->records[3], manager);
    ClearRecord_00418d40(&manager->records[3]);
    SetOwner_00418d40(&manager->records[4], manager);
    ClearRecord_00418d40(&manager->records[4]);
    SetOwner_00418d40(&manager->records[5], manager);
    ClearRecord_00418d40(&manager->records[5]);
    SetOwner_00418d40(&manager->records[6], manager);
    ClearRecord_00418d40(&manager->records[6]);
    SetOwner_00418d40(&manager->records[7], manager);
    ClearRecord_00418d40(&manager->records[7]);
    SetOwnerPair_00418d40(&manager->records[8], manager);
    ClearRecord_00418d40(&manager->records[8]);
    ClearRecord_00418d40(&manager->records[9]);
    SetOwner_00418d40(&manager->records[10], manager);
    ClearRecord_00418d40(&manager->records[10]);
    SetOwner_00418d40(&manager->records[11], manager);
    ClearRecord_00418d40(&manager->records[11]);
    SetOwner_00418d40(&manager->records[12], manager);
    ClearRecord_00418d40(&manager->records[12]);
    SetOwner_00418d40(&manager->records[13], manager);
    ClearRecord_00418d40(&manager->records[13]);
    SetOwner_00418d40(&manager->records[14], manager);
    ClearRecord_00418d40(&manager->records[14]);
    SetOwner_00418d40(&manager->records[15], manager);
    ClearRecord_00418d40(&manager->records[15]);
    data_00477814 = manager;
    return manager;
}
#pragma code_seg()
