// 00414370: FUN_00414370
// Original size: 512 bytes, actual code: 134 instructions
extern "C" void FUN_004136c0(void);
extern "C" void FUN_00447810(void);
extern "C" void FUN_004492a0(void);
extern "C" void FUN_004493e0(void);
extern "C" void _free(void);
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_00414370(void) {
    __asm {
        mov  al,ds:0x474ca0
        push  ebx
        push  ebp
        mov  ebp,DWORD PTR [esp+0xc]
        push  esi
        xor  ebx,ebx
        test  al,0x9
        push  edi
        jne loc_004143AD
        mov  esi,DWORD PTR ds:0x491c10
        mov  edi,DWORD PTR [esi+0x3ad0dc]
        add  esi,0x3ad0dc
        cmp  edi,ebx
        je loc_004143BD
        call FUN_00447810
        mov  eax,DWORD PTR [esi]
        push  eax
        call _free
        add  esp,0x4
        mov  DWORD PTR [esi],ebx
        jmp loc_004143BD
    loc_004143AD:
        mov  edx,DWORD PTR [ebp+0x9e80]
        mov  eax,ds:0x491c10
        call FUN_004493e0
    loc_004143BD:
        mov  esi,DWORD PTR [ebp+0x9eb8]
        cmp  esi,ebx
        mov  DWORD PTR [ebp+0x9e80],ebx
        je loc_004143E1
        call FUN_004136c0
        push  esi
        call _free
        add  esp,0x4
        mov  DWORD PTR [ebp+0x9eb8],ebx
    loc_004143E1:
        test  BYTE PTR ds:0x474ca0,0x9
        jne loc_00414411
        mov  eax,DWORD PTR [ebp+0x9ebc]
        cmp  eax,ebx
        je loc_00414403
        push  eax
        call _free
        add  esp,0x4
        mov  DWORD PTR [ebp+0x9ebc],ebx
    loc_00414403:
        mov  DWORD PTR [ebp+0x9ebc],ebx
        mov  DWORD PTR ds:0x491be8,ebx
        jmp loc_0041441D
    loc_00414411:
        mov  ecx,DWORD PTR [ebp+0x9ebc]
        mov  DWORD PTR ds:0x491be8,ecx
    loc_0041441D:
        mov  eax,DWORD PTR [ebp+0x8]
        cmp  eax,ebx
        je loc_00414428
        and  DWORD PTR [eax+0x4],0xfffffffd
    loc_00414428:
        mov  edx,DWORD PTR [ebp+0x9e14]
        push  edx
        mov  edx,DWORD PTR ds:0x491c10
        call FUN_004492a0
        mov  esi,DWORD PTR ds:0x491c10
        mov  DWORD PTR [ebp+0x9e14],ebx
        mov  eax,DWORD PTR [ebp+0x9e18]
        push  eax
        mov  edx,esi
        call FUN_004492a0
        mov  DWORD PTR [ebp+0x9e18],ebx
        mov  ecx,DWORD PTR [ebp+0x9e24]
        push  ecx
        mov  edx,esi
        call FUN_004492a0
        xor  edx,edx
        mov  DWORD PTR [ebp+0x9e24],ebx
        mov  DWORD PTR [ebp+0x9e28],edx
        mov  DWORD PTR [ebp+0x9e2c],edx
        mov  DWORD PTR [ebp+0x9e30],edx
        mov  DWORD PTR [ebp+0x9e34],edx
        mov  DWORD PTR [ebp+0x9e38],edx
        mov  DWORD PTR [ebp+0x9e3c],edx
        mov  DWORD PTR [ebp+0x9e40],edx
        mov  DWORD PTR [ebp+0x9e44],edx
        mov  DWORD PTR [ebp+0x9e48],edx
        mov  DWORD PTR [ebp+0x9e4c],edx
        lea  edx,[ebp+0x9df4]
        mov  DWORD PTR [esp+0x14],0x8
        lea  ebx,[ebx+0x0]
    loc_004144C0:
        mov  ecx,DWORD PTR [edx]
        cmp  ecx,ebx
        je loc_0041452F
        mov  eax,DWORD PTR [esi+0x72dad4]
        cmp  eax,ebx
        je loc_004144DD
    loc_004144D0:
        mov  edi,DWORD PTR [eax]
        cmp  DWORD PTR [edi],ecx
        je loc_004144F6
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_004144D0
    loc_004144DD:
        mov  eax,DWORD PTR [esi+0x72dadc]
        cmp  eax,ebx
        je loc_0041452F
    loc_004144E7:
        mov  edi,DWORD PTR [eax]
        cmp  DWORD PTR [edi],ecx
        je loc_004144F6
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_004144E7
        jmp loc_0041452F
    loc_004144F6:
        mov  eax,DWORD PTR [eax]
        cmp  eax,ebx
        je loc_0041452F
        mov  ecx,DWORD PTR [eax+0x35c]
        mov  edi,0x4000000
        or   ecx,edi
        mov  DWORD PTR [eax+0x35c],ecx
        cmp  DWORD PTR [eax+0x18],ebx
        jne loc_0041452F
        mov  eax,DWORD PTR [eax+0x14]
        cmp  eax,ebx
        je loc_0041452F
        jmp loc_00414520
        nop
    loc_00414520:
        mov  ecx,DWORD PTR [eax]
        or   DWORD PTR [ecx+0x35c],edi
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_00414520
    loc_0041452F:
        mov  eax,DWORD PTR [esp+0x14]
        mov  DWORD PTR [edx],ebx
        add  edx,0x4
        dec  eax
        mov  DWORD PTR [esp+0x14],eax
        jne loc_004144C0
        pop  edi
        pop  esi
        mov  DWORD PTR [ebp+0x9e90],ebx
        pop  ebp
        pop  ebx
        ret  0x4
    }
}
