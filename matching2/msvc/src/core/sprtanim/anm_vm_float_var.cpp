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

enum AnmFloatVarId {
    ANM_VAR_I0 = 0x2710,
    ANM_VAR_I1 = 0x2711,
    ANM_VAR_I2 = 0x2712,
    ANM_VAR_I3 = 0x2713,
    ANM_VAR_F0 = 0x2714,
    ANM_VAR_F1 = 0x2715,
    ANM_VAR_F2 = 0x2716,
    ANM_VAR_F3 = 0x2717,
    ANM_VAR_I4 = 0x2718,
    ANM_VAR_I5 = 0x2719,
    ANM_VAR_RAND_ANGLE = 0x271A,
    ANM_VAR_RAND_FLOAT = 0x271B,
    ANM_VAR_RAND_SIGNED = 0x271C,
    ANM_VAR_POS_X = 0x271D,
    ANM_VAR_POS_Y = 0x271E,
    ANM_VAR_POS_Z = 0x271F,
    ANM_VAR_CAMERA_X = 0x2720,
    ANM_VAR_CAMERA_Y = 0x2721,
    ANM_VAR_CAMERA_Z = 0x2722,
    ANM_VAR_TIME_A = 0x2723,
    ANM_VAR_TIME_B = 0x2724,
    ANM_VAR_TIME_C = 0x2725
};

enum AnmVmFlagMask {
    ANM_FLAG_USE_REPLAY_RNG = 0x40000000
};

struct EffectFieldStore {
    unsigned char pad_0000[0x30C];
    int int_var_0;      // +0x30C
    int int_var_1;      // +0x310
    int int_var_2;      // +0x314
    int int_var_3;      // +0x318
    float float_var_0;  // +0x31C
    float float_var_1;  // +0x320
    float float_var_2;  // +0x324
    float float_var_3;  // +0x328
    int int_var_4;      // +0x32C
    int int_var_5;      // +0x330
    float pos_x;        // +0x334
    float pos_y;        // +0x338
    float pos_z;        // +0x33C
    unsigned char pad_340[0x35C - 0x340];
    unsigned int flags; // +0x35C

    __declspec(noinline) float Get(float index);
};

#pragma code_seg(".text$01getfield")
float EffectFieldStore::Get(float index) {
    switch ((int)index) {
    case ANM_VAR_I0:
        return (float)int_var_0;
    case ANM_VAR_I1:
        return (float)int_var_1;
    case ANM_VAR_I2:
        return (float)int_var_2;
    case ANM_VAR_I3:
        return (float)int_var_3;
    case ANM_VAR_F0:
        return float_var_0;
    case ANM_VAR_F1:
        return float_var_1;
    case ANM_VAR_F2:
        return float_var_2;
    case ANM_VAR_F3:
        return float_var_3;
    case ANM_VAR_I4:
        return (float)int_var_4;
    case ANM_VAR_I5:
        return (float)int_var_5;
    case ANM_VAR_RAND_FLOAT:
        if (flags & ANM_FLAG_USE_REPLAY_RNG)
            return asm_Rng_NextFloat_0044bb20((const void*)0x004918A8);
        return asm_Rng_NextFloat_0044bb20((const void*)0x004918B0);
    case ANM_VAR_RAND_SIGNED:
        if (flags & ANM_FLAG_USE_REPLAY_RNG)
            return asm_Rng_NextFloatSigned_0044bb90((const void*)0x004918A8);
        return asm_Rng_NextFloatSigned_0044bb90((const void*)0x004918B0);
    case ANM_VAR_RAND_ANGLE:
        if (flags & ANM_FLAG_USE_REPLAY_RNG)
            return asm_Rng_NextFloatSigned_0044bb90((const void*)0x004918A8) * flt_pi;
        return asm_Rng_NextFloatSigned_0044bb90((const void*)0x004918B0) * flt_pi;
    case ANM_VAR_POS_X:
        return pos_x;
    case ANM_VAR_POS_Y:
        return pos_y;
    case ANM_VAR_POS_Z:
        return pos_z;
    case ANM_VAR_CAMERA_X:
        return g_back_camera;
    case ANM_VAR_CAMERA_Y:
        return g_back_camera_2;
    case ANM_VAR_CAMERA_Z:
        return g_back_camera_3;
    case ANM_VAR_TIME_A:
        return g_anm_vm_time_a;
    case ANM_VAR_TIME_B:
        return g_anm_vm_time_b;
    case ANM_VAR_TIME_C:
        return g_anm_vm_time_c;
    default:
        return index;
    }
}
#pragma code_seg()
