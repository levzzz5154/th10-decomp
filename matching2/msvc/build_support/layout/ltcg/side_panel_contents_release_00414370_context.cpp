// Compiler context and ABI anchors only; none of these bytes enter the image.
#include "../../../src/game/front/side_panel_contents_release_00414370.cpp"

extern "C" SidePanel* g_front;
extern "C" void __cdecl SidePanelContentsBarrier(void* value);

#pragma inline_depth(0)
#pragma code_seg(".text$0040a000_context")
extern "C" int __stdcall SidePanelContentsContext(int count) {
    // The run state is reachable through pointers in the real program.
    SidePanelContentsBarrier(&g_globals);
    for (int index = 0; index < count; ++index)
        SidePanel_ReleaseContents_00414370(g_front);
    return count;
}
#pragma code_seg()
#pragma inline_depth()

// Stand-ins for the two release routines. Each keeps its receiver across
// opaque calls the way the real body does, so the pass hands the slot over in
// ESI and the file in EDI.
#pragma code_seg(".text$004136c0_fn")
void PanelSlot_00414370::Release() {
    SidePanelContentsBarrier(this);
    SidePanelContentsBarrier(this);
}
#pragma code_seg(".text$00447810_fn")
void PanelResource_00414370::Release() {
    void** entry = reinterpret_cast<void**>(this);
    do {
        SidePanelContentsBarrier(*entry);
        ++entry;
    } while (*entry);
    SidePanelContentsBarrier(this);
}

// The bodies of the lookup (0x004491C0), the flag setter (0x004492A0) and the
// resource marker (0x004493E0).
#pragma code_seg(".text$004491c0_fn")
__declspec(noinline) PanelAnimationEntry* __fastcall PanelAnimation_Find_004491c0(
        PanelAnimationManager_00414370* manager, PanelAnimationId id) {
    if (!id.value)
        return 0;
    for (PanelAnimationEntry* node = manager->primary; node != 0; node = node->next)
        if (*(int*)node->object == id.value)
            return node->object;
    for (PanelAnimationEntry* node = manager->secondary; node != 0; node = node->next)
        if (*(int*)node->object == id.value)
            return node->object;
    return 0;
}
#pragma code_seg(".text$004492a0_fn")
__declspec(noinline) PanelAnimationEntry* __fastcall PanelAnimation_SetFlag_004492a0(
        PanelAnimationManager_00414370* manager, PanelAnimationId id) {
    PanelAnimationEntry* entry = PanelAnimation_Find_004491c0(manager, id);
    if (entry) {
        entry->flags |= 0x4000000;
        if (!entry->children_flagged)
            for (entry = entry->children; entry != 0; entry = entry->next)
                entry->object->flags |= 0x4000000;
    }
    return entry;
}
#pragma code_seg(".text$004493e0_fn")
__declspec(noinline) void PanelAnimationManager_00414370::MarkResourceForRemoval(void* resource) {
    PanelAnimationEntry* node = primary;
    while (node) {
        PanelAnimationEntry* next = node->next;
        PanelAnimationEntry* object = node->object;
        if (object->resource == resource)
            object->flags |= 0x04000000u;
        node = next;
    }
    node = secondary;
    while (node) {
        PanelAnimationEntry* next = node->next;
        PanelAnimationEntry* object = node->object;
        if (object->resource == resource)
            object->flags |= 0x04000000u;
        node = next;
    }
}
#pragma code_seg()
