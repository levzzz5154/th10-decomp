// Compiler context only; never selected as recovered game code.
#include "../../src/game/entity_angle_from_point_00426660.cpp"

#pragma code_seg(".text$03context")
float __stdcall EntityAngleFromPointCompilerContext(
        EntityAngleFromPoint_00426660* entity, const float* point) {
    return entity->AngleFromPoint(point);
}
#pragma code_seg()
