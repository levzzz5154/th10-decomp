// 0040B7B0: FUN_0040b7b0
// Original size: 400 bytes, actual code: 107 instructions
extern "C" void FUN_0040b3a0(void);
extern "C" void FUN_00447810(void);
extern "C" void FUN_00447f70(void);
extern "C" void FUN_00449f60(void);
extern "C" void _free(void);
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_0040b7b0(void) {
    __asm {
        mov  eax,DWORD PTR [esp+0x4]
        push  ebx
        mov  ebx,DWORD PTR ds:0x4660b0
        push  ebp
        mov  ebp,DWORD PTR ds:0x4660b4
        push  esi
        mov  esi,DWORD PTR [eax+0x8]
        test  esi,esi
        push  edi
        mov  edi,DWORD PTR ds:0x491be4
        je loc_0040B7F4
        push  0x492274
        call  ebx
        inc  BYTE PTR ds:0x49231c
        mov  ecx,esi
        mov  edx,edi
        call FUN_00449f60
        push  0x492274
        call  ebp
        dec  BYTE PTR ds:0x49231c
    loc_0040B7F4:
        mov  ecx,DWORD PTR [esp+0x14]
        mov  esi,DWORD PTR [ecx+0xc]
        test  esi,esi
        mov  edi,DWORD PTR ds:0x491be4
        je loc_0040B828
        push  0x492274
        call  ebx
        inc  BYTE PTR ds:0x49231c
        mov  ecx,esi
        mov  edx,edi
        call FUN_00449f60
        push  0x492274
        call  ebp
        dec  BYTE PTR ds:0x49231c
    loc_0040B828:
        mov  edi,DWORD PTR ds:0x491c10
        xor  esi,esi
        call FUN_00447f70
        mov  ebp,DWORD PTR [esp+0x14]
        mov  esi,DWORD PTR [ebp+0x18]
        xor  ebx,ebx
        cmp  esi,ebx
        je loc_0040B852
        mov  eax,esi
        call FUN_0040b3a0
        push  esi
        call _free
        add  esp,0x4
    loc_0040B852:
        mov  esi,DWORD PTR ds:0x491c10
        add  esi,0x3ad0e0
        mov  DWORD PTR [ebp+0x18],ebx
        mov  edi,DWORD PTR [esi]
        cmp  edi,ebx
        je loc_0040B879
        call FUN_00447810
        mov  edx,DWORD PTR [esi]
        push  edx
        call _free
        add  esp,0x4
        mov  DWORD PTR [esi],ebx
    loc_0040B879:
        mov  esi,DWORD PTR ds:0x491c10
        mov  edi,DWORD PTR [esi+0x3ad0e4]
        add  esi,0x3ad0e4
        cmp  edi,ebx
        je loc_0040B8A1
        call FUN_00447810
        mov  eax,DWORD PTR [esi]
        push  eax
        call _free
        add  esp,0x4
        mov  DWORD PTR [esi],ebx
    loc_0040B8A1:
        mov  esi,DWORD PTR ds:0x491c10
        mov  edi,DWORD PTR [esi+0x3ad0e8]
        add  esi,0x3ad0e8
        cmp  edi,ebx
        je loc_0040B8C9
        call FUN_00447810
        mov  ecx,DWORD PTR [esi]
        push  ecx
        call _free
        add  esp,0x4
        mov  DWORD PTR [esi],ebx
    loc_0040B8C9:
        mov  esi,DWORD PTR ds:0x491c10
        mov  edi,DWORD PTR [esi+0x3ad0ec]
        add  esi,0x3ad0ec
        cmp  edi,ebx
        je loc_0040B8F1
        call FUN_00447810
        mov  edx,DWORD PTR [esi]
        push  edx
        call _free
        add  esp,0x4
        mov  DWORD PTR [esi],ebx
    loc_0040B8F1:
        mov  eax,DWORD PTR [ebp+0x14]
        cmp  eax,ebx
        je loc_0040B904
        push  eax
        call _free
        add  esp,0x4
        mov  DWORD PTR [ebp+0x14],ebx
    loc_0040B904:
        pop  edi
        pop  esi
        mov  DWORD PTR [ebp+0x14],ebx
        pop  ebp
        mov  DWORD PTR ds:0x477700,ebx
        mov  DWORD PTR ds:0x4918a4,ebx
        pop  ebx
        ret  0x4
    }
}
