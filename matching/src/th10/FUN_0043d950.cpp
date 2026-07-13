// 0043D950: FUN_0043d950
// Original size: 352 bytes, actual code: 93 instructions
extern "C" void FUN_0043d790(void);
extern "C" void FUN_0044cbf0(void);

extern "C" __declspec(naked) void FUN_0043d950(void) {
    __asm {
        push  ebx
        mov  ebx,eax
        mov  eax,DWORD PTR [esi+0x610]
        test  eax,eax
        push  ebp
        push  edi
        je loc_0043DA67
        mov  al,ds:0x491d63
        test  al,al
        jne loc_0043D975
        mov  eax,0xffffffff
        pop  edi
        pop  ebp
        pop  ebx
        ret
    loc_0043D975:
        cmp  DWORD PTR [esi],0x0
        je loc_0043DA67
        test  BYTE PTR ds:0x491d78,0x10
        jne loc_0043D99B
        shl  ebx,0x8
        lea  ecx,[ebx+esi*1+0x4108]
        mov  eax,esi
        pop  edi
        pop  ebp
        pop  ebx
        jmp FUN_0043d790
    loc_0043D99B:
        mov  eax,DWORD PTR [esi+ebx*4+0x1ec0]
        test  eax,eax
        je loc_0043DA67
        mov  eax,DWORD PTR [esi+ebx*4+0x1e80]
        movzx ebp,WORD PTR [eax+0x2c]
        mov  edi,DWORD PTR [eax+0x24]
        imul  edi,ebp
        push  0x0
        push  0x0
        push  0x0
        shl  edi,0x2
        push  0x0
        shr  edi,0x4
        call  DWORD PTR ds:0x466120
        mov  DWORD PTR [esi+0x520c],eax
        mov  ecx,DWORD PTR ds:0x491c70
        lea  eax,[esi+0x614]
        push  eax
        push  0x0
        push  ecx
        push  0x43e3a0
        push  0x0
        push  0x0
        call  DWORD PTR ds:0x466118
        mov  edx,DWORD PTR [esi+0x520c]
        push  edx
        mov  DWORD PTR [esi+0x618],eax
        xor  edx,edx
        mov  eax,edi
        div  ebp
        mov  ecx,DWORD PTR ds:0x46a67c
        sub  edi,edx
        mov  edx,DWORD PTR ds:0x46a680
        push  edi
        push  0x10
        sub  esp,0x10
        mov  eax,esp
        mov  DWORD PTR [eax],ecx
        mov  ecx,DWORD PTR ds:0x46a684
        mov  DWORD PTR [eax+0x4],edx
        mov  edx,DWORD PTR ds:0x46a688
        mov  DWORD PTR [eax+0x8],ecx
        mov  ecx,DWORD PTR [esi+ebx*4+0x1f40]
        mov  DWORD PTR [eax+0xc],edx
        mov  eax,DWORD PTR [esi+ebx*4+0x1e80]
        mov  edx,DWORD PTR [esi+ebx*4+0x1f00]
        push  eax
        mov  eax,DWORD PTR [esi+0x610]
        push  ecx
        push  edx
        lea  ecx,[esi+0x5208]
        push  eax
        mov  edx,0x10100
        call FUN_0044cbf0
        test  eax,eax
        jge loc_0043DA6E
    loc_0043DA67:
        or   eax,0xffffffff
        pop  edi
        pop  ebp
        pop  ebx
        ret
    loc_0043DA6E:
        pop  edi
        pop  ebp
        mov  DWORD PTR [esi+0x1f80],ebx
        xor  eax,eax
        pop  ebx
        ret
    }
}
