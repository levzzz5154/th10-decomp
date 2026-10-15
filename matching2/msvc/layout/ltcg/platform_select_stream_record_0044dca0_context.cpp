// Compiler context only; never selected as recovered game code.
#include "../../src/core/zwave/platform_select_stream_record_0044dca0.cpp"

#pragma code_seg(".text$03context")
int __stdcall PlatformSelectStreamRecord0044DCA0CompilerContext(
        PlatformStreamState_0044DCA0** states,
        PlatformStreamRecord_0044DCA0** records, int count) {
    int result = 0;
    while (count-- > 0)
        result |= (*states++)->Select(*records++);
    return result;
}
#pragma code_seg()
