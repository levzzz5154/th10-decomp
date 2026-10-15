// 0x0044C260..0x0044C299 (58 bytes): refresh a polar-motion record.
//
// Bit 0 of the +0x28 flag word selects the shape. When it is set the record
// advances its own scalar field at +0x20 by the +0x24 delta and re-normalizes
// the accumulated angle into the +0x1C slot; when it is clear the pair
// (+0x1C, +0x18) is converted through the retail polar routine at 0x0044C5D0
// into the +0x0C vector and the state word at +0x14 is cleared.
//
// The record arrives in ESI, a receiver no C++ declaration names, so the body
// is compiled in the native-LTCG cluster build_support/layout/ltcg/polar_update_0044c260.json
// whose array-walking synthetic caller establishes that convention. Both
// callees keep the conventions a declaration already names: 0x0044C5D0 is a
// __fastcall reached with its destination pointer in ECX and the two floats on
// the stack, and Angle_Normalize is the recovered __stdcall at 0x0044BC70.

struct Vec2_0044c260 {
    float x;                        // +0x0C
    float y;                        // +0x10
};

struct PolarMotion_0044c260 {
    unsigned char unknown_0000[0x0C];
    Vec2_0044c260 direction;        // +0x0C
    int state;                      // +0x14
    float field_18;                 // +0x18
    float angle;                    // +0x1C
    float field_20;                 // +0x20
    float delta;                    // +0x24
    unsigned char flags;            // +0x28
};

extern "C" void __fastcall asm_Recovery_PolarToVectorRetail_0044c5d0(
        Vec2_0044c260* destination, float angle, float radius);
float __stdcall Angle_Normalize(float angle);

__declspec(noinline) void PolarMotion_0044c260_Update(PolarMotion_0044c260* motion);

#pragma code_seg(".text$01polar")
void PolarMotion_0044c260_Update(PolarMotion_0044c260* motion) {
    if ((motion->flags & 1) == 0) {
        asm_Recovery_PolarToVectorRetail_0044c5d0(
                &motion->direction, motion->angle, motion->field_18);
        motion->state = 0;
    } else {
        motion->field_20 += motion->delta;
        motion->angle = Angle_Normalize(motion->field_18 + motion->angle);
    }
}
#pragma code_seg()
