// 004391F0: FUN_004391f0
// Original size: 240 bytes, actual code: 65 instructions
extern "C" void FUN_00420670(void);
extern "C" void FUN_00438a30(void);
extern "C" void FUN_00438a60(void);
extern "C" void FUN_00439d20(void);
extern "C" void FUN_0044b4d0(void);
extern "C" void FUN_00452abc(void);
extern "C" void _sprintf(void);
extern "C" void __security_check_cookie(void);

extern "C" __declspec(naked) void FUN_004391f0(void) {
    __asm {
        sub  esp,0x104
        mov  eax,ds:0x473660
        xor  eax,esp
        push  0x0
        push  0x0
        push  0x0
        mov  DWORD PTR [esp+0x10c],eax
        mov  eax,ds:0x491c30
        mov  ecx,DWORD PTR [eax]
        push  0x0
        push  eax
        call  DWORD PTR [ecx+0x44]
        test  eax,eax
        jge loc_00439244
        mov  eax,ds:0x491c10
        call FUN_00438a30
        mov  eax,ds:0x491c30
        mov  edx,DWORD PTR [eax]
        push  0x491d0c
        push  eax
        call  DWORD PTR [edx+0x40]
        call FUN_00439d20
        mov  DWORD PTR ds:0x491fd4,0x2
    loc_00439244:
        push  esi
        mov  esi,DWORD PTR ds:0x491c10
        call FUN_00438a60
        mov  eax,ds:0x474e36
        test  ah,0x8
        je loc_004392C6
        push  0x46f6e4
        call FUN_00452abc
        add  esp,0x4
        xor  esi,esi
        nop
    loc_00439270:
        push  esi
        lea  eax,[esp+0x8]
        push  0x46f6d0
        push  eax
        call _sprintf
        add  esp,0xc
        lea  ecx,[esp+0x4]
        push  ecx
        call FUN_0044b4d0
        test  eax,eax
        je loc_004392B0
        inc  esi
        cmp  esi,0x3e8
        jl loc_00439270
        pop  esi
        mov  ecx,DWORD PTR [esp+0x100]
        xor  ecx,esp
        call __security_check_cookie
        add  esp,0x104
        ret
    loc_004392B0:
        cmp  esi,0x3e8
        jge loc_004392C6
        lea  eax,[esp+0x4]
        mov  esi,0x491c28
        call FUN_00420670
    loc_004392C6:
        mov  ecx,DWORD PTR [esp+0x104]
        pop  esi
        xor  ecx,esp
        call __security_check_cookie
        add  esp,0x104
        ret
    }
}
