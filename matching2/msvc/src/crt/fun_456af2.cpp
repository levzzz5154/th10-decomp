extern "C" void* __cdecl crt_getptd();

// 0x00456AF2..0x00456AFA: Address the thread-local errno word.
extern "C" int* __cdecl crt_errno() {
    return reinterpret_cast<int*>(static_cast<unsigned char*>(crt_getptd()) + 8);
}
