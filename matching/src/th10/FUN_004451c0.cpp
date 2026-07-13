// 004451C0: FUN_004451c0
// Original size: 304 bytes, actual code: 130 instructions
extern "C" void FUN_00443080(void);
extern "C" void FUN_00443290(void);
extern "C" void FUN_004436C0(void);
extern "C" void FUN_00443910(void);
extern "C" void FUN_00443f80(void);
extern "C" void FUN_00443fb0(void);
extern "C" void FUN_00444580(void);
extern "C" void FUN_004445c0(void);
extern "C" void FUN_00444760(void);
extern "C" void FUN_00444ce0(void);

extern "C" __declspec(naked) void FUN_004451c0(void) {
    __asm {
        mov  edx,DWORD PTR [eax+0x35c]
        test  dl,0x1
        je loc_004451DC
        test  dl,0x2
        je loc_004451DC
        push  ebx
        mov  bl,BYTE PTR [eax+0x2ff]
        test  bl,bl
        pop  ebx
        jne loc_004451E0
    loc_004451DC:
        or   eax,0xffffffff
        ret
    loc_004451E0:
        shr  edx,0x16
        and  edx,0xf
        cmp  edx,0x9
        push  esi
        push  edi
        ja loc_00445268
        jmp  DWORD PTR [edx*4+0x445270]
        push  ecx
        mov  esi,eax
        call FUN_00443080
        pop  edi
        pop  esi
        ret
        pop  edi
        mov  edx,eax
        pop  esi
        jmp FUN_004436C0
        push  ecx
        mov  esi,eax
        call FUN_00443f80
        pop  edi
        pop  esi
        ret
        mov  esi,eax
        mov  edi,ecx
        call FUN_00444580
        pop  edi
        pop  esi
        ret
        mov  edi,eax
        mov  esi,ecx
        call FUN_00443fb0
        pop  edi
        pop  esi
        ret
        push  eax
        push  ecx
        call FUN_004445c0
        pop  edi
        pop  esi
        ret
        push  ecx
        call FUN_00444760
        pop  edi
        pop  esi
        ret
        mov  edx,DWORD PTR [eax+0x30c]
        shl  edx,1
        push  edx
        mov  edx,DWORD PTR [eax+0x358]
        push  edx
        call FUN_00444ce0
        pop  edi
        pop  esi
        ret
        push  ecx
        call FUN_00443290
        pop  edi
        pop  esi
        ret
        pop  edi
        mov  edx,eax
        pop  esi
        jmp FUN_00443910
    loc_00445268:
        pop  edi
        xor  eax,eax
        pop  esi
        ret
        nop
        hlt
        push  ecx
        inc  esp
        add  bh,bh
        push  ecx
        inc  esp
        add  BYTE PTR [esi+0x52],dl
        inc  esp
        add  BYTE PTR [edi+0x52],bl
        inc  esp
        add  BYTE PTR [eax],cl
        push  edx
        inc  esp
        add  BYTE PTR [ebx],dl
        push  edx
        inc  esp
        add  BYTE PTR [edi],bl
        push  edx
        inc  esp
        add  BYTE PTR [ebx],ch
        push  edx
        inc  esp
        add  BYTE PTR ds:0x3e004452,dh
        push  edx
        inc  esp
        add  ah,cl
        int3
        int3
        int3
        int3
        int3
        int3
        int3
        fld  DWORD PTR [eax+0x8]
        fld  DWORD PTR [eax+0x4]
        fld  DWORD PTR [eax]
        fld  st(0)
        fmul  st,st(1)
        fld  st(2)
        fmul  st,st(3)
        faddp st(1),st
        fld  st(3)
        fmul  st,st(4)
        faddp st(1),st
        fsqrt
        fstp  st(3)
        fstp  st(0)
        fstp  st(0)
        ret
    }
}
