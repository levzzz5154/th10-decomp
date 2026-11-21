extern "C" void* __cdecl asm_getptd_00456357();

// 0x0045FE7E..0x0045FE86: Address the thread-local initialization argument.
extern "C" void** __cdecl asm_FUN_0045fe7e_0045fe7e() {
    return reinterpret_cast<void**>(static_cast<unsigned char*>(asm_getptd_00456357()) + 0x58);
}
