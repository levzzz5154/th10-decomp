// 0x004053B0: store a three-dword record into the record whose address arrives
// in EAX.
//
// Retail: 8B 4C 24 04        mov ecx,[esp+4]     ; value[0]
//         8B 54 24 08        mov edx,[esp+8]     ; value[1]
//         89 08              mov [eax],ecx
//         8B 4C 24 0C        mov ecx,[esp+0xC]   ; value[2]
//         89 50 04           mov [eax+4],edx
//         89 48 08           mov [eax+8],ecx
//         C2 0C 00           ret 0xC
// The interleaved dword-pair copy and the 12 bytes of callee-popped stack show
// a by-value three-dword record argument, while the destination arrives in EAX,
// so the store is compiled as a native LTCG cluster
// (see build_support/layout/ltcg/fun_4053b0.json).

struct FUN_004053b0_Triple {
    int values[3];
};

#pragma code_seg(".text$01storetriple")
__declspec(noinline) void __stdcall FUN_004053b0_StoreTriple(FUN_004053b0_Triple* out, FUN_004053b0_Triple value) {
    *out = value;
}
#pragma code_seg()
