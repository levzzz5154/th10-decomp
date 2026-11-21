// 0x0043ED00: ResolveFloatVariable
enum AnmFloatRefId {
    ANM_REF_F0 = 10004,
    ANM_REF_F1 = 10005,
    ANM_REF_F2 = 10006,
    ANM_REF_F3 = 10007,
    ANM_REF_POS_X = 10013,
    ANM_REF_POS_Y = 10014,
    ANM_REF_POS_Z = 10015
};

#pragma code_seg(".text$01resolvefloat")
extern "C" __declspec(noinline) float* __stdcall ResolveFloatVariable(
        unsigned char selector, float* value, unsigned char* object, unsigned short mask) {
    if (((1u << selector) & mask) != 0) {
        switch ((int)*value) {
        case ANM_REF_F0: return (float*)(object + 0x31c);
        case ANM_REF_F1: return (float*)(object + 0x320);
        case ANM_REF_F2: return (float*)(object + 0x324);
        case ANM_REF_F3: return (float*)(object + 0x328);
        case ANM_REF_POS_X: return (float*)(object + 0x334);
        case ANM_REF_POS_Y: return (float*)(object + 0x338);
        case ANM_REF_POS_Z: return (float*)(object + 0x33c);
        }
    }
    return value;
}
#pragma code_seg()
