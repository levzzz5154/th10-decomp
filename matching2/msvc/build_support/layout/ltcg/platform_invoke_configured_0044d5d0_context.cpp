// Compiler context only; never selected as recovered game code.
#include "../../../src/core/zwave/platform_invoke_configured_0044d5d0.cpp"

#pragma code_seg(".text$03context")
int __stdcall PlatformInvokeConfigured0044D5D0CompilerContext(
        PlatformInterfaceState_0044D5D0** states, int count) {
    int result = 0;
    while (count-- > 0)
        result |= (*states++)->InvokeConfigured();
    return result;
}
#pragma code_seg()
