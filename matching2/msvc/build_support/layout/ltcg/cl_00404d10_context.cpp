// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_00404d10.cpp"

#pragma code_seg(".text$03anchor")
__declspec(noinline) float __stdcall EvaluateCurveAnchor_0044c350(unsigned int op, float first,
                                                                 float second) {
    switch (op) {
    case 1: return first + second;
    case 2: return first - second;
    case 3: return first * second;
    case 4: return first / second;
    case 5: return second - first;
    case 6: return second / first;
    case 7: return (first + second) * 0.5f;
    case 8: return (first - second) * 0.5f;
    case 9: return first > second ? first : second;
    case 10: return first < second ? first : second;
    case 11: return -first;
    case 12: return -second;
    case 13: return first * first + second * second;
    case 14: return first * second - 1.0f;
    case 15: return 1.0f - first * second;
    case 16: return first + second * 2.0f;
    default: return 0.0f;
    }
}
#pragma code_seg()

#pragma code_seg(".text$05context")
float __stdcall EvaluateContext_00404d10(CurveObject_00404d10** items, int count) {
    float total = 0.0f;
    while (count--) {
        total += (*items++)->Evaluate();
    }
    return total;
}
#pragma code_seg()
