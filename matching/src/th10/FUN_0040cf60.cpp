// 0040CF60: FUN_0040cf60
// Original size: 48 bytes, actual code: 8 instructions

extern "C" __declspec(naked) void FUN_0040cf60(void) {
    __asm {
        mov  edx,DWORD PTR [eax]
        add  ecx,0x430
        mov  DWORD PTR [ecx],edx
        mov  edx,DWORD PTR [eax+0x4]
        mov  DWORD PTR [ecx+0x4],edx
        mov  eax,DWORD PTR [eax+0x8]
        mov  DWORD PTR [ecx+0x8],eax
        ret
    }
}
