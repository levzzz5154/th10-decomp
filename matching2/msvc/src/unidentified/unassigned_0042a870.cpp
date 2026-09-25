// 0x0042A870..0x0042A899: total replay bytes buffered so far. The record
// cursor counts whole six-byte records from the start of the state, and the
// byte cursor counts pending bytes in the trailing byte buffer.
struct ReplayRecord_0042a870 {
    unsigned char bytes[6];
};

struct ReplayBufferState_0042a870 {
    unsigned char earlier_fields[0x5460];
    ReplayRecord_0042a870* record_cursor;  // +0x5460
    unsigned char byte_buffer[0xE10];      // +0x5464
    unsigned char* byte_cursor;            // +0x6274

    __declspec(noinline) int GetBufferedBytes() const;
};

#pragma code_seg(".text$01accessor")
int ReplayBufferState_0042a870::GetBufferedBytes() const {
    const ReplayRecord_0042a870* records =
        reinterpret_cast<const ReplayRecord_0042a870*>(this);
    return (int)(record_cursor - records) * sizeof(ReplayRecord_0042a870) +
           (int)(byte_cursor - byte_buffer);
}
#pragma code_seg()
