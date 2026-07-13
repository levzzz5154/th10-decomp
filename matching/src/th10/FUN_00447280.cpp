// 00447280: FUN_00447280
// Original size: 96 bytes, actual code: 29 instructions
extern "C" void FUN_004470c0(void);

extern "C" __declspec(naked) void FUN_00447280(void) {
    __asm {
        mov  eax,DWORD PTR [edx+ecx*4+0x3ad06c]
        test  eax,eax
        jne loc_004472CE
        mov  eax,DWORD PTR [esp+0x4]
        push  esi
        push  eax
        push  ecx
        push  edx
        call FUN_004470c0
        mov  esi,eax
        test  esi,esi
        jne loc_004472A2
        pop  esi
        ret  0x4
    loc_004472A2:
        push  edi
        mov  edi,DWORD PTR ds:0x4660ac
        mov  DWORD PTR [esi+0x124],0x1
    loc_004472B3:
        mov  al,ds:0x491ff4
        test  al,al
        js loc_004472CA
        push  0x1
        call  edi
        mov  eax,DWORD PTR [esi+0x124]
        test  eax,eax
        jne loc_004472B3
    loc_004472CA:
        pop  edi
        mov  eax,esi
        pop  esi
    loc_004472CE:
        ret  0x4
    }
}
