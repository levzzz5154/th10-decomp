// 00442F50: FUN_00442f50
// Original size: 144 bytes, actual code: 40 instructions

extern "C" __declspec(naked) void FUN_00442f50(void) {
    __asm {
        mov  eax,DWORD PTR [esi+0x3adac8]
        test  eax,eax
        je loc_00442FD4
        mov  eax,ds:0x491c30
        mov  ecx,DWORD PTR [eax]
        push  0x0
        push  0x6
        push  0x0
        push  eax
        call  DWORD PTR [ecx+0x10c]
        mov  eax,ds:0x491c30
        mov  edx,DWORD PTR [eax]
        push  0x0
        push  0x3
        push  0x0
        push  eax
        call  DWORD PTR [edx+0x10c]
        mov  eax,ds:0x491c30
        mov  ecx,DWORD PTR [eax]
        push  0x144
        push  eax
        call  DWORD PTR [ecx+0x164]
        mov  ecx,DWORD PTR [esi+0x72dad0]
        mov  eax,ds:0x491c30
        mov  edx,DWORD PTR [eax]
        push  0x1c
        push  ecx
        mov  ecx,DWORD PTR [esi+0x3adac8]
        shl  ecx,1
        push  ecx
        push  0x4
        push  eax
        call  DWORD PTR [edx+0x14c]
        mov  eax,DWORD PTR [esi+0x58]
        mov  edx,DWORD PTR [esi+0x72dacc]
        inc  eax
        mov  DWORD PTR [esi+0x72dad0],edx
        mov  DWORD PTR [esi+0x3adac8],0x0
        mov  DWORD PTR [esi+0x58],eax
    loc_00442FD4:
        ret
    }
}
