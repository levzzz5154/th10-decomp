// Compiler context only; not selected as recovered code.
#include "../../../src/script/sptlib/fun_00450700_00450700.cpp"
#pragma code_seg(".text$07context")
extern "C" int __stdcall ScriptResolverContext(ScriptVm** vms, ScriptTable_00450470** tables, const char** names, int count) {
    int result = 0;
    while(count--) {
        result += (*vms)->BindTable(*tables, *names);
        result += (*vms)->TryBind(*tables, *names);
        result += BindName(*names++, *vms++);
        result += (*tables++)->CreateVm(*names)->field_1010;
    }
    return result;
}
#pragma code_seg()
