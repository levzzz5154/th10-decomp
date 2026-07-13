// 0044D850: FUN_0044d850
// Original size: 640 bytes, actual code: 238 instructions
extern "C" void FUN_0044d110(void);
extern "C" void FUN_0044d300(void);
extern "C" void FUN_0044dd40(void);
extern "C" void FUN_0044de10(void);

extern "C" __declspec(naked) void FUN_0044d850(void) {
    __asm {
        sub  esp,0x1c
        push  ebp
        mov  ebp,DWORD PTR [esp+0x24]
        mov  eax,DWORD PTR [ebp+0x4]
        push  edi
        xor  edi,edi
        cmp  eax,edi
        je loc_0044DAC0
        cmp  DWORD PTR [ebp+0xc],edi
        je loc_0044DAC0
        mov  eax,DWORD PTR [eax]
        mov  ecx,DWORD PTR [eax]
        push  ebx
        lea  edx,[esp+0x18]
        push  edx
        lea  edx,[esp+0x24]
        push  edx
        push  eax
        call  DWORD PTR [ecx+0x10]
        mov  ecx,DWORD PTR [esp+0x18]
        mov  ebx,DWORD PTR [ebp+0x6c]
        mov  eax,DWORD PTR [ebp+0x64]
        mov  edx,ecx
        sub  edx,ebx
        cmp  eax,edx
        jb loc_0044D8A6
        cmp  eax,ecx
        jae loc_0044D8A6
        pop  ebx
        pop  edi
        mov  eax,0x800401f0
        pop  ebp
        add  esp,0x1c
        ret  0x8
    loc_0044D8A6:
        mov  eax,DWORD PTR [ebp+0x4]
        push  esi
        mov  esi,DWORD PTR [eax]
        lea  ebx,[esp+0x14]
        call FUN_0044d300
        cmp  eax,edi
        jl loc_0044D8D7
        cmp  DWORD PTR [esp+0x14],edi
        push  edi
        je loc_0044D8E1
        mov  ecx,DWORD PTR [ebp+0x4]
        mov  edx,DWORD PTR [ecx]
        push  edx
        mov  eax,ebp
        call FUN_0044d110
        xor  ecx,ecx
        cmp  eax,edi
        setge cl
        dec  ecx
        and  eax,ecx
    loc_0044D8D7:
        pop  esi
        pop  ebx
        pop  edi
        pop  ebp
        add  esp,0x1c
        ret  0x8
    loc_0044D8E1:
        mov  edx,DWORD PTR [ebp+0x4]
        mov  DWORD PTR [esp+0x14],edi
        mov  DWORD PTR [esp+0x1c],edi
        mov  eax,DWORD PTR [edx]
        mov  ecx,DWORD PTR [eax]
        lea  edx,[esp+0x2c]
        push  edx
        lea  edx,[esp+0x20]
        push  edx
        lea  edx,[esp+0x3c]
        push  edx
        lea  edx,[esp+0x20]
        push  edx
        mov  edx,DWORD PTR [ebp+0x6c]
        push  edx
        mov  edx,DWORD PTR [ebp+0x64]
        push  edx
        push  eax
        call  DWORD PTR [ecx+0x2c]
        cmp  eax,edi
        jl loc_0044D8D7
        cmp  DWORD PTR [esp+0x18],edi
        je loc_0044D929
        pop  esi
        pop  ebx
        pop  edi
        mov  eax,0x8000ffff
        pop  ebp
        add  esp,0x1c
        ret  0x8
    loc_0044D929:
        cmp  DWORD PTR [ebp+0x68],edi
        jne loc_0044D9AD
        mov  ecx,DWORD PTR [esp+0x10]
        mov  edx,DWORD PTR [esp+0x30]
        lea  eax,[esp+0x14]
        push  eax
        mov  eax,DWORD PTR [ebp+0xc]
        push  ecx
        call FUN_0044de10
        cmp  eax,edi
        jl loc_0044D8D7
        mov  edi,DWORD PTR [esp+0x14]
        mov  ecx,DWORD PTR [esp+0x30]
        cmp  edi,ecx
        jae loc_0044DA33
        mov  eax,DWORD PTR [esp+0x34]
        test  eax,eax
        jne loc_0044D9F0
        mov  eax,DWORD PTR [ebp+0xc]
        mov  edx,DWORD PTR [eax+0x90]
        sub  ecx,edi
        cmp  WORD PTR [edx+0x2e],0x8
        mov  edx,DWORD PTR [esp+0x10]
        setne al
        dec  al
        add  edi,edx
        mov  edx,ecx
        shr  ecx,0x2
        and  eax,0x80
        movzx eax,al
        mov  bl,al
        mov  bh,bl
        mov  eax,ebx
        shl  eax,0x10
        mov  ax,bx
        rep stosd
        mov  ecx,edx
        and  ecx,0x3
        rep stosb
        mov  DWORD PTR [ebp+0x68],0x1
        jmp loc_0044DA33
    loc_0044D9AD:
        mov  edx,DWORD PTR [ebp+0xc]
        mov  eax,DWORD PTR [edx+0x90]
        cmp  WORD PTR [eax+0x2e],0x8
        mov  ecx,DWORD PTR [esp+0x30]
        setne dl
        dec  dl
        mov  edi,DWORD PTR [esp+0x10]
        and  edx,0x80
        movzx eax,dl
        mov  bl,al
        mov  bh,bl
        mov  edx,ecx
        shr  ecx,0x2
        mov  eax,ebx
        shl  eax,0x10
        mov  ax,bx
        rep stosd
        mov  ecx,edx
        and  ecx,0x3
        rep stosb
        jmp loc_0044DA33
        nop
    loc_0044D9F0:
        mov  esi,DWORD PTR [ebp+0xc]
        mov  al,0x1
        call FUN_0044dd40
        test  eax,eax
        jl loc_0044D8D7
        mov  ecx,DWORD PTR [esp+0x10]
        mov  edx,DWORD PTR [esp+0x30]
        lea  eax,[esp+0x14]
        push  eax
        lea  eax,[edi+ecx*1]
        push  eax
        mov  eax,DWORD PTR [ebp+0xc]
        sub  edx,edi
        call FUN_0044de10
        test  eax,eax
        jl loc_0044D8D7
        mov  ecx,DWORD PTR [esp+0x14]
        mov  eax,DWORD PTR [esp+0x30]
        add  edi,ecx
        cmp  edi,eax
        jb loc_0044D9F0
    loc_0044DA33:
        mov  ecx,DWORD PTR [ebp+0x4]
        mov  eax,DWORD PTR [ecx]
        mov  ecx,DWORD PTR [esp+0x30]
        mov  edx,DWORD PTR [eax]
        push  0x0
        push  0x0
        push  ecx
        mov  ecx,DWORD PTR [esp+0x1c]
        push  ecx
        push  eax
        call  DWORD PTR [edx+0x4c]
        mov  edx,DWORD PTR [ebp+0x4]
        mov  eax,DWORD PTR [edx]
        mov  ecx,DWORD PTR [eax]
        push  0x0
        lea  edx,[esp+0x24]
        push  edx
        push  eax
        call  DWORD PTR [ecx+0x10]
        test  eax,eax
        jl loc_0044D8D7
        mov  edx,DWORD PTR [ebp+0x5c]
        mov  ecx,DWORD PTR [esp+0x20]
        cmp  ecx,edx
        jae loc_0044DA7A
        mov  eax,DWORD PTR [ebp+0x8]
        sub  eax,edx
        add  eax,ecx
        jmp loc_0044DA7E
    loc_0044DA7A:
        mov  eax,ecx
        sub  eax,edx
    loc_0044DA7E:
        mov  edx,DWORD PTR [ebp+0x60]
        add  edx,eax
        mov  DWORD PTR [ebp+0x5c],ecx
        mov  ecx,DWORD PTR [ebp+0x68]
        test  ecx,ecx
        mov  DWORD PTR [ebp+0x60],edx
        mov  eax,edx
        je loc_0044DAA5
        mov  ecx,DWORD PTR [ebp+0xc]
        cmp  eax,DWORD PTR [ecx+0x2c]
        jb loc_0044DAA5
        mov  edx,DWORD PTR [ebp+0x4]
        mov  eax,DWORD PTR [edx]
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0x48]
    loc_0044DAA5:
        mov  eax,DWORD PTR [ebp+0x64]
        add  eax,DWORD PTR [esp+0x30]
        xor  edx,edx
        div  DWORD PTR [ebp+0x8]
        pop  esi
        pop  ebx
        pop  edi
        xor  eax,eax
        mov  DWORD PTR [ebp+0x64],edx
        pop  ebp
        add  esp,0x1c
        ret  0x8
    loc_0044DAC0:
        pop  edi
        mov  eax,0x800401f0
        pop  ebp
        add  esp,0x1c
        ret  0x8
    }
}
