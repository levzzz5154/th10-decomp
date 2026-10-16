#include "script_vm.hpp"
#pragma code_seg(".text$04trybind")
int ScriptVm::TryBind(ScriptTable2* script_table, const char* name) {
    current->instruction = script_table->Resolve(name);
    current->time = 0;
    return current->instruction == 0;
}
#pragma code_seg()
