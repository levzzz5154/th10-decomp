// Record write runs whose receiver arrives in EAX: a mask clear across eight
// flag words (0x004020B0) and a vtable stamp with four cleared fields
// (0x0044C0E0).
struct WriteRunB_004020b0 {
    unsigned char pad_000[0x6C];
    unsigned int flags_06c;              // +0x06C
    unsigned char pad_070[0x40];
    unsigned int flags_0b0;              // +0x0B0
    unsigned char pad_0b4[0x48];
    unsigned int flags_0fc;              // +0x0FC
    unsigned char pad_100[0x28];
    unsigned int flags_128;              // +0x128
    unsigned char pad_12c[0x48];
    unsigned int flags_174;              // +0x174
    unsigned char pad_178[0x38];
    unsigned int flags_1b0;              // +0x1B0
    unsigned char pad_1b4[0x48];
    unsigned int flags_1fc;              // +0x1FC
    unsigned char pad_200[0x28];
    unsigned int flags_228;              // +0x228
    __declspec(noinline) void Clear();
};

struct WriteRunB_0044c0e0 {
    void* stamp_000;                     // +0x000
    int field_004;                       // +0x004
    int field_008;                       // +0x008
    int field_00c;                       // +0x00C
    int field_010;                       // +0x010
    __declspec(noinline) void Init();
};

#pragma code_seg(".text$01b")
void WriteRunB_004020b0::Clear() {
    unsigned int mask = ~1u;
    flags_06c &= mask;
    flags_0b0 &= mask;
    flags_0fc &= mask;
    flags_128 &= mask;
    flags_174 &= mask;
    flags_1b0 &= mask;
    flags_1fc &= mask;
    flags_228 &= mask;
}
#pragma code_seg()

#pragma code_seg(".text$03c")
void WriteRunB_0044c0e0::Init() {
    stamp_000 = (void*)0x004703E4;
    field_004 = 0;
    field_008 = 0;
    field_00c = 0;
    field_010 = 0;
}
#pragma code_seg()
