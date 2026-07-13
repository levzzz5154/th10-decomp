// 00420A90: FUN_00420a90
// Original size: 128 bytes, actual code: 32 instructions
extern "C" void FUN_0043e460(void);
extern "C" void _strrchr(void);
extern "C" void __security_check_cookie(void);

extern "C" __declspec(naked) void FUN_00420a90(void) {
    __asm {
        sub  esp,0x104
        mov  eax,ds:0x473660
        xor  eax,esp
        mov  DWORD PTR [esp+0x100],eax
        mov  eax,DWORD PTR [esp+0x10c]
        lea  edx,[esp]
        sub  edx,eax
    loc_00420AB0:
        mov  cl,BYTE PTR [eax]
        mov  BYTE PTR [edx+eax*1],cl
        inc  eax
        test  cl,cl
        jne loc_00420AB0
        lea  eax,[esp]
        push  0x2e
        push  eax
        call _strrchr
        mov  ecx,DWORD PTR [esp+0x110]
        add  esp,0x8
        push  ecx
        mov  BYTE PTR [eax+0x1],0x77
        mov  BYTE PTR [eax+0x2],0x61
        mov  BYTE PTR [eax+0x3],0x76
        push  0x1
        lea  edx,[esp+0x8]
        mov  eax,0x492590
        call FUN_0043e460
        mov  ecx,DWORD PTR [esp+0x100]
        xor  ecx,esp
        mov  eax,0x1
        call __security_check_cookie
        add  esp,0x104
        ret  0x8
    }
}
