// 0041FD00: FUN_0041fd00
// Original size: 208 bytes, actual code: 29 instructions
extern "C" void FUN_0041f850(void);
extern "C" void FUN_0041fac0(void);
extern "C" void FUN_0041fb50(void);
extern "C" void operator_new(void);
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_0041fd00(void) {
    __asm {
        push  ebx
        push  0x3f0
        call operator_new
        add  esp,0x4
        test  eax,eax
        je loc_0041FD1F
        push  esi
        mov  esi,eax
        call FUN_0041f850
        mov  ebx,eax
        pop  esi
        jmp loc_0041FD21
    loc_0041FD1F:
        xor  ebx,ebx
    loc_0041FD21:
        call FUN_0041fac0
        test  eax,eax
        je loc_0041FD41
        test  ebx,ebx
        je loc_0041FD3D
        push  ebx
        call FUN_0041fb50
        push  ebx
        call _free
        add  esp,0x4
    loc_0041FD3D:
        xor  eax,eax
        pop  ebx
        ret
    loc_0041FD41:
        mov  eax,ebx
        pop  ebx
        ret
    }
}
