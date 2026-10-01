#include "../../src/render/animation_handle_change_script_004496d0.cpp"
#include "script_change_body_anchor.cpp"
#include "script_change_find_anchor.cpp"
#pragma code_seg(".text$07context")
extern "C" int __stdcall ScriptChangeCompilerContext(ScriptChangeHandle* handles, int count, int index) {
    while (count--) { handles->ChangeScript(index); ++handles; }
    return index;
}
#pragma code_seg()
