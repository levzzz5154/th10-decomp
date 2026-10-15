// Compiler context only; never selected as recovered game code.
#include "../../../src/game/title/title_set_timer_target.cpp"

#pragma code_seg(".text$03context")
int __stdcall TitleOptionsTimer0042c620CompilerContext(
    Title** states, int* targets, int count) {
    int total = 0;
    while (count--) {
        int target = *targets++;
        (*states++)->SetTimerTarget(target);
        total += target;
    }
    return total;
}
#pragma code_seg()
