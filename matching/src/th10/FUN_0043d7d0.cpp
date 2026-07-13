// 0043D7D0: FUN_0043d7d0
// Original size: 384 bytes, actual code: 121 instructions
extern "C" void FUN_0043d2a0(void);
extern "C" void _free(void);
extern "C" void _malloc(void);

extern "C" __declspec(naked) void FUN_0043d7d0(void) {
    __asm {
        push  ecx
        push  ebx
        push  ebp
        mov  ebp,DWORD PTR [esp+0x10]
        mov  ebx,eax
        mov  eax,DWORD PTR [esi+ebp*4+0x1ec0]
        test  eax,eax
        push  edi
        je loc_0043D824
        mov  eax,ebp
        shl  eax,0x8
        lea  edi,[eax+esi*1+0x4108]
        mov  eax,ebx
    loc_0043D7F3:
        mov  dl,BYTE PTR [eax]
        mov  cl,dl
        cmp  dl,BYTE PTR [edi]
        jne loc_0043D817
        test  cl,cl
        je loc_0043D813
        mov  dl,BYTE PTR [eax+0x1]
        mov  cl,dl
        cmp  dl,BYTE PTR [edi+0x1]
        jne loc_0043D817
        add  eax,0x2
        add  edi,0x2
        test  cl,cl
        jne loc_0043D7F3
    loc_0043D813:
        xor  eax,eax
        jmp loc_0043D81C
    loc_0043D817:
        sbb  eax,eax
        sbb  eax,0xffffffff
    loc_0043D81C:
        test  eax,eax
        je loc_0043D938
    loc_0043D824:
        mov  ecx,ebp
        shl  ecx,0x8
        lea  edx,[ecx+0x496698]
        mov  eax,ebx
        sub  edx,ebx
    loc_0043D833:
        mov  cl,BYTE PTR [eax]
        mov  BYTE PTR [edx+eax*1],cl
        inc  eax
        test  cl,cl
        jne loc_0043D833
        test  BYTE PTR ds:0x491d78,0x10
        je loc_0043D938
        mov  eax,DWORD PTR [esi+0x610]
        test  eax,eax
        je loc_0043D938
        mov  eax,DWORD PTR [esi+ebp*4+0x1ec0]
        test  eax,eax
        je loc_0043D877
        push  eax
        call _free
        add  esp,0x4
        mov  DWORD PTR [esi+ebp*4+0x1ec0],0x0
    loc_0043D877:
        push  0x0
        push  0x8000080
        push  0x3
        push  0x0
        push  0x1
        push  0x80000000
        lea  edx,[esi+0x5108]
        push  edx
        call  DWORD PTR ds:0x4660c4
        mov  ebp,eax
        cmp  ebp,0xffffffff
        je loc_0043D8E0
        push  esi
        mov  ecx,ebx
        call FUN_0043d2a0
        mov  edi,eax
        mov  eax,DWORD PTR [esi+0x1f84]
        imul  edi,edi,0x34
        mov  ecx,DWORD PTR [eax+edi*1+0x10]
        push  0x0
        push  0x0
        push  ecx
        push  ebp
        call  DWORD PTR ds:0x4660c8
        mov  edx,DWORD PTR [esi+0x1f84]
        mov  eax,DWORD PTR [edx+edi*1+0x14]
        push  eax
        call _malloc
        mov  ebx,eax
        add  esp,0x4
        test  ebx,ebx
        jne loc_0043D8EA
        push  ebp
        call  DWORD PTR ds:0x4660cc
    loc_0043D8E0:
        pop  edi
        pop  ebp
        or   eax,0xffffffff
        pop  ebx
        pop  ecx
        ret  0x4
    loc_0043D8EA:
        mov  ecx,DWORD PTR [esi+0x1f84]
        mov  edx,DWORD PTR [ecx+edi*1+0x14]
        push  0x0
        lea  eax,[esp+0x10]
        push  eax
        push  edx
        push  ebx
        push  ebp
        call  DWORD PTR ds:0x4660d0
        push  ebp
        call  DWORD PTR ds:0x4660cc
        mov  ecx,DWORD PTR [esi+0x1f84]
        mov  eax,DWORD PTR [esp+0x14]
        add  ecx,edi
        mov  edx,ecx
        mov  DWORD PTR [esi+eax*4+0x1e80],ecx
        mov  DWORD PTR [esi+eax*4+0x1ec0],ebx
        mov  DWORD PTR [esi+eax*4+0x1f00],ebx
        mov  ecx,DWORD PTR [edx+0x14]
        mov  DWORD PTR [esi+eax*4+0x1f40],ecx
    loc_0043D938:
        pop  edi
        pop  ebp
        xor  eax,eax
        pop  ebx
        pop  ecx
        ret  0x4
    }
}
