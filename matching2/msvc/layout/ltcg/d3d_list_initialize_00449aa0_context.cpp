// Compiler context only; never selected as recovered game code.
#include "../../src/render/d3_d_resource_manager_initialize_00449aa0.cpp"
#pragma code_seg(".text$03context")
void __stdcall D3DInitializeCompilerContext(D3DResourceManager_00449AA0** items, int count) {
    while (count--) (*items++)->Initialize();
}
#pragma code_seg()
