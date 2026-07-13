// 0043A290: FUN_0043a290
// Original size: 1184 bytes, actual code: 157 instructions
extern "C" void operator_new(void);
extern "C" void _free(void);
extern "C" void __security_check_cookie(void);

extern "C" __declspec(naked) void FUN_0043a290(void) {
    __asm {
        sub  esp,0x150
        mov  eax,ds:0x473660
        xor  eax,esp
        test  ebx,ebx
        push  ebp
        mov  ebp,DWORD PTR [esp+0x158]
        mov  DWORD PTR [esp+0x150],eax
        jne loc_0043A2CA
        xor  eax,eax
        pop  ebp
        mov  ecx,DWORD PTR [esp+0x14c]
        xor  ecx,esp
        call __security_check_cookie
        add  esp,0x150
        ret  0x4
    loc_0043A2CA:
        push  0x0
        mov  DWORD PTR [esp+0x10],0x0
        call  DWORD PTR ds:0x466308
        lea  eax,[esp+0x4]
        push  eax
        push  0x46931c
        push  0x1
        push  0x0
        push  0x46954c
        call  DWORD PTR ds:0x466304
        test  eax,eax
        jl loc_0043A37E
        mov  eax,DWORD PTR [esp+0x4]
        mov  ecx,DWORD PTR [eax]
        lea  edx,[esp+0x8]
        push  edx
        push  0x46997c
        push  eax
        call  DWORD PTR [ecx]
        test  eax,eax
        jl loc_0043A374
        lea  eax,[edi+edi*1]
        push  esi
        push  eax
        call operator_new
        add  esp,0x4
        push  edi
        mov  esi,eax
        push  esi
        push  0xffffffff
        push  ebp
        push  0x0
        push  0x0
        call  DWORD PTR ds:0x466104
        mov  eax,DWORD PTR [esp+0xc]
        mov  ecx,DWORD PTR [eax]
        push  0x0
        push  esi
        push  eax
        call  DWORD PTR [ecx+0x14]
        test  eax,eax
        jl loc_0043A360
        mov  eax,DWORD PTR [esp+0x8]
        mov  edx,DWORD PTR [eax]
        push  0x0
        lea  ecx,[esp+0x18]
        push  ecx
        push  edi
        push  ebx
        push  eax
        call  DWORD PTR [edx+0xc]
        test  eax,eax
        jl loc_0043A360
        mov  DWORD PTR [esp+0x10],0x1
    loc_0043A360:
        push  esi
        call _free
        mov  eax,DWORD PTR [esp+0x10]
        mov  edx,DWORD PTR [eax]
        add  esp,0x4
        push  eax
        call  DWORD PTR [edx+0x8]
        pop  esi
    loc_0043A374:
        mov  eax,DWORD PTR [esp+0x4]
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0x8]
    loc_0043A37E:
        call  DWORD PTR ds:0x466300
        mov  ecx,DWORD PTR [esp+0x150]
        mov  eax,DWORD PTR [esp+0xc]
        pop  ebp
        xor  ecx,esp
        call __security_check_cookie
        add  esp,0x150
        ret  0x4
        mov  eax,DWORD PTR [esp+0x8]
        sub  eax,0x110
        je loc_0043A464
        dec  eax
        push  esi
        jne loc_0043A45E
        movzx eax,WORD PTR [esp+0x10]
        sub  eax,0xc9
        je loc_0043A418
        sub  eax,0x2
        jne loc_0043A45E
        mov  esi,DWORD PTR [esp+0x8]
        push  0xca
        push  esi
        call  DWORD PTR ds:0x466250
        cmp  eax,0x1
        mov  eax,ds:0x491d78
        jne loc_0043A3FF
        push  0x7
        or   eax,0x100
        push  esi
        mov  ds:0x491d78,eax
        call  DWORD PTR ds:0x466244
        xor  eax,eax
        pop  esi
        ret  0x10
    loc_0043A3FF:
        push  0x7
        and  eax,0xfffffeff
        push  esi
        mov  ds:0x491d78,eax
        call  DWORD PTR ds:0x466244
        xor  eax,eax
        pop  esi
        ret  0x10
    loc_0043A418:
        mov  esi,DWORD PTR [esp+0x8]
        push  0xca
        push  esi
        call  DWORD PTR ds:0x466250
        cmp  eax,0x1
        mov  eax,ds:0x491d78
        jne loc_0043A44B
        push  0x6
        or   eax,0x100
        push  esi
        mov  ds:0x491d78,eax
        call  DWORD PTR ds:0x466244
        xor  eax,eax
        pop  esi
        ret  0x10
    loc_0043A44B:
        push  0x6
        and  eax,0xfffffeff
        push  esi
        mov  ds:0x491d78,eax
        call  DWORD PTR ds:0x466244
    loc_0043A45E:
        xor  eax,eax
        pop  esi
        ret  0x10
    loc_0043A464:
        mov  eax,DWORD PTR [esp+0x4]
        push  0x0
        push  0x1
        push  0xf1
        push  0xca
        push  eax
        call  DWORD PTR ds:0x466240
        push  eax
        call  DWORD PTR ds:0x466228
        xor  eax,eax
        ret  0x10
    }
}
