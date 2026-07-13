// 0041FDD0: FUN_0041fdd0
// Original size: 432 bytes, actual code: 56 instructions
extern "C" void FUN_004489d0(void);
extern "C" void FUN_00448d50(void);
extern "C" void FUN_00449870(void);
extern "C" void FUN_00449950(void);

extern "C" __declspec(naked) void FUN_0041fdd0(void) {
    __asm {
        sub  esp,0xc
        push  ebp
        mov  ebp,DWORD PTR [esp+0x14]
        cmp  DWORD PTR [ebp+0x3e4],0x1
        push  esi
        push  edi
        jne loc_0041FE3A
        mov  esi,DWORD PTR ds:0x491c10
        mov  edi,DWORD PTR [ebp+0x3e0]
        push  ebx
        call FUN_00449950
        mov  ebx,eax
        mov  esi,DWORD PTR [ebx+0x35c]
        push  0x0
        or   esi,0x40000000
        push  ebx
        mov  ecx,edi
        mov  DWORD PTR [ebx+0x20],0xf
        mov  DWORD PTR [ebx+0x35c],esi
        call FUN_00449870
        mov  edx,DWORD PTR ds:0x491c10
        lea  eax,[esp+0x20]
        call FUN_004489d0
        mov  eax,DWORD PTR [esp+0x20]
        mov  DWORD PTR [ebp+0x3dc],eax
        inc  DWORD PTR [ebp+0x3e4]
        pop  ebx
    loc_0041FE3A:
        cmp  DWORD PTR [ebp+0x3e8],0x1
        jne loc_0041FE91
        mov  eax,ds:0x4776e0
        mov  ecx,DWORD PTR [eax+0x89a4]
        test  ecx,ecx
        lea  esi,[eax+0x89a4]
        mov  DWORD PTR [esp+0xc],0x43f00000
        mov  DWORD PTR [esp+0x10],0x43c40000
        mov  DWORD PTR [esp+0x14],0x0
        jne loc_0041FE8B
        mov  eax,DWORD PTR [eax+0x8994]
        push  0x6
        lea  ecx,[esp+0x20]
        push  ecx
        push  eax
        lea  edi,[esp+0x18]
        call FUN_00448d50
        mov  edx,DWORD PTR [eax]
        mov  DWORD PTR [esi],edx
    loc_0041FE8B:
        inc  DWORD PTR [ebp+0x3e8]
    loc_0041FE91:
        mov  eax,DWORD PTR [ebp+0x3ec]
        pop  edi
        inc  eax
        mov  DWORD PTR [ebp+0x3ec],eax
        pop  esi
        mov  eax,0x1
        pop  ebp
        add  esp,0xc
        ret  0x4
    }
}
