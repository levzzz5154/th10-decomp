// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_412ef0.cpp"
#pragma code_seg(".text$03context")
float __stdcall VectorContext_00412ef0(Vector22** items, Vector22** others, int count) {
    float total = 0.0f;
    while (count--) {
        total += (*items++)->DistanceSquared(*others++);
    }
    return total;
}
#pragma code_seg()
