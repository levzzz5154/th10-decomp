// 004366C0: FUN_004366c0
// Original size: 880 bytes, actual code: 74 instructions
extern "C" void _malloc(void);

extern "C" __declspec(naked) void FUN_004366c0(void) {
    __asm {
        push  ebx
        push  ebp
        push  esi
        mov  ebx,ecx
        mov  eax,DWORD PTR [ebx]
        push  edi
        call  DWORD PTR [eax+0x4]
        mov  ecx,DWORD PTR [esp+0x14]
        push  0xa
        push  ecx
        push  0x0
        call  DWORD PTR ds:0x4660e8
        mov  edi,eax
        test  edi,edi
        je loc_0043672F
        push  edi
        push  0x0
        call  DWORD PTR ds:0x4660ec
        mov  ebp,eax
        test  ebp,ebp
        je loc_0043672F
        push  ebp
        call  DWORD PTR ds:0x4661dc
        mov  esi,eax
        test  esi,esi
        jne loc_00436713
        push  eax
        call  DWORD PTR ds:0x4660f4
        mov  edx,DWORD PTR [ebx]
        mov  ecx,ebx
        call  DWORD PTR [edx+0x4]
        pop  edi
        pop  esi
        pop  ebp
        mov  al,0x1
        pop  ebx
        ret  0x8
    loc_00436713:
        push  edi
        push  0x0
        call  DWORD PTR ds:0x4660f8
        push  eax
        mov  DWORD PTR [ebx+0x4],eax
        call _malloc
        add  esp,0x4
        test  eax,eax
        mov  DWORD PTR [ebx+0xc],eax
        jne loc_0043673F
    loc_0043672F:
        mov  edx,DWORD PTR [ebx]
        mov  ecx,ebx
        call  DWORD PTR [edx+0x4]
        pop  edi
        pop  esi
        pop  ebp
        mov  al,0x1
        pop  ebx
        ret  0x8
    loc_0043673F:
        mov  ecx,DWORD PTR [ebx+0x4]
        mov  edi,eax
        mov  eax,ecx
        shr  ecx,0x2
        rep movsd
        mov  ecx,eax
        and  ecx,0x3
        rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
        mov  ecx,DWORD PTR [ebx+0xc]
        push  ebp
        mov  DWORD PTR [ebx+0x8],ecx
        call  DWORD PTR ds:0x4660f4
        pop  edi
        pop  esi
        pop  ebp
        mov  al,0x1
        pop  ebx
        ret  0x8
    }
}
