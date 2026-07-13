// 0041C510: FUN_0041c510
// Original size: 160 bytes, actual code: 44 instructions
extern "C" void FUN_0041c5b0(void);
extern "C" void FUN_0041c680(void);
extern "C" void operator_new(void);

extern "C" __declspec(naked) void FUN_0041c510(void) {
    __asm {
        cmp  DWORD PTR [esi+0x438],0x100
        jl loc_0041C521
        xor  eax,eax
        ret  0x4
    loc_0041C521:
        inc  DWORD PTR [esi+0x43c]
        jne loc_0041C533
        mov  DWORD PTR [esi+0x43c],0x1
    loc_0041C533:
        mov  eax,DWORD PTR [esp+0x4]
        sub  eax,0x0
        push  ebx
        je loc_0041C55A
        dec  eax
        jne loc_0041C59F
        push  0xd74
        call operator_new
        add  esp,0x4
        test  eax,eax
        je loc_0041C574
        mov  ebx,eax
        call FUN_0041c680
        jmp loc_0041C576
    loc_0041C55A:
        push  0xd58
        call operator_new
        add  esp,0x4
        test  eax,eax
        je loc_0041C574
        mov  ebx,eax
        call FUN_0041c5b0
        jmp loc_0041C576
    loc_0041C574:
        xor  eax,eax
    loc_0041C576:
        mov  ecx,DWORD PTR [esi+0x43c]
        mov  DWORD PTR [eax+0x54],ecx
        mov  ecx,DWORD PTR [esi+0x434]
        mov  DWORD PTR [eax+0x4],ecx
        mov  DWORD PTR [ecx+0x8],eax
        inc  DWORD PTR [esi+0x438]
        mov  DWORD PTR [esi+0x434],eax
        mov  edx,DWORD PTR [eax]
        mov  ecx,eax
        push  edi
        call  DWORD PTR [edx+0x4]
    loc_0041C59F:
        mov  eax,DWORD PTR [esi+0x43c]
        pop  ebx
        ret  0x4
    }
}
