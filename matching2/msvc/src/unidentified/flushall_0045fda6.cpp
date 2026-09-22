extern "C" void __cdecl asm_flsall_0045fc81(int value);

// Flush all CRT streams.
extern "C" void __cdecl asm_flushall_0045fda6() {
    asm_flsall_0045fc81(1);
}
