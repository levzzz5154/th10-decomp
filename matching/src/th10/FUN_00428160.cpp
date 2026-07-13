// 00428160: FUN_00428160
// Original size: 112 bytes, actual code: 38 instructions
extern "C" void FUN_00427e90(void);

extern "C" __declspec(naked) void FUN_00428160(void) {
    __asm {
        movzx ecx,WORD PTR ds:0x474c48
        mov  eax,0x66666667
        imul  ecx
        sar  edx,0x3
        mov  eax,edx
        shr  eax,0x1f
        add  eax,edx
        cmp  eax,0x5
        jl loc_00428182
        mov  eax,0x4
    loc_00428182:
        mov  ecx,DWORD PTR [edi+0x4474]
        test  ecx,ecx
        je loc_0042818F
        add  eax,0x5
    loc_0042818F:
        mov  ecx,DWORD PTR [edi+0x45c]
        push  esi
        mov  esi,DWORD PTR [ecx+eax*8+0x110]
        mov  al,BYTE PTR [esi]
        test  al,al
        jl loc_004281C5
    loc_004281A3:
        movsx ecx,al
        mov  eax,ebx
        cdq
        idiv  ecx
        movsx eax,BYTE PTR [esi+0x1]
        cmp  edx,eax
        jne loc_004281BB
        push  ebx
        push  esi
        push  edi
        call FUN_00427e90
    loc_004281BB:
        mov  al,BYTE PTR [esi+0x34]
        add  esi,0x34
        test  al,al
        jge loc_004281A3
    loc_004281C5:
        xor  eax,eax
        pop  esi
        ret
    }
}
