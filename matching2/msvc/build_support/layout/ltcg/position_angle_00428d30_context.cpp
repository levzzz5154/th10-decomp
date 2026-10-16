// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_428d30.cpp"

#pragma code_seg(".text$03context")
extern "C" float __stdcall PositionAngleContext_00428d30(Position2** items, Position2* origin, int count) {
    float total = 0.0f;
    while (count--) {
        total += Position_00428d30_AngleTo(origin, *items++);
    }
    return total;
}
#pragma code_seg()
