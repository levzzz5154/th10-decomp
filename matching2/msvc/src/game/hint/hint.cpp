#include <string.h>
#include "th10/game/hint_layout.hpp"
static void SetOwner_00418d40(HintDataRecord* record,
                             Hint* owner) {
    record->owner = owner;
}

static void SetOwnerPair_00418d40(HintDataRecord* record,
                                 Hint* owner) {
    record[0].owner = owner;
    record[1].owner = owner;
}

static void ClearRecord_00418d40(HintDataRecord* record) {
    record->unknown_04 = 0;
    record->unknown_08 = 0;
}

#pragma code_seg(".text$a00construct")
Hint* Hint::InitializeLayout() {
    Hint* manager = this;
    memset(manager, 0, sizeof(Hint));
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
    g_hint = manager;
    return manager;
}
#pragma code_seg()


#include "th10/game/hint_layout.hpp"
#pragma code_seg(".text$a02initialize")
extern "C" __declspec(noinline) int __stdcall Hint_Initialize(Hint* manager) {
    SchedulerTask* primary = SchedulerCallback_Create_00449ed0((void*)0x4198A0);
    primary->context = manager;
    primary->reserved_flags &= ~1u;
    FuncCtrl_RegisterPrimary(g_func_ctrl, primary, 0x19);
    manager->primary_task_008 = primary;

    SchedulerTask* secondary = SchedulerCallback_Create_00449ed0((void*)0x4198B0);
    secondary->reserved_flags &= ~1u;
    secondary->context = manager;
    FuncCtrl_RegisterSecondary(g_func_ctrl, secondary, 0x2C);
    manager->secondary_task_00C = secondary;
    manager->field_010 = 0;

    if (data_00491d6a) {
        asm_FUN_00419960_00419960(manager, (const char*)0x46D6D8, 0);
        asm_FUN_00419960_00419960(manager, (const char*)0x46D6C4, 1);
    }
    return 0;
}
#pragma code_seg()


#include "th10/game/hint_layout.hpp"
#pragma code_seg(".text$a04factory")
__declspec(noinline) Hint* __cdecl Hint_Create() {
    Hint* block = new Hint;
    Hint* manager;
    if (block)
        manager = block->InitializeLayout();
    else
        manager = 0;
    if (Hint_Initialize(manager)) {
        if (manager) {
            asm_FUN_00418ee0_00418ee0(manager);
            entry_free_004524a1(manager);
        }
        return 0;
    }
    return manager;
}
#pragma code_seg()
