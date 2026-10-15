#pragma code_seg(".text$03resolveinteger")
extern "C" __declspec(noinline) int* __stdcall ResolveIntegerVariable(
        int* value, unsigned char* object, unsigned char selector, unsigned short mask) {
    if (((1u << selector) & mask) != 0) {
        switch (*value) {
        case 10000: return (int*)(object + 0x30c);
        case 10001: return (int*)(object + 0x310);
        case 10002: return (int*)(object + 0x314);
        case 10003: return (int*)(object + 0x318);
        case 10008: return (int*)(object + 0x32c);
        case 10009: return (int*)(object + 0x330);
        }
    }
    return value;
}
#pragma code_seg()
