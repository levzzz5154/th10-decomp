extern "C" int __cdecl crt_helper_45dd85(const void*, char*, int, int);
extern "C" int __cdecl crt_helper_45de91(const void*, char*, int);
extern "C" int __cdecl crt_helper_45def8(const void*, char*, int, int);

extern "C" int __cdecl crt_cfltcvt(const void* value, char* buffer, int format, int precision, int caps) {
    if (format == 'e' || format == 'E') return crt_helper_45dd85(value, buffer, precision, caps);
    if (format == 'f') return crt_helper_45de91(value, buffer, precision);
    return crt_helper_45def8(value, buffer, precision, caps);
}
