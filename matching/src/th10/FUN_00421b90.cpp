// 00421B90: FUN_00421b90
// Original size: 192 bytes, actual code: 35 instructions

extern "C" __declspec(naked) void FUN_00421b90(void) {
    __asm {
        sub  esp,0xc
        fld  DWORD PTR [ecx+0x8]
        fmul  DWORD PTR [edx+0x4]
        fld  DWORD PTR [edx+0x8]
        fmul  DWORD PTR [ecx+0x4]
        fsubp st(1),st
        fstp  DWORD PTR [esp]
        fld  DWORD PTR [edx+0x8]
        fmul  DWORD PTR [ecx]
        fld  DWORD PTR [ecx+0x8]
        fmul  DWORD PTR [edx]
        fsubp st(1),st
        fstp  DWORD PTR [esp+0x4]
        fld  DWORD PTR [edx]
        fmul  DWORD PTR [ecx+0x4]
        fld  DWORD PTR [ecx]
        mov  ecx,eax
        fmul  DWORD PTR [edx+0x4]
        mov  edx,DWORD PTR [esp]
        mov  DWORD PTR [ecx],edx
        mov  edx,DWORD PTR [esp+0x4]
        fsubp st(1),st
        mov  DWORD PTR [ecx+0x4],edx
        fstp  DWORD PTR [esp+0x8]
        mov  edx,DWORD PTR [esp+0x8]
        mov  DWORD PTR [ecx+0x8],edx
        add  esp,0xc
        ret
    }
}
