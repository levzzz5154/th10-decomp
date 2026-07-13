// 0044BD10: FUN_0044bd10
// Original size: 272 bytes, actual code: 87 instructions
extern "C" void __security_check_cookie(void);

extern "C" __declspec(naked) void FUN_0044bd10(void) {
    __asm {
        push  ebp
        mov  ebp,esp
        and  esp,0xfffffff8
        sub  esp,0xa4
        mov  eax,ds:0x473660
        xor  eax,ebp
        push  edi
        mov  DWORD PTR [esp+0xa4],eax
        xor  eax,eax
        mov  ecx,0x25
        lea  edi,[esp+0x8]
        rep stosd
        lea  eax,[esp+0x8]
        push  eax
        mov  DWORD PTR [esp+0xc],0x94
        call  DWORD PTR ds:0x46612c
        mov  eax,DWORD PTR [esp+0x18]
        sub  eax,0x0
        je loc_0044BDFC
        dec  eax
        je loc_0044BDB6
        dec  eax
        je loc_0044BD74
        or   eax,0xffffffff
        pop  edi
        mov  ecx,DWORD PTR [esp+0xa0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
    loc_0044BD74:
        mov  eax,DWORD PTR [esp+0xc]
        cmp  eax,0x5
        jne loc_0044BD95
        mov  eax,0x7d0
        pop  edi
        mov  ecx,DWORD PTR [esp+0xa0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
    loc_0044BD95:
        mov  edx,DWORD PTR [esp+0x10]
        imul  eax,eax,0x64
        add  eax,edx
        lea  eax,[eax+eax*4]
        shl  eax,1
        pop  edi
        mov  ecx,DWORD PTR [esp+0xa0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
    loc_0044BDB6:
        mov  eax,DWORD PTR [esp+0xc]
        cmp  eax,0x4
        jne loc_0044BDE0
        mov  eax,DWORD PTR [esp+0x10]
        neg  eax
        sbb  eax,eax
        and  eax,0x3
        add  eax,0x5f
        pop  edi
        mov  ecx,DWORD PTR [esp+0xa0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
    loc_0044BDE0:
        mov  ecx,DWORD PTR [esp+0x10]
        imul  eax,eax,0x64
        add  eax,ecx
        pop  edi
        mov  ecx,DWORD PTR [esp+0xa0]
        xor  ecx,ebp
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
    loc_0044BDFC:
        mov  ecx,DWORD PTR [esp+0xa4]
        xor  ecx,ebp
        mov  eax,0x1f
        pop  edi
        call __security_check_cookie
        mov  esp,ebp
        pop  ebp
        ret
    }
}
