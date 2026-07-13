// 0040CFB0: FUN_0040cfb0
// Original size: 720 bytes, actual code: 213 instructions
extern "C" void FUN_0040d830(void);
extern "C" void FUN_0040dc80(void);
extern "C" void operator_new(void);

extern "C" __declspec(naked) void FUN_0040cfb0(void) {
    __asm {
        push  ebx
        push  ebp
        push  esi
        push  edi
        push  0x2518
        mov  ebx,eax
        call operator_new
        add  esp,0x4
        test  eax,eax
        je loc_0040CFD7
        mov  ecx,DWORD PTR [esp+0x18]
        push  ecx
        mov  esi,eax
        call FUN_0040d830
        mov  ebp,eax
        jmp loc_0040CFD9
    loc_0040CFD7:
        xor  ebp,ebp
    loc_0040CFD9:
        mov  eax,ebx
        mov  ecx,DWORD PTR [eax]
        lea  edx,[ebp+0x1094]
        mov  DWORD PTR [edx],ecx
        mov  ecx,DWORD PTR [eax+0x4]
        mov  DWORD PTR [edx+0x4],ecx
        mov  eax,DWORD PTR [eax+0x8]
        mov  DWORD PTR [edx+0x8],eax
        mov  ecx,DWORD PTR [ebx+0xc]
        mov  DWORD PTR [ebp+0x23f8],ecx
        mov  edx,DWORD PTR [ebx+0x14]
        mov  DWORD PTR [ebp+0x23fc],edx
        mov  eax,DWORD PTR [ebx+0x10]
        mov  edx,DWORD PTR [ebp+0x2480]
        mov  DWORD PTR [ebp+0x2408],eax
        mov  ecx,DWORD PTR [ebx+0x18]
        shl  ecx,0xb
        xor  ecx,edx
        and  ecx,0x800
        mov  edi,edx
        xor  edi,ecx
        mov  DWORD PTR [ebp+0x2480],edi
        mov  ecx,DWORD PTR ds:0x474c74
        mov  dl,0x1
        shl  dl,cl
        lea  esi,[ebx+0x20]
        lea  edi,[ebp+0x1138]
        mov  ecx,0x8
        mov  BYTE PTR [ebp+0x1024],dl
        rep movsd
        mov  eax,DWORD PTR [ebp+0x2468]
        xor  edi,edi
        test  al,0x1
        jne loc_0040D07F
        or   eax,0x1
        mov  DWORD PTR [ebp+0x245c],edi
        mov  DWORD PTR [ebp+0x2458],0xfff0bdc1
        mov  DWORD PTR [ebp+0x2460],edi
        mov  DWORD PTR [ebp+0x2464],0x476f78
        mov  DWORD PTR [ebp+0x2468],eax
    loc_0040D07F:
        mov  DWORD PTR [ebp+0x245c],0x2
        mov  DWORD PTR [ebp+0x2460],0x40000000
        mov  esi,0x1
        mov  DWORD PTR [ebp+0x2458],esi
        mov  eax,DWORD PTR [ebx+0x1c]
        mov  edx,DWORD PTR [ebp+0x2480]
        shl  eax,0x12
        xor  eax,edx
        and  eax,0x40000
        mov  ebx,edx
        lea  ecx,[ebp+0x103c]
        xor  ebx,eax
        push  ecx
        mov  DWORD PTR [ebp+0x2480],ebx
        call FUN_0040dc80
        mov  eax,DWORD PTR [ebp+0x2480]
        test  ah,ah
        jns loc_0040D0F2
        mov  eax,DWORD PTR [ebp+0x2408]
        cmp  eax,esi
        jne loc_0040D0E2
        mov  eax,0xa
        jmp loc_0040D0EC
    loc_0040D0E2:
        cmp  eax,0x4
        jne loc_0040D0EC
        mov  eax,0xb
    loc_0040D0EC:
        mov  DWORD PTR [ebp+0x2408],eax
    loc_0040D0F2:
        mov  eax,DWORD PTR [esp+0x14]
        mov  edx,DWORD PTR [eax+0x64]
        mov  ecx,DWORD PTR [ebp+0x1128]
        and  edx,esi
        add  edx,0x2
        cmp  ecx,esi
        mov  DWORD PTR [ebp+0x2444],edx
        mov  edx,0x167
        mov  DWORD PTR [ebp+0x2448],edx
        jne loc_0040D15C
        mov  ecx,DWORD PTR [ebp+0x112c]
        cmp  ecx,0x34
        ja loc_0040D15C
        movzx ecx,BYTE PTR [ecx+0x40d1bc]
        jmp  DWORD PTR [ecx*4+0x40d1a8]
        mov  DWORD PTR [ebp+0x2448],edx
        jmp loc_0040D15C
        mov  DWORD PTR [ebp+0x2448],0x164
        jmp loc_0040D15C
        mov  DWORD PTR [ebp+0x2448],0x16d
        jmp loc_0040D15C
        mov  DWORD PTR [ebp+0x2448],0x16a
    loc_0040D15C:
        mov  DWORD PTR [ebp+0x244c],edi
        cmp  DWORD PTR [eax+0x58],edi
        lea  ecx,[ebp+0x116c]
        jne loc_0040D172
        mov  DWORD PTR [eax+0x58],ecx
        jmp loc_0040D18B
    loc_0040D172:
        mov  edx,DWORD PTR [eax+0x5c]
        mov  esi,DWORD PTR [edx+0x4]
        cmp  esi,edi
        je loc_0040D185
        mov  DWORD PTR [ecx+0x4],esi
        mov  esi,DWORD PTR [edx+0x4]
        mov  DWORD PTR [esi+0x8],ecx
    loc_0040D185:
        mov  DWORD PTR [edx+0x4],ecx
        mov  DWORD PTR [ecx+0x8],edx
    loc_0040D18B:
        mov  edx,DWORD PTR [eax+0x60]
        mov  DWORD PTR [eax+0x5c],ecx
        mov  ecx,DWORD PTR [eax+0x64]
        inc  edx
        pop  edi
        inc  ecx
        pop  esi
        mov  DWORD PTR [eax+0x60],edx
        mov  DWORD PTR [eax+0x64],ecx
        mov  eax,ebp
        pop  ebp
        pop  ebx
        ret  0x8
        nop
        xor  dl,cl
        inc  eax
        add  BYTE PTR [edx],bh
        rol  DWORD PTR [eax+0x0],1
        push  edx
        rol  DWORD PTR [eax+0x0],1
        inc  esi
        rol  DWORD PTR [eax+0x0],1
        pop  esp
        rol  DWORD PTR [eax+0x0],1
        add  BYTE PTR [esp+eax*1],al
        add  al,0x4
        add  DWORD PTR [esp+eax*1],eax
        add  al,0x4
        add  al,BYTE PTR [esp+eax*1]
        add  al,0x4
        add  eax,DWORD PTR [esp+eax*1]
        add  al,0x4
        add  BYTE PTR [esp+eax*1],al
        add  al,0x4
        add  DWORD PTR [esp+eax*1],eax
        add  al,0x4
        add  al,BYTE PTR [esp+eax*1]
        add  al,0x4
        add  eax,DWORD PTR [esp+eax*1]
        add  al,0x4
        add  al,0x4
        add  al,0x4
        add  al,0x4
        add  al,0x4
        add  al,0x0
        add  DWORD PTR [edx],eax
        add  ecx,esp
        int3
        int3
        int3
        int3
        int3
        int3
        int3
        int3
        int3
        int3
        int3
        int3
        int3
        int3
        push  esi
        mov  esi,DWORD PTR [ecx+0x58]
        lea  eax,[edx+0x116c]
        cmp  esi,eax
        push  edi
        jne loc_0040D218
        mov  esi,DWORD PTR [edx+0x1170]
        mov  DWORD PTR [ecx+0x58],esi
    loc_0040D218:
        cmp  DWORD PTR [ecx+0x5c],eax
        jne loc_0040D226
        mov  edx,DWORD PTR [edx+0x1174]
        mov  DWORD PTR [ecx+0x5c],edx
    loc_0040D226:
        mov  edx,DWORD PTR [eax+0x4]
        xor  esi,esi
        cmp  edx,esi
        je loc_0040D235
        mov  edi,DWORD PTR [eax+0x8]
        mov  DWORD PTR [edx+0x8],edi
    loc_0040D235:
        mov  edx,DWORD PTR [eax+0x8]
        cmp  edx,esi
        je loc_0040D242
        mov  edi,DWORD PTR [eax+0x4]
        mov  DWORD PTR [edx+0x4],edi
    loc_0040D242:
        mov  DWORD PTR [eax+0x4],esi
        mov  DWORD PTR [eax+0x8],esi
        mov  eax,DWORD PTR [ecx+0x60]
        dec  eax
        pop  edi
        mov  DWORD PTR [ecx+0x60],eax
        pop  esi
        ret
    }
}
