// 0040B480: FUN_0040b480
// Original size: 224 bytes, actual code: 43 instructions
extern "C" void FUN_0044b360(void);
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_0040b480(void) {
    __asm {
        push  ebp
        mov  ebp,DWORD PTR [esp+0x8]
        push  esi
        mov  BYTE PTR ds:0x497c38,0x0
        mov  ecx,eax
        nop
    loc_0040B490:
        mov  dl,BYTE PTR [eax]
        inc  eax
        test  dl,dl
        jne loc_0040B490
        push  edi
        mov  edi,0x497c38
        sub  eax,ecx
        mov  esi,ecx
        dec  edi
    loc_0040B4A2:
        mov  cl,BYTE PTR [edi+0x1]
        inc  edi
        test  cl,cl
        jne loc_0040B4A2
        mov  ecx,eax
        shr  ecx,0x2
        rep movsd
        mov  ecx,eax
        push  0x0
        and  ecx,0x3
        push  0x0
        mov  eax,0x497c38
        rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
        call FUN_0044b360
        mov  esi,eax
        mov  eax,DWORD PTR [ebp+0x14]
        test  eax,eax
        pop  edi
        je loc_0040B4E0
        push  eax
        call _free
        add  esp,0x4
        mov  DWORD PTR [ebp+0x14],0x0
    loc_0040B4E0:
        mov  DWORD PTR [ebp+0x14],esi
        mov  eax,esi
        pop  esi
        pop  ebp
        ret  0x4
    }
}
