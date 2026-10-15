// Compiler context only; never selected as recovered game code.
#include "../../src/script/sptlib/final_script_runtime.cpp"

#pragma code_seg(".text$03context")
int __stdcall ScriptTable00450470CompilerContext(
        ScriptTable_00450470** tables, const char** names, int count) {
    int result = 0;
    while (count--) {
        result += (*tables++)->Resolve(*names++);
    }
    return result;
}
#pragma code_seg()
