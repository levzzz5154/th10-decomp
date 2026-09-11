// 0x004014F0..0x00401509: clears the two pending-timer words, bumps the
// sequence counter and reports success. The owner block is huge, so only the
// touched offsets are described.
struct WidgetHost {
    unsigned char unknown_00[0x896C];
    int field_896C;                  // +0x896C
    int field_8970;                  // +0x8970
    unsigned char unknown_8974[0x1C];
    int field_8990;                  // +0x8990

    int ClearPending_004014f0();
};

int WidgetHost::ClearPending_004014f0() {
    field_896C = 0;
    field_8970 = 0;
    ++field_8990;
    return 1;
}
