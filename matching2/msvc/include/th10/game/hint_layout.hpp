#pragma once
// Retains the three pre-existing scheduler-order qualifiers from the selected
// 418E30 model. Six unforced models failed; these are not a new removal claim.
#include "th10/core/func_ctrl.hpp"
struct Hint;
struct HintDataRecord {
    Hint* owner;
    unsigned int unknown_04;
    unsigned int unknown_08;
};
struct Hint {
    unsigned int flags;
    unsigned int unknown_004;
    void* primary_task_008;
    void* volatile secondary_task_00C;
    void* volatile field_010;
    unsigned int unknown_014;
    HintDataRecord records[16];
    unsigned char remainder[0x1A8 - 0xD8];
    __declspec(noinline) Hint* InitializeLayout();
};
typedef char Hint_size[sizeof(Hint) == 0x1A8 ? 1 : -1];
typedef char Hint_record_offset[offsetof(Hint, records) == 0x18 ? 1 : -1];
extern "C" FuncCtrl* g_func_ctrl;
extern "C" volatile unsigned char data_00491d6a;
extern "C" Hint* g_hint;
extern "C" SchedulerTask* __stdcall SchedulerCallback_Create_00449ed0(void*);
extern "C" int __stdcall asm_FUN_00419960_00419960(Hint*, const char*, int);
extern "C" void __stdcall asm_FUN_00418ee0_00418ee0(void*);
extern "C" void __cdecl entry_free_004524a1(void*);
void* __cdecl operator new(unsigned int);
extern "C" __declspec(noinline) int __stdcall Hint_Initialize(Hint*);
Hint* __cdecl Hint_Create();
