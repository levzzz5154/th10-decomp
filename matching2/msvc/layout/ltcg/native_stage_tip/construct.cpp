#include <string.h>
#include "stage_tip.hpp"
static void SetOwner_00418d40(StageTipRecord* record,
                             StageTipManager* owner) {
    record->owner = owner;
}

static void SetOwnerPair_00418d40(StageTipRecord* record,
                                 StageTipManager* owner) {
    record[0].owner = owner;
    record[1].owner = owner;
}

static void ClearRecord_00418d40(StageTipRecord* record) {
    record->unknown_04 = 0;
    record->unknown_08 = 0;
}

#pragma code_seg(".text$a00construct")
StageTipManager* StageTipManager::InitializeLayout() {
    StageTipManager* manager = this;
    memset(manager, 0, sizeof(StageTipManager));
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
