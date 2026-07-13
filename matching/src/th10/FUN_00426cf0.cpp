// 00426CF0: FUN_00426cf0
// Original size: 640 bytes, actual code: 141 instructions
extern "C" void FUN_0043dc90(void);
extern "C" void FUN_0043e710(void);
extern "C" void FUN_004489d0(void);
extern "C" void FUN_004492f0(void);
extern "C" void FUN_00449870(void);
extern "C" void FUN_00449950(void);

extern "C" __declspec(naked) void FUN_00426cf0(void) {
    __asm {
        sub  esp,0x14
        mov  ecx,DWORD PTR ds:0x4776f0
        push  ebx
        push  ebp
        mov  ebp,DWORD PTR [esp+0x20]
        mov  DWORD PTR [ebp+0x458],0x4
        fld  DWORD PTR [ebp+0x3c0]
        fadd  DWORD PTR ds:0x470b4c
        mov  eax,DWORD PTR [ebp+0x3c8]
        push  esi
        mov  esi,DWORD PTR ds:0x491c10
        fstp  DWORD PTR [esp+0x14]
        push  edi
        fld  DWORD PTR [ebp+0x3c4]
        mov  edi,DWORD PTR [ecx+0x3e0b50]
        fadd  DWORD PTR ds:0x470b48
        mov  DWORD PTR [esp+0x20],eax
        fstp  DWORD PTR [esp+0x1c]
        call FUN_00449950
        mov  ebx,eax
        mov  esi,DWORD PTR [ebx+0x35c]
        push  0x162
        or   esi,0x40000000
        push  ebx
        mov  ecx,edi
        mov  DWORD PTR [ebx+0x20],0x0
        mov  DWORD PTR [ebx+0x35c],esi
        call FUN_00449870
        mov  edi,DWORD PTR ds:0x491c10
        lea  eax,[esp+0x28]
        mov  edx,edi
        call FUN_004489d0
        mov  edx,DWORD PTR [esp+0x28]
        push  edx
        lea  esi,[esp+0x1c]
        mov  edx,edi
        call FUN_004492f0
        mov  DWORD PTR [esp+0x28],0x20
        jmp loc_00426DA0
        nop
    loc_00426DA0:
        mov  eax,ds:0x4776f0
        mov  ecx,DWORD PTR [eax+0x3e0b50]
        mov  esi,edi
        mov  DWORD PTR [esp+0x10],ecx
        call FUN_00449950
        mov  ecx,DWORD PTR [esp+0x10]
        mov  ebx,eax
        mov  edi,DWORD PTR [ebx+0x35c]
        push  0x163
        or   edi,0x40000000
        push  ebx
        mov  DWORD PTR [ebx+0x20],0x0
        mov  DWORD PTR [ebx+0x35c],edi
        call FUN_00449870
        mov  edi,DWORD PTR ds:0x491c10
        lea  eax,[esp+0x14]
        mov  edx,edi
        call FUN_004489d0
        mov  edx,DWORD PTR [esp+0x14]
        push  edx
        lea  esi,[esp+0x1c]
        mov  edx,edi
        call FUN_004492f0
        dec  DWORD PTR [esp+0x28]
        jne loc_00426DA0
        mov  eax,DWORD PTR [ebp+0x484]
        xor  esi,esi
        test  al,0x1
        mov  ebx,0x476f78
        jne loc_00426E3D
        or   eax,0x1
        mov  DWORD PTR [ebp+0x478],esi
        mov  DWORD PTR [ebp+0x474],0xfff0bdc1
        mov  DWORD PTR [ebp+0x47c],esi
        mov  DWORD PTR [ebp+0x480],ebx
        mov  DWORD PTR [ebp+0x484],eax
    loc_00426E3D:
        mov  eax,ds:0x477810
        cmp  eax,esi
        mov  DWORD PTR [ebp+0x478],esi
        mov  DWORD PTR [ebp+0x47c],esi
        mov  DWORD PTR [ebp+0x474],0xffffffff
        je loc_00426E76
        mov  ecx,DWORD PTR [eax+0x58]
        test  ch,0x2
        jne loc_00426E76
        push  esi
        mov  edi,0x4
        mov  ecx,0x492590
        call FUN_0043dc90
        xor  esi,esi
    loc_00426E76:
        mov  eax,DWORD PTR [ebp+0x431c]
        test  al,0x1
        jne loc_00426EA5
        or   eax,0x1
        mov  DWORD PTR [ebp+0x4310],esi
        mov  DWORD PTR [ebp+0x430c],0xfff0bdc1
        mov  DWORD PTR [ebp+0x4314],esi
        mov  DWORD PTR [ebp+0x4318],ebx
        mov  DWORD PTR [ebp+0x431c],eax
    loc_00426EA5:
        mov  DWORD PTR [ebp+0x4310],0x6
        mov  DWORD PTR [ebp+0x4314],0x40c00000
        mov  DWORD PTR [ebp+0x430c],0x5
        mov  ecx,DWORD PTR [ebp+0x10]
        lea  eax,[ebp+0x14]
        xor  ebx,ebx
        call FUN_0043e710
        mov  eax,ds:0x4776f4
        cmp  DWORD PTR [eax+0x3738],0x3c
        jl loc_00426F59
        mov  edi,DWORD PTR [eax+0x378c]
        mov  DWORD PTR [eax+0x3790],esi
        mov  ecx,0xfffffffd
        and  edi,ecx
        mov  DWORD PTR [eax+0x378c],edi
        mov  esi,DWORD PTR [eax+0xad4]
        mov  edx,DWORD PTR [eax+0xe80]
        mov  ebp,DWORD PTR [eax+0x15d8]
        mov  ebx,DWORD PTR [eax+0x1984]
        mov  edi,DWORD PTR [eax+0x1d30]
        and  esi,ecx
        and  edx,ecx
        mov  DWORD PTR [eax+0xad4],esi
        mov  esi,DWORD PTR [eax+0x20dc]
        mov  DWORD PTR [eax+0xe80],edx
        mov  edx,DWORD PTR [eax+0x2488]
        and  ebp,ecx
        and  ebx,ecx
        and  edi,ecx
        and  esi,ecx
        and  edx,ecx
        mov  DWORD PTR [eax+0x15d8],ebp
        mov  DWORD PTR [eax+0x1984],ebx
        mov  DWORD PTR [eax+0x1d30],edi
        mov  DWORD PTR [eax+0x20dc],esi
        mov  DWORD PTR [eax+0x2488],edx
    loc_00426F59:
        pop  edi
        pop  esi
        pop  ebp
        pop  ebx
        add  esp,0x14
        ret  0x4
    }
}
