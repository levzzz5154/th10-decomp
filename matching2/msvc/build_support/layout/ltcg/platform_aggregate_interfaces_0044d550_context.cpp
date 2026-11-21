// Compiler context only; never selected as recovered game code.
#include "../../../src/core/zwave/platform_aggregate_interfaces.cpp"

#pragma code_seg(".text$03context")
int __stdcall PlatformAggregateInterfaces0044D550CompilerContext(
        SoundBuffer** states, int count) {
    int result = 0;
    while (count-- > 0)
        result |= (*states++)->StopAndRewind();
    return result;
}
#pragma code_seg()
