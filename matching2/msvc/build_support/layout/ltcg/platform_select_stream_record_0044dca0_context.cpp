// Compiler context only; never selected as recovered game code.
#include "../../../src/core/zwave/platform_select_stream_record.cpp"

#pragma code_seg(".text$03context")
int __stdcall PlatformSelectStreamRecord0044DCA0CompilerContext(
        PlatformStreamState** states,
        PlatformStreamRecord** records, int count) {
    int result = 0;
    while (count-- > 0)
        result |= (*states++)->Select(*records++);
    return result;
}
#pragma code_seg()
