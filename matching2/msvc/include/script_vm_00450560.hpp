#ifndef SCRIPT_VM_00450560_HPP
#define SCRIPT_VM_00450560_HPP
#include "script_resolver_00450470.hpp"
struct ScriptFrame_00450560 { int time; int instruction; };
struct ScriptVm {
    ScriptVm();
    unsigned int vtable;
    ScriptFrame_00450560* current;
    unsigned char reserved_0008[0x1010-8];
    int field_1010;
    int field_1014;
    unsigned char reserved_1018[0x102C-0x1018];
    ScriptTable_00450470* table;
    unsigned char reserved_1030[12];
    __declspec(noinline) int BindTable(ScriptTable_00450470* script_table, const char* name);
    __declspec(noinline) int TryBind(ScriptTable_00450470* script_table, const char* name);
};
__declspec(noinline) int __fastcall BindName(const char* name, ScriptVm* vm);
#endif
