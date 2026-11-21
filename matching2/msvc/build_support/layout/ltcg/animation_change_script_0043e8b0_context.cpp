// Compiler-context driver for the selected script changer at 0x0043E8B0.
// Pairs the changer body with its real caller (the handle wrapper), the lookup
// anchor and the synthetic array-walking entry so this whole translation unit
// reproduces the measurement's link context exactly.
#include "../../../src/core/sprtlib/animation_handle_change_script.cpp"
#include "../../../src/core/sprtanim/animation_change_script.cpp"
#include "script_change_find_anchor.cpp"
#pragma code_seg(".text$07context")
extern "C" int __stdcall ScriptChangeCompilerContext(ScriptChangeHandle* handles, int count, int index) {
    while (count--) { handles->ChangeScript(index); ++handles; }
    return index;
}
#pragma code_seg()
