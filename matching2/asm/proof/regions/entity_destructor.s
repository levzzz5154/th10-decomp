# Retail 00401ff0..00402011, from ghidra_full/functions/00401FF0.asm.
# ECX = entity; the non-null path calls the not-yet-assembled retail free.
.globl _th10_00401ff0
_th10_00401ff0:
    push esi
    {load} mov esi, ecx
    mov eax, DWORD PTR [esi + 0x358]
    test eax, eax
    je .Lentity_clear
    push eax
    call _th10_00452422
    add esp, 4
.Lentity_clear:
    mov DWORD PTR [esi + 0x358], 0
    pop esi
    ret
.globl _th10_00401ff0_end
_th10_00401ff0_end:
