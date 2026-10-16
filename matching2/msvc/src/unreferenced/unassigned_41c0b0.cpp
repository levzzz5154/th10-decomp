struct Node3 {
    void* field_000;
    Node3* field_004;
    Node3* field_008;
};
struct List {
    unsigned char pad_000[0x434];
    Node3* head_434;
    unsigned int count_438;
};
__declspec(noinline) void Insert(List* list, Node3* node);
#pragma code_seg(".text$01accessor")
void Insert(List* list, Node3* node) {
    Node3* head = list->head_434;
    node->field_004 = head;
    head->field_008 = node;
    list->head_434 = node;
    ++list->count_438;
}
#pragma code_seg()
