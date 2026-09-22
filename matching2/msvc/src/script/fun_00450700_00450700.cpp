#include "script_vm_00450560.hpp"
// 0x00450700: bind a named subroutine and reset its frame time.
#pragma code_seg(".text$05bindname")
int __fastcall BindName_00450700(const char* name, ScriptVm_00450560* vm) {
    ScriptTable_00450470* script_table = vm->table;
    vm->table = script_table;
    vm->current->instruction = script_table->Resolve(name);
    vm->current->time = 0;
    return 0;
}
#pragma code_seg()
