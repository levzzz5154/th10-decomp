// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_0040e760.cpp"

#pragma code_seg(".text$03anchor")
__declspec(noinline) void Inner_0040e760::Run() {
    unsigned char* bytes = this->bytes;
    for (int i = 0; i < 0x100; ++i) {
        bytes[i] = (unsigned char)i;
    }
    int sum = 0;
    sum += bytes[0x14];
    sum += bytes[0x15];
    bytes[0x20] = (unsigned char)sum;
}
#pragma code_seg()

#pragma code_seg(".text$05context")
int __stdcall RunContext_0040e760(Outer_0040e760** items, int count) {
    for (int i = 0; i < count; ++i) {
        (*items++)->Run();
    }
    return 0;
}
#pragma code_seg()
