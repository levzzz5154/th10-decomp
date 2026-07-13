// 00409D90: FUN_00409d90
// Original size: 144 bytes, actual code: 18 instructions

extern "C" __declspec(naked) void FUN_00409d90(void) {
    __asm {
        mov  eax,0x66666667
        imul  DWORD PTR [esp+0x4]
        sar  edx,0x2
        mov  eax,edx
        shr  eax,0x1f
        add  eax,edx
        mov  edx,DWORD PTR [ecx+0x4]
        add  edx,eax
        mov  eax,edx
        cmp  eax,0x3b9aca00
        mov  DWORD PTR [ecx+0x4],edx
        jl loc_00409DBB
        mov  DWORD PTR [ecx+0x4],0x3b9ac9ff
    loc_00409DBB:
        ret  0x4
    }
}
