#pragma once
#include <stddef.h>

// Record zero is the default; six main stages and the Extra stage follow.
// Score and replay screens use the one-past-end pointer, never a ninth record.
enum { ExtraStageIndex = 7, StageRouteCount = ExtraStageIndex + 1 };

struct StageRoute {
    int stage_kind;
    const char* stage_file;             // .std
    const char* enemy_animation_file;   // .anm
    const char* enemy_script_file;      // .ecl
    const char* music_files[2];         // stage and boss
    const char* message_files[2];       // one per player character
    const char* logo_animation_file;
    int music_tracks[2];                // stage and boss
    int reserved_2c;
};
typedef char StageRouteLayout[
    sizeof(StageRoute) == 0x30 && offsetof(StageRoute, enemy_script_file) == 0x0c &&
    offsetof(StageRoute, message_files) == 0x18 && offsetof(StageRoute, music_tracks) == 0x24 ? 1 : -1];

extern "C" StageRoute g_stage_routes[StageRouteCount];  // 0x00474788
extern "C" StageRoute* g_stage_route_current;           // 0x00477848
