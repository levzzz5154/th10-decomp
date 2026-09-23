// 0x0042A900..0x0042A925 (38 bytes): append one byte to the slot buffer.
//
// The retail entry receives the buffer object in EAX and the byte in DL. It
// loads the cursor at +0x6274, writes through it, advances and stores the
// cursor, then returns whether the advanced cursor is at least 0x78 bytes past
// the buffer start at +0x5464.
//
// The C++ signature below is a semantic model only. A normal __cdecl signature
// cannot express the private EAX receiver / DL value ABI. The old C-linkage
// symbol spelling is retained while the manifest still points at this source;
// this does not claim that this compiled function has the retail ABI or bytes.

struct SlotBuffer_0042a900 {
    unsigned char unknown_0000[0x5464];
    unsigned char bytes_5464[0xE10];       // +0x5464 .. +0x6273
    unsigned char* cursor_6274;             // +0x6274
};

typedef char SlotBuffer_0042a900_requires_32_bit_pointers[
    sizeof(unsigned char*) == 4 ? 1 : -1];
typedef char SlotBuffer_0042a900_layout_check[
    sizeof(SlotBuffer_0042a900) == 0x6278 ? 1 : -1];

extern "C" __declspec(noinline) int __cdecl asm_unassigned_0042a900(
    SlotBuffer_0042a900* buffer, unsigned char value) {
    unsigned char* write_cursor = buffer->cursor_6274;
    *write_cursor = value;

    unsigned char* next_cursor = write_cursor + 1;
    buffer->cursor_6274 = next_cursor;

    // For a cursor inside this byte array, this is the retail signed test:
    // (next_cursor - object - 0x5464) >= 0x78.
    int bytes_written = static_cast<int>(next_cursor - buffer->bytes_5464);
    return bytes_written >= 0x78;
}
