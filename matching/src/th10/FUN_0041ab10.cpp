// 0041AB10: FUN_0041ab10
// Original size: 96 bytes, actual code: 20 instructions

extern "C" __declspec(naked) void FUN_0041ab10(void) {
    __asm {
        lea  ecx,[eax+0x4]
        push  esi
        cmp  DWORD PTR [ecx],0x0
        je loc_0041AB2C
        nop
    loc_0041AB20:
        mov  eax,DWORD PTR [ecx]
        mov  esi,DWORD PTR [eax+0x4]
        test  esi,esi
        lea  ecx,[eax+0x4]
        jne loc_0041AB20
    loc_0041AB2C:
        mov  ecx,DWORD PTR [eax+0x4]
        test  ecx,ecx
        pop  esi
        je loc_0041AB3D
        mov  DWORD PTR [edx+0x4],ecx
        mov  ecx,DWORD PTR [eax+0x4]
        mov  DWORD PTR [ecx+0x8],edx
    loc_0041AB3D:
        mov  DWORD PTR [eax+0x4],edx
        mov  DWORD PTR [edx+0x8],eax
        ret
    }
}
