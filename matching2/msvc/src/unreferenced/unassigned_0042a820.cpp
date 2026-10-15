// 0x0042A820..0x0042A82D (14 bytes): bytes used in the slot buffer.
//
// The object carries a byte cursor at +0x6274 into the buffer that starts at
// +0x5464 (0x42A900 advances that cursor one byte at a time and stops it at
// 0x78 bytes).  Retail subtracts the object address and then the literal
// 0x5464, which is the shape `(cursor - (char*)this) - 0x5464`; writing
// `cursor - slots` instead would add an `lea` for the base.
//
// ECX is the object, so the body compiles as a plain __thiscall member.

struct SlotBuffer {
    unsigned char unknown_00[0x5464];
    unsigned char slots[0xE10];             // +0x5464 .. +0x6274
    unsigned char* cursor;                  // +0x6274

    __declspec(noinline) int BytesUsed();
};

#pragma code_seg(".text$01used")
int SlotBuffer::BytesUsed() {
    return (int)(cursor - (unsigned char*)this) - 0x5464;
}
#pragma code_seg()
