#include "../../../src/core/sound/animation_manager_queue_resource_0043dc90.cpp"
#include "../../../src/game/title/key_config.cpp"
// Compiler-visible ABI anchors and synthetic caller, never selected as recovered code.
#include "../../../src/game/title/fun_0042f8b0_0042f8b0.cpp"
__forceinline void KeyConfigMatrix::SetIdentity() {
    values[3][2] = 0.0f;
    values[3][1] = 0.0f;
    values[3][0] = 0.0f;
    values[2][3] = 0.0f;
    values[2][1] = 0.0f;
    values[2][0] = 0.0f;
    values[1][3] = 0.0f;
    values[1][2] = 0.0f;
    values[1][0] = 0.0f;
    values[0][3] = 0.0f;
    values[0][2] = 0.0f;
    values[0][1] = 0.0f;
    values[3][3] = 1.0f;
    values[2][2] = 1.0f;
    values[1][1] = 1.0f;
    values[0][0] = 1.0f;
}

#pragma code_seg(".text$07configure")
extern "C" __declspec(noinline) int __stdcall ConfigureKeyConfigDigit_0043e5a0(
    KeyConfigResource* resource, KeyConfigAnimationObject* object, int index) {
    unsigned char* res = reinterpret_cast<unsigned char*>(resource);
    if (*reinterpret_cast<void**>(res + 0x108) == 0 ||
        *reinterpret_cast<unsigned int*>(res + 0x124) != 0)
        return -1;

    object->record_index = static_cast<unsigned short>(index);
    object->resource = resource;
    object->record = *reinterpret_cast<unsigned char**>(res + 0x118) + index * 0x44;
    object->width = *reinterpret_cast<float*>(object->record + 0x34);
    object->height = *reinterpret_cast<float*>(object->record + 0x30);
    object->block_a.SetIdentity();
    object->block_b.SetIdentity();
    unsigned char* rec = object->record;
    object->block_a.values[0][0] = object->width * 0.00390625f;
    object->block_a.values[1][1] = object->height * 0.00390625f;
    object->block_b.values[0][0] =
        (*reinterpret_cast<float*>(rec + 0x38) /
         *reinterpret_cast<float*>(rec + 0x1C)) * object->width;
    object->block_b.values[1][1] =
        (*reinterpret_cast<float*>(rec + 0x3C) /
         *reinterpret_cast<float*>(rec + 0x18)) * object->height;
    object->block_copy = object->block_a;
    return 0;
}
#pragma code_seg()

#pragma code_seg(".text$09find")
void* __fastcall KeyConfigAnimationManager::Find(
        KeyConfigLookupContext* context, KeyConfigScriptId id) {
    if (!id.value) return 0;
    for (KeyConfigChildNode* node = context->primary_bucket; node != 0; node = node->next)
        if (node->object->handle == id.value) return node->object;
    for (KeyConfigChildNode* node = context->secondary_bucket; node != 0; node = node->next)
        if (node->object->handle == id.value) return node->object;
    return 0;
}
#pragma code_seg()


#pragma code_seg(".text$11context")
extern "C" __declspec(noinline) int __stdcall KeyConfigReassignContext(TitleKeyConfigView** states, int* slots, int* keys, int count) {
    for (int i = 0; i < count; ++i) KeyConfigReassignSlot_00430250(states[i], slots[i], keys[i]);
    return count;
}
#pragma code_seg()
