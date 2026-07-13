// 0044BE20: FUN_0044be20
// Original size: 80 bytes, actual code: 15 instructions

extern "C" __declspec(naked) void FUN_0044be20(void) {
    __asm {
        mov  ecx,DWORD PTR [eax+0x8c]
        mov  edx,DWORD PTR [eax]
        mov  DWORD PTR [eax+ecx*4+0xc],edx
        mov  ecx,DWORD PTR [eax+0x8c]
        mov  edx,DWORD PTR [eax+0x8]
        mov  DWORD PTR [eax+ecx*4+0x4c],edx
        mov  edx,DWORD PTR [eax+0x8c]
        inc  edx
        mov  ecx,edx
        cmp  ecx,0x10
        mov  DWORD PTR [eax+0x8c],edx
        mov  DWORD PTR [eax+0xd4],0x0
        jl loc_0044BE61
        mov  DWORD PTR [eax+0x8c],0xf
    loc_0044BE61:
        ret
    }
}
