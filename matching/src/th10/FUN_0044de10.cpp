// 0044DE10: FUN_0044de10
// Original size: 352 bytes, actual code: 81 instructions

extern "C" __declspec(naked) void FUN_0044de10(void) {
    __asm {
        mov  ecx,DWORD PTR [eax+0x7c]
        test  ecx,ecx
        push  ebx
        mov  ebx,DWORD PTR [esp+0x8]
        push  esi
        push  edi
        mov  edi,DWORD PTR [esp+0x14]
        je loc_0044DE91
        mov  ecx,DWORD PTR [eax+0x84]
        test  ecx,ecx
        jne loc_0044DE37
    loc_0044DE2C:
        pop  edi
        pop  esi
        mov  eax,0x800401f0
        pop  ebx
        ret  0x8
    loc_0044DE37:
        test  edi,edi
        je loc_0044DE41
        mov  DWORD PTR [edi],0x0
    loc_0044DE41:
        mov  ebx,DWORD PTR [eax+0x88]
        mov  ecx,DWORD PTR [eax+0x80]
        mov  esi,DWORD PTR [eax+0x84]
        push  ebp
        lea  ebp,[esi+edx*1]
        lea  edi,[ecx+ebx*1]
        cmp  ebp,edi
        pop  ebp
        jbe loc_0044DE65
        sub  ecx,esi
        add  ecx,ebx
        mov  edx,ecx
    loc_0044DE65:
        mov  edi,DWORD PTR [esp+0x10]
        mov  ecx,edx
        mov  ebx,ecx
        shr  ecx,0x2
        rep movsd
        mov  ecx,ebx
        and  ecx,0x3
        rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
        add  DWORD PTR [eax+0x84],edx
        mov  eax,DWORD PTR [esp+0x14]
        test  eax,eax
        je loc_0044DE89
        mov  DWORD PTR [eax],edx
    loc_0044DE89:
        pop  edi
        pop  esi
        xor  eax,eax
        pop  ebx
        ret  0x8
    loc_0044DE91:
        mov  esi,DWORD PTR [eax+0x8c]
        test  esi,esi
        je loc_0044DE2C
        test  ebx,ebx
        je loc_0044DECF
        test  edi,edi
        je loc_0044DECF
        mov  ecx,DWORD PTR [eax+0x8]
        cmp  edx,ecx
        jbe loc_0044DEAC
        mov  edx,ecx
    loc_0044DEAC:
        sub  ecx,edx
        push  0x0
        mov  DWORD PTR [eax+0x8],ecx
        lea  eax,[esp+0x14]
        push  eax
        push  edx
        push  ebx
        push  esi
        call  DWORD PTR ds:0x4660d0
        mov  ecx,DWORD PTR [esp+0x10]
        mov  DWORD PTR [edi],ecx
        pop  edi
        pop  esi
        xor  eax,eax
        pop  ebx
        ret  0x8
    loc_0044DECF:
        pop  edi
        pop  esi
        mov  eax,0x80070057
        pop  ebx
        ret  0x8
    }
}
