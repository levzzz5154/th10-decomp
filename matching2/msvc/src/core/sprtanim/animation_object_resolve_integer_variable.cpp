// 0x0043EDA0: ResolveIntegerVariable
enum AnmIntRefId {
    ANM_REF_I0 = 10000,
    ANM_REF_I1 = 10001,
    ANM_REF_I2 = 10002,
    ANM_REF_I3 = 10003,
    ANM_REF_I4 = 10008,
    ANM_REF_I5 = 10009
};

#pragma code_seg(".text$03resolveinteger")
extern "C" __declspec(noinline) int* __stdcall ResolveIntegerVariable(
        int* value, unsigned char* object, unsigned char selector, unsigned short mask) {
    if (((1u << selector) & mask) != 0) {
        switch (*value) {
        case ANM_REF_I0: return (int*)(object + 0x30c);
        case ANM_REF_I1: return (int*)(object + 0x310);
        case ANM_REF_I2: return (int*)(object + 0x314);
        case ANM_REF_I3: return (int*)(object + 0x318);
        case ANM_REF_I4: return (int*)(object + 0x32c);
        case ANM_REF_I5: return (int*)(object + 0x330);
        }
    }
    return value;
}
#pragma code_seg()
