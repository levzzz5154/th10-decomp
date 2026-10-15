// Reset the intrusive variable-binding chain rooted in the ECL instance.
struct EclBindingInstance_00450190 {
    void* field_000;
    int binding;
};

struct EclBindingNode_00450190 {
    EclBindingInstance_00450190* instance;
    EclBindingNode_00450190* next;
};

struct EclVm_00450190 {
    unsigned char pad_000[0x1034];
    EclBindingNode_00450190* bindings;
    __declspec(noinline) void ResetVariableBindings();
};

typedef char EclVm_00450190_size_must_fit[sizeof(EclVm_00450190) == 0x1038 ? 1 : -1];

#pragma code_seg(".text$01reset")
void EclVm_00450190::ResetVariableBindings() {
    EclBindingNode_00450190* node = bindings;
    while (node != 0) {
        EclBindingNode_00450190* next = node->next;
        node->instance->binding = 0;
        node = next;
    }
}
#pragma code_seg()
