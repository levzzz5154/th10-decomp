struct CrtThreadErrors { unsigned char prefix[8]; int error; unsigned int dos_error; };
struct CrtErrorMap { unsigned int dos_error; int error; };
extern "C" CrtThreadErrors* __cdecl crt_getptd();
extern "C" CrtErrorMap g_crt_doserr_table[45];

// 0x00456B04..0x00456B76: Translate a DOS error to thread-local errno.
extern "C" void __cdecl crt_dosmaperr(unsigned int dos_error) {
    crt_getptd()->dos_error = dos_error;
    for (unsigned int i = 0; i < 45; ++i) {
        if (dos_error == g_crt_doserr_table[i].dos_error) {
            crt_getptd()->error = g_crt_doserr_table[i].error;
            return;
        }
    }
    if (dos_error >= 0x13 && dos_error <= 0x24) {
        crt_getptd()->error = 0x0d;
        return;
    }
    if (dos_error >= 0xbc && dos_error <= 0xca) {
        crt_getptd()->error = 8;
        return;
    }
    crt_getptd()->error = 0x16;
}
