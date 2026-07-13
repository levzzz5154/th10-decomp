// 004473C0: FUN_004473c0
// Original size: 176 bytes, actual code: 70 instructions
extern "C" void FUN_00447470(void);

extern "C" __declspec(naked) void FUN_004473c0(void) {
    __asm {
        push  ecx
        push  ebx
        push  ebp
        mov  ebp,DWORD PTR [esp+0x14]
        push  esi
        mov  esi,DWORD PTR [ebp+0x108]
        xor  edx,edx
        xor  ecx,ecx
        push  edi
        xor  ebx,ebx
        mov  DWORD PTR [esp+0x10],ecx
        xor  edi,edi
        mov  DWORD PTR [esp+0x1c],edx
        nop
    loc_004473E0:
        mov  eax,DWORD PTR [ebp+0x124]
        dec  eax
        cmp  ecx,eax
        jne loc_0044740A
        mov  ecx,DWORD PTR [esp+0x18]
        mov  eax,DWORD PTR [esp+0x1c]
        push  esi
        push  ebx
        push  edi
        push  ebp
        push  ecx
        call FUN_00447470
        test  eax,eax
        jl loc_00447446
        mov  ecx,DWORD PTR [esp+0x10]
        mov  edx,0x1
    loc_0044740A:
        add  edi,DWORD PTR [esi]
        add  ebx,DWORD PTR [esi+0x4]
        inc  DWORD PTR [esp+0x1c]
        mov  eax,DWORD PTR [esi+0x38]
        test  eax,eax
        je loc_0044745A
        add  esi,eax
        mov  eax,DWORD PTR [ebp+0x124]
        inc  ecx
        cmp  ecx,eax
        mov  DWORD PTR [esp+0x10],ecx
        je loc_0044742F
        test  edx,edx
        je loc_004473E0
    loc_0044742F:
        mov  eax,DWORD PTR [ebp+0x124]
        pop  edi
        inc  eax
        mov  DWORD PTR [ebp+0x124],eax
        pop  esi
        mov  eax,ebp
        pop  ebp
        pop  ebx
        pop  ecx
        ret  0x8
    loc_00447446:
        pop  edi
        pop  esi
        mov  DWORD PTR [ebp+0x124],0x0
        pop  ebp
        xor  eax,eax
        pop  ebx
        pop  ecx
        ret  0x8
    loc_0044745A:
        pop  edi
        pop  esi
        mov  DWORD PTR [ebp+0x124],0x0
        mov  eax,ebp
        pop  ebp
        pop  ebx
        pop  ecx
        ret  0x8
    }
}
