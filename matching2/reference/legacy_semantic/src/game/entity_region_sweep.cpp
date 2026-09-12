// =============================================================================
// entity_region_sweep.cpp - Rectangular region sweep over the entity pool
// Functions: 0x00408210
// =============================================================================
#include "th10/game/entity_region_sweep.hpp"

namespace {

// Retail immediates: _DAT_00470B0C = 0.5, and the two radius thresholds are
// the literals 16.0 and 32.0.
const float kHalf = 0.5f;
const float kSmallRadiusLimit = 16.0f;
const float kMediumRadiusLimit = 32.0f;

float FloatAt(const unsigned char* base, int offset) {
    return *(const float*)(base + offset);
}

} // namespace

// 0x00408210 - Sweep the 2000-entry pool against an axis-aligned region and
// mark every live entry that overlaps it.
//
// The owner supplies a centre and a full extent; retail halves the extent once
// up front and derives the region's minimum and maximum corners from it. Note
// that although the third axis is halved and folded into a min/max pair just
// like the other two, the overlap test never reads it - the sweep is purely
// two-dimensional, and the z work is dead. That is reproduced here rather than
// tidied away.
//
// Entries whose 16-bit state word is 0 or 3 are skipped. Every other entry is
// expanded from its own centre and size into a rectangle, and the overlap test
// is inclusive on all four edges. On a hit retail sets bit 3 of the entry's
// leading flag word, optionally spawns the cancel effect, creates an animation
// for the entry position and resolves it back to a record, tints that record
// from one of three palette tables chosen by the descriptor radius, and finally
// clears the entry's timer.
//
// The palette lookup is indexed by the entry's 16-bit sprite field, and the
// table it indexes is chosen by strict greater-than comparisons against 16.0
// and 32.0, so a radius of exactly 16.0 still uses the small table.
int EntityRegionSweep_Run(EntityRegionSweepOwner* owner, int spawn_effects,
                          const EntityRegionSweepPalettes* palettes,
                          const EntityRegionSweepHooks* hooks) {
    const float half_x = owner->extent[0] * kHalf;
    const float half_y = owner->extent[1] * kHalf;
    // Halved and paired exactly like the other two axes, then never consulted.
    const float half_z = owner->extent[2] * kHalf;

    const float region_min_x = owner->center[0] - half_x;
    const float region_min_y = owner->center[1] - half_y;
    const float region_min_z = owner->center[2] - half_z;
    const float region_max_x = half_x + owner->center[0];
    const float region_max_y = half_y + owner->center[1];
    const float region_max_z = half_z + owner->center[2];
    (void)region_min_z;
    (void)region_max_z;

    unsigned char* entry = owner->entries;
    for (int remaining = ENTITY_REGION_SWEEP_COUNT; remaining != 0;
         --remaining, entry += ENTITY_REGION_SWEEP_STRIDE) {
        const short state =
            *(const short*)(entry + ENTITY_REGION_ENTRY_STATE);
        if (state == 0 || state == 3) continue;

        const float entry_half_x =
            FloatAt(entry, ENTITY_REGION_ENTRY_SIZE) * kHalf;
        const float entry_half_y =
            FloatAt(entry, ENTITY_REGION_ENTRY_SIZE + 4) * kHalf;
        const float entry_x = FloatAt(entry, ENTITY_REGION_ENTRY_POSITION);
        const float entry_y = FloatAt(entry, ENTITY_REGION_ENTRY_POSITION + 4);

        const float entry_min_x = entry_x - entry_half_x;
        const float entry_min_y = entry_y - entry_half_y;
        const float entry_max_x = entry_half_x + entry_x;
        const float entry_max_y = entry_half_y + entry_y;

        if (!(entry_max_x >= region_min_x && entry_min_x <= region_max_x &&
              entry_max_y >= region_min_y && entry_min_y <= region_max_y))
            continue;

        *(unsigned int*)(entry + ENTITY_REGION_ENTRY_FLAGS) |=
            (unsigned int)ENTITY_REGION_SWEEP_HIT_FLAG;

        float* position = (float*)(entry + ENTITY_REGION_ENTRY_POSITION);
        if (spawn_effects != 0 && hooks->spawn_effect != 0)
            hooks->spawn_effect(hooks->context, position);

        const int* handle = hooks->create_animation(
            hooks->context, position, owner->animation_archive,
            ENTITY_REGION_SWEEP_SCRIPT);
        unsigned char* record =
            hooks->find_animation(hooks->context, *handle);

        const unsigned char* descriptor =
            *(unsigned char**)(entry + ENTITY_REGION_ENTRY_DESCRIPTOR);
        if (descriptor != 0) {
            const float radius =
                FloatAt(descriptor, ENTITY_REGION_DESCRIPTOR_RADIUS);
            const short sprite =
                *(const short*)(entry + ENTITY_REGION_ENTRY_SPRITE);
            unsigned int color;
            if (radius > kSmallRadiusLimit) {
                color = radius > kMediumRadiusLimit
                            ? palettes->large_radius[sprite]
                            : palettes->medium_radius[sprite];
            } else {
                color = palettes->small_radius[sprite];
            }
            *(unsigned int*)(record + ENTITY_REGION_RECORD_COLOR) = color;
        }

        *(unsigned int*)(entry + ENTITY_REGION_ENTRY_TIMER) = 0;
    }

    return 0;
}
