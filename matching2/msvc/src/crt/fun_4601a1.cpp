extern "C" int (__stdcall *imp_GetLocaleInfoA)(unsigned int, unsigned int, char*, int);
extern "C" long __cdecl crt_atol(const char*);

extern "C" long __cdecl crt_ansicp(unsigned int locale) {
    char buffer[7];
    buffer[6] = 0;
    if (imp_GetLocaleInfoA(locale, 0x1004, buffer, 6) == 0) return -1;
    return crt_atol(buffer);
}
