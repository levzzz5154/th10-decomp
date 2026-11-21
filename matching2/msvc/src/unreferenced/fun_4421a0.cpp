// 0x004421A0: copy 3 dwords into destination offset +0x0.
struct CopyValue8 { unsigned int values[3]; };
struct CopyBlock9 {
    unsigned int values[3];
    __declspec(noinline) void Assign(const CopyValue8& other);
};
#pragma code_seg(".text$01copy004421a0")
void CopyBlock9::Assign(const CopyValue8& other) {
    values[0] = other.values[0];
    values[1] = other.values[1];
    values[2] = other.values[2];
}
#pragma code_seg()
