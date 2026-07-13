// 0044DF70: FUN_0044df70
// Original size: 560 bytes, actual code: 165 instructions
extern "C" void FUN_0044ff00(void);
extern "C" void FUN_0044ff80(void);
extern "C" void FUN_00450470(void);
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_0044df70(void) {
    __asm {
        sub  esp,0x10
        mov  edx,DWORD PTR [esp+0x18]
        push  ebx
        push  ebp
        push  esi
        push  edi
        mov  edi,DWORD PTR [esp+0x24]
        add  edi,0x4
        mov  esi,eax
        mov  eax,DWORD PTR [edi]
        mov  ecx,DWORD PTR [eax+0x10]
        mov  eax,DWORD PTR [esi+0x1008]
        lea  ebp,[ecx+edx*4+0x4]
        xor  edx,edx
        test  eax,eax
        mov  DWORD PTR [esp+0x14],edx
        mov  DWORD PTR [esp+0x1c],eax
        lea  ecx,[eax+0x8]
        jne loc_0044DFC1
        mov  ecx,eax
        lea  ebx,[ecx+0x4]
        cmp  ebx,0x1000
        jge loc_0044DFBC
        mov  DWORD PTR [ecx+esi*1+0x8],edx
        add  DWORD PTR [esi+0x1008],0x4
    loc_0044DFBC:
        mov  ecx,0xc
    loc_0044DFC1:
        mov  edx,DWORD PTR [edi]
        mov  ebx,DWORD PTR [esp+0x28]
        movzx edx,BYTE PTR [edx+0xb]
        inc  ebx
        cmp  ebx,edx
        jge loc_0044E08E
        lea  eax,[ecx+esi*1+0x8]
        mov  DWORD PTR [esp+0x28],eax
        lea  eax,[ebp+0x4]
        mov  DWORD PTR [esp+0x10],eax
        jmp loc_0044DFF0
    loc_0044DFE5:
        mov  eax,DWORD PTR [esp+0x10]
        nop
    loc_0044DFF0:
        mov  ecx,DWORD PTR [edi]
        mov  dl,BYTE PTR [ecx+ebp*1+0x10]
        cmp  dl,0x66
        je loc_0044E033
        cmp  dl,0x67
        je loc_0044E033
        mov  edx,DWORD PTR [esp+0x24]
        shr  eax,0x2
        mov  ecx,DWORD PTR [ecx+eax*4+0x10]
        push  ecx
        push  ebx
        call FUN_0044ff00
        mov  edx,DWORD PTR [edi]
        cmp  BYTE PTR [edx+ebp*1+0x11],0x66
        mov  DWORD PTR [esp+0x18],eax
        jne loc_0044E02B
        fild  DWORD PTR [esp+0x18]
        mov  eax,DWORD PTR [esp+0x28]
        fstp  DWORD PTR [eax]
        jmp loc_0044E062
    loc_0044E02B:
        mov  ecx,DWORD PTR [esp+0x28]
        mov  DWORD PTR [ecx],eax
        jmp loc_0044E062
    loc_0044E033:
        shr  eax,0x2
        mov  edx,DWORD PTR [ecx+eax*4+0x10]
        mov  eax,DWORD PTR [esp+0x24]
        push  edx
        mov  ecx,ebx
        call FUN_0044ff80
        mov  eax,DWORD PTR [edi]
        cmp  BYTE PTR [eax+ebp*1+0x11],0x66
        jne loc_0044E057
        mov  ecx,DWORD PTR [esp+0x28]
        fstp  DWORD PTR [ecx]
        jmp loc_0044E062
    loc_0044E057:
        call FUN_00463b2c
        mov  edx,DWORD PTR [esp+0x28]
        mov  DWORD PTR [edx],eax
    loc_0044E062:
        mov  ecx,DWORD PTR [esp+0x28]
        mov  eax,DWORD PTR [edi]
        mov  edx,DWORD PTR [esp+0x10]
        add  ecx,0x4
        mov  DWORD PTR [esp+0x28],ecx
        movzx ecx,BYTE PTR [eax+0xb]
        inc  ebx
        add  edx,0x8
        add  ebp,0x8
        cmp  ebx,ecx
        mov  DWORD PTR [esp+0x10],edx
        jl loc_0044DFE5
        mov  eax,DWORD PTR [esp+0x1c]
    loc_0044E08E:
        test  eax,eax
        mov  edx,DWORD PTR [esp+0x24]
        mov  ebx,0x4
        je loc_0044E0F4
        mov  ecx,DWORD PTR [esi+0x1008]
        add  ecx,0xfffffffc
        js loc_0044E0B4
        mov  DWORD PTR [esi+0x1008],ecx
        mov  ecx,DWORD PTR [ecx+esi*1+0x8]
        mov  DWORD PTR [esp+0x14],ecx
    loc_0044E0B4:
        mov  ecx,DWORD PTR [esp+0x14]
        mov  DWORD PTR [esi+0x1008],eax
        mov  DWORD PTR [eax+esi*1+0x4],ecx
        mov  eax,DWORD PTR [esi+0x1008]
        lea  ecx,[eax+0x4]
        cmp  ecx,0x1000
        jge loc_0044E0DF
        mov  ecx,DWORD PTR [edx]
        mov  DWORD PTR [eax+esi*1+0x8],ecx
        add  DWORD PTR [esi+0x1008],ebx
    loc_0044E0DF:
        mov  eax,DWORD PTR [esi+0x1008]
        lea  ecx,[eax+0x4]
        cmp  ecx,0x1000
        jge loc_0044E12E
        mov  ecx,DWORD PTR [edi]
        jmp loc_0044E124
    loc_0044E0F4:
        mov  eax,ebx
        lea  ebp,[eax+0x4]
        xor  ecx,ecx
        cmp  ebp,0x1000
        mov  DWORD PTR [esi+0x1008],ebx
        jge loc_0044E113
        mov  DWORD PTR [eax+esi*1+0x8],ecx
        add  DWORD PTR [esi+0x1008],ebx
    loc_0044E113:
        mov  eax,DWORD PTR [esi+0x1008]
        lea  ebp,[eax+0x4]
        cmp  ebp,0x1000
        jge loc_0044E12E
    loc_0044E124:
        mov  DWORD PTR [eax+esi*1+0x8],ecx
        add  DWORD PTR [esi+0x1008],ebx
    loc_0044E12E:
        mov  eax,DWORD PTR [edx+0x1014]
        mov  ebx,DWORD PTR [eax+0x4]
        mov  DWORD PTR [eax+0x4],esi
        mov  esi,DWORD PTR [edx+0x1014]
        mov  edx,DWORD PTR [edi]
        mov  eax,DWORD PTR [esi+0x102c]
        add  edx,0x14
        push  edx
        call FUN_00450470
        mov  ecx,DWORD PTR [esi+0x4]
        mov  DWORD PTR [ecx+0x4],eax
        mov  edx,DWORD PTR [esi+0x4]
        mov  DWORD PTR [edx],0x0
        mov  eax,DWORD PTR [esi+0x4]
        mov  ecx,DWORD PTR [eax+0x4]
        test  ecx,ecx
        jne loc_0044E17D
        mov  DWORD PTR [edi],0x0
        pop  edi
        pop  esi
        pop  ebp
        or   eax,0xffffffff
        pop  ebx
        add  esp,0x10
        ret  0x8
    loc_0044E17D:
        mov  ecx,DWORD PTR [esp+0x24]
        mov  edx,DWORD PTR [ecx+0x1014]
        pop  edi
        pop  esi
        pop  ebp
        mov  DWORD PTR [edx+0x4],ebx
        xor  eax,eax
        pop  ebx
        add  esp,0x10
        ret  0x8
    }
}
