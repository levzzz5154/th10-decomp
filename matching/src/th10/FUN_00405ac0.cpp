// 00405AC0: FUN_00405ac0
// Original size: 160 bytes, actual code: 43 instructions
extern "C" void FUN_00408100(void);
extern "C" void FUN_0041c800(void);

extern "C" __declspec(naked) void FUN_00405ac0(void) {
    __asm {
        mov  eax,DWORD PTR [esi+0x28]
        test  eax,eax
        je loc_00405B39
        mov  ecx,DWORD PTR ds:0x4776f4
        mov  eax,DWORD PTR [ecx+0x378c]
        test  al,0x1
        push  ebx
        je loc_00405AE8
        mov  edx,DWORD PTR [ecx+0x3788]
        cmp  edx,0x5d
        jl loc_00405AE8
        cmp  edx,0x60
        jle loc_00405AF1
    loc_00405AE8:
        cmp  DWORD PTR [ecx+0x3788],0x6d
        jne loc_00405AFF
    loc_00405AF1:
        not  eax
        push  0x0
        and  eax,0x1
        push  eax
        mov  eax,DWORD PTR [esi+0x3c]
        push  eax
        jmp loc_00405B0B
    loc_00405AFF:
        mov  ecx,DWORD PTR [esi+0x3c]
        not  eax
        push  0x1
        and  eax,0x1
        push  eax
        push  ecx
    loc_00405B0B:
        mov  eax,ds:0x4776f0
        lea  ebx,[esi+0x30]
        call FUN_00408100
        mov  edx,DWORD PTR ds:0x4776f4
        mov  eax,DWORD PTR [edx+0x378c]
        mov  ecx,DWORD PTR [esi+0x3c]
        not  eax
        and  eax,0x1
        push  eax
        mov  eax,ds:0x47781c
        push  ecx
        call FUN_0041c800
        pop  ebx
    loc_00405B39:
        xor  eax,eax
        ret
    }
}
