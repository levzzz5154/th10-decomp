// Compiler context only; never selected as recovered game code.
#include "../../src/game/player_angle_to_point.cpp"

#pragma code_seg(".text$03context")
double __stdcall EntityAngleToPointCompilerContext(
        const float** points,
        const EntityAngleTarget_00426610** entities,
        int count) {
    double sum = 0.0;
    while (count--)
        sum += Entity_AngleToPoint(*entities++, *points++);
    return sum;
}
#pragma code_seg()
