// 0x00428D60..0x00428D63 (4 bytes): the float at +0x2C.
//
// Retail is `fld dword ptr [eax+2Ch]` / `ret`: the record arrives in EAX and
// the value is left in ST(0).  The two leaves before it in the same block work
// on the same record: 0x00428D30 is atan2 of the (+0x00,+0x04) pair against a
// second record and 0x00428D40 is the squared distance of that pair, so the
// first two floats are a position and this field is a third scalar.

struct MotionRecord_00428d60 {
    float x;                       // +0x00
    float y;                       // +0x04
    unsigned char unknown_08[0x24];
    float value;                   // +0x2C

    __declspec(noinline) float GetValue();
};

#pragma code_seg(".text$01get")
float MotionRecord_00428d60::GetValue() {
    return value;
}
#pragma code_seg()
