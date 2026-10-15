// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_0044dcf0.cpp"

#pragma code_seg(".text$03context")
int __stdcall StreamStateInitializer0044DCF0CompilerContext(
        StreamState** states,
        void** values_090, void** values_080,
        int* values_088, int* counts, int count) {
    int result = 0;
    while (count-- > 0) {
        result += (*states++)->Initialize(
                *values_090++, *values_080++, *values_088++, *counts++);
    }
    return result;
}
#pragma code_seg()
