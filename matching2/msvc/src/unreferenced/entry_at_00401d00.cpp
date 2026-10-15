// 0x00401D00: address of one 0x44-byte record in the table at +0x118.
// The table owner arrives in ECX and the index in EAX.
struct Record_00401d00 { unsigned char bytes[0x44]; };
struct RecordTable {
    unsigned char reserved_000[0x118];
    Record_00401d00* records;       // +0x118
    __declspec(noinline) Record_00401d00* At(int index);
};

#pragma code_seg(".text$01accessor")
Record_00401d00* RecordTable::At(int index) {
    return &records[index];
}
#pragma code_seg()
