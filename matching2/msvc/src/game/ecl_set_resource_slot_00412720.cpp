// 0x00412720: bind an ECL resource slot and, for a valid id, its value and data cursor.
struct ResourceSlot_00412720 {
    int id;
    int value;
    const char* begin;
    const char* cursor;
};
struct SlotTable_00412720 {
    unsigned char reserved_0000[0x2494];
    ResourceSlot_00412720 slots[1];
};

#pragma code_seg(".text$01accessor")
__declspec(noinline) void __stdcall BindSlot_00412720(SlotTable_00412720* table, int index, int id, int value, const char* data) {
    table->slots[index].id = id;
    if (id >= 0) {
        table->slots[index].value = value;
        table->slots[index].begin = data;
        table->slots[index].cursor = data;
    }
}
#pragma code_seg()
