// 0041C850: FUN_0041c850
// Original size: 1920 bytes, actual code: 18 instructions

extern "C" __declspec(naked) void FUN_0041c850(void) {
    __asm {
        mov  ecx,DWORD PTR [eax+0x18]
        test  ecx,ecx
        je loc_0041C876
        push  esi
        jmp loc_0041C860
        lea  ebx,[ebx+0x0]
    loc_0041C860:
        cmp  DWORD PTR [ecx+0xc],0x1
        mov  esi,DWORD PTR [ecx+0x8]
        je loc_0041C86F
        mov  edx,DWORD PTR [ecx]
        push  ebx
        call  DWORD PTR [edx+0x14]
    loc_0041C86F:
        test  esi,esi
        mov  ecx,esi
        jne loc_0041C860
        pop  esi
    loc_0041C876:
        mov  eax,0x1
        ret
    }
}
