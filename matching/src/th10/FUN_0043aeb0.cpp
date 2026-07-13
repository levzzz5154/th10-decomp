// 0043AEB0: FUN_0043aeb0
// Original size: 128 bytes, actual code: 37 instructions
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_0043aeb0(void) {
    __asm {
        xor  eax,eax
        lea  ecx,[edx+0x14]
    loc_0043AEB5:
        cmp  DWORD PTR [ecx],esi
        je loc_0043AEC6
        inc  eax
        add  ecx,0x4
        cmp  eax,0x20
        jl loc_0043AEB5
        or   eax,0xffffffff
        ret
    loc_0043AEC6:
        push  0x40
        mov  DWORD PTR [edx+eax*4+0x14],0x0
        mov  eax,DWORD PTR [edx+0x13c]
        push  esi
        push  eax
        call  DWORD PTR ds:0x466284
        mov  eax,DWORD PTR [esi]
        test  eax,eax
        je loc_0043AEF3
        push  eax
        call _free
        add  esp,0x4
        mov  DWORD PTR [esi],0x0
    loc_0043AEF3:
        push  esi
        call _free
        add  esp,0x4
        xor  eax,eax
        ret
    }
}
