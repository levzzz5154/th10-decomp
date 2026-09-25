#include <stdint.h>

struct SevenWordRecordPair_00404c60 {
    uint32_t first[7];
    uint32_t second[7];
};

// Retail 0x00404C60..0x00404C6F receives source in EAX and target in EDX.
extern "C" void __cdecl CopySevenWordRecord_00404c60(
    uint32_t* target, const uint32_t* source) {
    for (unsigned int i = 0; i < 7; ++i)
        target[i] = source[i];
}

// Retail 0x00404C70..0x00404C82 receives the pair in EAX and source in EDX.
extern "C" void __cdecl CopySecondSevenWordRecord_00404c70(
    SevenWordRecordPair_00404c60* pair, const uint32_t* source) {
    for (unsigned int i = 0; i < 7; ++i)
        pair->second[i] = source[i];
}
