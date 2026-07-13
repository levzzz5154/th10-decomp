// 0041C800: FUN_0041c800
// Original size: 80 bytes, actual code: 34 instructions

extern "C" __declspec(naked) void FUN_0041c800(void) {
    __asm {
        mov  ecx,DWORD PTR [eax+0x18]
        push  esi
        add  eax,0x440
        mov  edx,ebx
        mov  esi,DWORD PTR [edx]
        mov  DWORD PTR [eax],esi
        mov  esi,DWORD PTR [edx+0x4]
        mov  DWORD PTR [eax+0x4],esi
        mov  edx,DWORD PTR [edx+0x8]
        push  edi
        xor  edi,edi
        test  ecx,ecx
        mov  DWORD PTR [eax+0x8],edx
        je loc_0041C845
        push  ebp
        mov  ebp,DWORD PTR [esp+0x10]
    loc_0041C827:
        cmp  DWORD PTR [ecx+0xc],0x1
        mov  esi,DWORD PTR [ecx+0x8]
        je loc_0041C83E
        mov  edx,DWORD PTR [esp+0x14]
        mov  eax,DWORD PTR [ecx]
        push  edx
        push  ebp
        push  ebx
        call  DWORD PTR [eax+0x1c]
        add  edi,eax
    loc_0041C83E:
        test  esi,esi
        mov  ecx,esi
        jne loc_0041C827
        pop  ebp
    loc_0041C845:
        mov  eax,edi
        pop  edi
        pop  esi
        ret  0x8
    }
}
