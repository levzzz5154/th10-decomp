// Compiler context only; never selected as recovered game code.
// The array-walking caller is what makes the whole-program pass keep the
// record in ESI: it is live across the __ftol2 call, so it needs a
// callee-saved register, and the loop's own induction value stays in a
// scratch one.
#include "../../../src/unreferenced/unassigned_43e500.cpp"

#pragma code_seg(".text$03context")
int __stdcall TimeValueCompilerContext(TimeValue2** items, int count, float seconds) {
    while (count--)
        (*items++)->SetSeconds(seconds);
    return 0;
}
#pragma code_seg()
