// 0x0040CF90..0x0040CFA5: find a linked bullet node by its runtime ID.
// The native-LTCG cluster supplies the retail manager-in-EAX/ID-in-ECX ABI.

struct BulletEntityFindByIdNode_0040cf90 {
    unsigned char pad_000[0x8];
    BulletEntityFindByIdNode_0040cf90* next;
    unsigned char pad_00c[0x48];
    int id;
};

struct BulletEntityFindByIdManager_0040cf90 {
    unsigned char pad_000[0x18];
    BulletEntityFindByIdNode_0040cf90* list_head;

    __declspec(noinline) BulletEntityFindByIdNode_0040cf90* FindById(
        int id);
};

#pragma code_seg(".text$01findbyid")
BulletEntityFindByIdNode_0040cf90*
BulletEntityFindByIdManager_0040cf90::FindById(int id) {
    BulletEntityFindByIdNode_0040cf90* node = list_head;
    while (node != 0) {
        if (node->id == id)
            return node;
        node = node->next;
    }
    return 0;
}
#pragma code_seg()
