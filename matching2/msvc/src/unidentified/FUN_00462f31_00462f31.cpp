extern "C" void* __cdecl asm_getptd_00456357();

// 0x00462F31..0x00462F4B: Decrement the thread-local purecall depth.
extern "C" void __cdecl asm_FUN_00462f31_00462f31() {
    unsigned char* data = static_cast<unsigned char*>(asm_getptd_00456357());
    if (*reinterpret_cast<int*>(data + 0x84) > 0) {
        int* counter = reinterpret_cast<int*>(
            static_cast<unsigned char*>(asm_getptd_00456357()) + 0x84);
        --*counter;
    }
}
