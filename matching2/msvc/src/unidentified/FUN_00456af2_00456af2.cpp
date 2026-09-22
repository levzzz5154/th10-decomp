extern "C" void* __cdecl asm_getptd_00456357();

// 0x00456AF2..0x00456AFA: Address the thread-local errno word.
extern "C" int* __cdecl asm_FUN_00456af2_00456af2() {
    return reinterpret_cast<int*>(static_cast<unsigned char*>(asm_getptd_00456357()) + 8);
}
