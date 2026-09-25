// 0x0043A700..0x0043A724: reverse the byte order of one 32-bit word.
// The retail function uses RET 4, so this wrapper retains the callee-cleanup ABI.
extern "C" unsigned int __stdcall ReverseWordBytes_0043a700(unsigned int value) {
    return ((value & 0x000000FFu) << 24) |
           ((value & 0x0000FF00u) << 8) |
           ((value & 0x00FF0000u) >> 8) |
           ((value & 0xFF000000u) >> 24);
}
