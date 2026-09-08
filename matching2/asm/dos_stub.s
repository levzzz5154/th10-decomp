/*
 * The DOS compatibility stub from the supported PE, in its original 16-bit
 * code mode.  This source is assembled to a flat 0x40-byte payload by the
 * PE packer.  The DOS header and Rich data surrounding it remain declarative
 * metadata; they are not instruction sources.
 */

.code16
.section .text
.balign 1
.globl dos_stub_code
dos_stub_code:
        pushw   %cs
        popw    %ds
        movw    $dos_message, %dx
        movb    $9, %ah
        int     $0x21
        movw    $0x4c01, %ax
        int     $0x21
dos_message:
        .ascii  "This program cannot be run in DOS mode."
        .byte   0x0d, 0x0d, 0x0a, 0x24
        .fill   0x40 - (. - dos_stub_code), 1, 0
