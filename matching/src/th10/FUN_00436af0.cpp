// 00436AF0: FUN_00436af0
// Original size: 432 bytes, actual code: 130 instructions
extern "C" void FUN_00436a30(void);

extern "C" __declspec(naked) void FUN_00436af0(void) {
    __asm {
        sub  esp,0x70
        push  ebp
        push  esi
        push  edi
        mov  esi,eax
        call FUN_00436a30
        xor  eax,eax
        mov  ecx,0x1b
        lea  edi,[esp+0x10]
        rep stosd
        mov  ecx,DWORD PTR ds:0x474918
        cmp  ecx,0xffffffff
        je loc_00436B32
    loc_00436B15:
        mov  ebp,DWORD PTR [esp+0x88]
        cmp  ecx,ebp
        je loc_00436B39
        inc  eax
        lea  ecx,[eax+eax*2]
        mov  ecx,DWORD PTR [ecx*8+0x474918]
        cmp  ecx,0xffffffff
        jne loc_00436B15
        jmp loc_00436B39
    loc_00436B32:
        mov  ebp,DWORD PTR [esp+0x88]
    loc_00436B39:
        cmp  ebp,0xffffffff
        je loc_00436B4C
        lea  ecx,[eax+eax*2]
        lea  ecx,[ecx*8+0x474918]
        test  ecx,ecx
        jne loc_00436B57
    loc_00436B4C:
        pop  edi
        pop  esi
        xor  al,al
        pop  ebp
        add  esp,0x70
        ret  0xc
    loc_00436B57:
        mov  edi,DWORD PTR [esp+0x80]
        mov  eax,DWORD PTR [ecx+0x4]
        imul  eax,edi
        cdq
        and  edx,0x7
        add  eax,edx
        sar  eax,0x3
        add  eax,0x3
        cdq
        and  edx,0x3
        add  eax,edx
        push  ebx
        or   edx,0xffffffff
        mov  ebx,eax
        mov  eax,DWORD PTR [esp+0x88]
        sub  edx,eax
        mov  DWORD PTR [esp+0x1c],edx
        mov  dx,WORD PTR [ecx+0x4]
        sar  ebx,0x2
        shl  ebx,0x2
        mov  WORD PTR [esp+0x22],dx
        mov  edx,ebx
        imul  edx,eax
        cmp  ebp,0x18
        mov  DWORD PTR [esp+0x14],0x6c
        mov  DWORD PTR [esp+0x18],edi
        mov  WORD PTR [esp+0x20],0x1
        mov  DWORD PTR [esp+0x28],edx
        je loc_00436BE2
        cmp  ebp,0x16
        je loc_00436BE2
        mov  eax,DWORD PTR [ecx+0xc]
        mov  edx,DWORD PTR [ecx+0x10]
        mov  DWORD PTR [esp+0x3c],eax
        mov  eax,DWORD PTR [ecx+0x14]
        mov  ecx,DWORD PTR [ecx+0x8]
        mov  DWORD PTR [esp+0x24],0x3
        mov  DWORD PTR [esp+0x40],edx
        mov  DWORD PTR [esp+0x44],eax
        mov  DWORD PTR [esp+0x48],ecx
    loc_00436BE2:
        push  0x0
        push  0x0
        lea  edx,[esp+0x18]
        push  edx
        push  0x0
        lea  eax,[esp+0x24]
        push  eax
        push  0x0
        call  DWORD PTR ds:0x466024
        mov  ebp,eax
        test  ebp,ebp
        jne loc_00436C0C
        pop  ebx
        pop  edi
        pop  esi
        xor  al,al
        pop  ebp
        add  esp,0x70
        ret  0xc
    loc_00436C0C:
        mov  ecx,DWORD PTR [esp+0x28]
        mov  edi,DWORD PTR [esp+0x10]
        mov  edx,ecx
        shr  ecx,0x2
        xor  eax,eax
        rep stosd
        mov  ecx,edx
        and  ecx,0x3
        push  0x0
        rep stosb
        call  DWORD PTR ds:0x466020
        mov  edi,eax
        push  ebp
        push  edi
        call  DWORD PTR ds:0x46602c
        mov  ecx,DWORD PTR [esp+0x10]
        mov  edx,DWORD PTR [esp+0x28]
        mov  DWORD PTR [esi+0x118],eax
        mov  eax,DWORD PTR [esp+0x84]
        mov  DWORD PTR [esi+0x110],ebx
        pop  ebx
        mov  DWORD PTR [esi+0x120],ecx
        mov  ecx,DWORD PTR [esp+0x84]
        mov  DWORD PTR [esi+0x10c],edx
        mov  edx,DWORD PTR [esp+0x88]
        mov  DWORD PTR [esi+0x114],edi
        pop  edi
        mov  DWORD PTR [esi+0x11c],ebp
        mov  DWORD PTR [esi+0x104],eax
        mov  DWORD PTR [esi+0x108],ecx
        mov  DWORD PTR [esi+0x100],edx
        pop  esi
        mov  al,0x1
        pop  ebp
        add  esp,0x70
        ret  0xc
    }
}
