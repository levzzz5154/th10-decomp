// Resolve a path using the executable directory unless a colon occurs.
// Native LTCG preserves source EAX, destination ECX, and plain RET.
#include <string.h>
#include "th10/platform/windows_types.hpp"
#pragma intrinsic(strcat, strcpy)
#pragma function(strrchr)
extern "C" char* __cdecl FirstByteSearch_00452730(const char* text, int character);
extern "C" __declspec(dllimport) DWORD __stdcall GetModuleFileNameA(HANDLE module, char* output,
                                                                    DWORD capacity);
#pragma code_seg(".text$03resolve")
extern "C" __declspec(noinline) void __fastcall ResolvePath435610(char* output, const char* path) {
    if (FirstByteSearch_00452730(path, ':')) {
        strcpy(output, path);
        return;
    }
    GetModuleFileNameA(0, output, 260);
    char* separator = strrchr(output, '\\');
    // Retail clears output but still writes through address 1 if no separator
    // was found. Keep the integer-address operation and unconditional store.
    if (!separator)
        *output = 0;
    *reinterpret_cast<char*>(reinterpret_cast<unsigned int>(separator) + 1) = 0;
    strcat(output, path);
}
#pragma code_seg()
