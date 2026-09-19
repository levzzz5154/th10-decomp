// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_00424530.cpp"
#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) int __stdcall InitializeRecordContext_00424530(
        Record_00424530** records, int** values, int count) {
    int result = 0;
    for (int index = 0; index < count; ++index) {
        int* value = values[index];
        result += InitializeRecord_00424530(
            records[index], value[0], value[1], value[2], value[3], value[4],
            value[5], value[6], value[7], value[8], value[9]);
    }
    return result;
}
#pragma code_seg()
