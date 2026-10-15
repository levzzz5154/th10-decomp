// 0x004014D0..0x004014E9: clear the two pending words, advance the
// sequence counter, and report success.
struct WidgetHost_004014d0 {
    unsigned char unknown_00[0x896C];
    int field_896C;
    int field_8970;
    unsigned char unknown_8974[0x1C];
    int field_8990;

    __declspec(noinline) int ClearPending_004014d0();
};

#pragma code_seg(".text$01accessor")
int WidgetHost_004014d0::ClearPending_004014d0() {
    field_896C = 0;
    field_8970 = 0;
    ++field_8990;
    return 1;
}
#pragma code_seg()
