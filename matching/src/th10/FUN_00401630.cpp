// 00401630: FUN_00401630
// Original size: 96 bytes, actual code: 20 instructions
extern "C" void FUN_00401530(void);
extern "C" void _vsprintf(void);
extern "C" void __security_check_cookie(void);

extern "C" __declspec(naked) void FUN_00401630(void) {
    __asm {
        sub  esp,0x204
        mov  eax,ds:0x473660
        mov  ecx,DWORD PTR [esp+0x20c]
        xor  eax,esp
        mov  DWORD PTR [esp+0x200],eax
        lea  eax,[esp+0x210]
        push  eax
        push  ecx
        lea  edx,[esp+0x8]
        push  edx
        call _vsprintf
        mov  ecx,DWORD PTR [esp+0x214]
        add  esp,0xc
        lea  eax,[esp]
        call FUN_00401530
        mov  ecx,DWORD PTR [esp+0x200]
        xor  ecx,esp
        call __security_check_cookie
        add  esp,0x204
        ret
    }
}
