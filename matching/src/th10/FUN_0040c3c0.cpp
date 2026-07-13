// 0040C3C0: FUN_0040c3c0
// Original size: 192 bytes, actual code: 53 instructions
extern "C" void FUN_00409e50(void);
extern "C" void FUN_00447280(void);

extern "C" __declspec(naked) void FUN_0040c3c0(void) {
    __asm {
        mov  eax,DWORD PTR [ebx+0x70]
        push  esi
        push  edi
        mov  BYTE PTR ds:0x497c38,0x0
        mov  esi,eax
        mov  edi,edi
    loc_0040C3D0:
        mov  cl,BYTE PTR [eax]
        inc  eax
        test  cl,cl
        jne loc_0040C3D0
        mov  edi,0x497c38
        sub  eax,esi
        dec  edi
        nop
    loc_0040C3E0:
        mov  cl,BYTE PTR [edi+0x1]
        inc  edi
        test  cl,cl
        jne loc_0040C3E0
        mov  edx,DWORD PTR ds:0x491c10
        mov  ecx,eax
        shr  ecx,0x2
        rep movsd
        mov  ecx,eax
        and  ecx,0x3
        rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
        mov  eax,DWORD PTR [ebx+0x54]
        mov  ecx,DWORD PTR [eax+0x4]
        push  0x497c38
        add  ecx,0x1d
        call FUN_00447280
        mov  ecx,DWORD PTR [ebx+0x54]
        mov  edx,DWORD PTR [ecx+0x4]
        mov  esi,DWORD PTR ds:0x4776e0
        mov  DWORD PTR [ebx+edx*4+0x80],eax
        and  DWORD PTR [ebx+0x74],0xfffffffb
        add  esi,0x89a4
        mov  eax,esi
        call FUN_00409e50
        pop  edi
        mov  DWORD PTR [esi],0x0
        xor  eax,eax
        pop  esi
        ret
    }
}
