// 00448860: FUN_00448860
// Original size: 160 bytes, actual code: 54 instructions
extern "C" void FUN_0043ee30(void);
extern "C" void FUN_00448bb0(void);

extern "C" __declspec(naked) void FUN_00448860(void) {
    __asm {
        sub  esp,0x50
        push  ebp
        push  edi
        mov  edi,eax
        xor  ebp,ebp
        xor  eax,eax
        lea  ecx,[edi+0x72dae4]
    loc_00448871:
        mov  DWORD PTR [esp+eax*4+0x8],ecx
        mov  DWORD PTR [ecx+0x1c],ebp
        inc  eax
        add  ecx,0x3ac
        cmp  eax,0x13
        jl loc_00448871
        mov  eax,DWORD PTR [edi+0x72dad4]
        cmp  eax,ebp
        je loc_004488EA
        push  ebx
        push  esi
    loc_00448890:
        mov  esi,DWORD PTR [eax]
        mov  ebx,DWORD PTR [eax+0x4]
        test  DWORD PTR [esi+0x35c],0x4000000
        je loc_004488A8
        call FUN_00448bb0
        jmp loc_004488DB
    loc_004488A8:
        mov  eax,DWORD PTR [esi+0x398]
        cmp  eax,ebp
        je loc_004488B6
        mov  ecx,esi
        call  eax
    loc_004488B6:
        push  esi
        call FUN_0043ee30
        test  eax,eax
        je loc_004488C7
        call FUN_00448bb0
        jmp loc_004488DB
    loc_004488C7:
        mov  eax,DWORD PTR [esi+0x20]
        mov  ecx,DWORD PTR [esp+eax*4+0x10]
        mov  DWORD PTR [ecx+0x1c],esi
        mov  edx,DWORD PTR [esi+0x20]
        mov  DWORD PTR [esp+edx*4+0x10],esi
        mov  DWORD PTR [esi+0x1c],ebp
    loc_004488DB:
        mov  edx,DWORD PTR [edi+0x64]
        inc  edx
        cmp  ebx,ebp
        mov  DWORD PTR [edi+0x64],edx
        mov  eax,ebx
        jne loc_00448890
        pop  esi
        pop  ebx
    loc_004488EA:
        pop  edi
        mov  eax,0x1
        pop  ebp
        add  esp,0x50
        ret
    }
}
