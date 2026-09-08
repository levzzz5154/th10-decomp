# This .text contribution follows layout.obj at 0x00452420.
# A section-backed symbol makes the cross-object REL32 relocation unambiguous.
# INT3 guards the unrecovered target; this is not an implementation of free.
# Runtime tests must never execute it.
.text
.fill 2, 1, 0xcc
.globl _th10_00452422
_th10_00452422:
    int3
