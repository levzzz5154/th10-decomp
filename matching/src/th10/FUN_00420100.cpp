// 00420100: FUN_00420100
// Original size: 368 bytes, actual code: 90 instructions
extern "C" void FUN_00413350(void);
extern "C" void FUN_004216f0(void);
extern "C" void FUN_00434c30(void);
extern "C" void FUN_00437a00(void);
extern "C" void FUN_004462f0(void);
extern "C" void FUN_0044b360(void);
extern "C" void FUN_0044b8e0(void);
extern "C" void FUN_0044c150(void);
extern "C" void _sprintf(void);
extern "C" void __beginthreadex(void);
extern "C" void __security_check_cookie(void);

extern "C" __declspec(naked) void FUN_00420100(void) {
    __asm {
        sub  esp,0x88
        mov  eax,ds:0x473660
        xor  eax,esp
        mov  DWORD PTR [esp+0x84],eax
        push  edi
        mov  eax,0x46e000
        mov  ecx,0x497990
        call FUN_00434c30
        test  al,al
        je loc_00420183
        push  0x61
        push  0x100
        lea  eax,[esp+0x10]
        push  0x46dff0
        push  eax
        call _sprintf
        add  esp,0x10
        push  0x0
        lea  ecx,[esp+0x8]
        push  ecx
        lea  eax,[esp+0x10]
        call FUN_0044b360
        test  eax,eax
        mov  edx,DWORD PTR [esp+0x4]
        mov  ds:0x49238c,eax
        mov  DWORD PTR ds:0x492388,edx
        jne loc_0042016B
        push  0x46dfc8
        jmp loc_00420188
    loc_0042016B:
        xor  eax,eax
        pop  edi
        mov  ecx,DWORD PTR [esp+0x84]
        xor  ecx,esp
        call __security_check_cookie
        add  esp,0x88
        ret
    loc_00420183:
        push  0x46dfa0
    loc_00420188:
        mov  edi,0x474f70
        call FUN_0044b8e0
        mov  ecx,DWORD PTR [esp+0x8c]
        add  esp,0x4
        pop  edi
        xor  ecx,esp
        or   eax,0xffffffff
        call __security_check_cookie
        add  esp,0x88
        ret
    }
}
