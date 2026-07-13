// 0043C500: FUN_0043c500
// Original size: 880 bytes, actual code: 19 instructions
extern "C" void FUN_0043bda0(void);

extern "C" __declspec(naked) void FUN_0043c500(void) {
    __asm {
        sub  esp,0x10
        mov  eax,DWORD PTR [ecx+0x18]
        push  ebx
        mov  ebx,DWORD PTR [ecx+0x24]
        and  ebx,0xffffff
        shl  eax,0x18
        push  edi
        or   ebx,eax
        lea  edi,[esp+0x8]
        mov  DWORD PTR [esp+0x8],0x42000000
        mov  DWORD PTR [esp+0xc],0x41800000
        mov  DWORD PTR [esp+0x10],0x43d00000
        mov  DWORD PTR [esp+0x14],0x43e80000
        call FUN_0043bda0
        pop  edi
        mov  eax,0x1
        pop  ebx
        add  esp,0x10
        ret
    }
}
