// 0043E710: FUN_0043e710
// Original size: 208 bytes, actual code: 57 instructions
extern "C" void FUN_00401de0(void);
extern "C" void FUN_0043ee30(void);

extern "C" __declspec(naked) void FUN_0043e710(void) {
    __asm {
        push  ebp
        push  esi
        mov  esi,ecx
        push  edi
        mov  edi,eax
        mov  eax,DWORD PTR [esi+0x11c]
        mov  ecx,DWORD PTR [eax+ebx*4]
        xor  ebp,ebp
        cmp  ecx,ebp
        je loc_0043E7CE
        cmp  DWORD PTR [esi+0x124],ebp
        jne loc_0043E7CE
        mov  edx,edi
        call FUN_00401de0
        mov  edx,DWORD PTR [edi+0x35c]
        mov  WORD PTR [edi+0x38a],bx
        mov  cx,WORD PTR [esi]
        and  edx,0xfffff9ff
        mov  WORD PTR [edi+0x386],cx
        mov  DWORD PTR [edi+0x308],esi
        mov  DWORD PTR [edi+0x35c],edx
        mov  edx,DWORD PTR [esi+0x11c]
        mov  eax,DWORD PTR [edx+ebx*4]
        mov  DWORD PTR [edi+0x38c],eax
        mov  DWORD PTR [edi+0x390],eax
        mov  eax,DWORD PTR [edi+0x6c]
        test  al,0x1
        jne loc_0043E79C
        or   eax,0x1
        mov  DWORD PTR [edi+0x60],ebp
        mov  DWORD PTR [edi+0x5c],0xfff0bdc1
        mov  DWORD PTR [edi+0x64],ebp
        mov  DWORD PTR [edi+0x68],0x476f78
        mov  DWORD PTR [edi+0x6c],eax
    loc_0043E79C:
        mov  DWORD PTR [edi+0x60],ebp
        mov  DWORD PTR [edi+0x64],ebp
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
        pop  ebp
        ret
    loc_0043E7CE:
        mov  ecx,0xeb
        xor  eax,eax
        rep stosd
        pop  edi
        pop  esi
        pop  ebp
        ret
    }
}
