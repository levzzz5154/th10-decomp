struct Node_0041c0d0 {
    void* field_000;
    Node_0041c0d0* previous_004;
    Node_0041c0d0* next_008;
};
struct List_0041c0d0 {
    unsigned char pad_000[0x434];
    Node_0041c0d0* head_434;
    unsigned int count_438;
};
__declspec(noinline) void Remove_0041c0d0(List_0041c0d0* list, Node_0041c0d0* node);
#pragma code_seg(".text$01accessor")
void Remove_0041c0d0(List_0041c0d0* list, Node_0041c0d0* node) {
    --list->count_438;
    node->previous_004->next_008 = node->next_008;
    if (node->next_008)
        node->next_008->previous_004 = node->previous_004;
    if (list->head_434 == node)
        list->head_434 = node->previous_004;
}
#pragma code_seg()
