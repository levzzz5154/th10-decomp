// Exact native-LTCG body for the private EAX/ECX linked-list helper.
struct EclVariableNode {
    void* object;
    EclVariableNode* next;
};

struct EclVariableVm {
    unsigned char pad_000[0x1030];
    EclVariableNode bindings;
    __declspec(noinline) EclVariableNode* FindVariable(int variable);
};

#pragma code_seg(".text$02find")
EclVariableNode* EclVariableVm::FindVariable(int variable) {
    EclVariableNode* node = &bindings;
    while (node != 0) {
        if (*(int*)((unsigned char*)node->object + 0x1010) == variable)
            return node;
        node = node->next;
    }
    return 0;
}
#pragma code_seg()
