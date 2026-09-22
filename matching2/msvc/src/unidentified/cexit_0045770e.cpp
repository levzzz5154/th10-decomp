extern "C" void __cdecl asm_doexit_00457629(int code, int quick, int return_to_caller);

extern "C" void __cdecl asm_cexit_0045770e() {
    asm_doexit_00457629(0, 0, 1);
}
