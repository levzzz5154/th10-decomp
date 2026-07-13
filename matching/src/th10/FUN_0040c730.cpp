// 0040C730: FUN_0040c730
// Original size: 624 bytes, actual code: 17 instructions

extern "C" __declspec(naked) void FUN_0040c730(void) {
    __asm {
        push  esi
        mov  esi,DWORD PTR [eax+0x1028]
        xor  edx,edx
        lea  ecx,[eax+0x8]
        and  esi,0xfffffffe
        mov  DWORD PTR [eax+0x1028],esi
        mov  DWORD PTR [ecx],edx
        mov  DWORD PTR [eax+0xc],edx
        mov  DWORD PTR [eax+0x101c],eax
        mov  DWORD PTR [eax+0x1018],0xffffffff
        mov  DWORD PTR [eax+0x1020],edx
        mov  DWORD PTR [eax+0x4],ecx
        mov  DWORD PTR [eax+0x1030],ecx
        mov  DWORD PTR [eax+0x1034],edx
        mov  DWORD PTR [eax+0x1038],edx
        pop  esi
        ret
    }
}
