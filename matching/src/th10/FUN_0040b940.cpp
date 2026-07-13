// 0040B940: FUN_0040b940
// Original size: 144 bytes, actual code: 40 instructions
extern "C" void FUN_0040b560(void);
extern "C" void FUN_0040b7b0(void);
extern "C" void operator_new(void);
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_0040b940(void) {
    __asm {
        push  esi
        push  0x28
        call operator_new
        add  esp,0x4
        test  eax,eax
        je loc_0040B97C
        xor  ecx,ecx
        mov  edx,eax
        mov  DWORD PTR [edx],ecx
        mov  DWORD PTR [edx+0x4],ecx
        mov  DWORD PTR [edx+0x8],ecx
        mov  DWORD PTR [edx+0xc],ecx
        mov  DWORD PTR [edx+0x10],ecx
        mov  DWORD PTR [edx+0x14],ecx
        mov  DWORD PTR [edx+0x18],ecx
        mov  DWORD PTR [edx+0x1c],ecx
        mov  DWORD PTR [edx+0x20],ecx
        mov  DWORD PTR [edx+0x24],ecx
        or   DWORD PTR [eax],0x2
        mov  ds:0x477700,eax
        mov  esi,eax
        jmp loc_0040B97E
    loc_0040B97C:
        xor  esi,esi
    loc_0040B97E:
        push  esi
        call FUN_0040b560
        test  eax,eax
        je loc_0040B99F
        test  esi,esi
        je loc_0040B99B
        push  esi
        call FUN_0040b7b0
        push  esi
        call _free
        add  esp,0x4
    loc_0040B99B:
        xor  eax,eax
        pop  esi
        ret
    loc_0040B99F:
        mov  eax,esi
        pop  esi
        ret
    }
}
