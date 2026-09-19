// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_00412ef0.cpp"
#pragma code_seg(".text$03context")
float __stdcall VectorContext_00412ef0(Vector2_00412ef0** items, Vector2_00412ef0** others, int count) {
    float total = 0.0f;
    while (count--) {
        total += (*items++)->DistanceSquared(*others++);
    }
    return total;
}
#pragma code_seg()
