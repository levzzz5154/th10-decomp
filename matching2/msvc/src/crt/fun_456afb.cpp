extern "C" void* __cdecl crt_getptd();

// 0x00456AFB..0x00456B03: Address the thread-local DOS error word.
extern "C" unsigned int* __cdecl crt_doserrno() {
    return reinterpret_cast<unsigned int*>(static_cast<unsigned char*>(crt_getptd()) + 12);
}
