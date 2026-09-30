extern "C" void __cdecl asm_FF_MSGBANNER_0045909f();

// The actual handler at 0x00458EFD is cdecl and returns with a plain RET. This
// routine immediately enters the non-returning process-exit path afterward,
// so its argument word is abandoned. The local stdcall declaration below is
// an intentional call-site code-generation aid: it suppresses cleanup that
// retail omits on this terminal path. The decorated COFF reference is bound
// back to the real cdecl entry.
extern "C" void __attribute__((stdcall)) asm_FUN_00458efd_00458efd(int errorCode);
extern "C" __declspec(noreturn) void __cdecl asm_crtExitProcess_00457547(int exitCode);

enum : unsigned int { RuntimeErrorMessageModeAddress = 0x0047720cu };

// Retail reads errorCode from its original stack slot after the optional
// banner call, so keep the parameter access volatile at that point.
extern "C" __declspec(noinline) __declspec(noreturn)
void __cdecl fast_error_exit_00453762(volatile int errorCode) {
    if (*reinterpret_cast<const int*>(RuntimeErrorMessageModeAddress) == 1)
        asm_FF_MSGBANNER_0045909f();
    asm_FUN_00458efd_00458efd(errorCode);
    asm_crtExitProcess_00457547(0xff);
}
