// 00448900: FUN_00448900
// Original size: 128 bytes, actual code: 44 instructions
extern "C" void FUN_0043ee30(void);
extern "C" void FUN_00448bb0(void);

extern "C" __declspec(naked) void FUN_00448900(void) {
    __asm {
        push  ebp
        push  edi
        mov  edi,eax
        mov  eax,DWORD PTR [edi+0x72dadc]
        xor  ecx,ecx
        cmp  eax,ecx
        mov  DWORD PTR [edi+0x7320c4],ecx
        lea  ebp,[edi+0x7320a8]
        mov  DWORD PTR [edi+0x64],ecx
        je loc_00448973
        push  ebx
        push  esi
    loc_00448921:
        mov  esi,DWORD PTR [eax]
        mov  ebx,DWORD PTR [eax+0x4]
        test  DWORD PTR [esi+0x35c],0x4000000
        je loc_00448939
        call FUN_00448bb0
        jmp loc_00448964
    loc_00448939:
        mov  eax,DWORD PTR [esi+0x398]
        test  eax,eax
        je loc_00448947
        mov  ecx,esi
        call  eax
    loc_00448947:
        push  esi
        call FUN_0043ee30
        test  eax,eax
        je loc_00448958
        call FUN_00448bb0
        jmp loc_00448964
    loc_00448958:
        mov  DWORD PTR [ebp+0x1c],esi
        mov  ebp,esi
        mov  DWORD PTR [esi+0x1c],0x0
    loc_00448964:
        mov  edx,DWORD PTR [edi+0x64]
        inc  edx
        test  ebx,ebx
        mov  DWORD PTR [edi+0x64],edx
        mov  eax,ebx
        jne loc_00448921
        pop  esi
        pop  ebx
    loc_00448973:
        pop  edi
        mov  eax,0x1
        pop  ebp
        ret
    }
}
