// 0x0045326D..0x0045327C: install the pure-virtual-call handler, return the old one.

extern "C" void* data_00477200;

extern "C" void* __cdecl unassigned_0045326d(void* handler) {
    void* previous = data_00477200;
    data_00477200 = handler;
    return previous;
}
