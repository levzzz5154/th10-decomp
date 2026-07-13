// 0040CD20: FUN_0040cd20
// Original size: 384 bytes, actual code: 44 instructions
extern "C" void FUN_0044b360(void);
extern "C" void FUN_00450220(void);

extern "C" __declspec(naked) void FUN_0040cd20(void) {
    __asm {
        mov  eax,DWORD PTR [esp+0x4]
        push  ebx
        push  esi
        mov  ebx,ecx
        push  edi
        mov  BYTE PTR ds:0x497c38,0x0
        mov  ecx,eax
    loc_0040CD32:
        mov  dl,BYTE PTR [eax]
        inc  eax
        test  dl,dl
        jne loc_0040CD32
        mov  edi,0x497c38
        sub  eax,ecx
        mov  esi,ecx
        dec  edi
    loc_0040CD43:
        mov  cl,BYTE PTR [edi+0x1]
        inc  edi
        test  cl,cl
        jne loc_0040CD43
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
        push  eax
        mov  ecx,ebx
        call FUN_00450220
        xor  ecx,ecx
        test  eax,eax
        setge cl
        pop  edi
        pop  esi
        pop  ebx
        dec  ecx
        mov  eax,ecx
        ret  0x4
    }
}
