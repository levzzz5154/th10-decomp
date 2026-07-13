// 004203C0: FUN_004203c0
// Original size: 48 bytes, actual code: 17 instructions

extern "C" __declspec(naked) void FUN_004203c0(void) {
    __asm {
        mov  eax,DWORD PTR [esi+0x4]
        test  eax,eax
        mov  DWORD PTR [esi],0x46f810
        je loc_004203D4
        push  eax
        call  DWORD PTR ds:0x466288
    loc_004203D4:
        mov  eax,DWORD PTR [esi+0x8]
        push  edi
        mov  edi,DWORD PTR ds:0x466274
        push  eax
        call  edi
        mov  ecx,DWORD PTR [esi+0x8]
        push  ecx
        mov  DWORD PTR [esi+0x4],0x0
        call  edi
        pop  edi
        ret
    }
}
