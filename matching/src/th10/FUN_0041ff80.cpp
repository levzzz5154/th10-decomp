// 0041FF80: FUN_0041ff80
// Original size: 384 bytes, actual code: 39 instructions
extern "C" void FUN_004218d0(void);
extern "C" void FUN_00421e00(void);
extern "C" void FUN_00447700(void);
extern "C" void FUN_0044a5f0(void);

extern "C" __declspec(naked) void FUN_0041ff80(void) {
    __asm {
        push  esi
        mov  esi,ecx
        mov  al,BYTE PTR [esi+0x3cc]
        test  al,al
        jns loc_0041FFA1
        mov  eax,DWORD PTR [esi+0x63c]
        test  eax,eax
        jne loc_0041FFA1
        mov  DWORD PTR ds:0x491fb8,0x3
    loc_0041FFA1:
        mov  eax,0x492590
        call FUN_00421e00
        xor  ecx,ecx
        call FUN_0044a5f0
        mov  eax,ds:0x491c10
        push  eax
        call FUN_00447700
        test  eax,eax
        je loc_0041FFC8
        mov  eax,0x4
        pop  esi
        ret
    loc_0041FFC8:
        mov  eax,DWORD PTR [esi+0x648]
        test  eax,eax
        je loc_0041FFE3
        xor  ecx,ecx
        cmp  eax,0x2
        setne cl
        pop  esi
        dec  ecx
        and  ecx,0x3
        inc  ecx
        mov  eax,ecx
        ret
    loc_0041FFE3:
        mov  eax,esi
        call FUN_004218d0
        cmp  eax,0x1
        jne loc_0041FFEF
    loc_0041FFEF:
        pop  esi
        ret
    }
}
