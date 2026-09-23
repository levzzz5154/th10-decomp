// 0x0045E8B4..0x0045E8E0: map CRT floating-point status flags to an error code.
extern "C" int __cdecl asm_errcode_0045e8b4(unsigned char status_flags) {
    if ((status_flags & 0x20u) != 0u)
        return 5;

    if ((status_flags & 0x08u) != 0u)
        return 1;

    if ((status_flags & 0x04u) != 0u)
        return 2;

    if ((status_flags & 0x01u) != 0u)
        return 3;

    return static_cast<int>(status_flags & 0x02u) << 1;
}
