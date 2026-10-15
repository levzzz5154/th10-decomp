// Compiler context: complete recovered angle helper and a public member caller.
#include "../../../src/game/enemy/ecl_float_value_00412350.cpp"

#pragma code_seg(".text$04angle")
float Player::AngleFromPoint(const float* point) {
    float dx = position.x - point[0];
    float dy = position.y - point[1];
    if (dy == flt_0 && dx == flt_0)
        return flt_pi_2;
    return (float)atan2((double)dy, (double)dx);
}
#pragma code_seg()

#pragma code_seg(".text$00context")
extern "C" float __stdcall EclFloatContext(EclFloatSource_00412350* object, int selector) {
    return object->ResolveFloatValue(selector);
}
#pragma code_seg()
