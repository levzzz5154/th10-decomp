#pragma once

#include "th10/game/stage_entry.hpp"
#include "th10/game/stage_std.hpp"
#include "th10/game/stage_timeline.hpp"
#include "th10/math/interpolators.hpp"
#include "th10/script/stage_ecl_load.hpp"

// =============================================================================
// host_stage.hpp - Weapon Select -> stage-entry bridge (host side)
//
// Drives the reconstructed gameplay-entry chain with live objects only:
//   publish character/weapon/difficulty
//     -> GameMode_ApplyRequested (0x004218D0, menu -> gameplay dispatch)
//     -> construct StageContext
//     -> StageContext_Enter (0x00417870) with a live StageEntryEnv built from
//        the reconstructed scheduler (0x00449AE0..0x00449F17), archive/resource
//        manager (0x00434C20..0x00435800), stage script loader (0x00403850),
//        manager factories (0x00408C90/0x00414830/0x00429610/0x0040D6B0/
//        0x0041AED0/0x0041C290) and recovery leaves.
// Stage 1 resources come straight out of th10.dat via Resource_LoadFile.
// =============================================================================

struct HostStageReport {
	// Bridge entry
	int confirm_invoked;
	int character;
	int weapon;
	int difficulty;
	int archive_available;      // th10.dat mounted through the archive manager
	// Mode machine
	int mode_apply_result;      // GameMode_ApplyRequested return (1 = handled)
	int leave_gameplay_fired;   // menu -> gameplay dispatch hook invoked
	int mode_current_after;     // GameModeState.current after the apply
	// Stage entry
	int enter_attempted;
	int enter_result;           // StageContext_Enter: 0 = success, -1 = failure
	int factories_created;      // factory wrappers invoked successfully
	int factory_failures;
	int owned_allocations;      // allocations retained for the live bridge
	int update_task_registered; // priority-10 primary registration observed
	int draw_task_registered;   // priority-4 secondary registration observed
	// Real Stage 1 resource evidence (all byte counts from th10.dat)
	unsigned int std_size;      // th10/stage01.std
	int std_objects;            // STD header short @0
	int std_quads;              // STD header short @2
	char std_companion_anm[64]; // name embedded at STD +0x10 (stage01.anm)
	unsigned int companion_anm_size;
	unsigned int ecl_size;      // th10/stage01.ecl (SCPT container)
	int ecl_sub_count;          // SCPT dword @0x10
	int ecl_anim_includes;      // ANIM list entries (enemy.anm, stgenm01.anm)
	int ecl_ecli_includes;      // ECLI list entries (default.ecl)
	char ecl_include_names[160];
	unsigned int include_anm_bytes; // bytes loaded for the ANIM include files
	int music_loads;            // music_load slots submitted (intro + loop)
	int bgm_records;            // records parsed from th10/thbgm.fmt
	char bgm_track[64];         // resolved Stage 1 track (th10_00.wav)
	unsigned int bgm_offset;    // PCM offset in thbgm.dat
	unsigned int bgm_intro;     // raw loop field +0x14
	unsigned int bgm_total;     // raw loop field +0x18
	unsigned int bgm_rate;      // WAVEFORMATEX samples/second
	// Scheduler drive
	int frames_run;             // Scheduler_RunPrimary/RunSecondary iterations
	int update_ticks;           // StageContext_Update calls observed
	int draw_ticks;             // StageTask_ClearCameraOnIdle calls observed
	int stage_frame;            // StageContext frame word (+0x14)
	int last_update_result;
	int std_raw_view_valid;     // real DAT-backed STD passed bounded validation
	int std_geometry_valid;
	int std_subrecords;
	int std_placements;
	int timeline_initialized;
	unsigned int timeline_decoded;
	unsigned int timeline_stopped_events;
	unsigned int timeline_cursor_jumps;
	unsigned int timeline_rejected;
	unsigned int timeline_budget_rejections;
	size_t timeline_maximum_accessed_offset;
	size_t timeline_maximum_record_extent;
	unsigned int timeline_opcode_histogram[15];
};

struct HostStageRuntimeView {
	const StageScript* script;
	const unsigned char* std_data;
	unsigned int std_size;
	const unsigned char* companion_anm_data;
	unsigned int companion_anm_size;
	const unsigned char* ecl_data;
	unsigned int ecl_size;
	const unsigned int* ecl_sub_offsets;
	unsigned int ecl_sub_count;
	const StageStdRawView* std_view;
	const StageTimelineView* timeline_view;
	const struct HostStageCameraView* camera;
	const StageContext* context;
	const int* camera_words;
	int stage_frame;
};

struct HostStageCameraView {
	float eye[3];
	float target[3];
	float up[3];
	float field_of_view;
};

// Record whether th10.dat was mounted (host_main calls this at startup).
void HostStage_SetArchiveAvailable(int available);

// Publish the selections and run the genuine construction chain.
// Returns 0 when GameMode_ApplyRequested dispatched and StageContext_Enter
// returned success.
int HostStage_ConfirmWeapon(int character, int weapon, int difficulty);

// Advance the registered stage tasks through the real scheduler lists.
// Returns the number of frames actually run.
int HostStage_RunFrames(int frames);
int HostStage_IsActive();

const HostStageReport& HostStage_GetReport();
const HostStageRuntimeView& HostStage_GetRuntimeView();
