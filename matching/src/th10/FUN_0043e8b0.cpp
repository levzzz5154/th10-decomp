// 0043E8B0: FUN_0043e8b0
// Original size: 528 bytes, actual code: 128 instructions
extern "C" void FUN_0043ee30(void);
extern "C" void FUN_0044b360(void);
extern "C" void FUN_0044b4d0(void);
extern "C" void _sprintf(void);
extern "C" void __security_check_cookie(void);

extern "C" __declspec(naked) void FUN_0043e8b0(void) {
    __asm {
        push  esi
        push  edi
        mov  edi,ecx
        mov  ecx,DWORD PTR [edx+0x11c]
        mov  esi,DWORD PTR [ecx+edi*4]
        xor  ecx,ecx
        cmp  esi,ecx
        je loc_0043E9CC
        push  ebp
        cmp  DWORD PTR [edx+0x124],ecx
        jne loc_0043E9CB
        mov  WORD PTR [eax+0x38a],di
        mov  edi,DWORD PTR [eax+0x35c]
        test  edi,0x200
        mov  DWORD PTR [eax+0x308],edx
        je loc_0043E90A
        fld  DWORD PTR [eax+0x3c]
        or   edi,0x8
        fmul  DWORD PTR ds:0x470b60
        xor  edi,0x200
        mov  DWORD PTR [eax+0x35c],edi
        fstp  DWORD PTR [eax+0x3c]
    loc_0043E90A:
        mov  WORD PTR [eax+0x35c],0x7
        mov  DWORD PTR [eax+0x2fc],0xffffffff
        mov  DWORD PTR [eax+0x60],ecx
        mov  DWORD PTR [eax+0x64],ecx
        mov  edi,0xfff0bdc1
        mov  DWORD PTR [eax+0x5c],edi
        mov  DWORD PTR [eax+0xb4],ecx
        mov  DWORD PTR [eax+0x100],ecx
        mov  DWORD PTR [eax+0x12c],ecx
        mov  DWORD PTR [eax+0x178],ecx
        mov  DWORD PTR [eax+0x1b4],ecx
        mov  DWORD PTR [eax+0x200],ecx
        mov  DWORD PTR [eax+0x22c],ecx
        mov  bp,WORD PTR [edx]
        mov  WORD PTR [eax+0x386],bp
        mov  ebp,DWORD PTR [eax+0x35c]
        and  ebp,0xfffff9ff
        mov  DWORD PTR [eax+0x308],edx
        mov  DWORD PTR [eax+0x35c],ebp
        mov  DWORD PTR [eax+0x38c],esi
        mov  DWORD PTR [eax+0x390],esi
        mov  edx,DWORD PTR [eax+0x6c]
        test  dl,0x1
        jne loc_0043E9A1
        or   edx,0x1
        mov  DWORD PTR [eax+0x60],ecx
        mov  DWORD PTR [eax+0x5c],edi
        mov  DWORD PTR [eax+0x64],ecx
        mov  DWORD PTR [eax+0x68],0x476f78
        mov  DWORD PTR [eax+0x6c],edx
    loc_0043E9A1:
        mov  DWORD PTR [eax+0x60],ecx
        mov  DWORD PTR [eax+0x64],ecx
        mov  DWORD PTR [eax+0x5c],0xffffffff
        mov  esi,DWORD PTR [eax+0x35c]
        and  esi,0xfffffffe
        push  eax
        mov  DWORD PTR [eax+0x35c],esi
        call FUN_0043ee30
        mov  eax,ds:0x491c10
        inc  DWORD PTR [eax+0x4c]
    loc_0043E9CB:
        pop  ebp
    loc_0043E9CC:
        pop  edi
        pop  esi
        ret
    }
}
