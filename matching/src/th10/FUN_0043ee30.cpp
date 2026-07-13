// 0043EE30: FUN_0043ee30
// Original size: 10192 bytes, actual code: 2937 instructions
extern "C" void FUN_00404610(void);
extern "C" void FUN_004050d0(void);
extern "C" void FUN_00405410(void);
extern "C" void FUN_00413200(void);
extern "C" void FUN_0041ab70(void);
extern "C" void FUN_00428dd0(void);
extern "C" void FUN_0043cb80(void);
extern "C" void FUN_0043e5a0(void);
extern "C" void FUN_0043eac0(void);
extern "C" void FUN_0043ec70(void);
extern "C" void FUN_0043ed00(void);
extern "C" void FUN_0043eda0(void);
extern "C" void FUN_00441600(void);
extern "C" void FUN_00441950(void);
extern "C" void FUN_00441ad0(void);
extern "C" void FUN_00441ef0(void);
extern "C" void FUN_00441f50(void);
extern "C" void FUN_00442050(void);
extern "C" void FUN_00442220(void);
extern "C" void FUN_00442300(void);
extern "C" void FUN_004452f0(void);
extern "C" void FUN_00448d00(void);
extern "C" void FUN_00448e30(void);
extern "C" void FUN_00448f60(void);
extern "C" void FUN_00449090(void);
extern "C" void FUN_00449450(void);
extern "C" void FUN_0044bb20(void);
extern "C" void FUN_0044bc10(void);
extern "C" void FUN_0044bf40(void);
extern "C" void _malloc(void);
extern "C" void FUN_00463b2c(void);
extern "C" void FUN_00463bba(void);
extern "C" void FUN_00463bf0(void);

extern "C" __declspec(naked) void FUN_0043ee30(void) {
    __asm {
        sub  esp,0xfc
        push  ebp
        mov  ebp,DWORD PTR [esp+0x104]
        mov  eax,DWORD PTR [ebp+0x390]
        test  eax,eax
        jne loc_0043EE57
        mov  eax,0x1
        pop  ebp
        add  esp,0xfc
        ret  0x4
    loc_0043EE57:
        mov  eax,DWORD PTR [ebp+0x35c]
        test  eax,0x20000
        je loc_0043EE70
        xor  eax,eax
        pop  ebp
        add  esp,0xfc
        ret  0x4
    loc_0043EE70:
        test  eax,0x20000000
        mov  ecx,DWORD PTR ds:0x476f78
        mov  DWORD PTR [esp+0x98],ecx
        je loc_0043EE8E
        mov  DWORD PTR ds:0x476f78,0x3f800000
    loc_0043EE8E:
        mov  ax,WORD PTR [ebp+0x304]
        push  ebx
        push  esi
        push  edi
        or   edi,0xffffffff
        test  ax,ax
        jne loc_0043F62D
    loc_0043EEA4:
        mov  ebx,DWORD PTR [ebp+0x390]
        movsx edx,WORD PTR [ebx+0x4]
        cmp  edx,DWORD PTR [ebp+0x60]
        jg loc_00440E42
        movsx eax,WORD PTR [ebx]
        inc  eax
        cmp  eax,0x5d
        ja loc_0043F532
        jmp  DWORD PTR [eax*4+0x4413a4]
        test  BYTE PTR [ebx+0x6],0x1
        mov  eax,DWORD PTR [ebx+0x8]
        je loc_0043EEDB
        mov  ecx,ebp
        call FUN_0043ec70
    loc_0043EEDB:
        mov  esi,DWORD PTR [ebp+0x35c]
        shl  eax,0x1d
        xor  eax,esi
        and  eax,0x20000000
        mov  ecx,esi
        xor  ecx,eax
        mov  DWORD PTR [ebp+0x35c],ecx
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        test  BYTE PTR [ebx+0x6],0x1
        mov  eax,DWORD PTR [ebx+0x8]
        je loc_0043EF16
        mov  ecx,ebp
        call FUN_0043ec70
    loc_0043EF16:
        mov  ecx,DWORD PTR [ebp+0x20]
        mov  edx,DWORD PTR [ebp+0x308]
        push  ecx
        push  eax
        push  edx
        lea  edi,[esp+0xf0]
        call FUN_00448d00
        mov  esi,edi
        jmp loc_0043EF88
        test  BYTE PTR [ebx+0x6],0x1
        mov  eax,DWORD PTR [ebx+0x8]
        je loc_0043EF42
        mov  ecx,ebp
        call FUN_0043ec70
    loc_0043EF42:
        mov  edx,DWORD PTR [ebp+0x20]
        push  edx
        push  eax
        mov  eax,DWORD PTR [ebp+0x308]
        push  eax
        lea  edi,[esp+0x100]
        call FUN_00448e30
        mov  esi,edi
        jmp loc_0043F00D
        test  BYTE PTR [ebx+0x6],0x1
        mov  eax,DWORD PTR [ebx+0x8]
        je loc_0043EF71
        mov  ecx,ebp
        call FUN_0043ec70
    loc_0043EF71:
        mov  ecx,DWORD PTR [ebp+0x20]
        mov  edx,DWORD PTR [ebp+0x308]
        push  ecx
        push  eax
        push  edx
        lea  edi,[esp+0x40]
        call FUN_00448f60
        mov  esi,edi
    loc_0043EF88:
        call FUN_00449450
        mov  esi,eax
        lea  eax,[esi+0x10]
        lea  ecx,[ebp+0x10]
        call FUN_00413200
        lea  ecx,[esi+0x34c]
        lea  eax,[ebp+0x334]
        mov  edx,DWORD PTR [eax]
        mov  DWORD PTR [ecx],edx
        mov  edx,DWORD PTR [eax+0x4]
        mov  DWORD PTR [ecx+0x4],edx
        mov  eax,DWORD PTR [eax+0x8]
        mov  DWORD PTR [ecx+0x8],eax
        lea  ecx,[ebp+0x340]
        mov  edx,DWORD PTR [ecx]
        add  esi,0x340
        mov  DWORD PTR [esi],edx
        mov  eax,DWORD PTR [ecx+0x4]
        mov  DWORD PTR [esi+0x4],eax
        mov  ecx,DWORD PTR [ecx+0x8]
        mov  DWORD PTR [esi+0x8],ecx
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        test  BYTE PTR [ebx+0x6],0x1
        mov  eax,DWORD PTR [ebx+0x8]
        je loc_0043EFF6
        mov  ecx,ebp
        call FUN_0043ec70
    loc_0043EFF6:
        mov  edx,DWORD PTR [ebp+0x20]
        push  edx
        push  eax
        mov  eax,DWORD PTR [ebp+0x308]
        push  eax
        lea  edi,[esp+0x34]
        call FUN_00449090
        mov  esi,edi
    loc_0043F00D:
        call FUN_00449450
        mov  esi,eax
        lea  eax,[esi+0x10]
        lea  ecx,[ebp+0x10]
        call FUN_00413200
        lea  edx,[esi+0x34c]
        lea  ecx,[ebp+0x334]
        mov  eax,DWORD PTR [ecx]
        mov  DWORD PTR [edx],eax
        mov  eax,DWORD PTR [ecx+0x4]
        mov  DWORD PTR [edx+0x4],eax
        mov  ecx,DWORD PTR [ecx+0x8]
        mov  DWORD PTR [edx+0x8],ecx
        lea  edx,[ebp+0x340]
        mov  eax,DWORD PTR [edx]
        add  esi,0x340
        mov  DWORD PTR [esi],eax
        mov  ecx,DWORD PTR [edx+0x4]
        mov  DWORD PTR [esi+0x4],ecx
        mov  edx,DWORD PTR [edx+0x8]
        mov  DWORD PTR [esi+0x8],edx
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        or   DWORD PTR [ebp+0x35c],0x1
        test  BYTE PTR [ebx+0x6],0x1
        mov  eax,DWORD PTR [ebx+0x8]
        je loc_0043F082
        mov  ecx,ebp
        call FUN_0043ec70
    loc_0043F082:
        mov  ecx,DWORD PTR [ebp+0x308]
        mov  edx,eax
        mov  eax,ebp
        call FUN_0043e5a0
        mov  eax,DWORD PTR [ebp+0x60]
        mov  DWORD PTR [ebp+0x380],eax
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        test  BYTE PTR [ebx+0x6],0x1
        je loc_0043F0C1
        mov  ecx,DWORD PTR [ebx+0x8]
        push  ecx
        mov  esi,ebp
        call FUN_0043eac0
        jmp loc_0043F0C4
    loc_0043F0C1:
        fld  DWORD PTR [ebx+0x8]
    loc_0043F0C4:
        fstp  DWORD PTR [ebp+0x3c]
        mov  al,BYTE PTR [ebx+0x6]
        test  al,0x2
        je loc_0043F0DB
        mov  edx,DWORD PTR [ebx+0xc]
        push  edx
        mov  esi,ebp
        call FUN_0043eac0
        jmp loc_0043F0DE
    loc_0043F0DB:
        fld  DWORD PTR [ebx+0xc]
    loc_0043F0DE:
        mov  eax,DWORD PTR [ebp+0x35c]
        fstp  DWORD PTR [ebp+0x40]
        or   eax,0x8
        mov  DWORD PTR [ebp+0x35c],eax
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        test  BYTE PTR [ebx+0x6],0x1
        mov  eax,DWORD PTR [ebx+0x8]
        je loc_0043F114
        mov  ecx,ebp
        call FUN_0043ec70
    loc_0043F114:
        mov  BYTE PTR [ebp+0x2ff],al
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        test  BYTE PTR [ebx+0x6],0x1
        mov  eax,DWORD PTR [ebx+0x8]
        je loc_0043F13E
        mov  ecx,ebp
        call FUN_0043ec70
    loc_0043F13E:
        mov  BYTE PTR [ebp+0x2fe],al
        test  BYTE PTR [ebx+0x6],0x2
        mov  eax,DWORD PTR [ebx+0xc]
        je loc_0043F154
        mov  ecx,ebp
        call FUN_0043ec70
    loc_0043F154:
        mov  BYTE PTR [ebp+0x2fd],al
        test  BYTE PTR [ebx+0x6],0x4
        mov  eax,DWORD PTR [ebx+0x10]
        je loc_0043F16A
        mov  ecx,ebp
        call FUN_0043ec70
    loc_0043F16A:
        mov  BYTE PTR [ebp+0x2fc],al
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        test  BYTE PTR [ebx+0x6],0x1
        mov  eax,DWORD PTR [ebx+0x8]
        je loc_0043F194
        mov  ecx,ebp
        call FUN_0043ec70
    loc_0043F194:
        mov  BYTE PTR [ebp+0x303],al
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        test  BYTE PTR [ebx+0x6],0x1
        mov  eax,DWORD PTR [ebx+0x8]
        je loc_0043F1BE
        mov  ecx,ebp
        call FUN_0043ec70
    loc_0043F1BE:
        mov  BYTE PTR [ebp+0x302],al
        test  BYTE PTR [ebx+0x6],0x2
        mov  eax,DWORD PTR [ebx+0xc]
        je loc_0043F1D4
        mov  ecx,ebp
        call FUN_0043ec70
    loc_0043F1D4:
        mov  BYTE PTR [ebp+0x301],al
        test  BYTE PTR [ebx+0x6],0x4
        mov  eax,DWORD PTR [ebx+0x10]
        je loc_0043F1EA
        mov  ecx,ebp
        call FUN_0043ec70
    loc_0043F1EA:
        mov  BYTE PTR [ebp+0x300],al
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        mov  eax,DWORD PTR [ebx+0xc]
        push  eax
        lea  eax,[ebp+0x5c]
        call FUN_00405410
        mov  eax,DWORD PTR [ebx+0x8]
        mov  ecx,DWORD PTR [ebp+0x38c]
        add  ecx,eax
        mov  DWORD PTR [ebp+0x390],ecx
        jmp loc_0043EEA4
        xor  edx,edx
        mov  dx,WORD PTR [ebx+0x6]
        lea  esi,[ebx+0x8]
        xor  ecx,ecx
        mov  eax,esi
        push  edx
        mov  edx,ebp
        call FUN_0043eda0
        dec  DWORD PTR [eax]
        test  BYTE PTR [ebx+0x6],0x1
        mov  eax,DWORD PTR [esi]
        je loc_0043F24C
        mov  ecx,ebp
        call FUN_0043ec70
    loc_0043F24C:
        test  eax,eax
        jle loc_0043F532
        mov  eax,DWORD PTR [ebx+0x10]
        push  eax
        lea  eax,[ebp+0x5c]
        call FUN_00405410
        mov  eax,DWORD PTR [ebx+0xc]
        mov  ecx,DWORD PTR [ebp+0x38c]
        add  ecx,eax
        mov  DWORD PTR [ebp+0x390],ecx
        jmp loc_0043EEA4
        mov  eax,DWORD PTR [ebp+0x35c]
        fld  DWORD PTR [ebp+0x3c]
        fmul  DWORD PTR ds:0x470b60
        xor  eax,0x200
        or   eax,0x8
        mov  DWORD PTR [ebp+0x35c],eax
        fstp  DWORD PTR [ebp+0x3c]
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        mov  eax,DWORD PTR [ebp+0x35c]
        fld  DWORD PTR [ebp+0x40]
        fmul  DWORD PTR ds:0x470b60
        xor  eax,0x400
        or   eax,0x8
        mov  DWORD PTR [ebp+0x35c],eax
        fstp  DWORD PTR [ebp+0x40]
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        test  BYTE PTR [ebx+0x6],0x1
        je loc_0043F2F1
        mov  edx,DWORD PTR [ebx+0x8]
        push  edx
        mov  esi,ebp
        call FUN_0043eac0
        jmp loc_0043F2F4
    loc_0043F2F1:
        fld  DWORD PTR [ebx+0x8]
    loc_0043F2F4:
        fstp  DWORD PTR [ebp+0x24]
        mov  al,BYTE PTR [ebx+0x6]
        test  al,0x2
        je loc_0043F30B
        mov  eax,DWORD PTR [ebx+0xc]
        push  eax
        mov  esi,ebp
        call FUN_0043eac0
        jmp loc_0043F30E
    loc_0043F30B:
        fld  DWORD PTR [ebx+0xc]
    loc_0043F30E:
        fstp  DWORD PTR [ebp+0x28]
        mov  al,BYTE PTR [ebx+0x6]
        test  al,0x4
        je loc_0043F325
        mov  ecx,DWORD PTR [ebx+0x10]
        push  ecx
        mov  esi,ebp
        call FUN_0043eac0
        jmp loc_0043F328
    loc_0043F325:
        fld  DWORD PTR [ebx+0x10]
    loc_0043F328:
        mov  eax,DWORD PTR [ebp+0x35c]
        fstp  DWORD PTR [ebp+0x2c]
        or   eax,0x4
        mov  DWORD PTR [ebp+0x35c],eax
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        test  BYTE PTR [ebx+0x6],0x1
        je loc_0043F361
        mov  edx,DWORD PTR [ebx+0x8]
        push  edx
        mov  esi,ebp
        call FUN_0043eac0
        jmp loc_0043F364
    loc_0043F361:
        fld  DWORD PTR [ebx+0x8]
    loc_0043F364:
        fstp  DWORD PTR [ebp+0x30]
        mov  al,BYTE PTR [ebx+0x6]
        test  al,0x2
        je loc_0043F37B
        mov  eax,DWORD PTR [ebx+0xc]
        push  eax
        mov  esi,ebp
        call FUN_0043eac0
        jmp loc_0043F37E
    loc_0043F37B:
        fld  DWORD PTR [ebx+0xc]
    loc_0043F37E:
        fstp  DWORD PTR [ebp+0x34]
        mov  al,BYTE PTR [ebx+0x6]
        test  al,0x4
        je loc_0043F395
        mov  ecx,DWORD PTR [ebx+0x10]
        push  ecx
        mov  esi,ebp
        call FUN_0043eac0
        jmp loc_0043F398
    loc_0043F395:
        fld  DWORD PTR [ebx+0x10]
    loc_0043F398:
        mov  eax,DWORD PTR [ebp+0x35c]
        fstp  DWORD PTR [ebp+0x38]
        or   eax,0x4
        mov  DWORD PTR [ebp+0x35c],eax
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        test  BYTE PTR [ebx+0x6],0x1
        je loc_0043F3D1
        mov  edx,DWORD PTR [ebx+0x8]
        push  edx
        mov  esi,ebp
        call FUN_0043eac0
        jmp loc_0043F3D4
    loc_0043F3D1:
        fld  DWORD PTR [ebx+0x8]
    loc_0043F3D4:
        fstp  DWORD PTR [ebp+0x44]
        mov  al,BYTE PTR [ebx+0x6]
        test  al,0x2
        je loc_0043F400
        mov  eax,DWORD PTR [ebx+0xc]
        push  eax
        mov  esi,ebp
        call FUN_0043eac0
        fstp  DWORD PTR [ebp+0x48]
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
    loc_0043F400:
        fld  DWORD PTR [ebx+0xc]
        fstp  DWORD PTR [ebp+0x48]
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        test  BYTE PTR [ebx+0x6],0x2
        mov  eax,DWORD PTR [ebx+0xc]
        je loc_0043F42A
        mov  ecx,ebp
        call FUN_0043ec70
    loc_0043F42A:
        xor  ecx,ecx
        mov  cl,BYTE PTR [ebx+0x8]
        xor  edx,edx
        mov  dl,BYTE PTR [ebp+0x2ff]
        push  ecx
        mov  ecx,eax
        push  edx
        push  0x0
        mov  eax,ebp
        call FUN_00442300
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        mov  eax,DWORD PTR [ebx+0x8]
        mov  esi,DWORD PTR [ebp+0x35c]
        shl  eax,0x4
        xor  eax,esi
        and  eax,0x30
        mov  ecx,esi
        xor  ecx,eax
        mov  DWORD PTR [ebp+0x35c],ecx
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        mov  eax,DWORD PTR [ebp+0x35c]
        test  ah,0x1
        mov  al,BYTE PTR [ebx+0x6]
        jne loc_0043F546
        test  al,0x4
        je loc_0043F4AE
        mov  ecx,DWORD PTR [ebx+0x10]
        push  ecx
        mov  esi,ebp
        call FUN_0043eac0
        fstp  DWORD PTR [esp+0x48]
        jmp loc_0043F4B5
    loc_0043F4AE:
        mov  edx,DWORD PTR [ebx+0x10]
        mov  DWORD PTR [esp+0x48],edx
    loc_0043F4B5:
        test  BYTE PTR [ebx+0x6],0x2
        je loc_0043F4CF
        mov  eax,DWORD PTR [ebx+0xc]
        push  eax
        mov  esi,ebp
        call FUN_0043eac0
        fstp  DWORD PTR [esp+0xc4]
        jmp loc_0043F4D9
    loc_0043F4CF:
        mov  ecx,DWORD PTR [ebx+0xc]
        mov  DWORD PTR [esp+0xc4],ecx
    loc_0043F4D9:
        test  BYTE PTR [ebx+0x6],0x1
        je loc_0043F4EC
        mov  edx,DWORD PTR [ebx+0x8]
        push  edx
        mov  esi,ebp
        call FUN_0043eac0
        jmp loc_0043F4EF
    loc_0043F4EC:
        fld  DWORD PTR [ebx+0x8]
    loc_0043F4EF:
        mov  eax,DWORD PTR [esp+0xc4]
        fstp  DWORD PTR [esp+0xf8]
        mov  ecx,DWORD PTR [esp+0x48]
        mov  DWORD PTR [esp+0xfc],eax
        mov  eax,DWORD PTR [esp+0xf8]
        lea  edx,[ebp+0x334]
        mov  DWORD PTR [esp+0x100],ecx
        mov  ecx,DWORD PTR [esp+0xfc]
        mov  DWORD PTR [edx],eax
        mov  eax,DWORD PTR [esp+0x100]
        mov  DWORD PTR [edx+0x4],ecx
    loc_0043F52F:
        mov  DWORD PTR [edx+0x8],eax
    loc_0043F532:
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
    loc_0043F546:
        test  al,0x4
        je loc_0043F55E
        mov  ecx,DWORD PTR [ebx+0x10]
        push  ecx
        mov  esi,ebp
        call FUN_0043eac0
        fstp  DWORD PTR [esp+0x9c]
        jmp loc_0043F568
    loc_0043F55E:
        mov  edx,DWORD PTR [ebx+0x10]
        mov  DWORD PTR [esp+0x9c],edx
    loc_0043F568:
        test  BYTE PTR [ebx+0x6],0x2
        je loc_0043F582
        mov  eax,DWORD PTR [ebx+0xc]
        push  eax
        mov  esi,ebp
        call FUN_0043eac0
        fstp  DWORD PTR [esp+0xd4]
        jmp loc_0043F58C
    loc_0043F582:
        mov  ecx,DWORD PTR [ebx+0xc]
        mov  DWORD PTR [esp+0xd4],ecx
    loc_0043F58C:
        test  BYTE PTR [ebx+0x6],0x1
        je loc_0043F59F
        mov  edx,DWORD PTR [ebx+0x8]
        push  edx
        mov  esi,ebp
        call FUN_0043eac0
        jmp loc_0043F5A2
    loc_0043F59F:
        fld  DWORD PTR [ebx+0x8]
    loc_0043F5A2:
        mov  eax,DWORD PTR [esp+0xd4]
        fstp  DWORD PTR [esp+0xe8]
        mov  ecx,DWORD PTR [esp+0x9c]
        mov  DWORD PTR [esp+0xec],eax
        mov  eax,DWORD PTR [esp+0xe8]
        lea  edx,[ebp+0x34c]
        mov  DWORD PTR [esp+0xf0],ecx
        mov  ecx,DWORD PTR [esp+0xec]
        mov  DWORD PTR [edx],eax
        mov  eax,DWORD PTR [esp+0xf0]
        mov  DWORD PTR [edx+0x4],ecx
        jmp loc_0043F52F
        test  BYTE PTR [ebx+0x6],0x1
        mov  eax,DWORD PTR [ebx+0x8]
        je loc_0043F5FA
        mov  ecx,ebp
        call FUN_0043ec70
    loc_0043F5FA:
        lea  esi,[ebp+0x5c]
        call FUN_00428dd0
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        and  DWORD PTR [ebp+0x35c],0xfffffffe
        mov  ax,WORD PTR [ebp+0x304]
        test  ax,ax
        je loc_00440E2B
    loc_0043F62D:
        mov  esi,DWORD PTR [ebp+0x38c]
        xor  edx,edx
    loc_0043F635:
        mov  cx,WORD PTR [esi]
        cmp  cx,0x40
        jne loc_0043F646
        movsx ebx,ax
        cmp  ebx,DWORD PTR [esi+0x8]
        je loc_0043F660
    loc_0043F646:
        cmp  cx,di
        je loc_0043F660
        cmp  cx,0x40
        jne loc_0043F658
        cmp  DWORD PTR [esi+0x8],edi
        jne loc_0043F658
        mov  edx,esi
    loc_0043F658:
        movzx ecx,WORD PTR [esi+0x2]
        add  esi,ecx
        jmp loc_0043F635
    loc_0043F660:
        mov  ecx,DWORD PTR [ebp+0x35c]
        and  ecx,0xffffefff
        mov  WORD PTR [ebp+0x304],0x0
        mov  DWORD PTR [ebp+0x35c],ecx
        cmp  WORD PTR [esi],0x40
        je loc_0043F68B
        test  edx,edx
        je loc_00440E35
        mov  esi,edx
    loc_0043F68B:
        lea  eax,[ebp+0x5c]
        mov  ecx,eax
        mov  ebx,DWORD PTR [ecx]
        lea  edx,[ebp+0x368]
        mov  DWORD PTR [edx],ebx
        mov  ebx,DWORD PTR [ecx+0x4]
        mov  DWORD PTR [edx+0x4],ebx
        mov  ebx,DWORD PTR [ecx+0x8]
        mov  DWORD PTR [edx+0x8],ebx
        mov  ebx,DWORD PTR [ecx+0xc]
        mov  ecx,DWORD PTR [ecx+0x10]
        mov  DWORD PTR [edx+0xc],ebx
        mov  DWORD PTR [edx+0x10],ecx
        mov  edx,DWORD PTR [ebp+0x390]
        mov  DWORD PTR [ebp+0x37c],edx
        movsx ecx,WORD PTR [esi+0x4]
        push  ecx
        call FUN_00405410
        movzx edx,WORD PTR [esi+0x2]
        mov  eax,DWORD PTR [ebp+0x35c]
        add  edx,esi
        or   eax,0x1
        mov  DWORD PTR [ebp+0x390],edx
        mov  DWORD PTR [ebp+0x35c],eax
        jmp loc_0043EEA4
        lea  eax,[ebp+0x368]
        mov  edx,DWORD PTR [eax]
        lea  ecx,[ebp+0x5c]
        mov  DWORD PTR [ecx],edx
        mov  edx,DWORD PTR [eax+0x4]
        mov  DWORD PTR [ecx+0x4],edx
        mov  edx,DWORD PTR [eax+0x8]
        mov  DWORD PTR [ecx+0x8],edx
        mov  edx,DWORD PTR [eax+0xc]
        mov  eax,DWORD PTR [eax+0x10]
        mov  DWORD PTR [ecx+0xc],edx
        mov  DWORD PTR [ecx+0x10],eax
        mov  ecx,DWORD PTR [ebp+0x37c]
        mov  DWORD PTR [ebp+0x390],ecx
        jmp loc_0043EEA4
        mov  edx,DWORD PTR [ebx+0x8]
        mov  esi,DWORD PTR [ebp+0x35c]
        xor  edx,esi
        and  edx,0x1
        mov  eax,esi
        xor  eax,edx
        mov  DWORD PTR [ebp+0x35c],eax
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        movzx eax,WORD PTR [ebx+0x8]
        mov  ecx,DWORD PTR [ebp+0x35c]
        shl  eax,0x12
        xor  eax,ecx
        mov  esi,ecx
        and  eax,0xc0000
        xor  esi,eax
        mov  DWORD PTR [ebp+0x35c],esi
        movzx ecx,WORD PTR [ebx+0xa]
        shl  ecx,0x14
        mov  eax,esi
        xor  ecx,eax
        and  ecx,0x300000
        xor  ecx,eax
        mov  DWORD PTR [ebp+0x35c],ecx
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        test  BYTE PTR [ebx+0x6],0x1
        je loc_0043F7C0
        mov  edx,DWORD PTR [ebx+0x8]
        push  edx
        mov  esi,ebp
        call FUN_0043eac0
        fstp  DWORD PTR [ebp+0x234]
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
    loc_0043F7C0:
        fld  DWORD PTR [ebx+0x8]
        fstp  DWORD PTR [ebp+0x234]
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        test  BYTE PTR [ebx+0x6],0x1
        je loc_0043F808
        mov  eax,DWORD PTR [ebx+0x8]
        push  eax
        mov  esi,ebp
        call FUN_0043eac0
        fstp  DWORD PTR [ebp+0x238]
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
    loc_0043F808:
        fld  DWORD PTR [ebx+0x8]
        fstp  DWORD PTR [ebp+0x238]
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        mov  ecx,DWORD PTR [ebx+0x8]
        mov  esi,DWORD PTR [ebp+0x35c]
        shl  ecx,0xb
        xor  ecx,esi
        and  ecx,0x800
        mov  eax,esi
        xor  eax,ecx
        mov  DWORD PTR [ebp+0x35c],eax
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        mov  edx,DWORD PTR [ebx+0x8]
        mov  esi,DWORD PTR [ebp+0x35c]
        shl  edx,0xd
        xor  edx,esi
        and  edx,0x2000
        mov  eax,esi
        xor  eax,edx
        mov  DWORD PTR [ebp+0x35c],eax
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        mov  eax,DWORD PTR [ebx+0x8]
        mov  ecx,DWORD PTR [ebp+0x35c]
        shl  eax,0x1f
        and  ecx,0x7fffffff
        or   eax,ecx
        mov  DWORD PTR [ebp+0x35c],eax
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        test  BYTE PTR [ebx+0x6],0x1
        mov  eax,DWORD PTR [ebx+0x8]
        je loc_0043F8C7
        mov  ecx,ebp
        call FUN_0043ec70
    loc_0043F8C7:
        mov  DWORD PTR [ebp+0xb4],eax
        mov  eax,ds:0x491c14
        lea  edx,[ebp+0x88]
        mov  DWORD PTR [edx],eax
        mov  ecx,DWORD PTR ds:0x491c18
        mov  DWORD PTR [edx+0x4],ecx
        mov  eax,ds:0x491c1c
        mov  DWORD PTR [edx+0x8],eax
        mov  edx,DWORD PTR ds:0x491c14
        lea  ecx,[ebp+0x94]
        mov  DWORD PTR [ecx],edx
        mov  eax,ds:0x491c18
        mov  DWORD PTR [ecx+0x4],eax
        mov  edx,DWORD PTR ds:0x491c1c
        mov  DWORD PTR [ecx+0x8],edx
        mov  eax,DWORD PTR [ebx+0xc]
        mov  DWORD PTR [ebp+0xb8],eax
        mov  eax,DWORD PTR [ebp+0x35c]
        test  ah,0x1
        lea  edi,[ebp+0x70]
        jne loc_0043F93B
        lea  ecx,[ebp+0x334]
        mov  eax,DWORD PTR [ecx]
        mov  edx,edi
        mov  DWORD PTR [edx],eax
        mov  eax,DWORD PTR [ecx+0x4]
        mov  ecx,DWORD PTR [ecx+0x8]
        mov  DWORD PTR [edx+0x4],eax
        mov  DWORD PTR [edx+0x8],ecx
        jmp loc_0043F953
    loc_0043F93B:
        lea  edx,[ebp+0x34c]
        mov  ecx,DWORD PTR [edx]
        mov  eax,edi
        mov  DWORD PTR [eax],ecx
        mov  ecx,DWORD PTR [edx+0x4]
        mov  edx,DWORD PTR [edx+0x8]
        mov  DWORD PTR [eax+0x4],ecx
        mov  DWORD PTR [eax+0x8],edx
    loc_0043F953:
        test  BYTE PTR [ebx+0x6],0x10
        je loc_0043F96D
        mov  eax,DWORD PTR [ebx+0x18]
        push  eax
        mov  esi,ebp
        call FUN_0043eac0
        fstp  DWORD PTR [esp+0xd0]
        jmp loc_0043F977
    loc_0043F96D:
        mov  ecx,DWORD PTR [ebx+0x18]
        mov  DWORD PTR [esp+0xd0],ecx
    loc_0043F977:
        test  BYTE PTR [ebx+0x6],0x8
        je loc_0043F991
        mov  edx,DWORD PTR [ebx+0x14]
        push  edx
        mov  esi,ebp
        call FUN_0043eac0
        fstp  DWORD PTR [esp+0xc8]
        jmp loc_0043F99B
    loc_0043F991:
        mov  eax,DWORD PTR [ebx+0x14]
        mov  DWORD PTR [esp+0xc8],eax
    loc_0043F99B:
        test  BYTE PTR [ebx+0x6],0x4
        je loc_0043F9AE
        mov  ecx,DWORD PTR [ebx+0x10]
        push  ecx
        mov  esi,ebp
        call FUN_0043eac0
        jmp loc_0043F9B1
    loc_0043F9AE:
        fld  DWORD PTR [ebx+0x10]
    loc_0043F9B1:
        mov  edx,DWORD PTR [esp+0xc8]
        fstp  DWORD PTR [esp+0xd8]
        mov  eax,DWORD PTR [esp+0xd0]
        mov  DWORD PTR [esp+0xdc],edx
        mov  edx,DWORD PTR [esp+0xd8]
        mov  DWORD PTR [esp+0xe0],eax
        mov  eax,DWORD PTR [esp+0xdc]
        lea  ecx,[ebp+0x7c]
        mov  DWORD PTR [ecx],edx
        mov  edx,DWORD PTR [esp+0xe0]
        mov  DWORD PTR [ecx+0x4],eax
        mov  eax,edi
        mov  DWORD PTR [ecx+0x8],edx
        call FUN_004050d0
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        mov  al,BYTE PTR [ebp+0x2fc]
        mov  cl,BYTE PTR [ebp+0x2fd]
        mov  dl,BYTE PTR [ebp+0x2fe]
        mov  BYTE PTR [esp+0x3c],al
        test  BYTE PTR [ebx+0x6],0x10
        mov  eax,DWORD PTR [ebx+0x18]
        mov  BYTE PTR [esp+0x3d],cl
        mov  BYTE PTR [esp+0x3e],dl
        je loc_0043FA3D
        mov  ecx,ebp
        call FUN_0043ec70
    loc_0043FA3D:
        mov  DWORD PTR [esp+0x24],eax
        test  BYTE PTR [ebx+0x6],0x8
        je loc_0043FA57
        mov  eax,DWORD PTR [ebx+0x14]
        mov  ecx,ebp
        call FUN_0043ec70
        mov  DWORD PTR [esp+0x14],eax
        jmp loc_0043FA5E
    loc_0043FA57:
        mov  ecx,DWORD PTR [ebx+0x14]
        mov  DWORD PTR [esp+0x14],ecx
    loc_0043FA5E:
        test  BYTE PTR [ebx+0x6],0x4
        mov  eax,DWORD PTR [ebx+0x10]
        je loc_0043FA6E
        mov  ecx,ebp
        call FUN_0043ec70
    loc_0043FA6E:
        mov  dl,BYTE PTR [esp+0x24]
        mov  cl,BYTE PTR [esp+0x14]
        mov  BYTE PTR [esp+0x12],al
        test  BYTE PTR [ebx+0x6],0x1
        mov  eax,DWORD PTR [ebx+0x8]
        mov  BYTE PTR [esp+0x10],dl
        mov  BYTE PTR [esp+0x11],cl
        je loc_0043FA92
        mov  ecx,ebp
        call FUN_0043ec70
    loc_0043FA92:
        xor  edx,edx
        mov  dl,BYTE PTR [ebx+0xc]
        lea  ecx,[esp+0x10]
        push  edx
        push  eax
        lea  edx,[esp+0x44]
        mov  eax,ebp
        call FUN_00442220
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        test  BYTE PTR [ebx+0x6],0x4
        je loc_0043FAD0
        mov  eax,DWORD PTR [ebx+0x10]
        mov  ecx,ebp
        call FUN_0043ec70
        mov  esi,eax
        jmp loc_0043FAD3
    loc_0043FAD0:
        mov  esi,DWORD PTR [ebx+0x10]
    loc_0043FAD3:
        test  BYTE PTR [ebx+0x6],0x1
        mov  eax,DWORD PTR [ebx+0x8]
        je loc_0043FAE3
        mov  ecx,ebp
        call FUN_0043ec70
    loc_0043FAE3:
        xor  ecx,ecx
        mov  cl,BYTE PTR [ebp+0x2ff]
        xor  edx,edx
        mov  dl,BYTE PTR [ebx+0xc]
        push  esi
        push  ecx
        mov  ecx,eax
        push  edx
        mov  eax,ebp
        call FUN_00442300
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        mov  al,BYTE PTR [ebp+0x300]
        mov  cl,BYTE PTR [ebp+0x301]
        mov  dl,BYTE PTR [ebp+0x302]
        mov  BYTE PTR [esp+0x30],al
        test  BYTE PTR [ebx+0x6],0x10
        mov  eax,DWORD PTR [ebx+0x18]
        mov  BYTE PTR [esp+0x31],cl
        mov  BYTE PTR [esp+0x32],dl
        je loc_0043FB3E
        mov  ecx,ebp
        call FUN_0043ec70
    loc_0043FB3E:
        mov  DWORD PTR [esp+0x14],eax
        test  BYTE PTR [ebx+0x6],0x8
        je loc_0043FB58
        mov  eax,DWORD PTR [ebx+0x14]
        mov  ecx,ebp
        call FUN_0043ec70
        mov  DWORD PTR [esp+0x24],eax
        jmp loc_0043FB5F
    loc_0043FB58:
        mov  ecx,DWORD PTR [ebx+0x14]
        mov  DWORD PTR [esp+0x24],ecx
    loc_0043FB5F:
        test  BYTE PTR [ebx+0x6],0x4
        mov  eax,DWORD PTR [ebx+0x10]
        je loc_0043FB6F
        mov  ecx,ebp
        call FUN_0043ec70
    loc_0043FB6F:
        mov  dl,BYTE PTR [esp+0x14]
        mov  cl,BYTE PTR [esp+0x24]
        mov  BYTE PTR [esp+0x3a],al
        test  BYTE PTR [ebx+0x6],0x1
        mov  eax,DWORD PTR [ebx+0x8]
        mov  BYTE PTR [esp+0x38],dl
        mov  BYTE PTR [esp+0x39],cl
        je loc_0043FB93
        mov  ecx,ebp
        call FUN_0043ec70
    loc_0043FB93:
        xor  edx,edx
        mov  dl,BYTE PTR [ebx+0xc]
        lea  ecx,[esp+0x38]
        push  edx
        push  eax
        lea  edx,[esp+0x38]
        mov  eax,ebp
        call FUN_00442050
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        test  BYTE PTR [ebx+0x6],0x4
        je loc_0043FBD1
        mov  eax,DWORD PTR [ebx+0x10]
        mov  ecx,ebp
        call FUN_0043ec70
        mov  esi,eax
        jmp loc_0043FBD4
    loc_0043FBD1:
        mov  esi,DWORD PTR [ebx+0x10]
    loc_0043FBD4:
        test  BYTE PTR [ebx+0x6],0x1
        mov  eax,DWORD PTR [ebx+0x8]
        je loc_0043FBE4
        mov  ecx,ebp
        call FUN_0043ec70
    loc_0043FBE4:
        mov  dl,BYTE PTR [ebx+0xc]
        xor  ecx,ecx
        mov  cl,BYTE PTR [ebp+0x303]
        push  esi
        push  ecx
        mov  ecx,eax
        mov  eax,ebp
        call FUN_00441f50
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        test  BYTE PTR [ebx+0x6],0x10
        je loc_0043FC25
        mov  edx,DWORD PTR [ebx+0x18]
        push  edx
        mov  esi,ebp
        call FUN_0043eac0
        fstp  DWORD PTR [esp+0x50]
        jmp loc_0043FC2C
    loc_0043FC25:
        mov  eax,DWORD PTR [ebx+0x18]
        mov  DWORD PTR [esp+0x50],eax
    loc_0043FC2C:
        test  BYTE PTR [ebx+0x6],0x8
        je loc_0043FC46
        mov  ecx,DWORD PTR [ebx+0x14]
        push  ecx
        mov  esi,ebp
        call FUN_0043eac0
        fstp  DWORD PTR [esp+0xac]
        jmp loc_0043FC50
    loc_0043FC46:
        mov  edx,DWORD PTR [ebx+0x14]
        mov  DWORD PTR [esp+0xac],edx
    loc_0043FC50:
        test  BYTE PTR [ebx+0x6],0x4
        je loc_0043FC63
        mov  eax,DWORD PTR [ebx+0x10]
        push  eax
        mov  esi,ebp
        call FUN_0043eac0
        jmp loc_0043FC66
    loc_0043FC63:
        fld  DWORD PTR [ebx+0x10]
    loc_0043FC66:
        mov  al,BYTE PTR [ebx+0x6]
        fstp  DWORD PTR [esp+0x18]
        mov  ecx,DWORD PTR [esp+0xac]
        mov  edx,DWORD PTR [esp+0x50]
        test  al,0x1
        mov  eax,DWORD PTR [ebx+0x8]
        mov  DWORD PTR [esp+0x1c],ecx
        mov  DWORD PTR [esp+0x20],edx
        je loc_0043FC8E
        mov  ecx,ebp
        call FUN_0043ec70
    loc_0043FC8E:
        mov  DWORD PTR [ebp+0x178],eax
        mov  ecx,DWORD PTR ds:0x491c14
        lea  eax,[ebp+0x14c]
        mov  DWORD PTR [eax],ecx
        mov  edx,DWORD PTR ds:0x491c18
        mov  DWORD PTR [eax+0x4],edx
        mov  ecx,DWORD PTR ds:0x491c1c
        mov  DWORD PTR [eax+0x8],ecx
        mov  eax,ds:0x491c14
        lea  edx,[ebp+0x158]
        mov  DWORD PTR [edx],eax
        mov  ecx,DWORD PTR ds:0x491c18
        mov  DWORD PTR [edx+0x4],ecx
        mov  eax,ds:0x491c1c
        mov  DWORD PTR [edx+0x8],eax
        mov  ecx,DWORD PTR [ebx+0xc]
        mov  DWORD PTR [ebp+0x17c],ecx
        lea  eax,[ebp+0x134]
        lea  edx,[ebp+0x24]
        mov  esi,DWORD PTR [edx]
        mov  ecx,eax
        mov  DWORD PTR [ecx],esi
        mov  esi,DWORD PTR [edx+0x4]
        mov  edx,DWORD PTR [edx+0x8]
        mov  DWORD PTR [ecx+0x4],esi
        mov  DWORD PTR [ecx+0x8],edx
        mov  edx,DWORD PTR [esp+0x18]
        lea  ecx,[ebp+0x140]
        mov  DWORD PTR [ecx],edx
        mov  edx,DWORD PTR [esp+0x1c]
        mov  DWORD PTR [ecx+0x4],edx
        mov  edx,DWORD PTR [esp+0x20]
        mov  DWORD PTR [ecx+0x8],edx
        call FUN_004050d0
        or   DWORD PTR [ebp+0x35c],0x4
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        test  BYTE PTR [ebx+0x6],0x8
        je loc_0043FD4A
        mov  eax,DWORD PTR [ebx+0x14]
        push  eax
        mov  esi,ebp
        call FUN_0043eac0
        fstp  DWORD PTR [esp+0xa0]
        jmp loc_0043FD54
    loc_0043FD4A:
        mov  ecx,DWORD PTR [ebx+0x14]
        mov  DWORD PTR [esp+0xa0],ecx
    loc_0043FD54:
        test  BYTE PTR [ebx+0x6],0x4
        je loc_0043FD67
        mov  edx,DWORD PTR [ebx+0x10]
        push  edx
        mov  esi,ebp
        call FUN_0043eac0
        jmp loc_0043FD6A
    loc_0043FD67:
        fld  DWORD PTR [ebx+0x10]
    loc_0043FD6A:
        mov  eax,DWORD PTR [esp+0xa0]
        fstp  DWORD PTR [esp+0x104]
        mov  DWORD PTR [esp+0x108],eax
        test  BYTE PTR [ebx+0x6],0x1
        je loc_0043FD93
        mov  eax,DWORD PTR [ebx+0x8]
        mov  ecx,ebp
        call FUN_0043ec70
        mov  esi,eax
        jmp loc_0043FD96
    loc_0043FD93:
        mov  esi,DWORD PTR [ebx+0x8]
    loc_0043FD96:
        xor  ecx,ecx
        mov  cl,BYTE PTR [ebx+0xc]
        lea  edx,[ebp+0x3c]
        mov  eax,ebp
        push  ecx
        push  esi
        lea  ecx,[esp+0x10c]
        call FUN_0041ab70
        or   DWORD PTR [ebp+0x35c],0x8
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        mov  edx,DWORD PTR [ebx+0x8]
        mov  eax,DWORD PTR [ebp+0x35c]
        shl  edx,0x16
        xor  edx,eax
        mov  esi,eax
        and  edx,0x3c00000
        xor  esi,edx
        mov  eax,esi
        and  eax,0x3c00000
        cmp  eax,0x2800000
        mov  DWORD PTR [ebp+0x35c],esi
        jne loc_0043F532
        mov  edi,ebp
        call FUN_004452f0
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        lea  eax,[ebp+0x340]
        mov  edx,eax
        mov  esi,DWORD PTR [edx]
        lea  ecx,[ebp+0x334]
        mov  DWORD PTR [ecx],esi
        mov  esi,DWORD PTR [edx+0x4]
        mov  edx,DWORD PTR [edx+0x8]
        mov  DWORD PTR [ecx+0x4],esi
        mov  DWORD PTR [ecx+0x8],edx
        xor  ecx,ecx
        mov  DWORD PTR [eax],ecx
        mov  DWORD PTR [ebp+0x344],ecx
        mov  DWORD PTR [ebp+0x348],ecx
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        mov  eax,DWORD PTR [ebp+0x35c]
        and  eax,0xfe7fffff
        or   eax,0x2400000
        mov  DWORD PTR [ebp+0x35c],eax
        test  BYTE PTR [ebx+0x6],0x1
        mov  eax,DWORD PTR [ebx+0x8]
        je loc_0043FE7C
        mov  ecx,ebp
        call FUN_0043ec70
    loc_0043FE7C:
        imul  eax,eax,0x38
        push  eax
        call _malloc
        mov  DWORD PTR [ebp+0x358],eax
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        add  esp,0x4
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        test  BYTE PTR [ebx+0x6],0x2
        je loc_0043FEB6
        mov  eax,DWORD PTR [ebx+0xc]
        mov  ecx,ebp
        call FUN_0043ec70
        mov  esi,eax
        jmp loc_0043FEB9
    loc_0043FEB6:
        mov  esi,DWORD PTR [ebx+0xc]
    loc_0043FEB9:
        xor  eax,eax
        mov  ax,WORD PTR [ebx+0x6]
        xor  ecx,ecx
        mov  edx,ebp
        push  eax
        lea  eax,[ebx+0x8]
        call FUN_0043eda0
        mov  DWORD PTR [eax],esi
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        test  BYTE PTR [ebx+0x6],0x2
        je loc_0043FEF9
        mov  ecx,DWORD PTR [ebx+0xc]
        push  ecx
        mov  esi,ebp
        call FUN_0043eac0
        fstp  DWORD PTR [esp+0x58]
        jmp loc_0043FF00
    loc_0043FEF9:
        mov  edx,DWORD PTR [ebx+0xc]
        mov  DWORD PTR [esp+0x58],edx
    loc_0043FF00:
        xor  eax,eax
        mov  ax,WORD PTR [ebx+0x6]
        lea  edi,[ebx+0x8]
        xor  ecx,ecx
        mov  esi,ebp
        push  eax
        call FUN_0043ed00
        mov  ecx,DWORD PTR [esp+0x58]
        mov  DWORD PTR [eax],ecx
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        test  BYTE PTR [ebx+0x6],0x2
        je loc_0043FF41
        mov  eax,DWORD PTR [ebx+0xc]
        mov  ecx,ebp
        call FUN_0043ec70
        mov  edi,eax
        jmp loc_0043FF44
    loc_0043FF41:
        mov  edi,DWORD PTR [ebx+0xc]
    loc_0043FF44:
        test  BYTE PTR [ebx+0x6],0x4
        je loc_0043FF58
        mov  eax,DWORD PTR [ebx+0x10]
        mov  ecx,ebp
        call FUN_0043ec70
        mov  esi,eax
        jmp loc_0043FF5B
    loc_0043FF58:
        mov  esi,DWORD PTR [ebx+0x10]
    loc_0043FF5B:
        xor  eax,eax
        mov  ax,WORD PTR [ebx+0x6]
        xor  ecx,ecx
        mov  edx,ebp
        push  eax
        lea  eax,[ebx+0x8]
        call FUN_0043eda0
        add  esi,edi
        mov  DWORD PTR [eax],esi
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        test  BYTE PTR [ebx+0x6],0x2
        je loc_0043FF9D
        mov  edx,DWORD PTR [ebx+0xc]
        push  edx
        mov  esi,ebp
        call FUN_0043eac0
        fstp  DWORD PTR [esp+0x60]
        jmp loc_0043FFA4
    loc_0043FF9D:
        mov  eax,DWORD PTR [ebx+0xc]
        mov  DWORD PTR [esp+0x60],eax
    loc_0043FFA4:
        test  BYTE PTR [ebx+0x6],0x4
        je loc_0043FFBE
        mov  ecx,DWORD PTR [ebx+0x10]
        push  ecx
        mov  esi,ebp
        call FUN_0043eac0
        fstp  DWORD PTR [esp+0xb0]
        jmp loc_0043FFC8
    loc_0043FFBE:
        mov  edx,DWORD PTR [ebx+0x10]
        mov  DWORD PTR [esp+0xb0],edx
    loc_0043FFC8:
        xor  eax,eax
        mov  ax,WORD PTR [ebx+0x6]
        lea  edi,[ebx+0x8]
        xor  ecx,ecx
        mov  esi,ebp
        push  eax
        call FUN_0043ed00
        fld  DWORD PTR [esp+0xb0]
        fadd  DWORD PTR [esp+0x60]
        fstp  DWORD PTR [eax]
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        test  BYTE PTR [ebx+0x6],0x2
        je loc_00440010
        mov  eax,DWORD PTR [ebx+0xc]
        mov  ecx,ebp
        call FUN_0043ec70
        mov  esi,eax
        jmp loc_00440013
    loc_00440010:
        mov  esi,DWORD PTR [ebx+0xc]
    loc_00440013:
        test  BYTE PTR [ebx+0x6],0x4
        je loc_00440027
        mov  eax,DWORD PTR [ebx+0x10]
        mov  ecx,ebp
        call FUN_0043ec70
        mov  edi,eax
        jmp loc_0044002A
    loc_00440027:
        mov  edi,DWORD PTR [ebx+0x10]
    loc_0044002A:
        xor  eax,eax
        mov  ax,WORD PTR [ebx+0x6]
        xor  ecx,ecx
        mov  edx,ebp
        push  eax
        lea  eax,[ebx+0x8]
        call FUN_0043eda0
        sub  esi,edi
        mov  DWORD PTR [eax],esi
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        test  BYTE PTR [ebx+0x6],0x2
        je loc_0044006F
        mov  ecx,DWORD PTR [ebx+0xc]
        push  ecx
        mov  esi,ebp
        call FUN_0043eac0
        fstp  DWORD PTR [esp+0xa8]
        jmp loc_00440079
    loc_0044006F:
        mov  edx,DWORD PTR [ebx+0xc]
        mov  DWORD PTR [esp+0xa8],edx
    loc_00440079:
        test  BYTE PTR [ebx+0x6],0x4
        je loc_00440090
        mov  eax,DWORD PTR [ebx+0x10]
        push  eax
        mov  esi,ebp
        call FUN_0043eac0
        fstp  DWORD PTR [esp+0x68]
        jmp loc_00440097
    loc_00440090:
        mov  ecx,DWORD PTR [ebx+0x10]
        mov  DWORD PTR [esp+0x68],ecx
    loc_00440097:
        xor  edx,edx
        mov  dx,WORD PTR [ebx+0x6]
        lea  edi,[ebx+0x8]
        xor  ecx,ecx
        mov  esi,ebp
        push  edx
        call FUN_0043ed00
        fld  DWORD PTR [esp+0xa8]
        fsub  DWORD PTR [esp+0x68]
        fstp  DWORD PTR [eax]
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        test  BYTE PTR [ebx+0x6],0x2
        je loc_004400DF
        mov  eax,DWORD PTR [ebx+0xc]
        mov  ecx,ebp
        call FUN_0043ec70
        mov  edi,eax
        jmp loc_004400E2
    loc_004400DF:
        mov  edi,DWORD PTR [ebx+0xc]
    loc_004400E2:
        test  BYTE PTR [ebx+0x6],0x4
        je loc_004400F6
        mov  eax,DWORD PTR [ebx+0x10]
        mov  ecx,ebp
        call FUN_0043ec70
        mov  esi,eax
        jmp loc_004400F9
    loc_004400F6:
        mov  esi,DWORD PTR [ebx+0x10]
    loc_004400F9:
        xor  eax,eax
        mov  ax,WORD PTR [ebx+0x6]
        xor  ecx,ecx
        mov  edx,ebp
        push  eax
        lea  eax,[ebx+0x8]
        call FUN_0043eda0
        imul  esi,edi
        mov  DWORD PTR [eax],esi
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        test  BYTE PTR [ebx+0x6],0x2
        je loc_0044013C
        mov  eax,DWORD PTR [ebx+0xc]
        push  eax
        mov  esi,ebp
        call FUN_0043eac0
        fstp  DWORD PTR [esp+0x70]
        jmp loc_00440143
    loc_0044013C:
        mov  ecx,DWORD PTR [ebx+0xc]
        mov  DWORD PTR [esp+0x70],ecx
    loc_00440143:
        test  BYTE PTR [ebx+0x6],0x4
        je loc_0044015D
        mov  edx,DWORD PTR [ebx+0x10]
        push  edx
        mov  esi,ebp
        call FUN_0043eac0
        fstp  DWORD PTR [esp+0xb8]
        jmp loc_00440167
    loc_0044015D:
        mov  eax,DWORD PTR [ebx+0x10]
        mov  DWORD PTR [esp+0xb8],eax
    loc_00440167:
        xor  ecx,ecx
        mov  cx,WORD PTR [ebx+0x6]
        lea  edi,[ebx+0x8]
        mov  esi,ebp
        push  ecx
        xor  ecx,ecx
        call FUN_0043ed00
        fld  DWORD PTR [esp+0xb8]
        fmul  DWORD PTR [esp+0x70]
        fstp  DWORD PTR [eax]
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        test  BYTE PTR [ebx+0x6],0x2
        je loc_004401AF
        mov  eax,DWORD PTR [ebx+0xc]
        mov  ecx,ebp
        call FUN_0043ec70
        mov  edi,eax
        jmp loc_004401B2
    loc_004401AF:
        mov  edi,DWORD PTR [ebx+0xc]
    loc_004401B2:
        test  BYTE PTR [ebx+0x6],0x4
        je loc_004401C6
        mov  eax,DWORD PTR [ebx+0x10]
        mov  ecx,ebp
        call FUN_0043ec70
        mov  esi,eax
        jmp loc_004401C9
    loc_004401C6:
        mov  esi,DWORD PTR [ebx+0x10]
    loc_004401C9:
        xor  eax,eax
        mov  ax,WORD PTR [ebx+0x6]
        xor  ecx,ecx
        mov  edx,ebp
        push  eax
        lea  eax,[ebx+0x8]
        call FUN_0043eda0
        mov  ecx,eax
        mov  eax,edi
        cdq
        idiv  esi
        mov  DWORD PTR [ecx],eax
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        test  BYTE PTR [ebx+0x6],0x2
        je loc_00440213
        mov  edx,DWORD PTR [ebx+0xc]
        push  edx
        mov  esi,ebp
        call FUN_0043eac0
        fstp  DWORD PTR [esp+0xc0]
        jmp loc_0044021D
    loc_00440213:
        mov  eax,DWORD PTR [ebx+0xc]
        mov  DWORD PTR [esp+0xc0],eax
    loc_0044021D:
        test  BYTE PTR [ebx+0x6],0x4
        je loc_00440234
        mov  ecx,DWORD PTR [ebx+0x10]
        push  ecx
        mov  esi,ebp
        call FUN_0043eac0
        fstp  DWORD PTR [esp+0x78]
        jmp loc_0044023B
    loc_00440234:
        mov  edx,DWORD PTR [ebx+0x10]
        mov  DWORD PTR [esp+0x78],edx
    loc_0044023B:
        xor  eax,eax
        mov  ax,WORD PTR [ebx+0x6]
        lea  edi,[ebx+0x8]
        xor  ecx,ecx
        mov  esi,ebp
        push  eax
        call FUN_0043ed00
        fld  DWORD PTR [esp+0xc0]
        fdiv  DWORD PTR [esp+0x78]
        fstp  DWORD PTR [eax]
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        test  BYTE PTR [ebx+0x6],0x2
        je loc_00440283
        mov  eax,DWORD PTR [ebx+0xc]
        mov  ecx,ebp
        call FUN_0043ec70
        mov  edi,eax
        jmp loc_00440286
    loc_00440283:
        mov  edi,DWORD PTR [ebx+0xc]
    loc_00440286:
        test  BYTE PTR [ebx+0x6],0x4
        je loc_0044029A
        mov  eax,DWORD PTR [ebx+0x10]
        mov  ecx,ebp
        call FUN_0043ec70
        mov  esi,eax
        jmp loc_0044029D
    loc_0044029A:
        mov  esi,DWORD PTR [ebx+0x10]
    loc_0044029D:
        xor  eax,eax
        mov  ax,WORD PTR [ebx+0x6]
        xor  ecx,ecx
        mov  edx,ebp
        push  eax
        lea  eax,[ebx+0x8]
        call FUN_0043eda0
        mov  ecx,eax
        mov  eax,edi
        cdq
        idiv  esi
        mov  DWORD PTR [ecx],edx
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        test  BYTE PTR [ebx+0x6],0x4
        je loc_004402E7
        mov  ecx,DWORD PTR [ebx+0x10]
        push  ecx
        mov  esi,ebp
        call FUN_0043eac0
        fstp  DWORD PTR [esp+0x80]
        jmp loc_004402F1
    loc_004402E7:
        mov  edx,DWORD PTR [ebx+0x10]
        mov  DWORD PTR [esp+0x80],edx
    loc_004402F1:
        test  BYTE PTR [ebx+0x6],0x2
        je loc_0044030B
        mov  eax,DWORD PTR [ebx+0xc]
        push  eax
        mov  esi,ebp
        call FUN_0043eac0
        fstp  DWORD PTR [esp+0xb4]
        jmp loc_00440315
    loc_0044030B:
        mov  ecx,DWORD PTR [ebx+0xc]
        mov  DWORD PTR [esp+0xb4],ecx
    loc_00440315:
        xor  edx,edx
        mov  dx,WORD PTR [ebx+0x6]
        lea  edi,[ebx+0x8]
        xor  ecx,ecx
        mov  esi,ebp
        push  edx
        call FUN_0043ed00
        fld  DWORD PTR [esp+0xb4]
        fld  DWORD PTR [esp+0x80]
        mov  esi,eax
        call FUN_00463bba
        fstp  DWORD PTR [esi]
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        test  BYTE PTR [ebx+0x6],0x2
        je loc_00440367
        mov  eax,DWORD PTR [ebx+0xc]
        mov  ecx,ebp
        call FUN_0043ec70
        mov  esi,eax
        jmp loc_0044036A
    loc_00440367:
        mov  esi,DWORD PTR [ebx+0xc]
    loc_0044036A:
        xor  eax,eax
        mov  ax,WORD PTR [ebx+0x6]
        xor  ecx,ecx
        mov  edx,ebp
        push  eax
        lea  eax,[ebx+0x8]
        call FUN_0043eda0
        add  DWORD PTR [eax],esi
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        test  BYTE PTR [ebx+0x6],0x2
        je loc_004403AA
        mov  eax,DWORD PTR [ebx+0xc]
        push  eax
        mov  esi,ebp
        call FUN_0043eac0
        fstp  DWORD PTR [esp+0x40]
        jmp loc_004403B1
    loc_004403AA:
        mov  ecx,DWORD PTR [ebx+0xc]
        mov  DWORD PTR [esp+0x40],ecx
    loc_004403B1:
        xor  edx,edx
        mov  dx,WORD PTR [ebx+0x6]
        lea  edi,[ebx+0x8]
        xor  ecx,ecx
        mov  esi,ebp
        push  edx
        call FUN_0043ed00
        fld  DWORD PTR [esp+0x40]
        fadd  DWORD PTR [eax]
        fstp  DWORD PTR [eax]
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        test  BYTE PTR [ebx+0x6],0x2
        je loc_004403F4
        mov  eax,DWORD PTR [ebx+0xc]
        mov  ecx,ebp
        call FUN_0043ec70
        mov  esi,eax
        jmp loc_004403F7
    loc_004403F4:
        mov  esi,DWORD PTR [ebx+0xc]
    loc_004403F7:
        xor  eax,eax
        mov  ax,WORD PTR [ebx+0x6]
        xor  ecx,ecx
        mov  edx,ebp
        push  eax
        lea  eax,[ebx+0x8]
        call FUN_0043eda0
        sub  DWORD PTR [eax],esi
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        test  BYTE PTR [ebx+0x6],0x2
        je loc_0044043A
        mov  eax,DWORD PTR [ebx+0xc]
        push  eax
        mov  esi,ebp
        call FUN_0043eac0
        fstp  DWORD PTR [esp+0x88]
        jmp loc_00440444
    loc_0044043A:
        mov  ecx,DWORD PTR [ebx+0xc]
        mov  DWORD PTR [esp+0x88],ecx
    loc_00440444:
        xor  edx,edx
        mov  dx,WORD PTR [ebx+0x6]
        lea  edi,[ebx+0x8]
        xor  ecx,ecx
        mov  esi,ebp
        push  edx
        call FUN_0043ed00
        fld  DWORD PTR [eax]
        fsub  DWORD PTR [esp+0x88]
        fstp  DWORD PTR [eax]
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        test  BYTE PTR [ebx+0x6],0x2
        je loc_0044048A
        mov  eax,DWORD PTR [ebx+0xc]
        mov  ecx,ebp
        call FUN_0043ec70
        mov  esi,eax
        jmp loc_0044048D
    loc_0044048A:
        mov  esi,DWORD PTR [ebx+0xc]
    loc_0044048D:
        xor  eax,eax
        mov  ax,WORD PTR [ebx+0x6]
        xor  ecx,ecx
        mov  edx,ebp
        push  eax
        lea  eax,[ebx+0x8]
        call FUN_0043eda0
        mov  ecx,DWORD PTR [eax]
        imul  ecx,esi
        mov  DWORD PTR [eax],ecx
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        test  BYTE PTR [ebx+0x6],0x2
        je loc_004404D5
        mov  edx,DWORD PTR [ebx+0xc]
        push  edx
        mov  esi,ebp
        call FUN_0043eac0
        fstp  DWORD PTR [esp+0xbc]
        jmp loc_004404DF
    loc_004404D5:
        mov  eax,DWORD PTR [ebx+0xc]
        mov  DWORD PTR [esp+0xbc],eax
    loc_004404DF:
        xor  ecx,ecx
        mov  cx,WORD PTR [ebx+0x6]
        lea  edi,[ebx+0x8]
        mov  esi,ebp
        push  ecx
        xor  ecx,ecx
        call FUN_0043ed00
        fld  DWORD PTR [esp+0xbc]
        fmul  DWORD PTR [eax]
        fstp  DWORD PTR [eax]
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        test  BYTE PTR [ebx+0x6],0x2
        je loc_00440525
        mov  eax,DWORD PTR [ebx+0xc]
        mov  ecx,ebp
        call FUN_0043ec70
        mov  esi,eax
        jmp loc_00440528
    loc_00440525:
        mov  esi,DWORD PTR [ebx+0xc]
    loc_00440528:
        xor  eax,eax
        mov  ax,WORD PTR [ebx+0x6]
        xor  ecx,ecx
        mov  edx,ebp
        push  eax
        lea  eax,[ebx+0x8]
        call FUN_0043eda0
        mov  ecx,eax
        mov  eax,DWORD PTR [ecx]
        cdq
        idiv  esi
        mov  DWORD PTR [ecx],eax
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        test  BYTE PTR [ebx+0x6],0x2
        je loc_00440572
        mov  edx,DWORD PTR [ebx+0xc]
        push  edx
        mov  esi,ebp
        call FUN_0043eac0
        fstp  DWORD PTR [esp+0x90]
        jmp loc_0044057C
    loc_00440572:
        mov  eax,DWORD PTR [ebx+0xc]
        mov  DWORD PTR [esp+0x90],eax
    loc_0044057C:
        xor  ecx,ecx
        mov  cx,WORD PTR [ebx+0x6]
        lea  edi,[ebx+0x8]
        mov  esi,ebp
        push  ecx
        xor  ecx,ecx
        call FUN_0043ed00
        fld  DWORD PTR [eax]
        fdiv  DWORD PTR [esp+0x90]
        fstp  DWORD PTR [eax]
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        test  BYTE PTR [ebx+0x6],0x2
        je loc_004405C2
        mov  eax,DWORD PTR [ebx+0xc]
        mov  ecx,ebp
        call FUN_0043ec70
        mov  esi,eax
        jmp loc_004405C5
    loc_004405C2:
        mov  esi,DWORD PTR [ebx+0xc]
    loc_004405C5:
        xor  eax,eax
        mov  ax,WORD PTR [ebx+0x6]
        xor  ecx,ecx
        mov  edx,ebp
        push  eax
        lea  eax,[ebx+0x8]
        call FUN_0043eda0
        mov  ecx,eax
        mov  eax,DWORD PTR [ecx]
        cdq
        idiv  esi
        mov  DWORD PTR [ecx],edx
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        test  BYTE PTR [ebx+0x6],0x2
        je loc_0044060F
        mov  edx,DWORD PTR [ebx+0xc]
        push  edx
        mov  esi,ebp
        call FUN_0043eac0
        fstp  DWORD PTR [esp+0x98]
        jmp loc_00440619
    loc_0044060F:
        mov  eax,DWORD PTR [ebx+0xc]
        mov  DWORD PTR [esp+0x98],eax
    loc_00440619:
        test  BYTE PTR [ebx+0x6],0x1
        lea  edi,[ebx+0x8]
        je loc_00440635
        mov  ecx,DWORD PTR [edi]
        push  ecx
        mov  esi,ebp
        call FUN_0043eac0
        fstp  DWORD PTR [esp+0xcc]
        jmp loc_0044063E
    loc_00440635:
        mov  edx,DWORD PTR [edi]
        mov  DWORD PTR [esp+0xcc],edx
    loc_0044063E:
        xor  eax,eax
        mov  ax,WORD PTR [ebx+0x6]
        xor  ecx,ecx
        mov  esi,ebp
        push  eax
        call FUN_0043ed00
        fld  DWORD PTR [esp+0xcc]
        fld  DWORD PTR [esp+0x98]
        mov  esi,eax
        call FUN_00463bba
        fstp  DWORD PTR [esi]
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        test  DWORD PTR [ebp+0x35c],0x40000000
        mov  al,BYTE PTR [ebx+0x6]
        je loc_0044069D
        test  al,0x2
        mov  eax,DWORD PTR [ebx+0xc]
        je loc_00440696
        mov  ecx,ebp
        call FUN_0043ec70
    loc_00440696:
        mov  ecx,0x4918a8
        jmp loc_004406B0
    loc_0044069D:
        test  al,0x2
        mov  eax,DWORD PTR [ebx+0xc]
        je loc_004406AB
        mov  ecx,ebp
        call FUN_0043ec70
    loc_004406AB:
        mov  ecx,0x4918b0
    loc_004406B0:
        mov  edi,eax
        call FUN_0043cb80
        xor  ecx,ecx
        mov  cx,WORD PTR [ebx+0x6]
        mov  esi,eax
        lea  eax,[ebx+0x8]
        mov  edx,ebp
        push  ecx
        xor  ecx,ecx
        call FUN_0043eda0
        mov  DWORD PTR [eax],esi
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        test  DWORD PTR [ebp+0x35c],0x40000000
        mov  al,BYTE PTR [ebx+0x6]
        je loc_00440711
        test  al,0x2
        je loc_00440707
        mov  edx,DWORD PTR [ebx+0xc]
        push  edx
        mov  esi,ebp
        call FUN_0043eac0
        mov  ecx,0x4918a8
        jmp loc_0044072A
    loc_00440707:
        fld  DWORD PTR [ebx+0xc]
        mov  ecx,0x4918a8
        jmp loc_0044072A
    loc_00440711:
        test  al,0x2
        je loc_00440722
        mov  eax,DWORD PTR [ebx+0xc]
        push  eax
        mov  esi,ebp
        call FUN_0043eac0
        jmp loc_00440725
    loc_00440722:
        fld  DWORD PTR [ebx+0xc]
    loc_00440725:
        mov  ecx,0x4918b0
    loc_0044072A:
        call FUN_0044bb20
        fmul  st,st(1)
        xor  ecx,ecx
        mov  cx,WORD PTR [ebx+0x6]
        fstp  DWORD PTR [esp+0x14]
        lea  edi,[ebx+0x8]
        mov  esi,ebp
        fstp  st(0)
        push  ecx
        xor  ecx,ecx
        call FUN_0043ed00
        mov  edx,DWORD PTR [esp+0x14]
        mov  DWORD PTR [eax],edx
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        test  BYTE PTR [ebx+0x6],0x2
        je loc_0044077B
        mov  eax,DWORD PTR [ebx+0xc]
        push  eax
        mov  esi,ebp
        call FUN_0043eac0
        fstp  DWORD PTR [esp+0x44]
        jmp loc_00440782
    loc_0044077B:
        mov  ecx,DWORD PTR [ebx+0xc]
        mov  DWORD PTR [esp+0x44],ecx
    loc_00440782:
        xor  edx,edx
        mov  dx,WORD PTR [ebx+0x6]
        lea  edi,[ebx+0x8]
        xor  ecx,ecx
        mov  esi,ebp
        push  edx
        call FUN_0043ed00
        fld  DWORD PTR [esp+0x44]
        fsin
        fstp  DWORD PTR [eax]
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        test  BYTE PTR [ebx+0x6],0x2
        je loc_004407C8
        mov  eax,DWORD PTR [ebx+0xc]
        push  eax
        mov  esi,ebp
        call FUN_0043eac0
        fstp  DWORD PTR [esp+0x4c]
        jmp loc_004407CF
    loc_004407C8:
        mov  ecx,DWORD PTR [ebx+0xc]
        mov  DWORD PTR [esp+0x4c],ecx
    loc_004407CF:
        xor  edx,edx
        mov  dx,WORD PTR [ebx+0x6]
        lea  edi,[ebx+0x8]
        xor  ecx,ecx
        mov  esi,ebp
        push  edx
        call FUN_0043ed00
        fld  DWORD PTR [esp+0x4c]
        fcos
        fstp  DWORD PTR [eax]
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        test  BYTE PTR [ebx+0x6],0x2
        je loc_00440815
        mov  eax,DWORD PTR [ebx+0xc]
        push  eax
        mov  esi,ebp
        call FUN_0043eac0
        fstp  DWORD PTR [esp+0x54]
        jmp loc_0044081C
    loc_00440815:
        mov  ecx,DWORD PTR [ebx+0xc]
        mov  DWORD PTR [esp+0x54],ecx
    loc_0044081C:
        xor  edx,edx
        mov  dx,WORD PTR [ebx+0x6]
        lea  edi,[ebx+0x8]
        xor  ecx,ecx
        mov  esi,ebp
        push  edx
        call FUN_0043ed00
        fld  DWORD PTR [esp+0x54]
        fptan
        fstp  st(0)
        fstp  DWORD PTR [eax]
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        test  BYTE PTR [ebx+0x6],0x2
        je loc_00440864
        mov  eax,DWORD PTR [ebx+0xc]
        push  eax
        mov  esi,ebp
        call FUN_0043eac0
        fstp  DWORD PTR [esp+0x5c]
        jmp loc_0044086B
    loc_00440864:
        mov  ecx,DWORD PTR [ebx+0xc]
        mov  DWORD PTR [esp+0x5c],ecx
    loc_0044086B:
        xor  edx,edx
        mov  dx,WORD PTR [ebx+0x6]
        lea  edi,[ebx+0x8]
        xor  ecx,ecx
        mov  esi,ebp
        push  edx
        call FUN_0043ed00
        fld  DWORD PTR [esp+0x5c]
        mov  esi,eax
        call FUN_00463bf0
        fstp  DWORD PTR [esi]
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        test  BYTE PTR [ebx+0x6],0x2
        je loc_004408B6
        mov  eax,DWORD PTR [ebx+0xc]
        push  eax
        mov  esi,ebp
        call FUN_0043eac0
        fstp  DWORD PTR [esp+0x64]
        jmp loc_004408BD
    loc_004408B6:
        mov  ecx,DWORD PTR [ebx+0xc]
        mov  DWORD PTR [esp+0x64],ecx
    loc_004408BD:
        xor  edx,edx
        mov  dx,WORD PTR [ebx+0x6]
        lea  edi,[ebx+0x8]
        xor  ecx,ecx
        mov  esi,ebp
        push  edx
        call FUN_0043ed00
        fld  DWORD PTR [esp+0x64]
        fld1
        fpatan
        fstp  DWORD PTR [eax]
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        test  BYTE PTR [ebx+0x6],0x1
        lea  edi,[ebx+0x8]
        je loc_00440907
        mov  eax,DWORD PTR [edi]
        push  eax
        mov  esi,ebp
        call FUN_0043eac0
        fstp  DWORD PTR [esp+0x6c]
        jmp loc_0044090D
    loc_00440907:
        mov  ecx,DWORD PTR [edi]
        mov  DWORD PTR [esp+0x6c],ecx
    loc_0044090D:
        xor  edx,edx
        mov  dx,WORD PTR [ebx+0x6]
        xor  ecx,ecx
        mov  esi,ebp
        push  edx
        call FUN_0043ed00
        mov  esi,eax
        mov  eax,DWORD PTR [esp+0x6c]
        push  0x0
        push  eax
        call FUN_0044bc10
        fstp  DWORD PTR [esi]
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        movzx ecx,BYTE PTR [ebx+0x8]
        mov  esi,DWORD PTR [ebp+0x35c]
        shl  ecx,0x1c
        xor  ecx,esi
        and  ecx,0x10000000
        mov  eax,esi
        xor  eax,ecx
        mov  DWORD PTR [ebp+0x35c],eax
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        movzx edx,BYTE PTR [ebx+0x8]
        mov  DWORD PTR [ebp+0x20],edx
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        movzx eax,BYTE PTR [ebx+0x8]
        mov  esi,DWORD PTR [ebp+0x35c]
        shl  eax,0xf
        xor  eax,esi
        and  eax,0x8000
        mov  ecx,esi
        xor  ecx,eax
        mov  DWORD PTR [ebp+0x35c],ecx
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        movzx ecx,BYTE PTR [ebx+0x8]
        mov  esi,DWORD PTR [ebp+0x35c]
        shl  ecx,0x1b
        xor  ecx,esi
        and  ecx,0x8000000
        mov  eax,esi
        xor  eax,ecx
        mov  DWORD PTR [ebp+0x35c],eax
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        movzx edx,BYTE PTR [ebx+0x8]
        mov  esi,DWORD PTR [ebp+0x35c]
        shl  edx,0x1e
        xor  edx,esi
        and  edx,0x40000000
        mov  eax,esi
        xor  eax,edx
        mov  DWORD PTR [ebp+0x35c],eax
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        test  BYTE PTR [ebx+0x6],0x1
        je loc_00440A3B
        mov  eax,DWORD PTR [ebx+0x8]
        mov  ecx,ebp
        call FUN_0043ec70
        mov  esi,eax
        jmp loc_00440A3E
    loc_00440A3B:
        mov  esi,DWORD PTR [ebx+0x8]
    loc_00440A3E:
        test  BYTE PTR [ebx+0x6],0x2
        mov  eax,DWORD PTR [ebx+0xc]
        je loc_00440A4E
        mov  ecx,ebp
        call FUN_0043ec70
    loc_00440A4E:
        cmp  esi,eax
        je loc_00440DDA
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        test  BYTE PTR [ebx+0x6],0x1
        je loc_00440A81
        mov  eax,DWORD PTR [ebx+0x8]
        push  eax
        mov  esi,ebp
        call FUN_0043eac0
        fstp  DWORD PTR [esp+0x74]
        jmp loc_00440A88
    loc_00440A81:
        mov  ecx,DWORD PTR [ebx+0x8]
        mov  DWORD PTR [esp+0x74],ecx
    loc_00440A88:
        test  BYTE PTR [ebx+0x6],0x2
        je loc_00440A9B
        mov  edx,DWORD PTR [ebx+0xc]
        push  edx
        mov  esi,ebp
        call FUN_0043eac0
        jmp loc_00440A9E
    loc_00440A9B:
        fld  DWORD PTR [ebx+0xc]
    loc_00440A9E:
        fld  DWORD PTR [esp+0x74]
        fucompp
        fnstsw ax
        test  ah,0x44
        jnp loc_00440DDA
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        test  BYTE PTR [ebx+0x6],0x1
        je loc_00440AD7
        mov  eax,DWORD PTR [ebx+0x8]
        mov  ecx,ebp
        call FUN_0043ec70
        mov  esi,eax
        jmp loc_00440ADA
    loc_00440AD7:
        mov  esi,DWORD PTR [ebx+0x8]
    loc_00440ADA:
        test  BYTE PTR [ebx+0x6],0x2
        mov  eax,DWORD PTR [ebx+0xc]
        je loc_00440AEA
        mov  ecx,ebp
        call FUN_0043ec70
    loc_00440AEA:
        cmp  esi,eax
        jne loc_00440DDA
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        test  BYTE PTR [ebx+0x6],0x1
        je loc_00440B1D
        mov  eax,DWORD PTR [ebx+0x8]
        push  eax
        mov  esi,ebp
        call FUN_0043eac0
        fstp  DWORD PTR [esp+0x7c]
        jmp loc_00440B24
    loc_00440B1D:
        mov  ecx,DWORD PTR [ebx+0x8]
        mov  DWORD PTR [esp+0x7c],ecx
    loc_00440B24:
        test  BYTE PTR [ebx+0x6],0x2
        je loc_00440B37
        mov  edx,DWORD PTR [ebx+0xc]
        push  edx
        mov  esi,ebp
        call FUN_0043eac0
        jmp loc_00440B3A
    loc_00440B37:
        fld  DWORD PTR [ebx+0xc]
    loc_00440B3A:
        fld  DWORD PTR [esp+0x7c]
        fucompp
        fnstsw ax
        test  ah,0x44
        jp loc_00440DDA
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        test  BYTE PTR [ebx+0x6],0x1
        je loc_00440B73
        mov  eax,DWORD PTR [ebx+0x8]
        mov  ecx,ebp
        call FUN_0043ec70
        mov  esi,eax
        jmp loc_00440B76
    loc_00440B73:
        mov  esi,DWORD PTR [ebx+0x8]
    loc_00440B76:
        test  BYTE PTR [ebx+0x6],0x2
        mov  eax,DWORD PTR [ebx+0xc]
        je loc_00440B86
        mov  ecx,ebp
        call FUN_0043ec70
    loc_00440B86:
        cmp  esi,eax
        jl loc_00440DDA
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        test  BYTE PTR [ebx+0x6],0x1
        je loc_00440BBC
        mov  eax,DWORD PTR [ebx+0x8]
        push  eax
        mov  esi,ebp
        call FUN_0043eac0
        fstp  DWORD PTR [esp+0x84]
        jmp loc_00440BC6
    loc_00440BBC:
        mov  ecx,DWORD PTR [ebx+0x8]
        mov  DWORD PTR [esp+0x84],ecx
    loc_00440BC6:
        test  BYTE PTR [ebx+0x6],0x2
        je loc_00440BD9
        mov  edx,DWORD PTR [ebx+0xc]
        push  edx
        mov  esi,ebp
        call FUN_0043eac0
        jmp loc_00440BDC
    loc_00440BD9:
        fld  DWORD PTR [ebx+0xc]
    loc_00440BDC:
        fld  DWORD PTR [esp+0x84]
        fcomp st(1)
        fnstsw ax
        fstp  st(0)
        test  ah,0x5
        jnp loc_00440DDA
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        test  BYTE PTR [ebx+0x6],0x1
        je loc_00440C1A
        mov  eax,DWORD PTR [ebx+0x8]
        mov  ecx,ebp
        call FUN_0043ec70
        mov  esi,eax
        jmp loc_00440C1D
    loc_00440C1A:
        mov  esi,DWORD PTR [ebx+0x8]
    loc_00440C1D:
        test  BYTE PTR [ebx+0x6],0x2
        mov  eax,DWORD PTR [ebx+0xc]
        je loc_00440C2D
        mov  ecx,ebp
        call FUN_0043ec70
    loc_00440C2D:
        cmp  esi,eax
        jle loc_00440DDA
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        test  BYTE PTR [ebx+0x6],0x1
        je loc_00440C63
        mov  eax,DWORD PTR [ebx+0x8]
        push  eax
        mov  esi,ebp
        call FUN_0043eac0
        fstp  DWORD PTR [esp+0x8c]
        jmp loc_00440C6D
    loc_00440C63:
        mov  ecx,DWORD PTR [ebx+0x8]
        mov  DWORD PTR [esp+0x8c],ecx
    loc_00440C6D:
        test  BYTE PTR [ebx+0x6],0x2
        je loc_00440C80
        mov  edx,DWORD PTR [ebx+0xc]
        push  edx
        mov  esi,ebp
        call FUN_0043eac0
        jmp loc_00440C83
    loc_00440C80:
        fld  DWORD PTR [ebx+0xc]
    loc_00440C83:
        fld  DWORD PTR [esp+0x8c]
        fcomp st(1)
        fnstsw ax
        fstp  st(0)
        test  ah,0x41
        jnp loc_00440DDA
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        test  BYTE PTR [ebx+0x6],0x1
        je loc_00440CC1
        mov  eax,DWORD PTR [ebx+0x8]
        mov  ecx,ebp
        call FUN_0043ec70
        mov  esi,eax
        jmp loc_00440CC4
    loc_00440CC1:
        mov  esi,DWORD PTR [ebx+0x8]
    loc_00440CC4:
        test  BYTE PTR [ebx+0x6],0x2
        mov  eax,DWORD PTR [ebx+0xc]
        je loc_00440CD4
        mov  ecx,ebp
        call FUN_0043ec70
    loc_00440CD4:
        cmp  esi,eax
        jg loc_00440DDA
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        test  BYTE PTR [ebx+0x6],0x1
        je loc_00440D0A
        mov  eax,DWORD PTR [ebx+0x8]
        push  eax
        mov  esi,ebp
        call FUN_0043eac0
        fstp  DWORD PTR [esp+0x94]
        jmp loc_00440D14
    loc_00440D0A:
        mov  ecx,DWORD PTR [ebx+0x8]
        mov  DWORD PTR [esp+0x94],ecx
    loc_00440D14:
        test  BYTE PTR [ebx+0x6],0x2
        je loc_00440D27
        mov  edx,DWORD PTR [ebx+0xc]
        push  edx
        mov  esi,ebp
        call FUN_0043eac0
        jmp loc_00440D2A
    loc_00440D27:
        fld  DWORD PTR [ebx+0xc]
    loc_00440D2A:
        fld  DWORD PTR [esp+0x94]
        fcomp st(1)
        fnstsw ax
        fstp  st(0)
        test  ah,0x41
        je loc_00440DDA
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        test  BYTE PTR [ebx+0x6],0x1
        je loc_00440D68
        mov  eax,DWORD PTR [ebx+0x8]
        mov  ecx,ebp
        call FUN_0043ec70
        mov  esi,eax
        jmp loc_00440D6B
    loc_00440D68:
        mov  esi,DWORD PTR [ebx+0x8]
    loc_00440D6B:
        test  BYTE PTR [ebx+0x6],0x2
        mov  eax,DWORD PTR [ebx+0xc]
        je loc_00440D7B
        mov  ecx,ebp
        call FUN_0043ec70
    loc_00440D7B:
        cmp  esi,eax
        jge loc_00440DDA
        movzx edx,WORD PTR [ebx+0x2]
        add  edx,ebx
        mov  DWORD PTR [ebp+0x390],edx
        or   edi,0xffffffff
        jmp loc_0043EEA4
        test  BYTE PTR [ebx+0x6],0x1
        je loc_00440DAA
        mov  eax,DWORD PTR [ebx+0x8]
        push  eax
        mov  esi,ebp
        call FUN_0043eac0
        fstp  DWORD PTR [esp+0x2c]
        jmp loc_00440DB1
    loc_00440DAA:
        mov  ecx,DWORD PTR [ebx+0x8]
        mov  DWORD PTR [esp+0x2c],ecx
    loc_00440DB1:
        test  BYTE PTR [ebx+0x6],0x2
        je loc_00440DC4
        mov  edx,DWORD PTR [ebx+0xc]
        push  edx
        mov  esi,ebp
        call FUN_0043eac0
        jmp loc_00440DC7
    loc_00440DC4:
        fld  DWORD PTR [ebx+0xc]
    loc_00440DC7:
        fld  DWORD PTR [esp+0x2c]
        fcomp st(1)
        fnstsw ax
        fstp  st(0)
        test  ah,0x1
        jne loc_0043F532
    loc_00440DDA:
        mov  eax,DWORD PTR [ebx+0x14]
        push  eax
        lea  eax,[ebp+0x5c]
        call FUN_00405410
        mov  eax,DWORD PTR [ebx+0x10]
        mov  ecx,DWORD PTR [ebp+0x38c]
        add  ecx,eax
        mov  DWORD PTR [ebp+0x390],ecx
        jmp loc_0043EEA4
        and  DWORD PTR [ebp+0x35c],0xfffffffe
        mov  eax,DWORD PTR [esp+0xa4]
        pop  edi
        pop  esi
        mov  DWORD PTR [ebp+0x390],0x0
        pop  ebx
        mov  ds:0x476f78,eax
        mov  eax,0x1
        pop  ebp
        add  esp,0xfc
        ret  0x4
    loc_00440E2B:
        or   DWORD PTR [ebp+0x35c],0x1000
    loc_00440E35:
        lea  esi,[ebp+0x5c]
        push  0xbf800000
        call FUN_0044bf40
    loc_00440E42:
        fld  DWORD PTR ds:0x470b04
        fld  DWORD PTR [ebp+0x30]
        fucompp
        fnstsw ax
        test  ah,0x44
        jnp loc_00440E82
        fld  DWORD PTR ds:0x476f78
        push  ecx
        fmul  DWORD PTR [ebp+0x30]
        mov  ecx,DWORD PTR [ebp+0x24]
        fstp  DWORD PTR [esp]
        push  ecx
        call FUN_0044bc10
        fstp  DWORD PTR [ebp+0x24]
        mov  eax,DWORD PTR [ebp+0x35c]
        mov  esi,0x4
        or   eax,esi
        mov  DWORD PTR [ebp+0x35c],eax
        jmp loc_00440E87
    loc_00440E82:
        mov  esi,0x4
    loc_00440E87:
        fld  DWORD PTR ds:0x470b04
        fld  DWORD PTR [ebp+0x34]
        fucompp
        fnstsw ax
        test  ah,0x44
        jnp loc_00440EB8
        fld  DWORD PTR ds:0x476f78
        mov  edx,DWORD PTR [ebp+0x28]
        fmul  DWORD PTR [ebp+0x34]
        push  ecx
        fstp  DWORD PTR [esp]
        push  edx
        call FUN_0044bc10
        fstp  DWORD PTR [ebp+0x28]
        or   DWORD PTR [ebp+0x35c],esi
    loc_00440EB8:
        fld  DWORD PTR ds:0x470b04
        fld  DWORD PTR [ebp+0x38]
        fucompp
        fnstsw ax
        test  ah,0x44
        jnp loc_00440EE9
        fld  DWORD PTR ds:0x476f78
        mov  eax,DWORD PTR [ebp+0x2c]
        fmul  DWORD PTR [ebp+0x38]
        push  ecx
        fstp  DWORD PTR [esp]
        push  eax
        call FUN_0044bc10
        fstp  DWORD PTR [ebp+0x2c]
        or   DWORD PTR [ebp+0x35c],esi
    loc_00440EE9:
        fld  DWORD PTR ds:0x470b04
        fld  DWORD PTR [ebp+0x48]
        fucompp
        fnstsw ax
        test  ah,0x44
        jnp loc_00440F19
        fld  DWORD PTR ds:0x476f78
        mov  eax,DWORD PTR [ebp+0x35c]
        fmul  DWORD PTR [ebp+0x48]
        or   eax,0x8
        mov  DWORD PTR [ebp+0x35c],eax
        fadd  DWORD PTR [ebp+0x40]
        fstp  DWORD PTR [ebp+0x40]
    loc_00440F19:
        fld  DWORD PTR ds:0x470b04
        fld  DWORD PTR [ebp+0x44]
        fucompp
        fnstsw ax
        test  ah,0x44
        jnp loc_00440F49
        fld  DWORD PTR ds:0x476f78
        mov  eax,DWORD PTR [ebp+0x35c]
        fmul  DWORD PTR [ebp+0x44]
        or   eax,0xc
        mov  DWORD PTR [ebp+0x35c],eax
        fadd  DWORD PTR [ebp+0x3c]
        fstp  DWORD PTR [ebp+0x3c]
    loc_00440F49:
        fld  DWORD PTR ds:0x476f78
        fmul  DWORD PTR [ebp+0x234]
        fadd  DWORD PTR [ebp+0x54]
        fcom  DWORD PTR ds:0x470afc
        fst  DWORD PTR [ebp+0x54]
        fnstsw ax
        test  ah,0x1
        jne loc_00440F73
        fsub  DWORD PTR ds:0x470afc
        fstp  DWORD PTR [ebp+0x54]
        jmp loc_00440F8D
    loc_00440F73:
        fcom  DWORD PTR ds:0x470b04
        fnstsw ax
        test  ah,0x5
        jp loc_00440F8B
        fadd  DWORD PTR ds:0x470afc
        fstp  DWORD PTR [ebp+0x54]
        jmp loc_00440F8D
    loc_00440F8B:
        fstp  st(0)
    loc_00440F8D:
        fld  DWORD PTR ds:0x476f78
        fmul  DWORD PTR [ebp+0x238]
        fadd  DWORD PTR [ebp+0x58]
        fcom  DWORD PTR ds:0x470afc
        fst  DWORD PTR [ebp+0x58]
        fnstsw ax
        test  ah,0x1
        jne loc_00440FB7
        fsub  DWORD PTR ds:0x470afc
        fstp  DWORD PTR [ebp+0x58]
        jmp loc_00440FD1
    loc_00440FB7:
        fcom  DWORD PTR ds:0x470b04
        fnstsw ax
        test  ah,0x5
        jp loc_00440FCF
        fadd  DWORD PTR ds:0x470afc
        fstp  DWORD PTR [ebp+0x58]
        jmp loc_00440FD1
    loc_00440FCF:
        fstp  st(0)
    loc_00440FD1:
        mov  eax,DWORD PTR [ebp+0x35c]
        test  ah,0x20
        je loc_00441012
        fld  DWORD PTR ds:0x491e6c
        fadd  DWORD PTR [ebp+0x340]
        fstp  DWORD PTR [ebp+0x340]
        fld  DWORD PTR ds:0x491e70
        fadd  DWORD PTR [ebp+0x344]
        fstp  DWORD PTR [ebp+0x344]
        fld  DWORD PTR ds:0x491e74
        fadd  DWORD PTR [ebp+0x348]
        fstp  DWORD PTR [ebp+0x348]
    loc_00441012:
        mov  eax,DWORD PTR [ebp+0xb4]
        test  eax,eax
        je loc_00441056
        mov  eax,DWORD PTR [ebp+0x35c]
        test  ah,0x1
        lea  edi,[esp+0x18]
        lea  eax,[ebp+0x70]
        jne loc_0044103B
        call FUN_00404610
        lea  ecx,[ebp+0x334]
        jmp loc_00441046
    loc_0044103B:
        call FUN_00404610
        lea  ecx,[ebp+0x34c]
    loc_00441046:
        mov  edx,DWORD PTR [eax]
        mov  DWORD PTR [ecx],edx
        mov  edx,DWORD PTR [eax+0x4]
        mov  DWORD PTR [ecx+0x4],edx
        mov  eax,DWORD PTR [eax+0x8]
        mov  DWORD PTR [ecx+0x8],eax
    loc_00441056:
        mov  eax,DWORD PTR [ebp+0x100]
        test  eax,eax
        je loc_0044108E
        lea  ecx,[esp+0x18]
        push  ecx
        lea  eax,[ebp+0xbc]
        call FUN_00441600
        mov  dl,BYTE PTR [esp+0x20]
        mov  al,BYTE PTR [esp+0x1c]
        mov  cl,BYTE PTR [esp+0x18]
        mov  BYTE PTR [ebp+0x2fe],dl
        mov  BYTE PTR [ebp+0x2fd],al
        mov  BYTE PTR [ebp+0x2fc],cl
    loc_0044108E:
        mov  eax,DWORD PTR [ebp+0x12c]
        test  eax,eax
        je loc_004410A9
        lea  esi,[ebp+0x108]
        call FUN_00441950
        mov  BYTE PTR [ebp+0x2ff],al
    loc_004410A9:
        mov  eax,DWORD PTR [ebp+0x1b4]
        test  eax,eax
        je loc_004410D7
        lea  esi,[ebp+0x180]
        lea  edi,[esp+0x104]
        call FUN_00441ad0
        mov  edx,DWORD PTR [eax]
        mov  DWORD PTR [ebp+0x3c],edx
        mov  eax,DWORD PTR [eax+0x4]
        mov  DWORD PTR [ebp+0x40],eax
        or   DWORD PTR [ebp+0x35c],0x8
    loc_004410D7:
        mov  eax,DWORD PTR [ebp+0x178]
        test  eax,eax
        je loc_0044110A
        lea  eax,[ebp+0x134]
        lea  edi,[esp+0x18]
        call FUN_00404610
        mov  edx,DWORD PTR [eax]
        lea  ecx,[ebp+0x24]
        mov  DWORD PTR [ecx],edx
        mov  edx,DWORD PTR [eax+0x4]
        mov  DWORD PTR [ecx+0x4],edx
        mov  eax,DWORD PTR [eax+0x8]
        mov  DWORD PTR [ecx+0x8],eax
        or   DWORD PTR [ebp+0x35c],0x4
    loc_0044110A:
        mov  eax,DWORD PTR [ebp+0x200]
        test  eax,eax
        je loc_00441142
        lea  ecx,[esp+0x18]
        push  ecx
        lea  eax,[ebp+0x1bc]
        call FUN_00441600
        mov  dl,BYTE PTR [esp+0x20]
        mov  al,BYTE PTR [esp+0x1c]
        mov  cl,BYTE PTR [esp+0x18]
        mov  BYTE PTR [ebp+0x302],dl
        mov  BYTE PTR [ebp+0x301],al
        mov  BYTE PTR [ebp+0x300],cl
    loc_00441142:
        mov  eax,DWORD PTR [ebp+0x22c]
        test  eax,eax
        je loc_0044115D
        lea  esi,[ebp+0x208]
        call FUN_00441950
        mov  BYTE PTR [ebp+0x303],al
    loc_0044115D:
        mov  edx,DWORD PTR [ebp+0x35c]
        and  edx,0x3c00000
        cmp  edx,0x2400000
        jne loc_0044133E
        mov  eax,DWORD PTR [ebp+0x30c]
        lea  esi,[eax-0x1]
        test  esi,esi
        mov  DWORD PTR [esp+0x28],esi
        fild  DWORD PTR [esp+0x28]
        fld  DWORD PTR ds:0x470b14
        mov  ecx,DWORD PTR [ebp+0x2c]
        mov  ebx,DWORD PTR [ebp+0x358]
        fdiv  st,st(1)
        mov  DWORD PTR [esp+0x2c],ecx
        mov  DWORD PTR [esp+0x10],0x0
        fstp  DWORD PTR [esp+0x28]
        fild  DWORD PTR [ebp+0x310]
        fdiv  st,st(1)
        fstp  DWORD PTR [esp+0x34]
        fstp  st(0)
        jle loc_00441308
        mov  edi,DWORD PTR [esp+0x28]
        jmp loc_004411D0
        nop
        lea  ebx,[ebx+0x0]
    loc_004411D0:
        mov  DWORD PTR [ebx+0xc],0x3f800000
        mov  edx,DWORD PTR [ebp+0x2fc]
        mov  DWORD PTR [ebx+0x10],edx
        mov  eax,DWORD PTR [ebp+0x394]
        fld  DWORD PTR [eax+0x20]
        mov  edx,DWORD PTR [esp+0x2c]
        fadd  DWORD PTR [ebp+0x54]
        push  ecx
        mov  ecx,ebx
        fstp  DWORD PTR [ebx+0x14]
        fld  DWORD PTR [esp+0x14]
        fadd  DWORD PTR [ebp+0x58]
        fstp  DWORD PTR [ebx+0x18]
        fld  DWORD PTR [ebp+0x3c]
        fmul  DWORD PTR ds:0x470b0c
        fadd  DWORD PTR [ebp+0x40]
        fstp  DWORD PTR [esp]
        push  edx
        call FUN_00441ef0
        mov  DWORD PTR [ebx+0x8],0x0
        fld  DWORD PTR [ebp+0x340]
        fadd  DWORD PTR [ebp+0x334]
        add  ebx,0x1c
        fld  DWORD PTR [ebp+0x344]
        fadd  DWORD PTR [ebp+0x338]
        fstp  DWORD PTR [esp+0x1c]
        fld  DWORD PTR [ebp+0x348]
        fadd  DWORD PTR [ebp+0x33c]
        fxch  st(1)
        fadd  DWORD PTR [ebx-0x1c]
        fstp  DWORD PTR [ebx-0x1c]
        fld  DWORD PTR [esp+0x1c]
        fadd  DWORD PTR [ebx-0x18]
        fstp  DWORD PTR [ebx-0x18]
        fstp  DWORD PTR [ebx-0x14]
        mov  DWORD PTR [ebx+0xc],0x3f800000
        mov  ecx,DWORD PTR [ebp+0x2fc]
        mov  DWORD PTR [ebx+0x10],ecx
        mov  eax,DWORD PTR [ebp+0x394]
        fld  DWORD PTR [eax+0x28]
        push  ecx
        fadd  DWORD PTR [ebp+0x54]
        mov  ecx,ebx
        fstp  DWORD PTR [ebx+0x14]
        fld  DWORD PTR [esp+0x14]
        fadd  DWORD PTR [ebp+0x58]
        fstp  DWORD PTR [ebx+0x18]
        fld  DWORD PTR [ebp+0x3c]
        fmul  DWORD PTR ds:0x470b0c
        fsubr DWORD PTR [ebp+0x40]
        fstp  DWORD PTR [esp]
        push  edx
        call FUN_00441ef0
        mov  DWORD PTR [ebx+0x8],0x0
        fld  DWORD PTR [ebp+0x340]
        fadd  DWORD PTR [ebp+0x334]
        push  edi
        fld  DWORD PTR [ebp+0x344]
        push  edx
        fadd  DWORD PTR [ebp+0x338]
        add  ebx,0x1c
        fstp  DWORD PTR [esp+0xe4]
        fld  DWORD PTR [ebp+0x33c]
        fadd  DWORD PTR [ebp+0x348]
        fxch  st(1)
        fadd  DWORD PTR [ebx-0x1c]
        fstp  DWORD PTR [ebx-0x1c]
        fld  DWORD PTR [esp+0xe4]
        fadd  DWORD PTR [ebx-0x18]
        fstp  DWORD PTR [ebx-0x18]
        fstp  DWORD PTR [ebx-0x14]
        fld  DWORD PTR [esp+0x3c]
        fadd  DWORD PTR [esp+0x18]
        fstp  DWORD PTR [esp+0x18]
        call FUN_0044bc10
        dec  esi
        fstp  DWORD PTR [esp+0x2c]
        jne loc_004411D0
    loc_00441308:
        mov  esi,DWORD PTR [ebp+0x358]
        fld  DWORD PTR [esp+0x10]
        mov  ecx,0x7
        mov  edi,ebx
        rep movsd
        fadd  DWORD PTR [ebp+0x58]
        fstp  DWORD PTR [ebx+0x18]
        fld  DWORD PTR [esp+0x10]
        mov  esi,DWORD PTR [ebp+0x358]
        add  esi,0x1c
        lea  edi,[ebx+0x1c]
        mov  ecx,0x7
        rep movsd
        fadd  DWORD PTR [ebp+0x58]
        fstp  DWORD PTR [ebx+0x34]
    loc_0044133E:
        mov  edx,DWORD PTR [ebp+0x60]
        mov  ecx,DWORD PTR [ebp+0x68]
        mov  DWORD PTR [ebp+0x5c],edx
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b68
        fnstsw ax
        test  ah,0x41
        jne loc_00441377
        fld  DWORD PTR [ecx]
        fcomp DWORD PTR ds:0x470b64
        fnstsw ax
        test  ah,0x5
        jp loc_00441377
        fld  DWORD PTR [ebp+0x64]
        inc  edx
        fadd  DWORD PTR ds:0x470afc
        mov  DWORD PTR [ebp+0x60],edx
        fstp  DWORD PTR [ebp+0x64]
        jmp loc_00441387
    loc_00441377:
        fld  DWORD PTR [ecx]
        fadd  DWORD PTR [ebp+0x64]
        fst  DWORD PTR [ebp+0x64]
        call FUN_00463b2c
        mov  DWORD PTR [ebp+0x60],eax
    loc_00441387:
        mov  ecx,DWORD PTR [esp+0xa4]
        pop  edi
        pop  esi
        pop  ebx
        mov  DWORD PTR ds:0x476f78,ecx
        xor  eax,eax
        pop  ebp
        add  esp,0xfc
        ret  0x4
    }
}
