#ifndef SCRIPT_RESOLVER_00450470_HPP
#define SCRIPT_RESOLVER_00450470_HPP
// 0x00450470..0x004504F7: sorted script-table lookup.
//
// Native LTCG supplies the private retail convention for this member:
// the table object arrives in EAX, the label remains on the stack, and
// the integer result is returned with RET 4.
struct ScriptEntry_00450470 {
    const char* name;
    unsigned int value;
};

struct ScriptVm;
struct ScriptTable_00450470 {
    unsigned int reserved_00;
    unsigned int reserved_04;
    int count;
    unsigned int reserved_0C[0x20];
    const ScriptEntry_00450470* entries;

    __declspec(noinline) int Resolve(const char* name);
    __declspec(noinline) ScriptVm* CreateVm(const char* name);
};


#endif
