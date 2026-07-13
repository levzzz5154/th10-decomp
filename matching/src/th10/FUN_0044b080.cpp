// 0044B080: FUN_0044b080
// Original size: 80 bytes, actual code: 20 instructions
extern "C" void __security_check_cookie(void);

extern "C" __declspec(naked) void FUN_0044b080(void) {
    __asm {
        sub  esp,0x104
        mov  eax,ds:0x473660
        xor  eax,esp
        mov  DWORD PTR [esp+0x100],eax
        lea  eax,[esp]
        push  eax
        call  DWORD PTR ds:0x466208
        xor  eax,eax
    loc_0044B0A0:
        and  BYTE PTR [esp+eax*1],0x7f
        inc  eax
        cmp  eax,0x100
        jl loc_0044B0A0
        lea  ecx,[esp]
        push  ecx
        call  DWORD PTR ds:0x466204
        mov  ecx,DWORD PTR [esp+0x100]
        xor  ecx,esp
        call __security_check_cookie
        add  esp,0x104
        ret
    }
}
