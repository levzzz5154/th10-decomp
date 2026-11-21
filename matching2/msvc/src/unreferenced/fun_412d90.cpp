// 0x00412D90: copy 2 dwords into destination offset +0x18.
struct CopyValue4 { unsigned int values[2]; };
struct CopyBlock5 {
    unsigned char pad[0x18];
    unsigned int values[2];
    __declspec(noinline) void Assign(const CopyValue4& other);
};
#pragma code_seg(".text$01copy00412d90")
void CopyBlock5::Assign(const CopyValue4& other) {
    values[0] = other.values[0];
    values[1] = other.values[1];
}
#pragma code_seg()
