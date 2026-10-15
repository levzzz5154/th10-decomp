#include "script_vm_00450560.hpp"
void* __cdecl operator new(unsigned int size);
extern "C" const unsigned int data_0046d0d8[];
inline ScriptVm_00450560::ScriptVm_00450560()
    : vtable(reinterpret_cast<unsigned int>(data_0046d0d8)), field_1010(0), field_1014(0) {}
// 0x00450500: create a script VM for the script viewer. Allocate the base VM, install its vtable, then bind the initial subroutine.
#pragma code_seg(".text$02create")
ScriptVm_00450560* ScriptTable_00450470::CreateVm(const char* name) {
    ScriptVm_00450560* vm = new ScriptVm_00450560;
    vm->table = this;
    vm->current->instruction = Resolve(name);
    vm->current->time = 0;
    return vm;
}
#pragma code_seg()
