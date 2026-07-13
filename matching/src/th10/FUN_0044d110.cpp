// 0044D110: FUN_0044d110
// Original size: 496 bytes, actual code: 169 instructions
extern "C" void FUN_0044dd40(void);
extern "C" void FUN_0044de10(void);

extern "C" __declspec(naked) void FUN_0044d110(void) {
    __asm {
        sub  esp,0xc
        push  ebx
        push  ebp
        mov  ebp,DWORD PTR [esp+0x18]
        push  edi
        xor  edi,edi
        cmp  ebp,edi
        mov  ebx,eax
        mov  DWORD PTR [esp+0xc],edi
        mov  DWORD PTR [esp+0x1c],edi
        mov  DWORD PTR [esp+0x10],edi
        jne loc_0044D13C
        pop  edi
        pop  ebp
        mov  eax,0x800401f0
        pop  ebx
        add  esp,0xc
        ret  0x8
    loc_0044D13C:
        mov  eax,DWORD PTR [ebp+0x0]
        lea  ecx,[esp+0x14]
        push  ecx
        push  ebp
        call  DWORD PTR [eax+0x24]
        cmp  eax,edi
        jl loc_0044D2EA
        test  BYTE PTR [esp+0x14],0x2
        push  esi
        je loc_0044D17D
        mov  esi,DWORD PTR ds:0x4660ac
        mov  edi,edi
    loc_0044D160:
        mov  edx,DWORD PTR [ebp+0x0]
        push  ebp
        call  DWORD PTR [edx+0x50]
        cmp  eax,0x88780096
        jne loc_0044D172
        push  0xa
        call  esi
    loc_0044D172:
        mov  eax,DWORD PTR [ebp+0x0]
        push  ebp
        call  DWORD PTR [eax+0x50]
        test  eax,eax
        jne loc_0044D160
    loc_0044D17D:
        mov  ecx,DWORD PTR [ebp+0x0]
        push  edi
        push  edi
        push  edi
        lea  edx,[esp+0x2c]
        push  edx
        mov  edx,DWORD PTR [ebx+0x8]
        lea  eax,[esp+0x20]
        push  eax
        push  edx
        push  edi
        push  ebp
        call  DWORD PTR [ecx+0x2c]
        cmp  eax,edi
        jl loc_0044D2E9
        mov  esi,DWORD PTR [ebx+0xc]
        cmp  DWORD PTR [esi+0x7c],edi
        je loc_0044D1C7
        mov  eax,DWORD PTR [esi+0x80]
        mov  ecx,DWORD PTR [esi+0x90]
        mov  DWORD PTR [esi+0x84],eax
        mov  eax,DWORD PTR [ecx+0x1c]
        cmp  eax,edi
        jle loc_0044D1F8
        mov  DWORD PTR [esi+0x88],eax
        jmp loc_0044D1F8
    loc_0044D1C7:
        mov  eax,DWORD PTR [esi+0x8c]
        cmp  eax,edi
        je loc_0044D1F8
        mov  edx,DWORD PTR [esi+0x90]
        mov  ecx,DWORD PTR [edx+0x10]
        mov  edx,DWORD PTR ds:0x4977a4
        push  edi
        push  edi
        add  ecx,edx
        push  ecx
        push  eax
        call  DWORD PTR ds:0x4660c8
        mov  edx,DWORD PTR [esi+0x90]
        mov  eax,DWORD PTR [edx+0x1c]
        mov  DWORD PTR [esi+0x8],eax
    loc_0044D1F8:
        mov  edx,DWORD PTR [esp+0x10]
        mov  eax,DWORD PTR [ebx+0xc]
        lea  ecx,[esp+0x14]
        push  ecx
        push  edx
        mov  edx,DWORD PTR [esp+0x28]
        call FUN_0044de10
        cmp  eax,edi
        jl loc_0044D2E9
        mov  edi,DWORD PTR [esp+0x14]
        test  edi,edi
        mov  ecx,DWORD PTR [esp+0x20]
        jne loc_0044D243
        mov  eax,DWORD PTR [ebx+0xc]
        mov  edx,DWORD PTR [eax+0x90]
        cmp  WORD PTR [edx+0x2e],0x8
        mov  edi,DWORD PTR [esp+0x10]
        setne al
        dec  al
        and  eax,0x80
        movzx eax,al
        jmp loc_0044D2B8
    loc_0044D243:
        cmp  edi,ecx
        jae loc_0044D2D2
        mov  eax,DWORD PTR [esp+0x24]
        test  eax,eax
        je loc_0044D294
    loc_0044D253:
        mov  esi,DWORD PTR [ebx+0xc]
        xor  al,al
        call FUN_0044dd40
        test  eax,eax
        jl loc_0044D2E9
        mov  ecx,DWORD PTR [esp+0x10]
        mov  edx,DWORD PTR [esp+0x20]
        lea  eax,[esp+0x14]
        push  eax
        lea  eax,[edi+ecx*1]
        push  eax
        mov  eax,DWORD PTR [ebx+0xc]
        sub  edx,edi
        call FUN_0044de10
        test  eax,eax
        jl loc_0044D2E9
        mov  ecx,DWORD PTR [esp+0x14]
        mov  eax,DWORD PTR [esp+0x20]
        add  edi,ecx
        cmp  edi,eax
        jb loc_0044D253
        jmp loc_0044D2D2
    loc_0044D294:
        mov  edx,DWORD PTR [ebx+0xc]
        mov  eax,DWORD PTR [edx+0x90]
        sub  ecx,edi
        cmp  WORD PTR [eax+0x2e],0x8
        setne dl
        dec  dl
        and  edx,0x80
        movzx eax,dl
        mov  edx,DWORD PTR [esp+0x10]
        add  edi,edx
    loc_0044D2B8:
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
    loc_0044D2D2:
        mov  ecx,DWORD PTR [esp+0x20]
        mov  edx,DWORD PTR [esp+0x10]
        mov  eax,DWORD PTR [ebp+0x0]
        push  0x0
        push  0x0
        push  ecx
        push  edx
        push  ebp
        call  DWORD PTR [eax+0x4c]
        xor  eax,eax
    loc_0044D2E9:
        pop  esi
    loc_0044D2EA:
        pop  edi
        pop  ebp
        pop  ebx
        add  esp,0xc
        ret  0x8
    }
}
