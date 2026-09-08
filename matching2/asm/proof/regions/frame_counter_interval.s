# Retail 00427c70..00427c8c, from ghidra_full/functions/00427C70.asm.
# ECX = {previous, current}; divisor on stack; callee pops four bytes.
.globl _th10_00427c70
_th10_00427c70:
    mov eax, DWORD PTR [ecx + 4]
    cmp eax, DWORD PTR [ecx]
    je .Linterval_false
    cdq
    idiv DWORD PTR [esp + 4]
    test edx, edx
    jne .Linterval_false
    mov eax, 1
    ret 4
.Linterval_false:
    {load} xor eax, eax
    ret 4
.globl _th10_00427c70_end
_th10_00427c70_end:
