// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/unassigned_00427d30.cpp"

#pragma code_seg(".text$03context")
extern "C" int __stdcall pair_matches_00427d30Context_00427d30(Pair_00427d30** items, int id, int count) {
    while (count--) {
        Pair_00427d30_Matches(*items++, id);
    }
    return 0;
}
#pragma code_seg()
