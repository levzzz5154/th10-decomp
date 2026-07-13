// 00436000: FUN_00436000
// Original size: 528 bytes, actual code: 138 instructions

extern "C" __declspec(naked) void FUN_00436000(void) {
    __asm {
        test  edx,edx
        jne loc_00436009
        xor  eax,eax
        ret  0x4
    loc_00436009:
        push  ebx
        push  esi
        mov  esi,DWORD PTR ds:0x48f860
        push  ebp
        xor  ebx,ebx
        push  edi
    loc_00436015:
        mov  edi,esi
        xor  eax,eax
        sub  edi,edx
        jmp loc_00436020
        nop
    loc_00436020:
        lea  ecx,[eax+edx*1]
        lea  ebp,[edi+ecx*1]
        and  ebp,0x1fff
        movzx ebp,BYTE PTR [ebp+0x48f868]
        and  ecx,0x1fff
        movzx ecx,BYTE PTR [ecx+0x48f868]
        sub  ecx,ebp
        jne loc_00436131
        lea  ecx,[eax+esi*1+0x1]
        and  ecx,0x1fff
        movzx ebp,BYTE PTR [ecx+0x48f868]
        lea  ecx,[eax+edx*1+0x1]
        and  ecx,0x1fff
        movzx ecx,BYTE PTR [ecx+0x48f868]
        sub  ecx,ebp
        jne loc_0043611C
        lea  ecx,[eax+esi*1+0x2]
        and  ecx,0x1fff
        movzx ebp,BYTE PTR [ecx+0x48f868]
        lea  ecx,[eax+edx*1+0x2]
        and  ecx,0x1fff
        movzx ecx,BYTE PTR [ecx+0x48f868]
        sub  ecx,ebp
        jne loc_0043611F
        lea  ecx,[eax+esi*1+0x3]
        and  ecx,0x1fff
        movzx ebp,BYTE PTR [ecx+0x48f868]
        lea  ecx,[eax+edx*1+0x3]
        and  ecx,0x1fff
        movzx ecx,BYTE PTR [ecx+0x48f868]
        sub  ecx,ebp
        jne loc_00436124
        lea  ecx,[eax+esi*1+0x4]
        and  ecx,0x1fff
        movzx ebp,BYTE PTR [ecx+0x48f868]
        lea  ecx,[eax+edx*1+0x4]
        and  ecx,0x1fff
        movzx ecx,BYTE PTR [ecx+0x48f868]
        sub  ecx,ebp
        jne loc_00436129
        lea  ecx,[eax+esi*1+0x5]
        and  ecx,0x1fff
        movzx ebp,BYTE PTR [ecx+0x48f868]
        lea  ecx,[eax+edx*1+0x5]
        and  ecx,0x1fff
        movzx ecx,BYTE PTR [ecx+0x48f868]
        sub  ecx,ebp
        jne loc_0043612E
        add  eax,0x6
        cmp  eax,0x12
        jl loc_00436020
        jmp loc_00436131
    loc_0043611C:
        inc  eax
        jmp loc_00436131
    loc_0043611F:
        add  eax,0x2
        jmp loc_00436131
    loc_00436124:
        add  eax,0x3
        jmp loc_00436131
    loc_00436129:
        add  eax,0x4
        jmp loc_00436131
    loc_0043612E:
        add  eax,0x5
    loc_00436131:
        cmp  eax,ebx
        jl loc_00436142
        cmp  eax,0x12
        mov  edi,DWORD PTR [esp+0x14]
        mov  ebx,eax
        mov  DWORD PTR [edi],esi
        jge loc_00436166
    loc_00436142:
        test  ecx,ecx
        lea  eax,[esi+esi*2]
        jl loc_00436152
        lea  eax,[eax*4+0x477860]
        jmp loc_00436159
    loc_00436152:
        lea  eax,[eax*4+0x47785c]
    loc_00436159:
        mov  ecx,DWORD PTR [eax]
        test  ecx,ecx
        je loc_004361D9
        mov  esi,ecx
        jmp loc_00436015
    loc_00436166:
        lea  ecx,[esi+esi*2]
        lea  edi,[ecx*4+0x477858]
        mov  ecx,DWORD PTR [edi]
        lea  ecx,[ecx+ecx*2]
        shl  ecx,0x2
        cmp  DWORD PTR [ecx+0x47785c],esi
        jne loc_00436188
        mov  DWORD PTR [ecx+0x47785c],edx
        jmp loc_0043618E
    loc_00436188:
        mov  DWORD PTR [ecx+0x477860],edx
    loc_0043618E:
        lea  ecx,[edx+edx*2]
        shl  ecx,0x2
        lea  esi,[ecx+0x477858]
        mov  ebx,edi
        mov  ebp,DWORD PTR [ebx]
        mov  DWORD PTR [esi],ebp
        mov  ebp,DWORD PTR [ebx+0x4]
        mov  DWORD PTR [esi+0x4],ebp
        mov  ebx,DWORD PTR [ebx+0x8]
        mov  DWORD PTR [esi+0x8],ebx
        mov  esi,DWORD PTR [ecx+0x47785c]
        lea  esi,[esi+esi*2]
        mov  DWORD PTR [esi*4+0x477858],edx
        mov  ecx,DWORD PTR [ecx+0x477860]
        lea  ecx,[ecx+ecx*2]
        mov  DWORD PTR [ecx*4+0x477858],edx
        mov  DWORD PTR [edi],0x0
        pop  edi
        pop  ebp
        pop  esi
        pop  ebx
        ret  0x4
    loc_004361D9:
        mov  DWORD PTR [eax],edx
        pop  edi
        lea  eax,[edx+edx*2]
        shl  eax,0x2
        pop  ebp
        mov  DWORD PTR [eax+0x477858],esi
        mov  DWORD PTR [eax+0x477860],0x0
        mov  DWORD PTR [eax+0x47785c],0x0
        pop  esi
        mov  eax,ebx
        pop  ebx
        ret  0x4
    }
}
