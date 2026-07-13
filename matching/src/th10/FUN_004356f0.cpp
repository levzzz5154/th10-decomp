// 004356F0: FUN_004356f0
// Original size: 272 bytes, actual code: 105 instructions
extern "C" void FUN_00434c30(void);
extern "C" void FUN_00452730(void);
extern "C" void __security_check_cookie(void);

extern "C" __declspec(naked) void FUN_004356f0(void) {
    __asm {
        sub  esp,0x108
        mov  eax,ds:0x473660
        xor  eax,esp
        push  ebx
        push  ebp
        push  esi
        push  edi
        mov  esi,ecx
        push  0x2f
        push  esi
        mov  DWORD PTR [esp+0x11c],eax
        call FUN_00452730
        add  esp,0x8
        test  eax,eax
        je loc_0043571C
        inc  eax
        jmp loc_0043571E
    loc_0043571C:
        mov  eax,esi
    loc_0043571E:
        sub  eax,esi
        dec  eax
        lea  edx,[esp+0x10]
        mov  edi,eax
        mov  eax,esi
        sub  edx,esi
        jmp loc_00435730
        nop
    loc_00435730:
        mov  cl,BYTE PTR [eax]
        mov  BYTE PTR [edx+eax*1],cl
        inc  eax
        test  cl,cl
        jne loc_00435730
        test  edi,edi
        jl loc_00435753
        mov  ecx,DWORD PTR ds:0x46f274
        mov  dl,BYTE PTR ds:0x46f278
        lea  eax,[esp+edi*1+0x10]
        mov  DWORD PTR [eax],ecx
        mov  BYTE PTR [eax+0x4],dl
    loc_00435753:
        mov  eax,ds:0x477850
        xor  ebp,ebp
        test  eax,eax
        mov  edi,0x4923b0
        jle loc_004357A5
    loc_00435763:
        mov  ecx,DWORD PTR [edi+0x8]
        lea  esi,[esp+0x10]
        lea  ebx,[ebx+0x0]
    loc_00435770:
        mov  bl,BYTE PTR [ecx]
        mov  dl,bl
        cmp  bl,BYTE PTR [esi]
        jne loc_00435794
        test  dl,dl
        je loc_00435790
        mov  bl,BYTE PTR [ecx+0x1]
        mov  dl,bl
        cmp  bl,BYTE PTR [esi+0x1]
        jne loc_00435794
        add  ecx,0x2
        add  esi,0x2
        test  dl,dl
        jne loc_00435770
    loc_00435790:
        xor  ecx,ecx
        jmp loc_00435799
    loc_00435794:
        sbb  ecx,ecx
        sbb  ecx,0xffffffff
    loc_00435799:
        test  ecx,ecx
        je loc_004357C0
        inc  ebp
        add  edi,0x10
        cmp  ebp,eax
        jl loc_00435763
    loc_004357A5:
        xor  eax,eax
    loc_004357A7:
        mov  ecx,DWORD PTR [esp+0x114]
        pop  edi
        pop  esi
        pop  ebp
        pop  ebx
        xor  ecx,esp
        call __security_check_cookie
        add  esp,0x108
        ret
    loc_004357C0:
        mov  eax,edi
        jmp loc_004357A7
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
        mov  ecx,DWORD PTR ds:0x477850
        shl  ecx,0x4
        add  ecx,0x4923b0
        call FUN_00434c30
        test  al,al
        je loc_004357F1
        inc  DWORD PTR ds:0x477850
        mov  al,0x1
        ret
    loc_004357F1:
        xor  al,al
        ret
    }
}
