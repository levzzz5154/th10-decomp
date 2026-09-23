// 0x00458E74..0x00458EA3: report_failure
// The helper receives mode 1 and flags 0; ExitProcess terminates with code 3.
extern "C" void __cdecl asm_FUN_0045f259_0045f259(int mode, int flags);
extern "C" void (__stdcall *data_0046614c)(unsigned int exit_code);

extern "C" __declspec(noreturn) void __cdecl asm_report_failure_00458e74() {
    asm_FUN_0045f259_0045f259(1, 0);
    data_0046614c(3);
    for (;;) {
    }
}
