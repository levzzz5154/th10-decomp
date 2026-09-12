// Compiler context only; never selected as recovered game code.
#include "../../src/game/platform_aggregate_interfaces_0044d550.cpp"

#pragma code_seg(".text$03context")
int __stdcall PlatformAggregateInterfaces0044D550CompilerContext(
        PlatformInterfaceState_0044D550** states, int count) {
    int result = 0;
    while (count-- > 0)
        result |= (*states++)->Aggregate();
    return result;
}
#pragma code_seg()
