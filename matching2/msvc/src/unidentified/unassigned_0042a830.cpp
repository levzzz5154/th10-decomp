// 0x0042A830..0x0042A84B (28 bytes): byte distance to the cursor at +0x5460,
// truncated to a whole record.
//
// Retail divides the byte distance by 6 (magic 0x2AAAAAAB and no shift) and
// multiplies the quotient back by 6, so the source is the same quotient as
// 0x0042A850 scaled back to bytes.

struct CursorState_0042a830 {
    unsigned char unknown_0000[0x5460];
    unsigned char* cursor;                 // +0x5460

    __declspec(noinline) int WholeRecordBytes();
};

#pragma code_seg(".text$01rec")
int CursorState_0042a830::WholeRecordBytes() {
    return (int)(cursor - (unsigned char*)this) / 6 * 6;
}
#pragma code_seg()
