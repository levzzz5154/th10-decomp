// The CRT exit helper gives the managed runtime a chance to terminate first,
// then falls back to the process-wide Win32 exit API.
typedef void* ModuleHandle;
typedef int (__stdcall *GenericProcedure)(void);
typedef ModuleHandle (__stdcall *GetModuleHandleAFunction)(const char*);
typedef GenericProcedure (__stdcall *GetProcAddressFunction)(ModuleHandle, const char*);
typedef void (__stdcall *ExitProcessFunction)(unsigned int);
typedef void (__stdcall *CorExitProcessFunction)(unsigned int);

// These are the three Win32 IAT slots used directly by the retail body.
extern "C" GetModuleHandleAFunction data_00466198;
extern "C" GetProcAddressFunction data_00466158;
extern "C" ExitProcessFunction data_0046614c;

// 0x00457547..0x00457575: ___crtExitProcess
extern "C" __declspec(noinline) __declspec(noreturn) void __cdecl
CrtExitProcess_00457547(int exitCode) {
    const ModuleHandle runtimeModule = data_00466198("mscoree.dll");
    if (runtimeModule != 0) {
        const GenericProcedure procedure =
            data_00466158(runtimeModule, "CorExitProcess");
        if (procedure != 0) {
            const CorExitProcessFunction corExitProcess =
                reinterpret_cast<CorExitProcessFunction>(procedure);
            corExitProcess(static_cast<unsigned int>(exitCode));
        }
    }

    data_0046614c(static_cast<unsigned int>(exitCode));
    __assume(0);
}
