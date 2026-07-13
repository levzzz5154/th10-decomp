// 004172E0: FUN_004172e0
// Original size: 768 bytes, actual code: 193 instructions
extern "C" void FUN_0043e5a0(void);
extern "C" void FUN_004489d0(void);
extern "C" void FUN_00448d00(void);
extern "C" void FUN_004491c0(void);
extern "C" void FUN_004492a0(void);
extern "C" void FUN_00449590(void);
extern "C" void FUN_004495e0(void);
extern "C" void FUN_00449870(void);
extern "C" void FUN_00449950(void);

extern "C" __declspec(naked) void FUN_004172e0(void) {
    __asm {
        sub  esp,0x28
        cmp  eax,0x6
        push  ebp
        mov  ebp,DWORD PTR [esp+0x30]
        ja loc_00417559
        push  edi
        jmp  DWORD PTR [eax*4+0x417560]
        mov  eax,DWORD PTR [ebp+0x9e14]
        mov  edx,DWORD PTR ds:0x491c10
        push  ebx
        push  esi
        push  eax
        call FUN_004492a0
        xor  esi,esi
        push  0xf
        mov  DWORD PTR [ebp+0x9e14],esi
        mov  ecx,DWORD PTR [ebp+0x9ec8]
        push  0x47
        push  ecx
        lea  edi,[esp+0x2c]
        call FUN_00448d00
        mov  edx,DWORD PTR [eax]
        mov  eax,DWORD PTR [esp+0x40]
        mov  DWORD PTR [esp+0x10],esi
        mov  DWORD PTR [esp+0x40],esi
        mov  esi,DWORD PTR ds:0x491c10
        mov  DWORD PTR [ebp+0x9e14],edx
        mov  DWORD PTR [esp+0x14],eax
        mov  DWORD PTR [esp+0x3c],0x989680
        lea  edi,[ebp+0x9df4]
    loc_00417355:
        mov  ecx,DWORD PTR [edi]
        push  ecx
        mov  edx,esi
        call FUN_004492a0
        mov  DWORD PTR [edi],0x0
        mov  edx,DWORD PTR [ebp+0x9ec8]
        mov  DWORD PTR [esp+0x18],edx
        call FUN_00449950
        mov  ecx,DWORD PTR [esp+0x18]
        mov  ebx,eax
        mov  eax,DWORD PTR [esp+0x40]
        mov  esi,DWORD PTR [ebx+0x35c]
        add  eax,0x27
        push  eax
        or   esi,0x40000000
        push  ebx
        mov  DWORD PTR [ebx+0x20],0xf
        mov  DWORD PTR [ebx+0x35c],esi
        call FUN_00449870
        mov  esi,DWORD PTR ds:0x491c10
        lea  eax,[esp+0x1c]
        mov  edx,esi
        call FUN_004489d0
        mov  eax,DWORD PTR [esp+0x14]
        cdq
        idiv  DWORD PTR [esp+0x3c]
        mov  ecx,DWORD PTR [esp+0x1c]
        mov  DWORD PTR [edi],ecx
        mov  ebx,eax
        test  ebx,ebx
        mov  DWORD PTR [esp+0x18],edx
        je loc_004173D3
        mov  DWORD PTR [esp+0x10],0x1
    loc_004173D3:
        push  ecx
        mov  edx,esi
        call FUN_004491c0
        test  eax,eax
        je loc_004173ED
        mov  ecx,DWORD PTR [eax+0x308]
        lea  edx,[ebx+0x8]
        call FUN_0043e5a0
    loc_004173ED:
        mov  eax,DWORD PTR [esp+0x10]
        test  eax,eax
        mov  eax,edi
        jne loc_004173FE
        call FUN_004495e0
        jmp loc_00417403
    loc_004173FE:
        call FUN_00449590
    loc_00417403:
        mov  ecx,DWORD PTR [esp+0x18]
        mov  eax,0x66666667
        imul  DWORD PTR [esp+0x3c]
        sar  edx,0x2
        mov  eax,edx
        shr  eax,0x1f
        add  eax,edx
        mov  DWORD PTR [esp+0x3c],eax
        mov  eax,DWORD PTR [esp+0x40]
        inc  eax
        add  edi,0x4
        cmp  eax,0x8
        mov  DWORD PTR [esp+0x14],ecx
        mov  DWORD PTR [esp+0x40],eax
        jl loc_00417355
        pop  esi
        pop  ebx
        pop  edi
        pop  ebp
        add  esp,0x28
        ret  0x8
        mov  ecx,DWORD PTR [ebp+0x9e14]
        mov  edx,DWORD PTR ds:0x491c10
        push  ecx
        call FUN_004492a0
        push  0xf
        push  0x48
        lea  edi,[esp+0x24]
        jmp loc_0041753A
        mov  ecx,DWORD PTR [ebp+0x9e18]
        mov  edx,DWORD PTR ds:0x491c10
        push  ecx
        call FUN_004492a0
        push  0xf
        mov  DWORD PTR [ebp+0x9e18],0x0
        mov  edx,DWORD PTR [ebp+0x9ec8]
        push  0x49
        push  edx
        lea  edi,[esp+0x2c]
        call FUN_00448d00
        mov  eax,DWORD PTR [eax]
        pop  edi
        mov  DWORD PTR [ebp+0x9e18],eax
        pop  ebp
        add  esp,0x28
        ret  0x8
        mov  ecx,DWORD PTR [ebp+0x9e18]
        mov  edx,DWORD PTR ds:0x491c10
        push  ecx
        call FUN_004492a0
        push  0xf
        mov  DWORD PTR [ebp+0x9e18],0x0
        mov  edx,DWORD PTR [ebp+0x9ec8]
        push  0x4a
        push  edx
        lea  edi,[esp+0x30]
        call FUN_00448d00
        mov  eax,DWORD PTR [eax]
        pop  edi
        mov  DWORD PTR [ebp+0x9e18],eax
        pop  ebp
        add  esp,0x28
        ret  0x8
        mov  ecx,DWORD PTR [ebp+0x9e18]
        mov  edx,DWORD PTR ds:0x491c10
        push  ecx
        call FUN_004492a0
        push  0xf
        mov  DWORD PTR [ebp+0x9e18],0x0
        mov  edx,DWORD PTR [ebp+0x9ec8]
        push  0x4b
        push  edx
        lea  edi,[esp+0x34]
        call FUN_00448d00
        mov  eax,DWORD PTR [eax]
        pop  edi
        mov  DWORD PTR [ebp+0x9e18],eax
        pop  ebp
        add  esp,0x28
        ret  0x8
        mov  ecx,DWORD PTR [ebp+0x9e14]
        mov  edx,DWORD PTR ds:0x491c10
        push  ecx
        call FUN_004492a0
        push  0xf
        push  0x4c
        lea  edi,[esp+0x34]
    loc_0041753A:
        mov  DWORD PTR [ebp+0x9e14],0x0
        mov  edx,DWORD PTR [ebp+0x9ec8]
        push  edx
        call FUN_00448d00
        mov  eax,DWORD PTR [eax]
        mov  DWORD PTR [ebp+0x9e14],eax
        pop  edi
    loc_00417559:
        pop  ebp
        add  esp,0x28
        ret  0x8
        stc
        jb loc_004175A4
        add  BYTE PTR [ecx+0x74],al
        inc  ecx
        add  BYTE PTR [eax+0x74],ah
        inc  ecx
        add  BYTE PTR [eax-0x1fffbe8c],ah
        je loc_004175B4
        add  BYTE PTR [eax+0x75],bl
        inc  ecx
        add  BYTE PTR [eax],ah
        jne loc_004175BC
        add  ah,cl
        int3
        int3
        int3
        mov  DWORD PTR [eax+0x5c],ecx
        ret
    }
}
