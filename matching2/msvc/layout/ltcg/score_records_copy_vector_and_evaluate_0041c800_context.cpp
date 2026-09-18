// Compiler context only; never selected as recovered game code.
//
// The array-walking caller is what makes the whole-program pass pick the
// observed retail internal convention for
// ScoreRecords_0041c800::CopyVectorAndEvaluate: receiver in EAX, vector in EBX,
// the float value and the int flag on the stack, result in EAX and RET 8.  The
// callee's own shape pins the same convention for every context shape tried, so
// this driver only needs to hand it a receiver and a vector.
#include "../../src/game/score_records_copy_vector_and_evaluate_0041c800.cpp"

#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) int __stdcall ScoreRecordsCopyVectorAndEvaluateContext(
        ScoreRecords_0041c800** records, int count, const float* vector, float value, int flag) {
    int total = 0;
    while (count--) {
        total += (*records++)->CopyVectorAndEvaluate(vector, value, flag);
    }
    return total;
}
#pragma code_seg()
