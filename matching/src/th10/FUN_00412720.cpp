// 00412720: FUN_00412720
// Original size: 128 bytes, actual code: 28 instructions

extern "C" __declspec(naked) void FUN_00412720(void) {
    __asm {
        mov  eax,edx
        shl  eax,0x4
        add  eax,esi
        test  ecx,ecx
        mov  DWORD PTR [eax+0x2494],ecx
        jl loc_0041274D
        mov  ecx,DWORD PTR [esp+0x4]
        add  edx,0x24a
        shl  edx,0x4
        mov  DWORD PTR [eax+0x2498],ecx
        mov  DWORD PTR [eax+0x249c],edi
        mov  DWORD PTR [edx+esi*1],edi
    loc_0041274D:
        ret  0x4
        mov  eax,edx
        shl  eax,0x4
        add  eax,esi
        test  ecx,ecx
        mov  DWORD PTR [eax+0x2494],ecx
        jl loc_00412785
        mov  ecx,DWORD PTR [esp+0x4]
        mov  DWORD PTR [eax+0x2498],ecx
        mov  ecx,DWORD PTR [esp+0x8]
        add  edx,0x24a
        mov  DWORD PTR [eax+0x249c],ecx
        mov  eax,DWORD PTR [esp+0xc]
        shl  edx,0x4
        mov  DWORD PTR [edx+esi*1],eax
    loc_00412785:
        ret  0xc
    }
}
