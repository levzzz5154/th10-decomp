#include "th10/game/effect_indicator_queue.hpp"
#include "th10/game/scheduler.hpp"
#include "th10/game/stage_focus_fade.hpp"
#include "th10/game/stage_tips.hpp"
#include "th10/runtime/missing_edge.hpp"

#ifdef _MSC_VER
#include "th10/msvc_stdint.hpp"
#endif

#ifdef _MSC_VER
extern "C" int dword_474C7C;
extern "C" void* sub_41A120(void*, void*, void*);
extern "C" void* sub_452493(unsigned long);
extern "C" char* _strncpy(char*, const char*, unsigned int);
extern "C" int dword_474C84;
extern "C" int dword_474C88;
extern "C" int dword_474C8C;
extern "C" void* sub_449ED0(void*);
extern "C" int sub_449AE0(void*, int, void*);
extern "C" int sub_449B70(void*, int, void*);
extern "C" int sub_419960(void*, const char*, int);
#endif

#include <new>

#ifndef _MSC_VER
#include <cstring>
#else
extern "C" void* memset(void*, int, unsigned long);
#endif

// Stage-tip manager global declared in retail at 0x00477814.
StageTipManager* DAT_00477814;

// Difficulty globals shared with the tip-creation path.
extern int32_t DAT_00474c7c;  // difficulty setting
extern int32_t DAT_00474c84;  // tip display mode
extern int32_t DAT_00474c88;  // display value used while mode == 0
extern int32_t DAT_00474c8c;  // display value used while mode != 0
extern uint32_t DAT_00491be4;
extern uint8_t DAT_00491d6a;
// Player block published at retail 0x00477834; the focus-fade update reads
// the position floats at +0x3C0/+0x3C4 as the camera anchor. The standalone
// host never publishes the block, so the host path treats it as optional.
extern uint32_t* DAT_00477834;

namespace {
StageTipRuntimeBindings g_stage_tip_bindings = {};

// 0x00419650 - The stage-tip update edge doubles as the stage-focus fade
// driver. The retail body resets the secondary counter when the display
// mode (dword_474C84) differs from the manager's +0xD8 snapshot, expires
// the current difficulty's queued chain through 0x00419120, then walks ten
// focus slots scattered through the manager tail (+0xDC handles, +0x104
// x/y/z triples, +0x17C half-widths), resolving each handle through the
// animation manager's world/UI lists (dword_491C10 + 0x72DAD4 / +0x72DADC)
// and fading the matched entity's alpha around the player camera.
#ifdef _MSC_VER
int __fastcall StageTipRuntime_Update(void* owner) {
    if (g_stage_tip_bindings.update == 0)
        Runtime_MissingEdge(0x00419650u, "stage-tip/focus update");
    return g_stage_tip_bindings.update(owner);
}
#else
// Copy one retail focus slot (scattered manager tail fields) into the
// compact StageFocusSlot layout the recovery consumes.
static void FocusSlotLoad(StageFocusSlot* slot, const unsigned char* bytes,
                          int index) {
    slot->handle = *(const uint32_t*)(bytes + 0xDC + 4 * index);
    slot->x = *(const float*)(bytes + 0x104 + 12 * index);
    slot->y = *(const float*)(bytes + 0x108 + 12 * index);
    slot->z = *(const float*)(bytes + 0x10C + 12 * index);
    slot->half_width = *(const float*)(bytes + 0x17C + 4 * index);
}

// Write the recovery's slot back into the manager's retail field layout.
static void FocusSlotStore(const StageFocusSlot* slot, unsigned char* bytes,
                           int index) {
    *(uint32_t*)(bytes + 0xDC + 4 * index) = slot->handle;
    *(float*)(bytes + 0x104 + 12 * index) = slot->x;
    *(float*)(bytes + 0x108 + 12 * index) = slot->y;
    *(float*)(bytes + 0x10C + 12 * index) = slot->z;
    *(float*)(bytes + 0x17C + 4 * index) = slot->half_width;
}

int __fastcall StageTipRuntime_Update(void* owner) {
    // Host path: drive the recovered StageFocus_UpdateFade over the
    // manager's retail focus-slot fields. The retail reads the player
    // position at DAT_00477834 +0x3C0/+0x3C4 and the recovery adds the
    // +224/+16 camera offsets internally, so the env carries the raw
    // floats; the standalone host never publishes the player block, so a
    // missing block reads as the origin.
    unsigned char* bytes = reinterpret_cast<unsigned char*>(owner);
    StageFocusState state;
    state.frame = *(const uint32_t*)(bytes + 0x10);
    state.secondary_frame = *(const uint32_t*)(bytes + 0x14);
    state.stage_id = *(const int32_t*)(bytes + 0xD8);
    // Retail keeps the manager self-pointer at +0x0C (set by 0x00418D40);
    // the recovery only forwards it to the (unwired) prepare callback.
    state.selected = owner;
    for (int index = 0; index < 10; ++index) {
        FocusSlotLoad(&state.slots[index], bytes, index);
    }

    StageFocusEnv env;
    env.current_stage_id = DAT_00474c84;  // retail dword_474C84 comparison
    const unsigned char* player =
        reinterpret_cast<const unsigned char*>(DAT_00477834);
    env.camera_x = player != 0 ? *(const float*)(player + 0x3C0) : 0.0f;
    env.camera_y = player != 0 ? *(const float*)(player + 0x3C4) : 0.0f;
    // Retail resolves each slot handle through the animation manager's
    // world/UI lists (dword_491C10 + 0x72DAD4 / +0x72DADC); the env has no
    // name-list lookup, so empty lists reproduce retail's not-found path,
    // which clears the slot handle. Retail's 0x00419120 chain-head expiry
    // (env.prepare) is not recovered - TODO.
    env.active = 0;
    env.pending = 0;
    env.prepare = 0;

    int result = StageFocus_UpdateFade(&state, &env);

    // The manager is the persistent store: write back the counters and the
    // ten slots (the recovery clears handles whose entity is not found).
    *(uint32_t*)(bytes + 0x10) = state.frame;
    *(uint32_t*)(bytes + 0x14) = state.secondary_frame;
    *(int32_t*)(bytes + 0xD8) = state.stage_id;
    for (int index = 0; index < 10; ++index) {
        FocusSlotStore(&state.slots[index], bytes, index);
    }
    return result;
}
#endif

// Retail 0x004198B0: the stage-tip render edge.  The entire body is
// `mov eax, 1; retn` - the listing shows no other effect.
int __fastcall StageTipRuntime_Render(void* owner) {
    (void)owner;
    return 1;
}

void StageTipRuntime_SpawnTip(void* owner, uint32_t text_address,
                              int32_t slot) {
#ifdef _MSC_VER
    if (g_stage_tip_bindings.spawn_tip == 0)
        Runtime_MissingEdge(0x0041A120u, "stage-tip spawn");
    g_stage_tip_bindings.spawn_tip(owner, text_address, slot);
#else
    // Host path: retail 0x0041A120 is the record allocation + chain
    // append modelled by StageTip_Create below (the same body, with the
    // allocator injected); the wrapper's position argument is not
    // carried by the host call sites, so the record spawns at 0 and the
    // slot selects nothing on this path (the built-in tips rely on the
    // display-mode globals StageTip_Create already reads).
    (void)slot;
    static const float origin[3] = {0.0f, 0.0f, 0.0f};
    StageTip_Create((StageTipManager*)owner, origin,
                    (const char*)(uintptr_t)text_address,
                    +[](uint32_t size) { return ::operator new(size); });
#endif
}
}  // namespace

// strncpy with the exact retail semantics (copy up to ``limit`` bytes,
// zero-fill the remainder, no forced terminator), written out so the
// host build does not depend on the CRT's truncation diagnostics.
static void CopyTipText(char* destination, const char* source,
                        unsigned int limit) {
    unsigned int index = 0;
    for (; index < limit && source[index] != 0; ++index) {
        destination[index] = source[index];
    }
    for (; index < limit; ++index) {
        destination[index] = 0;
    }
}

// 0x00418D40 - Construct the 0x1A8-byte stage-tip manager: clear the
// whole state, set constructed bit 1 in the flags word, point all
// sixteen intrusive list sentinels back at the manager with empty
// next/previous links, and publish the instance through the retail
// global at 0x00477814.
#ifdef _MSC_VER
__declspec(naked) StageTipManager* StageTipManager_Construct(
        StageTipManager* state) {
    __asm {
        xor eax, eax
        push edi
        mov ecx, 6Ah
        mov edi, edx
        rep stosd
        or dword ptr [edx], 2
        mov [edx+18h], edx
        mov [edx+24h], edx
        xor eax, eax
        mov [edx+1Ch], eax
        mov [edx+20h], eax
        mov [edx+28h], eax
        mov [edx+2Ch], eax
        mov [edx+30h], edx
        mov [edx+34h], eax
        mov [edx+38h], eax
        mov [edx+3Ch], edx
        mov [edx+40h], eax
        mov [edx+44h], eax
        mov [edx+48h], edx
        mov [edx+4Ch], eax
        mov [edx+50h], eax
        mov [edx+54h], edx
        mov [edx+58h], eax
        mov [edx+5Ch], eax
        mov [edx+60h], edx
        mov [edx+64h], eax
        mov [edx+68h], eax
        mov [edx+6Ch], edx
        mov [edx+70h], eax
        mov [edx+74h], eax
        mov [edx+78h], edx
        mov [edx+84h], edx
        mov [edx+7Ch], eax
        mov [edx+80h], eax
        mov [edx+88h], eax
        mov [edx+8Ch], eax
        mov [edx+90h], edx
        mov [edx+94h], eax
        mov [edx+98h], eax
        mov [edx+9Ch], edx
        mov [edx+0A0h], eax
        mov [edx+0A4h], eax
        mov [edx+0A8h], edx
        mov [edx+0ACh], eax
        mov [edx+0B0h], eax
        mov [edx+0B4h], edx
        mov [edx+0B8h], eax
        mov [edx+0BCh], eax
        mov [edx+0C0h], edx
        mov [edx+0C4h], eax
        mov [edx+0C8h], eax
        mov [edx+0CCh], edx
        mov [edx+0D0h], eax
        mov [edx+0D4h], eax
        mov [DAT_00477814], edx
        mov eax, edx
        pop edi
        ret
    }
}
#else
StageTipManager* StageTipManager_Construct(StageTipManager* state) {
    memset(state, 0, sizeof(*state));
    state->flags |= 2u;
    for (int index = 0; index < 16; ++index) {
        state->lists[index].owner = (StageTip*)state;
        state->lists[index].next = 0;
        state->lists[index].previous = 0;
    }
    DAT_00477814 = state;
    return state;
}
#endif

void StageTipRuntime_SetBindings(const StageTipRuntimeBindings* bindings) {
    if (bindings != 0)
        g_stage_tip_bindings = *bindings;
    else
        memset(&g_stage_tip_bindings, 0, sizeof(g_stage_tip_bindings));
}

// 0x00418E30 - Register the manager's update/render pair, clear its counter,
// and create the two built-in tips when the retail tips option is enabled.
#ifdef _MSC_VER
__declspec(naked) int StageTipRuntime_InitializeRetail() {
    __asm {
        push esi
        push edi
        push 4198A0h
        call sub_449ED0
        mov esi, eax
        mov edx, [esi+4]
        mov eax, dword ptr [DAT_00491be4]
        and edx, 0FFFFFFFDh
        push eax
        mov edi, 19h
        mov [esi+20h], ebx
        mov [esi+4], edx
        call sub_449AE0
        push 4198B0h
        mov [ebx+8], esi
        call sub_449ED0
        mov ecx, dword ptr [DAT_00491be4]
        mov esi, eax
        and dword ptr [esi+4], 0FFFFFFFDh
        push ecx
        mov edi, 2Ch
        mov [esi+20h], ebx
        call sub_449B70
        mov [ebx+0Ch], esi
        mov dword ptr [ebx+10h], 0
        mov al, byte ptr [DAT_00491d6a]
        test al, al
        pop edi
        pop esi
        jz loc_418EB0
        push 0
        push 46D6D8h
        push ebx
        call sub_419960
        push 1
        push 46D6C4h
        push ebx
        call sub_419960
loc_418EB0:
        xor eax, eax
        ret
    }
}
#endif

int StageTipRuntime_Initialize(void* state) {
    if (state == 0 || DAT_00491be4 == 0)
        return -1;
    unsigned char* bytes = (unsigned char*)state;
    SchedulerCallback* update =
        SchedulerCallback_Create(StageTipRuntime_Update);
    if (update == 0)
        return -1;
    update->flags &= ~2u;
    update->owner = state;
    Scheduler_RegisterPrimary(update, 0, (void*)(uintptr_t)DAT_00491be4);
    *(SchedulerCallback**)(bytes + 8) = update;

    SchedulerCallback* render =
        SchedulerCallback_Create(StageTipRuntime_Render);
    if (render == 0) {
        Scheduler_Remove(update, (void*)(uintptr_t)DAT_00491be4);
        *(SchedulerCallback**)(bytes + 8) = 0;
        return -1;
    }
    render->flags &= ~2u;
    render->owner = state;
    Scheduler_RegisterSecondary(render, 0, (void*)(uintptr_t)DAT_00491be4);
    *(SchedulerCallback**)(bytes + 12) = render;
    *(uint32_t*)(bytes + 0x10) = 0;

    // Retail gates the two startup tips on the display flag only; the spawn
    // edge itself is mandatory, so a missing binding is a build error rather
    // than a silently skipped pair.
    if (DAT_00491d6a != 0) {
        StageTipRuntime_SpawnTip(state, 0x0046D6D8u, 0);
        StageTipRuntime_SpawnTip(state, 0x0046D6C4u, 1);
    }
    return 0;
}

// 0x0041A120 - Allocate one 0x88-byte stage-tip record, run the same
// initialization as StageTip_Initialize (0x00418D00), append the tip to
// the tail of the current difficulty's chain, and fill in position,
// text, and the display fields selected by the difficulty globals.
//
// Retail ABI: the record's position vector arrives in EBX and the
// allocation goes through the statically linked operator new; the
// readable signature reifies the position and injects the allocator.
// Retail addresses the list head as manager + (DAT_00474C7C * 3 + 0x1E)
// 32-bit words, i.e. sentinel 8 + difficulty of the manager's sixteen
// list heads (+0x78 onward).
//
// Retail never observes an allocation failure (its statically linked
// allocator aborts), so the readable form returns null early instead of
// linking a null record.
#ifdef _MSC_VER
__declspec(naked) StageTip* StageTip_CreateRetail() {
    __asm {
        push esi
        push 88h
        call sub_452493
        mov edx, eax
        add esp, 4
        test edx, edx
        jz loc_41A168
        push edi
        xor eax, eax
        mov ecx, 22h
        mov edi, edx
        rep stosd
        mov [edx+10h], eax
        mov [edx+14h], eax
        mov [edx+0Ch], edx
        or eax, 0FFFFFFFFh
        mov [edx+84h], eax
        mov dword ptr [edx+6Ch], 12Ch
        mov dword ptr [edx+7Ch], 3F800000h
        mov [edx+70h], eax
        mov esi, edx
        pop edi
        jmp loc_41A16A
loc_41A168:
        xor esi, esi
loc_41A16A:
        mov eax, dword ptr [dword_474C7C]
        mov edx, [esp+8]
        lea eax, [eax+eax*2+1Eh]
        lea eax, [edx+eax*4]
        mov edx, [eax+4]
        test edx, edx
        lea ecx, [esi+0Ch]
        jz loc_41A18E
loc_41A184:
        mov eax, [eax+4]
        mov edx, [eax+4]
        test edx, edx
        jnz loc_41A184
loc_41A18E:
        mov edx, [eax+4]
        test edx, edx
        jz loc_41A19E
        mov [ecx+4], edx
        mov edx, [eax+4]
        mov [edx+8], ecx
loc_41A19E:
        mov [eax+4], ecx
        mov [ecx+8], eax
        mov dword ptr [esi+70h], 1Eh
        mov ecx, [ebx]
        mov eax, esi
        mov [eax], ecx
        mov edx, [ebx+4]
        mov [eax+4], edx
        mov ecx, [ebx+8]
        mov edx, [esp+0Ch]
        push 40h
        mov [eax+8], ecx
        push edx
        lea eax, [esi+1Ch]
        push eax
        call _strncpy
        mov dword ptr [esi+64h], 0
        mov ecx, dword ptr [dword_474C84]
        mov [esi+68h], ecx
        mov eax, dword ptr [dword_474C84]
        add esp, 0Ch
        test eax, eax
        mov eax, dword ptr [dword_474C8C]
        jnz loc_41A1F3
        mov eax, dword ptr [dword_474C88]
loc_41A1F3:
        mov [esi+60h], eax
        mov eax, esi
        pop esi
        ret 8
    }
}
#endif

StageTip* StageTip_Create(StageTipManager* manager, const float position[3],
                          const char* text, void* (*allocate)(uint32_t)) {
    // Retail allocates the 0x88-byte record; the host struct carries
    // host-side tail members, so the allocation must match sizeof.
    StageTip* tip = allocate != 0 ? (StageTip*)allocate(sizeof(StageTip)) : 0;
    if (tip == 0) {
        return 0;
    }

    // Inlined retail body of StageTip_Initialize (0x00418D00).
    memset(tip, 0, sizeof(StageTip));
    tip->node.next = 0;
    tip->node.previous = 0;
    tip->node.owner = tip;
    tip->state = -1;
    tip->selection = -1;
    tip->duration = 300;
    tip->scale = 1.0f;

    // Walk to the tail of the current difficulty's chain and append.
    StageTipNode* tail = &manager->lists[8 + DAT_00474c7c];
    while (tail->next != 0) {
        tail = tail->next;
    }
    tail->next = &tip->node;
    tip->node.previous = tail;

    tip->selection = 0x1E;
    tip->x = position[0];
    tip->y = position[1];
    tip->z = position[2];
    CopyTipText(tip->name, text, 0x40);
    tip->display_zero = 0;
    tip->display_mode = DAT_00474c84;
    tip->display_value = DAT_00474c84 == 0 ? DAT_00474c88 : DAT_00474c8c;
    return tip;
}

// 0x00424650 - Age every selected tip in the current difficulty chain, create
// a replacement through the common 0x0041A120 path, shorten its lifetime by
// sixty frames with a one-frame floor, and install the highlighted style.
#ifdef _MSC_VER
__declspec(naked) StageTip* StageTip_CreateUrgent(
        StageTipManager* manager, const float position[3], const char* text,
        void* (*allocate)(uint32_t)) {
    __asm {
        mov eax, dword_474C7C
        lea eax, [eax+eax*2]
        mov eax, [esi+eax*4+7Ch]
        test eax, eax
        je spawn
age_loop:
        mov edx, [eax+4]
        mov eax, [eax]
        mov ecx, [eax+70h]
        test ecx, ecx
        jle next
        dec ecx
        mov [eax+70h], ecx
next:
        test edx, edx
        mov eax, edx
        jne age_loop
spawn:
        mov ecx, [esp+4]
        push ebx
        mov ebx, [esp+0Ch]
        push ecx
        push esi
        call sub_41A120
        mov edx, [eax+60h]
        add edx, 0FFFFFFC4h
        mov ecx, edx
        test ecx, ecx
        mov [eax+60h], edx
        pop ebx
        jg set_fields
        mov dword ptr [eax+60h], 1
set_fields:
        mov dword ptr [eax+6Ch], 5Ah
        mov dword ptr [eax+84h], 0FFFF8080h
        mov dword ptr [eax+70h], 1Eh
        ret 8
    }
}
#else
StageTip* StageTip_CreateUrgent(StageTipManager* manager,
                                const float position[3], const char* text,
                                void* (*allocate)(uint32_t)) {
    StageTipNode* node = manager->lists[8 + DAT_00474c7c].next;
    while (node != 0) {
        if (node->owner->selection > 0) {
            --node->owner->selection;
        }
        node = node->next;
    }

    StageTip* tip = StageTip_Create(manager, position, text, allocate);
    if (tip == 0) {
        return 0;
    }
    tip->duration -= 60;
    if (tip->duration < 1) {
        tip->duration = 1;
    }
    tip->display_mode = 90;
    tip->state = static_cast<int32_t>(0xffff8080u);
    tip->selection = 30;
    return tip;
}
#endif
