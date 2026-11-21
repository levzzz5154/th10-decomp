// Exact native-LTCG body for the private EAX/ECX linked-list helper.
struct EclVariableObject {
    unsigned char pad_000[0x1010];
    int variable_id;
};

struct EclVariableNode {
    EclVariableObject* object;
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
        if (node->object->variable_id == variable)
            return node;
        node = node->next;
    }
    return 0;
}
#pragma code_seg()
