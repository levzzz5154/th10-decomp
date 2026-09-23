// 0x0044C080..0x0044C0A3: sum every other byte from a signed-length range.
// The result is the 8-bit running sum, zero-extended in AX. The retail loop
// ignores a final unpaired byte and does no reads for a nonpositive count.
#pragma code_seg(".text$01bytesum")
extern "C" __declspec(noinline) unsigned short __fastcall
SumAlternateBytes_0044c080(const unsigned char* bytes, int count) {
    unsigned char sum = 0;
    const int pair_count = count / 2;

    for (int pair = 0; pair < pair_count; ++pair) {
        sum = static_cast<unsigned char>(sum + bytes[pair * 2]);
    }

    return sum;
}
#pragma code_seg()
