// 00449AA0: FUN_00449aa0
// Original size: 64 bytes, actual code: 21 instructions

extern "C" __declspec(naked) void FUN_00449aa0(void) {
    __asm {
        mov  ecx,DWORD PTR [eax+0x4]
        xor  edx,edx
        mov  DWORD PTR [eax+0x8],edx
        mov  DWORD PTR [eax+0xc],edx
        mov  DWORD PTR [eax+0x10],edx
        mov  DWORD PTR [eax],edx
        and  ecx,0xfffffffe
        mov  DWORD PTR [eax+0x4],ecx
        lea  ecx,[eax+0x24]
        mov  DWORD PTR [eax+0x14],eax
        mov  DWORD PTR [eax+0x18],edx
        mov  DWORD PTR [eax+0x1c],edx
        and  DWORD PTR [ecx+0x4],0xfffffffe
        mov  DWORD PTR [ecx+0x8],edx
        mov  DWORD PTR [ecx+0xc],edx
        mov  DWORD PTR [ecx+0x10],edx
        mov  DWORD PTR [ecx],edx
        mov  DWORD PTR [ecx+0x14],ecx
        mov  DWORD PTR [ecx+0x18],edx
        mov  DWORD PTR [ecx+0x1c],edx
        ret
    }
}
