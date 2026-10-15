// Compiler context: complete recovered angle helper and a public member caller.
#include "../../src/script/ecl_float_value_00412350.cpp"

#pragma code_seg(".text$04angle")
float Player::AngleFromPoint(const float* point) {
    float dx = position.x - point[0];
    float dy = position.y - point[1];
    if (dy == data_00470b04 && dx == data_00470b04)
        return data_00470b94;
    return (float)atan2((double)dy, (double)dx);
}
#pragma code_seg()

#pragma code_seg(".text$00context")
extern "C" float __stdcall EclFloatContext(EclFloatSource_00412350* object, int selector) {
    return object->ResolveFloatValue(selector);
}
#pragma code_seg()
