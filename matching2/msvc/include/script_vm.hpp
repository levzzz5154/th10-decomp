#ifndef SCRIPT_VM_00450560_HPP
#define SCRIPT_VM_00450560_HPP
#include "script_resolver.hpp"
struct ScriptFrame2 { int time; int instruction; };
struct ScriptVm {
    ScriptVm();
    unsigned int vtable;
    ScriptFrame2* current;
    unsigned char reserved_0008[0x1010-8];
    int field_1010;
    int field_1014;
    unsigned char reserved_1018[0x102C-0x1018];
    ScriptTable2* table;
    unsigned char reserved_1030[12];
    __declspec(noinline) int BindTable(ScriptTable2* script_table, const char* name);
    __declspec(noinline) int TryBind(ScriptTable2* script_table, const char* name);
};
__declspec(noinline) int __fastcall BindName(const char* name, ScriptVm* vm);
#endif
