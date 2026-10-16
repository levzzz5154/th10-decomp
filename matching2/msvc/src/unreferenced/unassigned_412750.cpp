// 0x00412750: bind an ECL resource slot and, for a valid id, its three values.
struct ResourceSlot3 {
    int id;
    int first, second, third;
};
struct SlotTable2 {
    unsigned char reserved_0000[0x2494];
    ResourceSlot3 slots[1];
};

#pragma code_seg(".text$01accessor")
__declspec(noinline) void __stdcall SetSlot(SlotTable2* table, int index, int id, int first, int second, int third) {
    table->slots[index].id = id;
    if (id >= 0) {
        table->slots[index].first = first;
        table->slots[index].second = second;
        table->slots[index].third = third;
    }
}
#pragma code_seg()
