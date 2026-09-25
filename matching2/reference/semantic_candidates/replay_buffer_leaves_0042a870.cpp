#include <stdint.h>

struct ReplayBufferState_0042a870 {
    uint8_t earlier_fields[0x5460];
    uint8_t* record_cursor;       // +0x5460, advances by six-byte records
    uint8_t byte_buffer[0xE10];  // +0x5464
    uint8_t* byte_cursor;         // +0x6274
};

// Retail 0x0042A870..0x0042A899 receives the state in ECX.
extern "C" int __fastcall GetCombinedReplayBytes_0042a870(
    const ReplayBufferState_0042a870* state) {
    const uint8_t* base = reinterpret_cast<const uint8_t*>(state);
    const int record_distance = static_cast<int>(state->record_cursor - base);
    const int whole_record_bytes = record_distance / 6 * 6;
    const int byte_buffer_bytes =
        static_cast<int>(state->byte_cursor - state->byte_buffer);
    return whole_record_bytes + byte_buffer_bytes;
}

// Retail 0x0042A900..0x0042A925 receives the state in EAX and byte in DL.
extern "C" bool __cdecl AppendReplayByte_0042a900(
    ReplayBufferState_0042a870* state, uint8_t value) {
    *state->byte_cursor = value;
    ++state->byte_cursor;
    return state->byte_cursor - state->byte_buffer >= 0x78;
}
