struct Node4 {
    void* field_000;
    Node4* previous_004;
    Node4* next_008;
};
struct List2 {
    unsigned char pad_000[0x434];
    Node4* head_434;
    unsigned int count_438;
};
__declspec(noinline) void Remove2(List2* list, Node4* node);
#pragma code_seg(".text$01accessor")
void Remove2(List2* list, Node4* node) {
    --list->count_438;
    node->previous_004->next_008 = node->next_008;
    if (node->next_008)
        node->next_008->previous_004 = node->previous_004;
    if (list->head_434 == node)
        list->head_434 = node->previous_004;
}
#pragma code_seg()
