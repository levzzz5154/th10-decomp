// 0040B110: FUN_0040b110
// Original size: 320 bytes, actual code: 48 instructions
extern "C" void FUN_004489d0(void);
extern "C" void FUN_004491c0(void);
extern "C" void FUN_00449870(void);
extern "C" void FUN_00449950(void);

extern "C" __declspec(naked) void FUN_0040b110(void) {
    __asm {
        push  ebx
        push  ebp
        push  esi
        mov  esi,DWORD PTR ds:0x491c10
        shl  eax,0x4
        add  eax,0x474430
        push  edi
        mov  edi,eax
        movsx ebp,WORD PTR [edi]
        call FUN_00449950
        mov  ecx,DWORD PTR [esp+0x18]
        mov  ebx,eax
        mov  eax,DWORD PTR [ebx+0x35c]
        push  ebp
        or   eax,0x40000000
        push  ebx
        mov  DWORD PTR [ebx+0x20],0xf
        mov  DWORD PTR [ebx+0x35c],eax
        call FUN_00449870
        mov  esi,DWORD PTR ds:0x491c10
        lea  eax,[esp+0x18]
        mov  edx,esi
        call FUN_004489d0
        mov  ebx,DWORD PTR [esp+0x18]
        push  ebx
        mov  edx,esi
        call FUN_004491c0
        mov  esi,eax
        test  esi,esi
        jne loc_0040B176
        xor  ebx,ebx
    loc_0040B176:
        mov  eax,DWORD PTR [edi+0x4]
        test  eax,eax
        je loc_0040B185
        mov  edx,DWORD PTR [esp+0x1c]
        mov  ecx,esi
        call  eax
    loc_0040B185:
        mov  eax,DWORD PTR [edi+0x8]
        mov  DWORD PTR [esi+0x398],eax
        mov  ecx,DWORD PTR [edi+0xc]
        mov  eax,DWORD PTR [esp+0x14]
        pop  edi
        mov  DWORD PTR [esi+0x39c],ecx
        pop  esi
        pop  ebp
        mov  DWORD PTR [eax],ebx
        pop  ebx
        ret  0xc
    }
}
