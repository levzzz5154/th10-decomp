extern "C" void* __cdecl crt_getptd();

// 0x0045FE7E..0x0045FE86: Address the thread-local initialization argument.
extern "C" void** __cdecl crt_pxcptinfoptrs() {
    return reinterpret_cast<void**>(static_cast<unsigned char*>(crt_getptd()) + 0x58);
}
