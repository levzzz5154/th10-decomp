// The CRT exit helper gives the managed runtime a chance to terminate first,
// then falls back to the process-wide Win32 exit API.
using ModuleHandle = void*;
using GenericProcedure = int (__stdcall *)(void);
using GetModuleHandleAFunction = ModuleHandle (__stdcall *)(const char*);
using GetProcAddressFunction = GenericProcedure (__stdcall *)(ModuleHandle, const char*);
using ExitProcessFunction = void (__stdcall *)(unsigned int);
using CorExitProcessFunction = void (__stdcall *)(unsigned int);

// These are the three Win32 IAT slots used directly by the retail body.
extern "C" GetModuleHandleAFunction data_00466198;
extern "C" GetProcAddressFunction data_00466158;
extern "C" ExitProcessFunction data_0046614c;

// 0x00457547..0x00457575: ___crtExitProcess
extern "C" __declspec(noinline) __declspec(noreturn) void __cdecl
CrtExitProcess_00457547(int exitCode) {
    const ModuleHandle runtimeModule = data_00466198("mscoree.dll");
    if (runtimeModule != nullptr) {
        const GenericProcedure procedure =
            data_00466158(runtimeModule, "CorExitProcess");
        if (procedure != nullptr) {
            const auto corExitProcess =
                reinterpret_cast<CorExitProcessFunction>(procedure);
            corExitProcess(static_cast<unsigned int>(exitCode));
        }
    }

    data_0046614c(static_cast<unsigned int>(exitCode));
    __assume(0);
}
