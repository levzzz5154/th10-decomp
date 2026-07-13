// 00420EA0: FUN_00420ea0
// Original size: 464 bytes, actual code: 36 instructions
extern "C" void FUN_0044c150(void);
extern "C" void __beginthreadex(void);

extern "C" __declspec(naked) void FUN_00420ea0(void) {
    __asm {
        push  ebx
        push  ebp
        mov  ebp,DWORD PTR [esp+0xc]
        push  esi
        lea  ebx,[edi+0x6dc]
        push  ebx
        call  DWORD PTR ds:0x4660b0
        mov  dl,BYTE PTR [edi+0x6fa]
        inc  dl
        lea  esi,[edi+0x62c]
        mov  BYTE PTR [edi+0x6fa],dl
        call FUN_0044c150
        mov  ecx,DWORD PTR [esp+0x14]
        lea  eax,[esi+0x8]
        push  eax
        push  0x0
        push  ecx
        push  ebp
        push  0x0
        push  0x0
        mov  DWORD PTR [esi+0x18],ebp
        mov  DWORD PTR [esi+0x10],0x1
        mov  DWORD PTR [esi+0xc],0x0
        call __beginthreadex
        add  esp,0x18
        push  ebx
        mov  DWORD PTR [esi+0x4],eax
        call  DWORD PTR ds:0x4660b4
        mov  al,BYTE PTR [edi+0x6fa]
        pop  esi
        dec  al
        pop  ebp
        mov  BYTE PTR [edi+0x6fa],al
        xor  eax,eax
        pop  ebx
        ret  0x8
    }
}
