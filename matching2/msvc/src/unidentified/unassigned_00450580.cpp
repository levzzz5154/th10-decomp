#include "script_vm_00450560.hpp"
#pragma code_seg(".text$04trybind")
int ScriptVm_00450560::TryBind(ScriptTable_00450470* script_table, const char* name) {
    current->instruction = script_table->Resolve(name);
    current->time = 0;
    return current->instruction == 0;
}
#pragma code_seg()
