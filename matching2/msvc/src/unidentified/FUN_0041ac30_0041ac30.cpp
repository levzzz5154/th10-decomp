// 0x0041AC30: copy 2 dwords into destination offset +0x8.
struct CopyValue_0041ac30 { unsigned int values[2]; };
struct CopyBlock_0041ac30 {
    unsigned char pad[0x8];
    unsigned int values[2];
    __declspec(noinline) void Assign(const CopyValue_0041ac30& other);
};
#pragma code_seg(".text$01copy0041ac30")
void CopyBlock_0041ac30::Assign(const CopyValue_0041ac30& other) {
    values[0] = other.values[0];
    values[1] = other.values[1];
}
#pragma code_seg()
