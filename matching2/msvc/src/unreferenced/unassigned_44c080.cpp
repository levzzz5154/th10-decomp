// 0x0044C080..0x0044C0A3: sum every other byte of a signed-length range. The 8-bit running sum is
// returned zero-extended in AX; a final unpaired byte is ignored.
#pragma code_seg(".text$01accessor")
extern "C" __declspec(noinline) unsigned short __fastcall
SumAlternateBytes(const unsigned char* bytes, int count) {
    unsigned short sum = 0;
    count -= count & 1;
    for (int offset = 0; offset < count; offset += 2) {
        sum = static_cast<unsigned char>(sum + *bytes);
        bytes += 2;
    }
    return sum;
}
#pragma code_seg()
