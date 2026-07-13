// 0043ED00: FUN_0043ed00
// Original size: 160 bytes, actual code: 53 instructions
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_0043ed00(void) {
    __asm {
        mov  eax,0x1
        shl  eax,cl
        movzx ecx,WORD PTR [esp+0x4]
        test  ecx,eax
        je loc_0043ED67
        fld  DWORD PTR [edi]
        call FUN_00463b2c
        add  eax,0xffffd8ec
        cmp  eax,0xb
        ja loc_0043ED67
        jmp  DWORD PTR [eax*4+0x43ed6c]
        lea  eax,[esi+0x31c]
        ret  0x4
        lea  eax,[esi+0x320]
        ret  0x4
        lea  eax,[esi+0x324]
        ret  0x4
        lea  eax,[esi+0x328]
        ret  0x4
        lea  eax,[esi+0x334]
        ret  0x4
        lea  eax,[esi+0x338]
        ret  0x4
        lea  eax,[esi+0x33c]
        ret  0x4
    loc_0043ED67:
        mov  eax,edi
        ret  0x4
        sub  ch,ch
        inc  ebx
        add  BYTE PTR [ecx],dh
        in   eax,dx
        inc  ebx
        add  BYTE PTR [edx],bh
        in   eax,dx
        inc  ebx
        add  BYTE PTR [ebx-0x13],al
        inc  ebx
        add  BYTE PTR [edi-0x13],ah
        inc  ebx
        add  BYTE PTR [edi-0x13],ah
        inc  ebx
        add  BYTE PTR [edi-0x13],ah
        inc  ebx
        add  BYTE PTR [edi-0x13],ah
        inc  ebx
        add  BYTE PTR [edi-0x13],ah
        inc  ebx
        add  BYTE PTR [ebp+ebp*8+0x43],cl
        add  BYTE PTR [ebp-0x13],dl
        inc  ebx
        add  BYTE PTR [esi-0x13],bl
        inc  ebx
        add  ah,cl
    }
}
