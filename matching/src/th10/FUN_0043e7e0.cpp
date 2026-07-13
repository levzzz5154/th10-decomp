// 0043E7E0: FUN_0043e7e0
// Original size: 208 bytes, actual code: 54 instructions
extern "C" void FUN_0043ee30(void);

extern "C" __declspec(naked) void FUN_0043e7e0(void) {
    __asm {
        push  ebx
        push  esi
        mov  esi,DWORD PTR [eax+0x11c]
        mov  ebx,DWORD PTR [esi+ecx*4]
        push  edi
        mov  edi,edx
        xor  edx,edx
        cmp  ebx,edx
        je loc_0043E895
        cmp  DWORD PTR [eax+0x124],edx
        jne loc_0043E895
        mov  WORD PTR [edi+0x38a],cx
        mov  si,WORD PTR [eax]
        mov  WORD PTR [edi+0x386],si
        mov  esi,DWORD PTR [edi+0x35c]
        and  esi,0xfffff9ff
        mov  DWORD PTR [edi+0x308],eax
        mov  DWORD PTR [edi+0x35c],esi
        mov  eax,DWORD PTR [eax+0x11c]
        mov  eax,DWORD PTR [eax+ecx*4]
        mov  DWORD PTR [edi+0x38c],eax
        mov  DWORD PTR [edi+0x390],eax
        mov  eax,DWORD PTR [edi+0x6c]
        test  al,0x1
        jne loc_0043E863
        or   eax,0x1
        mov  DWORD PTR [edi+0x60],edx
        mov  DWORD PTR [edi+0x5c],0xfff0bdc1
        mov  DWORD PTR [edi+0x64],edx
        mov  DWORD PTR [edi+0x68],0x476f78
        mov  DWORD PTR [edi+0x6c],eax
    loc_0043E863:
        mov  DWORD PTR [edi+0x60],edx
        mov  DWORD PTR [edi+0x64],edx
        mov  DWORD PTR [edi+0x5c],0xffffffff
        mov  esi,DWORD PTR [edi+0x35c]
        and  esi,0xfffffffe
        push  edi
        mov  DWORD PTR [edi+0x35c],esi
        call FUN_0043ee30
        mov  eax,ds:0x491c10
        mov  ecx,DWORD PTR [eax+0x4c]
        pop  edi
        inc  ecx
        pop  esi
        mov  DWORD PTR [eax+0x4c],ecx
        pop  ebx
        ret
    loc_0043E895:
        mov  ecx,0xeb
        xor  eax,eax
        rep stosd
        pop  edi
        pop  esi
        pop  ebx
        ret
    }
}
