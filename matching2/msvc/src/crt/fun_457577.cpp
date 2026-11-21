extern "C" void __cdecl crt_lock(int value);

// Acquire CRT lock 8.
extern "C" void __cdecl crt_lockexit() {
    crt_lock(8);
}
