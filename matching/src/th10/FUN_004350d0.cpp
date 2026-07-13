// 004350D0: FUN_004350d0
// Original size: 336 bytes, actual code: 116 instructions
extern "C" void operator_new(void);
extern "C" void _eh_vector_constructor_iterator_(void);
extern "C" void _malloc(void);

extern "C" __declspec(naked) void FUN_004350d0(void) {
    __asm {
        push  0xffffffff
        push  0x4653cb
        mov  eax,fs:0x0
        push  eax
        mov  DWORD PTR fs:0x0,esp
        sub  esp,0x8
        push  ebp
        mov  ebp,DWORD PTR [esp+0x20]
        push  esi
        lea  esi,[ebp+0x1]
        mov  eax,esi
        shl  eax,0x4
        add  eax,0x4
        push  edi
        push  eax
        call operator_new
        add  esp,0x4
        mov  DWORD PTR [esp+0x10],eax
        test  eax,eax
        mov  DWORD PTR [esp+0x1c],0x0
        je loc_00435133
        push  0x435250
        push  0x4352c0
        push  esi
        lea  edi,[eax+0x4]
        push  0x10
        push  edi
        mov  DWORD PTR [eax],esi
        mov  DWORD PTR [esp+0x20],edi
        call _eh_vector_constructor_iterator_
        test  edi,edi
        jne loc_00435149
    loc_00435133:
        pop  edi
        pop  esi
        xor  eax,eax
        pop  ebp
        mov  ecx,DWORD PTR [esp+0x8]
        mov  DWORD PTR fs:0x0,ecx
        add  esp,0x14
        ret  0xc
    loc_00435149:
        test  ebp,ebp
        mov  esi,DWORD PTR [esp+0x24]
        jle loc_004351ED
        mov  ecx,DWORD PTR [esp+0x28]
        lea  ebp,[edi+0x8]
        mov  DWORD PTR [esp+0x24],ecx
    loc_00435160:
        mov  eax,esi
        lea  edx,[eax+0x1]
    loc_00435165:
        mov  cl,BYTE PTR [eax]
        inc  eax
        test  cl,cl
        jne loc_00435165
        sub  eax,edx
        inc  eax
        push  eax
        call _malloc
        add  esp,0x4
        test  eax,eax
        je loc_00435190
        mov  edi,eax
        mov  ecx,esi
        sub  edi,esi
    loc_00435182:
        mov  dl,BYTE PTR [ecx]
        mov  BYTE PTR [edi+ecx*1],dl
        inc  ecx
        test  dl,dl
        jne loc_00435182
        mov  edi,DWORD PTR [esp+0xc]
    loc_00435190:
        mov  DWORD PTR [ebp-0x8],eax
        mov  eax,esi
        lea  edx,[eax+0x1]
    loc_00435198:
        mov  cl,BYTE PTR [eax]
        inc  eax
        test  cl,cl
        jne loc_00435198
        sub  eax,edx
        inc  eax
        mov  ecx,eax
        and  ecx,0x80000003
        jns loc_004351B1
        dec  ecx
        or   ecx,0xfffffffc
        inc  ecx
    loc_004351B1:
        je loc_004351BC
        mov  edx,0x4
        sub  edx,ecx
        add  eax,edx
    loc_004351BC:
        add  esi,eax
        mov  eax,DWORD PTR [esi]
        mov  DWORD PTR [ebp-0x4],eax
        mov  ecx,DWORD PTR [esi+0x4]
        mov  eax,DWORD PTR [esp+0x24]
        add  esi,0x4
        add  esi,0x4
        mov  DWORD PTR [ebp+0x0],ecx
        mov  edx,DWORD PTR [esi]
        mov  DWORD PTR [ebp+0x4],edx
        add  esi,0x4
        add  ebp,0x10
        dec  eax
        mov  DWORD PTR [esp+0x24],eax
        jne loc_00435160
        mov  ebp,DWORD PTR [esp+0x28]
    loc_004351ED:
        mov  ecx,DWORD PTR [esp+0x2c]
        shl  ebp,0x4
        lea  eax,[edi+ebp*1]
        mov  DWORD PTR [eax+0x4],ecx
        mov  ecx,DWORD PTR [esp+0x14]
        mov  DWORD PTR [eax+0x8],0x0
        mov  eax,edi
        pop  edi
        pop  esi
        pop  ebp
        mov  DWORD PTR fs:0x0,ecx
        add  esp,0x14
        ret  0xc
    }
}
