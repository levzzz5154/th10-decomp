// =============================================================================
// bullet.cpp - Bullet/enemy entity spawning and initialization
// Functions: 0x0040CFB0 (Entity_Spawn), 0x0040D830 (Entity_InitHelper),
//            0x0040CC70 (Entity_ClearAnims), 0x0040DC80 (Entity_UpdateTransform),
//            0x0040AF90 (BulletManager_Create), 0x0040AF00 (BulletManager_Release),
//            0x0040AE70 (BulletManager_LoadScripts)
// =============================================================================
#include "th10/game/entity.hpp"
#include "th10/game/scheduler.hpp"

extern "C" void* __cdecl operator_new(uint32_t size);
extern "C" void __cdecl _free(void* memory);
extern "C" void __stdcall EnterCriticalSection(void* criticalSection);
extern "C" void __stdcall LeaveCriticalSection(void* criticalSection);
extern void* PTR_LAB_0046d0c0;       // vtable for bullet entities
extern uint32_t DAT_00476f78;         // scheduler sentinel
extern uint32_t DAT_00474c74;         // global flag
extern uint32_t DAT_00477704;         // global config pointer
extern uint32_t DAT_004776fc;         // global bullet manager state
extern uint32_t DAT_00491be4;         // scheduler device
extern uint32_t DAT_00492274;         // scheduler critical section
extern unsigned char DAT_0049231c;    // scheduler reentrancy counter
extern void* g_pGameStateManager;     // typed alias for DAT_00491c10

int __fastcall ResourceManager_FindTexture(void* resource_template);
void __fastcall Entity_ClearAnims(void* unused, uint8_t* data);
int BulletEntity_UpdateTransform(uint32_t* bullet_transform);
void __fastcall AnimationManager_RemoveHandle(void* unused, void* manager, int handle);

// Resource-manager lookup: returns a typed resource pointer (or NULL). The
// retail name is loaded through this entry point so bullet manager setup can
// be exercised independently of the resource manager.
int* ResourceManager_FindResource(int type, void* manager, const char* name);

// 0x0040CF40 - Initialize the complete spawn-parameter record.
BulletSpawnParameters* __fastcall BulletSpawnParameters_Initialize(
    void* unused, BulletSpawnParameters* parameters) {
    for (int index = 0; index < 0x7E; ++index) {
        parameters->fields[index] = 0;
    }
    parameters->fields[0x0B] = 0x41000000; // 8.0f
    return parameters;
}

// 0x0040CF60 - Copy the three-component animation vector into a bullet.
void BulletEntity_SetAnimationVector(BulletEntity* entity, const float* value) {
    float* destination = reinterpret_cast<float*>(
        reinterpret_cast<uint8_t*>(entity) + 0x430);
    destination[0] = value[0];
    destination[1] = value[1];
    destination[2] = value[2];
}

// 0x0040CF90 - Find a linked bullet by its runtime identifier.
BulletEntity* BulletEntity_FindById(BulletEntityManager* manager, int id) {
    uint8_t* owner = reinterpret_cast<uint8_t*>(manager);
    uint8_t* node = *reinterpret_cast<uint8_t**>(owner + 0x18);
    while (node != 0) {
        if (*reinterpret_cast<int32_t*>(node + 0x54) == id)
            return reinterpret_cast<BulletEntity*>(node);
        node = *reinterpret_cast<uint8_t**>(node + 8);
    }
    return 0;
}

// 0x0040CEA0 - Mark the bullet's active animation for deferred resource
// removal, then invalidate the local handle. The retail animation manager
// performs the root/child flag propagation behind AnimationManager_RemoveHandle.
void BulletEntity_MarkAnimationForRemoval(BulletEntity* entity) {
    uint8_t* bytes = (uint8_t*)entity;
    *(uint32_t*)(bytes + 0x378C) |= 0x10;
    AnimationManager_RemoveHandle(0, g_pGameStateManager,
                 *(int*)(bytes + 0x774));
    *(uint32_t*)(bytes + 0x774) = 0;
}

// 0x0040B250 - Give an entity its private copy of a 0x2c-byte resource
// record. Retail immediately mirrors the record's leading vector into the
// entity position, leaving the remaining eight words owned by the resource.
int __fastcall Entity_AttachResourceSnapshot(
    Entity* entity, const EntityResourceSnapshot* snapshot) {
    EntityResourceSnapshot* copy = (EntityResourceSnapshot*)operator_new(
        sizeof(EntityResourceSnapshot));
    *(EntityResourceSnapshot**)((uint8_t*)entity + 0x358) = copy;
    *copy = *snapshot;
    entity->Position() = *(const Vector3*)copy;
    return 0;
}

// 0x0040D680 - Restore the bullet vtable and release its owned resource.
void BulletEntity_ReleaseResource(BulletEntity* entity, void* vtable) {
    uint8_t* bytes = reinterpret_cast<uint8_t*>(entity);
    *reinterpret_cast<void**>(bytes) = vtable;
    void*& resource = *reinterpret_cast<void**>(bytes + 0x8c);
    if (resource != 0) {
        _free(resource);
        resource = 0;
    }
}

// 0x0040C6E0 - Release the bullet's linked resource records.
// Each record stores an owned resource pointer at +0 and the next record at
// +4; the head pointer is retained at the retail entity offset +0x1034.
void BulletEntity_ClearResourceList(BulletEntity* entity) {
    uint8_t* bytes = reinterpret_cast<uint8_t*>(entity);
    uint8_t* record = *reinterpret_cast<uint8_t**>(bytes + 0x1034);
    while (record != 0) {
        uint8_t* next = *reinterpret_cast<uint8_t**>(record + 4);
        _free(*reinterpret_cast<void**>(record));
        _free(record);
        record = next;
    }
    *reinterpret_cast<uint8_t**>(bytes + 0x1034) = 0;
}

// ============================================================================
// 0x0040CC70 - Clear Animation States
// Clears flag bits at various offsets and zeroes 8 blocks of 0x84 dwords.
// __fastcall: ECX = this (unused), EDX = bullet_data pointer
//
// Ghidra decompilation:
//   Clears bit 0 at offsets: +300, +0x17C, +0x1C8, +0x204, +0x240, +0x27C, +0x2B8
//   Then zeroes 8 blocks of 0x84 dwords starting at bullet_data + 0x2C4
//   Each block ends with a 0xFFFFFFFF marker at offset +0x204 within block
//   Clears bit 0 at +0x142C and +0x1440
// ============================================================================
void __fastcall Entity_ClearAnims(void* unused, uint8_t* data) {
    *(uint32_t*)(data + 300)   &= 0xFFFFFFFE;
    *(uint32_t*)(data + 0x17C) &= 0xFFFFFFFE;
    *(uint32_t*)(data + 0x1C8) &= 0xFFFFFFFE;
    *(uint32_t*)(data + 0x204) &= 0xFFFFFFFE;
    *(uint32_t*)(data + 0x240) &= 0xFFFFFFFE;
    *(uint32_t*)(data + 0x27C) &= 0xFFFFFFFE;
    *(uint32_t*)(data + 0x2B8) &= 0xFFFFFFFE;

    // 8 blocks of 0x84 dwords (0x210 bytes each) starting at +0x2C4
    uint32_t* p = (uint32_t*)(data + 0x2C4);
    for (int block = 8; block != 0; block--) {
        for (int i = 0x84; i != 0; i--) {
            *p++ = 0;
        }
        p[-1] = 0xFFFFFFFF;  // marker at end of each block (offset +0x204)
    }

    *(uint32_t*)(data + 0x142C) &= 0xFFFFFFFE;
    *(uint32_t*)(data + 0x1440) &= 0xFFFFFFFE;
}

// ============================================================================
// 0x0040D830 - Bullet Entity Init Helper
// Initializes a freshly allocated 0x2518-byte bullet entity.
// The retail ABI used ECX for template data and ESI for the entity. The clean
// API exposes both inputs as ordinary typed parameters.
//
// Ghidra decompilation (ESI = bullet entity pointer):
//   Sets vtable, clears anim states, zeroes bullet data (0x537 dwords),
//   initializes linked lists, timers, animation defaults (24.0f), 
//   scheduler chains, texture lookup, and collision group markers.
// ============================================================================
BulletEntity* BulletEntity_Initialize(
    BulletEntity* entity, const uint8_t* templateData) {
    uint32_t* esi = (uint32_t*)entity;

    esi[0x404] = 0;
    esi[0x405] = 0;
    esi[0] = (uint32_t)&PTR_LAB_0046d0c0;  // vtable

    // Clear animation states (offset 0x103C = esi + 0x40F dwords)
    Entity_ClearAnims(0, (uint8_t*)(esi + 0x40F));

    // Zero bullet data (0x537 dwords from esi+0x40F)
    uint32_t* p = esi + 0x40F;
    for (int i = 0x537; i != 0; i--) {
        *p++ = 0;
    }

    // Initialize linked lists
    esi[2] = 0;          // list1.next
    esi[3] = 0;          // list1.field
    esi[0x407] = (uint32_t)esi;  // list2 prev = self
    esi[0x40A] &= 0xFFFFFFFE;    // clear flag
    esi[0x408] = 0;
    esi[1] = (uint32_t)(esi + 2);  // list1.prev = &list1.next
    esi[0x406] = 0xFFFFFFFF;
    esi[0x40C] = (uint32_t)(esi + 2);
    esi[0x40D] = 0;
    esi[0x40E] = 0;

    // Self-reference
    esi[0x945] = (uint32_t)esi;

    // Zero various animation slots
    esi[0x46F] = 0;
    esi[0x482] = 0;
    esi[0x491] = 0;
    esi[0x4A0] = 0;
    esi[0x4AF] = 0;
    esi[0x4BE] = 0;

    // Zero 3 groups of 11 dwords (animation position data)
    for (int group = 0; group < 3; group++) {
        uint32_t* gp = esi + 0x430 - group * 0xB;
        for (int i = 0xB; i != 0; i--) {
            *gp++ = 0;
        }
    }

    // Set animation bounds = 24.0f (0x41C00000)
    esi[0x43B] = 0x41C00000;
    esi[0x43C] = 0x41C00000;
    esi[0x43D] = 0x41C00000;
    esi[0x43E] = 0x41C00000;

    esi[0x923] = 0xFFFFFFFF;
    esi[0x45B] = (uint32_t)esi;
    esi[0x45C] = 0;
    esi[0x45D] = 0;

    // Zero 15 dwords at esi+0x902
    p = esi + 0x902;
    for (int i = 0xF; i != 0; i--) {
        *p++ = 0;
    }

    esi[0x910] = 0x42000000;  // 32.0f
    esi[0x90F] = 0x42000000;  // 32.0f

    // Initialize scheduler chains (3 chains)
    // Chain 1: offsets 0x456-0x45A
    if ((esi[0x45A] & 1) == 0) {
        esi[0x457] = 0;
        esi[0x456] = 0xFFF0BDC1;
        esi[0x458] = 0;
        esi[0x459] = (uint32_t)&DAT_00476f78;
        esi[0x45A] |= 1;
    }
    esi[0x457] = 0;
    esi[0x458] = 0;
    esi[0x456] = 0xFFFFFFFF;

    // Chain 2: offsets 0x916-0x91A
    if ((esi[0x91A] & 1) == 0) {
        esi[0x917] = 0;
        esi[0x916] = 0xFFF0BDC1;
        esi[0x918] = 0;
        esi[0x919] = (uint32_t)&DAT_00476f78;
        esi[0x91A] |= 1;
    }
    esi[0x917] = 0;
    esi[0x918] = 0;
    esi[0x916] = 0xFFFFFFFF;

    // Chain 3: offsets 0x91B-0x91F
    if ((esi[0x91F] & 1) == 0) {
        esi[0x91C] = 0;
        esi[0x91B] = 0xFFF0BDC1;
        esi[0x91D] = 0;
        esi[0x91E] = (uint32_t)&DAT_00476f78;
        esi[0x91F] |= 1;
    }
    esi[0x91C] = 0;
    esi[0x91D] = 0;
    esi[0x91B] = 0xFFFFFFFF;

    // Load config value
    int config = *(int*)DAT_00477704;
    esi[0x40B] = *(uint32_t*)(config + 0x54);

    // Texture/sprite lookup
    int texId = ResourceManager_FindTexture((void*)templateData);
    *(int*)(esi[1] + 4) = texId;
    *(uint32_t*)esi[1] = 0;

    // Zero collision-related fields
    esi[0x8FF] = 0;
    esi[0x900] = 0;
    esi[0x901] = 0;

    // Set collision group markers (pairs of 0xFFFFFFFF and 0)
    esi[0x925] = 0xFFFFFFFF; esi[0x926] = 0xFFFFFFFF;
    esi[0x929] = 0xFFFFFFFF; esi[0x92A] = 0xFFFFFFFF;
    esi[0x92D] = 0xFFFFFFFF; esi[0x92E] = 0xFFFFFFFF;
    esi[0x931] = 0xFFFFFFFF; esi[0x932] = 0xFFFFFFFF;
    esi[0x935] = 0xFFFFFFFF; esi[0x936] = 0xFFFFFFFF;
    esi[0x939] = 0xFFFFFFFF; esi[0x93A] = 0xFFFFFFFF;
    esi[0x93D] = 0xFFFFFFFF; esi[0x93E] = 0xFFFFFFFF;
    esi[0x941] = 0xFFFFFFFF; esi[0x942] = 0xFFFFFFFF;

    esi[0x927] = 0; esi[0x92B] = 0; esi[0x92F] = 0; esi[0x933] = 0;
    esi[0x937] = 0; esi[0x93B] = 0; esi[0x93F] = 0; esi[0x943] = 0;
    return entity;
}

// ============================================================================
// 0x0040CFB0 - Entity Spawn (Bullet/Enemy Creation)
// Allocates a 0x2518-byte bullet entity, initializes it, copies spawn params
// from the EAX array, updates transform, links into entity manager's list.
//
// Parameters:
//   manager: list head/tail at +0x58/+0x5C and counters at +0x60/+0x64
//   templateData: texture/template data passed to the initializer
//   parameters: position, velocity, flags, and type fields
//
// Ghidra decompilation:
//   alloc = operator_new(0x2518)
//   if alloc == NULL: return 0
//   entity = Entity_InitHelper(templateData, allocation)  // ESI = alloc
//   Copy spawn params from in_EAX to entity fields
//   Update transform via BulletEntity_UpdateTransform
//   Determine sprite ID based on entity type/subtype
//   Link entity into manager's doubly-linked list
//   Increment entity count
// ============================================================================
BulletEntity* BulletEntity_Spawn(
    BulletEntityManager* manager, const uint8_t* templateData,
    const BulletSpawnParameters* parameters) {
    const uint32_t* spawnParams = parameters->fields;
    BulletEntity* allocation =
        (BulletEntity*)operator_new(sizeof(BulletEntity));
    uint8_t* entity;
    if (allocation == 0) {
        return 0;
    } else {
        entity = (uint8_t*)BulletEntity_Initialize(allocation, templateData);
    }

    // Copy spawn parameters from in_EAX array
    *(uint32_t*)(entity + 0x1094) = spawnParams[0];
    *(uint32_t*)(entity + 0x1098) = spawnParams[1];
    *(uint32_t*)(entity + 0x109C) = spawnParams[2];
    *(uint32_t*)(entity + 0x23F8) = spawnParams[3];
    *(uint32_t*)(entity + 0x23FC) = spawnParams[5];
    *(uint32_t*)(entity + 0x2408) = spawnParams[4];

    // Toggle bit 0x800 based on spawnParams[6]
    *(uint32_t*)(entity + 0x2480) ^= (spawnParams[6] << 11 ^ *(uint32_t*)(entity + 0x2480)) & 0x800;

    // Set type flag
    *(char*)(entity + 0x1024) = (char)(1 << (*(uint8_t*)&DAT_00474c74 & 0x1F));

    // Copy 8 dwords from spawnParams[8..] to entity+0x1138
    const uint32_t* src = spawnParams + 8;
    uint32_t* dst = (uint32_t*)(entity + 0x1138);
    for (int i = 8; i != 0; i--) {
        *dst++ = *src++;
    }

    // Initialize scheduler if needed
    if ((*(uint32_t*)(entity + 0x2468) & 1) == 0) {
        *(uint32_t*)(entity + 0x245C) = 0;
        *(uint32_t*)(entity + 0x2458) = 0xFFF0BDC1;
        *(uint32_t*)(entity + 0x2460) = 0;
        *(uint32_t*)(entity + 0x2464) = (uint32_t)&DAT_00476f78;
        *(uint32_t*)(entity + 0x2468) |= 1;
    }
    *(uint32_t*)(entity + 0x245C) = 2;
    *(uint32_t*)(entity + 0x2460) = 0x40000000;
    *(uint32_t*)(entity + 0x2458) = 1;

    // Toggle bit 0x40000 based on spawnParams[7]
    *(uint32_t*)(entity + 0x2480) ^= (spawnParams[7] << 18 ^ *(uint32_t*)(entity + 0x2480)) & 0x40000;

    // Update transform
    BulletEntity_UpdateTransform((uint32_t*)(entity + 0x103C));

    // Adjust sprite type based on flags
    if ((char)(*(uint32_t*)(entity + 0x2480) >> 8) < 0) {
        int varType = *(int*)(entity + 0x2408);
        if (varType == 1) {
            varType = 10;
        } else if (varType == 4) {
            varType = 0xB;
        }
        *(int*)(entity + 0x2408) = varType;
    }

    // Set difficulty-based flags
    *(uint32_t*)(entity + 0x2444) = (manager->spawnSerial & 1) + 2;

    // Determine sprite ID (default 0x167, varies by type/subtype)
    *(uint32_t*)(entity + 0x2448) = 0x167;
    if (*(int*)(entity + 0x1128) == 1) {
        switch (*(uint32_t*)(entity + 0x112C)) {
            case 0:   case 0x14: case 0x31:
                *(uint32_t*)(entity + 0x2448) = 0x167;
                break;
            case 5:   case 0x19: case 0x32:
                *(uint32_t*)(entity + 0x2448) = 0x164;
                break;
            case 10:  case 0x1E: case 0x33:
                *(uint32_t*)(entity + 0x2448) = 0x16A;
                break;
            case 0xF: case 0x23: case 0x34:
                *(uint32_t*)(entity + 0x2448) = 0x16D;
                break;
        }
    }
    *(uint32_t*)(entity + 0x244C) = 0;

    // Link into entity manager's doubly-linked list
    uint8_t* node = entity + 0x116C;
    if (manager->listHead == 0) {
        manager->listHead = node;
    } else {
        uint8_t* tail = (uint8_t*)manager->listTail;
        if (*(uint8_t**)(tail + 4) != 0) {
            *(uint8_t**)(entity + 0x1170) = *(uint8_t**)(tail + 4);
            *(uint8_t**)(*(uint8_t**)(tail + 4) + 8) = node;
        }
        *(uint8_t**)(tail + 4) = node;
        *(uint8_t**)(entity + 0x1174) = tail;
    }
    manager->listTail = node;
    ++manager->entityCount;
    ++manager->spawnSerial;

    return (BulletEntity*)entity;
}

// ============================================================================
// 0x0040AF00 - BulletManager_Release
// Retire the bullet manager's two scheduler callbacks and clear the global
// state pointer. Each release is wrapped in the scheduler critical section
// so it stays safe against the primary/secondary list being walked
// concurrently. The retail helper uses the device global (DAT_00491BE4) and
// the EnterCriticalSection/LeaveCriticalSection imports the scheduler keeps
// in its own import slots. __fastcall so ECX is the manager state.
// ============================================================================
void __fastcall BulletManager_Release(BulletManagerState* state) {
    void* device = (void*)DAT_00491be4;

    SchedulerCallback* primary = state->primary_callback;
    if (primary != 0) {
        EnterCriticalSection(&DAT_00492274);
        ++DAT_0049231c;
        Scheduler_Remove(primary, device);
        LeaveCriticalSection(&DAT_00492274);
        --DAT_0049231c;
    }

    SchedulerCallback* secondary = state->secondary_callback;
    if (secondary != 0) {
        EnterCriticalSection(&DAT_00492274);
        ++DAT_0049231c;
        Scheduler_Remove(secondary, device);
        LeaveCriticalSection(&DAT_00492274);
        --DAT_0049231c;
    }

    DAT_004776fc = 0;
}

// ============================================================================
// 0x0040B050 / 0x0040B060 - Scheduler callback stubs
// The bullet manager registers two "return 1" callbacks; the scheduler fires
// them on each tick and the engine just uses the success return value to
// keep ticking the manager. The clean C++ form replaces the retail naked
// stubs that live at the named addresses.
// ============================================================================
static int __fastcall BulletManager_PrimaryStub(void* /*owner*/) {
    return 1;
}
static int __fastcall BulletManager_SecondaryStub(void* /*owner*/) {
    return 1;
}

// ============================================================================
// 0x0040AE70 - BulletManager_LoadScripts
// Load "bullet.anm" from the game-state manager and register a primary and a
// secondary scheduler callback that both point at the success-stub. The
// retail ABI hides the manager pointer in EBX; the clean C++ form takes it
// as an explicit argument. Returns 0 on success, -1 if the resource lookup
// fails.
// ============================================================================
int BulletManager_LoadScripts(BulletManagerState* state) {
    int* resource = ResourceManager_FindResource(7, g_pGameStateManager, "bullet.anm");
    state->bullet_resource = resource;
    if (resource == 0) {
        return -1;
    }

    SchedulerCallback* primary = SchedulerCallback_Create(
        (SchedulerFunction)BulletManager_PrimaryStub);
    primary->flags &= ~2u;
    primary->owner = state;
    Scheduler_RegisterPrimary(primary, 0x17, (void*)DAT_00491be4);
    state->primary_callback = primary;

    SchedulerCallback* secondary = SchedulerCallback_Create(
        (SchedulerFunction)BulletManager_SecondaryStub);
    secondary->flags &= ~2u;
    secondary->owner = state;
    Scheduler_RegisterSecondary(secondary, 0x20, (void*)DAT_00491be4);
    state->secondary_callback = secondary;

    return 0;
}

// ============================================================================
// 0x0040AF90 - BulletManager_Create
// Allocate a fresh 0x18-byte manager state, zero it, mark it initialized,
// publish it through the global pointer, and load its scripts. The retail
// helper returns NULL on script-load failure after releasing the allocation
// so callers can distinguish "not yet created" from "created and live".
// ============================================================================
BulletManagerState* BulletManager_Create() {
    BulletManagerState* state =
        (BulletManagerState*)operator_new(sizeof(BulletManagerState));
    if (state == 0) {
        return 0;
    }
    state->flags = 0;
    state->reserved_004 = 0;
    state->primary_callback = 0;
    state->secondary_callback = 0;
    state->bullet_resource = 0;
    state->reserved_014 = 0;
    state->flags |= 2u;
    DAT_004776fc = (uint32_t)state;

    if (BulletManager_LoadScripts(state) != 0) {
        if (state != 0) {
            BulletManager_Release(state);
            _free(state);
        }
        return 0;
    }
    return state;
}
