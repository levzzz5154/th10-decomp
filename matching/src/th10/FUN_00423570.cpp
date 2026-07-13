// 00423570: FUN_00423570
// Original size: 384 bytes, actual code: 106 instructions
extern "C" void FUN_00421fa0(void);
extern "C" void FUN_0044bea0(void);

extern "C" __declspec(naked) void FUN_00423570(void) {
    __asm {
        mov  eax,ds:0x474c7c
        push  ebp
        mov  ebp,DWORD PTR [esp+0x8]
        push  esi
        mov  esi,0x7
        cmp  eax,esi
        push  edi
        jne loc_004235A8
        mov  eax,DWORD PTR [ebp+0x1e4]
        test  eax,eax
        je loc_004235A8
        mov  eax,0x8
        mov  DWORD PTR ds:0x477848,0x474908
        mov  ds:0x474c7c,eax
        mov  ds:0x474c80,eax
    loc_004235A8:
        mov  eax,ds:0x474c68
        mov  ecx,DWORD PTR ds:0x474c6c
        lea  edx,[ecx+eax*2]
        add  edx,eax
        mov  eax,ds:0x47783c
        imul  edx,edx,0x437c
        lea  edi,[edx+eax*1+0x8]
        call FUN_00421fa0
        cmp  DWORD PTR ds:0x474c7c,esi
        jne loc_004235F4
        mov  ecx,DWORD PTR [ebp+0x1e4]
        test  ecx,ecx
        je loc_004235F4
        mov  DWORD PTR ds:0x477848,0x4748d8
        mov  DWORD PTR ds:0x474c7c,esi
        mov  DWORD PTR ds:0x474c80,esi
    loc_004235F4:
        test  eax,eax
        jl loc_004236D9
        mov  esi,0x1
        mov  DWORD PTR [ebp+0x2c],0x19
        mov  DWORD PTR [ebp+0xf4],esi
        mov  ecx,DWORD PTR [ebp+0x2c]
        test  ecx,ecx
        je loc_0042361C
        cmp  eax,ecx
        jl loc_0042361C
        lea  eax,[ecx-0x1]
    loc_0042361C:
        push  ebx
        lea  ebx,[ebp+0xfc]
        mov  DWORD PTR [ebp+0x24],eax
        mov  eax,DWORD PTR [ebx+0x8]
        test  eax,eax
        je loc_0042363A
        jg loc_00423634
        dec  eax
        mov  DWORD PTR [ebx],eax
        jmp loc_00423640
    loc_00423634:
        xor  eax,eax
        mov  DWORD PTR [ebx],eax
        jmp loc_00423640
    loc_0042363A:
        mov  DWORD PTR [ebx],0x0
    loc_00423640:
        mov  ecx,DWORD PTR ds:0x4746d8
        lea  edx,[ecx+0x1]
        nop
    loc_00423650:
        mov  al,BYTE PTR [ecx]
        inc  ecx
        test  al,al
        jne loc_00423650
        sub  ecx,edx
        mov  DWORD PTR [ebp+0x104],ecx
        mov  ecx,DWORD PTR ds:0x47783c
        mov  DWORD PTR [ebp+0x1cc],esi
        lea  esi,[ebp+0x2b4]
        add  ecx,0x1d878
        mov  edx,esi
        sub  edx,ecx
        jmp loc_00423680
        nop
    loc_00423680:
        mov  al,BYTE PTR [ecx]
        mov  BYTE PTR [edx+ecx*1],al
        inc  ecx
        test  al,al
        jne loc_00423680
        mov  edi,0x46e354
        mov  ecx,0x9
        xor  edx,edx
        mov  DWORD PTR [ebp+0x1e0],0x0
        repz cmps BYTE PTR ds:[esi],BYTE PTR es:[edi]
        je loc_004236AD
        push  0xffffffff
        mov  eax,ebx
        call FUN_0044bea0
    loc_004236AD:
        mov  eax,0x8
        mov  cl,0x20
        pop  ebx
    loc_004236B5:
        cmp  BYTE PTR [eax+ebp*1+0x2b3],cl
        jne loc_004236C3
        dec  eax
        test  eax,eax
        jg loc_004236B5
    loc_004236C3:
        pop  edi
        pop  esi
        mov  DWORD PTR [ebp+0x1e0],eax
        mov  DWORD PTR [ebp+0x1e8],0x0
        pop  ebp
        ret  0x4
    loc_004236D9:
        pop  edi
        pop  esi
        mov  DWORD PTR [ebp+0x1e8],0x1
        pop  ebp
        ret  0x4
    }
}
