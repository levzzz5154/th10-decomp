// 00404F30: FUN_00404f30
// Original size: 272 bytes, actual code: 45 instructions
extern "C" void FUN_00401de0(void);
extern "C" void FUN_0043e710(void);

extern "C" __declspec(naked) void FUN_00404f30(void) {
    __asm {
        sub  esp,0xc
        push  ebx
        mov  edx,esi
        mov  ebx,eax
        call FUN_00401de0
        mov  DWORD PTR [esp+0x4],0x0
        mov  ecx,DWORD PTR [esp+0x4]
        lea  eax,[esi+0x340]
        mov  DWORD PTR [eax],ecx
        mov  DWORD PTR [esp+0x8],0x0
        mov  edx,DWORD PTR [esp+0x8]
        mov  DWORD PTR [eax+0x4],edx
        mov  DWORD PTR [esp+0xc],0x0
        mov  ecx,DWORD PTR [esp+0xc]
        mov  DWORD PTR [eax+0x8],ecx
        mov  DWORD PTR [esp+0x4],0x0
        mov  eax,DWORD PTR [esp+0x4]
        lea  edx,[esi+0x334]
        mov  DWORD PTR [edx],eax
        mov  DWORD PTR [esp+0x8],0x0
        mov  ecx,DWORD PTR [esp+0x8]
        mov  DWORD PTR [edx+0x4],ecx
        mov  DWORD PTR [esp+0xc],0x0
        mov  eax,DWORD PTR [esp+0xc]
        mov  DWORD PTR [edx+0x8],eax
        mov  DWORD PTR [esp+0x4],0x0
        mov  edx,DWORD PTR [esp+0x4]
        lea  ecx,[esi+0x34c]
        mov  DWORD PTR [ecx],edx
        mov  DWORD PTR [esp+0x8],0x0
        mov  eax,DWORD PTR [esp+0x8]
        mov  DWORD PTR [ecx+0x4],eax
        mov  al,0x10
        mov  DWORD PTR [esp+0xc],0x0
        mov  edx,DWORD PTR [esp+0xc]
        mov  DWORD PTR [ecx+0x8],edx
        mov  ecx,DWORD PTR [esp+0x14]
        mov  BYTE PTR [esi+0x3a1],al
        mov  BYTE PTR [esi+0x3a0],al
        mov  eax,esi
        mov  WORD PTR [esi+0x38a],bx
        call FUN_0043e710
        pop  ebx
        add  esp,0xc
        ret  0x4
    }
}
