// 00436330: FUN_00436330
// Original size: 112 bytes, actual code: 14 instructions

extern "C" __declspec(naked) void FUN_00436330(void) {
    __asm {
        lea  eax,[eax+eax*2]
        mov  eax,DWORD PTR [eax*4+0x47785c]
        lea  ecx,[eax+eax*2]
        mov  ecx,DWORD PTR [ecx*4+0x477860]
        test  ecx,ecx
        je loc_00436360
        jmp loc_00436350
        lea  ebx,[ebx+0x0]
    loc_00436350:
        mov  eax,ecx
        lea  edx,[eax+eax*2]
        mov  ecx,DWORD PTR [edx*4+0x477860]
        test  ecx,ecx
        jne loc_00436350
    loc_00436360:
        ret
    }
}
