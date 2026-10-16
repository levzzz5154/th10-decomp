// Compiler context only; never selected as recovered game code.
#include "../../../src/core/zwave/platform_query_interfaces.cpp"

#pragma code_seg(".text$03context")
int __stdcall PlatformQueryInterfaces0044D600CompilerContext(
        PlatformQueryInterfaces** states, int count) {
    int result = 0;
    while (count-- > 0)
        result |= (*states++)->Query();
    return result;
}
#pragma code_seg()
