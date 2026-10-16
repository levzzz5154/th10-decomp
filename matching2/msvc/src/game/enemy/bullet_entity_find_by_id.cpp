// 0x0040CF90..0x0040CFA5: find a linked bullet node by its runtime ID.
// The native-LTCG cluster supplies the retail manager-in-EAX/ID-in-ECX ABI.

struct BulletEntityFindByIdNode {
    unsigned char pad_000[0x8];
    BulletEntityFindByIdNode* next;
    unsigned char pad_00c[0x48];
    int id;
};

struct BulletEntityFindByIdManager {
    unsigned char pad_000[0x18];
    BulletEntityFindByIdNode* list_head;

    __declspec(noinline) BulletEntityFindByIdNode* FindById(
        int id);
};

#pragma code_seg(".text$01findbyid")
BulletEntityFindByIdNode*
BulletEntityFindByIdManager::FindById(int id) {
    BulletEntityFindByIdNode* node = list_head;
    while (node != 0) {
        if (node->id == id)
            return node;
        node = node->next;
    }
    return 0;
}
#pragma code_seg()
