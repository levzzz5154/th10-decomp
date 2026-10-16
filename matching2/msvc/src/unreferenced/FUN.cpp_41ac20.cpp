// 0x0041AC20: copy 2 dwords into destination offset +0x0.
struct CopyValue6 { unsigned int values[2]; };
struct CopyBlock7 {
    unsigned int values[2];
    __declspec(noinline) void Assign(const CopyValue6& other);
};
#pragma code_seg(".text$01copy0041ac20")
void CopyBlock7::Assign(const CopyValue6& other) {
    values[0] = other.values[0];
    values[1] = other.values[1];
}
#pragma code_seg()
