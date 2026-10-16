// 0x00413220: copy 3 dwords into destination offset +0x0.
struct CopyValue5 { unsigned int values[3]; };
struct CopyBlock6 {
    unsigned int values[3];
    __declspec(noinline) void Assign(const CopyValue5& other);
};
#pragma code_seg(".text$01copy00413220")
void CopyBlock6::Assign(const CopyValue5& other) {
    values[0] = other.values[0];
    values[1] = other.values[1];
    values[2] = other.values[2];
}
#pragma code_seg()
