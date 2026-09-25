// 0x0044C0B0..0x0044C0D3: add every fourth byte in a signed-length range.
// The byte accumulator wraps modulo 256; EAX returns that sum zero-extended.
#pragma code_seg(".text$01bytesum")
extern "C" __declspec(noinline) unsigned int __fastcall
SumEveryFourthByte_0044c0b0(const unsigned char* bytes, int count) {
    unsigned char sum = 0;
    const int sample_count = count / 4;

    for (int sample = 0; sample < sample_count; ++sample) {
        sum = static_cast<unsigned char>(sum + bytes[sample * 4]);
    }

    return static_cast<unsigned int>(sum);
}
#pragma code_seg()
