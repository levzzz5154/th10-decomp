// 0044C7E0: FUN_0044c7e0
// Original size: 272 bytes, actual code: 79 instructions
extern "C" void __security_check_cookie(void);

extern "C" __declspec(naked) void FUN_0044c7e0(void) {
    __asm {
        sub  esp,0x40
        mov  eax,ds:0x473660
        xor  eax,esp
        mov  DWORD PTR [esp+0x3c],eax
        mov  eax,DWORD PTR [esp+0x44]
        mov  eax,DWORD PTR [eax]
        test  eax,eax
        push  esi
        mov  esi,ecx
        mov  DWORD PTR [esp+0x4],0x0
        jne loc_0044C81A
        mov  eax,0x800401f0
        pop  esi
        mov  ecx,DWORD PTR [esp+0x3c]
        xor  ecx,esp
        call __security_check_cookie
        add  esp,0x40
        ret  0x4
    loc_0044C81A:
        xor  ecx,ecx
        mov  DWORD PTR [esp+0x1c],ecx
        mov  DWORD PTR [esp+0x20],ecx
        mov  DWORD PTR [esp+0x24],ecx
        mov  DWORD PTR [esp+0x28],ecx
        mov  DWORD PTR [esp+0x2c],ecx
        mov  DWORD PTR [esp+0x30],ecx
        mov  DWORD PTR [esp+0x34],ecx
        mov  DWORD PTR [esp+0x38],ecx
        push  ecx
        mov  DWORD PTR [esp+0x40],ecx
        mov  DWORD PTR [esp+0x28],ecx
        mov  DWORD PTR [esp+0x30],ecx
        lea  ecx,[esp+0x8]
        push  ecx
        lea  ecx,[esp+0x24]
        push  ecx
        mov  DWORD PTR [esp+0x28],0x24
        mov  DWORD PTR [esp+0x2c],0x1
        mov  edx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [edx+0xc]
        test  eax,eax
        jl loc_0044C8D2
        xor  edx,edx
        mov  DWORD PTR [esp+0x8],edx
        mov  DWORD PTR [esp+0xc],edx
        mov  DWORD PTR [esp+0x10],edx
        mov  DWORD PTR [esp+0x14],edx
        mov  WORD PTR [esp+0x16],si
        shr  si,0x3
        mov  WORD PTR [esp+0x18],dx
        lea  edx,[esp+0x8]
        push  edx
        mov  WORD PTR [esp+0xc],0x1
        mov  WORD PTR [esp+0xe],bx
        mov  DWORD PTR [esp+0x10],edi
        imul  esi,ebx
        movzx eax,si
        imul  eax,edi
        mov  DWORD PTR [esp+0x14],eax
        mov  eax,DWORD PTR [esp+0x8]
        mov  WORD PTR [esp+0x18],si
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0x38]
        test  eax,eax
        jl loc_0044C8D2
        mov  eax,DWORD PTR [esp+0x4]
        test  eax,eax
        je loc_0044C8D0
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0x8]
    loc_0044C8D0:
        xor  eax,eax
    loc_0044C8D2:
        mov  ecx,DWORD PTR [esp+0x40]
        pop  esi
        xor  ecx,esp
        call __security_check_cookie
        add  esp,0x40
        ret  0x4
    }
}
