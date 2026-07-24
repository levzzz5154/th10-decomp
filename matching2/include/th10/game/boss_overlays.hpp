#pragma once

// Boss overlay position sync and boss UI indicator release (retail 0x0041D7C0, 0x0040E5F0).

struct BossVec3 {
    float x;
    float y;
    float z;
};

int Boss_SyncOverlayPositions(const BossVec3* position,
                              float facing_angle, float slot_marker,
                              float sentinel, float offset_x, float offset_y,
                              BossVec3* primary_overlay,
                              float* sprite_angle, unsigned int* sprite_flags,
                              BossVec3* secondary_overlay,
                              float (*normalize_angle)(float angle,
                                                       float quarter_turn),
                              void (*mark_dirty)(void* state), void* state);

int BossUi_ReleaseIndicators(int gauge_slot, int marker_slot, int marker_index,
                             int* popup_count, void* popup_zone,
                             void (*release_gauge)(void),
                             void (*release_marker)(int marker_index),
                             void (*spawn_popup)(void* zone, int count),
                             void (*flush_popups)(int* count),
                             void (*set_stage_timer)(int frames));
