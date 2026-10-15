// 0x0041C480..0x0041C4DA (91 bytes): per-frame advance of the score records.
//
// The score display installs this very address as its primary scheduler task
// (0x0041C120 does), so the callback runs once per frame: it advances the linked
// record list at +0x18 through 0x0041C330 and returns that call's result.  The
// frame state published at data_00477810 says when the display must not advance
// - bit 0, bit 2 and bit 0x400 of its +0x58 flag word each report success
// without touching the records.  When the same word carries bit 1 (the frozen
// step), the time scale at data_00476f78 is zeroed around the call, so the
// records advance by their own per-record step only, and the global scale is
// restored afterwards.
//
// The flag word is read as three one-bit fields of a 32-bit word: retail's first
// test is the `(flags >> 2 | flags) & 1` shape MSVC emits for `paused | idle`,
// never the `test al,5` it emits for the equivalent masks.  Reading the fields
// through the global instead of caching the word in a local is what keeps the
// state pointer live in EDX, the word in EAX and both later tests on the EDX
// copy, exactly as retail's bytes show.
//
// Retail reaches the body with the records object in ECX and hands it to
// 0x0041C330 in EDI; EDI is not the parameter register of any declaration, so
// the body is compiled in the native-LTCG cluster
// layout/ltcg/score_records_advance_frame_0041c480.json together with that
// callee (src/game/laser/score_records_tick_0041c330.cpp).
#include <stddef.h>

// The frame state at data_00477810; only the flag word this region reads is
// described.
struct FrameFlagBits_0041c480 {
    unsigned int paused:1;              // bit 0
    unsigned int frozen:1;              // bit 1
    unsigned int idle:1;                // bit 2
    unsigned int reserved_03:7;
    unsigned int deferred:1;            // bit 10 (0x400)
    unsigned int reserved_0B:21;
};

struct FrameState_0041c480 {
    unsigned char pad_00[0x58];
    FrameFlagBits_0041c480 flags_58;    // +0x58
};

#include "th10/game/score_record_list.hpp"

extern "C" FrameState_0041c480* data_00477810;
extern "C" float data_00476f78;

// 0x0041C330 (src/game/laser/score_records_tick_0041c330.cpp).  Its records object
// arrives in EDI: this region, its only caller, sets it there.
extern "C" int __cdecl ScoreRecords_Tick_0041c330(ScoreRecords_0041c480* records);

#pragma code_seg(".text$03advance")
int ScoreRecords_0041c480::AdvanceFrame() {
    if (data_00477810->flags_58.paused | data_00477810->flags_58.idle)
        return 1;
    if (data_00477810->flags_58.deferred)
        return 1;
    if (data_00477810->flags_58.frozen) {
        float saved = data_00476f78;
        data_00476f78 = 0.0f;
        int result = ScoreRecords_Tick_0041c330(this);
        data_00476f78 = saved;
        return result;
    }
    return ScoreRecords_Tick_0041c330(this);
}
#pragma code_seg()
