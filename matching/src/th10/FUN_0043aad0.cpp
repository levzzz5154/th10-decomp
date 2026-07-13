// 0043AAD0: FUN_0043aad0
// Original size: 528 bytes, actual code: 158 instructions
extern "C" void FUN_0043A9B0(void);
extern "C" void FUN_0043aa60(void);
extern "C" void _free(void);
extern "C" void _malloc(void);
extern "C" void __security_check_cookie(void);

extern "C" __declspec(naked) void FUN_0043aad0(void) {
    __asm {
        sub  esp,0x18
        mov  eax,ds:0x473660
        xor  eax,esp
        push  ebp
        push  esi
        mov  esi,ebx
        mov  DWORD PTR [esp+0x1c],eax
        call FUN_0043aa60
        mov  eax,DWORD PTR [esp+0x24]
        mov  ebp,DWORD PTR [ebx+eax*4+0x98]
        test  ebp,ebp
        jne loc_0043AB0C
        pop  esi
        or   eax,0xffffffff
        pop  ebp
        mov  ecx,DWORD PTR [esp+0x14]
        xor  ecx,esp
        call __security_check_cookie
        add  esp,0x18
        ret  0x4
    loc_0043AB0C:
        mov  eax,DWORD PTR [ebp+0x4]
        mov  ecx,DWORD PTR [ebp+0x0]
        mov  DWORD PTR [esp+0x14],ecx
        mov  edx,eax
        mov  ecx,eax
        mov  BYTE PTR [esp+0xa],ah
        mov  BYTE PTR [esp+0xb],al
        mov  DWORD PTR [esp+0x18],eax
        shr  ecx,0x10
        mov  BYTE PTR [esp+0x9],cl
        add  ebp,0x8
        mov  eax,ebp
        mov  cx,WORD PTR [eax]
        shr  edx,0x18
        mov  BYTE PTR [esp+0x8],dl
        push  edi
        mov  edi,DWORD PTR [esp+0xc]
        mov  BYTE PTR [esp+0xc],ch
        mov  BYTE PTR [esp+0xd],cl
        movzx edx,WORD PTR [esp+0xc]
        mov  DWORD PTR [ebx+0x11c],edx
        mov  cx,WORD PTR [eax+0x4]
        mov  BYTE PTR [esp+0xc],ch
        mov  BYTE PTR [esp+0xd],cl
        movzx ecx,WORD PTR [esp+0xc]
        mov  DWORD PTR [ebx+0x120],ecx
        mov  ax,WORD PTR [eax+0x2]
        mov  BYTE PTR [esp+0xc],ah
        mov  BYTE PTR [esp+0xd],al
        movzx eax,WORD PTR [esp+0xc]
        mov  DWORD PTR [ebx+0x118],eax
        shl  eax,0x5
        push  eax
        add  ebp,edi
        call _malloc
        mov  ecx,DWORD PTR [ebx+0x118]
        shl  ecx,0x5
        mov  edx,ecx
        mov  edi,eax
        shr  ecx,0x2
        xor  eax,eax
        mov  DWORD PTR [ebx+0x138],edi
        rep stosd
        mov  ecx,edx
        and  ecx,0x3
        rep stosb
        mov  eax,DWORD PTR [ebx+0x118]
        add  esp,0x4
        test  eax,eax
        mov  DWORD PTR [esp+0x18],0x0
        jle loc_0043AC69
        xor  edi,edi
        mov  DWORD PTR [esp+0x10],edi
        jmp loc_0043ABD3
    loc_0043ABCF:
        mov  edi,DWORD PTR [esp+0x10]
    loc_0043ABD3:
        mov  eax,ebp
        mov  eax,DWORD PTR [eax+0x4]
        mov  ecx,eax
        mov  edx,eax
        shr  ecx,0x18
        shr  edx,0x10
        mov  BYTE PTR [esp+0xe],ah
        mov  BYTE PTR [esp+0xf],al
        mov  BYTE PTR [esp+0xc],cl
        mov  BYTE PTR [esp+0xd],dl
        mov  esi,DWORD PTR [esp+0xc]
        mov  DWORD PTR [esp+0x14],eax
        mov  eax,DWORD PTR [ebx+0x138]
        push  esi
        add  ebp,0x8
        mov  DWORD PTR [edi+eax*1+0x8],esi
        call _malloc
        mov  ecx,DWORD PTR [ebx+0x138]
        mov  DWORD PTR [edi+ecx*1+0x10],eax
        mov  edx,DWORD PTR [ebx+0x138]
        mov  DWORD PTR [edi+edx*1],0x1
        mov  eax,DWORD PTR [ebx+0x138]
        mov  edi,DWORD PTR [edi+eax*1+0x10]
        mov  eax,DWORD PTR [esp+0x1c]
        mov  ecx,esi
        mov  edx,ecx
        shr  ecx,0x2
        mov  esi,ebp
        rep movsd
        mov  ecx,edx
        and  ecx,0x3
        rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
        mov  ecx,DWORD PTR [ebx+0x118]
        mov  edi,edx
        mov  edx,DWORD PTR [esp+0x14]
        add  esp,0x4
        add  ebp,edi
        inc  eax
        add  edx,0x20
        cmp  eax,ecx
        mov  DWORD PTR [esp+0x18],eax
        mov  DWORD PTR [esp+0x10],edx
        jl loc_0043ABCF
    loc_0043AC69:
        mov  eax,DWORD PTR [esp+0x28]
        mov  ecx,DWORD PTR [esp+0x20]
        pop  edi
        pop  esi
        pop  ebp
        mov  DWORD PTR [ebx+0x10],eax
        xor  ecx,esp
        mov  DWORD PTR [ebx+0x124],0xf4240
        xor  eax,eax
        call __security_check_cookie
        add  esp,0x18
        ret  0x4
        push  ebx
        push  esi
        mov  ebx,ecx
        push  eax
        mov  esi,0x1f
        mov  eax,ebx
        call FUN_0043A9B0
        test  eax,eax
        je loc_0043ACAB
        pop  esi
        or   eax,0xffffffff
        pop  ebx
        ret
    loc_0043ACAB:
        push  0x1f
        call FUN_0043aad0
        mov  eax,DWORD PTR [ebx+0x114]
        xor  esi,esi
        cmp  eax,esi
        je loc_0043ACCD
        push  eax
        call _free
        add  esp,0x4
        mov  DWORD PTR [ebx+0x114],esi
    loc_0043ACCD:
        mov  DWORD PTR [ebx+0x114],esi
        pop  esi
        xor  eax,eax
        pop  ebx
        ret
    }
}
