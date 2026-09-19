#pragma code_seg(".text$01resolvefloat")
extern "C" __declspec(noinline) float* __stdcall ResolveFloatVariable_0043ed00(
        unsigned char selector, float* value, unsigned char* object, unsigned short mask) {
    if (((1u << selector) & mask) != 0) {
        switch ((int)*value) {
        case 10004: return (float*)(object + 0x31c);
        case 10005: return (float*)(object + 0x320);
        case 10006: return (float*)(object + 0x324);
        case 10007: return (float*)(object + 0x328);
        case 10013: return (float*)(object + 0x334);
        case 10014: return (float*)(object + 0x338);
        case 10015: return (float*)(object + 0x33c);
        }
    }
    return value;
}
#pragma code_seg()
