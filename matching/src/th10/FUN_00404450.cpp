// 00404450: FUN_00404450
// Original size: 224 bytes, actual code: 73 instructions
extern "C" void FUN_00404f30(void);

extern "C" __declspec(naked) void FUN_00404450(void) {
    __asm {
        push  ecx
        push  ebx
        push  ebp
        mov  ebp,DWORD PTR [esp+0x10]
        mov  eax,DWORD PTR [ebp+0x8]
        mov  ebx,DWORD PTR [eax+0x4]
        mov  ecx,0x2
        or   ebx,ecx
        mov  DWORD PTR [eax+0x4],ebx
        mov  eax,DWORD PTR [ebp+0xc]
        push  esi
        push  edi
        or   DWORD PTR [eax+0x4],ecx
        mov  eax,DWORD PTR [ebp+0x2a40]
        or   DWORD PTR [eax+0x4],ecx
        mov  ecx,DWORD PTR [ebp+0x10]
        xor  eax,eax
        cmp  WORD PTR [ecx],ax
        mov  DWORD PTR [esp+0x18],eax
        mov  DWORD PTR [esp+0x10],eax
        jle loc_00404518
        mov  edi,edi
    loc_00404490:
        mov  edx,DWORD PTR [ebp+0x14]
        mov  ecx,DWORD PTR [edx+eax*4]
        mov  BYTE PTR [ecx+0x3],0x1
        mov  edx,DWORD PTR [ebp+0x14]
        mov  edi,DWORD PTR [edx+eax*4]
        add  edi,0x1c
        cmp  WORD PTR [edi],0x0
        jl loc_004044FB
        mov  ebx,DWORD PTR [esp+0x18]
        imul  ebx,ebx,0x3ac
        jmp loc_004044C0
        nop
        nop
    loc_004044C0:
        mov  esi,DWORD PTR [ebp+0x17c]
        mov  ecx,DWORD PTR [ebp+0x178]
        movsx eax,WORD PTR [edi+0x4]
        add  esi,ebx
        push  ecx
        call FUN_00404f30
        mov  eax,DWORD PTR [esp+0x18]
        movsx edx,WORD PTR [edi+0x2]
        mov  WORD PTR [edi+0x6],ax
        inc  eax
        add  edi,edx
        add  ebx,0x3ac
        cmp  WORD PTR [edi],0x0
        mov  DWORD PTR [esp+0x18],eax
        jge loc_004044C0
        mov  eax,DWORD PTR [esp+0x10]
    loc_004044FB:
        mov  ecx,DWORD PTR [ebp+0x10]
        movsx edx,WORD PTR [ecx]
        inc  eax
        cmp  eax,edx
        mov  DWORD PTR [esp+0x10],eax
        jl loc_00404490
        mov  eax,DWORD PTR [ebp+0x1c]
        pop  edi
        pop  esi
        mov  DWORD PTR [ebp+0x4c],eax
        pop  ebp
        pop  ebx
        pop  ecx
        ret  0x4
    loc_00404518:
        mov  ecx,DWORD PTR [ebp+0x1c]
        pop  edi
        pop  esi
        mov  DWORD PTR [ebp+0x4c],ecx
        pop  ebp
        pop  ebx
        pop  ecx
        ret  0x4
    }
}
