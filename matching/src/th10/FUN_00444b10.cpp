// 00444B10: FUN_00444b10
// Original size: 208 bytes, actual code: 74 instructions

extern "C" __declspec(naked) void FUN_00444b10(void) {
    __asm {
        sub  esp,0x8
        push  esi
        mov  esi,eax
        cmp  esi,0x3
        jge loc_00444B23
        or   eax,0xffffffff
        pop  esi
        add  esp,0x8
        ret
    loc_00444B23:
        mov  eax,DWORD PTR [ecx+0x394]
        fld  DWORD PTR [ecx+0x54]
        fadd  DWORD PTR [eax+0x28]
        push  edi
        fld  DWORD PTR [eax+0x24]
        mov  edi,0x3f800000
        fadd  DWORD PTR [ecx+0x58]
        fstp  DWORD PTR [esp+0x8]
        fld  DWORD PTR [eax+0x28]
        fsub  DWORD PTR [eax+0x20]
        lea  eax,[esi+0x1]
        cdq
        sub  eax,edx
        sar  eax,1
        dec  eax
        test  esi,esi
        mov  DWORD PTR [esp+0xc],eax
        fidiv DWORD PTR [esp+0xc]
        fstp  DWORD PTR [esp+0xc]
        fld  st(0)
        jle loc_00444B90
        lea  edx,[esi-0x1]
        shr  edx,1
        lea  eax,[ebx+0x18]
        inc  edx
        push  ebp
        lea  ebx,[ebx+0x0]
    loc_00444B70:
        mov  ebp,DWORD PTR [esp+0xc]
        fst  DWORD PTR [eax-0x4]
        fsub  DWORD PTR [esp+0x10]
        mov  DWORD PTR [eax],ebp
        mov  ebp,DWORD PTR [ecx+0x2fc]
        mov  DWORD PTR [eax-0x8],ebp
        mov  DWORD PTR [eax-0xc],edi
        add  eax,0x38
        dec  edx
        jne loc_00444B70
        pop  ebp
    loc_00444B90:
        cmp  esi,0x1
        fstp  st(0)
        mov  eax,DWORD PTR [ecx+0x394]
        fld  DWORD PTR [eax+0x2c]
        fadd  DWORD PTR [ecx+0x58]
        fstp  DWORD PTR [esp+0x8]
        jle loc_00444BCF
        lea  edx,[esi-0x2]
        shr  edx,1
        lea  eax,[ebx+0x34]
        inc  edx
    loc_00444BB0:
        mov  esi,DWORD PTR [esp+0x8]
        fst  DWORD PTR [eax-0x4]
        fsub  DWORD PTR [esp+0xc]
        mov  DWORD PTR [eax],esi
        mov  esi,DWORD PTR [ecx+0x2fc]
        mov  DWORD PTR [eax-0x8],esi
        mov  DWORD PTR [eax-0xc],edi
        add  eax,0x38
        dec  edx
        jne loc_00444BB0
    loc_00444BCF:
        pop  edi
        fstp  st(0)
        xor  eax,eax
        pop  esi
        add  esp,0x8
        ret
    }
}
