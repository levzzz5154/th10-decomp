// =============================================================================
// entity_region_sweep.hpp - Rectangular region sweep over the entity pool
// Retail function: 0x00408210
// =============================================================================
#ifndef TH10_GAME_ENTITY_REGION_SWEEP_HPP
#define TH10_GAME_ENTITY_REGION_SWEEP_HPP

enum {
    ENTITY_REGION_SWEEP_COUNT = 2000,   // retail loop counter
    ENTITY_REGION_SWEEP_STRIDE = 2032,  // retail entry stride, 0x1FC dwords
    ENTITY_REGION_SWEEP_HIT_FLAG = 8,   // bit 3 of the entry's leading flags
    ENTITY_REGION_SWEEP_SCRIPT = 371    // retail script index passed to create
};

// Offsets into one pool entry, relative to the entry base (owner + 0x60).
enum {
    ENTITY_REGION_ENTRY_FLAGS = 0x000,
    ENTITY_REGION_ENTRY_DESCRIPTOR = 0x39C, // 924
    ENTITY_REGION_ENTRY_POSITION = 0x3B4,   // 948, two floats
    ENTITY_REGION_ENTRY_SIZE = 0x3D0,       // 1008, two floats
    ENTITY_REGION_ENTRY_STATE = 0x446,      // 1094, int16
    ENTITY_REGION_ENTRY_TIMER = 0x450,      // 1104
    ENTITY_REGION_ENTRY_SPRITE = 0x7EC      // 2028, int16
};

// The descriptor's radius lives at +0x34 and selects one of three palette
// tables (retail 0x00474350, 0x00474390, 0x004743B0).
enum { ENTITY_REGION_DESCRIPTOR_RADIUS = 0x34 };

// Retail writes the selected palette entry to +0x2FC of the resolved record.
enum { ENTITY_REGION_RECORD_COLOR = 0x2FC };

struct EntityRegionSweepOwner {
    unsigned char* entries;   // owner + 0x60
    float center[3];          // owner + 0x44
    float extent[3];          // owner + 0x50
    void* animation_archive;  // owner + 0x3E0B50
};

struct EntityRegionSweepPalettes {
    const unsigned int* small_radius;  // 0x00474350, 16 entries
    const unsigned int* medium_radius; // 0x00474390, 8 entries
    const unsigned int* large_radius;  // 0x004743B0, 4 entries
};

struct EntityRegionSweepHooks {
    void* context;
    // 0x0041BB00, only invoked when the caller asks for the effect.
    void (*spawn_effect)(void* context, float* position);
    // 0x00448DB0 allocates the animation and reports a handle whose first
    // dword is the id; 0x004491C0 resolves that id to the record.
    const int* (*create_animation)(void* context, float* position,
                                   void* archive, int script_index);
    unsigned char* (*find_animation)(void* context, int animation_id);
};

// Returns 0, matching retail.
int EntityRegionSweep_Run(EntityRegionSweepOwner* owner, int spawn_effects,
                          const EntityRegionSweepPalettes* palettes,
                          const EntityRegionSweepHooks* hooks);

#endif // TH10_GAME_ENTITY_REGION_SWEEP_HPP
