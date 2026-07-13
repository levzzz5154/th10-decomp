// 0042F8B0: FUN_0042f8b0
// Original size: 2464 bytes, actual code: 748 instructions
extern "C" void FUN_0043e5a0(void);
extern "C" void FUN_004491c0(void);

extern "C" __declspec(naked) void FUN_0042f8b0(void) {
    __asm {
        push  ebx
        push  esi
        push  edi
        mov  edi,DWORD PTR ds:0x491c10
        mov  esi,eax
        mov  eax,DWORD PTR [esi+0x2cc]
        push  eax
        mov  edx,edi
        call FUN_004491c0
        xor  ebx,ebx
        cmp  eax,ebx
        jne loc_0042F8D5
        mov  DWORD PTR [esi+0x2cc],ebx
    loc_0042F8D5:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042F8F7
        mov  ecx,0x43
    loc_0042F8E1:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_0043018D
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042F8E1
    loc_0042F8F7:
        xor  eax,eax
    loc_0042F8F9:
        push  eax
        mov  edx,edi
        call FUN_004491c0
        mov  ecx,eax
        cmp  ecx,ebx
        je loc_0042F92E
        movsx edx,WORD PTR [esi+0x59cc]
        mov  eax,0x66666667
        imul  edx
        sar  edx,0x2
        mov  eax,edx
        shr  eax,0x1f
        lea  edx,[edx+eax*1+0x33]
        mov  eax,ecx
        mov  ecx,DWORD PTR [ecx+0x308]
        call FUN_0043e5a0
    loc_0042F92E:
        mov  ecx,DWORD PTR [esi+0x2cc]
        push  ecx
        mov  edx,edi
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042F946
        mov  DWORD PTR [esi+0x2cc],ebx
    loc_0042F946:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042F976
        mov  ecx,0x44
        jmp loc_0042F960
        nop
        jmp loc_0042F960
        nop
    loc_0042F960:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_00430196
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042F960
    loc_0042F976:
        xor  eax,eax
    loc_0042F978:
        push  ebp
        push  eax
        mov  edx,edi
        call FUN_004491c0
        mov  ecx,eax
        cmp  ecx,ebx
        je loc_0042F9A6
        movsx eax,WORD PTR [esi+0x59cc]
        cdq
        mov  ebp,0xa
        idiv  ebp
        mov  eax,ecx
        mov  ecx,DWORD PTR [ecx+0x308]
        add  edx,0x33
        call FUN_0043e5a0
    loc_0042F9A6:
        mov  ecx,DWORD PTR [esi+0x2cc]
        push  ecx
        mov  edx,edi
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042F9BE
        mov  DWORD PTR [esi+0x2cc],ebx
    loc_0042F9BE:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042F9E6
        mov  ecx,0x4d
        lea  ebx,[ebx+0x0]
    loc_0042F9D0:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_0043019F
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042F9D0
    loc_0042F9E6:
        xor  eax,eax
    loc_0042F9E8:
        push  eax
        mov  edx,edi
        call FUN_004491c0
        mov  ecx,eax
        cmp  ecx,ebx
        je loc_0042FA1D
        movsx edx,WORD PTR [esi+0x59cc]
        mov  eax,0x66666667
        imul  edx
        sar  edx,0x2
        mov  eax,edx
        shr  eax,0x1f
        lea  edx,[edx+eax*1+0x33]
        mov  eax,ecx
        mov  ecx,DWORD PTR [ecx+0x308]
        call FUN_0043e5a0
    loc_0042FA1D:
        mov  ecx,DWORD PTR [esi+0x2cc]
        push  ecx
        mov  edx,edi
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042FA35
        mov  DWORD PTR [esi+0x2cc],ebx
    loc_0042FA35:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042FA57
        mov  ecx,0x4e
    loc_0042FA41:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_004301A8
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042FA41
    loc_0042FA57:
        xor  eax,eax
    loc_0042FA59:
        push  eax
        mov  edx,edi
        call FUN_004491c0
        mov  ecx,eax
        cmp  ecx,ebx
        je loc_0042FA86
        movsx eax,WORD PTR [esi+0x59cc]
        cdq
        mov  ebp,0xa
        idiv  ebp
        mov  eax,ecx
        mov  ecx,DWORD PTR [ecx+0x308]
        add  edx,0x33
        call FUN_0043e5a0
    loc_0042FA86:
        mov  ecx,DWORD PTR [esi+0x2cc]
        push  ecx
        mov  edx,edi
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042FA9E
        mov  DWORD PTR [esi+0x2cc],ebx
    loc_0042FA9E:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042FAC6
        mov  ecx,0x45
        lea  ebx,[ebx+0x0]
    loc_0042FAB0:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_004301B1
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042FAB0
    loc_0042FAC6:
        xor  eax,eax
    loc_0042FAC8:
        push  eax
        mov  edx,edi
        call FUN_004491c0
        mov  ecx,eax
        cmp  ecx,ebx
        je loc_0042FAFD
        movsx edx,WORD PTR [esi+0x59ce]
        mov  eax,0x66666667
        imul  edx
        sar  edx,0x2
        mov  eax,edx
        shr  eax,0x1f
        lea  edx,[edx+eax*1+0x33]
        mov  eax,ecx
        mov  ecx,DWORD PTR [ecx+0x308]
        call FUN_0043e5a0
    loc_0042FAFD:
        mov  ecx,DWORD PTR [esi+0x2cc]
        push  ecx
        mov  edx,edi
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042FB15
        mov  DWORD PTR [esi+0x2cc],ebx
    loc_0042FB15:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042FB37
        mov  ecx,0x46
    loc_0042FB21:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_004301BA
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042FB21
    loc_0042FB37:
        xor  eax,eax
    loc_0042FB39:
        push  eax
        mov  edx,edi
        call FUN_004491c0
        mov  ecx,eax
        cmp  ecx,ebx
        je loc_0042FB66
        movsx eax,WORD PTR [esi+0x59ce]
        cdq
        mov  ebp,0xa
        idiv  ebp
        mov  eax,ecx
        mov  ecx,DWORD PTR [ecx+0x308]
        add  edx,0x33
        call FUN_0043e5a0
    loc_0042FB66:
        mov  ecx,DWORD PTR [esi+0x2cc]
        push  ecx
        mov  edx,edi
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042FB7E
        mov  DWORD PTR [esi+0x2cc],ebx
    loc_0042FB7E:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042FBA6
        mov  ecx,0x4f
        lea  ebx,[ebx+0x0]
    loc_0042FB90:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_004301C3
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042FB90
    loc_0042FBA6:
        xor  eax,eax
    loc_0042FBA8:
        push  eax
        mov  edx,edi
        call FUN_004491c0
        mov  ecx,eax
        cmp  ecx,ebx
        je loc_0042FBDD
        movsx edx,WORD PTR [esi+0x59ce]
        mov  eax,0x66666667
        imul  edx
        sar  edx,0x2
        mov  eax,edx
        shr  eax,0x1f
        lea  edx,[edx+eax*1+0x33]
        mov  eax,ecx
        mov  ecx,DWORD PTR [ecx+0x308]
        call FUN_0043e5a0
    loc_0042FBDD:
        mov  ecx,DWORD PTR [esi+0x2cc]
        push  ecx
        mov  edx,edi
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042FBF5
        mov  DWORD PTR [esi+0x2cc],ebx
    loc_0042FBF5:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042FC17
        mov  ecx,0x50
    loc_0042FC01:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_004301CC
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042FC01
    loc_0042FC17:
        xor  eax,eax
    loc_0042FC19:
        push  eax
        mov  edx,edi
        call FUN_004491c0
        mov  ecx,eax
        cmp  ecx,ebx
        je loc_0042FC46
        movsx eax,WORD PTR [esi+0x59ce]
        cdq
        mov  ebp,0xa
        idiv  ebp
        mov  eax,ecx
        mov  ecx,DWORD PTR [ecx+0x308]
        add  edx,0x33
        call FUN_0043e5a0
    loc_0042FC46:
        mov  ecx,DWORD PTR [esi+0x2cc]
        push  ecx
        mov  edx,edi
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042FC5E
        mov  DWORD PTR [esi+0x2cc],ebx
    loc_0042FC5E:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042FC86
        mov  ecx,0x47
        lea  ebx,[ebx+0x0]
    loc_0042FC70:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_004301D5
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042FC70
    loc_0042FC86:
        xor  eax,eax
    loc_0042FC88:
        push  eax
        mov  edx,edi
        call FUN_004491c0
        mov  ecx,eax
        cmp  ecx,ebx
        je loc_0042FCBD
        movsx edx,WORD PTR [esi+0x59d0]
        mov  eax,0x66666667
        imul  edx
        sar  edx,0x2
        mov  eax,edx
        shr  eax,0x1f
        lea  edx,[edx+eax*1+0x33]
        mov  eax,ecx
        mov  ecx,DWORD PTR [ecx+0x308]
        call FUN_0043e5a0
    loc_0042FCBD:
        mov  ecx,DWORD PTR [esi+0x2cc]
        push  ecx
        mov  edx,edi
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042FCD5
        mov  DWORD PTR [esi+0x2cc],ebx
    loc_0042FCD5:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042FCF7
        mov  ecx,0x48
    loc_0042FCE1:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_004301DE
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042FCE1
    loc_0042FCF7:
        xor  eax,eax
    loc_0042FCF9:
        push  eax
        mov  edx,edi
        call FUN_004491c0
        mov  ecx,eax
        cmp  ecx,ebx
        je loc_0042FD26
        movsx eax,WORD PTR [esi+0x59d0]
        cdq
        mov  ebp,0xa
        idiv  ebp
        mov  eax,ecx
        mov  ecx,DWORD PTR [ecx+0x308]
        add  edx,0x33
        call FUN_0043e5a0
    loc_0042FD26:
        mov  ecx,DWORD PTR [esi+0x2cc]
        push  ecx
        mov  edx,edi
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042FD3E
        mov  DWORD PTR [esi+0x2cc],ebx
    loc_0042FD3E:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042FD66
        mov  ecx,0x51
        lea  ebx,[ebx+0x0]
    loc_0042FD50:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_004301E7
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042FD50
    loc_0042FD66:
        xor  eax,eax
    loc_0042FD68:
        push  eax
        mov  edx,edi
        call FUN_004491c0
        mov  ecx,eax
        cmp  ecx,ebx
        je loc_0042FD9D
        movsx edx,WORD PTR [esi+0x59d0]
        mov  eax,0x66666667
        imul  edx
        sar  edx,0x2
        mov  eax,edx
        shr  eax,0x1f
        lea  edx,[edx+eax*1+0x33]
        mov  eax,ecx
        mov  ecx,DWORD PTR [ecx+0x308]
        call FUN_0043e5a0
    loc_0042FD9D:
        mov  ecx,DWORD PTR [esi+0x2cc]
        push  ecx
        mov  edx,edi
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042FDB5
        mov  DWORD PTR [esi+0x2cc],ebx
    loc_0042FDB5:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042FDD7
        mov  ecx,0x52
    loc_0042FDC1:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_004301F0
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042FDC1
    loc_0042FDD7:
        xor  eax,eax
    loc_0042FDD9:
        push  eax
        mov  edx,edi
        call FUN_004491c0
        mov  ecx,eax
        cmp  ecx,ebx
        je loc_0042FE06
        movsx eax,WORD PTR [esi+0x59d0]
        cdq
        mov  ebp,0xa
        idiv  ebp
        mov  eax,ecx
        mov  ecx,DWORD PTR [ecx+0x308]
        add  edx,0x33
        call FUN_0043e5a0
    loc_0042FE06:
        mov  ecx,DWORD PTR [esi+0x2cc]
        push  ecx
        mov  edx,edi
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042FE1E
        mov  DWORD PTR [esi+0x2cc],ebx
    loc_0042FE1E:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042FE46
        mov  ecx,0x49
        lea  ebx,[ebx+0x0]
    loc_0042FE30:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_004301F9
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042FE30
    loc_0042FE46:
        xor  eax,eax
    loc_0042FE48:
        push  eax
        mov  edx,edi
        call FUN_004491c0
        mov  ecx,eax
        cmp  ecx,ebx
        je loc_0042FE7D
        movsx edx,WORD PTR [esi+0x59d2]
        mov  eax,0x66666667
        imul  edx
        sar  edx,0x2
        mov  eax,edx
        shr  eax,0x1f
        lea  edx,[edx+eax*1+0x33]
        mov  eax,ecx
        mov  ecx,DWORD PTR [ecx+0x308]
        call FUN_0043e5a0
    loc_0042FE7D:
        mov  ecx,DWORD PTR [esi+0x2cc]
        push  ecx
        mov  edx,edi
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042FE95
        mov  DWORD PTR [esi+0x2cc],ebx
    loc_0042FE95:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042FEB7
        mov  ecx,0x4a
    loc_0042FEA1:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_00430202
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042FEA1
    loc_0042FEB7:
        xor  eax,eax
    loc_0042FEB9:
        push  eax
        mov  edx,edi
        call FUN_004491c0
        mov  ecx,eax
        cmp  ecx,ebx
        je loc_0042FEE6
        movsx eax,WORD PTR [esi+0x59d2]
        cdq
        mov  ebp,0xa
        idiv  ebp
        mov  eax,ecx
        mov  ecx,DWORD PTR [ecx+0x308]
        add  edx,0x33
        call FUN_0043e5a0
    loc_0042FEE6:
        mov  ecx,DWORD PTR [esi+0x2cc]
        push  ecx
        mov  edx,edi
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042FEFE
        mov  DWORD PTR [esi+0x2cc],ebx
    loc_0042FEFE:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042FF26
        mov  ecx,0x53
        lea  ebx,[ebx+0x0]
    loc_0042FF10:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_0043020B
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042FF10
    loc_0042FF26:
        xor  eax,eax
    loc_0042FF28:
        push  eax
        mov  edx,edi
        call FUN_004491c0
        mov  ecx,eax
        cmp  ecx,ebx
        je loc_0042FF5D
        movsx edx,WORD PTR [esi+0x59d2]
        mov  eax,0x66666667
        imul  edx
        sar  edx,0x2
        mov  eax,edx
        shr  eax,0x1f
        lea  edx,[edx+eax*1+0x33]
        mov  eax,ecx
        mov  ecx,DWORD PTR [ecx+0x308]
        call FUN_0043e5a0
    loc_0042FF5D:
        mov  ecx,DWORD PTR [esi+0x2cc]
        push  ecx
        mov  edx,edi
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042FF75
        mov  DWORD PTR [esi+0x2cc],ebx
    loc_0042FF75:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042FF97
        mov  ecx,0x54
    loc_0042FF81:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_00430214
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042FF81
    loc_0042FF97:
        xor  eax,eax
    loc_0042FF99:
        push  eax
        mov  edx,edi
        call FUN_004491c0
        mov  ecx,eax
        cmp  ecx,ebx
        je loc_0042FFC6
        movsx eax,WORD PTR [esi+0x59d2]
        cdq
        mov  ebp,0xa
        idiv  ebp
        mov  eax,ecx
        mov  ecx,DWORD PTR [ecx+0x308]
        add  edx,0x33
        call FUN_0043e5a0
    loc_0042FFC6:
        mov  ecx,DWORD PTR [esi+0x2cc]
        push  ecx
        mov  edx,edi
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042FFDE
        mov  DWORD PTR [esi+0x2cc],ebx
    loc_0042FFDE:
        add  eax,0x10
        cmp  eax,ebx
        je loc_00430006
        mov  ecx,0x4b
        lea  ebx,[ebx+0x0]
    loc_0042FFF0:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_0043021D
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042FFF0
    loc_00430006:
        xor  eax,eax
    loc_00430008:
        push  eax
        mov  edx,edi
        call FUN_004491c0
        mov  ecx,eax
        cmp  ecx,ebx
        je loc_0043003D
        movsx edx,WORD PTR [esi+0x59d4]
        mov  eax,0x66666667
        imul  edx
        sar  edx,0x2
        mov  eax,edx
        shr  eax,0x1f
        lea  edx,[edx+eax*1+0x33]
        mov  eax,ecx
        mov  ecx,DWORD PTR [ecx+0x308]
        call FUN_0043e5a0
    loc_0043003D:
        mov  ecx,DWORD PTR [esi+0x2cc]
        push  ecx
        mov  edx,edi
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_00430055
        mov  DWORD PTR [esi+0x2cc],ebx
    loc_00430055:
        add  eax,0x10
        cmp  eax,ebx
        je loc_00430077
        mov  ecx,0x4c
    loc_00430061:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_00430226
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_00430061
    loc_00430077:
        xor  eax,eax
    loc_00430079:
        push  eax
        mov  edx,edi
        call FUN_004491c0
        mov  ecx,eax
        cmp  ecx,ebx
        je loc_004300A6
        movsx eax,WORD PTR [esi+0x59d4]
        cdq
        mov  ebp,0xa
        idiv  ebp
        mov  eax,ecx
        mov  ecx,DWORD PTR [ecx+0x308]
        add  edx,0x33
        call FUN_0043e5a0
    loc_004300A6:
        mov  ecx,DWORD PTR [esi+0x2cc]
        push  ecx
        mov  edx,edi
        call FUN_004491c0
        cmp  eax,ebx
        pop  ebp
        jne loc_004300BF
        mov  DWORD PTR [esi+0x2cc],ebx
    loc_004300BF:
        add  eax,0x10
        cmp  eax,ebx
        je loc_004300E6
        mov  ecx,0x55
        jmp loc_004300D0
        nop
    loc_004300D0:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_0043022F
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_004300D0
    loc_004300E6:
        xor  eax,eax
    loc_004300E8:
        push  eax
        mov  edx,edi
        call FUN_004491c0
        mov  ecx,eax
        cmp  ecx,ebx
        je loc_0043011D
        movsx edx,WORD PTR [esi+0x59d4]
        mov  eax,0x66666667
        imul  edx
        sar  edx,0x2
        mov  eax,edx
        shr  eax,0x1f
        lea  edx,[edx+eax*1+0x33]
        mov  eax,ecx
        mov  ecx,DWORD PTR [ecx+0x308]
        call FUN_0043e5a0
    loc_0043011D:
        mov  ecx,DWORD PTR [esi+0x2cc]
        push  ecx
        mov  edx,edi
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_00430135
        mov  DWORD PTR [esi+0x2cc],ebx
    loc_00430135:
        add  eax,0x10
        cmp  eax,ebx
        je loc_00430157
        mov  ecx,0x56
    loc_00430141:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_00430238
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_00430141
    loc_00430157:
        xor  eax,eax
    loc_00430159:
        push  eax
        mov  edx,edi
        call FUN_004491c0
        mov  ecx,eax
        cmp  ecx,ebx
        pop  edi
        je loc_00430241
        movsx eax,WORD PTR [esi+0x59d4]
        cdq
        mov  esi,0xa
        idiv  esi
        pop  esi
        mov  eax,ecx
        mov  ecx,DWORD PTR [ecx+0x308]
        pop  ebx
        add  edx,0x33
        jmp FUN_0043e5a0
    loc_0043018D:
        mov  eax,DWORD PTR [eax]
        mov  eax,DWORD PTR [eax]
        jmp loc_0042F8F9
    loc_00430196:
        mov  eax,DWORD PTR [eax]
        mov  eax,DWORD PTR [eax]
        jmp loc_0042F978
    loc_0043019F:
        mov  eax,DWORD PTR [eax]
        mov  eax,DWORD PTR [eax]
        jmp loc_0042F9E8
    loc_004301A8:
        mov  eax,DWORD PTR [eax]
        mov  eax,DWORD PTR [eax]
        jmp loc_0042FA59
    loc_004301B1:
        mov  eax,DWORD PTR [eax]
        mov  eax,DWORD PTR [eax]
        jmp loc_0042FAC8
    loc_004301BA:
        mov  eax,DWORD PTR [eax]
        mov  eax,DWORD PTR [eax]
        jmp loc_0042FB39
    loc_004301C3:
        mov  eax,DWORD PTR [eax]
        mov  eax,DWORD PTR [eax]
        jmp loc_0042FBA8
    loc_004301CC:
        mov  eax,DWORD PTR [eax]
        mov  eax,DWORD PTR [eax]
        jmp loc_0042FC19
    loc_004301D5:
        mov  eax,DWORD PTR [eax]
        mov  eax,DWORD PTR [eax]
        jmp loc_0042FC88
    loc_004301DE:
        mov  eax,DWORD PTR [eax]
        mov  eax,DWORD PTR [eax]
        jmp loc_0042FCF9
    loc_004301E7:
        mov  eax,DWORD PTR [eax]
        mov  eax,DWORD PTR [eax]
        jmp loc_0042FD68
    loc_004301F0:
        mov  eax,DWORD PTR [eax]
        mov  eax,DWORD PTR [eax]
        jmp loc_0042FDD9
    loc_004301F9:
        mov  eax,DWORD PTR [eax]
        mov  eax,DWORD PTR [eax]
        jmp loc_0042FE48
    loc_00430202:
        mov  eax,DWORD PTR [eax]
        mov  eax,DWORD PTR [eax]
        jmp loc_0042FEB9
    loc_0043020B:
        mov  eax,DWORD PTR [eax]
        mov  eax,DWORD PTR [eax]
        jmp loc_0042FF28
    loc_00430214:
        mov  eax,DWORD PTR [eax]
        mov  eax,DWORD PTR [eax]
        jmp loc_0042FF99
    loc_0043021D:
        mov  eax,DWORD PTR [eax]
        mov  eax,DWORD PTR [eax]
        jmp loc_00430008
    loc_00430226:
        mov  eax,DWORD PTR [eax]
        mov  eax,DWORD PTR [eax]
        jmp loc_00430079
    loc_0043022F:
        mov  eax,DWORD PTR [eax]
        mov  eax,DWORD PTR [eax]
        jmp loc_004300E8
    loc_00430238:
        mov  eax,DWORD PTR [eax]
        mov  eax,DWORD PTR [eax]
        jmp loc_00430159
    loc_00430241:
        pop  esi
        pop  ebx
        ret
    }
}
