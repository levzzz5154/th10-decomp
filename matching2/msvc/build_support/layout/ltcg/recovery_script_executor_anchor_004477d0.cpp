// 0x004477D0..0x00447806: release and null one animation-manager resource slot.
//
// Retail enters with the manager singleton in EBX and the slot index in ESI,
// and hands the slot's record to the release routine at 0x00447810 in EDI:
// conventions only a native /LTCG link of this source chooses.  They come from
// this region's place in build_support/layout/ltcg/animation_manager_mark_resource_for_removal_004493e0.json,
// whose synthetic caller keeps the manager and the index in those registers and
// whose co-compiled release body is the real recovered 0x00447810 model.
//
// The two range tests stay separate because retail has both (jl and jae); a
// merged (unsigned)index >= 0x21u produces a single jae.
struct AnimationResource_00447810 {
    __declspec(noinline) void Release();
};

extern "C" void __cdecl crt_free_startup(void* memory);

struct AnimationManager_004477d0 {
    unsigned char pad_000[0x3AD06C];
    AnimationResource_00447810* slots_3ad06c[0x21];   // +0x3AD06C

    __declspec(noinline) void ClearResourceSlot(int index);
};

#pragma code_seg(".text$004477d0_fn")
void AnimationManager_004477d0::ClearResourceSlot(int index) {
    if (index < 0)
        return;
    if ((unsigned)index >= 0x21u)
        return;
    if (slots_3ad06c[index] == 0)
        return;
    slots_3ad06c[index]->Release();
    crt_free_startup(slots_3ad06c[index]);
    slots_3ad06c[index] = 0;
}
#pragma code_seg()
