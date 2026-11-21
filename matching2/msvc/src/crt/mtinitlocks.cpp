extern "C" int g_crt_lock_flags[];
extern "C" void* g_crt_lock_table[];
extern "C" char g_crt_lock_initialized;
extern "C" int __cdecl crt_crtInitCritSecAndSpinCount(void*, unsigned int);

extern "C" int __cdecl crt_mtinitlocks() {
    int i = 0;
    char* next = &g_crt_lock_initialized;
    do {
        if (g_crt_lock_flags[i * 2] == 1) {
            g_crt_lock_table[i * 2] = next;
            next += 24;
            if (!crt_crtInitCritSecAndSpinCount(g_crt_lock_table[i * 2], 4000)) {
                g_crt_lock_table[i * 2] = 0;
                return 0;
            }
        }
        ++i;
    } while (i < 36);
    return 1;
}
