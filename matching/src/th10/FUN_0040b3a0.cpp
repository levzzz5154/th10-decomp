// 0040B3A0: FUN_0040b3a0
// Original size: 224 bytes, actual code: 72 instructions
extern "C" void FUN_0044c150(void);

extern "C" __declspec(naked) void FUN_0040b3a0(void) {
    __asm {
        push  ecx
        push  ebx
        push  ebp
        push  esi
        push  edi
        mov  edi,eax
        lea  esi,[edi+0xd0]
        mov  DWORD PTR [esp+0x10],esi
        call FUN_0044c150
        mov  ebx,DWORD PTR ds:0x491c10
        lea  edx,[edi+0x40]
        mov  ebp,0x5
        mov  edi,0x4000000
        nop
    loc_0040B3D0:
        mov  ecx,DWORD PTR [edx]
        test  ecx,ecx
        je loc_0040B43F
        mov  eax,DWORD PTR [ebx+0x72dad4]
        test  eax,eax
        je loc_0040B3ED
    loc_0040B3E0:
        mov  esi,DWORD PTR [eax]
        cmp  DWORD PTR [esi],ecx
        je loc_0040B406
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_0040B3E0
    loc_0040B3ED:
        mov  eax,DWORD PTR [ebx+0x72dadc]
        test  eax,eax
        je loc_0040B43F
    loc_0040B3F7:
        mov  esi,DWORD PTR [eax]
        cmp  DWORD PTR [esi],ecx
        je loc_0040B406
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_0040B3F7
        jmp loc_0040B43F
    loc_0040B406:
        mov  eax,DWORD PTR [eax]
        test  eax,eax
        je loc_0040B43F
        mov  esi,DWORD PTR [eax+0x35c]
        mov  ecx,DWORD PTR [eax+0x18]
        or   esi,edi
        test  ecx,ecx
        mov  DWORD PTR [eax+0x35c],esi
        jne loc_0040B43F
        mov  eax,DWORD PTR [eax+0x14]
        test  eax,eax
        je loc_0040B43F
        jmp loc_0040B430
        lea  ebx,[ebx+0x0]
    loc_0040B430:
        mov  ecx,DWORD PTR [eax]
        or   DWORD PTR [ecx+0x35c],edi
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_0040B430
    loc_0040B43F:
        mov  DWORD PTR [edx],0x0
        add  edx,0x4
        dec  ebp
        jne loc_0040B3D0
        mov  esi,DWORD PTR [esp+0x10]
        mov  DWORD PTR [esi],0x4703e4
        call FUN_0044c150
        pop  edi
        pop  esi
        pop  ebp
        pop  ebx
        pop  ecx
        ret
        mov  eax,DWORD PTR [eax+0x74]
        shr  eax,1
        and  eax,0x1
        ret
    }
}
