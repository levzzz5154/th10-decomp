// 0x00405730: release a raw pair, then free the block itself.
//
// Retail: 85 F6           test esi,esi
//         74 0D           je   done
//         56              push esi
//         E8 E6 FE FF FF  call 0x00405620   ; release the pair contents
//         56              push esi
//         E8 61 CD 04 00  call 0x004524A1   ; free the block
//         59              pop  ecx
//         C3              ret
// The pair pointer arrives in ESI, so the release helper is compiled as a
// native LTCG cluster (see layout/ltcg/fun_00405730.json).

extern "C" void __stdcall asm_Recovery_ReleaseRawPairAndReset_00405620(void* pair);
extern "C" void __cdecl entry_free_004524a1(void* block);

static __forceinline void PlayerRuntime_ReleaseAndFree(void* runtime) {
    if (runtime) {
        asm_Recovery_ReleaseRawPairAndReset_00405620(runtime);
        entry_free_004524a1(runtime);
    }
}

#pragma code_seg(".text$01release")
__declspec(noinline) void FUN_00405730_ReleasePair(void* pair) {
    PlayerRuntime_ReleaseAndFree(pair);
}
#pragma code_seg()
