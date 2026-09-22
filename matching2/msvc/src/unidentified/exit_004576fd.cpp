extern "C" void __cdecl asm_doexit_00457629(int code, int quick, int return_to_caller);

extern "C" void __cdecl asm_exit_004576fd(int code) {
    asm_doexit_00457629(code, 1, 0);
}
