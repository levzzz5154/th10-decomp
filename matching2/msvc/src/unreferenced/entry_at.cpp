// 0x00401D00: address of one 0x44-byte record in the table at +0x118.
// The table owner arrives in ECX and the index in EAX.
struct Record2 { unsigned char bytes[0x44]; };
struct RecordTable {
    unsigned char reserved_000[0x118];
    Record2* records;       // +0x118
    __declspec(noinline) Record2* At(int index);
};

#pragma code_seg(".text$01accessor")
Record2* RecordTable::At(int index) {
    return &records[index];
}
#pragma code_seg()
