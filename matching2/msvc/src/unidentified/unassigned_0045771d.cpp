// 0x0045771D..0x0045772B: run the exit path with the process-leaving flags.
//
// The three pushed constants are the exit code, the "quick" flag and the
// "process" flag the retail image hands to doexit.

extern "C" void __cdecl asm_doexit_00457629(int code, int quick, int process);

extern "C" void __cdecl unassigned_0045771d(void) {
    asm_doexit_00457629(0, 1, 1);
}
