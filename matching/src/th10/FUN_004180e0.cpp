// 004180E0: FUN_004180e0
// Original size: 112 bytes, actual code: 37 instructions
extern "C" void FUN_00418c40(void);
extern "C" void FUN_00420ea0(void);
extern "C" void operator_new(void);

extern "C" __declspec(naked) void FUN_004180e0(void) {
    __asm {
        push  esi
        push  edi
        push  0x60
        call operator_new
        mov  esi,eax
        add  esp,0x4
        test  esi,esi
        je loc_00418110
        mov  eax,DWORD PTR [esi+0x20]
        and  eax,0xfffffffe
        lea  edx,[esi+0x24]
        mov  DWORD PTR [esi+0x20],eax
        call FUN_00418c40
        mov  ecx,0x18
        xor  eax,eax
        mov  edi,esi
        rep stosd
        jmp loc_00418112
    loc_00418110:
        xor  esi,esi
    loc_00418112:
        mov  eax,ds:0x491c30
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0x14]
        mov  edx,DWORD PTR [esp+0xc]
        mov  DWORD PTR [esi+0x5c],edx
        mov  edx,DWORD PTR [esi+0x58]
        push  0x0
        or   edx,0x4
        push  0x417c70
        mov  edi,0x491c28
        mov  DWORD PTR ds:0x477810,esi
        mov  DWORD PTR [esi+0x58],edx
        call FUN_00420ea0
        pop  edi
        mov  eax,esi
        pop  esi
        ret  0x4
    }
}
