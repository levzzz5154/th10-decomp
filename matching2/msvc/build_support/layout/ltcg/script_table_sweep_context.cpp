#include "../../../src/game/background/anm_script_table_sweep.cpp"
#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) int __stdcall SweepContext(ScriptTableSweep* table, int count) {
    int result=0;
    while (count--) result+=table->Sweep();
    return result;
}
#pragma code_seg()
