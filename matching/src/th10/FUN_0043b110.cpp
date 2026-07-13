// 0043B110: FUN_0043b110
// Original size: 1680 bytes, actual code: 600 instructions
extern "C" void FUN_0043a730(void);
extern "C" void FUN_0043aeb0(void);
extern "C" void _free(void);
extern "C" void _malloc(void);
extern "C" void __allmul(void);
extern "C" void __aulldiv(void);
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_0043b110(void) {
    __asm {
        sub  esp,0xc
        push  ebx
        push  ebp
        mov  ebp,DWORD PTR [esp+0x18]
        push  esi
        mov  esi,DWORD PTR [esp+0x20]
        mov  eax,DWORD PTR [esi+0x14]
        mov  cl,BYTE PTR [eax]
        push  edi
        lea  edi,[esi+0x14]
        xor  dl,dl
        cmp  cl,0x80
        mov  BYTE PTR [esp+0x11],dl
        mov  BYTE PTR [esp+0x20],dl
        mov  BYTE PTR [esp+0x12],cl
        jae loc_0043B143
        mov  al,BYTE PTR [esi+0xc]
        mov  BYTE PTR [esp+0x12],al
        jmp loc_0043B146
    loc_0043B143:
        inc  eax
        mov  DWORD PTR [edi],eax
    loc_0043B146:
        mov  cl,BYTE PTR [esp+0x12]
        mov  al,cl
        and  al,0xf0
        movzx eax,al
        mov  bl,cl
        add  eax,0xffffff80
        and  bl,0xf
        cmp  eax,0x70
        mov  BYTE PTR [esp+0x13],bl
        mov  DWORD PTR [esp+0x18],eax
        ja loc_0043B287
        movzx eax,BYTE PTR [eax+0x43b64c]
        jmp  DWORD PTR [eax*4+0x43b63c]
        cmp  cl,0xf0
        jne loc_0043B2A2
        mov  ecx,DWORD PTR [ebp+0x94]
        mov  esi,DWORD PTR [ebp+ecx*4+0x14]
        test  esi,esi
        je loc_0043B196
        mov  edx,ebp
        call FUN_0043aeb0
    loc_0043B196:
        push  0x40
        call _malloc
        mov  edx,DWORD PTR [ebp+0x94]
        mov  DWORD PTR [ebp+edx*4+0x14],eax
        mov  eax,DWORD PTR [ebp+0x94]
        mov  ebx,DWORD PTR [ebp+eax*4+0x14]
        add  esp,0x4
        mov  esi,edi
        call FUN_0043a730
        mov  esi,eax
        xor  eax,eax
        mov  ecx,0x10
        mov  edi,ebx
        rep stosd
        lea  edi,[esi+0x1]
        push  edi
        call _malloc
        mov  DWORD PTR [ebx],eax
        mov  BYTE PTR [eax],0xf0
        xor  eax,eax
        add  esp,0x4
        cmp  esi,eax
        mov  DWORD PTR [ebx+0x10],eax
        mov  DWORD PTR [ebx+0x4],edi
        jle loc_0043B201
    loc_0043B1E5:
        mov  edi,DWORD PTR [esp+0x24]
        mov  ecx,DWORD PTR [edi+0x14]
        mov  cl,BYTE PTR [ecx]
        mov  edx,DWORD PTR [ebx]
        add  edi,0x14
        mov  BYTE PTR [eax+edx*1+0x1],cl
        mov  ecx,DWORD PTR [edi]
        inc  ecx
        inc  eax
        cmp  eax,esi
        mov  DWORD PTR [edi],ecx
        jl loc_0043B1E5
    loc_0043B201:
        mov  eax,DWORD PTR [ebp+0x13c]
        test  eax,eax
        je loc_0043B261
        push  0x40
        push  ebx
        push  eax
        call  DWORD PTR ds:0x4662a0
        test  eax,eax
        jne loc_0043B235
        mov  edx,DWORD PTR [ebp+0x13c]
        push  0x40
        push  ebx
        push  edx
        call  DWORD PTR ds:0x46629c
        neg  eax
        sbb  eax,eax
        neg  eax
        mov  DWORD PTR [esp+0x14],eax
        je loc_0043B261
    loc_0043B235:
        mov  eax,DWORD PTR [ebx]
        test  eax,eax
        je loc_0043B24A
        push  eax
        call _free
        add  esp,0x4
        mov  DWORD PTR [ebx],0x0
    loc_0043B24A:
        push  ebx
        call _free
        mov  eax,DWORD PTR [ebp+0x94]
        add  esp,0x4
        mov  DWORD PTR [ebp+eax*4+0x14],0x0
    loc_0043B261:
        mov  ecx,DWORD PTR [ebp+0x94]
        inc  ecx
        and  ecx,0x8000001f
        jns loc_0043B275
        dec  ecx
        or   ecx,0xffffffe0
        inc  ecx
    loc_0043B275:
        mov  bl,BYTE PTR [esp+0x13]
        mov  DWORD PTR [ebp+0x94],ecx
    loc_0043B27F:
        mov  esi,DWORD PTR [esp+0x24]
    loc_0043B283:
        mov  dl,BYTE PTR [esp+0x11]
    loc_0043B287:
        mov  eax,DWORD PTR [esp+0x18]
        cmp  eax,0x40
        ja loc_0043B5D8
        movzx eax,BYTE PTR [eax+0x43b6d4]
        jmp  DWORD PTR [eax*4+0x43b6c0]
    loc_0043B2A2:
        cmp  cl,0xff
        jne loc_0043B287
        mov  eax,DWORD PTR [edi]
        mov  dl,BYTE PTR [eax]
        inc  eax
        mov  esi,edi
        mov  BYTE PTR [esp+0x13],dl
        mov  DWORD PTR [edi],eax
        call FUN_0043a730
        mov  cl,BYTE PTR [esp+0x13]
        cmp  cl,0x2f
        mov  DWORD PTR [esp+0x14],eax
        jne loc_0043B2DA
        mov  eax,DWORD PTR [esp+0x24]
        pop  edi
        pop  esi
        pop  ebp
        mov  DWORD PTR [eax],0x0
        pop  ebx
        add  esp,0xc
        ret  0x8
    loc_0043B2DA:
        cmp  cl,0x51
        jne loc_0043B386
        mov  ecx,DWORD PTR [ebp+0x12c]
        mov  eax,DWORD PTR [ebp+0x120]
        push  ecx
        mov  ecx,DWORD PTR [ebp+0x128]
        cdq
        push  ecx
        push  edx
        push  eax
        call __allmul
        push  0x0
        push  0x3e8
        push  edx
        push  eax
        call __allmul
        mov  ecx,eax
        mov  eax,DWORD PTR [ebp+0x124]
        mov  esi,edx
        cdq
        push  edx
        push  eax
        push  esi
        push  ecx
        call __aulldiv
        mov  ecx,DWORD PTR [ebp+0x130]
        mov  esi,DWORD PTR [ebp+0x134]
        add  ecx,eax
        mov  eax,DWORD PTR [esp+0x14]
        adc  esi,edx
        mov  DWORD PTR [ebp+0x130],ecx
        xor  ecx,ecx
        cmp  eax,ecx
        mov  DWORD PTR [ebp+0x134],esi
        mov  DWORD PTR [ebp+0x128],ecx
        mov  DWORD PTR [ebp+0x12c],ecx
        mov  DWORD PTR [ebp+0x124],ecx
        jle loc_0043B27F
        nop
    loc_0043B360:
        mov  edx,DWORD PTR [ebp+0x124]
        mov  ecx,DWORD PTR [edi]
        imul  edx,edx,0x101
        movzx ecx,BYTE PTR [ecx]
        add  edx,ecx
        mov  DWORD PTR [ebp+0x124],edx
        mov  edx,DWORD PTR [edi]
        inc  edx
        dec  eax
        mov  DWORD PTR [edi],edx
        jne loc_0043B360
        jmp loc_0043B27F
    loc_0043B386:
        add  DWORD PTR [edi],eax
        jmp loc_0043B27F
        mov  eax,DWORD PTR [edi]
        mov  dl,BYTE PTR [eax]
        inc  eax
        mov  DWORD PTR [edi],eax
        mov  cl,BYTE PTR [eax]
        inc  eax
        mov  BYTE PTR [esp+0x11],dl
        mov  BYTE PTR [esp+0x20],cl
        mov  DWORD PTR [edi],eax
        jmp loc_0043B283
        mov  eax,DWORD PTR [edi]
        mov  dl,BYTE PTR [eax]
        inc  eax
        mov  BYTE PTR [esp+0x11],dl
        mov  DWORD PTR [edi],eax
        mov  BYTE PTR [esp+0x20],0x0
        jmp loc_0043B283
        mov  al,BYTE PTR [esp+0x20]
        test  al,al
        je loc_0043B3EE
        add  dl,BYTE PTR [ebp+0x2c4]
        movzx edi,bl
        imul  edi,edi,0x17
        movzx ecx,dl
        mov  eax,ecx
        shr  eax,0x3
        add  eax,ebp
        lea  edi,[edi+eax*1+0x154]
        and  ecx,0x7
        mov  al,0x1
        shl  al,cl
        or   BYTE PTR [edi],al
        jmp loc_0043B5D8
    loc_0043B3EE:
        add  dl,BYTE PTR [ebp+0x2c4]
        movzx edi,bl
        imul  edi,edi,0x17
        movzx ecx,dl
        mov  eax,ecx
        shr  eax,0x3
        add  eax,ebp
        lea  edi,[edi+eax*1+0x154]
        and  ecx,0x7
        mov  al,0x1
        shl  al,cl
        mov  cl,BYTE PTR [edi]
        not  al
        and  cl,al
        mov  BYTE PTR [edi],cl
        jmp loc_0043B5D8
        movzx ecx,bl
        imul  ecx,ecx,0x17
        mov  BYTE PTR [ecx+ebp*1+0x164],dl
        jmp loc_0043B5D8
        movzx eax,dl
        cmp  eax,0x5d
        ja loc_0043B5D8
        movzx eax,BYTE PTR [eax+0x43b738]
        jmp  DWORD PTR [eax*4+0x43b718]
        mov  al,BYTE PTR [esp+0x20]
        movzx ecx,bl
        imul  ecx,ecx,0x17
        mov  BYTE PTR [ecx+ebp*1+0x165],al
        jmp loc_0043B5D8
        mov  al,BYTE PTR [esp+0x20]
        movzx ecx,bl
        imul  ecx,ecx,0x17
        movzx edx,al
        mov  DWORD PTR [esp+0x24],edx
        lea  edi,[ecx+ebp*1]
        mov  BYTE PTR [edi+0x169],al
        fild  DWORD PTR [esp+0x24]
        fmul  DWORD PTR [ebp+0x2c8]
        call FUN_00463b2c
        test  eax,eax
        jge loc_0043B4A3
        mov  dl,BYTE PTR [esp+0x11]
        xor  eax,eax
        mov  BYTE PTR [edi+0x16a],al
        mov  BYTE PTR [esp+0x20],al
        jmp loc_0043B5D8
    loc_0043B4A3:
        cmp  eax,0x7f
        jle loc_0043B4AD
        mov  eax,0x7f
    loc_0043B4AD:
        mov  dl,BYTE PTR [esp+0x11]
        mov  BYTE PTR [edi+0x16a],al
        mov  BYTE PTR [esp+0x20],al
        jmp loc_0043B5D8
        mov  cl,BYTE PTR [esp+0x20]
        movzx eax,bl
        imul  eax,eax,0x17
        mov  BYTE PTR [eax+ebp*1+0x167],cl
        jmp loc_0043B5D8
        mov  cl,BYTE PTR [esp+0x20]
        movzx eax,bl
        imul  eax,eax,0x17
        mov  BYTE PTR [eax+ebp*1+0x168],cl
        jmp loc_0043B5D8
        mov  cl,BYTE PTR [esp+0x20]
        movzx eax,bl
        imul  eax,eax,0x17
        mov  BYTE PTR [eax+ebp*1+0x166],cl
        jmp loc_0043B5D8
        mov  edi,DWORD PTR [ebp+0x118]
        mov  eax,DWORD PTR [ebp+0x138]
        xor  ecx,ecx
        test  edi,edi
        jle loc_0043B530
        add  eax,0x18
    loc_0043B517:
        mov  edi,DWORD PTR [eax-0x4]
        mov  DWORD PTR [eax],edi
        mov  edi,DWORD PTR [eax-0x14]
        mov  DWORD PTR [eax+0x4],edi
        mov  edi,DWORD PTR [ebp+0x118]
        inc  ecx
        add  eax,0x20
        cmp  ecx,edi
        jl loc_0043B517
    loc_0043B530:
        mov  eax,DWORD PTR [ebp+0x124]
        mov  ecx,DWORD PTR [ebp+0x128]
        mov  DWORD PTR [ebp+0x2ec],eax
        mov  eax,DWORD PTR [ebp+0x12c]
        mov  DWORD PTR [ebp+0x2f0],ecx
        mov  ecx,DWORD PTR [ebp+0x130]
        mov  DWORD PTR [ebp+0x2f4],eax
        mov  eax,DWORD PTR [ebp+0x134]
        mov  DWORD PTR [ebp+0x2f8],ecx
        mov  DWORD PTR [ebp+0x2fc],eax
        jmp loc_0043B5D8
        mov  edi,DWORD PTR [ebp+0x118]
        mov  eax,DWORD PTR [ebp+0x138]
        xor  ecx,ecx
        test  edi,edi
        jle loc_0043B59C
        add  eax,0x14
    loc_0043B583:
        mov  edi,DWORD PTR [eax+0x4]
        mov  DWORD PTR [eax],edi
        mov  edi,DWORD PTR [eax+0x8]
        mov  DWORD PTR [eax-0x10],edi
        mov  edi,DWORD PTR [ebp+0x118]
        inc  ecx
        add  eax,0x20
        cmp  ecx,edi
        jl loc_0043B583
    loc_0043B59C:
        mov  ecx,DWORD PTR [ebp+0x2ec]
        mov  eax,DWORD PTR [ebp+0x2f0]
        mov  DWORD PTR [ebp+0x124],ecx
        mov  ecx,DWORD PTR [ebp+0x2f4]
        mov  DWORD PTR [ebp+0x128],eax
        mov  eax,DWORD PTR [ebp+0x2f8]
        mov  DWORD PTR [ebp+0x12c],ecx
        mov  ecx,DWORD PTR [ebp+0x2fc]
        mov  DWORD PTR [ebp+0x130],eax
        mov  DWORD PTR [ebp+0x134],ecx
    loc_0043B5D8:
        mov  al,BYTE PTR [esp+0x12]
        cmp  al,0xf0
        jae loc_0043B606
        mov  ebp,DWORD PTR [ebp+0x13c]
        test  ebp,ebp
        je loc_0043B606
        mov  BYTE PTR [esp+0x25],dl
        mov  dl,BYTE PTR [esp+0x20]
        mov  BYTE PTR [esp+0x24],al
        mov  BYTE PTR [esp+0x26],dl
        mov  eax,DWORD PTR [esp+0x24]
        push  eax
        push  ebp
        call  DWORD PTR ds:0x466298
    loc_0043B606:
        mov  cl,BYTE PTR [esp+0x12]
        mov  BYTE PTR [esi+0xc],cl
        xor  edx,edx
        nop
    loc_0043B610:
        mov  eax,DWORD PTR [esi+0x14]
        mov  cl,BYTE PTR [eax]
        inc  eax
        mov  DWORD PTR [esi+0x14],eax
        xor  eax,eax
        mov  al,cl
        shl  edx,0x7
        and  eax,0x7f
        add  edx,eax
        test  cl,cl
        js loc_0043B610
        mov  eax,DWORD PTR [esi+0x4]
        pop  edi
        add  eax,edx
        mov  DWORD PTR [esi+0x4],eax
        pop  esi
        pop  ebp
        pop  ebx
        add  esp,0xc
        ret  0x8
    }
}
