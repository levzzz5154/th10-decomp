// 0043D690: FUN_0043d690
// Original size: 256 bytes, actual code: 83 instructions
extern "C" void FUN_0043dab0(void);
extern "C" void FUN_0044c8f0(void);

extern "C" __declspec(naked) void FUN_0043d690(void) {
    __asm {
        push  ebx
        push  ebp
        push  esi
        mov  esi,eax
        mov  eax,DWORD PTR [esp+0x10]
        lea  edx,[esi+0x5108]
        push  edi
        sub  edx,eax
    loc_0043D6A2:
        mov  cl,BYTE PTR [eax]
        mov  BYTE PTR [edx+eax*1],cl
        inc  eax
        test  cl,cl
        jne loc_0043D6A2
        mov  eax,DWORD PTR [esi+0x610]
        test  eax,eax
        jne loc_0043D6C0
    loc_0043D6B6:
        or   eax,0xffffffff
        pop  edi
        pop  esi
        pop  ebp
        pop  ebx
        ret  0x4
    loc_0043D6C0:
        cmp  DWORD PTR [esi],0x0
        je loc_0043D6B6
        call FUN_0043dab0
        mov  ebx,DWORD PTR [esi+0x1f84]
        movzx ebp,WORD PTR [ebx+0x2c]
        mov  edi,DWORD PTR [ebx+0x24]
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
        push  ebx
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
        mov  DWORD PTR [eax+0xc],edx
        mov  eax,DWORD PTR [esp+0x34]
        mov  edx,DWORD PTR [esi+0x610]
        push  eax
        push  edx
        lea  ecx,[esi+0x5208]
        mov  edx,0x10100
        call FUN_0044c8f0
        xor  ecx,ecx
        test  eax,eax
        setge cl
        pop  edi
        pop  esi
        pop  ebp
        pop  ebx
        dec  ecx
        mov  eax,ecx
        ret  0x4
    }
}
