// 0x00453259..0x0045326C: the default pure-virtual-call handler: run the
// installed handler if there is one, then report the error and abort.

extern "C" void __cdecl asm_amsg_exit_0045373d(int code);
extern "C" void* g_crt_terminate_handle;

extern "C" void __cdecl unassigned_00453259(void) {
    if (g_crt_terminate_handle != 0)
        ((void (__cdecl*)(void))g_crt_terminate_handle)();
    asm_amsg_exit_0045373d(25);
}
