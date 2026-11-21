extern "C" void* __cdecl asm_getptd_00456357();

// 0x00456AFB..0x00456B03: Address the thread-local DOS error word.
extern "C" unsigned int* __cdecl asm_FUN_00456afb_00456afb() {
    return reinterpret_cast<unsigned int*>(static_cast<unsigned char*>(asm_getptd_00456357()) + 12);
}
