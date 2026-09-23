// 0x0045373D: report a CRT message and terminate through __exit.
extern "C" int data_0047720c;
extern "C" void __cdecl asm_FF_MSGBANNER_0045909f();
extern "C" void __cdecl asm_FUN_00458efd_00458efd(int errorCode);
typedef void (__cdecl *CrtExitFunction_0045373d)(int exitCode);
extern "C" CrtExitFunction_0045373d data_00473070;

extern "C" __declspec(noinline) __declspec(noreturn) void __cdecl
asm_amsg_exit_0045373d(int errorCode) {
    if (data_0047720c == 1) {
        asm_FF_MSGBANNER_0045909f();
    }

    asm_FUN_00458efd_00458efd(errorCode);
    data_00473070(0xff);
}
