// 0x0044C0B0..0x0044C0D3: sum every fourth byte of a signed-length range. The 8-bit running sum is
// returned zero-extended in EAX; a trailing partial group is ignored.
#pragma code_seg(".text$01accessor")
extern "C" __declspec(noinline) unsigned int __fastcall
SumEveryFourthByte(const unsigned char* bytes, int count) {
    unsigned int sum = 0;
    count -= count & 3;
    for (int offset = 0; offset < count; offset += 4) {
        sum = static_cast<unsigned char>(sum + *bytes);
        bytes += 4;
    }
    return sum;
}
#pragma code_seg()
