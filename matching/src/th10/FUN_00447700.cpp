// 00447700: FUN_00447700
// Original size: 208 bytes, actual code: 51 instructions
extern "C" void FUN_004473c0(void);
extern "C" void FUN_00447810(void);
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_00447700(void) {
    __asm {
        push  ebx
        push  esi
        mov  esi,DWORD PTR [esp+0xc]
        xor  ebx,ebx
        push  edi
        add  esi,0x3ad06c
        nop
    loc_00447710:
        mov  edi,DWORD PTR [esi]
        test  edi,edi
        je loc_00447757
        mov  eax,DWORD PTR [edi+0x128]
        test  eax,eax
        je loc_0044774D
        test  ebx,ebx
        jl loc_0044773F
        cmp  ebx,0x21
        jae loc_0044773F
        call FUN_00447810
        mov  eax,DWORD PTR [esi]
        push  eax
        call _free
        add  esp,0x4
        mov  DWORD PTR [esi],0x0
    loc_0044773F:
        mov  ecx,DWORD PTR [esi]
        mov  DWORD PTR [ecx+0x128],0x0
        jmp loc_00447757
    loc_0044774D:
        mov  eax,DWORD PTR [edi+0x124]
        test  eax,eax
        jne loc_00447768
    loc_00447757:
        inc  ebx
        add  esi,0x4
        cmp  ebx,0x21
        jb loc_00447710
        pop  edi
        pop  esi
        xor  eax,eax
        pop  ebx
        ret  0x4
    loc_00447768:
        mov  eax,DWORD PTR [esp+0x10]
        mov  edx,DWORD PTR [eax+ebx*4+0x3ad06c]
        push  edx
        push  eax
        call FUN_004473c0
        neg  eax
        sbb  eax,eax
        pop  edi
        neg  eax
        pop  esi
        dec  eax
        pop  ebx
        ret  0x4
    }
}
