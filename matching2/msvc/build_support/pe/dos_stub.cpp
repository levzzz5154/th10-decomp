// C++ source for the 16-bit DOS compatibility payload at PE offset 0x40.
//
// The compiler is in 32-bit mode, while this code is entered by DOS in its
// 16-bit code segment.  The MOV helpers below emit the final 16-bit encodings
// directly: a 32-bit compiler would otherwise add an operand-size prefix.  A
// naked body avoids a compiler prologue/epilogue and leaves the payload
// independent of C++ runtime code.

#pragma code_seg(".doscode")

#define TH10_DOS_MOV16_DX_IMM(value) \
    __asm _emit 0xba \
    __asm _emit ((value) & 0xff) __asm _emit (((value) >> 8) & 0xff)
#define TH10_DOS_MOV16_AX_IMM(value) \
    __asm _emit 0xb8 \
    __asm _emit ((value) & 0xff) __asm _emit (((value) >> 8) & 0xff)

extern "C" __declspec(naked) void __cdecl dos_stub_code() {
    __asm {
        push cs
        pop ds
        TH10_DOS_MOV16_DX_IMM(0x000e)
        mov ah, 9
        int 21h
        TH10_DOS_MOV16_AX_IMM(0x4c01)
        int 21h
    }
}

#pragma code_seg()

// The message starts immediately after the 14-byte instruction body.  Keep it
// in its own initialized section so the PE packer can concatenate the two
// zero-relocation sections without depending on linker ordering or padding.
#pragma data_seg(".dosmsg")
extern "C" unsigned char dos_stub_message[50] = {
    'T', 'h', 'i', 's', ' ', 'p', 'r', 'o', 'g', 'r', 'a', 'm', ' ', 'c', 'a', 'n', 'n', 'o',
    't', ' ', 'b', 'e', ' ', 'r', 'u', 'n', ' ', 'i', 'n', ' ', 'D', 'O', 'S', ' ', 'm', 'o',
    'd', 'e', '.', 0x0d, 0x0d, 0x0a, 0x24,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
#pragma data_seg()
