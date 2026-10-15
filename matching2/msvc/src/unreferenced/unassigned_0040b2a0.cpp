// 0x0040B2A0: advance the worker's embedded polar record, then publish the
// resulting vector into the worker's own +0x340 triple. The worker arrives in
// EAX, which only the native LTCG link chooses, so this is a cluster.
extern "C" void __fastcall asm_Recovery_PolarToVectorRetail_0044c5d0(void* target, float value, float other);
extern "C" void __cdecl asm_Recovery_AdvancePolarMotion_0044c2a0();
extern "C" float __stdcall Angle_Normalize_0044bc70(float value);
struct Vec3_0040b2a0 {
    float x; float y; float z;
};
struct PolarState {
    Vec3_0040b2a0 vector_000;
    float field_00c;
    float field_010;
    float field_014;
    float field_018;
    float field_01c;
    float field_020;
    float field_024;
    unsigned int flags_028;
};
struct Worker {
    unsigned char pad_000[0x340];
    Vec3_0040b2a0 output_340;
    unsigned char pad_34c[0x0C];
    PolarState* state_358;
    __declspec(noinline) int Update();
};
#pragma code_seg(".text$01accessor")
int Worker::Update() {
    PolarState* state = state_358;
    if ((state->flags_028 & 1) == 0) {
        asm_Recovery_PolarToVectorRetail_0044c5d0(&state->field_00c, state->field_01c, state->field_018);
        state->field_014 = 0.0f;
    } else {
        state->field_020 += state->field_024;
        state->field_01c = Angle_Normalize_0044bc70(state->field_01c + state->field_018);
    }
    asm_Recovery_AdvancePolarMotion_0044c2a0();
    *(Vec3_0040b2a0*)((unsigned char*)this + 0x340) = state->vector_000;
    return 0;
}
#pragma code_seg()
