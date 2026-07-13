// 00447A50: FUN_00447a50
// Original size: 144 bytes, actual code: 40 instructions
extern "C" void FUN_004479d0(void);
extern "C" void _vsprintf(void);
extern "C" void __security_check_cookie(void);

extern "C" __declspec(naked) void FUN_00447a50(void) {
    __asm {
        sub  esp,0x84
        mov  eax,ds:0x473660
        mov  ecx,DWORD PTR [esp+0x90]
        xor  eax,esp
        push  ebx
        push  ebp
        movzx ebp,BYTE PTR [esi+0x3a0]
        mov  DWORD PTR [esp+0x88],eax
        push  edi
        lea  eax,[esp+0xa0]
        push  eax
        push  ecx
        lea  edx,[esp+0x14]
        push  edx
        call _vsprintf
        mov  eax,DWORD PTR [esi+0x360]
        mov  ecx,DWORD PTR [esp+0xa4]
        mov  edi,DWORD PTR [esi+0x394]
        mov  edx,DWORD PTR [edi+0x4]
        add  esp,0xc
        shr  eax,1
        and  eax,0x1
        push  eax
        push  ecx
        push  0x0
        push  edx
        lea  ebx,[esp+0x1c]
        mov  eax,ebp
        call FUN_004479d0
        mov  eax,DWORD PTR [esi+0x35c]
        mov  ecx,DWORD PTR [esp+0x8c]
        pop  edi
        pop  ebp
        or   eax,0x1
        pop  ebx
        xor  ecx,esp
        mov  DWORD PTR [esi+0x35c],eax
        call __security_check_cookie
        add  esp,0x84
        ret
    }
}
