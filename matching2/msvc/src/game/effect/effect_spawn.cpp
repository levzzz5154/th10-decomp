// 0x0040B070: start an effect of a kind from the owner's animation file.
//
// The kind names a script of the file; the new animation goes to the back of
// the primary list in bucket 15, gets the kind's setup step and its two
// values, and its handle is returned (zero when it is already gone). Nothing
// in the program calls it; the kind arrives in EAX and the owner, the hidden
// result pointer and the argument on the stack.
#include "th10/game/effect_kind_spawn.hpp"

// 0x00448D00 inline: script `index` of a file as a new animation at the back
// of the primary list.
static __forceinline void CreatePrimaryBack(
        AnimationBank* file, EffectAnimationHandle* out, int index, int bucket) {
    EffectAnimationNode* object =
        reinterpret_cast<AnimationPool2*>(g_sprt_ctrl)->Allocate();
    unsigned int flags = object->flags;
    object->render_bucket = bucket;
    object->flags = flags | 0x40000000u;
    file->InitializeObject(object, index);
    AnimationManager_RegisterPrimaryBack(g_sprt_ctrl, (void**)out, object);
}

#pragma code_seg(".text$0040b070_fn")
EffectAnimationHandle __stdcall EffectSpawnView::SpawnEffect(
        void* argument, int kind) {
    EffectKind* entry = &g_effect_kinds[kind];
    EffectAnimationHandle created;
    CreatePrimaryBack(file, &created, entry->script, 15);
    EffectAnimationNode* node = g_sprt_ctrl->Find(created);
    if (!node)
        created.value = 0;
    if (entry->setup)
        entry->setup(node, argument);
    node->kind_value_a = entry->value_a;
    node->kind_value_b = entry->value_b;
    return created;
}
#pragma code_seg()

// 0x0040B110: the same for an animation file given directly (kind in EAX,
// then the file, the hidden result pointer and the argument on the stack).
// Also uncalled. The two bodies are written out separately: a shared inline
// body changes 0x0040B070.
#pragma code_seg(".text$0040b110_fn")
EffectAnimationHandle __stdcall SpawnEffectFromFile(
        int kind, AnimationBank* file, void* argument) {
    EffectKind* entry = &g_effect_kinds[kind];
    EffectAnimationHandle created;
    CreatePrimaryBack(file, &created, entry->script, 15);
    EffectAnimationNode* node = g_sprt_ctrl->Find(created);
    if (!node)
        created.value = 0;
    if (entry->setup)
        entry->setup(node, argument);
    node->kind_value_a = entry->value_a;
    node->kind_value_b = entry->value_b;
    return created;
}
#pragma code_seg()
