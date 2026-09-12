// 0x00442F50 - Native-LTCG recovery of the internal ESI receiver convention.
struct AnimationManager_00442F50 {
    unsigned char unknown_00000000[0x58];
    int draw_calls;
    unsigned char unknown_0000005C[0x3ADAC8 - 0x5C];
    int quad_count;
    unsigned char unknown_003ADACC[0x72DACC - 0x3ADACC];
    void* cursor;
    void* batch_start;

    __declspec(noinline) int Flush();
};

typedef long (__stdcall *SetTextureStageState_00442F50)(
    void*, unsigned int, unsigned int, unsigned int);
typedef long (__stdcall *SetFVF_00442F50)(void*, unsigned int);
typedef long (__stdcall *DrawPrimitiveUP_00442F50)(
    void*, unsigned int, unsigned int, const void*, unsigned int);

#pragma code_seg(".text$01flush")
__declspec(noinline) int AnimationManager_00442F50::Flush() {
    int result = quad_count;
    if (result != 0) {
        void* device = *reinterpret_cast<void**>(0x00491C30);
        void** vtable = *reinterpret_cast<void***>(device);
        reinterpret_cast<SetTextureStageState_00442F50>(vtable[0x10C / 4])(
            device, 0, 6, 0);
        device = *reinterpret_cast<void**>(0x00491C30);
        vtable = *reinterpret_cast<void***>(device);
        reinterpret_cast<SetTextureStageState_00442F50>(vtable[0x10C / 4])(
            device, 0, 3, 0);
        device = *reinterpret_cast<void**>(0x00491C30);
        vtable = *reinterpret_cast<void***>(device);
        reinterpret_cast<SetFVF_00442F50>(vtable[0x164 / 4])(device, 0x144);
        const void* start = batch_start;
        device = *reinterpret_cast<void**>(0x00491C30);
        vtable = *reinterpret_cast<void***>(device);
        reinterpret_cast<DrawPrimitiveUP_00442F50>(vtable[0x14C / 4])(
            device, 4, static_cast<unsigned int>(quad_count << 1), start, 0x1C);
        batch_start = cursor;
        quad_count = 0;
        result = ++draw_calls;
    }
    return result;
}
#pragma code_seg()
