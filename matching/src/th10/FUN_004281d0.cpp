// 004281D0: FUN_004281d0
// Original size: 176 bytes, actual code: 55 instructions
extern "C" void FUN_00404ed0(void);
extern "C" void FUN_00405410(void);
extern "C" void FUN_00428160(void);
extern "C" void FUN_0044bf40(void);

extern "C" __declspec(naked) void FUN_004281d0(void) {
    __asm {
        push  ebx
        push  edi
        mov  edi,eax
        mov  eax,DWORD PTR [edi+0x458]
        mov  ebx,0x1
        cmp  eax,ebx
        jne loc_00428268
        mov  eax,DWORD PTR [edi+0x464]
        test  eax,eax
        jge loc_00428206
        test  BYTE PTR ds:0x474e5c,bl
        je loc_00428249
        push  0x0
        lea  eax,[edi+0x460]
        call FUN_00405410
    loc_00428206:
        mov  eax,DWORD PTR [edi+0x464]
        mov  ecx,DWORD PTR [edi+0x460]
        cmp  eax,ecx
        push  esi
        lea  esi,[edi+0x460]
        je loc_0042822D
        mov  ebx,DWORD PTR [edi+0x464]
        call FUN_00428160
        mov  ebx,0x1
    loc_0042822D:
        cmp  DWORD PTR [edi+0x464],0xf
        jl loc_0042825D
        test  BYTE PTR ds:0x474e5c,bl
        je loc_0042824E
        push  0xc1700000
        call FUN_0044bf40
        pop  esi
    loc_00428249:
        pop  edi
        xor  eax,eax
        pop  ebx
        ret
    loc_0042824E:
        push  0xffffffff
        mov  eax,esi
        call FUN_00405410
        pop  esi
        pop  edi
        xor  eax,eax
        pop  ebx
        ret
    loc_0042825D:
        call FUN_00404ed0
        pop  esi
        pop  edi
        xor  eax,eax
        pop  ebx
        ret
    loc_00428268:
        mov  DWORD PTR [edi+0x3504],0x0
        mov  BYTE PTR [edi+0x3508],0x0
        pop  edi
        xor  eax,eax
        pop  ebx
        ret
    }
}
