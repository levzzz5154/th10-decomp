// 00437750: FUN_00437750
// Original size: 688 bytes, actual code: 222 instructions

extern "C" __declspec(naked) void FUN_00437750(void) {
    __asm {
        sub  esp,0x48
        push  ebx
        push  ebp
        mov  ebp,DWORD PTR [esp+0x5c]
        push  esi
        push  edi
        mov  esi,edx
        mov  edi,eax
        mov  eax,DWORD PTR [esi+0x11c]
        test  eax,eax
        mov  ebx,ecx
        je loc_004377F2
        mov  eax,DWORD PTR [esp+0x5c]
        mov  ecx,DWORD PTR [eax]
        lea  edx,[esp+0x38]
        push  edx
        push  eax
        call  DWORD PTR [ecx+0x30]
        mov  eax,DWORD PTR [esi+0x104]
        mov  edx,DWORD PTR [esi+0x108]
        xor  ecx,ecx
        push  ecx
        mov  DWORD PTR [esp+0x2c],ecx
        mov  DWORD PTR [esp+0x30],ecx
        lea  ecx,[esp+0x2c]
        push  ecx
        lea  ecx,[esp+0x28]
        mov  DWORD PTR [esp+0x38],eax
        mov  eax,DWORD PTR [esp+0x64]
        push  ecx
        mov  DWORD PTR [esp+0x40],edx
        mov  edx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [edx+0x34]
        test  eax,eax
        jne loc_004377F2
        mov  edx,DWORD PTR [esi+0x110]
        mov  ecx,DWORD PTR [esi+0x120]
        mov  esi,DWORD PTR [esi+0x100]
        mov  eax,DWORD PTR [esp+0x20]
        mov  DWORD PTR [esp+0x64],edx
        cmp  DWORD PTR [esp+0x38],esi
        mov  DWORD PTR [esp+0x10],eax
        jne loc_004379BF
        sub  esi,0x15
        je loc_00437930
        sub  esi,0x4
        je loc_004378E0
        dec  esi
        je loc_004377FE
    loc_004377F2:
        pop  edi
        pop  esi
        pop  ebp
        xor  al,al
        pop  ebx
        add  esp,0x48
        ret  0xc
    loc_004377FE:
        mov  edx,DWORD PTR [esp+0x24]
        imul  eax,edi
        add  eax,edx
        test  ebp,ebp
        lea  edi,[eax+ebx*2]
        jle loc_004379BF
        mov  DWORD PTR [esp+0x18],ebp
    loc_00437816:
        mov  edx,DWORD PTR [esp+0x60]
        xor  eax,eax
        test  edx,edx
        jle loc_004378BA
        mov  DWORD PTR [esp+0x14],edx
        mov  DWORD PTR [esp+0x1c],edx
        nop
    loc_00437830:
        movzx edx,BYTE PTR [edi]
        movzx eax,BYTE PTR [ecx]
        movzx esi,BYTE PTR [ecx+0x1]
        shr  eax,0x4
        shr  edx,0x4
        sub  eax,edx
        shr  esi,0x4
        imul  eax,esi
        sar  eax,0x4
        add  al,dl
        shl  al,0x4
        mov  BYTE PTR [edi],al
        xor  edx,edx
        mov  dl,BYTE PTR [ecx]
        xor  ebx,ebx
        and  eax,0xf
        and  edx,0xf
        sub  edx,eax
        imul  edx,esi
        sar  edx,0x4
        add  dl,al
        or   BYTE PTR [edi],dl
        movzx eax,BYTE PTR [edi+0x1]
        mov  bl,BYTE PTR [ecx+0x1]
        mov  edx,eax
        shr  eax,0x2
        and  eax,0x3c
        add  eax,esi
        and  edx,0xf
        and  ebx,0xf
        cmp  eax,0x10
        mov  ebp,ebx
        jl loc_0043788D
        mov  eax,0xf
    loc_0043788D:
        mov  ebx,ebp
        sub  ebx,edx
        imul  ebx,esi
        sar  ebx,0x4
        shl  al,0x4
        add  bl,dl
        or   bl,al
        mov  eax,DWORD PTR [esp+0x14]
        mov  BYTE PTR [edi+0x1],bl
        add  edi,0x2
        add  ecx,0x2
        dec  eax
        mov  DWORD PTR [esp+0x14],eax
        jne loc_00437830
        mov  eax,DWORD PTR [esp+0x1c]
    loc_004378BA:
        mov  edx,DWORD PTR [esp+0x64]
        add  eax,eax
        sub  edx,eax
        add  ecx,edx
        mov  edx,DWORD PTR [esp+0x10]
        sub  edx,eax
        mov  eax,DWORD PTR [esp+0x18]
        add  edi,edx
        dec  eax
        mov  DWORD PTR [esp+0x18],eax
        jne loc_00437816
        jmp loc_004379BF
    loc_004378E0:
        mov  esi,DWORD PTR [esp+0x24]
        imul  eax,edi
        add  eax,esi
        test  ebp,ebp
        lea  eax,[eax+ebx*2]
        jle loc_004379BF
    loc_004378F4:
        mov  edx,DWORD PTR [esp+0x60]
        xor  edi,edi
        test  edx,edx
        jle loc_00437915
        mov  esi,edx
        mov  edi,edx
    loc_00437902:
        mov  dx,WORD PTR [ecx]
        test  dh,dh
        jns loc_0043790C
        mov  WORD PTR [eax],dx
    loc_0043790C:
        add  eax,0x2
        add  ecx,0x2
        dec  esi
        jne loc_00437902
    loc_00437915:
        mov  esi,DWORD PTR [esp+0x64]
        lea  edx,[edi+edi*1]
        sub  esi,edx
        add  ecx,esi
        mov  esi,DWORD PTR [esp+0x10]
        sub  esi,edx
        add  eax,esi
        dec  ebp
        jne loc_004378F4
        jmp loc_004379BF
    loc_00437930:
        mov  edx,DWORD PTR [esp+0x24]
        imul  eax,edi
        add  eax,edx
        test  ebp,ebp
        lea  esi,[eax+ebx*4]
        jle loc_004379BF
        mov  DWORD PTR [esp+0x18],ebp
    loc_00437948:
        mov  ebp,DWORD PTR [esp+0x60]
        xor  ebx,ebx
        test  ebp,ebp
        jle loc_0043799D
        mov  ebx,ebp
    loc_00437954:
        movzx edi,BYTE PTR [ecx+0x3]
        movzx eax,BYTE PTR [esi]
        movzx edx,BYTE PTR [ecx]
        sub  edx,eax
        imul  edx,edi
        sar  edx,0x8
        add  dl,al
        movzx eax,BYTE PTR [esi+0x1]
        mov  BYTE PTR [esi],dl
        movzx edx,BYTE PTR [ecx+0x1]
        sub  edx,eax
        imul  edx,edi
        sar  edx,0x8
        add  dl,al
        movzx eax,BYTE PTR [esi+0x2]
        mov  BYTE PTR [esi+0x1],dl
        movzx edx,BYTE PTR [ecx+0x2]
        sub  edx,eax
        imul  edx,edi
        sar  edx,0x8
        add  dl,al
        mov  BYTE PTR [esi+0x2],dl
        add  esi,0x4
        add  ecx,0x4
        dec  ebp
        jne loc_00437954
    loc_0043799D:
        mov  edx,DWORD PTR [esp+0x64]
        lea  eax,[ebx*4+0x0]
        sub  edx,eax
        add  ecx,edx
        mov  edx,DWORD PTR [esp+0x10]
        sub  edx,eax
        mov  eax,DWORD PTR [esp+0x18]
        add  esi,edx
        dec  eax
        mov  DWORD PTR [esp+0x18],eax
        jne loc_00437948
    loc_004379BF:
        mov  eax,DWORD PTR [esp+0x5c]
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0x38]
        pop  edi
        pop  esi
        pop  ebp
        mov  al,0x1
        pop  ebx
        add  esp,0x48
        ret  0xc
    }
}
