// 0x0042C800..0x0042C82C: release resource slot 1 of the animation manager,
// freeing its allocation and clearing the slot.  Compiled in the
// animation_manager_mark_resource_for_removal_004493e0 native-LTCG cluster,
// like 0x0041F930, so the call into 0x00447810 passes the record in EDI.

struct AnimationResource_00447810 {
    __declspec(noinline) void Release();
};

struct AnimationManager_0042c800 {
    unsigned char pad_000[0x3AD06C];
    AnimationResource_00447810* slots_3ad06c[0x21];
};

extern "C" AnimationManager_0042c800* data_00491c10;
extern "C" void __cdecl entry_free_004524a1(void* memory);

#pragma code_seg(".text$04layoutb")
extern "C" __declspec(noinline) void __cdecl ReleaseSlot1_0042c800() {
    AnimationResource_00447810** slot = &data_00491c10->slots_3ad06c[1];
    if (*slot != 0) {
        (*slot)->Release();
        entry_free_004524a1(*slot);
        *slot = 0;
    }
}
#pragma code_seg()
