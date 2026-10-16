// 0x0042C8A0: one entry of a two-dimensional table of 0x10DF-entry rows at +0x4D0.
struct Table {
    unsigned char reserved_000[0x4D0];
    int rows[1][0x10DF];              // +0x4D0
};

#pragma code_seg(".text$01accessor")
__declspec(noinline) int __stdcall TableEntry(Table* table, int row, int column) {
    return table->rows[row][column];
}
#pragma code_seg()
