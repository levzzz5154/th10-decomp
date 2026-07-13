// 00444BE0: FUN_00444be0
// Original size: 256 bytes, actual code: 74 instructions

extern "C" __declspec(naked) void FUN_00444be0(void) {
    __asm {
        sub  esp,0x8
        push  esi
        mov  esi,eax
        cmp  esi,0x3
        jge loc_00444BF3
        or   eax,0xffffffff
        pop  esi
        add  esp,0x8
        ret
    loc_00444BF3:
        mov  eax,DWORD PTR [ecx+0x394]
        fld  DWORD PTR [ecx+0x58]
        fadd  DWORD PTR [eax+0x2c]
        push  edi
        fld  DWORD PTR [eax+0x20]
        mov  edi,0x3f800000
        fadd  DWORD PTR [ecx+0x54]
        fstp  DWORD PTR [esp+0x8]
        fld  DWORD PTR [eax+0x2c]
        fsub  DWORD PTR [eax+0x24]
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
        jle loc_00444C60
        lea  edx,[esi-0x1]
        shr  edx,1
        lea  eax,[ebx+0x14]
        inc  edx
        push  ebp
        lea  ebx,[ebx+0x0]
    loc_00444C40:
        mov  ebp,DWORD PTR [esp+0xc]
        fst  DWORD PTR [eax+0x4]
        fsub  DWORD PTR [esp+0x10]
        mov  DWORD PTR [eax],ebp
        mov  ebp,DWORD PTR [ecx+0x2fc]
        mov  DWORD PTR [eax-0x4],ebp
        mov  DWORD PTR [eax-0x8],edi
        add  eax,0x38
        dec  edx
        jne loc_00444C40
        pop  ebp
    loc_00444C60:
        cmp  esi,0x1
        fstp  st(0)
        mov  eax,DWORD PTR [ecx+0x394]
        fld  DWORD PTR [eax+0x28]
        fadd  DWORD PTR [ecx+0x54]
        fstp  DWORD PTR [esp+0x8]
        jle loc_00444C9F
        lea  edx,[esi-0x2]
        shr  edx,1
        lea  eax,[ebx+0x30]
        inc  edx
    loc_00444C80:
        mov  esi,DWORD PTR [esp+0x8]
        fst  DWORD PTR [eax+0x4]
        fsub  DWORD PTR [esp+0xc]
        mov  DWORD PTR [eax],esi
        mov  esi,DWORD PTR [ecx+0x2fc]
        mov  DWORD PTR [eax-0x4],esi
        mov  DWORD PTR [eax-0x8],edi
        add  eax,0x38
        dec  edx
        jne loc_00444C80
    loc_00444C9F:
        pop  edi
        fstp  st(0)
        xor  eax,eax
        pop  esi
        add  esp,0x8
        ret
    }
}
