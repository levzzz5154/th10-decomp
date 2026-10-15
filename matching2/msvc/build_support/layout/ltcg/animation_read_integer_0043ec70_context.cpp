// Compiler context only; never selected as recovered game code.
#include "../units/animation_manager_12b25f.cpp"

#pragma code_seg(".text$05context")
int __stdcall AnimationReadIntegerCompilerContext(
        AnimationObjectVariables** objects, SprtCtrl** managers,
        AnimationLookupContext** contexts, const int* variables, int count) {
    int total = 0;
    while (count--) {
        int variable = *variables++;
        total += (*objects++)->ReadIntegerVariable(variable);
        (*managers++)->SetFlag(*contexts++, variable);
    }
    return total;
}
#pragma code_seg()
