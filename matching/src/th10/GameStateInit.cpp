// 00445900: GameStateInit
// Original size: 2336 bytes, actual code: 670 instructions
extern "C" void FUN_00401de0(void);
extern "C" void FUN_00449ae0(void);
extern "C" void FUN_00449b70(void);
extern "C" void operator_new(void);
extern "C" void _eh_vector_constructor_iterator_(void);

extern "C" __declspec(naked) void GameStateInit(void) {
    __asm {
        push  0xffffffff
        push  0x4657a5
        mov  eax,fs:0x0
        push  eax
        mov  DWORD PTR fs:0x0,esp
        push  ecx
        push  ebx
        push  ebp
        mov  ebp,DWORD PTR [esp+0x1c]
        push  esi
        push  edi
        push  0x401ff0
        push  0x402050
        push  0x1000
        lea  eax,[ebp+0x68]
        push  0x3ac
        push  eax
        call _eh_vector_constructor_iterator_
        lea  edx,[ebp+0x3ad130]
        mov  esi,0xfffffffe
        xor  ebx,ebx
        mov  DWORD PTR [esp+0x1c],ebx
        and  DWORD PTR [edx+0x6c],esi
        and  DWORD PTR [edx+0xb0],esi
        and  DWORD PTR [edx+0xfc],esi
        and  DWORD PTR [edx+0x128],esi
        and  DWORD PTR [edx+0x174],esi
        and  DWORD PTR [edx+0x1b0],esi
        and  DWORD PTR [edx+0x1fc],esi
        and  DWORD PTR [edx+0x228],esi
        and  DWORD PTR [edx+0x378],esi
        mov  ecx,0xeb
        xor  eax,eax
        mov  edi,edx
        rep stosd
        mov  WORD PTR [edx+0x384],0xffff
        push  0x401ff0
        push  0x402050
        push  0x14
        push  0x3ac
        lea  eax,[ebp+0x72dae4]
        push  eax
        mov  BYTE PTR [esp+0x30],0x1
        call _eh_vector_constructor_iterator_
        mov  BYTE PTR [esp+0x1c],0x2
        xor  eax,eax
        mov  ecx,0x1cc918
        mov  edi,ebp
        rep stosd
        mov  DWORD PTR ds:0x4978b4,0x3f800000
        mov  DWORD PTR ds:0x49789c,0x3f800000
        mov  DWORD PTR ds:0x497884,0x3f800000
        mov  DWORD PTR ds:0x49786c,0x3f800000
        mov  ds:0x497870,eax
        mov  ds:0x497874,eax
        mov  DWORD PTR ds:0x497888,0x3f800000
        mov  ds:0x49788c,eax
        mov  ds:0x4978a0,eax
        mov  DWORD PTR ds:0x4978a4,0x3f800000
        mov  DWORD PTR ds:0x4978b8,0x3f800000
        mov  DWORD PTR ds:0x4978bc,0x3f800000
        mov  DWORD PTR ds:0x497920,0x3f800000
        mov  DWORD PTR ds:0x497904,0x3f800000
        mov  DWORD PTR ds:0x4978e8,0x3f800000
        mov  DWORD PTR ds:0x4978cc,0x3f800000
        mov  ds:0x4978d4,eax
        mov  ds:0x4978d8,eax
        mov  DWORD PTR ds:0x4978f0,0x3f800000
        mov  ds:0x4978f4,eax
        mov  ds:0x49790c,eax
        mov  DWORD PTR ds:0x497910,0x3f800000
        mov  DWORD PTR ds:0x497928,0x3f800000
        mov  DWORD PTR ds:0x49792c,0x3f800000
        mov  DWORD PTR [ebp+0x3ada74],ebx
        mov  DWORD PTR [ebp+0x3ada64],ebx
        mov  BYTE PTR [ebp+0x3ada68],bl
        mov  BYTE PTR [ebp+0x3ada69],bl
        mov  DWORD PTR [ebp+0x3ada60],0x1
        mov  BYTE PTR [ebp+0x3ada6a],bl
        mov  BYTE PTR [ebp+0x3ada6c],0xff
        mov  BYTE PTR [ebp+0x3ada6b],bl
        mov  DWORD PTR [ebp+0x4],0xffffffff
        mov  DWORD PTR [ebp+0x0],0xffffffff
        lea  edi,[ebp+0x68]
        mov  DWORD PTR [esp+0x10],0x1000
        jmp loc_00445AE0
        nop
    loc_00445AE0:
        mov  edx,edi
        call FUN_00401de0
        mov  eax,DWORD PTR [esp+0x10]
        add  edi,0x3ac
        dec  eax
        mov  DWORD PTR [esp+0x10],eax
        jne loc_00445AE0
        push  0x24
        call operator_new
        add  esp,0x4
        cmp  eax,ebx
        je loc_00445B26
        mov  ecx,DWORD PTR [eax+0x4]
        and  ecx,esi
        mov  DWORD PTR [eax+0x8],ebx
        mov  DWORD PTR [eax+0xc],ebx
        mov  DWORD PTR [eax+0x10],ebx
        mov  DWORD PTR [eax],ebx
        mov  DWORD PTR [eax+0x4],ecx
        mov  DWORD PTR [eax+0x14],eax
        mov  DWORD PTR [eax+0x18],ebx
        mov  DWORD PTR [eax+0x1c],ebx
        mov  esi,eax
        jmp loc_00445B28
    loc_00445B26:
        xor  esi,esi
    loc_00445B28:
        mov  eax,DWORD PTR [esi+0x4]
        mov  ecx,DWORD PTR ds:0x491be4
        or   eax,0x3
        push  ecx
        mov  edi,0x1a
        mov  DWORD PTR [esi+0x8],0x4485d0
        mov  DWORD PTR [esi+0xc],ebx
        mov  DWORD PTR [esi+0x10],ebx
        mov  DWORD PTR [esi+0x20],ebp
        mov  DWORD PTR [esi+0x4],eax
        call FUN_00449ae0
        push  0x24
        call operator_new
        add  esp,0x4
        cmp  eax,ebx
        je loc_00445B7F
        mov  ecx,DWORD PTR [eax+0x4]
        mov  DWORD PTR [eax+0x8],ebx
        mov  DWORD PTR [eax+0xc],ebx
        mov  DWORD PTR [eax+0x10],ebx
        mov  DWORD PTR [eax],ebx
        and  ecx,0xfffffffe
        mov  DWORD PTR [eax+0x4],ecx
        mov  DWORD PTR [eax+0x14],eax
        mov  DWORD PTR [eax+0x18],ebx
        mov  DWORD PTR [eax+0x1c],ebx
        jmp loc_00445B81
    loc_00445B7F:
        xor  eax,eax
    loc_00445B81:
        mov  ecx,DWORD PTR [eax+0x4]
        mov  edx,DWORD PTR ds:0x491be4
        or   ecx,0x3
        push  edx
        mov  edi,0x8
        mov  esi,eax
        mov  DWORD PTR [eax+0x8],0x4485e0
        mov  DWORD PTR [eax+0xc],ebx
        mov  DWORD PTR [eax+0x10],ebx
        mov  DWORD PTR [eax+0x20],ebp
        mov  DWORD PTR [eax+0x4],ecx
        call FUN_00449ae0
        push  0x24
        call operator_new
        add  esp,0x4
        cmp  eax,ebx
        je loc_00445BDA
        mov  ecx,DWORD PTR [eax+0x4]
        mov  DWORD PTR [eax+0x8],ebx
        mov  DWORD PTR [eax+0xc],ebx
        mov  DWORD PTR [eax+0x10],ebx
        mov  DWORD PTR [eax],ebx
        and  ecx,0xfffffffe
        mov  DWORD PTR [eax+0x4],ecx
        mov  DWORD PTR [eax+0x14],eax
        mov  DWORD PTR [eax+0x18],ebx
        mov  DWORD PTR [eax+0x1c],ebx
        jmp loc_00445BDC
    loc_00445BDA:
        xor  eax,eax
    loc_00445BDC:
        or   DWORD PTR [eax+0x4],0x3
        mov  ecx,DWORD PTR ds:0x491be4
        push  ecx
        mov  edi,0x9
        mov  esi,eax
        mov  DWORD PTR [eax+0x8],0x4485f0
        mov  DWORD PTR [eax+0xc],ebx
        mov  DWORD PTR [eax+0x10],ebx
        mov  DWORD PTR [eax+0x20],ebp
        call FUN_00449b70
        push  0x24
        call operator_new
        add  esp,0x4
        cmp  eax,ebx
        je loc_00445C30
        mov  ecx,DWORD PTR [eax+0x4]
        mov  DWORD PTR [eax+0x8],ebx
        mov  DWORD PTR [eax+0xc],ebx
        mov  DWORD PTR [eax+0x10],ebx
        mov  DWORD PTR [eax],ebx
        and  ecx,0xfffffffe
        mov  DWORD PTR [eax+0x4],ecx
        mov  DWORD PTR [eax+0x14],eax
        mov  DWORD PTR [eax+0x18],ebx
        mov  DWORD PTR [eax+0x1c],ebx
        jmp loc_00445C32
    loc_00445C30:
        xor  eax,eax
    loc_00445C32:
        mov  ecx,DWORD PTR [eax+0x4]
        mov  edx,DWORD PTR ds:0x491be4
        or   ecx,0x3
        push  edx
        mov  edi,0xb
        mov  esi,eax
        mov  DWORD PTR [eax+0x8],0x448600
        mov  DWORD PTR [eax+0xc],ebx
        mov  DWORD PTR [eax+0x10],ebx
        mov  DWORD PTR [eax+0x20],ebp
        mov  DWORD PTR [eax+0x4],ecx
        call FUN_00449b70
        push  0x24
        call operator_new
        add  esp,0x4
        cmp  eax,ebx
        je loc_00445C8B
        mov  ecx,DWORD PTR [eax+0x4]
        mov  DWORD PTR [eax+0x8],ebx
        mov  DWORD PTR [eax+0xc],ebx
        mov  DWORD PTR [eax+0x10],ebx
        mov  DWORD PTR [eax],ebx
        and  ecx,0xfffffffe
        mov  DWORD PTR [eax+0x4],ecx
        mov  DWORD PTR [eax+0x14],eax
        mov  DWORD PTR [eax+0x18],ebx
        mov  DWORD PTR [eax+0x1c],ebx
        jmp loc_00445C8D
    loc_00445C8B:
        xor  eax,eax
    loc_00445C8D:
        or   DWORD PTR [eax+0x4],0x3
        mov  ecx,DWORD PTR ds:0x491be4
        push  ecx
        mov  edi,0xd
        mov  esi,eax
        mov  DWORD PTR [eax+0x8],0x448610
        mov  DWORD PTR [eax+0xc],ebx
        mov  DWORD PTR [eax+0x10],ebx
        mov  DWORD PTR [eax+0x20],ebp
        call FUN_00449b70
        push  0x24
        call operator_new
        add  esp,0x4
        cmp  eax,ebx
        je loc_00445CE1
        mov  ecx,DWORD PTR [eax+0x4]
        mov  DWORD PTR [eax+0x8],ebx
        mov  DWORD PTR [eax+0xc],ebx
        mov  DWORD PTR [eax+0x10],ebx
        mov  DWORD PTR [eax],ebx
        and  ecx,0xfffffffe
        mov  DWORD PTR [eax+0x4],ecx
        mov  DWORD PTR [eax+0x14],eax
        mov  DWORD PTR [eax+0x18],ebx
        mov  DWORD PTR [eax+0x1c],ebx
        jmp loc_00445CE3
    loc_00445CE1:
        xor  eax,eax
    loc_00445CE3:
        mov  ecx,DWORD PTR [eax+0x4]
        mov  edx,DWORD PTR ds:0x491be4
        or   ecx,0x3
        push  edx
        mov  edi,0xf
        mov  esi,eax
        mov  DWORD PTR [eax+0x8],0x448620
        mov  DWORD PTR [eax+0xc],ebx
        mov  DWORD PTR [eax+0x10],ebx
        mov  DWORD PTR [eax+0x20],ebp
        mov  DWORD PTR [eax+0x4],ecx
        call FUN_00449b70
        push  0x24
        call operator_new
        add  esp,0x4
        cmp  eax,ebx
        je loc_00445D3C
        mov  ecx,DWORD PTR [eax+0x4]
        mov  DWORD PTR [eax+0x8],ebx
        mov  DWORD PTR [eax+0xc],ebx
        mov  DWORD PTR [eax+0x10],ebx
        mov  DWORD PTR [eax],ebx
        and  ecx,0xfffffffe
        mov  DWORD PTR [eax+0x4],ecx
        mov  DWORD PTR [eax+0x14],eax
        mov  DWORD PTR [eax+0x18],ebx
        mov  DWORD PTR [eax+0x1c],ebx
        jmp loc_00445D3E
    loc_00445D3C:
        xor  eax,eax
    loc_00445D3E:
        or   DWORD PTR [eax+0x4],0x3
        mov  ecx,DWORD PTR ds:0x491be4
        push  ecx
        mov  edi,0x10
        mov  esi,eax
        mov  DWORD PTR [eax+0x8],0x4486a0
        mov  DWORD PTR [eax+0xc],ebx
        mov  DWORD PTR [eax+0x10],ebx
        mov  DWORD PTR [eax+0x20],ebp
        call FUN_00449b70
        push  0x24
        call operator_new
        add  esp,0x4
        cmp  eax,ebx
        je loc_00445D92
        mov  ecx,DWORD PTR [eax+0x4]
        mov  DWORD PTR [eax+0x8],ebx
        mov  DWORD PTR [eax+0xc],ebx
        mov  DWORD PTR [eax+0x10],ebx
        mov  DWORD PTR [eax],ebx
        and  ecx,0xfffffffe
        mov  DWORD PTR [eax+0x4],ecx
        mov  DWORD PTR [eax+0x14],eax
        mov  DWORD PTR [eax+0x18],ebx
        mov  DWORD PTR [eax+0x1c],ebx
        jmp loc_00445D94
    loc_00445D92:
        xor  eax,eax
    loc_00445D94:
        mov  ecx,DWORD PTR [eax+0x4]
        mov  edx,DWORD PTR ds:0x491be4
        or   ecx,0x3
        push  edx
        mov  edi,0x11
        mov  esi,eax
        mov  DWORD PTR [eax+0x8],0x4486b0
        mov  DWORD PTR [eax+0xc],ebx
        mov  DWORD PTR [eax+0x10],ebx
        mov  DWORD PTR [eax+0x20],ebp
        mov  DWORD PTR [eax+0x4],ecx
        call FUN_00449b70
        push  0x24
        call operator_new
        add  esp,0x4
        cmp  eax,ebx
        je loc_00445DED
        mov  ecx,DWORD PTR [eax+0x4]
        mov  DWORD PTR [eax+0x8],ebx
        mov  DWORD PTR [eax+0xc],ebx
        mov  DWORD PTR [eax+0x10],ebx
        mov  DWORD PTR [eax],ebx
        and  ecx,0xfffffffe
        mov  DWORD PTR [eax+0x4],ecx
        mov  DWORD PTR [eax+0x14],eax
        mov  DWORD PTR [eax+0x18],ebx
        mov  DWORD PTR [eax+0x1c],ebx
        jmp loc_00445DEF
    loc_00445DED:
        xor  eax,eax
    loc_00445DEF:
        or   DWORD PTR [eax+0x4],0x3
        mov  ecx,DWORD PTR ds:0x491be4
        push  ecx
        mov  edi,0x12
        mov  esi,eax
        mov  DWORD PTR [eax+0x8],0x4486c0
        mov  DWORD PTR [eax+0xc],ebx
        mov  DWORD PTR [eax+0x10],ebx
        mov  DWORD PTR [eax+0x20],ebp
        call FUN_00449b70
        push  0x24
        call operator_new
        add  esp,0x4
        cmp  eax,ebx
        je loc_00445E43
        mov  ecx,DWORD PTR [eax+0x4]
        mov  DWORD PTR [eax+0x8],ebx
        mov  DWORD PTR [eax+0xc],ebx
        mov  DWORD PTR [eax+0x10],ebx
        mov  DWORD PTR [eax],ebx
        and  ecx,0xfffffffe
        mov  DWORD PTR [eax+0x4],ecx
        mov  DWORD PTR [eax+0x14],eax
        mov  DWORD PTR [eax+0x18],ebx
        mov  DWORD PTR [eax+0x1c],ebx
        jmp loc_00445E45
    loc_00445E43:
        xor  eax,eax
    loc_00445E45:
        mov  ecx,DWORD PTR [eax+0x4]
        mov  edx,DWORD PTR ds:0x491be4
        or   ecx,0x3
        push  edx
        mov  edi,0x13
        mov  esi,eax
        mov  DWORD PTR [eax+0x8],0x4486d0
        mov  DWORD PTR [eax+0xc],ebx
        mov  DWORD PTR [eax+0x10],ebx
        mov  DWORD PTR [eax+0x20],ebp
        mov  DWORD PTR [eax+0x4],ecx
        call FUN_00449b70
        push  0x24
        call operator_new
        add  esp,0x4
        cmp  eax,ebx
        je loc_00445E9E
        mov  ecx,DWORD PTR [eax+0x4]
        mov  DWORD PTR [eax+0x8],ebx
        mov  DWORD PTR [eax+0xc],ebx
        mov  DWORD PTR [eax+0x10],ebx
        mov  DWORD PTR [eax],ebx
        and  ecx,0xfffffffe
        mov  DWORD PTR [eax+0x4],ecx
        mov  DWORD PTR [eax+0x14],eax
        mov  DWORD PTR [eax+0x18],ebx
        mov  DWORD PTR [eax+0x1c],ebx
        jmp loc_00445EA0
    loc_00445E9E:
        xor  eax,eax
    loc_00445EA0:
        or   DWORD PTR [eax+0x4],0x3
        mov  ecx,DWORD PTR ds:0x491be4
        push  ecx
        mov  edi,0x15
        mov  esi,eax
        mov  DWORD PTR [eax+0x8],0x4486e0
        mov  DWORD PTR [eax+0xc],ebx
        mov  DWORD PTR [eax+0x10],ebx
        mov  DWORD PTR [eax+0x20],ebp
        call FUN_00449b70
        push  0x24
        call operator_new
        add  esp,0x4
        cmp  eax,ebx
        je loc_00445EF4
        mov  ecx,DWORD PTR [eax+0x4]
        mov  DWORD PTR [eax+0x8],ebx
        mov  DWORD PTR [eax+0xc],ebx
        mov  DWORD PTR [eax+0x10],ebx
        mov  DWORD PTR [eax],ebx
        and  ecx,0xfffffffe
        mov  DWORD PTR [eax+0x4],ecx
        mov  DWORD PTR [eax+0x14],eax
        mov  DWORD PTR [eax+0x18],ebx
        mov  DWORD PTR [eax+0x1c],ebx
        jmp loc_00445EF6
    loc_00445EF4:
        xor  eax,eax
    loc_00445EF6:
        mov  ecx,DWORD PTR [eax+0x4]
        mov  edx,DWORD PTR ds:0x491be4
        or   ecx,0x3
        push  edx
        mov  edi,0x17
        mov  esi,eax
        mov  DWORD PTR [eax+0x8],0x4486f0
        mov  DWORD PTR [eax+0xc],ebx
        mov  DWORD PTR [eax+0x10],ebx
        mov  DWORD PTR [eax+0x20],ebp
        mov  DWORD PTR [eax+0x4],ecx
        call FUN_00449b70
        push  0x24
        call operator_new
        add  esp,0x4
        cmp  eax,ebx
        je loc_00445F4F
        mov  ecx,DWORD PTR [eax+0x4]
        mov  DWORD PTR [eax+0x8],ebx
        mov  DWORD PTR [eax+0xc],ebx
        mov  DWORD PTR [eax+0x10],ebx
        mov  DWORD PTR [eax],ebx
        and  ecx,0xfffffffe
        mov  DWORD PTR [eax+0x4],ecx
        mov  DWORD PTR [eax+0x14],eax
        mov  DWORD PTR [eax+0x18],ebx
        mov  DWORD PTR [eax+0x1c],ebx
        jmp loc_00445F51
    loc_00445F4F:
        xor  eax,eax
    loc_00445F51:
        or   DWORD PTR [eax+0x4],0x3
        mov  ecx,DWORD PTR ds:0x491be4
        push  ecx
        mov  edi,0x18
        mov  esi,eax
        mov  DWORD PTR [eax+0x8],0x448700
        mov  DWORD PTR [eax+0xc],ebx
        mov  DWORD PTR [eax+0x10],ebx
        mov  DWORD PTR [eax+0x20],ebp
        call FUN_00449b70
        push  0x24
        call operator_new
        add  esp,0x4
        cmp  eax,ebx
        je loc_00445FA5
        mov  ecx,DWORD PTR [eax+0x4]
        mov  DWORD PTR [eax+0x8],ebx
        mov  DWORD PTR [eax+0xc],ebx
        mov  DWORD PTR [eax+0x10],ebx
        mov  DWORD PTR [eax],ebx
        and  ecx,0xfffffffe
        mov  DWORD PTR [eax+0x4],ecx
        mov  DWORD PTR [eax+0x14],eax
        mov  DWORD PTR [eax+0x18],ebx
        mov  DWORD PTR [eax+0x1c],ebx
        jmp loc_00445FA7
    loc_00445FA5:
        xor  eax,eax
    loc_00445FA7:
        mov  ecx,DWORD PTR [eax+0x4]
        mov  edx,DWORD PTR ds:0x491be4
        or   ecx,0x3
        push  edx
        mov  edi,0x1a
        mov  esi,eax
        mov  DWORD PTR [eax+0x8],0x448710
        mov  DWORD PTR [eax+0xc],ebx
        mov  DWORD PTR [eax+0x10],ebx
        mov  DWORD PTR [eax+0x20],ebp
        mov  DWORD PTR [eax+0x4],ecx
        call FUN_00449b70
        push  0x24
        call operator_new
        add  esp,0x4
        cmp  eax,ebx
        je loc_00446000
        mov  ecx,DWORD PTR [eax+0x4]
        mov  DWORD PTR [eax+0x8],ebx
        mov  DWORD PTR [eax+0xc],ebx
        mov  DWORD PTR [eax+0x10],ebx
        mov  DWORD PTR [eax],ebx
        and  ecx,0xfffffffe
        mov  DWORD PTR [eax+0x4],ecx
        mov  DWORD PTR [eax+0x14],eax
        mov  DWORD PTR [eax+0x18],ebx
        mov  DWORD PTR [eax+0x1c],ebx
        jmp loc_00446002
    loc_00446000:
        xor  eax,eax
    loc_00446002:
        or   DWORD PTR [eax+0x4],0x3
        mov  ecx,DWORD PTR ds:0x491be4
        push  ecx
        mov  edi,0x1c
        mov  esi,eax
        mov  DWORD PTR [eax+0x8],0x448720
        mov  DWORD PTR [eax+0xc],ebx
        mov  DWORD PTR [eax+0x10],ebx
        mov  DWORD PTR [eax+0x20],ebp
        call FUN_00449b70
        push  0x24
        call operator_new
        add  esp,0x4
        cmp  eax,ebx
        je loc_00446056
        mov  ecx,DWORD PTR [eax+0x4]
        mov  DWORD PTR [eax+0x8],ebx
        mov  DWORD PTR [eax+0xc],ebx
        mov  DWORD PTR [eax+0x10],ebx
        mov  DWORD PTR [eax],ebx
        and  ecx,0xfffffffe
        mov  DWORD PTR [eax+0x4],ecx
        mov  DWORD PTR [eax+0x14],eax
        mov  DWORD PTR [eax+0x18],ebx
        mov  DWORD PTR [eax+0x1c],ebx
        jmp loc_00446058
    loc_00446056:
        xor  eax,eax
    loc_00446058:
        mov  ecx,DWORD PTR [eax+0x4]
        mov  edx,DWORD PTR ds:0x491be4
        or   ecx,0x3
        push  edx
        mov  edi,0x21
        mov  esi,eax
        mov  DWORD PTR [eax+0x8],0x448730
        mov  DWORD PTR [eax+0xc],ebx
        mov  DWORD PTR [eax+0x10],ebx
        mov  DWORD PTR [eax+0x20],ebp
        mov  DWORD PTR [eax+0x4],ecx
        call FUN_00449b70
        push  0x24
        call operator_new
        add  esp,0x4
        cmp  eax,ebx
        je loc_004460B1
        mov  ecx,DWORD PTR [eax+0x4]
        mov  DWORD PTR [eax+0x8],ebx
        mov  DWORD PTR [eax+0xc],ebx
        mov  DWORD PTR [eax+0x10],ebx
        mov  DWORD PTR [eax],ebx
        and  ecx,0xfffffffe
        mov  DWORD PTR [eax+0x4],ecx
        mov  DWORD PTR [eax+0x14],eax
        mov  DWORD PTR [eax+0x18],ebx
        mov  DWORD PTR [eax+0x1c],ebx
        jmp loc_004460B3
    loc_004460B1:
        xor  eax,eax
    loc_004460B3:
        or   DWORD PTR [eax+0x4],0x3
        mov  ecx,DWORD PTR ds:0x491be4
        push  ecx
        mov  edi,0x24
        mov  esi,eax
        mov  DWORD PTR [eax+0x8],0x448740
        mov  DWORD PTR [eax+0xc],ebx
        mov  DWORD PTR [eax+0x10],ebx
        mov  DWORD PTR [eax+0x20],ebp
        call FUN_00449b70
        push  edi
        call operator_new
        add  esp,0x4
        cmp  eax,ebx
        je loc_00446106
        mov  ecx,DWORD PTR [eax+0x4]
        mov  DWORD PTR [eax+0x8],ebx
        mov  DWORD PTR [eax+0xc],ebx
        mov  DWORD PTR [eax+0x10],ebx
        mov  DWORD PTR [eax],ebx
        and  ecx,0xfffffffe
        mov  DWORD PTR [eax+0x4],ecx
        mov  DWORD PTR [eax+0x14],eax
        mov  DWORD PTR [eax+0x18],ebx
        mov  DWORD PTR [eax+0x1c],ebx
        jmp loc_00446108
    loc_00446106:
        xor  eax,eax
    loc_00446108:
        mov  ecx,DWORD PTR [eax+0x4]
        mov  edx,DWORD PTR ds:0x491be4
        or   ecx,0x3
        push  edx
        mov  edi,0x29
        mov  esi,eax
        mov  DWORD PTR [eax+0x8],0x448770
        mov  DWORD PTR [eax+0xc],ebx
        mov  DWORD PTR [eax+0x10],ebx
        mov  DWORD PTR [eax+0x20],ebp
        mov  DWORD PTR [eax+0x4],ecx
        call FUN_00449b70
        push  0x24
        call operator_new
        add  esp,0x4
        cmp  eax,ebx
        je loc_00446161
        mov  ecx,DWORD PTR [eax+0x4]
        mov  DWORD PTR [eax+0x8],ebx
        mov  DWORD PTR [eax+0xc],ebx
        mov  DWORD PTR [eax+0x10],ebx
        mov  DWORD PTR [eax],ebx
        and  ecx,0xfffffffe
        mov  DWORD PTR [eax+0x4],ecx
        mov  DWORD PTR [eax+0x14],eax
        mov  DWORD PTR [eax+0x18],ebx
        mov  DWORD PTR [eax+0x1c],ebx
        jmp loc_00446163
    loc_00446161:
        xor  eax,eax
    loc_00446163:
        or   DWORD PTR [eax+0x4],0x3
        mov  ecx,DWORD PTR ds:0x491be4
        push  ecx
        mov  edi,0x2a
        mov  esi,eax
        mov  DWORD PTR [eax+0x8],0x4487c0
        mov  DWORD PTR [eax+0xc],ebx
        mov  DWORD PTR [eax+0x10],ebx
        mov  DWORD PTR [eax+0x20],ebp
        call FUN_00449b70
        push  0x24
        call operator_new
        add  esp,0x4
        cmp  eax,ebx
        je loc_004461B7
        mov  ecx,DWORD PTR [eax+0x4]
        mov  DWORD PTR [eax+0x8],ebx
        mov  DWORD PTR [eax+0xc],ebx
        mov  DWORD PTR [eax+0x10],ebx
        mov  DWORD PTR [eax],ebx
        and  ecx,0xfffffffe
        mov  DWORD PTR [eax+0x4],ecx
        mov  DWORD PTR [eax+0x14],eax
        mov  DWORD PTR [eax+0x18],ebx
        mov  DWORD PTR [eax+0x1c],ebx
        jmp loc_004461B9
    loc_004461B7:
        xor  eax,eax
    loc_004461B9:
        mov  ecx,DWORD PTR [eax+0x4]
        mov  edx,DWORD PTR ds:0x491be4
        or   ecx,0x3
        push  edx
        mov  edi,0x2d
        mov  esi,eax
        mov  DWORD PTR [eax+0x8],0x448810
        mov  DWORD PTR [eax+0xc],ebx
        mov  DWORD PTR [eax+0x10],ebx
        mov  DWORD PTR [eax+0x20],ebp
        mov  DWORD PTR [eax+0x4],ecx
        call FUN_00449b70
        mov  eax,ds:0x491c30
        mov  ecx,DWORD PTR [eax]
        push  ebx
        push  eax
        call  DWORD PTR [ecx+0x170]
        mov  ecx,DWORD PTR [esp+0x14]
        pop  edi
        pop  esi
        mov  eax,ebp
        pop  ebp
        pop  ebx
        mov  DWORD PTR fs:0x0,ecx
        add  esp,0x10
        ret  0x4
    }
}
