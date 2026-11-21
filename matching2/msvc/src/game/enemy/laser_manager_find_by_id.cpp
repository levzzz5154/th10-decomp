// 0x0040CF90..0x0040CFA5: find a linked enemy node by its runtime ID.
// The native-LTCG cluster supplies the retail manager-in-EAX/ID-in-ECX ABI.

struct EnemyListNode {
    unsigned char pad_000[0x8];
    EnemyListNode* next;
    unsigned char pad_00c[0x48];
    int id;
};

struct LaserManagerFindView {
    unsigned char pad_000[0x18];
    EnemyListNode* list_head;

    __declspec(noinline) EnemyListNode* FindById(
        int id);
};

#pragma code_seg(".text$01findbyid")
EnemyListNode*
LaserManagerFindView::FindById(int id) {
    EnemyListNode* node = list_head;
    while (node != 0) {
        if (node->id == id)
            return node;
        node = node->next;
    }
    return 0;
}
#pragma code_seg()
