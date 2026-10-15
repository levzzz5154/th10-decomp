// 0x00426360: draw the player and option callbacks, then the optional power bar.
// 0x00426510: scheduler callback forwarding its ECX state to that draw worker.
#include "th10/render/quad_batch.hpp"

struct PlayerOption {
    unsigned char unknown_00[0x94];
    int (__fastcall *draw)(PlayerOption*);
};
struct PlayerRenderState {
    unsigned char unknown_000[0x14];
    RenderEntity sprite;
    unsigned char unknown_3ac[0x3c0 - 0x3ac];
    RenderVec3 position;
    unsigned char unknown_3cc[0x458 - 0x3cc];
    int state;
    unsigned char unknown_45c[0x32a0 - 0x45c];
    PlayerOption options[4];
    __declspec(noinline) int Draw();
};
struct GameFlags { unsigned char unknown_00[0x54]; signed char flags; };
struct PauseState { unsigned char unknown_00[0x10]; int paused; };
struct EnemyState { unsigned char unknown_0000[0x9eb8]; int active; };
struct DialogState { int unknown_00; int active; };
extern "C" GameFlags* data_00477810;
extern "C" PauseState* data_00477704;
extern "C" EnemyState* data_0047770c;
extern "C" DialogState* g_pause_menu;
extern "C" int data_00474c58;
extern "C" __declspec(noinline) double __stdcall FloorPixelCoordinate(float);
extern "C" __declspec(noinline) int __cdecl asm_FUN_004451c0_004451c0(
    AnimationManager_00442F50*, RenderEntity*);

// Copy coordinates in order so source and destination may alias.
inline void CopyRenderPosition(RenderVec3& to, const RenderVec3& from, float dx, float dy) {
    to.x = from.x + dx;
    to.y = from.y + dy;
    to.z = from.z;
}
#pragma code_seg(".text$0001worker")
int PlayerRenderState::Draw() {
    if (state != 2) {
        CopyRenderPosition(sprite.position, position, 224.0f, 16.0f);
        asm_FUN_004451c0_004451c0(data_00491c10, &sprite);
        for (int index = 0; index < 4; ++index) {
            if (options[index].draw) options[index].draw(&options[index]);
        }
        if (data_00477810 && (data_00477810->flags & 0x80) && data_00477704 &&
            data_0047770c && data_00477704->paused == 0 &&
            data_0047770c->active == 0 && g_pause_menu->active == 0 &&
            data_00474c58 != 0) {
            int power = data_00474c58;
            ScreenRect rect;
            rect.left = (float)FloorPixelCoordinate((position.x + 225.0f) - 16.0f);
            rect.right = power * 0.29230770468711853f + rect.left;
            rect.top = (float)FloorPixelCoordinate((position.y + 17.0f) - 24.0f);
            rect.bottom = rect.top + 2.0f;
            DrawSolidQuad(&rect, 0x80000000);
            rect.left -= 1.0f;
            rect.right -= 1.0f;
            rect.top -= 1.0f;
            rect.bottom -= 1.0f;
            DrawSolidQuad(&rect, 0xffffffff);
        }
    }
    return 1;
}
#pragma code_seg(".text$0003callback")
int __fastcall PlayerDrawCallback(PlayerRenderState* player) {
    return player->Draw();
}
#pragma code_seg()


// Unselected complete retail helper models. The dispatcher uses its maintained
// body unchanged; this link derives its manager-ECX/entity-EAX entry convention.
#include "../render/special_quad.cpp"
#include "../render/anm_batch_flush.cpp"
#include "../render/anm_vm_draw_dispatch.cpp"
