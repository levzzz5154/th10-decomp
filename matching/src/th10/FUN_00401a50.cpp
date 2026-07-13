// 00401A50: FUN_00401a50
// Original size: 720 bytes, actual code: 149 instructions
extern "C" void FUN_004215a0(void);
extern "C" void FUN_00442f50(void);
extern "C" void FUN_00443080(void);
extern "C" void FUN_00443290(void);

extern "C" __declspec(naked) void FUN_00401a50(void) {
    __asm {
        sub  esp,0x10
        mov  eax,DWORD PTR [ebx+0x370]
        and  eax,0xffd7ffff
        or   eax,0x140001
        push  ebp
        mov  DWORD PTR [ebx+0x370],eax
        mov  eax,DWORD PTR [ebx+0x8970]
        test  eax,eax
        push  esi
        push  edi
        mov  DWORD PTR [esp+0xc],0x1
        lea  ebp,[ebx+0x6f6c]
        mov  DWORD PTR [esp+0x18],0x0
        jle loc_00401C37
    loc_00401A90:
        lea  eax,[ebp+0x40]
        mov  ecx,eax
        mov  edx,DWORD PTR [ecx]
        lea  eax,[ebx+0x348]
        mov  DWORD PTR [eax],edx
        mov  edx,DWORD PTR [ecx+0x4]
        mov  DWORD PTR [eax+0x4],edx
        mov  ecx,DWORD PTR [ecx+0x8]
        mov  DWORD PTR [eax+0x8],ecx
        fld  DWORD PTR [ebp+0x54]
        mov  edx,DWORD PTR [ebp+0x50]
        fstp  DWORD PTR [ebx+0x54]
        mov  ecx,DWORD PTR [esp+0xc]
        mov  DWORD PTR [ebx+0x50],edx
        mov  edx,DWORD PTR [ebx+0x370]
        or   edx,0x8
        mov  DWORD PTR [ebx+0x370],edx
        fild  DWORD PTR [ebx+0x898c]
        mov  eax,DWORD PTR [ebp+0x5c]
        cmp  ecx,eax
        fmul  DWORD PTR [ebp+0x50]
        mov  edi,ebp
        mov  DWORD PTR [esp+0x10],edi
        fstp  DWORD PTR [esp+0x14]
        je loc_00401B6D
        mov  esi,DWORD PTR ds:0x491c10
        mov  edi,eax
        mov  DWORD PTR [esp+0xc],edi
        call FUN_00442f50
        test  edi,edi
        je loc_00401B34
        mov  edi,0x491d7c
        mov  DWORD PTR ds:0x491fac,edi
        call FUN_004215a0
        mov  edx,DWORD PTR ds:0x491fac
        mov  eax,ds:0x491c30
        mov  ecx,DWORD PTR [eax]
        add  edx,0xcc
        push  edx
        push  eax
        call  DWORD PTR [ecx+0xbc]
        mov  DWORD PTR ds:0x491fb0,0x0
        jmp loc_00401B69
    loc_00401B34:
        mov  edi,0x491e94
        mov  DWORD PTR ds:0x491fac,edi
        call FUN_004215a0
        mov  edx,DWORD PTR ds:0x491fac
        mov  eax,ds:0x491c30
        mov  ecx,DWORD PTR [eax]
        add  edx,0xcc
        push  edx
        push  eax
        call  DWORD PTR [ecx+0xbc]
        mov  DWORD PTR ds:0x491fb0,0x1
    loc_00401B69:
        mov  edi,DWORD PTR [esp+0x10]
    loc_00401B6D:
        cmp  BYTE PTR [ebp+0x0],0x0
        je loc_00401C15
    loc_00401B77:
        mov  al,BYTE PTR [edi]
        cmp  al,0xa
        jne loc_00401B9D
        fld  DWORD PTR [ebp+0x54]
        fmul  DWORD PTR ds:0x470c88
        fadd  DWORD PTR [ebx+0x34c]
        fstp  DWORD PTR [ebx+0x34c]
        mov  eax,DWORD PTR [ebp+0x40]
        mov  DWORD PTR [ebx+0x348],eax
        jmp loc_00401C09
    loc_00401B9D:
        cmp  al,0x20
        je loc_00401BF9
        mov  edx,DWORD PTR [ebx+0x8994]
        fld  DWORD PTR ds:0x470afc
        fld  DWORD PTR [ebx+0x50]
        movzx ecx,al
        mov  eax,DWORD PTR [edx+0x118]
        fucompp
        sub  ecx,0x20
        imul  ecx,ecx,0x44
        add  ecx,eax
        mov  DWORD PTR [ebx+0x3a8],ecx
        mov  eax,DWORD PTR [ebp+0x4c]
        mov  DWORD PTR [ebx+0x310],eax
        fnstsw ax
        test  ah,0x44
        jnp loc_00401BEA
        mov  ecx,DWORD PTR ds:0x491c10
        push  ecx
        lea  eax,[ebx+0x14]
        call FUN_00443290
        jmp loc_00401BF9
    loc_00401BEA:
        mov  edx,DWORD PTR ds:0x491c10
        push  edx
        lea  esi,[ebx+0x14]
        call FUN_00443080
    loc_00401BF9:
        fld  DWORD PTR [esp+0x14]
        fadd  DWORD PTR [ebx+0x348]
        fstp  DWORD PTR [ebx+0x348]
    loc_00401C09:
        mov  al,BYTE PTR [edi+0x1]
        inc  edi
        test  al,al
        jne loc_00401B77
    loc_00401C15:
        mov  eax,DWORD PTR [esp+0x18]
        mov  ecx,DWORD PTR [ebx+0x8970]
        inc  eax
        add  ebp,0x68
        cmp  eax,ecx
        mov  DWORD PTR [esp+0x18],eax
        jl loc_00401A90
        mov  eax,DWORD PTR [esp+0xc]
        test  eax,eax
        je loc_00401C7E
    loc_00401C37:
        mov  esi,DWORD PTR ds:0x491c10
        call FUN_00442f50
        mov  edi,0x491e94
        mov  DWORD PTR ds:0x491fac,edi
        call FUN_004215a0
        mov  edx,DWORD PTR ds:0x491fac
        mov  eax,ds:0x491c30
        mov  ecx,DWORD PTR [eax]
        add  edx,0xcc
        push  edx
        push  eax
        call  DWORD PTR [ecx+0xbc]
        pop  edi
        mov  eax,0x1
        pop  esi
        mov  ds:0x491fb0,eax
        pop  ebp
        add  esp,0x10
        ret
    loc_00401C7E:
        pop  edi
        pop  esi
        mov  eax,0x1
        pop  ebp
        add  esp,0x10
        ret
    }
}
