#include "th10/game/pool_constructors.hpp"
#include "th10/game/entity.hpp"
#include "th10/game/floating_text_draw.hpp"
#include "th10/game/scheduler.hpp"
#include "th10/render/recovered_render_leaves.hpp"

#include <cstring>

// Retail globals that publish the constructed managers.
uint32_t* DAT_00477840;  // effect manager instance
uint32_t* DAT_0047784c;  // progress manager instance
uint32_t* DAT_0047770c;  // entity block pool instance
extern uint32_t DAT_00491be4;
extern void* g_pGameThread;
extern void __fastcall Entity_Init(void* unused, Entity* entity);
extern "C" void _free(void* memory);
extern "C" unsigned long dword_491C10;   // animation manager
extern "C" unsigned long dword_491D78;   // view flags
extern "C" unsigned long dword_492378;   // alpha-blend latch
// The 0x0042B9A0 sweep constants (retail float values from the data
// section): flt_470B0C = 0.5 (the frame-delta half-rate), flt_470AFC = 1.0
// (the ramp step), flt_470B68 = 0.99 (the ramp gate), flt_470B64 = 1.01
// (the NaN-filter sentinel - not part of the gate).
extern float DAT_00476f78;    // flt_476F78 (frame delta)
extern float _DAT_00470b0c;   // flt_470B0C
extern float _DAT_00470afc;   // flt_470AFC
extern float _DAT_00470b68;   // flt_470B68
extern float _DAT_00470b64;   // flt_470B64
extern "C" unsigned long dword_477834;   // player position

namespace {

// The retail per-glyph draw (sub_443080 within 0x0042B780) rasterizes a
// quad from the glyph's screen position, the font entry's texel
// dimensions (1/256-scaled, as 0x0043E5A0 scales them) and the record
// colour/alpha.  The recovered staging writer and the default leaves
// carry the quad to the batch; the sprite UV decode is the render
// platform's territory (the host supplies texture coordinates).
void Effect_DrawGlyph(const FloatingGlyphDraw* glyph) {
    void* manager = (void*)dword_491C10;
    if (manager == 0) return;
    void* table = *(void**)((char*)manager + 16);
    if (table == 0) return;
    const unsigned char* entry =
        *(const unsigned char**)((char*)table + 280) + 68 * glyph->glyph_index;
    const float width = *(const float*)(entry + 52) * 0.00390625f;
    const float height = *(const float*)(entry + 48) * 0.00390625f;
    const float corners[4][2] = {
        {glyph->x - width * 0.5f, glyph->y - height * 0.5f},
        {glyph->x + width * 0.5f, glyph->y - height * 0.5f},
        {glyph->x - width * 0.5f, glyph->y + height * 0.5f},
        {glyph->x + width * 0.5f, glyph->y + height * 0.5f},
    };
    const unsigned int color =
        (glyph->color & 0x00FFFFFFu) | ((unsigned int)glyph->alpha << 24);
    th10::render_leaves::AppendQuadColored(corners, color);
}

}  // namespace

// 0x0042B9A0 / 0x0042B9B0: the effect bookkeeping update and render are
// named-scope (declared in pool_constructors.hpp) so the scheduler and the
// standalone can reach them; the anonymous namespace above holds the file's
// internal helpers only.

int __fastcall EffectRuntime_Update(void* owner) {
    // Retail 0x0042B9A0 (weak fn): the effect bookkeeping sweep over the
    // 723 records at owner+0x3D4 (stride 0x40), returns 1.  Raw retail
    // record offsets: +0x00 the lifetime float, +0x08 the counter copy,
    // +0x10 the counter, +0x14 the value float, +0x18 the drive pointer,
    // +0x28 the active byte.
    //   if ([+0x28] == 0) skip;
    //   [+0x00] -= flt_476F78 * flt_470B0C;            (0.5x frame-delta)
    //   [+0x08] = counter = [+0x10];
    //   if ([+0x18][0] > flt_470B68)  { [+0x14] += flt_470AFC (1.0);
    //                                   [+0x10] = counter + 1; }
    //   else { [+0x14] += [+0x18][0]; [+0x10] = (int)[+0x14]; }
    //     (the retail's second compare against flt_470B64 (1.01) is the
    //      NaN filter for the drive value - jp on the parity flag - so the
    //      ramp gate is 0.99 only)
    //   if ([+0x10] > 0x3C) [+0x28] = 0;
    unsigned char* r = (unsigned char*)owner + 0x3D4;
    for (int i = 0; i < 723; ++i, r += 0x40) {
        if (r[0x28] == 0) continue;
        *(float*)(r + 0x00) -= DAT_00476f78 * _DAT_00470b0c;
        int counter = *(int*)(r + 0x10);
        *(int*)(r + 0x08) = counter;
        float drive = *(float*)(*(void**)(r + 0x18));
        if (drive > _DAT_00470b68) {
            *(float*)(r + 0x14) += _DAT_00470afc;
            *(int*)(r + 0x10) = counter + 1;
        } else {
            *(float*)(r + 0x14) += drive;
            *(int*)(r + 0x10) = (int)*(float*)(r + 0x14);
        }
        if (*(int*)(r + 0x10) > 0x3C) r[0x28] = 0;
    }
    return 1;
}

int __fastcall EffectRuntime_Render(void* owner) {
    // Retail 0x0042B9B0: `return sub_42B780(this)` - the effect bookkeeping
    // render edge is the floating-text pass over the 723 records at +964,
    // with the retail globals supplying the draw environment (view flags
    // 0x00491D78, the alpha-blend latch 0x00492378, the player position
    // 0x00477834[240/241]).  The per-glyph rasterization and the batch
    // reopen route through the recovered render chain (the reverse-glyph
    // pass 0x0042B780, the batch flush 0x00442F50, the quad staging append
    // at 0x00442FE0 and the quad builder at 0x00443080) via the shared
    // leaves; all four addresses are prose references, not impl headers.
    FloatingTextEnv env;
    env.view_flags = (unsigned int)dword_491D78;
    env.alpha_blend_state = (int*)&dword_492378;
    env.player_position[0] = ((const float*)dword_477834)[240];
    env.player_position[1] = ((const float*)dword_477834)[241];
    env.disable_alpha_blend = th10::render_leaves::FlushQuadBatch;
    env.draw_glyph = Effect_DrawGlyph;
    return TextBatch_DrawReverseGlyphs(
        (const FloatingTextRecord*)((char*)owner + 964), &env);
}

// 0x0043E5A0 - Preload an effect resource bank. The retail call shape is
// (owner record, slot index, bank): the slot record inside the bank is
// resolved and its texture dimensions are pulled into the owner, the
// 4x4 identity scale rows at +572 and +700 are installed (retail store
// order), and the width/height entries are scaled by 1/256 before the
// first row block is mirrored to +636.
int EffectRuntime_Preload(void* owner, int slot, void* bank) {
    // The standalone has no retail animation-manager bank. Keep this
    // external resource edge defined without fabricating bank storage.
    if (owner == 0 || bank == 0)
        return -1;
    unsigned char* bytes = (unsigned char*)owner;
    uint32_t* bank32 = (uint32_t*)bank;
    if (bank32[66] == 0 || bank32[73] != 0)
        return -1;
    *(uint16_t*)(bytes + 900) = (uint16_t)slot;
    *(uint32_t*)(bytes + 776) = (uint32_t)(uintptr_t)bank;
    uint32_t* record =
        (uint32_t*)(uintptr_t)(bank32[70] + 68u * (unsigned)slot);
    *(uint32_t*)(bytes + 916) = (uint32_t)(uintptr_t)record;
    *(uint32_t*)(bytes + 76) = record[13];  // slot record + 52
    *(uint32_t*)(bytes + 80) = record[12];  // slot record + 48
    // Identity scale rows at +572 and +700 (retail store order).
    *(uint32_t*)(bytes + 628) = 0;
    *(uint32_t*)(bytes + 624) = 0;
    *(uint32_t*)(bytes + 620) = 0;
    *(uint32_t*)(bytes + 616) = 0;
    *(uint32_t*)(bytes + 608) = 0;
    *(uint32_t*)(bytes + 604) = 0;
    *(uint32_t*)(bytes + 600) = 0;
    *(uint32_t*)(bytes + 596) = 0;
    *(uint32_t*)(bytes + 588) = 0;
    *(uint32_t*)(bytes + 584) = 0;
    *(uint32_t*)(bytes + 580) = 0;
    *(uint32_t*)(bytes + 576) = 0;
    *(uint32_t*)(bytes + 632) = 0x3F800000u;  // 1.0f
    *(uint32_t*)(bytes + 612) = 0x3F800000u;  // 1.0f
    *(uint32_t*)(bytes + 592) = 0x3F800000u;  // 1.0f
    *(uint32_t*)(bytes + 572) = 0x3F800000u;  // 1.0f
    *(uint32_t*)(bytes + 756) = 0;
    *(uint32_t*)(bytes + 752) = 0;
    *(uint32_t*)(bytes + 748) = 0;
    *(uint32_t*)(bytes + 744) = 0;
    *(uint32_t*)(bytes + 736) = 0;
    *(uint32_t*)(bytes + 732) = 0;
    *(uint32_t*)(bytes + 728) = 0;
    *(uint32_t*)(bytes + 724) = 0;
    *(uint32_t*)(bytes + 716) = 0;
    *(uint32_t*)(bytes + 712) = 0;
    *(uint32_t*)(bytes + 708) = 0;
    *(uint32_t*)(bytes + 704) = 0;
    *(uint32_t*)(bytes + 760) = 0x3F800000u;  // 1.0f
    *(uint32_t*)(bytes + 740) = 0x3F800000u;  // 1.0f
    *(uint32_t*)(bytes + 720) = 0x3F800000u;  // 1.0f
    *(uint32_t*)(bytes + 700) = 0x3F800000u;  // 1.0f
    float* v4 = (float*)record;
    *(float*)(bytes + 572) = *(float*)(bytes + 76) * 0.00390625f;
    *(float*)(bytes + 592) = *(float*)(bytes + 80) * 0.00390625f;
    *(float*)(bytes + 700) = v4[14] / v4[7] * *(float*)(bytes + 76);
    const float v5 = v4[15] / v4[6];
    memcpy(bytes + 636, bytes + 572, 0x40);
    *(float*)(bytes + 720) = v5 * *(float*)(bytes + 80);
    return 0;
}

// All three retail constructors share the same shape: a prologue of
// per-slot stores (sentinel bit clears, per-channel defaults, vtable
// pointers), followed by a full zero wipe of the whole block that makes
// every prologue store dead, then the constructed bit and the global
// publish. The readable forms keep only the observable effects and
// document the dead prologue.

// 0x0042B430 - Reset the effect manager. The retail prologue clears the
// in-use bit of nine embedded timer sentinels, wipes one 0x3AC-byte
// scratch record at +0x18 (with a 0xFFFF terminator half-word), and
// clears the in-use bit of 0x2D3 0x40-byte slots at +0x3F0 -- all dead
// stores, because the function then zeroes all 0x2E21 words. Bit 1 of
// the leading flags word marks the manager constructed and the instance
// is published through 0x00477840.
void EffectManager_ResetAndPublish(uint32_t* state) {
    memset(state, 0, kEffectManagerDwords * sizeof(uint32_t));
    state[0] |= 2u;
    DAT_00477840 = state;
}

// 0x0042B4D0 - Stamp the manager, install its callback pair, initialize the
// embedded entity/timer record, and preload effect bank 0xC4.
int EffectManagerRuntime_Initialize(void* state) {
    if (state == 0 || DAT_00491be4 == 0)
        return -1;
    unsigned char* bytes = (unsigned char*)state;
    const int stamp = g_pGameThread != 0
        ? *(int*)((unsigned char*)g_pGameThread + 0x8994) : 0;
    *(int*)(bytes + 0x10) = stamp;

    SchedulerCallback* update =
        SchedulerCallback_Create(EffectRuntime_Update);
    if (update == 0)
        return -1;
    update->flags &= ~2u;
    update->owner = state;
    Scheduler_RegisterPrimary(update, 0, (void*)(uintptr_t)DAT_00491be4);
    *(SchedulerCallback**)(bytes + 8) = update;

    SchedulerCallback* render =
        SchedulerCallback_Create(EffectRuntime_Render);
    if (render == 0) {
        Scheduler_Remove(update, (void*)(uintptr_t)DAT_00491be4);
        *(SchedulerCallback**)(bytes + 8) = 0;
        return -1;
    }
    render->flags &= ~2u;
    render->owner = state;
    Scheduler_RegisterSecondary(render, 0, (void*)(uintptr_t)DAT_00491be4);
    *(SchedulerCallback**)(bytes + 12) = render;
    Entity_Init(0, (Entity*)(bytes + 0x18));
    *(int*)(bytes + 0x320) = stamp;
    // Retail tail-calls sub_43E5A0(record, 0xC4, bank) with the embedded
    // record at +0x18 and the bank value copied into +0x10. The tail
    // call is unconditional; the wrapper defaults to the faithful body.
    EffectRuntime_Preload(bytes + 0x18, 0xC4, (void*)(uintptr_t)stamp);
    return 0;
}

void EffectManagerRuntime_Destroy(void* state) {
    if (state == 0)
        return;
    unsigned char* bytes = (unsigned char*)state;
    SchedulerCallback** update = (SchedulerCallback**)(bytes + 8);
    SchedulerCallback** render = (SchedulerCallback**)(bytes + 12);
    if (DAT_00491be4 != 0) {
        if (*update != 0)
            Scheduler_Remove(*update, (void*)(uintptr_t)DAT_00491be4);
        if (*render != 0)
            Scheduler_Remove(*render, (void*)(uintptr_t)DAT_00491be4);
    }
    *update = 0;
    *render = 0;
    DAT_00477840 = 0;
    void** buffer = (void**)(bytes + 0x370);
    if (*buffer != 0)
        _free(*buffer);
    *buffer = 0;
}

// 0x0042C920 - Construct the progress manager. The retail prologue
// installs two vtable pointers and seeds four gauge channels with the
// {enabled = 1, limit = 999} defaults before the full 0x16B3-word wipe
// discards them. Bit 1 of the flags word at +0x04 marks the manager
// constructed and the instance is published through 0x0047784C.
uint32_t* ProgressManager_ConstructAndPublish(uint32_t* state) {
    memset(state, 0, kProgressManagerDwords * sizeof(uint32_t));
    state[1] |= 2u;
    DAT_0047784c = state;
    return state;
}

// 0x00413810 - Construct the entity block pool. Retail runs
// _eh_vector_constructor_iterator_ over six embedded arrays of
// 0x3AC-byte entities (10, 10, 9, 4, 2, and 7 elements at word offsets
// 4, 0x932, 0x1260, 0x1AA3, 0x1E4F, and 0x2025), then performs the same
// clear-and-publish tail as the other pool constructors: the sentinel
// bit clears and the 0x3AC-byte scratch wipe at +0x9A48 are dead
// because the whole 0x27B4-word block is zeroed afterwards. Bit 1 of
// the leading flags word marks the pool constructed and the instance is
// published through 0x0047770C.
uint32_t* EntityBlockPool_ConstructAndPublish(
        uint32_t* state, void (*construct_entity)(void*)) {
    static const struct {
        uint32_t word_offset;
        uint32_t count;
    } kArrays[6] = {
        {0x0004, 10}, {0x0932, 10}, {0x1260, 9},
        {0x1AA3, 4},  {0x1E4F, 2},  {0x2025, 7},
    };
    const uint32_t kEntityDwords = 0x3AC / 4;
    if (construct_entity != 0) {
        for (int range = 0; range < 6; ++range) {
            for (uint32_t index = 0; index < kArrays[range].count; ++index) {
                construct_entity(state + kArrays[range].word_offset +
                                 index * kEntityDwords);
            }
        }
    }
    memset(state, 0, kEntityBlockPoolDwords * sizeof(uint32_t));
    state[0] |= 2u;
    DAT_0047770c = state;
    return state;
}
