// 0043AE20: FUN_0043ae20
// Original size: 144 bytes, actual code: 44 instructions
extern "C" void FUN_0043aeb0(void);

extern "C" __declspec(naked) void FUN_0043ae20(void) {
    __asm {
        mov  eax,DWORD PTR [edi+0x138]
        test  eax,eax
        jne loc_0043AE2E
        or   eax,0xffffffff
        ret
    loc_0043AE2E:
        push  ebx
        push  ebp
        push  esi
        lea  ebx,[edi+0x14]
        mov  ebp,0x20
        nop
    loc_0043AE40:
        mov  esi,DWORD PTR [ebx]
        test  esi,esi
        je loc_0043AE4D
        mov  edx,edi
        call FUN_0043aeb0
    loc_0043AE4D:
        add  ebx,0x4
        dec  ebp
        jne loc_0043AE40
        mov  eax,DWORD PTR [edi+0x4]
        test  eax,eax
        je loc_0043AE61
        push  eax
        call  DWORD PTR ds:0x466288
    loc_0043AE61:
        mov  eax,DWORD PTR [edi+0x8]
        push  eax
        call  DWORD PTR ds:0x466274
        xor  esi,esi
        mov  DWORD PTR [edi+0x4],esi
        mov  eax,DWORD PTR [edi+0x13c]
        cmp  eax,esi
        je loc_0043AE94
        push  eax
        call  DWORD PTR ds:0x4662a8
        mov  ecx,DWORD PTR [edi+0x13c]
        push  ecx
        call  DWORD PTR ds:0x4662a4
        mov  DWORD PTR [edi+0x13c],esi
    loc_0043AE94:
        pop  esi
        pop  ebp
        mov  DWORD PTR [edi+0x10],0xffffffff
        xor  eax,eax
        pop  ebx
        ret
    }
}
