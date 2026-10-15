// 0x0043EAC0: named float parameter lookup for one effect object.
//
// The object arrives in ESI and the selector in a single stack slot with callee
// cleanup, so this is a native-LTCG cluster: only the internal convention of the
// /GL link keeps `this` in a callee-saved register. The switch's jump table is
// inside the region extent and MSVC emits it from the normal `switch` source.

extern "C" float __fastcall asm_Rng_NextFloat_0044bb20(const void* self);       // 0x0044BB20
extern "C" float __fastcall asm_Rng_NextFloatSigned_0044bb90(const void* self); // 0x0044BB90
extern "C" float flt_pi;   // 3.1415927f
extern "C" float g_back_camera;
extern "C" float g_back_camera_2;
extern "C" float g_back_camera_3;
extern "C" float g_anm_vm_time_a;
extern "C" float g_anm_vm_time_b;
extern "C" float g_anm_vm_time_c;

struct EffectFieldStore_0043eac0 {
    unsigned char pad_0000[0x30C];
    int int_30c;    // +0x30C
    int int_310;    // +0x310
    int int_314;    // +0x314
    int int_318;    // +0x318
    float float_31c;  // +0x31C
    float float_320;  // +0x320
    float float_324;  // +0x324
    float float_328;  // +0x328
    int int_32c;    // +0x32C
    int int_330;    // +0x330
    float float_334;  // +0x334
    float float_338;  // +0x338
    float float_33c;  // +0x33C
    unsigned char pad_340[0x35C - 0x340];
    unsigned int flags;  // +0x35C

    __declspec(noinline) float Get(float index);
};

#pragma code_seg(".text$01getfield")
float EffectFieldStore_0043eac0::Get(float index) {
    switch ((int)index) {
    case 0x2710:
        return (float)int_30c;
    case 0x2711:
        return (float)int_310;
    case 0x2712:
        return (float)int_314;
    case 0x2713:
        return (float)int_318;
    case 0x2714:
        return float_31c;
    case 0x2715:
        return float_320;
    case 0x2716:
        return float_324;
    case 0x2717:
        return float_328;
    case 0x2718:
        return (float)int_32c;
    case 0x2719:
        return (float)int_330;
    case 0x271B:
        if (flags & 0x40000000)
            return asm_Rng_NextFloat_0044bb20((const void*)0x004918A8);
        return asm_Rng_NextFloat_0044bb20((const void*)0x004918B0);
    case 0x271C:
        if (flags & 0x40000000)
            return asm_Rng_NextFloatSigned_0044bb90((const void*)0x004918A8);
        return asm_Rng_NextFloatSigned_0044bb90((const void*)0x004918B0);
    case 0x271A:
        if (flags & 0x40000000)
            return asm_Rng_NextFloatSigned_0044bb90((const void*)0x004918A8) * flt_pi;
        return asm_Rng_NextFloatSigned_0044bb90((const void*)0x004918B0) * flt_pi;
    case 0x271D:
        return float_334;
    case 0x271E:
        return float_338;
    case 0x271F:
        return float_33c;
    case 0x2720:
        return g_back_camera;
    case 0x2721:
        return g_back_camera_2;
    case 0x2722:
        return g_back_camera_3;
    case 0x2723:
        return g_anm_vm_time_a;
    case 0x2724:
        return g_anm_vm_time_b;
    case 0x2725:
        return g_anm_vm_time_c;
    default:
        return index;
    }
}
#pragma code_seg()
