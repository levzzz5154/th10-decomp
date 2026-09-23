// Semantic model for 0x00422AB0..0x00422C2D. This initializes the pause-menu
// state and its two animation handles. State members whose meaning is not
// established by the caller/callee evidence keep their numeric offsets.

#include "asm_symbols.hpp"

#include "th10/game/entity.hpp"
#include "th10/platform/sound_queue.hpp"

typedef unsigned int uint32_00422ab0;

struct PauseMenuState_00422ab0 {
    unsigned char unknown_000[4];
    uint32_00422ab0 offset_004;
    unsigned char unknown_008[8];
    uint32_00422ab0 offset_010;
    uint32_00422ab0 offset_014;
    uint32_00422ab0 offset_018;
    uint32_00422ab0 offset_01c;
    uint32_00422ab0 flags_020;
    unsigned char unknown_024[0x1b0];
    uint32_00422ab0 offset_1d4;
    uint32_00422ab0 offset_1d8;
    unsigned char unknown_1dc[0xe4];
    uint32_00422ab0 offset_2c0;
    uint32_00422ab0 offset_2c4;
};

// This is the same pool view used by the semantic 0x00449950 implementation.
// A focused native-LTCG context has shown that this ordinary member-call form
// can lower with the manager in ESI when Allocate's definition is visible to
// the optimizer (see the allocator recovery note). The full 0x00422AB0 caller
// context still needs an integration-level check.
struct AnimationPool {
    char header[0x68];
    Entity objects[4096];
    unsigned char occupied[4096];
    int next_slot;
    __declspec(noinline) Entity* Allocate();
};

struct AnimationLookupEntry {
    AnimationLookupEntry* object;
    AnimationLookupEntry* next;
    unsigned char reserved_008[0x0c];
    AnimationLookupEntry* children;
    int children_flagged;
    unsigned char reserved_01c[0x340];
    uint32_00422ab0 flags_35c;
};

struct AnimationLookupContext {
    unsigned char reserved_000[0x72dad4];
    AnimationLookupEntry* primary_bucket_72dad4;
    uint32_00422ab0 unknown_72dad8;
    AnimationLookupEntry* secondary_bucket_72dadc;
};

struct AnimationManager {
    __declspec(noinline) void* __fastcall SetFlag(
        AnimationLookupContext* context, int id);
};

struct AnimationHandle {
    uint32_00422ab0 value;
    __declspec(noinline) void StopAtFrame2();
    __declspec(noinline) void StopAtFrame3();
};

struct AnimationBackLink_00422ab0 {
    void* object;
    AnimationBackLink_00422ab0* next;
    AnimationBackLink_00422ab0* previous;
};

struct AnimationChildLink_00422ab0 {
    void* object;
    AnimationChildLink_00422ab0* next;
};

typedef void (__thiscall *InitializeAnimation_00422ab0)(
    void* resource, void* object, int script_index);

// Source-only semantic model of the 0x00424480 work. Its ordinary signature
// takes the retail ESI receiver explicitly; it is not an ABI-compatible call
// to the retail entry, which remains assembly for other callers.
extern "C" int UpdateSpriteDescriptorModel_00424480(
    void* descriptor, int handle, int value_08, int value_0C,
    int value_10, int value_14);

extern "C" unsigned char data_00476f78;
extern "C" unsigned char data_004776e0;
extern "C" unsigned char data_0047770c;
extern "C" unsigned char data_00477810;
extern "C" unsigned char data_00491c10;

static void* FindAnimationByHandle_00422ab0(
    AnimationLookupContext* context, uint32_00422ab0 handle) {
    if (handle == 0)
        return 0;

    AnimationLookupEntry* bucket = context->primary_bucket_72dad4;
    while (bucket != 0) {
        void* object = bucket->object;
        if (*reinterpret_cast<uint32_00422ab0*>(object) == handle)
            return object;
        bucket = bucket->next;
    }

    bucket = context->secondary_bucket_72dadc;
    while (bucket != 0) {
        void* object = bucket->object;
        if (*reinterpret_cast<uint32_00422ab0*>(object) == handle)
            return object;
        bucket = bucket->next;
    }
    return 0;
}

// Semantic expansion of 0x00448AC0. The retail helper takes its output,
// manager, and object in EAX, EDX, and EBX, respectively.
static void RegisterSecondaryBack_00422ab0(
    void* manager, void* object, uint32_00422ab0* assigned_handle) {
    unsigned char* manager_bytes = static_cast<unsigned char*>(manager);
    AnimationBackLink_00422ab0* link =
        reinterpret_cast<AnimationBackLink_00422ab0*>(
            static_cast<unsigned char*>(object) + 4);
    AnimationBackLink_00422ab0** head =
        reinterpret_cast<AnimationBackLink_00422ab0**>(manager_bytes + 0x72dadc);
    AnimationBackLink_00422ab0** tail =
        reinterpret_cast<AnimationBackLink_00422ab0**>(manager_bytes + 0x72dae0);
    uint32_00422ab0* next_handle =
        reinterpret_cast<uint32_00422ab0*>(manager_bytes + 0x732454);

    link->object = object;
    link->next = 0;
    link->previous = 0;

    if (*head == 0) {
        *head = link;
    } else {
        AnimationBackLink_00422ab0* old_tail = *tail;
        AnimationBackLink_00422ab0* following = old_tail->next;
        if (following != 0) {
            link->next = following;
            following->previous = link;
        }
        old_tail->next = link;
        link->previous = old_tail;
    }
    *tail = link;

    ++*next_handle;
    if (*next_handle == 0)
        ++*next_handle;

    *reinterpret_cast<uint32_00422ab0*>(object) = *next_handle;
    *assigned_handle = *next_handle;
}

// Semantic expansion of the register-only 0x0043E460 call used for "Pause".
// The records are 0x10C bytes apart and the first zero key ends the scan.
static void RegisterPauseResource_00422ab0(
    void* manager, const char* name, uint32_00422ab0 resource_id,
    uint32_00422ab0 variant) {
    unsigned char* records = static_cast<unsigned char*>(manager) + 0x1f88;
    int slot;
    for (slot = 0; slot < 0x1f; ++slot) {
        if (*reinterpret_cast<uint32_00422ab0*>(records + slot * 0x10c) == 0)
            break;
    }
    if (slot == 0x1f)
        return;

    unsigned char* record = records + slot * 0x10c;
    *reinterpret_cast<uint32_00422ab0*>(record + 0) = resource_id;
    *reinterpret_cast<uint32_00422ab0*>(record + 4) = variant;
    const char* source = name;
    char* destination = reinterpret_cast<char*>(record + 0x0c);
    char character;
    do {
        character = *source++;
        *destination++ = character;
    } while (character != 0);
    *reinterpret_cast<uint32_00422ab0*>(record + 8) = 0;
}

// Semantic expansion of the ESI/EBX/EDI helper at 0x004497D0. The +0x10
// linked child view and +0x38A script index are observed; their class names
// remain unknown.
static uint32_00422ab0 FindPauseChild_00422ab0(
    AnimationLookupContext* context, uint32_00422ab0* root_handle,
    unsigned short script_index) {
    void* root = FindAnimationByHandle_00422ab0(context, *root_handle);
    if (root == 0) {
        *root_handle = 0;
        return 0;
    }

    AnimationChildLink_00422ab0* link =
        reinterpret_cast<AnimationChildLink_00422ab0*>(
            static_cast<unsigned char*>(root) + 0x10);
    while (link != 0) {
        void* child = link->object;
        if (child != 0 &&
            *reinterpret_cast<unsigned short*>(
                static_cast<unsigned char*>(child) + 0x38a) == script_index) {
            return *reinterpret_cast<uint32_00422ab0*>(child);
        }
        link = link->next;
    }
    return 0;
}

// 0x00422AB0 has one stack pointer argument and callee cleanup (RET 4).
// There are no private register inputs at entry. The retail caller is
// FUN_004223F0 at 0x0042243B.
extern "C" __declspec(noinline) void __stdcall
asm_FUN_00422ab0_00422ab0(void* pause_state) {
    PauseMenuState_00422ab0* state =
        static_cast<PauseMenuState_00422ab0*>(pause_state);

    state->offset_004 = 1;
    if ((state->flags_020 & 1) == 0) {
        state->offset_014 = 0;
        state->offset_010 = 0xfff0bdc1u;
        state->offset_018 = 0;
        state->offset_01c = reinterpret_cast<uint32_00422ab0>(&data_00476f78);
        state->flags_020 |= 1;
    }

    state->offset_014 = 0;
    state->offset_018 = 0;
    state->offset_010 = 0xffffffffu;

    void* pause_runtime = *reinterpret_cast<void**>(&data_00477810);
    *reinterpret_cast<uint32_00422ab0*>(
        static_cast<unsigned char*>(pause_runtime) + 0x58) |= 0x10;

    void* animation_manager = *reinterpret_cast<void**>(&data_00491c10);
    AnimationPool* animation_pool =
        reinterpret_cast<AnimationPool*>(animation_manager);
    void* ui_owner = *reinterpret_cast<void**>(&data_004776e0);
    void* first_resource = *reinterpret_cast<void**>(
        static_cast<unsigned char*>(ui_owner) + 0x8998);

    // The retail allocator consumes the manager in ESI and returns the object
    // in EAX. Keep the ordinary member call: the focused LTCG context proves
    // this edge is expressible without an assembly shim when Allocate's body
    // is visible. Verify both calls in this initializer's full context during
    // integration; this source expression alone does not force register use.
    Entity* first_object = animation_pool->Allocate();
    unsigned char* first_bytes = reinterpret_cast<unsigned char*>(first_object);
    uint32_00422ab0 first_flags =
        *reinterpret_cast<uint32_00422ab0*>(first_bytes + 0x35c);
    *reinterpret_cast<uint32_00422ab0*>(first_bytes + 0x20) = 0x0f;
    *reinterpret_cast<uint32_00422ab0*>(first_bytes + 0x35c) =
        first_flags | 0x40000000u;

    InitializeAnimation_00422ab0 initializeAnimation =
        reinterpret_cast<InitializeAnimation_00422ab0>(
            VA_asm_FUN_00449870_00449870);
    initializeAnimation(first_resource, first_object, 0);

    uint32_00422ab0 first_handle = 0;
    RegisterSecondaryBack_00422ab0(
        animation_manager, first_object, &first_handle);
    state->offset_1d8 = first_handle;

    // Retail 0x00424480 receives animation_manager in ESI. Use the separate
    // semantic model with that receiver explicit rather than making an
    // ordinary C++ call through the private-ABI assembly entry.
    UpdateSpriteDescriptorModel_00424480(
        animation_manager, static_cast<int>(first_handle),
        0x20, 0x10, 0x180, 0x1c0);

    void* game_state = *reinterpret_cast<void**>(&data_0047770c);
    void* second_resource = *reinterpret_cast<void**>(
        static_cast<unsigned char*>(game_state) + 0x9ec8);
    state->offset_2c4 = reinterpret_cast<uint32_00422ab0>(second_resource);

    Entity* second_object = animation_pool->Allocate();
    unsigned char* second_bytes = reinterpret_cast<unsigned char*>(second_object);
    uint32_00422ab0 second_flags =
        *reinterpret_cast<uint32_00422ab0*>(second_bytes + 0x35c);
    *reinterpret_cast<uint32_00422ab0*>(second_bytes + 0x20) = 0x0f;
    *reinterpret_cast<uint32_00422ab0*>(second_bytes + 0x35c) =
        second_flags | 0x40000000u;
    initializeAnimation(second_resource, second_object, 0x79);

    uint32_00422ab0 second_handle = 0;
    RegisterSecondaryBack_00422ab0(
        animation_manager, second_object, &second_handle);
    state->offset_1d4 = second_handle;
    reinterpret_cast<AnimationHandle*>(&state->offset_1d4)->StopAtFrame3();

    // The recovered sound-queue source model takes sound id 0x20 and request 0.
    data_00492590.Queue(0x20, 0);

    // 0x0043E460 takes the manager in EAX and the string in EDX, followed by
    // stack values 6 and 0. Its register-only entry is represented by the
    // equivalent ordered table update here.
    RegisterPauseResource_00422ab0(
        reinterpret_cast<void*>(0x00492590),
        reinterpret_cast<const char*>(0x0046e0c0), 6, 0);

    pause_runtime = *reinterpret_cast<void**>(&data_00477810);
    if (*reinterpret_cast<uint32_00422ab0*>(
            static_cast<unsigned char*>(pause_runtime) + 0x5c) != 0) {
        uint32_00422ab0 child_handle = FindPauseChild_00422ab0(
            reinterpret_cast<AnimationLookupContext*>(animation_manager),
            &state->offset_1d4, 0x75);
        reinterpret_cast<AnimationManager*>(animation_manager)->SetFlag(
            reinterpret_cast<AnimationLookupContext*>(animation_manager),
            static_cast<int>(child_handle));
        child_handle = 0;
    }

    float* global_float = reinterpret_cast<float*>(&data_00476f78);
    state->offset_2c0 = *reinterpret_cast<uint32_00422ab0*>(global_float);
    *global_float = 1.0f;
}
