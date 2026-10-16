#include "script_vm.hpp"
#pragma code_seg(".text$03bindtable")
int ScriptVm::BindTable(ScriptTable2* script_table, const char* name) {
    table = script_table;
    current->instruction = script_table->Resolve(name);
    current->time = 0;
    return 0;
}
#pragma code_seg()
