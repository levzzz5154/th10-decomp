// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_0041f760.cpp"
#pragma code_seg(".text$03context")
float __stdcall VectorContext_0041f760(Vector2_0041f760** items, Vector2_0041f760** others, int count) {
    float total = 0.0f;
    while (count--) {
        total += (*items++)->DistanceSquared(*others++);
    }
    return total;
}
#pragma code_seg()
