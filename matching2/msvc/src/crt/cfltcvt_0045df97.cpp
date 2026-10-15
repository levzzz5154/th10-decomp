extern "C" int __cdecl asm_FUN_0045dd85_0045dd85(const void*, char*, int, int);
extern "C" int __cdecl asm_FUN_0045de91_0045de91(const void*, char*, int);
extern "C" int __cdecl asm_FUN_0045def8_0045def8(const void*, char*, int, int);

extern "C" int __cdecl asm_cfltcvt_0045df97(const void* value, char* buffer, int format, int precision, int caps) {
    if (format == 'e' || format == 'E') return asm_FUN_0045dd85_0045dd85(value, buffer, precision, caps);
    if (format == 'f') return asm_FUN_0045de91_0045de91(value, buffer, precision);
    return asm_FUN_0045def8_0045def8(value, buffer, precision, caps);
}
