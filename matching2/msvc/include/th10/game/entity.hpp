#pragma once
#include "th10/types.hpp"

// Row-major D3D transformation matrix. Entity initialization and animation
// setup both construct this as an identity matrix before render code copies it
// into the derived world matrices.
struct Matrix4x4 {
    float values[4][4];
};

struct Vector3 {
    float x;
    float y;
    float z;
};

// ============================================================================
// Base Entity - 0x3AC bytes (0xEB dwords + 2 bytes)
// Used by Entity_Destructor (0x401FF0), Entity_Constructor (0x402050),
// Entity_Init (0x401DE0)
// ============================================================================
struct Entity {
    int32_t   animation_handle;    // +0x000, nonzero while registered
    // +0x004  embedded manager-list node
    Entity*   manager_node_animation;
    Entity*   manager_node_next;
    Entity*   manager_node_previous;
    // +0x010  embedded parent/child-list node
    Entity*   child_node_animation;
    Entity*   child_node_next;
    Entity*   child_node_previous;
    Entity*   render_chain_next;    // +0x01C
    int32_t   render_bucket;        // +0x020
    Vector3   rotation;             // +0x024, radians around X/Y/Z
    Vector3   angular_velocity;     // +0x030, radians per script tick
    float     scale_x;              // +0x03C, 1.0f by default
    float     scale_y;              // +0x040, 1.0f by default
    float     scale_velocity_x;     // +0x044
    float     scale_velocity_y;     // +0x048
    float     sprite_width;         // +0x04C, copied from sprite metadata
    float     sprite_height;        // +0x050, copied from sprite metadata
    float     uv_scroll_x;          // +0x054, wrapped to [0, 1)
    float     uv_scroll_y;          // +0x058, wrapped to [0, 1)
    int32_t   previous_frame;       // +0x05C
    int32_t   current_frame;        // +0x060
    float     frame_elapsed;        // +0x064
    float*    time_scale;           // +0x068, normally DAT_00476f78
    // +0x06C  flags (bit 0 cleared by constructor)
    uint32_t  flags_06C;
    // +0x070 - 0x0AF
    uint32_t  pad_070[16];
    // +0x0B0  flags (bit 0 cleared by constructor)
    uint32_t  flags_0B0;
    // +0x0B4 - 0x0FB
    uint32_t  pad_0B4[18];
    // +0x0FC  flags
    uint32_t  flags_0FC;
    // +0x100 - 0x127
    uint32_t  pad_100[10];
    // +0x128  flags
    uint32_t  flags_128;
    // +0x12C - 0x173
    uint32_t  pad_12C[18];
    // +0x174  flags
    uint32_t  flags_174;
    // +0x178 - 0x1AF
    uint32_t  pad_178[14];
    // +0x1B0  flags
    uint32_t  flags_1B0;
    // +0x1B4 - 0x1FB
    uint32_t  pad_1B4[18];
    // +0x1FC  flags
    uint32_t  flags_1FC;
    // +0x200 - 0x227
    uint32_t  pad_200[10];
    // +0x228  flags
    uint32_t  flags_228;
    // +0x22C - 0x23B
    uint32_t  pad_22C[4];
    Matrix4x4 local_transform;   // +0x23C, identity by default
    Matrix4x4 world_transform;   // +0x27C, derived during rendering
    Matrix4x4 backup_transform;  // +0x2BC
    uint32_t  primary_color;        // +0x2FC, ARGB; white by default
    uint32_t  secondary_color;      // +0x300, alternate ARGB color
    int16_t   stop_frame;          // +0x304
    uint16_t  reserved_306;
    void*     script_resource;     // +0x308
    // Interpreter variable banks occupy this region in the 32-bit layout:
    // four integers at +0x30C, four floats at +0x31C, then two integers at
    // +0x32C. Keep raw storage here because the preceding native pointer is
    // wider in host tests; the named accessors below preserve retail offsets.
    uint8_t   script_variable_storage[0x334 - 0x30C];
    Vector3   base_position;       // +0x334
    Vector3   position;            // +0x340, preserved across Entity_Init
    Vector3   render_offset;       // +0x34C
    // +0x358  resource pointer (freed by destructor)
    void*     resource;
    // Animation code treats the complete word as flags while constructors
    // initialize its low 16-bit end marker.
    union {
        uint32_t flags_35C;
        struct {
            uint16_t end_marker;   // +0x35C, 7 or 0xFFFF at construction
            uint16_t flags_high;
        };
    };
    // +0x360  second owned resource used by another entity subsystem
    void*     secondary_resource;
    // +0x364 - 0x377  runtime words not yet named by this header.
    uint8_t   pad_364[0x14];
    // +0x378  flag word cleared by Entity_Constructor alongside the animation
    // slot flags; the trailing script/sprite runtime follows it.
    uint32_t  flags_378;
    // Script execution state is documented here as raw storage for the same
    // native-pointer portability reason as script_variable_storage above:
    // +0x380 start frame, +0x384 sprite index, +0x386 resource ID,
    // +0x38A script index, +0x38C script base, +0x390 instruction cursor,
    // +0x394 sprite metadata, +0x398 update callback, +0x39C draw callback.
    uint8_t   animation_runtime_storage[0x3AC - 0x37C];

    // Accessors use retail byte offsets deliberately. Native pointers are
    // eight bytes in host-side tests but four bytes in the target ABI, so
    // direct late-structure fields are not portable between those builds.
    int16_t& StopFrame() {
        return *(int16_t*)((uint8_t*)this + 0x304);
    }
    void*& ScriptResource() {
        return *(void**)((uint8_t*)this + 0x308);
    }
    int32_t* ScriptIntegerVariables() {
        return (int32_t*)((uint8_t*)this + 0x30C);
    }
    float* ScriptFloatVariables() {
        return (float*)((uint8_t*)this + 0x31C);
    }
    int32_t* ScriptExtraIntegerVariables() {
        return (int32_t*)((uint8_t*)this + 0x32C);
    }
    Vector3& BasePosition() {
        return *(Vector3*)((uint8_t*)this + 0x334);
    }
    Vector3& Position() {
        return *(Vector3*)((uint8_t*)this + 0x340);
    }
    Vector3& RenderOffset() {
        return *(Vector3*)((uint8_t*)this + 0x34C);
    }
    void*& OwnedResource() {
        // Target offset is +0x358. Express it relative to the following flags
        // word so a native 64-bit host pointer does not overlap that word.
        return *(void**)((uint8_t*)this + 0x35C - sizeof(void*));
    }
    uint32_t& AnimationFlags() {
        return *(uint32_t*)((uint8_t*)this + 0x35C);
    }
    uint16_t& ScriptResourceId() {
        return *(uint16_t*)((uint8_t*)this + 0x386);
    }
    int16_t& SpriteIndex() {
        return *(int16_t*)((uint8_t*)this + 0x384);
    }
    int16_t& ScriptIndex() {
        return *(int16_t*)((uint8_t*)this + 0x38A);
    }
    int32_t& ScriptStartFrame() {
        return *(int32_t*)((uint8_t*)this + 0x380);
    }
    void*& ScriptBase() {
        return *(void**)((uint8_t*)this + 0x38C);
    }
    void*& ScriptCursor() {
        return *(void**)((uint8_t*)this + 0x390);
    }
    void*& SpriteMetadata() {
        return *(void**)((uint8_t*)this + 0x394);
    }

    // Outlined accessors recovered from the retail image at 0x00401CB0,
    // 0x00401CC0, 0x00401CD0 and 0x00401D10. Their native LTCG convention
    // keeps the entity pointer in EAX with the argument in CL or ECX.
    __declspec(noinline) void SetPrimaryColorAlpha(char alpha);
    __declspec(noinline) void SetPrimaryColor(uint32_t color);
    __declspec(noinline) void* GetSpriteMetadata();
    __declspec(noinline) void SetSpriteMetadata(void* metadata);
};
// Entity_Init (0x401DE0): the retail entity initializer.
void __fastcall Entity_Init(void* unused, Entity* entity);


bool Entity_PointWithinBounds(const Vector3* bounds, float x, float y);
bool Entity_PointWithinBoundsInclusive(const Vector3* bounds, float x, float y);
extern "C" unsigned char* __fastcall Entity_ResetRuntimeState_00405D00(
    unsigned char* entity);
// static_assert not available in MSVC 7.1
// sizeof(Entity) == 0x3AC

// ============================================================================
// Bullet / Enemy Entity - 0x2518 bytes
// Allocated by Entity_Spawn (0x40CFB0), initialized by Entity_InitHelper
// (0x40D830). Contains base Entity at offset 0, extended fields after.
// ============================================================================
struct BulletEntity {
    // +0x000  base Entity (0x3AC bytes)
    Entity    base;
    // +0x3AC - 0x103B  extended entity fields
    uint8_t   extended[0x103C - 0x3AC];
    // +0x103C  bullet data (zeroed as 0x537 dwords = 0x14DC bytes)
    uint32_t  bullet_data[0x537];
    // total = 0x103C + 0x14DC = 0x2518
};
// sizeof(BulletEntity) == 0x2518

// Parameters copied into a BulletEntity by the spawn path. The constructor at
// 0x0040CF40 clears all 0x1F8 bytes and gives the radius at +0x2C its default.
struct BulletSpawnParameters {
    uint32_t fields[0x7E];
};
// sizeof(BulletSpawnParameters) == 0x1F8

struct BulletEntityManager {
    uint8_t pad_000[0x58];
    void* listHead;                 // +0x58, points at entity +0x116C
    void* listTail;                 // +0x5C
    uint32_t entityCount;           // +0x60
    uint32_t spawnSerial;           // +0x64
};

// Fixed-size resource/template record copied by the entity attachment helper
// at 0x0040B250. The first three words are also the entity's initial position.
struct EntityResourceSnapshot {
    uint32_t fields[11];
};

// Runtime bullet manager state used by the bullet subsystem. Constructed
// lazily by BulletManager_Create (0x0040AF90) and torn down by
// BulletManager_Release (0x0040AF00). The retail layout exposes the primary
// and secondary scheduler callbacks and the loaded bullet.anm resource
// pointer used by the spawn path.
struct SchedulerCallback;
struct BulletManagerState {
    uint32_t flags;                // +0x00, bit 1 = initialized
    uint32_t reserved_004;
    SchedulerCallback* primary_callback;   // +0x08
    SchedulerCallback* secondary_callback; // +0x0C
    void* bullet_resource;         // +0x10, "bullet.anm" archive
    uint32_t reserved_014;
};
// sizeof(BulletManagerState) == 0x18

BulletSpawnParameters* __fastcall BulletSpawnParameters_Initialize(
    void* unused, BulletSpawnParameters* parameters);
void BulletEntity_SetAnimationVector(BulletEntity* entity, const float* value);
BulletEntity* BulletEntity_FindById(BulletEntityManager* manager, int id);
void BulletEntity_ReleaseResource(BulletEntity* entity, void* vtable);
void BulletEntity_ClearResourceList(BulletEntity* entity);
BulletEntity* BulletEntity_Initialize(
    BulletEntity* entity, const uint8_t* templateData);
BulletEntity* BulletEntity_Spawn(
    BulletEntityManager* manager, const uint8_t* templateData,
    const BulletSpawnParameters* parameters);
void BulletEntity_MarkAnimationForRemoval(BulletEntity* entity);
int __fastcall Entity_AttachResourceSnapshot(
    Entity* entity, const EntityResourceSnapshot* snapshot);

// 0x0040AF00 - Retire the bullet manager's two scheduler callbacks and clear
// the global pointer. Safe against null callback slots.
void __fastcall BulletManager_Release(BulletManagerState* state);
// 0x0040AF90 - Allocate a fresh 0x18-byte bullet manager state, mark it
// initialized, store it in the global slot, and load its scripts. Returns
// NULL when the script load fails and releases the allocation.
BulletManagerState* BulletManager_Create();
// 0x0040AE70 - Look up "bullet.anm" in the game-state manager and register
// the primary/secondary scheduler callbacks. The "this" pointer lives in EBX
// in the original ABI; the clean API exposes it as the first argument.
int BulletManager_LoadScripts(BulletManagerState* state);

// ============================================================================
// Entity Manager / GameStateManager
// Contains global state including entity slot array at +0x3AD4E0
// ============================================================================
struct EntityManager {
    uint8_t data[0x3AD4E0 + 0x80];  // includes 32 entity slots (0x20 * 4)
};

// ============================================================================
// Scheduler Task - 0x24 bytes (9 dwords)
// ============================================================================
struct SchedulerTask {
    SchedulerTask* next;
    SchedulerTask* prev;
    uint32_t       reserved_008;
    uint32_t       timer;
    uint32_t       reserved_010;
    uint32_t       reserved_014;
    uint32_t       reserved_018;
    uint32_t       reserved_01C;
    uint32_t       reserved_020;
};
// sizeof(SchedulerTask) == 0x24

// ============================================================================
// Type aliases (MSVC 7.1: no 'using' declarations, use typedefs)
// ============================================================================
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t   i8;
typedef int16_t  i16;
typedef int32_t  i32;
typedef int64_t  i64;
typedef float    f32;
typedef double   f64;
