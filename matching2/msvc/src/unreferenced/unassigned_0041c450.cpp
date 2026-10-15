// 0x0041C450: dispatch every list entry that is not the primary kind
// The register convention below is only reachable from a native LTCG link,
// so this region is compiled as a cluster.

struct Item_0041c450 {
    virtual void Slot00();
    virtual void Slot01();
    virtual void Slot02();
    virtual void Slot03();
    unsigned char pad_004[0x08 - 0x04];
    Item_0041c450* next;   // +0x08
    int kind;                                               // +0x0C
};

struct ObjectAccessor_0041c450 {
    unsigned char pad_000[0x18];
    Item_0041c450* head;    // +0x18
};

__declspec(noinline) void Slot03() {}

__declspec(noinline) int Process_0041c450(ObjectAccessor_0041c450* object);
#pragma code_seg(".text$01accessor")
int Process_0041c450(ObjectAccessor_0041c450* object) {
    Item_0041c450* item = object->head;
    if (item != 0) {
        do {
            Item_0041c450* next = item->next;
            if (item->kind != 1) {
                item->Slot03();
            }
            item = next;
        } while (item != 0);
    }
    return 1;
}
#pragma code_seg()
