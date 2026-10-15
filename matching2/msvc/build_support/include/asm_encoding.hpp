#pragma once
// MSVC 7.1 chooses shorter or alternate encodings for these architectural forms.
// These helpers encode explicit operands; there is no arbitrary instruction-byte
// fallback. The final linker verifies every operand and the complete image.
#define TH10_R8_AL 0
#define TH10_R8_CL 1
#define TH10_R8_DL 2
#define TH10_R8_BL 3
#define TH10_R8_AH 4
#define TH10_R8_CH 5
#define TH10_R8_DH 6
#define TH10_R8_BH 7
#define TH10_R32_EAX 0
#define TH10_R32_ECX 1
#define TH10_R32_EDX 2
#define TH10_R32_EBX 3
#define TH10_R32_ESP 4
#define TH10_R32_EBP 5
#define TH10_R32_ESI 6
#define TH10_R32_EDI 7
#define TH10_OPERAND16() __asm _emit 0x66
#define TH10_CMP_R8_STORE(dst, src) \
    __asm _emit 0x38 __asm _emit (0xc0 + (src) * 8 + (dst))
#define TH10_NOP_LEA_ECX_DISP8() \
    __asm _emit 0x8d __asm _emit 0x49 __asm _emit 0
#define TH10_NOP_LEA_ESP_DISP8() \
    __asm _emit 0x8d __asm _emit 0x64 __asm _emit 0x24 __asm _emit 0
#define TH10_ADD_M16_IMM16(base, imm) \
    __asm _emit 0x66 __asm _emit 0x81 __asm _emit (base) \
    __asm _emit ((imm) & 0xff) __asm _emit (((imm) >> 8) & 0xff)
#define TH10_CMP_EBP_DISP8_IMM16(disp, imm) \
    __asm _emit 0x66 __asm _emit 0x81 __asm _emit 0x7d \
    __asm _emit ((disp) & 0xff) __asm _emit ((imm) & 0xff) \
    __asm _emit (((imm) >> 8) & 0xff)
#define TH10_FDIV_ST_ST0() __asm _emit 0xd8 __asm _emit 0xf0
#define TH10_FDIVR_ST_ST0() __asm _emit 0xd8 __asm _emit 0xf8
#define TH10_REL8(opcode, source, target) \
    __asm _emit (opcode) __asm _emit (((target) - (source) - 2) & 0xff)
