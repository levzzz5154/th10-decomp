// 0043B7A0: FUN_0043b7a0
// Original size: 304 bytes, actual code: 47 instructions
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_0043b7a0(void) {
    __asm {
        mov  eax,DWORD PTR [edi+0x2d4]
        sub  esp,0x8
        test  eax,eax
        push  ebp
        mov  ebp,DWORD PTR [esp+0x10]
        jne loc_0043B825
        push  ebx
        push  esi
        xor  ebx,ebx
        lea  esi,[edi+0x169]
        nop
    loc_0043B7C0:
        movzx edx,BYTE PTR [esi]
        mov  DWORD PTR [esp+0xc],edx
        mov  al,bl
        sub  al,0x50
        fild  DWORD PTR [esp+0xc]
        movzx ecx,al
        fmul  DWORD PTR [edi+0x2c8]
        mov  DWORD PTR [esp+0x10],ecx
        call FUN_00463b2c
        add  eax,ebp
        jns loc_0043B7E9
        xor  eax,eax
        jmp loc_0043B7F3
    loc_0043B7E9:
        cmp  eax,0x7f
        jle loc_0043B7F3
        mov  eax,0x7f
    loc_0043B7F3:
        mov  ecx,DWORD PTR [edi+0x13c]
        test  ecx,ecx
        je loc_0043B81A
        mov  dl,BYTE PTR [esp+0x10]
        mov  BYTE PTR [esp+0x18],dl
        mov  BYTE PTR [esp+0x1a],al
        mov  BYTE PTR [esp+0x19],0x7
        mov  eax,DWORD PTR [esp+0x18]
        push  eax
        push  ecx
        call  DWORD PTR ds:0x466298
    loc_0043B81A:
        inc  ebx
        add  esi,0x17
        cmp  ebx,0x10
        jl loc_0043B7C0
        pop  esi
        pop  ebx
    loc_0043B825:
        pop  ebp
        add  esp,0x8
        ret  0x4
    }
}
