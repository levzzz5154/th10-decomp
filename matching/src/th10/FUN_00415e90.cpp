// 00415E90: FUN_00415e90
// Original size: 4480 bytes, actual code: 1219 instructions
extern "C" void FUN_00404ed0(void);
extern "C" void FUN_00405410(void);
extern "C" void FUN_00409d90(void);
extern "C" void FUN_00409e50(void);
extern "C" void FUN_0040ac90(void);
extern "C" void FUN_0040c480(void);
extern "C" void FUN_0040c4d0(void);
extern "C" void FUN_00417010(void);
extern "C" void FUN_004175e0(void);
extern "C" void FUN_00420b10(void);
extern "C" void FUN_00420c30(void);
extern "C" void FUN_00423370(void);
extern "C" void FUN_0043c8b0(void);
extern "C" void FUN_0043dc90(void);
extern "C" void FUN_00447a50(void);
extern "C" void FUN_00448d00(void);
extern "C" void FUN_004491c0(void);
extern "C" void FUN_004492a0(void);
extern "C" void FUN_004492f0(void);
extern "C" void FUN_00449470(void);
extern "C" void FUN_00449670(void);
extern "C" void FUN_004496a0(void);
extern "C" void FUN_004497d0(void);
extern "C" void FUN_0044bf40(void);

extern "C" __declspec(naked) void FUN_00415e90(void) {
    __asm {
        sub  esp,0xd8
        push  ebx
        push  ebp
        mov  ebp,DWORD PTR [esp+0xe4]
        mov  eax,DWORD PTR [ebp+0x78]
        xor  edx,edx
        cmp  eax,edx
        push  esi
        push  edi
        jle loc_00415EAE
        dec  eax
        mov  DWORD PTR [ebp+0x78],eax
    loc_00415EAE:
        test  BYTE PTR [ebp+0x7c],0x1
        je loc_00415EF7
        mov  eax,ds:0x474e5c
        test  ah,0x1
        je loc_00415EF7
        mov  eax,DWORD PTR [ebp+0x5c]
        movzx ecx,WORD PTR [eax]
        mov  eax,DWORD PTR [ebp+0x28]
        test  al,0x1
        mov  DWORD PTR [esp+0x10],ecx
        jne loc_00415EE9
        or   eax,0x1
        mov  DWORD PTR [ebp+0x1c],edx
        mov  DWORD PTR [ebp+0x18],0xfff0bdc1
        mov  DWORD PTR [ebp+0x20],edx
        mov  DWORD PTR [ebp+0x24],0x476f78
        mov  DWORD PTR [ebp+0x28],eax
    loc_00415EE9:
        fild  DWORD PTR [esp+0x10]
        mov  DWORD PTR [ebp+0x1c],ecx
        dec  ecx
        mov  DWORD PTR [ebp+0x18],ecx
        fstp  DWORD PTR [ebp+0x20]
    loc_00415EF7:
        mov  ecx,DWORD PTR [ebp+0x5c]
        movzx edx,WORD PTR [ecx]
        cmp  DWORD PTR [ebp+0x1c],edx
        jl loc_00416F25
    loc_00415F06:
        mov  eax,DWORD PTR [ebp+0x5c]
        movzx ecx,BYTE PTR [eax+0x2]
        cmp  ecx,0x17
        ja loc_00416F09
        jmp  DWORD PTR [ecx*4+0x416f64]
        lea  edi,[ebp+0x4c]
        jmp loc_00415F25
        lea  edi,[ebp+0x50]
    loc_00415F25:
        mov  eax,DWORD PTR [edi]
        mov  ebx,DWORD PTR ds:0x491c10
        mov  edx,ebx
        push  eax
        call FUN_004491c0
        mov  esi,eax
        test  esi,esi
        jne loc_00415F3D
        mov  DWORD PTR [edi],eax
    loc_00415F3D:
        mov  eax,DWORD PTR [ebp+0x5c]
        add  eax,0x4
        call FUN_00417010
        mov  ecx,DWORD PTR [ebp+0x84]
        mov  edx,DWORD PTR [ebp+ecx*4+0x88]
        push  eax
        push  edx
        push  ebx
        call FUN_00447a50
        add  esp,0xc
        mov  eax,edi
        call FUN_0040c480
        jmp loc_00416F09
        mov  eax,DWORD PTR [ebp+0x80]
        test  eax,eax
        jne loc_00416041
        mov  eax,DWORD PTR [ebp+0x4c]
        mov  esi,DWORD PTR ds:0x491c10
        lea  edi,[ebp+0x4c]
        push  eax
        mov  edx,esi
        call FUN_004491c0
        test  eax,eax
        jne loc_00415F94
        mov  DWORD PTR [edi],eax
    loc_00415F94:
        mov  ecx,DWORD PTR [ebp+0x84]
        mov  edx,DWORD PTR [ebp+ecx*4+0x88]
        push  0x46cfd4
        push  edx
        push  esi
        mov  esi,eax
        call FUN_00447a50
        mov  eax,DWORD PTR [ebp+0x50]
        mov  esi,DWORD PTR ds:0x491c10
        lea  ebx,[ebp+0x50]
        add  esp,0xc
        push  eax
        mov  edx,esi
        call FUN_004491c0
        test  eax,eax
        jne loc_00415FCC
        mov  DWORD PTR [ebx],eax
    loc_00415FCC:
        mov  ecx,DWORD PTR [ebp+0x84]
        mov  edx,DWORD PTR [ebp+ecx*4+0x88]
        push  0x46cfd4
        push  edx
        push  esi
        mov  esi,eax
        call FUN_00447a50
        mov  eax,DWORD PTR [edi]
        mov  edx,DWORD PTR ds:0x491c10
        add  esp,0xc
        push  eax
        call FUN_004491c0
        mov  esi,eax
        test  esi,esi
        jne loc_00416000
        mov  DWORD PTR [edi],eax
    loc_00416000:
        mov  eax,DWORD PTR [ebp+0x5c]
        add  eax,0x4
        call FUN_00417010
        mov  ecx,DWORD PTR [ebp+0x84]
        mov  edx,DWORD PTR [ebp+ecx*4+0x88]
        push  eax
        mov  eax,ds:0x491c10
        push  edx
        push  eax
        call FUN_00447a50
        add  esp,0xc
        mov  eax,edi
        call FUN_0040c480
        mov  eax,ebx
        call FUN_0040c4d0
        inc  DWORD PTR [ebp+0x80]
        jmp loc_00416F09
    loc_00416041:
        mov  ecx,DWORD PTR [ebp+0x50]
        mov  ebx,DWORD PTR ds:0x491c10
        lea  edi,[ebp+0x50]
        push  ecx
        mov  edx,ebx
        call FUN_004491c0
        mov  esi,eax
        test  esi,esi
        jne loc_0041605D
        mov  DWORD PTR [edi],eax
    loc_0041605D:
        mov  eax,DWORD PTR [ebp+0x5c]
        add  eax,0x4
        call FUN_00417010
        mov  edx,DWORD PTR [ebp+0x84]
        push  eax
        mov  eax,DWORD PTR [ebp+edx*4+0x88]
        push  eax
        push  ebx
        call FUN_00447a50
        add  esp,0xc
        mov  eax,edi
        call FUN_0040c480
        mov  DWORD PTR [ebp+0x80],0x0
        jmp loc_00416F09
        lea  eax,[ebp+0x4c]
        call FUN_0040c4d0
        lea  eax,[ebp+0x50]
        call FUN_0040c4d0
        jmp loc_00416F09
        mov  ecx,DWORD PTR ds:0x47770c
        mov  eax,DWORD PTR [ecx+0x9ec8]
        push  0xf
        push  0x5a
        push  eax
        lea  edi,[esp+0x1c]
        call FUN_00448d00
        mov  edx,DWORD PTR [eax]
        mov  DWORD PTR [ebp+0x48],edx
        jmp loc_00416F09
        mov  eax,ds:0x474c68
        sub  eax,0x0
        je loc_00416103
        dec  eax
        jne loc_00416F09
        mov  eax,ds:0x477834
        mov  eax,DWORD PTR [eax+0x10]
        push  0xf
        push  0x1d
        push  eax
        lea  edi,[esp+0xbc]
        call FUN_00448d00
        mov  ecx,DWORD PTR [eax]
        mov  DWORD PTR [ebp+0x40],ecx
        jmp loc_00416F09
    loc_00416103:
        mov  edx,DWORD PTR ds:0x477834
        mov  eax,DWORD PTR [edx+0x10]
        push  0xf
        push  0x1d
        push  eax
        lea  edi,[esp+0x8c]
        call FUN_00448d00
        mov  eax,DWORD PTR [eax]
        mov  DWORD PTR [ebp+0x40],eax
        jmp loc_00416F09
        mov  eax,ds:0x474c7c
        cmp  eax,0x6
        jne loc_00416186
        mov  eax,ds:0x474c68
        sub  eax,0x0
        je loc_00416163
        dec  eax
        jne loc_00416F09
        mov  ecx,DWORD PTR ds:0x477704
        mov  eax,DWORD PTR [ecx+0x38]
        push  0xf
        push  0x20
        push  eax
        lea  edi,[esp+0x2c]
        call FUN_00448d00
        mov  edx,DWORD PTR [eax]
        mov  DWORD PTR [ebp+0x44],edx
        jmp loc_00416F09
    loc_00416163:
        mov  eax,ds:0x477704
        mov  eax,DWORD PTR [eax+0x38]
        push  0xf
        push  0x20
        push  eax
        lea  edi,[esp+0xe4]
        call FUN_00448d00
        mov  ecx,DWORD PTR [eax]
        mov  DWORD PTR [ebp+0x44],ecx
        jmp loc_00416F09
    loc_00416186:
        cmp  eax,0x7
        jne loc_004161E7
        cmp  DWORD PTR [ebp+0x0],0x1
        jge loc_004161E7
        mov  eax,ds:0x474c68
        sub  eax,0x0
        je loc_004161C3
        dec  eax
        jne loc_00416F09
        mov  edx,DWORD PTR ds:0x477704
        mov  eax,DWORD PTR [edx+0x38]
        push  0xf
        push  0x25
        push  eax
        lea  edi,[esp+0x34]
        call FUN_00448d00
        mov  eax,DWORD PTR [eax]
        mov  DWORD PTR [ebp+0x44],eax
        jmp loc_00416F09
    loc_004161C3:
        mov  ecx,DWORD PTR ds:0x477704
        mov  eax,DWORD PTR [ecx+0x38]
        push  0xf
        push  0x25
        push  eax
        lea  edi,[esp+0x94]
        call FUN_00448d00
        mov  edx,DWORD PTR [eax]
        mov  DWORD PTR [ebp+0x44],edx
        jmp loc_00416F09
    loc_004161E7:
        mov  eax,ds:0x474c68
        sub  eax,0x0
        je loc_00416218
        dec  eax
        jne loc_00416F09
        mov  eax,ds:0x477834
        mov  eax,DWORD PTR [eax+0x10]
        push  0xf
        push  0x1e
        push  eax
        lea  edi,[esp+0x3c]
        call FUN_00448d00
        mov  ecx,DWORD PTR [eax]
        mov  DWORD PTR [ebp+0x44],ecx
        jmp loc_00416F09
    loc_00416218:
        mov  edx,DWORD PTR ds:0x477834
        mov  eax,DWORD PTR [edx+0x10]
        push  0xf
        push  0x1e
        push  eax
        lea  edi,[esp+0xc4]
        call FUN_00448d00
        mov  eax,DWORD PTR [eax]
        mov  DWORD PTR [ebp+0x44],eax
        jmp loc_00416F09
        lea  eax,[ebp+0x40]
        mov  esi,0x7
        call FUN_00449470
        jmp loc_00416F09
        lea  eax,[ebp+0x44]
        mov  esi,0x7
        call FUN_00449470
        jmp loc_00416F09
        lea  esi,[ebp+0x40]
        mov  eax,esi
        call FUN_00409e50
        mov  DWORD PTR [esi],0x0
        jmp loc_00416F09
        lea  esi,[ebp+0x44]
        mov  eax,esi
        call FUN_00409e50
        lea  eax,[ebp+0x54]
        mov  DWORD PTR [esi],0x0
        call FUN_00409e50
        jmp loc_00416F09
        lea  eax,[ebp+0x48]
        call FUN_00409e50
        lea  eax,[ebp+0x4c]
        call FUN_00409e50
        lea  eax,[ebp+0x50]
        call FUN_00409e50
        jmp loc_00416F09
        lea  eax,[ebp+0x44]
        call FUN_0040c4d0
        lea  eax,[ebp+0x40]
        call FUN_0040c480
        mov  ecx,DWORD PTR [ebp+0x4c]
        mov  edi,DWORD PTR ds:0x491c10
        xor  ebx,ebx
        lea  esi,[ebp+0x60]
        push  ecx
        mov  edx,edi
        mov  DWORD PTR [ebp+0x84],ebx
        call FUN_004492f0
        mov  eax,DWORD PTR [ebp+0x84]
        add  eax,0x8
        lea  edx,[eax+eax*2]
        mov  eax,DWORD PTR [ebp+0x50]
        lea  esi,[ebp+edx*4+0x0]
        push  eax
        mov  edx,edi
        call FUN_004492f0
        mov  DWORD PTR [ebp+0x80],ebx
        jmp loc_00416F09
        lea  eax,[ebp+0x40]
        call FUN_0040c4d0
        lea  eax,[ebp+0x44]
        call FUN_0040c480
        mov  ecx,DWORD PTR [ebp+0x4c]
        mov  edi,DWORD PTR ds:0x491c10
        lea  esi,[ebp+0x6c]
        push  ecx
        mov  edx,edi
        mov  DWORD PTR [ebp+0x84],0x1
        call FUN_004492f0
        mov  eax,DWORD PTR [ebp+0x84]
        add  eax,0x8
        lea  edx,[eax+eax*2]
        mov  eax,DWORD PTR [ebp+0x50]
        lea  esi,[ebp+edx*4+0x0]
        push  eax
        mov  edx,edi
        call FUN_004492f0
        mov  DWORD PTR [ebp+0x80],0x0
        jmp loc_00416F09
        mov  esi,DWORD PTR [ebp+0x7c]
        xor  ecx,ecx
        mov  cl,BYTE PTR [eax+0x4]
        mov  eax,esi
        xor  ecx,esi
        and  ecx,0x1
        xor  eax,ecx
        mov  DWORD PTR [ebp+0x7c],eax
        jmp loc_00416F09
        mov  ecx,DWORD PTR ds:0x474c68
        sub  ecx,0x0
        je loc_004163C6
        dec  ecx
        jne loc_00416F09
        mov  edx,DWORD PTR [eax+0x4]
        add  edx,0x2d
        lea  esi,[ebp+0x40]
        push  edx
        mov  ebx,0x17
        lea  edi,[esp+0x3c]
        call FUN_004497d0
        call FUN_00449670
        mov  eax,DWORD PTR [ebp+0x5c]
        mov  ecx,DWORD PTR [eax+0x4]
        add  ecx,0x35
        push  ecx
        mov  ebx,0x1a
        lea  edi,[esp+0x94]
        call FUN_004497d0
        call FUN_00449670
        jmp loc_00416F09
    loc_004163C6:
        mov  edx,DWORD PTR [eax+0x4]
        add  edx,0x34
        lea  esi,[ebp+0x40]
        push  edx
        mov  ebx,0x17
        lea  edi,[esp+0x44]
        call FUN_004497d0
        call FUN_00449670
        mov  eax,DWORD PTR [ebp+0x5c]
        mov  ecx,DWORD PTR [eax+0x4]
        add  ecx,0x3c
        push  ecx
        mov  ebx,0x1a
        lea  edi,[esp+0xd4]
        call FUN_004497d0
        call FUN_00449670
        jmp loc_00416F09
        mov  ecx,DWORD PTR ds:0x474c7c
        dec  ecx
        cmp  ecx,0x6
        ja loc_00416F09
        jmp  DWORD PTR [ecx*4+0x416fc4]
        mov  ecx,DWORD PTR ds:0x474c68
        sub  ecx,0x0
        je loc_00416487
        dec  ecx
        jne loc_00416F09
        mov  eax,DWORD PTR [eax+0x4]
        mov  edx,DWORD PTR ds:0x477704
        mov  ecx,DWORD PTR [edx+0x38]
        add  eax,0xf
        push  eax
        lea  esi,[ebp+0x44]
        push  ecx
        mov  ebx,0x18
        lea  edi,[esp+0x50]
        call FUN_004497d0
        call FUN_004496a0
        mov  ecx,DWORD PTR ds:0x477704
        mov  eax,DWORD PTR [ecx+0x38]
        mov  edx,DWORD PTR [ebp+0x5c]
        mov  ecx,DWORD PTR [edx+0x4]
        add  ecx,0x17
        push  ecx
        push  eax
        mov  ebx,0x1b
        lea  edi,[esp+0xa0]
        call FUN_004497d0
        call FUN_004496a0
        jmp loc_00416F09
    loc_00416487:
        mov  eax,DWORD PTR [eax+0x4]
        mov  edx,DWORD PTR ds:0x477704
        mov  ecx,DWORD PTR [edx+0x38]
        add  eax,0xf
        push  eax
        lea  esi,[ebp+0x44]
        push  ecx
        mov  ebx,0x18
        lea  edi,[esp+0x58]
        call FUN_004497d0
        call FUN_004496a0
        mov  ecx,DWORD PTR ds:0x477704
        mov  eax,DWORD PTR [ecx+0x38]
        mov  edx,DWORD PTR [ebp+0x5c]
        mov  ecx,DWORD PTR [edx+0x4]
        add  ecx,0x17
        push  ecx
        push  eax
        mov  ebx,0x1b
        lea  edi,[esp+0xc8]
        call FUN_004497d0
        call FUN_004496a0
        jmp loc_00416F09
        mov  ecx,DWORD PTR ds:0x474c68
        sub  ecx,0x0
        je loc_00416545
        dec  ecx
        jne loc_00416F09
        mov  eax,DWORD PTR [eax+0x4]
        mov  edx,DWORD PTR ds:0x477704
        mov  ecx,DWORD PTR [edx+0x38]
        add  eax,0x15
        push  eax
        lea  esi,[ebp+0x44]
        push  ecx
        mov  ebx,0x18
        lea  edi,[esp+0x60]
        call FUN_004497d0
        call FUN_004496a0
        mov  ecx,DWORD PTR ds:0x477704
        mov  eax,DWORD PTR [ecx+0x38]
        mov  edx,DWORD PTR [ebp+0x5c]
        mov  ecx,DWORD PTR [edx+0x4]
        add  ecx,0x1e
        push  ecx
        push  eax
        mov  ebx,0x1b
        lea  edi,[esp+0xa8]
        call FUN_004497d0
        call FUN_004496a0
        jmp loc_00416F09
    loc_00416545:
        mov  eax,DWORD PTR [eax+0x4]
        mov  edx,DWORD PTR ds:0x477704
        mov  ecx,DWORD PTR [edx+0x38]
        add  eax,0x15
        push  eax
        lea  esi,[ebp+0x44]
        push  ecx
        mov  ebx,0x18
        lea  edi,[esp+0x68]
        call FUN_004497d0
        call FUN_004496a0
        mov  ecx,DWORD PTR ds:0x477704
        mov  eax,DWORD PTR [ecx+0x38]
        mov  edx,DWORD PTR [ebp+0x5c]
        mov  ecx,DWORD PTR [edx+0x4]
        add  ecx,0x1e
        push  ecx
        push  eax
        mov  ebx,0x1b
        lea  edi,[esp+0xe8]
        call FUN_004497d0
        call FUN_004496a0
        jmp loc_00416F09
        mov  ecx,DWORD PTR ds:0x474c68
        sub  ecx,0x0
        je loc_00416603
        dec  ecx
        jne loc_00416F09
        mov  eax,DWORD PTR [eax+0x4]
        mov  edx,DWORD PTR ds:0x477704
        mov  ecx,DWORD PTR [edx+0x38]
        add  eax,0x22
        push  eax
        lea  esi,[ebp+0x44]
        push  ecx
        mov  ebx,0x18
        lea  edi,[esp+0x70]
        call FUN_004497d0
        call FUN_004496a0
        mov  ecx,DWORD PTR ds:0x477704
        mov  eax,DWORD PTR [ecx+0x38]
        mov  edx,DWORD PTR [ebp+0x5c]
        mov  ecx,DWORD PTR [edx+0x4]
        add  ecx,0x2b
        push  ecx
        push  eax
        mov  ebx,0x1b
        lea  edi,[esp+0xb0]
        call FUN_004497d0
        call FUN_004496a0
        jmp loc_00416F09
    loc_00416603:
        mov  eax,DWORD PTR [eax+0x4]
        mov  edx,DWORD PTR ds:0x477704
        mov  ecx,DWORD PTR [edx+0x38]
        add  eax,0x22
        push  eax
        lea  esi,[ebp+0x44]
        push  ecx
        mov  ebx,0x18
        lea  edi,[esp+0x78]
        call FUN_004497d0
        call FUN_004496a0
        mov  ecx,DWORD PTR ds:0x477704
        mov  eax,DWORD PTR [ecx+0x38]
        mov  edx,DWORD PTR [ebp+0x5c]
        mov  ecx,DWORD PTR [edx+0x4]
        add  ecx,0x2b
        push  ecx
        push  eax
        mov  ebx,0x1b
        lea  edi,[esp+0xd0]
        call FUN_004497d0
        call FUN_004496a0
        jmp loc_00416F09
        mov  ecx,DWORD PTR ds:0x474c68
        sub  ecx,0x0
        je loc_004166C1
        dec  ecx
        jne loc_00416F09
        mov  eax,DWORD PTR [eax+0x4]
        mov  edx,DWORD PTR ds:0x477704
        mov  ecx,DWORD PTR [edx+0x38]
        add  eax,0x25
        push  eax
        lea  esi,[ebp+0x44]
        push  ecx
        mov  ebx,0x18
        lea  edi,[esp+0x80]
        call FUN_004497d0
        call FUN_004496a0
        mov  ecx,DWORD PTR ds:0x477704
        mov  eax,DWORD PTR [ecx+0x38]
        mov  edx,DWORD PTR [ebp+0x5c]
        mov  ecx,DWORD PTR [edx+0x4]
        add  ecx,0x2e
        push  ecx
        push  eax
        mov  ebx,0x1b
        lea  edi,[esp+0x1c]
        call FUN_004497d0
        call FUN_004496a0
        jmp loc_00416F09
    loc_004166C1:
        mov  eax,DWORD PTR [eax+0x4]
        mov  edx,DWORD PTR ds:0x477704
        mov  ecx,DWORD PTR [edx+0x38]
        add  eax,0x25
        push  eax
        lea  esi,[ebp+0x44]
        push  ecx
        mov  ebx,0x18
        lea  edi,[esp+0x20]
        call FUN_004497d0
        call FUN_004496a0
        mov  ecx,DWORD PTR ds:0x477704
        mov  eax,DWORD PTR [ecx+0x38]
        mov  edx,DWORD PTR [ebp+0x5c]
        mov  ecx,DWORD PTR [edx+0x4]
        add  ecx,0x2e
        push  ecx
        push  eax
        mov  ebx,0x1b
        lea  edi,[esp+0x24]
        call FUN_004497d0
        call FUN_004496a0
        jmp loc_00416F09
        mov  ecx,DWORD PTR ds:0x474c68
        sub  ecx,0x0
        je loc_00416779
        dec  ecx
        jne loc_00416F09
        mov  eax,DWORD PTR [eax+0x4]
        mov  edx,DWORD PTR ds:0x477704
        mov  ecx,DWORD PTR [edx+0x38]
        add  eax,0x16
        push  eax
        lea  esi,[ebp+0x44]
        push  ecx
        mov  ebx,0x18
        lea  edi,[esp+0x2c]
        call FUN_004497d0
        call FUN_004496a0
        mov  ecx,DWORD PTR ds:0x477704
        mov  eax,DWORD PTR [ecx+0x38]
        mov  edx,DWORD PTR [ebp+0x5c]
        mov  ecx,DWORD PTR [edx+0x4]
        add  ecx,0x1f
        push  ecx
        push  eax
        mov  ebx,0x1b
        lea  edi,[esp+0x34]
        call FUN_004497d0
        call FUN_004496a0
        jmp loc_00416F09
    loc_00416779:
        mov  eax,DWORD PTR [eax+0x4]
        mov  edx,DWORD PTR ds:0x477704
        mov  ecx,DWORD PTR [edx+0x38]
        add  eax,0x16
        push  eax
        lea  esi,[ebp+0x44]
        push  ecx
        mov  ebx,0x18
        lea  edi,[esp+0x3c]
        call FUN_004497d0
        call FUN_004496a0
        mov  ecx,DWORD PTR ds:0x477704
        mov  eax,DWORD PTR [ecx+0x38]
        mov  edx,DWORD PTR [ebp+0x5c]
        mov  ecx,DWORD PTR [edx+0x4]
        add  ecx,0x1f
        push  ecx
        push  eax
        mov  ebx,0x1b
        lea  edi,[esp+0x44]
        call FUN_004497d0
        call FUN_004496a0
        jmp loc_00416F09
        mov  ecx,DWORD PTR ds:0x474c68
        sub  ecx,0x0
        je loc_00416831
        dec  ecx
        jne loc_00416F09
        mov  eax,DWORD PTR [eax+0x4]
        mov  edx,DWORD PTR ds:0x477704
        mov  ecx,DWORD PTR [edx+0x38]
        add  eax,0x30
        push  eax
        lea  esi,[ebp+0x44]
        push  ecx
        mov  ebx,0x1c
        lea  edi,[esp+0x4c]
        call FUN_004497d0
        call FUN_004496a0
        mov  ecx,DWORD PTR ds:0x477704
        mov  eax,DWORD PTR [ecx+0x38]
        mov  edx,DWORD PTR [ebp+0x5c]
        mov  ecx,DWORD PTR [edx+0x4]
        add  ecx,0x39
        push  ecx
        push  eax
        mov  ebx,0x1f
        lea  edi,[esp+0x54]
        call FUN_004497d0
        call FUN_004496a0
        jmp loc_00416F09
    loc_00416831:
        mov  eax,DWORD PTR [eax+0x4]
        mov  edx,DWORD PTR ds:0x477704
        mov  ecx,DWORD PTR [edx+0x38]
        add  eax,0x30
        push  eax
        lea  esi,[ebp+0x44]
        push  ecx
        mov  ebx,0x1c
        lea  edi,[esp+0x5c]
        call FUN_004497d0
        call FUN_004496a0
        mov  ecx,DWORD PTR ds:0x477704
        mov  eax,DWORD PTR [ecx+0x38]
        mov  edx,DWORD PTR [ebp+0x5c]
        mov  ecx,DWORD PTR [edx+0x4]
        add  ecx,0x39
        push  ecx
        push  eax
        mov  ebx,0x1f
        lea  edi,[esp+0x64]
        call FUN_004497d0
        call FUN_004496a0
        jmp loc_00416F09
        cmp  DWORD PTR [ebp+0x0],0x1
        mov  ecx,DWORD PTR ds:0x474c68
        jge loc_00416949
        sub  ecx,0x0
        je loc_004168F3
        dec  ecx
        jne loc_00416F09
        mov  eax,DWORD PTR [eax+0x4]
        mov  edx,DWORD PTR ds:0x477704
        mov  ecx,DWORD PTR [edx+0x38]
        add  eax,0x44
        push  eax
        lea  esi,[ebp+0x44]
        push  ecx
        mov  ebx,0x21
        lea  edi,[esp+0x6c]
        call FUN_004497d0
        call FUN_004496a0
        mov  ecx,DWORD PTR ds:0x477704
        mov  eax,DWORD PTR [ecx+0x38]
        mov  edx,DWORD PTR [ebp+0x5c]
        mov  ecx,DWORD PTR [edx+0x4]
        add  ecx,0x4d
        push  ecx
        push  eax
        mov  ebx,0x24
        lea  edi,[esp+0x74]
        call FUN_004497d0
        call FUN_004496a0
        jmp loc_00416F09
    loc_004168F3:
        mov  eax,DWORD PTR [eax+0x4]
        mov  edx,DWORD PTR ds:0x477704
        mov  ecx,DWORD PTR [edx+0x38]
        add  eax,0x44
        push  eax
        lea  esi,[ebp+0x44]
        push  ecx
        mov  ebx,0x21
        lea  edi,[esp+0x7c]
        call FUN_004497d0
        call FUN_004496a0
        mov  ecx,DWORD PTR ds:0x477704
        mov  eax,DWORD PTR [ecx+0x38]
        mov  edx,DWORD PTR [ebp+0x5c]
        mov  ecx,DWORD PTR [edx+0x4]
        add  ecx,0x4d
        push  ecx
        push  eax
        mov  ebx,0x24
        lea  edi,[esp+0x84]
        call FUN_004497d0
        call FUN_004496a0
        jmp loc_00416F09
    loc_00416949:
        sub  ecx,0x0
        je loc_004169AE
        dec  ecx
        jne loc_00416F09
        mov  eax,DWORD PTR [eax+0x4]
        mov  edx,DWORD PTR ds:0x477704
        mov  ecx,DWORD PTR [edx+0x38]
        add  eax,0x2e
        push  eax
        lea  esi,[ebp+0x44]
        push  ecx
        mov  ebx,0x18
        lea  edi,[esp+0x8c]
        call FUN_004497d0
        call FUN_004496a0
        mov  ecx,DWORD PTR ds:0x477704
        mov  eax,DWORD PTR [ecx+0x38]
        mov  edx,DWORD PTR [ebp+0x5c]
        mov  ecx,DWORD PTR [edx+0x4]
        add  ecx,0x37
        push  ecx
        push  eax
        mov  ebx,0x1b
        lea  edi,[esp+0x94]
        call FUN_004497d0
        call FUN_004496a0
        jmp loc_00416F09
    loc_004169AE:
        mov  eax,DWORD PTR [eax+0x4]
        mov  edx,DWORD PTR ds:0x477704
        mov  ecx,DWORD PTR [edx+0x38]
        add  eax,0x2e
        push  eax
        lea  esi,[ebp+0x44]
        push  ecx
        mov  ebx,0x18
        lea  edi,[esp+0x9c]
        call FUN_004497d0
        call FUN_004496a0
        mov  ecx,DWORD PTR ds:0x477704
        mov  eax,DWORD PTR [ecx+0x38]
        mov  edx,DWORD PTR [ebp+0x5c]
        mov  ecx,DWORD PTR [edx+0x4]
        add  ecx,0x37
        push  ecx
        push  eax
        mov  ebx,0x1b
        lea  edi,[esp+0xa4]
        call FUN_004497d0
        call FUN_004496a0
        jmp loc_00416F09
        mov  ecx,DWORD PTR [ebp+0x30]
        xor  ebx,ebx
        cmp  ecx,ebx
        jg loc_00416A1C
        mov  edx,DWORD PTR [eax+0x4]
        push  edx
        lea  eax,[ebp+0x2c]
        call FUN_00405410
    loc_00416A1C:
        lea  esi,[ebp+0x2c]
        push  0xbf800000
        call FUN_0044bf40
        test  DWORD PTR ds:0x474e62,0x1001
        jne loc_00416A65
        cmp  DWORD PTR [ebp+0x30],ebx
        jle loc_00416A65
        test  BYTE PTR [ebp+0x7c],0x1
        je loc_00416F2D
        mov  eax,ds:0x474e5c
        test  ah,0x1
        je loc_00416F2D
        push  ebx
        mov  eax,esi
        call FUN_00405410
        mov  DWORD PTR [ebp+0x80],ebx
        jmp loc_00416F09
    loc_00416A65:
        push  ebx
        xor  edi,edi
        mov  ecx,0x492590
        call FUN_0043dc90
        push  ebx
        mov  eax,esi
        call FUN_00405410
        mov  DWORD PTR [ebp+0x80],ebx
        jmp loc_00416F09
        mov  DWORD PTR [ebp+0x78],0x1
        jmp loc_00416F09
        mov  eax,ds:0x477848
        mov  ecx,DWORD PTR [eax+0x28]
        push  ecx
        push  0x1
        call FUN_00420b10
        mov  edx,DWORD PTR ds:0x47770c
        mov  eax,DWORD PTR [edx+0x9e80]
        push  0xf
        push  0x2
        push  eax
        lea  edi,[esp+0xb0]
        call FUN_00448d00
        jmp loc_00416F09
        mov  eax,ds:0x474c7c
        dec  eax
        cmp  eax,0x6
        ja loc_00416F09
        jmp  DWORD PTR [eax*4+0x416fe0]
        mov  ecx,DWORD PTR ds:0x477704
        mov  eax,DWORD PTR [ecx+0x38]
        push  0xf
        push  0xd
        push  eax
        lea  edi,[esp+0xb8]
        call FUN_00448d00
        mov  edx,DWORD PTR [eax]
        mov  DWORD PTR [ebp+0x54],edx
        jmp loc_00416F09
        mov  eax,ds:0x477704
        mov  eax,DWORD PTR [eax+0x38]
        push  0xf
        push  0x10
        push  eax
        lea  edi,[esp+0xc0]
        call FUN_00448d00
        mov  ecx,DWORD PTR [eax]
        mov  DWORD PTR [ebp+0x54],ecx
        jmp loc_00416F09
        mov  edx,DWORD PTR ds:0x477704
        mov  eax,DWORD PTR [edx+0x38]
        push  0xf
        push  0x14
        push  eax
        lea  edi,[esp+0xc8]
        call FUN_00448d00
        mov  eax,DWORD PTR [eax]
        mov  DWORD PTR [ebp+0x54],eax
        jmp loc_00416F09
        mov  ecx,DWORD PTR ds:0x477704
        mov  eax,DWORD PTR [ecx+0x38]
        push  0xf
        push  0x15
        push  eax
        lea  edi,[esp+0xd0]
        call FUN_00448d00
        mov  edx,DWORD PTR [eax]
        mov  DWORD PTR [ebp+0x54],edx
        jmp loc_00416F09
        mov  eax,ds:0x477704
        mov  eax,DWORD PTR [eax+0x38]
        push  0xf
        push  0xe
        push  eax
        lea  edi,[esp+0xd8]
        call FUN_00448d00
        mov  ecx,DWORD PTR [eax]
        mov  DWORD PTR [ebp+0x54],ecx
        jmp loc_00416F09
        mov  edx,DWORD PTR ds:0x477704
        mov  eax,DWORD PTR [edx+0x38]
        push  0xf
        push  0x23
        push  eax
        lea  edi,[esp+0xe0]
        call FUN_00448d00
        mov  eax,DWORD PTR [eax]
        mov  DWORD PTR [ebp+0x54],eax
        jmp loc_00416F09
        mov  ecx,DWORD PTR ds:0x477704
        mov  eax,DWORD PTR [ecx+0x38]
        push  0xf
        push  0x1d
        push  eax
        lea  edi,[esp+0xe8]
        call FUN_00448d00
        mov  edx,DWORD PTR [eax]
        mov  DWORD PTR [ebp+0x54],edx
        jmp loc_00416F09
        mov  ecx,DWORD PTR ds:0x474c74
        cmp  ecx,0x4
        je loc_00416C3D
        mov  eax,ds:0x474c68
        mov  edx,DWORD PTR ds:0x474c6c
        lea  edx,[edx+eax*2]
        add  edx,eax
        imul  edx,edx,0x437c
        lea  eax,[ecx+ecx*2]
        mov  ecx,DWORD PTR ds:0x474c7c
        lea  eax,[ecx+eax*2]
        mov  ecx,DWORD PTR ds:0x47783c
        add  edx,ecx
        mov  BYTE PTR [edx+eax*8+0x4e1],0x1
        mov  eax,ds:0x474c74
        mov  esi,DWORD PTR ds:0x474c6c
        lea  edx,[eax+eax*2+0x4e]
        mov  eax,ds:0x474c7c
        lea  edx,[eax+edx*2]
        mov  eax,ds:0x474c68
        lea  esi,[esi+eax*2]
        add  esi,eax
        imul  esi,esi,0x437c
        add  esi,ecx
        mov  BYTE PTR [esi+edx*8],0x1
    loc_00416C3D:
        test  BYTE PTR ds:0x474ca0,0x10
        je loc_00416C56
        mov  edi,DWORD PTR ds:0x477830
        call FUN_00423370
        jmp loc_00416F09
    loc_00416C56:
        mov  eax,ds:0x474c7c
        cmp  eax,0x6
        jne loc_00416DE8
        mov  eax,ds:0x47770c
        or   DWORD PTR [eax+0x9eb4],0x20
        mov  eax,ds:0x474c4c
        imul  eax,eax,0x3e8
        push  eax
        mov  ecx,0x474c40
        call FUN_00409d90
        mov  eax,ds:0x474c74
        cmp  eax,0x4
        ja loc_00416D66
        jmp  DWORD PTR [eax*4+0x416ffc]
        mov  ecx,DWORD PTR ds:0x474c70
        imul  ecx,ecx,0x1312d00
        push  ecx
        mov  ecx,0x474c40
        call FUN_00409d90
        movsx edx,WORD PTR ds:0x474c48
        imul  edx,edx,0x186a0
        push  edx
        jmp loc_00416D5C
        mov  eax,ds:0x474c70
        imul  eax,eax,0x17d7840
        push  eax
        mov  ecx,0x474c40
        call FUN_00409d90
        movsx ecx,WORD PTR ds:0x474c48
        imul  ecx,ecx,0x186a0
        jmp loc_00416D5B
        mov  edx,DWORD PTR ds:0x474c70
        imul  edx,edx,0x2160ec0
        push  edx
        mov  ecx,0x474c40
        call FUN_00409d90
        movsx eax,WORD PTR ds:0x474c48
        imul  eax,eax,0x30d40
        push  eax
        jmp loc_00416D5C
        mov  ecx,DWORD PTR ds:0x474c70
        imul  ecx,ecx,0x2625a00
        push  ecx
        mov  ecx,0x474c40
        call FUN_00409d90
        movsx edx,WORD PTR ds:0x474c48
        imul  edx,edx,0x493e0
        push  edx
        jmp loc_00416D5C
        mov  eax,ds:0x474c70
        imul  eax,eax,0x2625a00
        push  eax
        mov  ecx,0x474c40
        call FUN_00409d90
        movsx ecx,WORD PTR ds:0x474c48
        imul  ecx,ecx,0x61a80
    loc_00416D5B:
        push  ecx
    loc_00416D5C:
        mov  ecx,0x474c40
        call FUN_00409d90
    loc_00416D66:
        mov  edx,DWORD PTR ds:0x477838
        cmp  DWORD PTR [edx+0x10],0x1
        je loc_00416E8A
        push  0x0
        push  0x0
        push  0x0
        push  0x78
        push  0x5
        mov  ebx,0x31
        call FUN_0043c8b0
        mov  eax,ds:0x47770c
        mov  ebx,DWORD PTR [eax+0x9eb4]
        mov  DWORD PTR [eax+0x9ecc],0x0
        or   ebx,0x10
        mov  DWORD PTR [eax+0x9eb4],ebx
        mov  eax,ds:0x474c68
        mov  ecx,DWORD PTR ds:0x474c6c
        mov  esi,DWORD PTR ds:0x474c74
        lea  edx,[ecx+eax*2]
        add  edx,eax
        mov  eax,ds:0x47783c
        imul  edx,edx,0x10df
        add  edx,esi
        lea  eax,[eax+edx*4+0x4d0]
    loc_00416DD2:
        mov  ecx,DWORD PTR [eax]
        cmp  ecx,0x1869f
        jge loc_00416F09
        inc  ecx
        mov  DWORD PTR [eax],ecx
        jmp loc_00416F09
    loc_00416DE8:
        cmp  eax,0x7
        jne loc_00416E98
        mov  eax,ds:0x47770c
        or   DWORD PTR [eax+0x9eb4],0x20
        mov  ecx,DWORD PTR ds:0x474c4c
        imul  ecx,ecx,0x3e8
        push  ecx
        mov  ecx,0x474c40
        call FUN_00409d90
        mov  edx,DWORD PTR ds:0x474c70
        imul  edx,edx,0x2625a00
        push  edx
        mov  ecx,0x474c40
        call FUN_00409d90
        movsx eax,WORD PTR ds:0x474c48
        imul  eax,eax,0x61a80
        push  eax
        mov  ecx,0x474c40
        call FUN_00409d90
        mov  ecx,DWORD PTR ds:0x477838
        cmp  DWORD PTR [ecx+0x10],0x1
        je loc_00416E8A
        mov  edi,DWORD PTR ds:0x477830
        call FUN_00423370
        mov  eax,ds:0x474c68
        mov  edx,DWORD PTR ds:0x474c6c
        lea  ecx,[edx+eax*2]
        mov  edx,DWORD PTR ds:0x474c74
        add  ecx,eax
        imul  ecx,ecx,0x10df
        add  ecx,edx
        mov  edx,DWORD PTR ds:0x47783c
        lea  eax,[edx+ecx*4+0x4d0]
        jmp loc_00416DD2
    loc_00416E8A:
        push  0x4
        mov  eax,0x491c28
        call FUN_0040ac90
        jmp loc_00416F09
    loc_00416E98:
        mov  edi,DWORD PTR ds:0x47770c
        mov  eax,DWORD PTR [edi+0x9e14]
        mov  edx,DWORD PTR ds:0x491c10
        lea  esi,[edi+0x9e14]
        push  eax
        call FUN_004492a0
        push  0xf
        mov  DWORD PTR [esi],0x0
        mov  ecx,DWORD PTR [edi+0x9ec8]
        push  0x4c
        push  ecx
        lea  edi,[esp+0xf0]
        call FUN_00448d00
        mov  edx,DWORD PTR [eax]
        push  0xb
        mov  eax,0x491c28
        mov  DWORD PTR [esi],edx
        call FUN_0040ac90
        mov  eax,0x474c40
        call FUN_004175e0
        jmp loc_00416F09
        cmp  DWORD PTR ds:0x474c7c,0x6
        je loc_00416EFF
        push  0x40000000
        jmp loc_00416F04
    loc_00416EFF:
        push  0x41000000
    loc_00416F04:
        call FUN_00420c30
    loc_00416F09:
        mov  eax,DWORD PTR [ebp+0x5c]
        movzx ecx,BYTE PTR [eax+0x3]
        lea  edx,[ecx+eax*1+0x4]
        mov  eax,edx
        mov  DWORD PTR [ebp+0x5c],edx
        movzx ecx,WORD PTR [eax]
        cmp  DWORD PTR [ebp+0x1c],ecx
        jge loc_00415F06
    loc_00416F25:
        lea  esi,[ebp+0x18]
        call FUN_00404ed0
    loc_00416F2D:
        pop  edi
        pop  esi
        pop  ebp
        xor  eax,eax
        pop  ebx
        add  esp,0xd8
        ret  0x4
        mov  ecx,DWORD PTR ds:0x474c84
        xor  eax,eax
        cmp  ecx,eax
        je loc_00416F4D
        mov  ds:0x474c8c,eax
    loc_00416F4D:
        pop  edi
        pop  esi
        pop  ebp
        mov  ds:0x474c84,eax
        or   eax,0xffffffff
        pop  ebx
        add  esp,0xd8
        ret  0x4
        mov  edi,edi
        cmp  al,0x6f
        inc  ecx
        add  bh,cl
        pusha
        inc  ecx
        add  BYTE PTR [edi],ah
        popa
        inc  ecx
        add  BYTE PTR [ebx+0x60004160],ch
        bound eax,QWORD PTR [ecx+0x0]
        jne loc_00416FDC
        inc  ecx
        add  BYTE PTR [edx-0x50ffbe9e],dl
        bound eax,QWORD PTR [ecx+0x0]
        add  DWORD PTR [ebx+0x41],esp
        add  BYTE PTR [ecx+0x63],bl
        inc  ecx
        add  BYTE PTR [edi],al
        push  0x41
        add  BYTE PTR [ebp+0x7200416a],al
        arpl  WORD PTR [ecx+0x0],eax
        or   BYTE PTR [ecx+eax*2+0x0],ah
        sbb  eax,0x2200415f
        pop  edi
        inc  ecx
        add  BYTE PTR [edi+ebx*2+0x41],ch
        add  BYTE PTR [esi-0x6effbea0],dl
        push  0x41
        add  bl,al
        push  0x41
        add  bl,dl
        imul  eax,DWORD PTR [ecx+0x0],0xffffffef
        outs  dx,BYTE PTR ds:[esi]
        inc  ecx
        add  BYTE PTR [edx+eiz*2],bh
        inc  ecx
        add  BYTE PTR [esi+0x62],cl
        inc  ecx
        add  BYTE PTR [edi],bl
        fs inc ecx
        add  ch,bl
        fs inc ecx
        add  BYTE PTR [ebx+0x59004165],bl
        inc  cx
        add  BYTE PTR [edi+eiz*2],dl
        inc  ecx
        add  ah,cl
        addr16 inc ecx
        add  BYTE PTR [eax+ebp*2+0x6ad90041],al
        inc  ecx
        add  ch,bh
        push  0x41
        add  BYTE PTR [eax],ah
        imul  eax,DWORD PTR [ecx+0x0],0x44
        imul  eax,DWORD PTR [ecx+0x0],0x68
        imul  eax,DWORD PTR [ecx+0x0],0xffffff8b
        imul  eax,DWORD PTR [ecx+0x0],0xffffffaf
        imul  eax,DWORD PTR [ecx+0x0],0xffffff9b
        ins  BYTE PTR es:[edi],dx
        inc  ecx
        add  ch,al
        ins  BYTE PTR es:[edi],dx
        inc  ecx
        add  dl,ch
        ins  BYTE PTR es:[edi],dx
        inc  ecx
        add  BYTE PTR [ecx],dl
        ins  DWORD PTR es:[edi],dx
        inc  ecx
        add  BYTE PTR [eax],bh
        ins  DWORD PTR es:[edi],dx
        inc  ecx
    }
}
