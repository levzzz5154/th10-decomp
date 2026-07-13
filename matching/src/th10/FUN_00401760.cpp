// 00401760: FUN_00401760
// Original size: 752 bytes, actual code: 181 instructions
extern "C" void FUN_004215a0(void);
extern "C" void FUN_00442f50(void);
extern "C" void FUN_00443080(void);

extern "C" __declspec(naked) void FUN_00401760(void) {
    __asm {
        sub  esp,0x10
        push  ebx
        push  ebp
        mov  ebp,DWORD PTR [esp+0x1c]
        mov  eax,DWORD PTR [ebp+0x370]
        and  eax,0xffd7ffff
        or   eax,0x140001
        mov  DWORD PTR [ebp+0x370],eax
        mov  eax,DWORD PTR [ebp+0x896c]
        test  eax,eax
        push  esi
        push  edi
        mov  DWORD PTR [esp+0x10],0x1
        lea  ebx,[ebp+0x76c]
        mov  DWORD PTR [esp+0x1c],0x0
        jle loc_004019E9
    loc_004017A5:
        lea  eax,[ebx+0x40]
        mov  ecx,eax
        mov  edx,DWORD PTR [ecx]
        lea  eax,[ebp+0x348]
        mov  DWORD PTR [eax],edx
        mov  edx,DWORD PTR [ecx+0x4]
        mov  DWORD PTR [eax+0x4],edx
        mov  ecx,DWORD PTR [ecx+0x8]
        mov  DWORD PTR [eax+0x8],ecx
        fld  DWORD PTR [ebx+0x54]
        mov  ecx,DWORD PTR [ebp+0x370]
        mov  edx,DWORD PTR [ebx+0x50]
        fstp  DWORD PTR [ebp+0x54]
        or   ecx,0x8
        mov  DWORD PTR [ebp+0x50],edx
        mov  DWORD PTR [ebp+0x370],ecx
        cmp  DWORD PTR [ebx+0x60],0x1
        mov  edi,ebx
        mov  DWORD PTR [esp+0x14],edi
        jne loc_004017F9
        mov  DWORD PTR [esp+0x24],0x40e00000
        mov  DWORD PTR [esp+0x18],0x41100000
        jmp loc_0040180E
    loc_004017F9:
        fild  DWORD PTR [ebp+0x898c]
        mov  DWORD PTR [esp+0x18],0x41600000
        fmul  DWORD PTR [ebx+0x50]
        fstp  DWORD PTR [esp+0x24]
    loc_0040180E:
        mov  eax,DWORD PTR [ebx+0x5c]
        cmp  DWORD PTR [esp+0x10],eax
        je loc_004018A0
        mov  esi,DWORD PTR ds:0x491c10
        mov  edi,eax
        mov  DWORD PTR [esp+0x10],edi
        call FUN_00442f50
        test  edi,edi
        je loc_00401867
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
        jmp loc_0040189C
    loc_00401867:
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
    loc_0040189C:
        mov  edi,DWORD PTR [esp+0x14]
    loc_004018A0:
        cmp  BYTE PTR [ebx],0x0
        je loc_004019C7
        nop
    loc_004018B0:
        mov  al,BYTE PTR [edi]
        cmp  al,0xa
        jne loc_004018D7
        fld  DWORD PTR [esp+0x18]
        fmul  DWORD PTR [ebx+0x54]
        fadd  DWORD PTR [ebp+0x34c]
        fstp  DWORD PTR [ebp+0x34c]
        mov  eax,DWORD PTR [ebx+0x40]
        mov  DWORD PTR [ebp+0x348],eax
        jmp loc_004019BB
    loc_004018D7:
        cmp  al,0x20
        je loc_004019AB
        mov  ecx,DWORD PTR [ebx+0x60]
        imul  ecx,ecx,0x62
        movzx edx,al
        lea  eax,[ecx+edx*1-0x20]
        mov  ecx,DWORD PTR [ebp+0x8994]
        imul  eax,eax,0x44
        mov  edx,DWORD PTR [ecx+0x118]
        add  eax,edx
        mov  DWORD PTR [ebp+0x3a8],eax
        mov  ecx,DWORD PTR [ebp+0x370]
        fld  DWORD PTR [eax+0x30]
        mov  eax,DWORD PTR [eax+0x34]
        lea  esi,[ebp+0x14]
        or   ecx,0x8
        mov  DWORD PTR [esi+0x4c],eax
        fstp  DWORD PTR [esi+0x50]
        mov  DWORD PTR [esi+0x35c],ecx
        mov  eax,DWORD PTR [ebx+0x64]
        test  eax,eax
        je loc_00401996
        mov  ecx,DWORD PTR [ebx+0x4c]
        fld  DWORD PTR [ebp+0x348]
        fadd  DWORD PTR ds:0x470b08
        mov  eax,ds:0x491c10
        and  ecx,0xff000000
        mov  DWORD PTR [ebp+0x310],ecx
        mov  edx,DWORD PTR [ebx+0x4c]
        fstp  DWORD PTR [ebp+0x348]
        fld  DWORD PTR [ebp+0x34c]
        shr  edx,0x19
        fadd  DWORD PTR ds:0x470b08
        push  eax
        mov  BYTE PTR [ebp+0x313],dl
        fstp  DWORD PTR [ebp+0x34c]
        call FUN_00443080
        fld  DWORD PTR [ebp+0x348]
        fsub  DWORD PTR ds:0x470b08
        fstp  DWORD PTR [ebp+0x348]
        fld  DWORD PTR [ebp+0x34c]
        fsub  DWORD PTR ds:0x470b08
        fstp  DWORD PTR [ebp+0x34c]
    loc_00401996:
        mov  edx,DWORD PTR ds:0x491c10
        mov  ecx,DWORD PTR [ebx+0x4c]
        push  edx
        mov  DWORD PTR [ebp+0x310],ecx
        call FUN_00443080
    loc_004019AB:
        fld  DWORD PTR [esp+0x24]
        fadd  DWORD PTR [ebp+0x348]
        fstp  DWORD PTR [ebp+0x348]
    loc_004019BB:
        mov  al,BYTE PTR [edi+0x1]
        inc  edi
        test  al,al
        jne loc_004018B0
    loc_004019C7:
        mov  eax,DWORD PTR [esp+0x1c]
        mov  ecx,DWORD PTR [ebp+0x896c]
        inc  eax
        add  ebx,0x68
        cmp  eax,ecx
        mov  DWORD PTR [esp+0x1c],eax
        jl loc_004017A5
        mov  eax,DWORD PTR [esp+0x10]
        test  eax,eax
        je loc_00401A33
    loc_004019E9:
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
        pop  esi
        mov  eax,0x1
        pop  ebp
        mov  ds:0x491fb0,eax
        pop  ebx
        add  esp,0x10
        ret  0x4
    loc_00401A33:
        pop  edi
        pop  esi
        pop  ebp
        mov  eax,0x1
        pop  ebx
        add  esp,0x10
        ret  0x4
    }
}
