// 0x00413220: copy 3 dwords into destination offset +0x0.
struct CopyValue_00413220 { unsigned int values[3]; };
struct CopyBlock_00413220 {
    unsigned int values[3];
    __declspec(noinline) void Assign(const CopyValue_00413220& other);
};
#pragma code_seg(".text$01copy00413220")
void CopyBlock_00413220::Assign(const CopyValue_00413220& other) {
    values[0] = other.values[0];
    values[1] = other.values[1];
    values[2] = other.values[2];
}
#pragma code_seg()
