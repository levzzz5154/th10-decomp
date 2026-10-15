// Exact native-LTCG body for the private EAX/ECX linked-list helper.
struct EclVariableNode_00450160 {
    void* object;
    EclVariableNode_00450160* next;
};

struct EclVariableVm_00450160 {
    unsigned char pad_000[0x1030];
    EclVariableNode_00450160 bindings;
    __declspec(noinline) EclVariableNode_00450160* FindVariable(int variable);
};

#pragma code_seg(".text$02find")
EclVariableNode_00450160* EclVariableVm_00450160::FindVariable(int variable) {
    EclVariableNode_00450160* node = &bindings;
    while (node != 0) {
        if (*(int*)((unsigned char*)node->object + 0x1010) == variable)
            return node;
        node = node->next;
    }
    return 0;
}
#pragma code_seg()
