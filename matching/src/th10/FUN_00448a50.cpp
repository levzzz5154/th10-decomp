// 00448A50: FUN_00448a50
// Original size: 112 bytes, actual code: 35 instructions

extern "C" __declspec(naked) void FUN_00448a50(void) {
    __asm {
        lea  ecx,[ebx+0x4]
        push  esi
        mov  DWORD PTR [ecx],ebx
        mov  DWORD PTR [ecx+0x4],0x0
        mov  DWORD PTR [ecx+0x8],0x0
        mov  esi,DWORD PTR [edx+0x72dad4]
        test  esi,esi
        jne loc_00448A76
        mov  DWORD PTR [edx+0x72dad8],ecx
        jmp loc_00448A8E
    loc_00448A76:
        push  edi
        mov  edi,DWORD PTR [ecx+0x4]
        test  edi,edi
        je loc_00448A87
        mov  DWORD PTR [esi+0x4],edi
        mov  edi,DWORD PTR [ecx+0x4]
        mov  DWORD PTR [edi+0x8],esi
    loc_00448A87:
        mov  DWORD PTR [ecx+0x4],esi
        mov  DWORD PTR [esi+0x8],ecx
        pop  edi
    loc_00448A8E:
        mov  DWORD PTR [edx+0x72dad4],ecx
        mov  esi,DWORD PTR [edx+0x732454]
        inc  esi
        mov  ecx,esi
        test  ecx,ecx
        mov  DWORD PTR [edx+0x732454],esi
        pop  esi
        jne loc_00448AAF
        inc  ecx
        mov  DWORD PTR [edx+0x732454],ecx
    loc_00448AAF:
        mov  ecx,DWORD PTR [edx+0x732454]
        mov  DWORD PTR [ebx],ecx
        mov  edx,DWORD PTR [edx+0x732454]
        mov  DWORD PTR [eax],edx
        ret
    }
}
