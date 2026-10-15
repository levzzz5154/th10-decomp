// 0x00427C40..0x00427C43 (4 bytes): subtract from the dword at +0x30.
//
// Retail subtracts the incoming value from the field in place and returns
// nothing.  The object arrives in EAX and the value in ECX, so the two are
// register arguments no C++ declaration names; the body is compiled in the
// native-LTCG cluster build_support/layout/ltcg/counter_subtract.json whose
// synthetic caller establishes that pair.

struct Counter {
    unsigned char unknown_00[0x30];
    int value;                             // +0x30

    __declspec(noinline) void Subtract(int amount);
};

#pragma code_seg(".text$01sub")
void Counter::Subtract(int amount) {
    value -= amount;
}
#pragma code_seg()
