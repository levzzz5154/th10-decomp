// Compiler context only; never selected as recovered game code.
#include "../../src/game/player/player_angle_from_point.cpp"

#pragma code_seg(".text$03context")
float __stdcall EntityAngleFromPointCompilerContext(
        Player* entity, const float* point) {
    return entity->AngleFromPoint(point);
}
#pragma code_seg()
