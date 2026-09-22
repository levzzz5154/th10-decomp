extern "C" unsigned int __cdecl asm_unassigned_00461004(unsigned int status) {
    unsigned char flags = static_cast<unsigned char>(status);
    unsigned int result = 0;
    if (flags & 1) result = 0x10;
    if (flags & 4) result |= 8;
    if (flags & 8) result |= 4;
    if (flags & 0x10) result |= 2;
    if (flags & 0x20) result |= 1;
    if (flags & 2) result |= 0x80000;
    return result;
}
