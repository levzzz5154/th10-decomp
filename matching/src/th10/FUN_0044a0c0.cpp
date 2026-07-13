// 0044A0C0: FUN_0044a0c0
// Original size: 208 bytes, actual code: 33 instructions
extern "C" void FUN_0044b810(void);

extern "C" __declspec(naked) void FUN_0044a0c0(void) {
    __asm {
        sub  esp,0x34
        push  esi
        mov  esi,DWORD PTR ds:0x466280
        lea  eax,[esp+0x4]
        push  eax
        push  0x0
        mov  DWORD PTR [esp+0xc],0x34
        mov  DWORD PTR [esp+0x10],0xff
        call  esi
        test  eax,eax
        je loc_0044A10F
        lea  ecx,[esp+0x4]
        push  ecx
        push  0x1
        call  esi
        test  eax,eax
        je loc_0044A10F
        push  0x470580
        mov  ecx,0x474f70
        call FUN_0044b810
        add  esp,0x4
        mov  ax,0x1
        pop  esi
        add  esp,0x34
        ret
    loc_0044A10F:
        push  0x194
        push  0x4918b8
        push  0x0
        call  DWORD PTR ds:0x46627c
        xor  ax,ax
        pop  esi
        add  esp,0x34
        ret
    }
}
