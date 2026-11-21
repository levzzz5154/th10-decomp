extern "C" void __cdecl crt_libcmt_fflush_flsall(int value);

// Flush all CRT streams.
extern "C" void __cdecl crt_flushall() {
    crt_libcmt_fflush_flsall(1);
}
