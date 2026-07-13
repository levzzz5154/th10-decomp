// =============================================================================
// bullet.cpp - Bullet/enemy entity spawning and initialization
// Functions: 0x0040CFB0 (Entity_Spawn), 0x0040D830 (Entity_InitHelper),
//            0x0040CC70 (Entity_ClearAnims), 0x0040DC80 (Entity_UpdateTransform)
// =============================================================================
#include "th10/game/entity.hpp"

extern "C" void* operator_new(uint32_t size);
extern void* PTR_LAB_0046d0c0;       // vtable for bullet entities
extern uint32_t DAT_00476f78;         // scheduler sentinel
extern uint32_t DAT_00474c74;         // global flag
extern uint32_t DAT_00477704;         // global config pointer

int __fastcall FUN_00450470(void* param_1);  // texture/sprite lookup
void __fastcall Entity_ClearAnims(void* unused, int param_2);  // clear anim states
int FUN_0040dc80(uint32_t* param_1);  // update transform

// 0x0040CF40 - Initialize the complete spawn-parameter record.
BulletSpawnParameters* __fastcall BulletSpawnParameters_Initialize(
    void* unused, BulletSpawnParameters* parameters) {
    for (int index = 0; index < 0x7E; ++index) {
        parameters->fields[index] = 0;
    }
    parameters->fields[0x0B] = 0x41000000; // 8.0f
    return parameters;
}

// ============================================================================
// 0x0040CC70 - Clear Animation States
// Clears flag bits at various offsets and zeroes 8 blocks of 0x84 dwords.
// __fastcall: ECX = this (unused), EDX = param_2 (bullet data pointer)
//
// Ghidra decompilation:
//   Clears bit 0 at offsets: +300, +0x17C, +0x1C8, +0x204, +0x240, +0x27C, +0x2B8
//   Then zeroes 8 blocks of 0x84 dwords starting at param_2 + 0x2C4
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
// __thiscall: ECX = this (param data), but uses ESI as entity pointer
//   (ESI is set by caller before the call — non-standard register passing)
//
// Ghidra decompilation (unaff_ESI = entity pointer):
//   Sets vtable, clears anim states, zeroes bullet data (0x537 dwords),
//   initializes linked lists, timers, animation defaults (24.0f), 
//   scheduler chains, texture lookup, and collision group markers.
// ============================================================================
void __fastcall Entity_InitHelper(void* thisptr, uint8_t* param_1) {
    // unaff_ESI is the entity pointer — in the original code, ESI is loaded
    // before this call. We use a local to represent it.
    // In practice this function needs __asm for byte matching.
    uint32_t* esi = (uint32_t*)thisptr;  // actually from ESI register

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
    int texId = FUN_00450470(param_1);
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
}

// ============================================================================
// 0x0040CFB0 - Entity Spawn (Bullet/Enemy Creation)
// Allocates a 0x2518-byte bullet entity, initializes it, copies spawn params
// from the EAX array, updates transform, links into entity manager's list.
//
// Parameters:
//   param_1: entity manager (contains list head/tail at +0x58/+0x5C, count at +0x60)
//   param_2: template data (passed to init helper)
//   in_EAX: spawn parameter array (position, velocity, flags, etc.)
//
// Non-standard: in_EAX is passed via EAX register (not a normal parameter)
//
// Ghidra decompilation:
//   alloc = operator_new(0x2518)
//   if alloc == NULL: return 0
//   entity = Entity_InitHelper(param_2, param_2)  // ESI = alloc
//   Copy spawn params from in_EAX to entity fields
//   Update transform via FUN_0040DC80
//   Determine sprite ID based on entity type/subtype
//   Link entity into manager's doubly-linked list
//   Increment entity count
// ============================================================================
int Entity_Spawn(int* manager, void* template_data) {
    // in_EAX is the spawn parameter array (non-standard register passing)
    // In real code, EAX is loaded before this call
    uint32_t* spawnParams = (uint32_t*)manager;  // placeholder — actually from EAX

    void* alloc = operator_new(0x2518);
    int entity;
    if (alloc == 0) {
        entity = 0;
    } else {
        // FUN_0040d830 initializes the entity (uses ESI = alloc internally)
        entity = (int)alloc;  // simplified — actually calls init helper
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
    uint32_t* src = spawnParams + 8;
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
    FUN_0040dc80((uint32_t*)(entity + 0x103C));

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
    *(uint32_t*)(entity + 0x2444) = (*(uint32_t*)((uint8_t*)manager + 100) & 1) + 2;

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
    int node = entity + 0x116C;
    if (*(int*)((uint8_t*)manager + 0x58) == 0) {
        *(int*)((uint8_t*)manager + 0x58) = node;
    } else {
        int tail = *(int*)((uint8_t*)manager + 0x5C);
        if (*(int*)(tail + 4) != 0) {
            *(int*)(entity + 0x1170) = *(int*)(tail + 4);
            *(int*)(*(int*)(tail + 4) + 8) = node;
        }
        *(int*)(tail + 4) = node;
        *(int*)(entity + 0x1174) = tail;
    }
    *(int*)((uint8_t*)manager + 0x5C) = node;
    (*(int*)((uint8_t*)manager + 0x60))++;
    (*(int*)((uint8_t*)manager + 100))++;

    return entity;
}
