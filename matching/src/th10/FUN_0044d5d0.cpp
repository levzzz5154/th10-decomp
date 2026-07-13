// 0044D5D0: FUN_0044d5d0
// Original size: 48 bytes, actual code: 18 instructions

extern "C" __declspec(naked) void FUN_0044d5d0(void) {
    __asm {
        mov  ecx,DWORD PTR [eax+0x4]
        test  ecx,ecx
        jne loc_0044D5DD
        mov  eax,0x800401f0
        ret
    loc_0044D5DD:
        mov  ecx,DWORD PTR [ecx]
        push  esi
        mov  esi,DWORD PTR [eax+0x24]
        mov  DWORD PTR [eax+0x30],0x1
        mov  eax,DWORD PTR [eax+0x20]
        mov  edx,DWORD PTR [ecx]
        push  esi
        push  eax
        push  0x0
        push  ecx
        call  DWORD PTR [edx+0x30]
        pop  esi
        ret
    }
}
