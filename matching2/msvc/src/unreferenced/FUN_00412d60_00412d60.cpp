// 0x00412D60: copy 2 dwords into destination offset +0x0.
struct CopyValue_00412d60 { unsigned int values[2]; };
struct CopyBlock_00412d60 {
    unsigned int values[2];
    __declspec(noinline) void Assign(const CopyValue_00412d60& other);
};
#pragma code_seg(".text$01copy00412d60")
void CopyBlock_00412d60::Assign(const CopyValue_00412d60& other) {
    values[0] = other.values[0];
    values[1] = other.values[1];
}
#pragma code_seg()
