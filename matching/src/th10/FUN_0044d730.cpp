// 0044D730: FUN_0044d730
// Original size: 288 bytes, actual code: 31 instructions
extern "C" void FUN_0044d080(void);
extern "C" void FUN_0044d4e0(void);

extern "C" __declspec(naked) void FUN_0044d730(void) {
    __asm {
        mov  DWORD PTR [ecx],0x4705d4
        jmp FUN_0044d080
        int3
        int3
        int3
        int3
        int3
        cmp  DWORD PTR [ecx+0x1c],0x1
        jne loc_0044D780
        mov  eax,DWORD PTR [ecx+0x14]
        dec  eax
        test  eax,eax
        mov  DWORD PTR [ecx+0x14],eax
        jg loc_0044D769
        mov  eax,DWORD PTR [ecx+0x4]
        mov  DWORD PTR [ecx+0x1c],0x0
        mov  eax,DWORD PTR [eax]
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0x48]
        mov  eax,0x1
        ret
    loc_0044D769:
        imul  eax,eax,0x1388
        cdq
        idiv  DWORD PTR [ecx+0x18]
        sub  eax,0x1388
        push  eax
        mov  eax,ecx
        call FUN_0044d4e0
    loc_0044D780:
        xor  eax,eax
        ret
    }
}
