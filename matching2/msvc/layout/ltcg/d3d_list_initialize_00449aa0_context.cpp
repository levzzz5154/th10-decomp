// Compiler context only; never selected as recovered game code.
#include "../../src/core/zunlib/func_ctrl_initialize.cpp"
#pragma code_seg(".text$03context")
void __stdcall D3DInitializeCompilerContext(FuncCtrlInitializeView** items, int count) {
    while (count--) (*items++)->Initialize();
}
#pragma code_seg()
