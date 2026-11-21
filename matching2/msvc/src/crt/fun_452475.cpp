// 0x00452475..0x0045247D: allocate a four-byte CRT bookkeeping block.
extern "C" void __cdecl crt_unlock(unsigned int size);

extern "C" void __cdecl crt_helper_452475() {
    crt_unlock(4);
}
