// 0x0045FE75: the per-thread mode block, one field inside the per-thread data.

extern "C" char* __cdecl crt_getptd(void);

extern "C" char* __cdecl unassigned8(void) {
    return crt_getptd() + 0x5C;
}
