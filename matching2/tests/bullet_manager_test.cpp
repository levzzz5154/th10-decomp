// =============================================================================
// bullet_manager_test.cpp - Host-side tests for the bullet manager lifecycle
// =============================================================================
#include "th10/game/entity.hpp"
#include "th10/game/scheduler.hpp"
#include "th10/render/animation_manager.hpp"

#include <cassert>
#include <cmath>
#include <cstdlib>
#include <cstring>

uint32_t DAT_00492274 = 0;
unsigned char DAT_0049231c = 0;
uint32_t DAT_004776fc = 0;
uint32_t DAT_00491be4 = 0;
void* g_pGameStateManager = 0;

extern "C" void* operator_new(uint32_t size) {
    return std::malloc(size);
}
extern "C" void __cdecl _free(void* memory) {
    std::free(memory);
}
extern "C" void __stdcall EnterCriticalSection(void*) {}
extern "C" void __stdcall LeaveCriticalSection(void*) {}

// Mocked resource manager lookup. The real implementation in retail code
// waits for a background loader thread; in this harness we just hand back a
// non-null pointer so the manager's script-load step can complete.
static int* g_mock_resource = 0;
static int g_mock_resource_calls = 0;
int* ResourceManager_FindResource(int /*type*/, void* /*manager*/, const char* /*name*/) {
    ++g_mock_resource_calls;
    return g_mock_resource;
}

// The per-entity transform entry (0x0040DC80) is file-scoped in bullet.cpp;
// declare it here so the offscreen-despawn test can drive the kill bounds.
int BulletEntity_UpdateTransform(uint32_t* bullet_transform);

// Stubs for retail globals/functions the bullet file pulls in via the
// pre-existing entity spawn/init helpers. These are not exercised by the
// bullet manager lifecycle, but the linker still needs them.
void* PTR_LAB_0046d0c0 = (void*)0;
uint32_t DAT_00476f78 = 0;
uint32_t DAT_00474c74 = 0;
uint32_t DAT_00477704 = 0;
void* g_pD3DDevice = (void*)0x1234;
float _DAT_00470b0c = 1.0f;
float _DAT_00470b04 = 0.0f;
float _DAT_00470b38 = 448.0f;
float _DAT_00470b3c = 192.0f;
float _DAT_00470b40 = -192.0f;
float _DAT_00470b48 = 10.0f;
float _DAT_00470b4c = 20.0f;
float _DAT_00470b60 = 0.5f;
float _DAT_00470b44 = 100.0f;
float _DAT_00470b00 = 0.01f;
float _DAT_00491e6c = 0.0f;
float _DAT_00491e70 = 0.0f;
float _DAT_00491e74 = 0.0f;
int __fastcall ResourceManager_FindTexture(void* /*resource_template*/) {
    return 0;
}
Entity* Entity_Constructor(Entity* entity) { return entity; }
void Entity_Init(void*, Entity*) {}
void Entity_Destructor(Entity* entity) {
    unsigned char* bytes = (unsigned char*)entity;
    void** resource = (void**)(bytes + 0x35C - sizeof(void*));
    if (*resource != 0) {
        std::free(*resource);
        *resource = 0;
    }
}
int AnimationObject_ExecuteScript(AnimationObject*) { return 1; }
void AnimationObject_Render(void*, AnimationObject*) {}
extern "C" int __stdcall D3DXCreateTexture(
    void*, unsigned int, unsigned int, unsigned int, unsigned int,
    unsigned int, unsigned int, void* output) {
    *(unsigned int*)output = 0;
    return -1;
}
static void* g_mark_manager;
static int g_mark_handle;
void __fastcall AnimationManager_RemoveHandle(void*, void* manager, int handle) {
    g_mark_manager = manager;
    g_mark_handle = handle;
}

static void ResetGlobals(unsigned char* device) {
    DAT_004776fc = 0;
    DAT_00491be4 = (uint32_t)device;
    DAT_0049231c = 0;
    g_mock_resource_calls = 0;
    g_mock_resource = 0;
}

int main() {
    unsigned char device[0x80];
    std::memset(device, 0, sizeof(device));

    // --- BulletEntity_MarkAnimationForRemoval ---
    BulletEntity marked;
    std::memset(&marked, 0, sizeof(marked));
    g_mark_manager = 0;
    g_mark_handle = 0;
    g_pGameStateManager = (void*)0x12345678;
    *(uint32_t*)((unsigned char*)&marked + 0x774) = 41;
    BulletEntity_MarkAnimationForRemoval(&marked);
    assert((*(uint32_t*)((unsigned char*)&marked + 0x378C) & 0x10) != 0);
    assert(g_mark_manager == g_pGameStateManager && g_mark_handle == 41);
    assert(*(uint32_t*)((unsigned char*)&marked + 0x774) == 0);

    // --- Entity_AttachResourceSnapshot: private copy and leading vector ---
    Entity entity;
    std::memset(&entity, 0, sizeof(entity));
    EntityResourceSnapshot snapshot;
    for (int index = 0; index < 11; ++index) {
        snapshot.fields[index] = 0x10203040u + (uint32_t)index;
    }
    float position[3] = { 12.5f, -3.25f, 0.75f };
    std::memcpy(&snapshot.fields[0], position, sizeof(position));
    assert(Entity_AttachResourceSnapshot(&entity, &snapshot) == 0);
    EntityResourceSnapshot* attached =
        *(EntityResourceSnapshot**)((unsigned char*)&entity + 0x358);
    assert(attached != &snapshot);
    assert(std::memcmp(attached, &snapshot, sizeof(snapshot)) == 0);
    assert(entity.Position().x == position[0]);
    assert(entity.Position().y == position[1]);
    assert(entity.Position().z == position[2]);
    snapshot.fields[10] = 0;
    assert(attached->fields[10] != snapshot.fields[10]);
    std::free(attached);

    // --- BulletManager_Create: success path ---
    ResetGlobals(device);
    int mock_resource_storage = 0;
    g_mock_resource = &mock_resource_storage;
    BulletManagerState* state = BulletManager_Create();
    assert(state != 0);
    assert((state->flags & 2u) != 0);
    assert(DAT_004776fc == (uint32_t)state);
    assert(state->primary_callback != 0);
    assert(state->secondary_callback != 0);
    assert(state->bullet_resource == g_mock_resource);
    assert(g_mock_resource_calls == 1);
    assert(DAT_0049231c == 0);

    // The primary callback must be linked into the primary list at device+0x14.
    SchedulerNode* primary_head =
        (SchedulerNode*)(device + 0x14);
    assert(primary_head->next == &state->primary_callback->node);
    assert(state->primary_callback->node.owner == state->primary_callback);
    assert(state->primary_callback->owner == state);

    // The secondary callback must be linked into the secondary list at
    // device+0x38. The retail priorities are 0x17 and 0x20; with only one
    // callback per list, the head's next pointer is the new node.
    SchedulerNode* secondary_head =
        (SchedulerNode*)(device + 0x38);
    assert(secondary_head->next == &state->secondary_callback->node);
    assert(state->secondary_callback->owner == state);
    assert((state->primary_callback->flags & 2u) == 0);
    assert((state->secondary_callback->flags & 2u) == 0);

    // --- BulletManager_Release: clean teardown ---
    BulletManager_Release(state);
    assert(primary_head->next == 0);
    assert(secondary_head->next == 0);
    assert(DAT_004776fc == 0);
    // The free-on-retire flag in the callbacks is the default set by the
    // scheduler constructor, so the memory is gone after release.
    assert(DAT_0049231c == 0);
    std::free(state);

    // --- BulletManager_Create: missing resource path ---
    ResetGlobals(device);
    g_mock_resource = 0;
    BulletManagerState* failed = BulletManager_Create();
    assert(failed == 0);
    assert(DAT_004776fc == 0);
    assert(DAT_0049231c == 0);
    assert(g_mock_resource_calls == 1);

    // --- BulletEntity_Spawn: retail manager list ownership ---
    unsigned char config[0x58] = {};
    unsigned char inner_config[0x58] = {};
    *reinterpret_cast<uint32_t*>(config) =
        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(inner_config));
    DAT_00477704 =
        static_cast<uint32_t>(reinterpret_cast<uintptr_t>(config));
    BulletEntityManager entity_manager = {};
    BulletSpawnParameters parameters = {};
    BulletSpawnParameters_Initialize(nullptr, &parameters);
    float spawn_position[3] = {12.0f, -4.0f, 0.5f};
    std::memcpy(parameters.fields, spawn_position, sizeof(spawn_position));
    parameters.fields[3] = 7;
    parameters.fields[4] = 11;
    parameters.fields[5] = 13;
    parameters.fields[7] = 1;
    BulletEntity* spawned =
        BulletEntity_Spawn(&entity_manager, nullptr, &parameters);
    assert(spawned != 0);
    assert(entity_manager.entityCount == 1);
    assert(entity_manager.spawnSerial == 1);
    assert(entity_manager.listHead ==
           reinterpret_cast<unsigned char*>(spawned) + 0x116C);
    assert(entity_manager.listTail == entity_manager.listHead);
    unsigned char* spawned_bytes = reinterpret_cast<unsigned char*>(spawned);
    assert(std::memcmp(spawned_bytes + 0x1094, spawn_position,
                       sizeof(spawn_position)) == 0);
    assert(*reinterpret_cast<uint32_t*>(spawned_bytes + 0x2408) == 11);
    std::free(spawned);

    // --- BulletEntity_UpdateTransform: offscreen despawn bounds ---
    // Retail loc_40DFDA checks the four kill bounds as x+hw < 470B40 (-192),
    // x-hw > 470B3C (192), y+hh < 470B04 (0) and y-hh > 470B38 (448).  The
    // x/y pairings are the OPPOSITE of the player-clamp pairings, so each
    // bound must use the matching global.  An entity that has been inside
    // (0x100 flag) reports despawn (-1) once it crosses a bound.
    {
        BulletEntityManager offscreen_manager = {};
        BulletSpawnParameters offscreen_params = {};
        BulletSpawnParameters_Initialize(nullptr, &offscreen_params);
        float inside_position[3] = {0.0f, 100.0f, 0.0f};
        std::memcpy(offscreen_params.fields, inside_position,
                    sizeof(inside_position));
        offscreen_params.fields[7] = 1;
        BulletEntity* offscreen =
            BulletEntity_Spawn(&offscreen_manager, nullptr, &offscreen_params);
        assert(offscreen != 0);
        unsigned char* ob = reinterpret_cast<unsigned char*>(offscreen);
        // The spawn-time UpdateTransform ran at (0, 100), inside the field,
        // so the 0x100 "has been inside" flag is already set.
        assert((*reinterpret_cast<uint32_t*>(ob + 0x2480) & 0x100u) != 0);
        // Still inside: the next tick keeps returning 0.
        *reinterpret_cast<uint32_t*>(ob + 0x2480) &= ~0x400u;
        assert(BulletEntity_UpdateTransform(
                   reinterpret_cast<uint32_t*>(ob + 0x103C)) == 0);
        // Move past the right bound (x - half_width > 192, half_width = 0).
        *reinterpret_cast<float*>(ob + 0x1094) = 200.0f;
        *reinterpret_cast<uint32_t*>(ob + 0x2480) &= ~0x400u;
        assert(BulletEntity_UpdateTransform(
                   reinterpret_cast<uint32_t*>(ob + 0x103C)) == -1);
        // Move past the top bound (y - half_height > 448).
        *reinterpret_cast<float*>(ob + 0x1094) = 0.0f;
        *reinterpret_cast<float*>(ob + 0x1098) = 500.0f;
        *reinterpret_cast<uint32_t*>(ob + 0x2480) &= ~0x400u;
        assert(BulletEntity_UpdateTransform(
                   reinterpret_cast<uint32_t*>(ob + 0x103C)) == -1);
        std::free(offscreen);
    }

    // --- BulletEntity_UpdateTransform: armed per-axis record paths ---
    // Retail 0x0040DC80 follows the armed 0x13C/0x188 records (sub_404610)
    // while their duration words are nonzero, feeds the angle/radius slots
    // from the 0x1D4-family records (sub_412AC0), and integrates the
    // current position through sub_44C2A0 with the 0.01 grid quantizer.
    {
        DAT_00476f78 = 0x3F800000u;  // 1.0f: normal-speed clock window
        BulletEntityManager path_manager = {};
        BulletSpawnParameters path_params = {};
        BulletSpawnParameters_Initialize(nullptr, &path_params);
        float path_start[3] = {0.0f, 0.0f, 0.0f};
        std::memcpy(path_params.fields, path_start, sizeof(path_start));
        path_params.fields[7] = 1;
        BulletEntity* path_entity =
            BulletEntity_Spawn(&path_manager, nullptr, &path_params);
        assert(path_entity != 0);
        unsigned char* pb = reinterpret_cast<unsigned char*>(path_entity);
        unsigned char* state = pb + 0x103C;

        // Per-axis 2D record read (sub_412AC0): armed at +0x1D4, duration
        // gate at +0x208.  Mode 7 publishes p0+velocity into the slots.
        unsigned char* rec2d = state + 0x1D4;
        *reinterpret_cast<float*>(rec2d + 0x00) = 0.0f;
        *reinterpret_cast<float*>(rec2d + 0x04) = 0.0f;
        *reinterpret_cast<float*>(rec2d + 0x08) = 3.0f;
        *reinterpret_cast<float*>(rec2d + 0x0C) = 0.5f;
        *reinterpret_cast<int32_t*>(rec2d + 0x20) = -1;
        *reinterpret_cast<int32_t*>(rec2d + 0x24) = 0;
        *reinterpret_cast<float*>(rec2d + 0x28) = 0.0f;
        *reinterpret_cast<uintptr_t*>(rec2d + 0x2C) =
            reinterpret_cast<uintptr_t>(&DAT_00476f78);
        *reinterpret_cast<uint32_t*>(rec2d + 0x30) = 1u;
        *reinterpret_cast<int32_t*>(rec2d + 0x34) = 60;
        *reinterpret_cast<int32_t*>(rec2d + 0x38) = 7;
        *reinterpret_cast<uint32_t*>(pb + 0x2480) &= ~0x400u;
        assert(BulletEntity_UpdateTransform(
                   reinterpret_cast<uint32_t*>(state)) == 0);
        assert(std::fabs(*reinterpret_cast<float*>(state + 0x70) -
                         0.5f) < 1e-6f);
        assert(std::fabs(*reinterpret_cast<float*>(state + 0x74) -
                         3.0f) < 1e-6f);

        // 3D path record (sub_404610): ease mode 1 from (0,0,0) to
        // (192,0,0) over 60 frames.  Frame 1: t = 1/60, path.x = 192*t^2,
        // and the +0x64 row receives path - base.
        unsigned char* rec3d = state + 0x13C;
        *reinterpret_cast<float*>(rec3d + 0x00) = 0.0f;
        *reinterpret_cast<float*>(rec3d + 0x04) = 0.0f;
        *reinterpret_cast<float*>(rec3d + 0x08) = 0.0f;
        *reinterpret_cast<float*>(rec3d + 0x0C) = 192.0f;
        *reinterpret_cast<float*>(rec3d + 0x10) = 0.0f;
        *reinterpret_cast<float*>(rec3d + 0x14) = 0.0f;
        *reinterpret_cast<int32_t*>(rec3d + 0x30) = -1;
        *reinterpret_cast<int32_t*>(rec3d + 0x34) = 0;
        *reinterpret_cast<float*>(rec3d + 0x38) = 0.0f;
        *reinterpret_cast<uintptr_t*>(rec3d + 0x3C) =
            reinterpret_cast<uintptr_t>(&DAT_00476f78);
        *reinterpret_cast<uint32_t*>(rec3d + 0x40) = 1u;
        *reinterpret_cast<int32_t*>(rec3d + 0x44) = 60;
        *reinterpret_cast<int32_t*>(rec3d + 0x48) = 1;
        const float pre_base_x = *reinterpret_cast<float*>(state + 0x58);
        *reinterpret_cast<uint32_t*>(pb + 0x2480) &= ~0x400u;
        assert(BulletEntity_UpdateTransform(
                   reinterpret_cast<uint32_t*>(state)) == 0);
        {
            const float expected = 192.0f * (1.0f / 60.0f) *
                                   (1.0f / 60.0f);
            const float position_x =
                *reinterpret_cast<float*>(state + 0x64);
            assert(std::fabs((position_x + pre_base_x) - expected) < 1e-4f);
            // Current position integrated through the quantizer: the
            // delta (summed records - previous current) landed on the
            // 0.01 grid.
            assert(*reinterpret_cast<float*>(state + 0x2C) >= 0.0f);
        }

        // Mode 7 hold with duration 2: the record publishes p0 and
        // disarms on completion, so the next tick leaves the path mode.
        *reinterpret_cast<float*>(rec3d + 0x0C) = 8.0f;
        *reinterpret_cast<int32_t*>(rec3d + 0x34) = 0;
        *reinterpret_cast<float*>(rec3d + 0x38) = 0.0f;
        *reinterpret_cast<int32_t*>(rec3d + 0x44) = 2;
        *reinterpret_cast<int32_t*>(rec3d + 0x48) = 7;
        const float hold_base_x = *reinterpret_cast<float*>(state + 0x58);
        *reinterpret_cast<uint32_t*>(pb + 0x2480) &= ~0x400u;
        assert(BulletEntity_UpdateTransform(
                   reinterpret_cast<uint32_t*>(state)) == 0);
        {
            const float position_x =
                *reinterpret_cast<float*>(state + 0x64);
            assert(std::fabs((position_x + hold_base_x) - 8.0f) < 1e-4f);
        }
        *reinterpret_cast<uint32_t*>(pb + 0x2480) &= ~0x400u;
        assert(BulletEntity_UpdateTransform(
                   reinterpret_cast<uint32_t*>(state)) == 0);
        assert(*reinterpret_cast<int32_t*>(rec3d + 0x44) == 0);
        std::free(path_entity);

        // Polar advance: with record-1's polar flag set, sub_44C2A0
        // rebuilds the displacement from the angle/radius slots.
        BulletEntityManager polar_manager = {};
        BulletSpawnParameters polar_params = {};
        BulletSpawnParameters_Initialize(nullptr, &polar_params);
        float polar_start[3] = {0.0f, 0.0f, 0.0f};
        std::memcpy(polar_params.fields, polar_start, sizeof(polar_start));
        polar_params.fields[7] = 1;
        BulletEntity* polar_entity =
            BulletEntity_Spawn(&polar_manager, nullptr, &polar_params);
        assert(polar_entity != 0);
        unsigned char* qb = reinterpret_cast<unsigned char*>(polar_entity);
        unsigned char* qstate = qb + 0x103C;
        *reinterpret_cast<float*>(qstate + 0x78) = 10.0f;  // radius
        *reinterpret_cast<float*>(qstate + 0x74) = 0.0f;   // angle
        *reinterpret_cast<uint8_t*>(qstate + 0x80) |= 1u;  // polar mode
        *reinterpret_cast<uint32_t*>(qb + 0x2480) &= ~0x400u;
        assert(BulletEntity_UpdateTransform(
                   reinterpret_cast<uint32_t*>(qstate)) == 0);
        assert(std::fabs(*reinterpret_cast<float*>(qstate + 0x58) -
                         10.0f) < 0.01f);
        assert(std::fabs(*reinterpret_cast<float*>(qstate + 0x5C)) <
               0.01f);
        std::free(polar_entity);
    }

    return 0;
}
