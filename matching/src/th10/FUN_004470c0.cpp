// 004470C0: FUN_004470c0
// Original size: 448 bytes, actual code: 136 instructions
extern "C" void FUN_004472e0(void);
extern "C" void FUN_0044b360(void);
extern "C" void FUN_0044b8e0(void);
extern "C" void operator_new(void);
extern "C" void _malloc(void);
extern "C" void _sprintf(void);
extern "C" void __security_check_cookie(void);

extern "C" __declspec(naked) void FUN_004470c0(void) {
    __asm {
        sub  esp,0x110
        mov  eax,ds:0x473660
        xor  eax,esp
        push  ebp
        mov  ebp,DWORD PTR [esp+0x120]
        push  edi
        mov  edi,DWORD PTR [esp+0x120]
        cmp  edi,0x21
        mov  DWORD PTR [esp+0x114],eax
        mov  eax,DWORD PTR [esp+0x11c]
        mov  DWORD PTR [esp+0x8],eax
        jl loc_0044710D
        push  0x470384
        mov  edi,0x474f70
        call FUN_0044b8e0
        add  esp,0x4
        xor  eax,eax
        jmp loc_00447258
    loc_0044710D:
        push  ebx
        push  esi
        push  ebp
        lea  ecx,[esp+0x1c]
        push  0x46e1c8
        push  ecx
        call _sprintf
        add  esp,0xc
        push  0x0
        push  0x0
        lea  eax,[esp+0x20]
        call FUN_0044b360
        push  0x130
        mov  ebx,eax
        mov  DWORD PTR [esp+0x18],0x0
        call operator_new
        mov  esi,eax
        add  esp,0x4
        test  esi,esi
        je loc_00447160
        mov  ecx,0x4c
        xor  eax,eax
        mov  edi,esi
        rep stosd
        mov  edi,DWORD PTR [esp+0x128]
        jmp loc_00447162
    loc_00447160:
        xor  esi,esi
    loc_00447162:
        test  ebx,ebx
        mov  edx,DWORD PTR [esp+0x10]
        mov  DWORD PTR [edx+edi*4+0x3ad06c],esi
        je loc_00447250
        lea  edx,[esi+0x4]
        mov  DWORD PTR [esi],edi
        mov  DWORD PTR [esi+0x108],ebx
        mov  eax,ebp
        sub  edx,ebp
    loc_00447184:
        mov  cl,BYTE PTR [eax]
        mov  BYTE PTR [edx+eax*1],cl
        inc  eax
        test  cl,cl
        jne loc_00447184
        mov  edx,DWORD PTR [ebx+0x38]
        test  edx,edx
        mov  edi,DWORD PTR [ebx]
        mov  ebp,DWORD PTR [ebx+0x4]
        mov  eax,ebx
        mov  ecx,0x1
        mov  DWORD PTR [esp+0x10],edi
        je loc_004471B8
    loc_004471A5:
        add  eax,edx
        add  ebp,DWORD PTR [eax+0x4]
        add  edi,DWORD PTR [eax]
        mov  edx,DWORD PTR [eax+0x38]
        inc  ecx
        test  edx,edx
        jne loc_004471A5
        mov  DWORD PTR [esp+0x10],edi
    loc_004471B8:
        mov  DWORD PTR [esi+0x10c],ecx
        shl  ecx,0x4
        mov  edi,ecx
        push  edi
        call _malloc
        mov  edx,eax
        mov  ecx,edi
        mov  DWORD PTR [esi+0x120],edx
        mov  edi,edx
        mov  edx,ecx
        shr  ecx,0x2
        xor  eax,eax
        rep stosd
        mov  ecx,edx
        and  ecx,0x3
        rep stosb
        mov  edi,DWORD PTR [esp+0x14]
        mov  eax,edi
        imul  eax,eax,0x44
        push  eax
        call _malloc
        lea  ecx,[ebp*4+0x0]
        push  ecx
        mov  DWORD PTR [esi+0x118],eax
        call _malloc
        add  esp,0xc
        push  ebx
        xor  ecx,ecx
        mov  edx,esi
        mov  DWORD PTR [esi+0x11c],eax
        mov  DWORD PTR [esi+0x110],ebp
        mov  DWORD PTR [esi+0x114],edi
        call FUN_004472e0
        test  eax,eax
        jl loc_00447250
        lea  ebx,[ebx+0x0]
    loc_00447230:
        mov  edx,DWORD PTR [esp+0x14]
        mov  eax,DWORD PTR [ebx+0x38]
        inc  edx
        test  eax,eax
        mov  DWORD PTR [esp+0x14],edx
        je loc_00447254
        add  ebx,eax
        mov  ecx,edx
        push  ebx
        mov  edx,esi
        call FUN_004472e0
        test  eax,eax
        jge loc_00447230
    loc_00447250:
        xor  eax,eax
        jmp loc_00447256
    loc_00447254:
        mov  eax,esi
    loc_00447256:
        pop  esi
        pop  ebx
    loc_00447258:
        mov  ecx,DWORD PTR [esp+0x114]
        pop  edi
        pop  ebp
        xor  ecx,esp
        call __security_check_cookie
        add  esp,0x110
        ret  0xc
    }
}
