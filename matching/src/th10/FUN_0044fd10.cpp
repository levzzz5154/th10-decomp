// 0044FD10: FUN_0044fd10
// Original size: 160 bytes, actual code: 59 instructions
extern "C" void FUN_0044e1a0(void);
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_0044fd10(void) {
    __asm {
        push  ebx
        push  ebp
        push  esi
        lea  esi,[edi+0x1030]
        test  esi,esi
        mov  ebp,0x1
        je loc_0044FD8B
    loc_0044FD22:
        test  ebp,ebp
        mov  eax,DWORD PTR [esi]
        mov  ebx,DWORD PTR [esi+0x4]
        mov  DWORD PTR [edi+0x4],eax
        je loc_0044FD40
        mov  ecx,DWORD PTR [esp+0x10]
        push  ecx
        call FUN_0044e1a0
        test  eax,eax
        jne loc_0044FD99
        xor  ebp,ebp
        jmp loc_0044FD85
    loc_0044FD40:
        mov  edx,DWORD PTR [esp+0x10]
        push  edx
        call FUN_0044e1a0
        test  eax,eax
        je loc_0044FD85
        mov  eax,DWORD PTR [edi+0x4]
        push  eax
        call _free
        mov  eax,DWORD PTR [esi+0x4]
        xor  ecx,ecx
        add  esp,0x4
        cmp  eax,ecx
        je loc_0044FD69
        mov  edx,DWORD PTR [esi+0x8]
        mov  DWORD PTR [eax+0x8],edx
    loc_0044FD69:
        mov  eax,DWORD PTR [esi+0x8]
        cmp  eax,ecx
        je loc_0044FD76
        mov  edx,DWORD PTR [esi+0x4]
        mov  DWORD PTR [eax+0x4],edx
    loc_0044FD76:
        push  esi
        mov  DWORD PTR [esi+0x4],ecx
        mov  DWORD PTR [esi+0x8],ecx
        call _free
        add  esp,0x4
    loc_0044FD85:
        test  ebx,ebx
        mov  esi,ebx
        jne loc_0044FD22
    loc_0044FD8B:
        pop  esi
        lea  eax,[edi+0x8]
        pop  ebp
        mov  DWORD PTR [edi+0x4],eax
        xor  eax,eax
        pop  ebx
        ret  0x4
    loc_0044FD99:
        pop  esi
        pop  ebp
        or   eax,0xffffffff
        pop  ebx
        ret  0x4
    }
}
