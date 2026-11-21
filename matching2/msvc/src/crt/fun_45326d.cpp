// 0x0045326D..0x0045327C: install the pure-virtual-call handler, return the old one.

extern "C" void* g_crt_terminate_handle;

extern "C" void* __cdecl unassigned5(void* handler) {
    void* previous = g_crt_terminate_handle;
    g_crt_terminate_handle = handler;
    return previous;
}
