// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_405220.cpp"

#pragma code_seg(".text$03context")
float __stdcall Vector3CompilerContext_00405220(Vector33** items, int count) {
    float sum = 0.0f;
    for (int index = 0; index < count; ++index)
        sum += items[index]->LengthSquared();
    return sum;
}
#pragma code_seg()
