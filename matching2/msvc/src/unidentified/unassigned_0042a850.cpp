// 0x0042A850..0x0042A866 (23 bytes): index of the cursor at +0x5460.
//
// Retail subtracts the object address from the cursor and divides by 6 with the
// magic 0x2AAAAAAB and no shift, so the source is the byte distance divided by
// the 6-byte record the cursor walks.  The sibling 0x0042A830 multiplies the
// same quotient back by 6 and 0x0042A820 measures the other cursor (at +0x6274)
// against the buffer that starts at +0x5464.

struct CursorState_0042a850 {
    unsigned char unknown_0000[0x5460];
    unsigned char* cursor;                 // +0x5460

    __declspec(noinline) int RecordIndex();
};

#pragma code_seg(".text$01idx")
int CursorState_0042a850::RecordIndex() {
    return (int)(cursor - (unsigned char*)this) / 6;
}
#pragma code_seg()
