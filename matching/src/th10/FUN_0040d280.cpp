// 0040D280: FUN_0040d280
// Original size: 688 bytes, actual code: 120 instructions
extern "C" void FUN_00449ae0(void);
extern "C" void FUN_00449b70(void);
extern "C" void operator_new(void);

extern "C" __declspec(naked) void FUN_0040d280(void) {
    __asm {
        mov  eax,ds:0x4776f0
        mov  ecx,DWORD PTR [eax+0x3e0b50]
        push  ebp
        push  edi
        push  0x1098
        mov  DWORD PTR [ebx+0x30],ecx
        call operator_new
        mov  edx,eax
        xor  ebp,ebp
        add  esp,0x4
        cmp  edx,ebp
        je loc_0040D2C6
        mov  DWORD PTR [edx+0x1090],ebp
        mov  DWORD PTR [edx+0x1094],ebp
        mov  ecx,0x426
        xor  eax,eax
        mov  edi,edx
        rep stosd
        mov  DWORD PTR [edx],0x46d0b4
        mov  ecx,edx
        jmp loc_0040D2C8
    loc_0040D2C6:
        xor  ecx,ecx
    loc_0040D2C8:
        mov  eax,DWORD PTR [esp+0xc]
        push  esi
        mov  DWORD PTR [ebx+0x54],ecx
        mov  edx,DWORD PTR [ecx]
        push  eax
        call  DWORD PTR [edx+0x8]
        push  0x24
        call operator_new
        add  esp,0x4
        cmp  eax,ebp
        je loc_0040D305
        mov  ecx,DWORD PTR [eax+0x4]
        mov  DWORD PTR [eax+0x8],ebp
        mov  DWORD PTR [eax+0xc],ebp
        mov  DWORD PTR [eax+0x10],ebp
        mov  DWORD PTR [eax],ebp
        and  ecx,0xfffffffe
        mov  DWORD PTR [eax+0x4],ecx
        mov  DWORD PTR [eax+0x14],eax
        mov  DWORD PTR [eax+0x18],ebp
        mov  DWORD PTR [eax+0x1c],ebp
        mov  esi,eax
        jmp loc_0040D307
    loc_0040D305:
        xor  esi,esi
    loc_0040D307:
        mov  ecx,DWORD PTR [esi+0x4]
        mov  edx,DWORD PTR ds:0x491be4
        and  ecx,0xfffffffd
        or   ecx,0x1
        push  edx
        mov  edi,0x12
        mov  DWORD PTR [esi+0x8],0x40d810
        mov  DWORD PTR [esi+0xc],ebp
        mov  DWORD PTR [esi+0x10],ebp
        mov  DWORD PTR [esi+0x20],ebx
        mov  DWORD PTR [esi+0x4],ecx
        call FUN_00449ae0
        push  0x24
        mov  DWORD PTR [ebx+0x8],esi
        call operator_new
        add  esp,0x4
        cmp  eax,ebp
        je loc_0040D366
        mov  ecx,DWORD PTR [eax+0x4]
        mov  DWORD PTR [eax+0x8],ebp
        mov  DWORD PTR [eax+0xc],ebp
        mov  DWORD PTR [eax+0x10],ebp
        mov  DWORD PTR [eax],ebp
        and  ecx,0xfffffffe
        mov  DWORD PTR [eax+0x4],ecx
        mov  DWORD PTR [eax+0x14],eax
        mov  DWORD PTR [eax+0x18],ebp
        mov  DWORD PTR [eax+0x1c],ebp
        mov  esi,eax
        jmp loc_0040D368
    loc_0040D366:
        xor  esi,esi
    loc_0040D368:
        mov  eax,DWORD PTR [esi+0x4]
        mov  ecx,DWORD PTR ds:0x491be4
        and  eax,0xfffffffd
        or   eax,0x1
        push  ecx
        mov  edi,0x14
        mov  DWORD PTR [esi+0x8],0x40d820
        mov  DWORD PTR [esi+0xc],ebp
        mov  DWORD PTR [esi+0x10],ebp
        mov  DWORD PTR [esi+0x20],ebx
        mov  DWORD PTR [esi+0x4],eax
        call FUN_00449b70
        mov  DWORD PTR [ebx+0xc],esi
        mov  eax,DWORD PTR [ebx+0x50]
        test  al,0x1
        pop  esi
        jne loc_0040D3BA
        or   eax,0x1
        mov  DWORD PTR [ebx+0x44],ebp
        mov  DWORD PTR [ebx+0x40],0xfff0bdc1
        mov  DWORD PTR [ebx+0x48],ebp
        mov  DWORD PTR [ebx+0x4c],0x476f78
        mov  DWORD PTR [ebx+0x50],eax
    loc_0040D3BA:
        pop  edi
        mov  DWORD PTR [ebx+0x44],ebp
        mov  DWORD PTR [ebx+0x48],ebp
        mov  DWORD PTR [ebx+0x40],0xffffffff
        xor  eax,eax
        pop  ebp
        ret  0x4
    }
}
