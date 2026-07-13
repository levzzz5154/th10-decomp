// 00401690: FUN_00401690
// Original size: 208 bytes, actual code: 23 instructions
extern "C" void FUN_00401530(void);
extern "C" void _vsprintf(void);
extern "C" void __security_check_cookie(void);

extern "C" __declspec(naked) void FUN_00401690(void) {
    __asm {
        sub  esp,0x204
        mov  eax,ds:0x473660
        mov  ecx,DWORD PTR [esp+0x208]
        xor  eax,esp
        mov  DWORD PTR [esp+0x200],eax
        lea  eax,[esp+0x20c]
        push  eax
        push  ecx
        lea  edx,[esp+0x8]
        push  edx
        call _vsprintf
        add  esp,0xc
        lea  eax,[esp]
        mov  ecx,esi
        call FUN_00401530
        mov  eax,DWORD PTR [esi+0x896c]
        mov  ecx,DWORD PTR [esp+0x200]
        imul  eax,eax,0x68
        xor  ecx,esp
        mov  DWORD PTR [eax+esi*1+0x764],0x1
        call __security_check_cookie
        add  esp,0x204
        ret
    }
}
