typedef int (__cdecl *NewHandler)(unsigned int);
extern "C" NewHandler g_crt_ptd_raw;
extern "C" void __cdecl crt_lock(int lock);
extern "C" void __cdecl crt_unlock(int lock);

extern "C" NewHandler __cdecl crt_unassigned_45570d(NewHandler handler) {
    crt_lock(4);
    NewHandler previous = g_crt_ptd_raw;
    g_crt_ptd_raw = handler;
    crt_unlock(4);
    return previous;
}
