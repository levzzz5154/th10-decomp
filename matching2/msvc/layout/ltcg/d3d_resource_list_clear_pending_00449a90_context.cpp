// Compiler context only; never selected as recovered game code.
#include "../../src/core/zunlib/d3d_resource_manager.cpp"

#pragma code_seg(".text$03context")
void __stdcall D3DResourceListClearCompilerContext(D3DResourceList_ClearPending_00449a90** items, int count) {
    while (count--)
        (*items++)->ClearPending();
}
#pragma code_seg()
