// 0x004187A0: clear the shared state unless the object keeps it
// The leading parameter arrives in EAX, a convention only a native LTCG link
// chooses, so this region is compiled as a cluster.

struct GlobalState {
    unsigned char pad_04C[0x4C];
    int field_04C;
    int field_050;
    int field_054;
    int field_058;
};

struct ObjectAccessor_004187a0 {
    unsigned char pad_000[0x58];
    unsigned int flags;   // +0x58
};

extern "C" GlobalState* g_sprt_ctrl;

int __declspec(noinline) Reset_004187a0(ObjectAccessor_004187a0* object);
#pragma code_seg(".text$01accessor")
int Reset_004187a0(ObjectAccessor_004187a0* object) {
    if ((object->flags & 4u) == 0) {
        GlobalState* state = g_sprt_ctrl;
        state->field_050 = 0;
        state->field_054 = 0;
        state->field_04C = 0;
        state->field_058 = 0;
    }
    return 1;
}
#pragma code_seg()
