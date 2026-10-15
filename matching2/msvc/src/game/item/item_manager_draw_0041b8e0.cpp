// 0x0041B8E0 (281 bytes): draw every live item, and 0x0041BA30 (29 bytes),
// the scheduler draw callback that skips the pass while the game is paused.
//
// Items are positioned in playfield coordinates; the sprite is offset into
// screen space. An item above the top edge is drawn as a pinned indicator at
// y = 24 that fades with the item's distance beyond the edge.

#include "th10/game/item_manager_0041b8e0.hpp"

#pragma code_seg(".text$00draw")
__declspec(noinline) int ItemManager_0041b8e0::Draw() {
    Item_0041b8e0* item = items;
    for (int remaining = ITEM_COUNT; remaining != 0; --remaining, ++item) {
        if (item->state == 0) continue;

        PlayfieldToScreen_0041b8e0(&item->position, &item->sprite_position);

        if (item->sprite_position.y < 8.0f) {
            float distance = item->sprite_position.y - 8.0f;
            item->sprite_position.y = 24.0f;
            if (distance >= 32.0f)
                item->sprite_alpha = 0xFF;
            else
                item->sprite_alpha = (unsigned char)(255.0f * (distance / 32.0f));
            if (item->sprite_index != item->type + 0x161)
                g_bullet_manager->item_sprites->ConfigureObject(item->Sprite(), item->type + 0x160);
        } else if (item->sprite_index != item->type + 0x158) {
            g_bullet_manager->item_sprites->ConfigureObject(item->Sprite(), item->type + 0x157);
            item->sprite_alpha = 0xFF;
        }
        asm_FUN_004451c0_004451c0(item->Sprite(), g_sprt_ctrl);
    }
    return 1;
}
#pragma code_seg()

#pragma code_seg(".text$00ondraw")
int __fastcall ItemManager_OnDraw_0041ba30(ItemManager_0041b8e0* manager) {
    if (g_game != 0 && (g_game->flags & 4))
        return 1;
    return manager->Draw();
}
#pragma code_seg()
