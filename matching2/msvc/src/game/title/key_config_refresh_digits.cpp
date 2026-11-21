// 0x0042F8B0..0x00430243: refresh the twenty digit animations for five bindings.
// The native LTCG cluster preserves the private state-in-EAX entry and all
// twenty lookup/configuration paths as one complete compiler contribution.
#include "th10/game/key_config_refresh.hpp"

__forceinline int TitleKeyConfigView::FindChildHandle(
        unsigned short tag, KeyConfigLookupContext* context) {
    KeyConfigAnimationManager* manager = (KeyConfigAnimationManager*)context;
    KeyConfigAnimationObject* parent =
        (KeyConfigAnimationObject*)manager->Find(context, parent_handle_2cc);
    if (parent == 0) parent_handle_2cc.value = 0;
    // Retail forms the embedded child-link address even after a failed parent
    // lookup; preserve that observed path without adding a new null guard.
    for (KeyConfigChildNode* node = &parent->children_010;
         node != 0; node = node->next) {
        if (node->object->script_tag_38a == tag)
            return node->object->handle;
    }
    return 0;
}

__forceinline KeyConfigAnimationObject* TitleKeyConfigView::FindDigit(
        unsigned short tag) {
    KeyConfigLookupContext* context = g_sprt_ctrl;
    KeyConfigScriptId id;
    id.value = FindChildHandle(tag, context);
    return (KeyConfigAnimationObject*)
        ((KeyConfigAnimationManager*)context)->Find(context, id);
}

#pragma code_seg(".text$01refresh")
extern "C" __declspec(noinline) void __stdcall RefreshTitleKeyConfigView(TitleKeyConfigView* state) {
    {
        KeyConfigAnimationObject* digit = state->FindDigit(67);
        if (digit != 0)
            ConfigureKeyConfigDigit2(digit->resource, digit, state->bindings_59cc[0] / 10 + 0x33);
    }
    {
        KeyConfigAnimationObject* digit = state->FindDigit(68);
        if (digit != 0)
            ConfigureKeyConfigDigit2(digit->resource, digit, state->bindings_59cc[0] % 10 + 0x33);
    }
    {
        KeyConfigAnimationObject* digit = state->FindDigit(77);
        if (digit != 0)
            ConfigureKeyConfigDigit2(digit->resource, digit, state->bindings_59cc[0] / 10 + 0x33);
    }
    {
        KeyConfigAnimationObject* digit = state->FindDigit(78);
        if (digit != 0)
            ConfigureKeyConfigDigit2(digit->resource, digit, state->bindings_59cc[0] % 10 + 0x33);
    }
    {
        KeyConfigAnimationObject* digit = state->FindDigit(69);
        if (digit != 0)
            ConfigureKeyConfigDigit2(digit->resource, digit, state->bindings_59cc[1] / 10 + 0x33);
    }
    {
        KeyConfigAnimationObject* digit = state->FindDigit(70);
        if (digit != 0)
            ConfigureKeyConfigDigit2(digit->resource, digit, state->bindings_59cc[1] % 10 + 0x33);
    }
    {
        KeyConfigAnimationObject* digit = state->FindDigit(79);
        if (digit != 0)
            ConfigureKeyConfigDigit2(digit->resource, digit, state->bindings_59cc[1] / 10 + 0x33);
    }
    {
        KeyConfigAnimationObject* digit = state->FindDigit(80);
        if (digit != 0)
            ConfigureKeyConfigDigit2(digit->resource, digit, state->bindings_59cc[1] % 10 + 0x33);
    }
    {
        KeyConfigAnimationObject* digit = state->FindDigit(71);
        if (digit != 0)
            ConfigureKeyConfigDigit2(digit->resource, digit, state->bindings_59cc[2] / 10 + 0x33);
    }
    {
        KeyConfigAnimationObject* digit = state->FindDigit(72);
        if (digit != 0)
            ConfigureKeyConfigDigit2(digit->resource, digit, state->bindings_59cc[2] % 10 + 0x33);
    }
    {
        KeyConfigAnimationObject* digit = state->FindDigit(81);
        if (digit != 0)
            ConfigureKeyConfigDigit2(digit->resource, digit, state->bindings_59cc[2] / 10 + 0x33);
    }
    {
        KeyConfigAnimationObject* digit = state->FindDigit(82);
        if (digit != 0)
            ConfigureKeyConfigDigit2(digit->resource, digit, state->bindings_59cc[2] % 10 + 0x33);
    }
    {
        KeyConfigAnimationObject* digit = state->FindDigit(73);
        if (digit != 0)
            ConfigureKeyConfigDigit2(digit->resource, digit, state->bindings_59cc[3] / 10 + 0x33);
    }
    {
        KeyConfigAnimationObject* digit = state->FindDigit(74);
        if (digit != 0)
            ConfigureKeyConfigDigit2(digit->resource, digit, state->bindings_59cc[3] % 10 + 0x33);
    }
    {
        KeyConfigAnimationObject* digit = state->FindDigit(83);
        if (digit != 0)
            ConfigureKeyConfigDigit2(digit->resource, digit, state->bindings_59cc[3] / 10 + 0x33);
    }
    {
        KeyConfigAnimationObject* digit = state->FindDigit(84);
        if (digit != 0)
            ConfigureKeyConfigDigit2(digit->resource, digit, state->bindings_59cc[3] % 10 + 0x33);
    }
    {
        KeyConfigAnimationObject* digit = state->FindDigit(75);
        if (digit != 0)
            ConfigureKeyConfigDigit2(digit->resource, digit, state->bindings_59cc[4] / 10 + 0x33);
    }
    {
        KeyConfigAnimationObject* digit = state->FindDigit(76);
        if (digit != 0)
            ConfigureKeyConfigDigit2(digit->resource, digit, state->bindings_59cc[4] % 10 + 0x33);
    }
    {
        KeyConfigAnimationObject* digit = state->FindDigit(85);
        if (digit != 0)
            ConfigureKeyConfigDigit2(digit->resource, digit, state->bindings_59cc[4] / 10 + 0x33);
    }
    {
        KeyConfigAnimationObject* digit = state->FindDigit(86);
        if (digit != 0)
            ConfigureKeyConfigDigit2(digit->resource, digit, state->bindings_59cc[4] % 10 + 0x33);
    }
    return;
}
#pragma code_seg()
