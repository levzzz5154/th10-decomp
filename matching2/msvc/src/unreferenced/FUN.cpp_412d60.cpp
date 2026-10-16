// 0x00412D60: copy 2 dwords into destination offset +0x0.
struct CopyValue { unsigned int values[2]; };
struct CopyBlock2 {
    unsigned int values[2];
    __declspec(noinline) void Assign(const CopyValue& other);
};
#pragma code_seg(".text$01copy00412d60")
void CopyBlock2::Assign(const CopyValue& other) {
    values[0] = other.values[0];
    values[1] = other.values[1];
}
#pragma code_seg()
