// 0044B010: FUN_0044b010
// Original size: 112 bytes, actual code: 37 instructions

extern "C" __declspec(naked) void FUN_0044b010(void) {
    __asm {
        push  edi
        xor  eax,eax
        mov  ecx,0x40
        mov  edi,edx
        rep stosd
        mov  eax,ds:0x4924fc
        test  eax,eax
        pop  edi
        je loc_0044B037
        mov  eax,ds:0x491ff4
        test  ah,0x2
        push  edx
        jne loc_0044B03A
        call  DWORD PTR ds:0x466208
    loc_0044B037:
        xor  eax,eax
        ret
    loc_0044B03A:
        mov  eax,ds:0x491c38
        mov  ecx,DWORD PTR [eax]
        push  0x100
        push  eax
        call  DWORD PTR [ecx+0x24]
        cmp  eax,0x8007001e
        jne loc_0044B062
        mov  eax,ds:0x491c38
        mov  edx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [edx+0x1c]
        mov  eax,0x1
        ret
    loc_0044B062:
        test  eax,eax
        je loc_0044B071
        mov  eax,ds:0x491c38
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0x1c]
    loc_0044B071:
        mov  eax,0x1
        ret
    }
}
