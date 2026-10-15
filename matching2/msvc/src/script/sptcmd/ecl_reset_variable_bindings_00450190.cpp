// Reset the intrusive variable-binding chain rooted in the ECL instance.
struct EclBindingInstance {
    void* field_000;
    int binding;
};

struct EclBindingNode {
    EclBindingInstance* instance;
    EclBindingNode* next;
};

struct EclVm_00450190 {
    unsigned char pad_000[0x1034];
    EclBindingNode* bindings;
    __declspec(noinline) void ResetVariableBindings();
};

typedef char EclVm_00450190_size_must_fit[sizeof(EclVm_00450190) == 0x1038 ? 1 : -1];

#pragma code_seg(".text$01reset")
void EclVm_00450190::ResetVariableBindings() {
    EclBindingNode* node = bindings;
    while (node != 0) {
        EclBindingNode* next = node->next;
        node->instance->binding = 0;
        node = next;
    }
}
#pragma code_seg()
