// 0x00428F20..0x00428F23 (4 bytes): the float at +0x34.
//
// Retail is `fld dword ptr [eax+34h]` / `ret`: the record arrives in EAX and
// the value is left in ST(0).

struct ScalarRecord {
    unsigned char unknown_00[0x34];
    float value;                   // +0x34

    __declspec(noinline) float GetValue();
};

#pragma code_seg(".text$01get")
float ScalarRecord::GetValue() {
    return value;
}
#pragma code_seg()
