// The leaves only the options screen 0x0042D920 calls, unselected here: the
// slot stop 0x0042C730 and the sprite selection 0x00449670 with their real
// bodies (the maintained forms are
// src/game/title/title_dispatch_animation_slot.cpp and
// src/core/sprtlib/animation_manager_select_sprite_from_current_resource.cpp),
// and a stand-in for the label refresh 0x0042E5A0, whose complete body the
// options_label_refresh cluster selects (TH10_FULL_OPTIONS_REFRESH).
#include "th10/game/options_update.hpp"

struct SpriteVm_00449670 {
    unsigned char reserved_000[0x308];
    void* resource;                     // +0x308
};
// 0x0043E5A0: show a sprite of a resource.
void __fastcall SelectResourceSprite_0043e5a0(void* resource, int sprite);
extern "C" int g_options_music_volume;
extern "C" const char str_set_vol[];

#pragma code_seg(".text$0042c730_fn")
void TitleAnimationSlotView::StopSlot(int slot) {
    AnimationManager_SetStopFrameAndRun(
        2, reinterpret_cast<RecoveryLookupContext*>(g_sprt_ctrl), slots[slot]);
}
#pragma code_seg(".text$00449670_fn")
void SpriteHandle::SelectSprite(int sprite) {
    RecoveryScriptId id = { static_cast<int>(value) };
    SpriteVm_00449670* vm = static_cast<SpriteVm_00449670*>(
        reinterpret_cast<RecoveryLookup*>(g_sprt_ctrl)->Find(
            reinterpret_cast<RecoveryLookupContext*>(g_sprt_ctrl), id));
    if (vm != 0)
        SelectResourceSprite_0043e5a0(vm->resource, sprite);
}
#pragma code_seg(".text$0042e5a0_fn")
#ifndef TH10_FULL_OPTIONS_REFRESH
void __stdcall RefreshOptions2(Title* room) {
    g_options_music_volume = g_key_bindings.music_volume;
    for (int kind = 8; kind < 12; ++kind) {
        reinterpret_cast<RecoveryMusicResourceQueue*>(&g_sound_manager)->RegisterResource(
            str_set_vol, kind, kind);
        room->animation_slots[2] = 0;
    }
}
#endif
#pragma code_seg()
