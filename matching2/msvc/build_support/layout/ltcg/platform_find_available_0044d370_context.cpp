// Compiler context only; never selected as recovered game code.
#include "../../../src/core/zwave/platform_find_available.cpp"

#pragma code_seg(".text$03context")
PlatformD370Entry* __stdcall PlatformFindAvailable0044D370CompilerContext(
        PlatformInterfaceState** states, int count) {
    PlatformD370Entry* result = 0;
    while (count-- > 0)
        result = (*states++)->FindAvailable();
    return result;
}
#pragma code_seg()
