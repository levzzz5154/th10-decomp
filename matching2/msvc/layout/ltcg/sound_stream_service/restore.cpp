// Unselected native ABI anchor from src/core/zwave/platform_run_interface_0044d300.cpp.
// Only the shared type view and placement section differ.
#pragma code_seg(".text$03run")
__declspec(noinline) int PlatformD300Entry::Run(unsigned int* completed) {
    unsigned int state;
    if (this == 0)
        return (int)0x800401F0u;
    if (completed != 0)
        *completed = 0;

    int result = read_state(&state);
    if (result < 0)
        return result;
    if ((state & 2) != 0) {
        for (;;) {
            if (restore() == (int)0x88780096u)
                Sleep(10);
            if (restore() != 0)
                continue;
            if (completed != 0)
                *completed = 1;
            return 0;
        }
    }
    return 1;
}
#pragma code_seg()
