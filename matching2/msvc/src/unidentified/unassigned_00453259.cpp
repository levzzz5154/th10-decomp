// 0x00453259..0x0045326C: the default pure-virtual-call handler: run the
// installed handler if there is one, then report the error and abort.

extern "C" void __cdecl asm_amsg_exit_0045373d(int code);
extern "C" void* data_00477200;

extern "C" void __cdecl unassigned_00453259(void) {
    if (data_00477200 != 0)
        ((void (__cdecl*)(void))data_00477200)();
    asm_amsg_exit_0045373d(25);
}
