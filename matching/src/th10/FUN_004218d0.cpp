// 004218D0: FUN_004218d0
// Original size: 704 bytes, actual code: 173 instructions
extern "C" void FUN_0040b940(void);
extern "C" void FUN_0040b9d0(void);
extern "C" void FUN_004180e0(void);
extern "C" void FUN_00418150(void);
extern "C" void FUN_0041fd00(void);
extern "C" void FUN_004203f0(void);
extern "C" void FUN_00421c50(void);
extern "C" void FUN_0042cd50(void);
extern "C" void FUN_0042cdb0(void);

extern "C" __declspec(naked) void FUN_004218d0(void) {
    __asm {
        push  ebx
        push  ebp
        push  esi
        push  edi
        mov  edi,eax
        mov  eax,DWORD PTR [edi+0x38c]
        cmp  eax,DWORD PTR [edi+0x390]
        je loc_004219A4
        lea  ebp,[edi+0x6c4]
        push  ebp
        call  DWORD PTR ds:0x4660b0
        mov  bl,BYTE PTR [edi+0x6f9]
        mov  ecx,DWORD PTR [edi+0x390]
        mov  eax,DWORD PTR [edi+0x38c]
        inc  bl
        cmp  ecx,0xf
        mov  BYTE PTR [edi+0x6f9],bl
        mov  DWORD PTR [edi+0x394],eax
        mov  DWORD PTR [edi+0x780],0xff000000
        ja loc_0042198B
        jmp  DWORD PTR [ecx*4+0x421b0c]
        mov  DWORD PTR [edi+0x390],0x1
        call FUN_0041fd00
        test  eax,eax
        mov  DWORD PTR [edi+0x768],eax
        jne loc_0042198B
        mov  DWORD PTR [edi+0x390],0x3
        call FUN_004203f0
        mov  esi,0x5
        call FUN_00421c50
        pop  edi
        pop  esi
        pop  ebp
        mov  eax,0x4
        pop  ebx
        ret
        dec  eax
        cmp  eax,0xd
        ja loc_0042198B
        movzx ecx,BYTE PTR [eax+0x421b5c]
        jmp  DWORD PTR [ecx*4+0x421b4c]
        mov  esi,DWORD PTR ds:0x477810
        call FUN_00418150
    loc_00421986:
        call FUN_0042cd50
    loc_0042198B:
        mov  eax,DWORD PTR [edi+0x390]
        push  ebp
        mov  DWORD PTR [edi+0x38c],eax
        call  DWORD PTR ds:0x4660b4
        dec  BYTE PTR [edi+0x6f9]
    loc_004219A4:
        pop  edi
        pop  esi
        pop  ebp
        mov  eax,0x1
        pop  ebx
        ret
        mov  esi,DWORD PTR ds:0x477700
        call FUN_0040b9d0
        jmp loc_00421986
        sub  eax,0x2
        je loc_004219E2
        sub  eax,0x5
        je loc_004219D7
        sub  eax,0x7
        jne loc_0042198B
        mov  esi,DWORD PTR ds:0x477700
        call FUN_0040b9d0
        jmp loc_004219E2
    loc_004219D7:
        mov  esi,DWORD PTR ds:0x477810
        call FUN_00418150
    loc_004219E2:
        mov  DWORD PTR [edi+0x390],0x4
        mov  DWORD PTR ds:0x491c00,0x3
        jmp loc_00421986
        cmp  eax,0x4
        jne loc_00421A08
        mov  esi,DWORD PTR ds:0x47784c
        call FUN_0042cdb0
    loc_00421A08:
        push  0x0
        mov  DWORD PTR [edi+0x39c],0x1
        call FUN_004180e0
        jmp loc_0042198B
        cmp  eax,0x4
        jne loc_00421A2E
        mov  esi,DWORD PTR ds:0x47784c
        call FUN_0042cdb0
    loc_00421A2E:
        push  0x1
        mov  DWORD PTR [edi+0x390],0x7
        mov  DWORD PTR [edi+0x39c],0x1
        call FUN_004180e0
        jmp loc_0042198B
        cmp  eax,0x7
        mov  esi,DWORD PTR ds:0x477810
        mov  ebx,DWORD PTR [esi+0x5c]
        mov  DWORD PTR [edi+0x39c],0x0
        jne loc_00421A6B
        call FUN_00418150
    loc_00421A6B:
        push  ebx
        mov  DWORD PTR [edi+0x390],0x7
        call FUN_004180e0
        jmp loc_0042198B
        mov  esi,DWORD PTR ds:0x477810
        call FUN_00418150
        mov  DWORD PTR [edi+0x39c],0x1
        mov  DWORD PTR [edi+0x390],0x7
        mov  eax,ds:0x474c80
        lea  edx,[eax+eax*2]
        shl  edx,0x4
        add  edx,0x474788
        push  0x0
        mov  ds:0x474c7c,eax
        mov  DWORD PTR ds:0x477848,edx
        call FUN_004180e0
        jmp loc_0042198B
        mov  esi,DWORD PTR ds:0x477810
        call FUN_00418150
        push  0x0
        mov  DWORD PTR [edi+0x39c],0x1
        mov  DWORD PTR [edi+0x390],0x7
        call FUN_004180e0
        jmp loc_0042198B
        cmp  eax,0x7
        jne loc_00421B02
        mov  esi,DWORD PTR ds:0x477810
        call FUN_00418150
    loc_00421B02:
        call FUN_0040b940
        jmp loc_0042198B
        sub  ebx,DWORD PTR [ecx]
        inc  edx
        add  BYTE PTR [ebx-0x74ffbde7],cl
        sbb  DWORD PTR [edx+0x0],eax
        dec  esi
        sbb  DWORD PTR [edx+0x0],eax
        sbb  DWORD PTR [bp+si+0x0],eax
        mov  ebx,DWORD PTR [ecx]
        inc  edx
        add  BYTE PTR [ebx-0x7ffbde7],cl
        sbb  DWORD PTR [edx+0x0],eax
        mov  ebx,DWORD PTR [ecx]
        inc  edx
        add  BYTE PTR [ebx-0x7fffbde7],cl
        sbb  al,BYTE PTR [edx+0x0]
        dec  esi
        sbb  al,BYTE PTR [edx+0x0]
        push  ds
        sbb  al,BYTE PTR [edx+0x0]
        (bad]
        sbb  al,BYTE PTR [edx+0x0]
        repnz sbb al,BYTE PTR [edx+0x0]
        mov  ebx,0x86004219
        sbb  DWORD PTR [edx+0x0],eax
        jnp loc_00421B6B
        inc  edx
        add  BYTE PTR [esi-0x74ffbde7],ch
        sbb  DWORD PTR [edx+0x0],eax
        add  BYTE PTR [eax],al
        add  eax,DWORD PTR [ebx]
        add  eax,DWORD PTR [ebx]
        add  DWORD PTR [ebx],eax
        add  eax,DWORD PTR [ebx]
        add  eax,DWORD PTR [ebx]
        add  eax,DWORD PTR [edx]
        int3
    loc_00421B6B:
        int3
        int3
        int3
        int3
        int3
        mov  eax,DWORD PTR [ecx+0x40]
        mov  DWORD PTR [ecx+0x3c],eax
        lea  eax,[eax+eax*2]
        shl  eax,0x4
        add  eax,0x474788
        mov  ds:0x477848,eax
        ret
    }
}
