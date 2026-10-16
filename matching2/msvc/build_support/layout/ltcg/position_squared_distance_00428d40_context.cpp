// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_428d40.cpp"

#pragma code_seg(".text$03context")
extern "C" float __stdcall PositionDistanceContext_00428d40(Position3** items, Position3* origin, int count) {
    float total = 0.0f;
    while (count--) {
        total += Position_00428d40_SquaredDistance(*items++, origin);
    }
    return total;
}
#pragma code_seg()
