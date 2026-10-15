// 0x00412D90: copy 2 dwords into destination offset +0x18.
struct CopyValue_00412d90 { unsigned int values[2]; };
struct CopyBlock_00412d90 {
    unsigned char pad[0x18];
    unsigned int values[2];
    __declspec(noinline) void Assign(const CopyValue_00412d90& other);
};
#pragma code_seg(".text$01copy00412d90")
void CopyBlock_00412d90::Assign(const CopyValue_00412d90& other) {
    values[0] = other.values[0];
    values[1] = other.values[1];
}
#pragma code_seg()
