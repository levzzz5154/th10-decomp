// 0x00452475..0x0045247D: allocate a four-byte CRT bookkeeping block.
extern "C" void __cdecl asm_FUN_00453b3f_00453b3f(unsigned int size);

extern "C" void __cdecl asm_FUN_00452475_00452475() {
    asm_FUN_00453b3f_00453b3f(4);
}
