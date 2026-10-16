// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/record_write_runs_b_0040.cpp"

#pragma code_seg(".text$05context")
extern "C" int __stdcall RecordWriteRunsBCompilerContext(void** items, int count) {
    for (int index = 0; index < count; ++index)
        ((WriteRunB*)items[index])->Clear();
    for (int index = 0; index < count; ++index)
        ((WriteRunB2*)items[index])->Init();
    return 0;
}
#pragma code_seg()
