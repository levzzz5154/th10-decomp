// 0x00421F80..0x00421F92 (19 bytes): complement of the ratio between the two
// doubles at +0x24 and +0x2C.
//
// Retail divides the first double by the second, scales it by the shared float
// at 0x00470B44 and subtracts the result from it (FSUBR), so the body reads
// `scale - (first / second) * scale`.  The record arrives in EAX.

extern "C" float flt_100;

#pragma pack(push, 4)
struct Ratio_00421f80 {
    unsigned char unknown_0000[0x24];
    double first;                          // +0x24
    double second;                         // +0x2C

    __declspec(noinline) float Remaining();
};
#pragma pack(pop)

#pragma code_seg(".text$01ratio")
float Ratio_00421f80::Remaining() {
    return flt_100 - (float)(first / second) * flt_100;
}
#pragma code_seg()
