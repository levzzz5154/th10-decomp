// 00432690: FUN_00432690
// Original size: 864 bytes, actual code: 267 instructions
extern "C" void FUN_00447bb0(void);
extern "C" void __security_check_cookie(void);

extern "C" __declspec(naked) void FUN_00432690(void) {
    __asm {
        sub  esp,0xc0
        mov  eax,ds:0x473660
        xor  eax,esp
        push  ebx
        push  ebp
        push  esi
        mov  esi,ecx
        mov  DWORD PTR [esp+0xc8],eax
        mov  eax,DWORD PTR [esi+0x1d4]
        lea  eax,[eax+eax*4]
        push  edi
        xor  edi,edi
        lea  edx,[eax+eax*1-0xa]
        xor  ecx,ecx
        test  edx,edx
        mov  DWORD PTR [esp+0x1c],esi
        mov  DWORD PTR [esp+0x14],edi
        jle loc_004326F5
        mov  eax,DWORD PTR [esi+0x1d4]
        mov  edx,DWORD PTR [esi+0xfc]
        lea  eax,[eax+eax*4]
        lea  eax,[eax+eax*1-0xa]
        lea  ebx,[ebx+0x0]
    loc_004326E0:
        movsx ebx,BYTE PTR [edi+0x4743c0]
        cmp  ebx,edx
        jne loc_004326EC
        inc  ecx
    loc_004326EC:
        inc  edi
        cmp  ecx,eax
        jl loc_004326E0
        mov  DWORD PTR [esp+0x14],edi
    loc_004326F5:
        xor  ecx,ecx
        lea  eax,[esi+0x5d4]
        mov  DWORD PTR [esi+0x2ac],0x0
        mov  DWORD PTR [esp+0x18],ecx
        mov  DWORD PTR [esp+0x10],eax
        nop
    loc_00432710:
        cmp  edi,0x6e
        jge loc_00432735
        mov  eax,DWORD PTR [esi+0xfc]
        jmp loc_00432720
        nop
    loc_00432720:
        movsx edx,BYTE PTR [edi+0x4743c0]
        cmp  edx,eax
        je loc_00432767
        inc  edi
        cmp  edi,0x6e
        mov  DWORD PTR [esp+0x14],edi
        jl loc_00432720
    loc_00432735:
        cmp  ecx,0xa
        jge loc_004329C7
        mov  ebx,0xa
        lea  edi,[esi+ecx*4+0x5d4]
        sub  ebx,ecx
        nop
    loc_00432750:
        mov  ecx,DWORD PTR [edi]
        test  ecx,ecx
        mov  edx,DWORD PTR ds:0x491c10
        jne loc_0043295F
    loc_00432760:
        xor  eax,eax
        jmp loc_004329A5
    loc_00432767:
        cmp  edi,0x6e
        jge loc_00432735
        mov  ebp,DWORD PTR ds:0x47783c
        lea  ebx,[edi+edi*8]
        shl  ebx,0x4
        mov  eax,DWORD PTR [ebx+ebp*1+0x19b10]
        test  eax,eax
        mov  DWORD PTR [esp+0x20],ebx
        je loc_0043289C
        lea  eax,[ebx+ebp*1+0x19a8c]
        lea  edx,[esp+0x24]
        sub  edx,eax
    loc_00432798:
        mov  cl,BYTE PTR [eax]
        mov  BYTE PTR [edx+eax*1],cl
        inc  eax
        test  cl,cl
        jne loc_00432798
        lea  edx,[esp+0x24]
        lea  ecx,[edx+0x1]
        nop
    loc_004327B0:
        mov  al,BYTE PTR [edx]
        inc  edx
        test  al,al
        jne loc_004327B0
        sub  edx,ecx
        cmp  edx,0x2a
        jge loc_004327EC
        mov  esi,0x2a
        sub  esi,edx
        mov  ecx,esi
        mov  ebx,ecx
        shr  ecx,0x2
        lea  edi,[esp+edx*1+0x24]
        mov  eax,0x20202020
        rep stosd
        mov  ecx,ebx
        mov  ebx,DWORD PTR [esp+0x20]
        and  ecx,0x3
        rep stosb
        mov  edi,DWORD PTR [esp+0x14]
        add  edx,esi
        mov  esi,DWORD PTR [esp+0x1c]
    loc_004327EC:
        mov  eax,DWORD PTR [esi+0x24]
        mov  esi,DWORD PTR ds:0x491c10
        imul  eax,eax,0x437c
        mov  BYTE PTR [esp+edx*1+0x24],0x0
        mov  edx,DWORD PTR [esp+0x10]
        mov  edx,DWORD PTR [edx]
        test  edx,edx
        lea  ecx,[eax+ebp*1+0x8]
        jne loc_00432812
    loc_0043280E:
        xor  eax,eax
        jmp loc_0043284E
    loc_00432812:
        mov  eax,DWORD PTR [esi+0x72dad4]
        test  eax,eax
        je loc_0043282E
        nop
    loc_00432820:
        mov  ebp,DWORD PTR [eax]
        cmp  DWORD PTR [ebp+0x0],edx
        je loc_00432848
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_00432820
    loc_0043282E:
        mov  eax,DWORD PTR [esi+0x72dadc]
        test  eax,eax
        je loc_0043280E
    loc_00432838:
        mov  ebp,DWORD PTR [eax]
        cmp  DWORD PTR [ebp+0x0],edx
        je loc_00432848
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_00432838
        jmp loc_0043284E
    loc_00432848:
        mov  eax,DWORD PTR [eax]
        test  eax,eax
        jne loc_00432858
    loc_0043284E:
        mov  edx,DWORD PTR [esp+0x10]
        mov  DWORD PTR [edx],0x0
    loc_00432858:
        mov  edx,DWORD PTR [ebx+ecx*1+0x620]
        push  edx
        mov  edx,DWORD PTR [ebx+ecx*1+0x61c]
        mov  ecx,DWORD PTR [ebx+ecx*1+0x61c]
        push  edx
        inc  edi
        neg  ecx
        lea  edx,[esp+0x2c]
        push  edx
        sbb  ecx,ecx
        push  edi
        and  ecx,0x100f91
        push  0x46eef8
        add  ecx,0xefefef
        push  ecx
        push  esi
        mov  esi,eax
        call FUN_00447bb0
        add  esp,0x1c
        jmp loc_00432926
    loc_0043289C:
        mov  edx,DWORD PTR [esi+0x24]
        mov  eax,DWORD PTR [esp+0x10]
        imul  edx,edx,0x437c
        mov  ecx,DWORD PTR [eax]
        test  ecx,ecx
        lea  ebp,[edx+ebp*1+0x8]
        mov  edx,DWORD PTR ds:0x491c10
        jne loc_004328BD
    loc_004328B9:
        xor  eax,eax
        jmp loc_004328F5
    loc_004328BD:
        mov  eax,DWORD PTR [edx+0x72dad4]
        test  eax,eax
        je loc_004328D4
    loc_004328C7:
        mov  esi,DWORD PTR [eax]
        cmp  DWORD PTR [esi],ecx
        je loc_004328EF
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_004328C7
    loc_004328D4:
        mov  eax,DWORD PTR [edx+0x72dadc]
        test  eax,eax
        je loc_004328B9
        mov  edi,edi
    loc_004328E0:
        mov  esi,DWORD PTR [eax]
        cmp  DWORD PTR [esi],ecx
        je loc_004328EF
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_004328E0
        jmp loc_004328F5
    loc_004328EF:
        mov  eax,DWORD PTR [eax]
        test  eax,eax
        jne loc_004328FF
    loc_004328F5:
        mov  ecx,DWORD PTR [esp+0x10]
        mov  DWORD PTR [ecx],0x0
    loc_004328FF:
        mov  ecx,DWORD PTR [ebx+ebp*1+0x620]
        push  ecx
        mov  ecx,DWORD PTR [ebx+ebp*1+0x61c]
        push  ecx
        inc  edi
        push  edi
        push  0x46eebc
        push  0x808080
        push  edx
        mov  esi,eax
        call FUN_00447bb0
        add  esp,0x18
    loc_00432926:
        mov  eax,DWORD PTR [esp+0x1c]
        mov  ebx,DWORD PTR [eax+0x2ac]
        mov  edx,DWORD PTR [esp+0x10]
        inc  ebx
        mov  DWORD PTR [eax+0x2ac],ebx
        mov  eax,DWORD PTR [esp+0x18]
        inc  eax
        add  edx,0x4
        cmp  eax,0xa
        mov  DWORD PTR [esp+0x14],edi
        mov  DWORD PTR [esp+0x18],eax
        mov  DWORD PTR [esp+0x10],edx
        jge loc_004329C7
        mov  esi,DWORD PTR [esp+0x1c]
        mov  ecx,eax
        jmp loc_00432710
    loc_0043295F:
        mov  eax,DWORD PTR [edx+0x72dad4]
        test  eax,eax
        je loc_0043297D
        nop
    loc_00432970:
        mov  esi,DWORD PTR [eax]
        cmp  DWORD PTR [esi],ecx
        je loc_0043299F
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_00432970
    loc_0043297D:
        mov  eax,DWORD PTR [edx+0x72dadc]
        test  eax,eax
        je loc_00432760
        jmp loc_00432990
        nop
    loc_00432990:
        mov  esi,DWORD PTR [eax]
        cmp  DWORD PTR [esi],ecx
        je loc_0043299F
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_00432990
        jmp loc_004329A5
    loc_0043299F:
        mov  eax,DWORD PTR [eax]
        test  eax,eax
        jne loc_004329AB
    loc_004329A5:
        mov  DWORD PTR [edi],0x0
    loc_004329AB:
        push  0x46cfd4
        push  0xffffffff
        push  edx
        mov  esi,eax
        call FUN_00447bb0
        add  esp,0xc
        add  edi,0x4
        dec  ebx
        jne loc_00432750
    loc_004329C7:
        mov  ecx,DWORD PTR [esp+0xcc]
        pop  edi
        pop  esi
        pop  ebp
        pop  ebx
        xor  ecx,esp
        xor  eax,eax
        call __security_check_cookie
        add  esp,0xc0
        ret
    }
}
