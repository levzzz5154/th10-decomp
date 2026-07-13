// 0040ACE0: FUN_0040ace0
// Original size: 64 bytes, actual code: 13 instructions

extern "C" __declspec(naked) void FUN_0040ace0(void) {
    __asm {
        xor  edx,edx
        mov  dx,WORD PTR [ecx+0x6]
        and  edx,eax
        test  dx,dx
        jne loc_0040ACFB
        movzx ecx,WORD PTR [ecx+0x4]
        and  ecx,eax
        test  cx,cx
        jne loc_0040ACFB
        xor  eax,eax
        ret
    loc_0040ACFB:
        mov  eax,0x1
        ret
    }
}
