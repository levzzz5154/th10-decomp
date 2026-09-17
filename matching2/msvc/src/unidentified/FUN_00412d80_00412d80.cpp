// 0x00412D80: copy 2 dwords into destination offset +0x10.
struct CopyValue_00412d80 { unsigned int values[2]; };
struct CopyBlock_00412d80 {
    unsigned char pad[0x10];
    unsigned int values[2];
    __declspec(noinline) void Assign(const CopyValue_00412d80& other);
};
#pragma code_seg(".text$01copy00412d80")
void CopyBlock_00412d80::Assign(const CopyValue_00412d80& other) {
    values[0] = other.values[0];
    values[1] = other.values[1];
}
#pragma code_seg()
