// 00448980: FUN_00448980
// Original size: 80 bytes, actual code: 21 instructions
extern "C" void FUN_004451c0(void);

extern "C" __declspec(naked) void FUN_00448980(void) {
    __asm {
        imul  eax,eax,0x3ac
        push  esi
        mov  esi,DWORD PTR [eax+edi*1+0x72db00]
        test  esi,esi
        je loc_004489BC
    loc_00448992:
        test  DWORD PTR [esi+0x35c],0x4000000
        jne loc_004489B5
        mov  eax,DWORD PTR [esi+0x39c]
        test  eax,eax
        je loc_004489AC
        mov  ecx,esi
        call  eax
    loc_004489AC:
        mov  eax,esi
        mov  ecx,edi
        call FUN_004451c0
    loc_004489B5:
        mov  esi,DWORD PTR [esi+0x1c]
        test  esi,esi
        jne loc_00448992
    loc_004489BC:
        mov  eax,0x1
        pop  esi
        ret
    }
}
