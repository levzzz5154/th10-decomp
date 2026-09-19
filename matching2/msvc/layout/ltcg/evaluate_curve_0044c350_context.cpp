// Compiler context only; never selected as recovered game code.
#include "../../src/game/fun_0044c350_0044c350.cpp"

#pragma code_seg(".text$03context")
float __stdcall EvaluateCurveCompilerContext(const unsigned int* modes,
                                              const float* numerators,
                                              const float* denominators,
                                              int count) {
    float total = 0.0f;
    while (count--)
        total += EvaluateCurve_0044c350(*modes++, *numerators++, *denominators++);
    return total;
}
#pragma code_seg()
