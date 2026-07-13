// 00449E50: FUN_00449e50
// Original size: 128 bytes, actual code: 30 instructions
extern "C" void FUN_00449f60(void);

extern "C" __declspec(naked) void FUN_00449e50(void) {
    __asm {
        mov  eax,DWORD PTR [eax+0x18]
        test  eax,eax
        je loc_00449E9F
        push  ebx
        mov  ebx,DWORD PTR ds:0x4660b0
        push  ebp
        mov  ebp,DWORD PTR ds:0x4660b4
        push  esi
        push  edi
    loc_00449E67:
        mov  esi,DWORD PTR [eax]
        test  esi,esi
        mov  edi,DWORD PTR [eax+0x4]
        je loc_00449E95
        push  0x492274
        call  ebx
        inc  BYTE PTR ds:0x49231c
        mov  edx,DWORD PTR [esp+0x14]
        mov  ecx,esi
        call FUN_00449f60
        push  0x492274
        call  ebp
        dec  BYTE PTR ds:0x49231c
    loc_00449E95:
        test  edi,edi
        mov  eax,edi
        jne loc_00449E67
        pop  edi
        pop  esi
        pop  ebp
        pop  ebx
    loc_00449E9F:
        ret  0x4
    }
}
