struct Record3 {
    int unused_000;
    int field_004;
    int field_008;
    int field_00c;
    int field_010;
    int field_014;
    int field_018;
    int field_01c;
    int field_020;
    int field_024;
    int field_028;
};

__declspec(noinline) int InitializeRecord(
        Record3* record,
        int field_004, int field_008, int field_028,
        int field_00c, int field_010, int field_014,
        int field_018, int field_01c, int field_020, int field_024);
#pragma code_seg(".text$01accessor")
__declspec(noinline) int InitializeRecord(
        Record3* record,
        int field_004, int field_008, int field_028,
        int field_00c, int field_010, int field_014,
        int field_018, int field_01c, int field_020, int field_024) {
    if (record->field_004 >= 0)
        return -1;
    record->field_004 = field_004;
    record->field_008 = field_008;
    record->field_00c = field_00c;
    record->field_010 = field_010;
    record->field_014 = field_014;
    record->field_018 = field_018;
    record->field_01c = field_01c;
    record->field_020 = field_020;
    record->field_024 = field_024;
    record->field_028 = field_028;
    return 0;
}
#pragma code_seg()
