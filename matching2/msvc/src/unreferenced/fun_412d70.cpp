// 0x00412D70: copy 2 dwords into destination offset +0x8.
struct CopyValue2 { unsigned int values[2]; };
struct CopyBlock3 {
    unsigned char pad[0x8];
    unsigned int values[2];
    __declspec(noinline) void Assign(const CopyValue2& other);
};
#pragma code_seg(".text$01copy00412d70")
void CopyBlock3::Assign(const CopyValue2& other) {
    values[0] = other.values[0];
    values[1] = other.values[1];
}
#pragma code_seg()
