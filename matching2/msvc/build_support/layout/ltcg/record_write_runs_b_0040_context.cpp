// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/record_write_runs_b_0040.cpp"

#pragma code_seg(".text$05context")
extern "C" int __stdcall RecordWriteRunsBCompilerContext(void** items, int count) {
    for (int index = 0; index < count; ++index)
        ((WriteRunB_004020b0*)items[index])->Clear();
    for (int index = 0; index < count; ++index)
        ((WriteRunB_0044c0e0*)items[index])->Init();
    return 0;
}
#pragma code_seg()
