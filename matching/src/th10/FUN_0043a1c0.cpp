// 0043A1C0: FUN_0043a1c0
// Original size: 208 bytes, actual code: 66 instructions
extern "C" void FUN_0044b360(void);
extern "C" void _free(void);
extern "C" void __security_check_cookie(void);

extern "C" __declspec(naked) void FUN_0043a1c0(void) {
    __asm {
        sub  esp,0x110
        mov  eax,ds:0x473660
        xor  eax,esp
        mov  DWORD PTR [esp+0x10c],eax
        push  0x105
        lea  eax,[esp+0x8]
        push  eax
        push  0x0
        call  DWORD PTR ds:0x4660dc
        test  eax,eax
        je loc_0043A277
        push  ebx
        push  esi
        push  0x1
        lea  ecx,[esp+0xc]
        push  ecx
        lea  eax,[esp+0x14]
        xor  esi,esi
        call FUN_0044b360
        mov  ecx,eax
        test  ecx,ecx
        mov  ebx,ecx
        jne loc_0043A224
        pop  esi
        or   eax,0xffffffff
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x10c]
        xor  ecx,esp
        call __security_check_cookie
        add  esp,0x110
        ret
    loc_0043A224:
        push  edi
        mov  edi,DWORD PTR [esp+0xc]
        mov  eax,edi
        cdq
        and  edx,0x3
        add  eax,edx
        sar  eax,0x2
        dec  eax
        test  eax,eax
        jle loc_0043A248
        nop
    loc_0043A240:
        add  esi,DWORD PTR [ecx]
        add  ecx,0x4
        dec  eax
        jne loc_0043A240
    loc_0043A248:
        push  ebx
        call _free
        add  esp,0x4
        mov  DWORD PTR ds:0x492384,edi
        pop  edi
        mov  DWORD PTR ds:0x492380,esi
        mov  eax,esi
        pop  esi
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x10c]
        xor  ecx,esp
        call __security_check_cookie
        add  esp,0x110
        ret
    loc_0043A277:
        mov  ecx,DWORD PTR [esp+0x10c]
        xor  ecx,esp
        or   eax,0xffffffff
        call __security_check_cookie
        add  esp,0x110
        ret
    }
}
