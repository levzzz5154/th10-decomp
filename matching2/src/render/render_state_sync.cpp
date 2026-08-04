#include "th10/render/render_state_sync.hpp"

#ifdef _MSC_VER
extern "C" void sub_442F50(void);
extern "C" void* dword_491C30;
#endif

// 0x004425A0 - Synchronize the device render state with an entity's
// flag word. Retail keeps the manager in EAX and the entity in EDI and
// calls the device vtable directly (SetRenderState at +0xE4,
// SetSamplerState at +0x114); both are injected here together with the
// staged-geometry flush (0x00442F50).
#ifdef _MSC_VER
__declspec(naked) void AnmManager_SyncEntityRenderStateRetail() {
    __asm {
        push esi
        mov esi, eax
        mov eax, [edi+35Ch]
        mov cl, [esi+3ADA68h]
        shr eax, 4
        and eax, 3
        cmp cl, al
        jz loc_442600
        call sub_442F50
        mov eax, [edi+35Ch]
        shr eax, 4
        and al, 3
        mov [esi+3ADA68h], al
        movzx eax, al
        sub eax, 0
        jz loc_4425EE
        dec eax
        jnz loc_442600
        mov eax, dword ptr [dword_491C30]
        mov ecx, [eax]
        push 2
        push 14h
        push eax
        call dword ptr [ecx+0E4h]
        jmp loc_442600
loc_4425EE:
        mov eax, dword ptr [dword_491C30]
        mov edx, [eax]
        push 6
        push 14h
        push eax
        call dword ptr [edx+0E4h]
loc_442600:
        mov eax, [edi+35Ch]
        mov cl, [esi+3ADA6Eh]
        shr eax, 1Fh
        cmp cl, al
        jz loc_442664
        call sub_442F50
        mov eax, [edi+35Ch]
        shr eax, 1Fh
        and al, 1
        mov [esi+3ADA6Eh], al
        mov eax, dword ptr [dword_491C30]
        mov ecx, [eax]
        jnz loc_442643
        push 2
        push 5
        push 0
        push eax
        call dword ptr [ecx+114h]
        push 2
        jmp loc_442652
loc_442643:
        push 1
        push 5
        push 0
        push eax
        call dword ptr [ecx+114h]
        push 1
loc_442652:
        mov eax, dword ptr [dword_491C30]
        mov edx, [eax]
        push 6
        push 0
        push eax
        call dword ptr [edx+114h]
loc_442664:
        inc dword ptr [esi+54h]
        pop esi
        ret
    }
}
#endif

void AnmManager_SyncEntityRenderState(
        RenderStateCache* cache, uint32_t entity_flags, void (*flush)(),
        void (*set_render_state)(uint32_t state_id, uint32_t value),
        void (*set_sampler_state)(uint32_t stage, uint32_t state_id,
                                  uint32_t value)) {
    const uint8_t blend = (uint8_t)((entity_flags >> 4) & 3u);
    if (cache->blend_mode != blend) {
        if (flush != 0) {
            flush();
        }
        cache->blend_mode = blend;
        if (blend == 0) {
            set_render_state(0x14, 6);
        } else if (blend == 1) {
            set_render_state(0x14, 2);
        }
    }

    const int8_t filter = (int8_t)((entity_flags & 0x80000000u) != 0 ? 1 : 0);
    if (cache->filter_mode != filter) {
        if (flush != 0) {
            flush();
        }
        cache->filter_mode = filter;
        const uint32_t value = filter == 0 ? 2u : 1u;
        set_sampler_state(0, 5, value);
        set_sampler_state(0, 6, value);
    }

    cache->sync_counter += 1;
}
