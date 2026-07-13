// 00419F40: FUN_00419f40
// Original size: 272 bytes, actual code: 108 instructions
extern "C" void FUN_0041a0a0(void);
extern "C" void FUN_00452730(void);

extern "C" __declspec(naked) void FUN_00419f40(void) {
    __asm {
        mov  ecx,DWORD PTR [esp+0xc]
        push  ebx
        mov  edx,ecx
        push  ebp
        mov  ebp,DWORD PTR [esp+0xc]
        shr  ecx,0x2
        push  edi
        mov  ebx,eax
        xor  eax,eax
        mov  edi,ebp
        rep stosd
        mov  ecx,edx
        and  ecx,0x3
        rep stosb
        cmp  BYTE PTR [ebp+0x0],0x0
        jne loc_0041A03C
        push  esi
        lea  ebx,[ebx+0x0]
    loc_00419F70:
        push  0xa
        push  ebx
        call FUN_00452730
        add  esp,0x8
        test  eax,eax
        jne loc_00419F92
        push  0xd
        push  ebx
        call FUN_00452730
        add  esp,0x8
        test  eax,eax
        je loc_0041A01D
    loc_00419F92:
        mov  edx,DWORD PTR [esp+0x1c]
        mov  ecx,eax
        sub  ecx,ebx
        dec  edx
        cmp  ecx,edx
        jl loc_00419FA1
        mov  ecx,edx
    loc_00419FA1:
        mov  edx,ecx
        shr  ecx,0x2
        mov  esi,ebx
        mov  edi,ebp
        rep movsd
        mov  ecx,edx
        and  ecx,0x3
        rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
        mov  ecx,DWORD PTR [esp+0x18]
        mov  edx,DWORD PTR [ecx]
        sub  ebx,eax
        add  edx,ebx
        mov  DWORD PTR [ecx],edx
        mov  ebx,eax
    loc_00419FC1:
        mov  al,BYTE PTR [ebx]
        cmp  al,0xa
        je loc_00419FCB
        cmp  al,0xd
        jne loc_00419FD3
    loc_00419FCB:
        mov  eax,DWORD PTR [ecx]
        inc  ebx
        dec  eax
        mov  DWORD PTR [ecx],eax
        jmp loc_00419FC1
    loc_00419FD3:
        push  0x23
        push  ebp
        call FUN_00452730
        mov  edx,eax
        add  esp,0x8
        test  edx,edx
        je loc_0041A003
        mov  edi,DWORD PTR [esp+0x1c]
        mov  ecx,ebp
        sub  ecx,edx
        add  ecx,edi
        mov  esi,ecx
        shr  ecx,0x2
        xor  eax,eax
        mov  edi,edx
        rep stosd
        mov  ecx,esi
        and  ecx,0x3
        rep stosb
        mov  BYTE PTR [edx],0x0
    loc_0041A003:
        mov  eax,ebp
        call FUN_0041a0a0
        cmp  BYTE PTR [ebp+0x0],0x0
        je loc_00419F70
        pop  esi
        pop  edi
        pop  ebp
        mov  eax,ebx
        pop  ebx
        ret  0xc
    loc_0041A01D:
        mov  eax,DWORD PTR [esp+0x18]
        mov  ecx,DWORD PTR [eax]
        mov  edx,ecx
        shr  ecx,0x2
        mov  esi,ebx
        mov  edi,ebp
        rep movsd
        mov  ecx,edx
        and  ecx,0x3
        rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
        mov  DWORD PTR [eax],0x0
        pop  esi
    loc_0041A03C:
        pop  edi
        pop  ebp
        mov  eax,ebx
        pop  ebx
        ret  0xc
    }
}
