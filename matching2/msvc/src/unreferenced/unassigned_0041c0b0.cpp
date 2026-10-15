struct Node_0041c0b0 {
    void* field_000;
    Node_0041c0b0* field_004;
    Node_0041c0b0* field_008;
};
struct List_0041c0b0 {
    unsigned char pad_000[0x434];
    Node_0041c0b0* head_434;
    unsigned int count_438;
};
__declspec(noinline) void Insert(List_0041c0b0* list, Node_0041c0b0* node);
#pragma code_seg(".text$01accessor")
void Insert(List_0041c0b0* list, Node_0041c0b0* node) {
    Node_0041c0b0* head = list->head_434;
    node->field_004 = head;
    head->field_008 = node;
    list->head_434 = node;
    ++list->count_438;
}
#pragma code_seg()
