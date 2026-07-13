// 0043BC40: FUN_0043bc40
// Original size: 144 bytes, actual code: 51 instructions

extern "C" __declspec(naked) void FUN_0043bc40(void) {
    __asm {
        mov  eax,ds:0x491c30
        mov  ecx,DWORD PTR [eax]
        push  0x0
        push  0x3f800000
        push  esi
        push  0x3
        push  0x0
        push  0x0
        push  eax
        call  DWORD PTR [ecx+0xac]
        mov  eax,ds:0x491c30
        mov  edx,DWORD PTR [eax]
        push  0x0
        push  0x0
        push  0x0
        push  0x0
        push  eax
        call  DWORD PTR [edx+0x44]
        test  eax,eax
        jge loc_0043BC83
        mov  eax,ds:0x491c30
        mov  ecx,DWORD PTR [eax]
        push  0x491d0c
        push  eax
        call  DWORD PTR [ecx+0x40]
    loc_0043BC83:
        mov  eax,ds:0x491c30
        mov  edx,DWORD PTR [eax]
        push  0x0
        push  0x3f800000
        push  esi
        push  0x3
        push  0x0
        push  0x0
        push  eax
        call  DWORD PTR [edx+0xac]
        mov  eax,ds:0x491c30
        mov  ecx,DWORD PTR [eax]
        push  0x0
        push  0x0
        push  0x0
        push  0x0
        push  eax
        call  DWORD PTR [ecx+0x44]
        test  eax,eax
        jge loc_0043BCC6
        mov  eax,ds:0x491c30
        mov  edx,DWORD PTR [eax]
        push  0x491d0c
        push  eax
        call  DWORD PTR [edx+0x40]
    loc_0043BCC6:
        ret
    }
}
