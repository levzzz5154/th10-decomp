// 00448AC0: FUN_00448ac0
// Original size: 128 bytes, actual code: 36 instructions

extern "C" __declspec(naked) void FUN_00448ac0(void) {
    __asm {
        lea  ecx,[ebx+0x4]
        push  esi
        mov  DWORD PTR [ecx],ebx
        mov  DWORD PTR [ecx+0x4],0x0
        mov  DWORD PTR [ecx+0x8],0x0
        mov  esi,DWORD PTR [edx+0x72dadc]
        test  esi,esi
        jne loc_00448AE6
        mov  DWORD PTR [edx+0x72dadc],ecx
        jmp loc_00448B04
    loc_00448AE6:
        mov  esi,DWORD PTR [edx+0x72dae0]
        push  edi
        mov  edi,DWORD PTR [esi+0x4]
        test  edi,edi
        je loc_00448AFD
        mov  DWORD PTR [ecx+0x4],edi
        mov  edi,DWORD PTR [esi+0x4]
        mov  DWORD PTR [edi+0x8],ecx
    loc_00448AFD:
        mov  DWORD PTR [esi+0x4],ecx
        mov  DWORD PTR [ecx+0x8],esi
        pop  edi
    loc_00448B04:
        mov  DWORD PTR [edx+0x72dae0],ecx
        mov  esi,DWORD PTR [edx+0x732454]
        inc  esi
        mov  ecx,esi
        test  ecx,ecx
        mov  DWORD PTR [edx+0x732454],esi
        pop  esi
        jne loc_00448B25
        inc  ecx
        mov  DWORD PTR [edx+0x732454],ecx
    loc_00448B25:
        mov  ecx,DWORD PTR [edx+0x732454]
        mov  DWORD PTR [ebx],ecx
        mov  edx,DWORD PTR [edx+0x732454]
        mov  DWORD PTR [eax],edx
        ret
    }
}
