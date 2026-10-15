// 0x00401FB0: store a value into the large state object's field at +0x898C.
//
// Retail: 89 88 8C 89 00 00   mov [eax+0x898C], ecx
//         C3                  ret
// The object pointer arrives in EAX and the stored value in ECX, so this is
// compiled as a native LTCG cluster (see build_support/layout/ltcg/fun_00401fb0.json).

struct FUN_00401fb0_State {
    char unknown[0x898C];
    int field_898C;

    __declspec(noinline) void StoreValue(int value);
};

#pragma code_seg(".text$01store")
void FUN_00401fb0_State::StoreValue(int value) {
    this->field_898C = value;
}
#pragma code_seg()
