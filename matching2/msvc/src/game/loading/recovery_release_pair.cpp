// 0x0041F930..0x0041F98A: release two slots of the animation manager's
// resource array, freeing each allocation and clearing the slot.
//
// Retail calls the release routine at 0x00447810 with the record in EDI - a
// native /LTCG register choice, not a declared convention - and frees through
// the CRT entry at 0x004524A1.  The region therefore joins the whole-program
// link that already carries the recovered release body,
// build_support/layout/ltcg/animation_manager_mark_resource_for_removal.json.
//
// The two slots are indices 6 and 7 of the 0x21-entry resource-slot array at
// +0x3AD06C that AnimationManager_ClearResourceSlot indexes.  Retail holds the
// addressed slot in ESI across each block's calls and re-loads the singleton
// between the two blocks; holding only the record would cost a third
// callee-saved register and re-read the global after every call.

struct AnimationResource6 {
    __declspec(noinline) void Release();
};

struct AnimationManager6 {
    unsigned char pad_000[0x3AD06C];
    AnimationResource6* slots_3ad06c[0x21];
};

extern "C" AnimationManager6* g_sprt_ctrl;
extern "C" void __cdecl crt_free_startup(void* memory);

#pragma code_seg(".text$03pair")
extern "C" __declspec(noinline) int __cdecl ReleasePair2() {
    AnimationResource6** slot = &g_sprt_ctrl->slots_3ad06c[6];
    if (*slot != 0) {
        (*slot)->Release();
        crt_free_startup(*slot);
        *slot = 0;
    }
    slot = &g_sprt_ctrl->slots_3ad06c[7];
    if (*slot != 0) {
        (*slot)->Release();
        crt_free_startup(*slot);
        *slot = 0;
    }
    return 0;
}
#pragma code_seg()
