// 0044A4E0: FUN_0044a4e0
// Original size: 272 bytes, actual code: 80 instructions
extern "C" void __security_check_cookie(void);

extern "C" __declspec(naked) void FUN_0044a4e0(void) {
    __asm {
        sub  esp,0x148
        mov  eax,ds:0x473660
        xor  eax,esp
        push  ebx
        mov  DWORD PTR [esp+0x148],eax
        push  edi
        mov  ebx,ecx
        xor  eax,eax
        mov  ecx,0x20
        mov  edi,0x497bb0
        rep stosd
        mov  eax,ds:0x491ff4
        test  ah,0x4
        jne loc_0044A55D
        xor  eax,eax
        mov  ecx,0xd
        lea  edi,[esp+0x8]
        rep stosd
        lea  eax,[esp+0x8]
        push  eax
        push  0x0
        mov  DWORD PTR [esp+0x10],0x34
        mov  DWORD PTR [esp+0x14],0xff
        call  DWORD PTR ds:0x466280
        test  eax,eax
        jne loc_0044A5CC
        mov  ecx,DWORD PTR [esp+0x28]
        mov  dl,0x80
    loc_0044A548:
        test  cl,0x1
        je loc_0044A553
        mov  BYTE PTR [eax+0x497bb0],dl
    loc_0044A553:
        inc  eax
        shr  ecx,1
        cmp  eax,0x20
        jb loc_0044A548
        jmp loc_0044A5CC
    loc_0044A55D:
        mov  eax,DWORD PTR [ebx*4+0x491c3c]
        mov  ecx,DWORD PTR [eax]
        push  esi
        push  eax
        call  DWORD PTR [ecx+0x64]
        test  eax,eax
        jge loc_0044A5A4
        mov  eax,DWORD PTR [ebx*4+0x491c3c]
        mov  edx,DWORD PTR [eax]
        push  eax
        xor  esi,esi
        call  DWORD PTR [edx+0x1c]
        cmp  eax,0x8007001e
        jne loc_0044A5CB
    loc_0044A585:
        mov  eax,DWORD PTR [ebx*4+0x491c3c]
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0x1c]
        inc  esi
        cmp  esi,0x190
        jge loc_0044A5CB
        cmp  eax,0x8007001e
        je loc_0044A585
        jmp loc_0044A5CB
    loc_0044A5A4:
        mov  ebx,DWORD PTR [ebx*4+0x491c3c]
        mov  edx,DWORD PTR [ebx]
        lea  eax,[esp+0x40]
        push  eax
        push  0x110
        push  ebx
        call  DWORD PTR [edx+0x24]
        mov  ecx,0x20
        lea  esi,[esp+0x70]
        mov  edi,0x497bb0
        rep movsd
    loc_0044A5CB:
        pop  esi
    loc_0044A5CC:
        mov  ecx,DWORD PTR [esp+0x14c]
        pop  edi
        pop  ebx
        xor  ecx,esp
        mov  eax,0x497bb0
        call __security_check_cookie
        add  esp,0x148
        ret
    }
}
