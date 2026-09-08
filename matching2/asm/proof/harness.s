.intel_syntax noprefix
.code32
.section .proof,"xr"
.globl _probe_entry
_probe_entry:
    # True when current differs from previous and divides exactly.
    mov esi, esp
    mov ecx, OFFSET FLAT:.Lcounter
    push 3
    call _th10_00427c70
    cmp esp, esi
    jne .Lfail
    cmp eax, 1
    jne .Lfail
    # False when the frame did not advance.
    mov DWORD PTR [.Lcounter], 9
    mov ecx, OFFSET FLAT:.Lcounter
    push 3
    call _th10_00427c70
    test eax, eax
    jne .Lfail
    # False when the new frame is not an interval boundary.
    mov DWORD PTR [.Lcounter + 4], 10
    mov ecx, OFFSET FLAT:.Lcounter
    push 3
    call _th10_00427c70
    test eax, eax
    jne .Lfail
    # Exercise the destructor's null path without calling the external target.
    mov ecx, OFFSET FLAT:.Lentity
    call _th10_00401ff0
    cmp esp, esi
    jne .Lfail
    cmp DWORD PTR [.Lentity + 0x358], 0
    jne .Lfail
    push 0
    call "_ExitProcess@4"
.Lfail:
    push 1
    call "_ExitProcess@4"
.data
.Lcounter:
    .long 6, 9
.Lentity:
    .zero 0x35c
