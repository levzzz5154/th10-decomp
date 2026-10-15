// 0x0040C960: store two floats at +0x34/+0x38.
// The object arrives in EAX and both floats on the stack (RET 8); the body is
// compiled in the native-LTCG cluster build_support/layout/ltcg/setpair.json.
struct Pair_0040c960 {
    unsigned char reserved_000[0x34];
    float first;                   // +0x34
    float second;                  // +0x38
    __declspec(noinline) void SetPair(float first_value, float second_value);
};

#pragma code_seg(".text$01accessor")
void Pair_0040c960::SetPair(float first_value, float second_value) {
    first = first_value;
    second = second_value;
}
#pragma code_seg()
