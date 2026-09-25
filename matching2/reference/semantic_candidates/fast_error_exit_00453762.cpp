// 0x00453762: emit the runtime error and terminate the process.
// Ghidra identifies a one-int cdecl input and a non-returning exit path.
extern "C" int data_0047720c;
extern "C" void __cdecl asm_FF_MSGBANNER_0045909f();
extern "C" void __cdecl asm_FUN_00458efd_00458efd(int errorCode);
extern "C" __declspec(noreturn) void __cdecl
    asm_crtExitProcess_00457547(int exitCode);

extern "C" __declspec(noinline) __declspec(noreturn) void __cdecl
asm_fast_error_exit_00453762(int errorCode) {
    if (data_0047720c == 1) {
        asm_FF_MSGBANNER_0045909f();
    }

    asm_FUN_00458efd_00458efd(errorCode);
    asm_crtExitProcess_00457547(0xff);
}
