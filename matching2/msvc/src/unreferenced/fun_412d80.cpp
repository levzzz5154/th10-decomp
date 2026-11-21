// 0x00412D80: copy 2 dwords into destination offset +0x10.
struct CopyValue3 { unsigned int values[2]; };
struct CopyBlock4 {
    unsigned char pad[0x10];
    unsigned int values[2];
    __declspec(noinline) void Assign(const CopyValue3& other);
};
#pragma code_seg(".text$01copy00412d80")
void CopyBlock4::Assign(const CopyValue3& other) {
    values[0] = other.values[0];
    values[1] = other.values[1];
}
#pragma code_seg()
