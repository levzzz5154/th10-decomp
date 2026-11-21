extern "C" void __cdecl crt_unlock(int index);

// 0x00457580: Release CRT lock 8.
extern "C" void __cdecl crt_unlockexit() {
    crt_unlock(8);
}
