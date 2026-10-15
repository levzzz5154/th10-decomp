extern "C" int __cdecl asm_FUN_00454ed7_00454ed7(unsigned int*, const unsigned char*, void*);

extern "C" void __cdecl asm_FUN_004524fd_004524fd(const unsigned char* format, void* arguments) {
    unsigned int state[8];
    state[2] = 0;
    state[0] = 0;
    state[1] = 0x7fffffff;
    state[3] = 0x42;
    asm_FUN_00454ed7_00454ed7(state, format, arguments);
}
