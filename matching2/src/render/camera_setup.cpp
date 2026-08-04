// =============================================================================
// camera_setup.cpp - Camera, default viewport, and back-buffer surface ops
// =============================================================================
#include "th10/render/camera_setup.hpp"

#ifdef _MSC_VER
extern "C" void sub_442F50(void);
extern "C" void D3DXMatrixLookAtLH(void*, void*, void*, void*, void*);
extern "C" void D3DXMatrixPerspectiveFovLH(void*, float, float, float, float);
extern "C" unsigned long dword_491C10;
extern "C" void* dword_491C30;
extern "C" float flt_470B98;
extern "C" float flt_470B0C;
extern "C" double dbl_470BA0;
extern "C" void sub_43BC40(void*);
extern "C" unsigned long dword_491CF4;
extern "C" unsigned long dword_491CF8;
extern "C" unsigned long dword_491CFC;
extern "C" unsigned long dword_491D00;
extern "C" unsigned long dword_491D04;
extern "C" unsigned long dword_491D08;
#endif

// Semantic reconstruction 0x00421480 - rebuild view/projection matrices.
// camera block and hand both to the device (SetTransform states 2 and 3),
// then publish the clip-rect pointers into the manager.
#ifdef _MSC_VER
__declspec(naked) void Camera_ApplyRetail() {
    __asm {
        sub esp, 2Ch
        push ebx
        push esi
        mov esi, dword ptr [dword_491C10]
        test esi, esi
        jz loc_421494
        call sub_442F50
loc_421494:
        mov eax, [edi+0D4h]
        fild dword ptr [edi+0D4h]
        test eax, eax
        jge loc_4214AA
        fadd dword ptr [flt_470B98]
loc_4214AA:
        mov ecx, [edi+0D8h]
        fst dword ptr [esp+8]
        test ecx, ecx
        fmul dword ptr [flt_470B0C]
        fild dword ptr [edi+0D8h]
        jge loc_4214CA
        fadd dword ptr [flt_470B98]
loc_4214CA:
        fst dword ptr [esp+0Ch]
        lea edx, [esp+10h]
        fmul dword ptr [flt_470B0C]
        push edx
        fld dword ptr [esp+0Ch]
        lea eax, [esp+20h]
        fdiv dword ptr [esp+10h]
        push eax
        lea ecx, [esp+30h]
        push ecx
        lea esi, [edi+4Ch]
        push esi
        mov dword ptr [esp+34h], 0
        mov dword ptr [esp+20h], 0
        mov dword ptr [esp+24h], 0BF800000h
        mov dword ptr [esp+28h], 0
        fstp dword ptr [esp+1Ch]
        fld st(1)
        fstp dword ptr [esp+38h]
        fst dword ptr [esp+3Ch]
        fld qword ptr [dbl_470BA0]
        fptan
        fstp st(0)
        fdivr st, st(1)
        fstp dword ptr [esp+40h]
        fxch st(1)
        fstp dword ptr [esp+2Ch]
        fstp dword ptr [esp+30h]
        call D3DXMatrixLookAtLH
        mov edx, [esp+0Ch]
        push 461C4000h
        push 3F800000h
        push edx
        push 3EA0D97Ch
        lea ebx, [edi+8Ch]
        push ebx
        call D3DXMatrixPerspectiveFovLH
        mov eax, dword ptr [dword_491C30]
        mov ecx, [eax]
        push esi
        push 2
        push eax
        call dword ptr [ecx+0B0h]
        mov eax, dword ptr [dword_491C30]
        mov edx, [eax]
        push ebx
        push 3
        push eax
        call dword ptr [edx+0B0h]
        mov eax, dword ptr [dword_491C10]
        test eax, eax
        pop esi
        pop ebx
        jz loc_42159B
        mov ecx, [edi+0E8h]
        mov [eax+5Ch], ecx
        mov edx, [edi+0ECh]
        mov [eax+60h], edx
loc_42159B:
        add esp, 2Ch
        ret
    }
}
#endif

void Camera_Apply(CameraState* camera, const CameraHooks* hooks) {
    static const float kUp[3] = {0.0f, -1.0f, 0.0f};
    hooks->matrix_look_at_lh(hooks->context, camera->view, camera->eye,
                             camera->at, kUp);
    hooks->matrix_perspective_fov_lh(hooks->context, camera->projection,
                                     camera->fov_y, camera->aspect,
                                     camera->near_plane, camera->far_plane);
    hooks->set_transform(hooks->context, 2, camera->view);
    hooks->set_transform(hooks->context, 3, camera->projection);
    hooks->publish_clip_rect(hooks->context);
}

// Semantic reconstruction 0x0043BCD0 - apply the 640x480 viewport.
// into the caller's six-dword block, apply it, and reset clip state. The
// storage parameter replaces retail's fixed DAT_00491CF4 block.
#ifdef _MSC_VER
__declspec(naked) void Viewport_ApplyDefaultRetail() {
    __asm {
        push esi
        mov esi, dword ptr [dword_491C10]
        test esi, esi
        jz loc_43BCE0
        call sub_442F50
loc_43BCE0:
        mov eax, dword ptr [dword_491C30]
        push 491CF4h
        mov dword ptr [dword_491CF4], 0
        mov dword ptr [dword_491CF8], 0
        mov dword ptr [dword_491CFC], 280h
        mov dword ptr [dword_491D00], 1E0h
        mov dword ptr [dword_491D04], 0
        mov dword ptr [dword_491D08], 3F800000h
        mov ecx, [eax]
        push eax
        call dword ptr [ecx+0BCh]
        mov esi, [esp+8]
        call sub_43BC40
        pop esi
        ret 4
    }
}
#endif

// 0x0043BCD0 opens by flushing the staged sprite batch (0x00442F50)
// when the manager is live, then fills the six-dword block retail keeps
// at 0x00491CF4, hands it to SetViewport, and closes with 0x0043BC40.
void Viewport_ApplyDefault(ViewportBlock* storage,
                           const ViewportHooks* hooks) {
    if (hooks->flush_sprite_batch != 0)
        hooks->flush_sprite_batch(hooks->context);
    storage->x = 0;
    storage->y = 0;
    storage->width = 0x280;
    storage->height = 0x1E0;
    storage->min_z = 0.0f;
    storage->max_z = 1.0f;
    hooks->set_viewport(hooks->context, storage);
    hooks->reset_clip_state(hooks->context);
}

// 0x00448270 - Surface_CopyBackBufferToSlot: flush pending sprites, then blit
// the current back buffer into the slot texture's level-0 surface with point
// filtering. No-op when the slot has no texture.
int Surface_CopyBackBufferToSlot(int slot_has_texture,
                                 const SurfaceOpHooks* hooks) {
    if (slot_has_texture == 0)
        return -1;
    hooks->flush_sprite_batch(hooks->context);
    if (hooks->get_back_buffer(hooks->context) != 0)
        return -1;
    if (hooks->get_surface_level(hooks->context, 0) != 0)
        return -1;
    int status = hooks->copy_surface(hooks->context, 2); // D3DX_FILTER_POINT
    hooks->release_pair(hooks->context);
    return status;
}

// 0x00448450 - Surface_CreateSnapshotTargets: (re)build the pause-snapshot
// texture and the two offscreen plain surfaces sized to the back buffer,
// then seed both surfaces with the current frame.
int Surface_CreateSnapshotTargets(int slot_exists, unsigned int width,
                                  unsigned int height,
                                  const SurfaceOpHooks* hooks) {
    hooks->flush_sprite_batch(hooks->context);
    if (slot_exists != 0)
        hooks->release_existing(hooks->context, 0);
    if (hooks->get_back_buffer(hooks->context) != 0)
        return -1;
    hooks->store_dimensions(hooks->context, width, height);
    if (hooks->create_texture(hooks->context, 0, width, height) != 0)
        return -1;
    for (int slot = 0; slot < 2; ++slot) {
        if (hooks->create_plain_surface(hooks->context, slot, width,
                                        height) != 0)
            return -1;
        if (hooks->copy_surface(hooks->context, 2) != 0)
            return -1;
    }
    hooks->release_pair(hooks->context);
    return 0;
}
