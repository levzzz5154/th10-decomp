// 0x00404410: set the state flag at +0x1EE4 of the object whose address
// arrives in EAX.
//
// Retail: C7 80 E4 1E 00 00 01 00 00 00  mov dword ptr [eax+0x1EE4], 1
//         C3                             ret
// The object pointer arrives in EAX, so the setter is compiled as a native LTCG
// cluster (see layout/ltcg/fun_00404410.json).

struct FUN_00404410_State {
    char unknown[0x1EE4];
    int flag_1EE4;

    __declspec(noinline) void SetFlag();
};

#pragma code_seg(".text$01setflag")
void FUN_00404410_State::SetFlag() {
    this->flag_1EE4 = 1;
}
#pragma code_seg()
