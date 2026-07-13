// 0040AC20: FUN_0040ac20
// Original size: 112 bytes, actual code: 38 instructions

extern "C" __declspec(naked) void FUN_0040ac20(void) {
    __asm {
        push  ecx
        xor  eax,eax
        mov  ax,WORD PTR [ecx+0x2c]
        push  ebx
        push  esi
        mov  WORD PTR [ecx+0x4],0x0
        mov  edx,0x10
        mov  ebx,0x1
        mov  DWORD PTR [esp+0x8],eax
        lea  eax,[ecx+0x38]
    loc_0040AC40:
        test  BYTE PTR [esp+0x8],bl
        je loc_0040AC5A
        inc  WORD PTR [eax]
        cmp  WORD PTR [eax],0x1a
        jb loc_0040AC5F
        or   WORD PTR [ecx+0x30],bx
        add  WORD PTR [eax],0xfff8
        jmp loc_0040AC5F
    loc_0040AC5A:
        mov  WORD PTR [eax],0x0
    loc_0040AC5F:
        shr  WORD PTR [esp+0x8],1
        add  eax,0x2
        dec  edx
        jne loc_0040AC40
        xor  eax,eax
        mov  ax,WORD PTR [ecx+0x2c]
        xor  edx,edx
        mov  dx,WORD PTR [ecx+0x2e]
        xor  dx,ax
        mov  esi,edx
        and  esi,eax
        not  eax
        mov  WORD PTR [ecx+0x32],si
        and  eax,edx
        pop  esi
        mov  WORD PTR [ecx+0x34],ax
        pop  ebx
        pop  ecx
        ret
    }
}
