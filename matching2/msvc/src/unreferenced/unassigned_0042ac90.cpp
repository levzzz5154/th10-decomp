// 0x0042AC90: sum the bytes that follow an eight-byte header.

#pragma code_seg(".text$01accessor")
__declspec(noinline) int __stdcall SumPayload(const unsigned char* data, int size) {
    int sum = 0;
    const unsigned char* payload = data + 8;
    for (int i = 0; i < size - 8; ++i) sum += payload[i];
    return sum;
}
#pragma code_seg()
