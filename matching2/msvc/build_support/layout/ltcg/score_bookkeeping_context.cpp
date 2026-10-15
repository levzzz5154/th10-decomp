// Compiler context only; this caller is never selected as recovered game code.
// The shared LTCG unit recovers the observed argument and register allocation.
#include "../units/score_bookkeeping_7e27a0.cpp"

#pragma code_seg(".text$99context")
void __stdcall ScoreCompilerContext(ScoreState** states, const int* amounts, int count) {
    for (int index = 0; index < count; ++index) {
        states[index]->AddScore(amounts[index]);
        states[index]->ReduceGauge(amounts[index]);
        states[index]->IncrementCappedCount();
        states[index]->SetGauge(amounts[index]);
        states[index]->AddGauge(amounts[index]);
    }
}
#pragma code_seg()
