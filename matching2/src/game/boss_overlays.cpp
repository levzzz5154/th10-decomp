#include "th10/game/boss_overlays.hpp"

// 0x0041D7C0 - Refresh the boss overlay sprite positions. The primary
// overlay (+0x934) always takes the boss position plus the playfield offset,
// the sprite angle (+0x62C) is renormalized from the facing angle, and
// sprite-flag bit 2 is armed. When the slot marker (+0x4C) equals the free
// sentinel, the secondary overlay (+0xCE0) is refreshed the same way. Each
// refresh marks the shared state manager dirty.
int Boss_SyncOverlayPositions(const BossVec3* position,
                              float facing_angle, float slot_marker,
                              float sentinel, float offset_x, float offset_y,
                              BossVec3* primary_overlay,
                              float* sprite_angle, unsigned int* sprite_flags,
                              BossVec3* secondary_overlay,
                              float (*normalize_angle)(float angle,
                                                       float quarter_turn),
                              void (*mark_dirty)(void* state), void* state) {
    primary_overlay->x = position->x + offset_x;
    primary_overlay->y = position->y + offset_y;
    primary_overlay->z = position->z;
    *sprite_angle = normalize_angle(facing_angle, 1.5707964f);
    *sprite_flags = *sprite_flags | 4;
    if (mark_dirty != 0) mark_dirty(state);
    if (slot_marker == sentinel) {
        secondary_overlay->x = position->x + offset_x;
        secondary_overlay->y = position->y + offset_y;
        secondary_overlay->z = position->z;
        if (mark_dirty != 0) mark_dirty(state);
    }
    return 0;
}

// 0x0040E5F0 - Release the boss UI indicators at the end of an attack: the
// health gauge is released when its slot (+0x2444) is armed, the spell
// marker is released for its slot index when armed (+0x2448/+0x244C), a
// pending score popup spawns when the popup counter (+0x2408) is positive,
// the popup queue is flushed, the counter clears, and the stage timer is
// re-armed with ten frames.
int BossUi_ReleaseIndicators(int gauge_slot, int marker_slot, int marker_index,
                             int* popup_count, void* popup_zone,
                             void (*release_gauge)(void),
                             void (*release_marker)(int marker_index),
                             void (*spawn_popup)(void* zone, int count),
                             void (*flush_popups)(int* count),
                             void (*set_stage_timer)(int frames)) {
    if (-1 < gauge_slot && release_gauge != 0) release_gauge();
    if (-1 < marker_slot && release_marker != 0) release_marker(marker_index);
    if (0 < *popup_count && spawn_popup != 0) {
        spawn_popup(popup_zone, *popup_count);
    }
    if (flush_popups != 0) flush_popups(popup_count);
    *popup_count = 0;
    if (set_stage_timer != 0) set_stage_timer(10);
    return 1;
}

// --- Render and platform leaves -----------------------------------------------------
