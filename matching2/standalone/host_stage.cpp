// =============================================================================
// host_stage.cpp - Weapon Select -> stage-entry bridge
//
// Everything on the construction path is a reconstructed retail function:
//   GameMode_ApplyRequested (0x004218D0) dispatches menu -> gameplay through
//   its leave_gameplay edge; the bridge then builds a StageContext and runs
//   StageContext_Enter (0x00417870) with a live StageEntryEnv:
//     - task nodes:        SchedulerCallback_Create (0x00449ED0)
//     - registration:      Scheduler_RegisterPrimary/Secondary (0x00449AE0/B70)
//     - stage geometry:    StageScript_Load (0x00403850) reading
//                          th10/stage01.std out of th10.dat through the
//                          reconstructed archive manager (0x00434C20..0x00435800)
//     - managers:          StageManager_CreateFromScript (0x00429610),
//                          ItemManager_Create (0x00414830),
//                          BulletManager_Create pool (0x00406060),
//                          EffectManager_Create (0x0041AED0),
//                          ScoreManager_CreateAndInit (0x0041C290),
//                          EnemyManager_Create (0x0040D6B0),
//                          PlayerManager_Create (0x00408C90),
//                          Recovery_CreateTimerState (0x00422360, 0x2C8),
//                          Recovery_CreateResourceState (0x00419090, 0x1A8),
//                          Recovery_CreateFixedState (0x004056B0, 0x48),
//                          Recovery_CreateLargeResourceState (0x00425020),
//                          Recovery_CreateHugeResourceState (0x0042B660, 0xB884)
//     - music:             Recovery_ReplaceExtensionWav (0x00420A90 tail) plus
//                          the real th10/thbgm.fmt record table
//   Per-frame drive: Scheduler_RunPrimary/RunSecondary (0x00449C00/0x00449D40)
//   -> StageTask_UpdateThunk (0x004187C0) -> StageContext_Update (0x00418190)
//   and StageTask_ClearCameraOnIdle (0x004187D0).
//
// Host adapters remain only at boundaries whose retail callees are still
// unrecovered (sound playback, render effects, player runtime); each one
// logs itself as a host adapter so nothing synthetic can masquerade as
// reconstructed behavior.
// =============================================================================
#include "host_stage.hpp"

#include "th10/game/stage_entry.hpp"
#include "th10/game/stage_update.hpp"
#include "th10/game/game_mode_switch.hpp"
#include "th10/game/scheduler.hpp"
#include "th10/game/manager_factories.hpp"
#include "th10/game/object_factories.hpp"
#include "th10/game/recovery_leaves.hpp"
#include "th10/game/bullet_manager.hpp"
#include "th10/game/enemy_lifecycle.hpp"
#include "th10/game/entity.hpp"
#include "th10/game/player.hpp"
#include "th10/game/main_menu_dispatch.hpp"
#include "th10/game/stage_tips.hpp"
#include "th10/game/pool_constructors.hpp"
#include "th10/game/score.hpp"
#include "th10/game/task_registration.hpp"
#include "th10/game/player_runtime_init.hpp"
#include "th10/game/score_timer_leaves.hpp"
#include "th10/game/spell_card_dispatch.hpp"
#include "th10/game/registered_clock.hpp"
#include "th10/game/pause_menu_reset.hpp"
#include "th10/game/manager_teardown.hpp"
#include "th10/game/slot_snapshot.hpp"
#include "th10/game/player_front_runtime.hpp"
#include "th10/game/gameplay_final_runtime.hpp"
#include "th10/game/linked_pool_release.hpp"
#include "th10/game/linked_pool_append.hpp"
#include "th10/game/boss_gauge.hpp"
#include "th10/math/angle.hpp"
#include "th10/math/timer.hpp"
#include "th10/platform/sound_dummy.hpp"
#include "th10/render/effect_ring.hpp"
#include "th10/render/anm_propagate.hpp"
#include "th10/render/animation_manager.hpp"
#include "th10/game/stage_std.hpp"
#include "th10/script/stage_ecl_load.hpp"
#include "th10/script/ecl_core_interpreter.hpp"
#include "th10/script/ecl_name_table.hpp"
#include "th10/script/ecl_vm_children.hpp"
#include "th10/script/ecl.hpp"
#include "th10/archive/resource_manager.hpp"
// windows_types.hpp defines NULL unconditionally; glibc headers included
// above already define it, so drop theirs first to stay -Werror clean.
#undef NULL
#include "th10/platform/file.hpp"

#include <algorithm>
#include <cstdarg>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

extern void* g_pGameStateManager;
extern uint32_t DAT_00477824;
extern uint32_t DAT_00477828;
extern uint32_t DAT_0047782c;
extern uint32_t DAT_00491bec;
extern uint32_t DAT_004776f0;
extern uint32_t DAT_004776f4;
extern uint32_t DAT_0047770c;
extern uint32_t DAT_00477818;
extern uint32_t DAT_004776e8;
extern uint32_t DAT_00477830;
extern uint32_t DAT_00477834;
extern uint32_t DAT_00477704;
extern uint8_t DAT_00491d78;
extern float DAT_00476f78;
// Retail score/faith globals block (dword_474C40..dword_474CAC) and the
// FrameTimer embedded at dword_474C54; both are linked straight out of the
// original .data section, so 0x00418A00 gets retail's own argument.
extern unsigned char DAT_00474c40[];
extern int DAT_00474c7c;   // retail stage index (off_474744[...] labels)
extern int DAT_00474c90;   // retail 0x00413BC0 gate word
extern unsigned char DAT_00474c54[];
// Retail dword_47783C: the published score-file image (0x0042AF20 allocates
// 0x1DCB4 bytes and stores the pointer here).
extern uint8_t* DAT_0047783c;
void D3DResourceWorker_Stop();

// -----------------------------------------------------------------------------
// CRT / synchronization shims. The reconstructed TUs import the retail CRT
// names (scheduler.cpp, dat.cpp, crypt.cpp, lzss.cpp); the host maps them
// onto the C runtime. DAT_00476f78 is already defined by host_main.cpp.
// -----------------------------------------------------------------------------
extern "C" void* operator_new(unsigned int size) { return std::malloc(size); }
#if !defined(_WIN32)
extern "C" void _free(void* memory) { std::free(memory); }
extern "C" void* _malloc(unsigned int size) { return std::malloc(size); }
extern "C" int _stricmp(const char* left, const char* right) {
	for (;; ++left, ++right) {
		int a = (unsigned char)*left, b = (unsigned char)*right;
		if (a >= 'A' && a <= 'Z') a += 'a' - 'A';
		if (b >= 'A' && b <= 'Z') b += 'a' - 'A';
		if (a != b) return a < b ? -1 : 1;
		if (a == 0) return 0;
	}
}
#endif
#if !defined(_WIN32)
extern "C" void EnterCriticalSection(void* criticalSection) {
	(void)criticalSection;
}
extern "C" void LeaveCriticalSection(void* criticalSection) {
	(void)criticalSection;
}
unsigned int DAT_00492274 = 0;
#else
// 0x00492274 is the first of the seven CRITICAL_SECTIONs 0x00438AD0
// initialises (stride 0x18). Giving it host-private storage here detached it
// from the file (0x004922A4) and text-log (0x004922BC) sections that share
// that array, so it stays a plain reference into the retail block.
extern unsigned int DAT_00492274;
#endif
unsigned char DAT_0049231c = 0; // scheduler critical-section init flag

#if !defined(_WIN32)
// Win32 RCDATA / GDI imports referenced by resource_file.cpp and
// memory_file.cpp. The Linux stage path never reaches them (the archive layer
// opens th10.dat through FileHandle), so null stubs satisfy the linker.
extern "C" void* FindResourceA(void* module, const char* name,
                               const char* type) {
	(void)module; (void)name; (void)type;
	return 0;
}
extern "C" void* LoadResource(void* module, void* resource) {
	(void)module; (void)resource;
	return 0;
}
extern "C" void* LockResource(void* resource) { (void)resource; return 0; }
extern "C" unsigned int SizeofResource(void* module, void* resource) {
	(void)module; (void)resource;
	return 0;
}
extern "C" int FreeResource(void* resource) { (void)resource; return 0; }
extern "C" void* SelectObject(void* dc, void* object) {
	(void)dc; (void)object;
	return 0;
}
extern "C" int DeleteDC(void* dc) { (void)dc; return 0; }
extern "C" int DeleteObject(void* object) { (void)object; return 0; }
#endif // !_WIN32

// -----------------------------------------------------------------------------
// Portable FileHandle backend. src/platform/file.cpp is the Win32 CreateFile
// implementation; the host supplies an fopen()-backed one with identical
// semantics so the reconstructed archive layer runs unmodified on Linux.
// -----------------------------------------------------------------------------
#if !defined(_WIN32)
FileHandle::FileHandle() {
	handle = 0;
	access = 0;
}
FileHandle::~FileHandle() { Close(); }
BYTE FileHandle::Open(const char* path, const char* mode) {
	Close();
	// Retail opens through CreateFile, which is always byte-exact; force
	// binary mode regardless of the "r"/"w" mode letter the callers pass.
	const bool writing = mode != 0 && (mode[0] == 'w' || mode[0] == 'a');
	FILE* file = std::fopen(path, writing ? "wb" : "rb");
	handle = (HANDLE)file;
	access = writing ? 2u : 1u;
	return file != 0;
}
void FileHandle::Close() {
	if (handle != 0) {
		std::fclose((FILE*)handle);
		handle = 0;
	}
}
DWORD FileHandle::Read(void* destination, DWORD size) {
	if (handle == 0) return 0;
	return (DWORD)std::fread(destination, 1, size, (FILE*)handle);
}
BYTE FileHandle::Write(const void* source, DWORD size) {
	if (handle == 0) return 0;
	return std::fwrite(source, 1, size, (FILE*)handle) == size;
}
DWORD FileHandle::Tell() const {
	if (handle == 0) return 0;
	long position = std::ftell((FILE*)handle);
	return (DWORD)(position < 0 ? 0 : position);
}
DWORD FileHandle::GetSize() const {
	if (handle == 0) return 0;
	FILE* file = (FILE*)handle;
	long position = std::ftell(file);
	std::fseek(file, 0, SEEK_END);
	long size = std::ftell(file);
	std::fseek(file, position < 0 ? 0 : position, SEEK_SET);
	return (DWORD)(size < 0 ? 0 : size);
}
BYTE FileHandle::Seek(LONG distance, DWORD origin) {
	if (handle == 0) return 0;
	const int whence = origin == 0 ? SEEK_SET : (origin == 1 ? SEEK_CUR : SEEK_END);
	return std::fseek((FILE*)handle, distance, whence) == 0;
}
void* FileHandle::ReadWhole(DWORD capacity) {
	if (handle == 0 || capacity == 0) return 0;
	void* buffer = std::malloc(capacity);
	if (buffer == 0) return 0;
	if (Read(buffer, capacity) != capacity) {
		std::free(buffer);
		return 0;
	}
	return buffer;
}
void File_ResolvePath(const char* path, char output[260]) {
	// Retail resolves against the executable directory; the standalone host
	// runs from the data directory, so a bounded copy preserves behavior.
	unsigned int index = 0;
	for (; path[index] != 0 && index < 259; ++index) output[index] = path[index];
	output[index] = 0;
}
#endif // !_WIN32

namespace {

// -----------------------------------------------------------------------------
// Bridge state
// -----------------------------------------------------------------------------
HostStageReport g_report;

// Scheduler device block (retail dword_491BE4 object slice): primary list
// sentinel at +0x14, secondary list sentinel at +0x38 (see scheduler.cpp).
unsigned char g_scheduler_device[0x100];

StageGlobals g_globals;
StageUpdateGlobals g_update_globals;
// Four shot types times three retail record slots, plus guard capacity for
// future stage-table expansion.
unsigned char g_score_file[16 * 17276];
unsigned char g_stage_descriptor[52];
int g_camera_words[32];
int g_anm_slots[0x200];
int g_thread_pending;
StageContext g_context;
StageRecord g_stage_record;
// The retail stage table (dword_477848 -> 0x00474788, 48-byte rows) carries
// two music indices per row at +36 and +40. The Stage 1 row at 0x004747B8
// holds 1 and 2; StageRecord models only the first 24 bytes, so the value
// 0x00418190 reads for its sub_420B10(0, ...) call is named here.
const int kStageOneMusicIndex = 1;
StageUpdateTaskPair g_task_pairs[1];
StageUpdateEnv g_update_env;
StageEntryEnv g_entry_env;
GameModeState g_mode_state;
GameModeEnv g_mode_env;
int g_active_difficulty;
const void* g_active_difficulty_record;
const int g_difficulty_table[5] = {0, 1, 2, 3, 4};
int g_exit_reason;

char g_script_name_sink[512];
char g_pending_script[260];
StageScript g_stage_script;
StageStdRawView g_std_view;
StageTimelineView g_timeline_view;
HostStageCameraView g_stage_camera;
Interp3F g_eye_interpolator;
Interp3F g_target_interpolator;
bool g_eye_interpolating;
bool g_target_interpolating;
unsigned char* g_companion_anm;
unsigned int g_companion_anm_size;
unsigned char* g_enemy_ecl;
unsigned int g_enemy_ecl_size;
const unsigned int* g_enemy_ecl_sub_offsets;
unsigned int g_enemy_ecl_sub_count;
HostStageRuntimeView g_runtime_view;

void* g_enemy_manager_slot;
void* g_effect_manager_slot;
void* g_bullet_pool_slot;
BulletManagerState* g_bullet_manager;
void* g_stage_manager;
void* g_item_manager;
void* g_large_resource_state;
void* g_score_manager;
void* g_timer_state;
void* g_resource_state;
void* g_stage_state;
void* g_fixed_state;
void* g_player_manager;

unsigned char* g_bgm_fmt;
unsigned int g_bgm_fmt_size;

void Log(const char* format, ...) {
	std::va_list arguments;
	va_start(arguments, format);
	std::fputs("stage-bridge: ", stdout);
	std::vfprintf(stdout, format, arguments);
	std::fputc('\n', stdout);
	va_end(arguments);
}

// -----------------------------------------------------------------------------
// Small allocation / construction helpers shared by the factory calls.
// -----------------------------------------------------------------------------
void* g_owned_allocations[64];
int g_owned_allocation_count;
// Retail 0x00426F70; defined with the StageUpdateEnv edges below.
void HostRunAttachedEffects();
void* HostPoolAlloc(uint32_t size);

void* HostAlloc(unsigned int size) {
	void* memory = std::malloc(size);
	if (memory != 0 && g_owned_allocation_count < 64)
		g_owned_allocations[g_owned_allocation_count++] = memory;
	return memory;
}
void HostFreeMem(void* memory) { std::free(memory); }
void HostConstructSlots(void* slots, int stride, int count) {
	std::memset(slots, 0, (size_t)stride * (size_t)count);
}
void HostDestroyNoop(void* manager) { (void)manager; }
void HostSleep(unsigned int milliseconds) { (void)milliseconds; }

// -----------------------------------------------------------------------------
// Resource helpers (reconstructed archive manager)
// -----------------------------------------------------------------------------
unsigned char* LoadArchiveFile(const char* path, unsigned int* size_out) {
	const unsigned int size = Resource_GetFileSize(path);
	if (size == 0) return 0;
	unsigned char* buffer = (unsigned char*)std::malloc(size);
	if (buffer == 0) return 0;
	if (Resource_LoadFile(path, buffer) == 0) {
		std::free(buffer);
		return 0;
	}
	*size_out = size;
	return buffer;
}

// -----------------------------------------------------------------------------
// StageScript_Load (0x00403850) environment: real STD out of th10.dat.
// -----------------------------------------------------------------------------
Byte* HostReadScriptFile(Word* size_slot, int mode) {
	(void)mode;
	unsigned int size = 0;
	unsigned char* buffer = LoadArchiveFile(g_pending_script, &size);
	if (buffer == 0) {
		Log("FAILED to load %s from th10.dat", g_pending_script);
		return 0;
	}
	*size_slot = size;
	g_report.std_size = size;
	Log("loaded %s from th10.dat (%u bytes)", g_pending_script, size);
	return (Byte*)buffer;
}

void* HostOpenScriptEntry(int mode, void* archive_manager, const char* name) {
	(void)archive_manager;
	// 0x00447280 companion load: the STD names its stage ANM at +0x10.
	char path[260];
	std::snprintf(path, sizeof(path), "th10/%s", name);
	unsigned int size = 0;
	unsigned char* buffer = LoadArchiveFile(path, &size);
	if (buffer == 0) {
		Log("FAILED to load companion entry %s (mode %d)", path, mode);
		return 0;
	}
	std::snprintf(g_report.std_companion_anm, sizeof(g_report.std_companion_anm),
	              "%s", name);
	g_report.companion_anm_size = size;
	g_companion_anm = buffer;
	g_companion_anm_size = size;
	Log("companion stage ANM %s loaded from th10.dat (%u bytes, open_entry mode %d)",
	    path, size, mode);
	return buffer;
}

void HostReportScriptError(void* sink, const char* message) {
	(void)sink;
	Log("stage script error: %s", message != 0 ? message : "(null)");
}

// Stage entry env: load_stage_script (0x00402640) -> real StageScript_Load.
int HostLoadStageScript(const char* name, int flag) {
	std::snprintf(g_pending_script, sizeof(g_pending_script), "%s", name);
	std::memset(&g_stage_script, 0, sizeof(g_stage_script));
	StageScriptEnv env;
	std::memset(&env, 0, sizeof(env));
	env.name_sink = g_script_name_sink;
	env.read_script_file = HostReadScriptFile;
	env.archive_manager = 0;
	env.open_entry = HostOpenScriptEntry;
	env.report_error = HostReportScriptError;
	env.error_sink = 0;
	env.error_text = "stage script load failed";
	env.allocate = HostAlloc;
	const int result = StageScript_Load(&g_stage_script, name, &env);
	if (result == 0 && g_stage_script.buffer != 0) {
		short objects = 0;
		short quads = 0;
		std::memcpy(&objects, g_stage_script.buffer + 0, sizeof(objects));
		std::memcpy(&quads, g_stage_script.buffer + 2, sizeof(quads));
		g_report.std_objects = objects;
		g_report.std_quads = quads;
		g_report.std_raw_view_valid =
		    StageStd_ParseRaw(
		        reinterpret_cast<const uint8_t*>(g_stage_script.buffer),
		        g_stage_script.cached_size, &g_std_view)
		        ? 1
		        : 0;
		if (g_report.std_raw_view_valid == 0) {
			Log("bounded raw STD view rejected DAT-backed %s", name);
			return false;
		}
		g_report.timeline_initialized =
		    StageTimeline_Initialize(&g_std_view, &g_timeline_view) ? 1 : 0;
		if (g_report.timeline_initialized == 0) {
			Log("bounded timeline view rejected DAT-backed %s", name);
			return false;
		}
		int subrecords = 0;
		bool objects_valid = true;
		for (uint16_t object_index = 0;
		     object_index < g_std_view.count_00; ++object_index) {
			StageStdObjectView object = {};
			if (!StageStd_GetObject(
			        &g_std_view, object_index, &object)) {
				objects_valid = false;
				break;
			}
			for (uint16_t subrecord_index = 0;; ++subrecord_index) {
				StageStdSubrecordView subrecord = {};
				if (!StageStd_GetSubrecord(
				        &object, subrecord_index, &subrecord))
					break;
				++subrecords;
			}
		}
		int placements = 0;
		for (;; ++placements) {
			StageStdPlacementView placement = {};
			if (!StageStd_GetPlacement(
			        &g_std_view, static_cast<uint16_t>(placements),
			        &placement))
				break;
			if (placement.object_index < 0 ||
			    placement.object_index >= g_std_view.count_00) {
				objects_valid = false;
				break;
			}
		}
		g_report.std_subrecords = subrecords;
		g_report.std_placements = placements;
		g_report.std_geometry_valid =
		    objects_valid && subrecords == g_std_view.count_02 &&
		    placements > 0;
		if (g_report.std_geometry_valid == 0) {
			Log("bounded STD geometry rejected DAT-backed %s", name);
			return false;
		}
		Log("StageScript_Load(0x00403850): %s parsed - %d background objects, "
		    "%d quads, companion '%s' (flag %d)",
		    name, (int)objects, (int)quads, g_stage_script.buffer + 0x10, flag);
	}
	return result == 0;
}

// -----------------------------------------------------------------------------
// Stage 1 ECL evidence: EnemyManager_Create's initializer receives the enemy
// script name; load the real SCPT container plus its ANIM/ECLI includes.
// -----------------------------------------------------------------------------
void AppendIncludeName(const char* name) {
	const size_t used = std::strlen(g_report.ecl_include_names);
	std::snprintf(g_report.ecl_include_names + used,
	              sizeof(g_report.ecl_include_names) - used, "%s%s",
	              used != 0 ? " " : "", name);
}

int HostEnemyScriptInit(void* script_name) {
	const char* name = (const char*)script_name;
	unsigned int size = 0;
	unsigned char* data = LoadArchiveFile(name, &size);
	if (data == 0) {
		Log("FAILED to load enemy script %s", name);
		return -1;
	}
	g_report.ecl_size = size;
	if (size >= 0x18 && std::memcmp(data, "SCPT", 4) == 0) {
		unsigned int include_offset = 0;
		unsigned int sub_count = 0;
		std::memcpy(&include_offset, data + 0x08, 4);
		std::memcpy(&sub_count, data + 0x10, 4);
		g_report.ecl_sub_count = (int)sub_count;
		const unsigned int sub_table_offset = 0x58;
		bool sub_table_valid =
		    sub_count <= (size - sub_table_offset) / sizeof(unsigned int);
		unsigned int previous = 0;
		for (unsigned int index = 0; sub_table_valid && index < sub_count;
		     ++index) {
			unsigned int offset = 0;
			std::memcpy(
			    &offset, data + sub_table_offset + index * 4, 4);
			if (offset < sub_table_offset + sub_count * 4 ||
			    offset + 0x10 > size ||
			    std::memcmp(data + offset, "ECLH", 4) != 0 ||
			    (index != 0 && offset <= previous))
				sub_table_valid = false;
			previous = offset;
		}
		if (!sub_table_valid) {
			Log("enemy script %s rejected: invalid bounded subroutine table",
			    name);
			std::free(data);
			return -1;
		}
		g_enemy_ecl = data;
		g_enemy_ecl_size = size;
		g_enemy_ecl_sub_offsets =
		    reinterpret_cast<const unsigned int*>(
		        data + sub_table_offset);
		g_enemy_ecl_sub_count = sub_count;
		Log("enemy script %s loaded from th10.dat (%u bytes, SCPT container, "
		    "%u subroutines, include list @0x%X)",
		    name, size, sub_count, include_offset);
		// Walk the ANIM/ECLI include lists: tag[4] + count, then `count`
		// NUL-terminated names, padded to the next 4-byte boundary.
		unsigned int cursor = include_offset;
		for (int list = 0; list < 2 && cursor + 8 <= size; ++list) {
			char tag[5] = {0, 0, 0, 0, 0};
			std::memcpy(tag, data + cursor, 4);
			unsigned int count = 0;
			std::memcpy(&count, data + cursor + 4, 4);
			cursor += 8;
			for (unsigned int index = 0; index < count && cursor < size; ++index) {
				const char* include_name = (const char*)(data + cursor);
				const size_t length = std::strlen(include_name);
				AppendIncludeName(include_name);
				char path[260];
				std::snprintf(path, sizeof(path), "th10/%s", include_name);
				unsigned int include_size = 0;
				unsigned char* include_data = LoadArchiveFile(path, &include_size);
				if (include_data != 0) {
					if (std::strcmp(tag, "ANIM") == 0) {
						g_report.ecl_anim_includes += 1;
						g_report.include_anm_bytes += include_size;
					} else {
						g_report.ecl_ecli_includes += 1;
					}
					Log("  %s include %s loaded from th10.dat (%u bytes)", tag,
					    path, include_size);
					std::free(include_data);
				} else {
					Log("  %s include %s MISSING", tag, path);
				}
				cursor += (unsigned int)length + 1;
			}
			cursor = (cursor + 3u) & ~3u; // align to the next include list
		}
	} else {
		Log("enemy script %s loaded (%u bytes) but header is not SCPT", name, size);
	}
	if (data != g_enemy_ecl)
		std::free(data);
	return 0; // 0 = success for the factory initializer convention
}

// -----------------------------------------------------------------------------
// StageEntryEnv initializers: each returns nonzero on success and calls the
// genuine reconstructed factory.
// -----------------------------------------------------------------------------
int HostStageManagerScriptInit(const char* script_path) {
	// First operational initializer: require the selected retail STD to be
	// present in the mounted archive before accepting the stage manager.
	return Resource_GetFileSize(script_path) != 0 ? 0 : -1;
}

int HostAdoptItemScoreTask(void* owner) {
	if (owner == 0)
		return -1;
	unsigned char* bytes = (unsigned char*)owner;
	// Retail 0x00413A20 adopts DAT_00491BE8 when a score image is already
	// resident, then resets the +0x9E60 clock and both HUD cache slots.
	*(unsigned char**)(bytes + 0x9EBC) = g_score_file;
	unsigned int* flags = (unsigned int*)(bytes + 0x9E70);
	if ((*flags & 1u) == 0) {
		*(int*)(bytes + 0x9E64) = 0;
		*(int*)(bytes + 0x9E60) = (int)0xFFF0BDC1u;
		*(int*)(bytes + 0x9E68) = 0;
		*(uint32_t*)(bytes + 0x9E6C) =
		    (uint32_t)(uintptr_t)&DAT_00476f78;
		*flags |= 1u;
	}
	*(int*)(bytes + 0x9E64) = 0;
	*(int*)(bytes + 0x9E68) = 0;
	*(int*)(bytes + 0x9E60) = -1;
	*(int*)(bytes + 0x9EC0) = -1;
	*(int*)(bytes + 0x9EC4) = -1;
	*(int*)(bytes + 0x9E78) = g_globals.score_current;
	return 0;
}

int HostInitSidePanel(void* replay_handle, void* key_buffer) {
	(void)replay_handle;
	(void)key_buffer;
	void* manager = StageManager_CreateFromScript(
	    g_stage_record.script_name, HostAlloc, HostConstructSlots,
		    HostStageManagerScriptInit, HostDestroyNoop, HostFreeMem);
	g_stage_manager = manager;
	if (manager != 0) g_report.factories_created += 1;
	else g_report.factory_failures += 1;
	Log("StageManager_CreateFromScript(0x00429610): %s",
	    manager != 0 ? "created (0x2D4 bytes, 8 interpolator slots)" : "FAILED");
	return manager != 0;
}

int HostInitItemManager() {
	ItemFrontRuntimeBindings bindings = {};
	bindings.initialize_score_task = HostAdoptItemScoreTask;
	ItemFrontRuntime_SetBindings(&bindings);
	auto initialize = []() -> int {
		return ItemFrontRuntime_Initialize((void*)DAT_0047770c);
	};
	void* manager = ItemManager_Create(HostAlloc, ItemManager_Construct, initialize,
		                                   HostDestroyNoop, HostFreeMem);
	g_item_manager = manager;
	if (manager != 0) g_report.factories_created += 1;
	else g_report.factory_failures += 1;
	Log("ItemManager_Create(0x00414830): %s",
	    manager != 0 ? "created (0x9ED0 bytes)" : "FAILED");
	return manager != 0;
}

int HostInitLargeResource() {
	LargePlayerRuntimeBindings bindings = {};
	bindings.create_player_object = []() -> void* { return HostAlloc(0x10); };
	// Retail's edge here is FUN_00404f30(player_object, state+0x10). Its
	// recovered body (BulletSlot_Construct) was reconstructed for the
	// bullet-pool caller and writes through +0x334..+0x3A1, far past the
	// player object this call site owns, so it is not a drop-in. What the
	// edge establishes for the player runtime is the archive binding, which
	// is done here directly.
	bindings.initialize_animation = [](void* state, void* archive) {
		if (state != 0)
			*reinterpret_cast<void**>(state) = archive;
	};
	bindings.random_int = []() -> int { return std::rand(); };
	// Retail's tail call at 0x00426F70.
	bindings.refresh_derived = [](void*) { HostRunAttachedEffects(); };
	LargePlayerRuntime_SetBindings(&bindings);
	void* state = HostAlloc(0x4478);
	if (state != 0) {
		LargePlayerRuntime_Construct(state);
		if (LargePlayerRuntime_Initialize(state) != 0) {
			HostFreeMem(state);
			state = 0;
		}
	}
	g_large_resource_state = state;
	if (state != 0) g_report.factories_created += 1;
	else g_report.factory_failures += 1;
	Log("Recovery_CreateLargeResourceState(0x00425020): %s",
	    state != 0 ? "created" : "FAILED");
	return state != 0;
}

// Retail 0x004065C0: clear the six per-layer draw lists, update every live
// bullet, relink survivors into their layer list and advance each bullet's
// interpolator clock. The pool object is the 0x3E0B54-byte block the factory
// produced; the retail field offsets are named in BulletLinkManager.
int __fastcall HostBulletPoolUpdate(void* owner) {
	if (owner == 0)
		return 1;
	unsigned char* pool = static_cast<unsigned char*>(owner);
	BulletLinkManager manager = {};
	manager.active_count = 0;
	BulletLinkEnv env = {};
	env.player_flags = 0;                 // no capture state in the host yet
	env.update_bullet = [](LinkBullet* bullet) -> int {
		// Retail's per-bullet update is 0x004067A0's sibling and is not
		// recovered; a bullet with a zero state word is already free, so
		// reporting "keep" leaves the pool's own bookkeeping in charge.
		return bullet != 0 && bullet->state == 0 ? 1 : 0;
	};
	env.clock_env.frame_step = 1.0f;
	BulletManager_RelinkActive(
	    &manager, reinterpret_cast<LinkBullet*>(pool + 0x60), 0x7D1, &env);
	*reinterpret_cast<int*>(pool + 0x5C) = manager.active_count;
	g_report.bullets_active = manager.active_count;
	return 1;
}

// Retail 0x004067A0:
//   if (!dword_477810 || (*((_BYTE *)dword_477810 + 88) & 4) == 0)
//       for (i = 0; i < 6; ++i) sub_4066E0(this, i, this);
// dword_477810 is the stage context (0x00417870's argument) and +88 is its
// flag word, so the pass is skipped while the stage-entry bit is still set.
// 0x004066E0 walks one per-layer row from this+0x14+4*layer and refreshes
// each node's collision snapshot.
int __fastcall HostBulletPoolDraw(void* owner) {
	if (owner == 0)
		return 1;
	// Retail's guard byte is StageContext::flags (+0x58) bit 2.
	if ((g_context.flags & 4u) != 0)
		return 1;
	unsigned char* pool = static_cast<unsigned char*>(owner);
	BulletLinkManager* manager =
	    reinterpret_cast<BulletLinkManager*>(pool + 0x14);
	for (int layer = 0; layer < 6; ++layer) {
		HitboxEnemy* head =
		    reinterpret_cast<HitboxEnemy*>(manager->heads[layer]);
		if (head == 0)
			continue;
		// 0x004066E0 adds flt_470B4C (224.0, at 0x00470B4C) to x and
		// flt_470B48 (16.0, at 0x00470B48) to y, and recomputes the
		// sprite angle as sub_44BC10(facing, 1.5707964) - the
		// add-and-wrap leaf recovered as Angle_NormalizeSum.
		// Retail's per-node tail is sub_4451C0(node + 8, dword_491C10,
		// pool, node), the four-argument ANM draw dispatcher; the
		// recovered leaf's two-parameter mark_dirty hook cannot carry
		// the node, so it is left unbound rather than faked.
		EnemyList_SyncHitboxes(head, 224.0f, 16.0f, Angle_NormalizeSum, 0,
		                       0);
	}
	return 1;
}

int HostInitBulletPoolRuntime() {
	BulletPoolRuntimeBindings bindings = {};
	bindings.update = HostBulletPoolUpdate;
	bindings.draw = HostBulletPoolDraw;
	BulletPoolRuntime_SetBindings(&bindings);
	const int status = BulletPoolRuntime_Initialize((void*)DAT_004776f0);
	// Retail registers the pool's callbacks disarmed and the loading owner
	// arms them once streaming completes. The host loads synchronously, so
	// arm them here or the scheduler never runs the bullet pass.
	if (status == 0 && DAT_004776f0 != 0) {
		unsigned char* pool = reinterpret_cast<unsigned char*>(
		    static_cast<uintptr_t>(DAT_004776f0));
		SchedulerCallback* update =
		    *reinterpret_cast<SchedulerCallback**>(pool + 8);
		SchedulerCallback* draw =
		    *reinterpret_cast<SchedulerCallback**>(pool + 0xC);
		if (update != 0) update->flags |= 2u;
		if (draw != 0) draw->flags |= 2u;
		Log("bullet pool callbacks armed (update=%p draw=%p)",
		    (void*)update, (void*)draw);
	}
	return status;
}

int HostInitBulletPool() {
	void* pool = BulletManager_Create(HostAlloc, HostConstructSlots,
	                                  (void**)&DAT_004776f0,
	                                  HostInitBulletPoolRuntime,
	                                  HostDestroyNoop, HostFreeMem);
	g_bullet_pool_slot = pool;
	if (pool != 0) g_report.factories_created += 1;
	else g_report.factory_failures += 1;
	Log("BulletManager_Create(0x00406060): %s",
	    pool != 0 ? "pool created (0x3E0B54 bytes)" : "FAILED");
	return pool != 0;
}

int HostInitEffectManager() {
	auto initialize = []() -> int {
		return ParticleEffectRuntime_Initialize((void*)DAT_00477818);
	};
	void* manager = EffectManager_Create(HostAlloc, HostConstructSlots,
	                                     (void**)&DAT_00477818, initialize,
	                                     HostDestroyNoop, HostFreeMem);
	g_effect_manager_slot = manager;
	if (manager != 0) g_report.factories_created += 1;
	else g_report.factory_failures += 1;
	Log("EffectManager_Create(0x0041AED0): %s",
	    manager != 0 ? "created (0x21CEC0 bytes, 0x896 pools)" : "FAILED");
	return manager != 0;
}

void HostScoreConstructBase(uint32_t* base) { (void)base; }
int32_t HostScoreInit(uint32_t* state) { (void)state; return 0; }
void HostScoreDestroy(uint32_t* state) { (void)state; }

int HostCreateScoreManager() {
	uint32_t* state = ScoreManager_CreateAndInit(HostAlloc, HostScoreConstructBase,
		                                             HostScoreInit, HostScoreDestroy);
	g_score_manager = state;
	if (state != 0) g_report.factories_created += 1;
	else g_report.factory_failures += 1;
	Log("ScoreManager_CreateAndInit(0x0041C290): %s",
	    state != 0 ? "created (0x45C bytes, published)" : "FAILED");
	return state != 0;
}

int HostInitTimerState() {
	void* state = Recovery_CreateTimerState(HostAlloc,
	                                        MenuTimerRuntime_Initialize,
		                                        HostDestroyNoop, HostFreeMem);
	g_timer_state = state;
	if (state != 0) g_report.factories_created += 1;
	else g_report.factory_failures += 1;
	Log("Recovery_CreateTimerState(0x00422360): %s",
	    state != 0 ? "created (0x2C8 bytes)" : "FAILED");
	return state != 0;
}

// Retail 0x0041A120 allocates one 0x88-byte tip record, appends it to the
// current difficulty's chain and fills in its position and text. The two
// startup tips are spawned at the screen-centre origin retail uses.
void HostSpawnStageTip(void* owner, uint32_t text_address, int32_t slot) {
	static const float origin[3] = {0.0f, 0.0f, 0.0f};
	// The text pointers are retail .rdata addresses; the all-source build
	// aliases that section, so the strings resolve for real.
	const char* text = reinterpret_cast<const char*>(
	    static_cast<uintptr_t>(text_address));
	StageTip* tip = StageTip_Create(static_cast<StageTipManager*>(owner),
	                                origin, text, HostPoolAlloc);
	Log("StageTip_Create(0x0041A120): slot %d tip %s", slot,
	    tip != 0 ? "appended" : "FAILED");
}

int HostInitResourceState() {
	StageTipRuntimeBindings tip_bindings = {};
	tip_bindings.spawn_tip = HostSpawnStageTip;
	StageTipRuntime_SetBindings(&tip_bindings);
	StageTipManager* state =
	    (StageTipManager*)HostAlloc(sizeof(StageTipManager));
	if (state != 0) {
		StageTipManager_Construct(state);
		if (StageTipRuntime_Initialize(state) != 0) {
			HostFreeMem(state);
			state = 0;
		}
	}
	g_resource_state = state;
	if (state != 0) g_report.factories_created += 1;
	else g_report.factory_failures += 1;
	Log("Recovery_CreateResourceState(0x00419090): %s",
	    state != 0 ? "created (0x1A8 bytes)" : "FAILED");
	return state != 0;
}

// Retail's tail edge is FUN_0043e5a0(stamp, 0xC4) with the just-initialized
// entity in ECX. The stamp is the game thread's frame word copied into the
// manager at +0x10; it identifies the animation whose resource record the
// configure pass applies. Resolving it through the recovered handle lookup
// keeps the call real: an unresolved stamp is a data condition, not a
// skipped edge.
void HostPreloadEffectResource(int frame_stamp, int argument) {
	AnimationObject* object =
	    g_pGameStateManager != 0
	        ? AnimationManager_Find(g_pGameStateManager, frame_stamp)
	        : 0;
	if (object == 0) {
		Log("AnimationObject_ConfigureFromResource(0x0043E5A0): stamp %d "
		    "does not resolve to a live animation yet", frame_stamp);
		return;
	}
	const int result = AnimationObject_ConfigureFromResource(
	    object, g_pGameStateManager, argument);
	Log("AnimationObject_ConfigureFromResource(0x0043E5A0): stamp %d, "
	    "index 0x%X, result %d", frame_stamp, argument, result);
}

int HostCreateStageState() {
	EffectManagerRuntimeBindings effect_bindings = {};
	effect_bindings.preload = HostPreloadEffectResource;
	EffectManagerRuntime_SetBindings(&effect_bindings);
	uint32_t* state = (uint32_t*)HostAlloc(0xB884);
	if (state != 0) {
		EffectManager_ResetAndPublish(state);
		if (EffectManagerRuntime_Initialize(state) != 0) {
			EffectManagerRuntime_Destroy(state);
			HostFreeMem(state);
			state = 0;
		}
	}
	g_stage_state = state;
	if (state != 0) g_report.factories_created += 1;
	else g_report.factory_failures += 1;
	Log("Recovery_CreateHugeResourceState(0x0042B660): %s",
	    state != 0 ? "created (0xB884 bytes)" : "FAILED");
	return state != 0;
}

int HostCreateEnemyManager(void* enemy_script) {
	void* manager = EnemyManager_Create(enemy_script, HostAlloc,
	                                    &g_enemy_manager_slot, HostEnemyScriptInit,
	                                    HostDestroyNoop, HostFreeMem);
	if (manager != 0) g_report.factories_created += 1;
	else g_report.factory_failures += 1;
	Log("EnemyManager_Create(0x0040D6B0): %s",
	    manager != 0 ? "created (0x68 bytes, published)" : "FAILED");
	return manager != 0;
}

int HostCreateBulletManager() {
	g_bullet_manager = BulletManager_Create();
	if (g_bullet_manager != 0) g_report.factories_created += 1;
	else g_report.factory_failures += 1;
	Log("BulletManager_Create(0x0040AF90): %s",
	    g_bullet_manager != 0 ?
	        "created; bullet.anm mounted and callbacks registered" :
	        "FAILED");
	return g_bullet_manager != 0;
}

int HostInitFixedState() {
	void* state = Recovery_CreateFixedState(0x48, HostAlloc,
	                                        PlayerRuntime_Initialize,
	                                        PlayerRuntime_Destroy, HostFreeMem);
	g_fixed_state = state;
	if (state != 0) g_report.factories_created += 1;
	else g_report.factory_failures += 1;
	Log("Recovery_CreateFixedState(0x004056B0): %s",
	    state != 0 ? "created (0x48 bytes)" : "FAILED");
	return state != 0;
}

int HostInitPlayerManager() {
	auto initialize = []() -> int {
		return PlayerScoreRuntime_Initialize((void*)DAT_004776f4);
	};
	void* manager = PlayerManager_Create(HostAlloc, PlayerManager_Construct,
	                                     initialize,
		                                     HostDestroyNoop, HostFreeMem);
	g_player_manager = manager;
	if (manager != 0) g_report.factories_created += 1;
	else g_report.factory_failures += 1;
	Log("PlayerManager_Create(0x00408C90): %s",
	    manager != 0 ? "created (0x37B0 bytes)" : "FAILED");
	return manager != 0;
}

// -----------------------------------------------------------------------------
// Music: real Recovery_ReplaceExtensionWav (0x00420A90 tail) + real
// th10/thbgm.fmt record table for loop metadata.
// -----------------------------------------------------------------------------
void HostSubmitBgmTrack(void* context, const char* wav_path) {
	(void)context;
	if (g_bgm_fmt == 0) {
		g_bgm_fmt = LoadArchiveFile("th10/thbgm.fmt", &g_bgm_fmt_size);
		if (g_bgm_fmt != 0) {
			g_report.bgm_records = (int)(g_bgm_fmt_size / 0x34);
			Log("th10/thbgm.fmt loaded from th10.dat (%u bytes, %d records)",
			    g_bgm_fmt_size, g_report.bgm_records);
		}
	}
	const char* base = wav_path;
	for (const char* cursor = wav_path; *cursor != 0; ++cursor)
		if (*cursor == '/' || *cursor == '\\') base = cursor + 1;
	if (g_bgm_fmt == 0) {
		Log("BGM %s requested but thbgm.fmt is unavailable", base);
		return;
	}
	for (unsigned int offset = 0; offset + 0x34 <= g_bgm_fmt_size; offset += 0x34) {
		const unsigned char* record = g_bgm_fmt + offset;
		char record_name[17];
		std::memcpy(record_name, record, 16);
		record_name[16] = 0;
		if (record_name[0] == 0) break;
		if (_stricmp(record_name, base) != 0) continue;
		unsigned int pcm_offset = 0, intro = 0, total = 0, rate = 0;
		std::memcpy(&pcm_offset, record + 0x10, 4);
		std::memcpy(&intro, record + 0x14, 4);
		std::memcpy(&total, record + 0x18, 4);
		std::memcpy(&rate, record + 0x24, 4); // WAVEFORMATEX nSamplesPerSec
		std::snprintf(g_report.bgm_track, sizeof(g_report.bgm_track), "%s", base);
		g_report.bgm_offset = pcm_offset;
		g_report.bgm_intro = intro;
		g_report.bgm_total = total;
		g_report.bgm_rate = rate;
		Log("BGM record %s: pcm offset 0x%08X, raw loop words (0x%X, 0x%X), "
		    "%u Hz - PCM stream lives in thbgm.dat (not part of th10.dat)",
		    base, pcm_offset, intro, total, rate);
		return;
	}
	Log("BGM %s: no matching thbgm.fmt record", base);
}

// Retail 0x00420C00 selects the dummy resource index from bit 4 of
// DAT_00491D78 and installs it through 0x0043E460 on the animation manager.
int HostConfigureDummyResource(void* target, const char* name, int value,
                               int flags) {
	if (target == 0)
		return 0;
	AnimationManager_RegisterResource(target, 0, name, value, flags);
	return 0;
}

void HostMusicReset() {
	GameState_DispatchDummy(g_pGameStateManager, DAT_00491d78,
	                        HostConfigureDummyResource);
	Log("GameState_DispatchDummy(0x00420C00): dummy resource index %d "
	    "installed through AnimationManager_RegisterResource(0x0043E460)",
	    (DAT_00491d78 & 0x10) != 0 ? 4 : 3);
}

void HostMusicLoad(int slot, const char* name) {
	if (name == 0) return;
	char path[260];
	std::snprintf(path, sizeof(path), "%s", name);
	if (Recovery_ReplaceExtensionWav(0, path, HostSubmitBgmTrack) != 0) {
		g_report.music_loads += 1;
		Log("music_load slot %d: %s -> %s via Recovery_ReplaceExtensionWav"
		    "(0x00420A90 tail)", slot, name, path);
	}
}

// -----------------------------------------------------------------------------
// Stage-entry edges. Every edge below runs the recovered retail body against
// host-owned storage laid out at the retail offsets, so the log lines report
// work that actually happened.
// -----------------------------------------------------------------------------

// Retail calls FUN_00418b80(&DAT_00474C40, 50000): the score seed word is the
// head of the gauge record, its tenth-target sits at +0x0C and the embedded
// frame timer at +0x14. StageGlobals is a field-named mirror rather than a
// retail-laid-out block, so the gauge record is owned here and the seed word
// is copied through it.
ScoreGaugeTimedValue g_score_gauge;

void HostStoreScoreGauge(void* gauge, int value) {
	ScoreGauge_SetTargetTenthAndDisableTimer(
	    static_cast<ScoreGaugeTimedValue*>(gauge), value);
}

void HostSeedExtendThreshold(int* score_seed, int amount) {
	if (score_seed == 0)
		return;
	g_score_gauge.reserved_00[0] = static_cast<unsigned int>(*score_seed);
	ScoreGauge_SetTargetTenthAndDisableTimer(&g_score_gauge, amount);
	*score_seed = static_cast<int>(g_score_gauge.reserved_00[0]);
	Log("ScoreGauge_SetTargetTenthAndDisableTimer(0x00418B80): seed %d, "
	    "gauge target %d, timer flags 0x%X", *score_seed,
	    g_score_gauge.target_tenth, g_score_gauge.timer.flags);
}

// Retail 0x0042A6A0 runs on the spell-card manager carried in EBX: state word
// at +0x10, per-difficulty history table at +0x1C, slot table at +0xA0. The
// host owns one so the recovered dispatcher runs for real on the replay path.
const int kSpellDifficultyCount = 8;
SpellRecord* g_spell_history[kSpellDifficultyCount];
SpellSlot g_spell_slots[kSpellDifficultyCount];
SpellManager g_spell_manager;
short g_spell_active_id;
int g_spell_active_aux;
RegisteredClock g_spell_clock;      // retail 0x00474C54..0x00474C64
Word g_spell_capture_flag;

SpellRecord* HostAllocateSpellRecord() {
	SpellRecord* record =
	    static_cast<SpellRecord*>(HostAlloc(sizeof(SpellRecord)));
	if (record != 0)
		std::memset(record, 0, sizeof(SpellRecord));
	return record;
}

void HostReplayReset() {
	const int difficulty = g_globals.mode;
	if (difficulty < 0 || difficulty >= kSpellDifficultyCount) {
		Log("SpellCard_Dispatch(0x0042A6A0) skipped: slot index %d is outside "
		    "the %d-entry host table", difficulty, kSpellDifficultyCount);
		return;
	}
	// The activate state dereferences the slot's record; the declare state
	// publishes one. Retail reaches activate only after a declare, so the
	// host mirrors that ordering instead of faulting on a null record.
	if (g_spell_manager.state == kSpellStateActivate &&
	    g_spell_slots[difficulty].record == 0) {
		g_spell_manager.state = kSpellStateDeclare;
	}
	g_spell_manager.history = g_spell_history;
	g_spell_manager.slots = g_spell_slots;
	g_spell_capture_flag = static_cast<Word>(g_globals.fresh_run);

	SpellDispatchEnv env = {};
	env.difficulty = &g_globals.mode;              // DAT_00474C7C
	env.allocate_record = HostAllocateSpellRecord; // operator new + wipe
	env.ui.active_spell_id = &g_spell_active_id;   // DAT_004918B0
	env.ui.active_spell_aux = &g_spell_active_aux; // DAT_004918B4
	env.ui.bonus_value = &g_globals.score_current; // DAT_00474C44
	env.ui.bonus_active = &g_globals.bomb_fragments; // DAT_00474C48
	env.ui.gauge = &g_score_gauge;                 // &DAT_00474C40
	env.ui.store_gauge = HostStoreScoreGauge;      // 0x00418B80
	env.ui.spell_clock = &g_spell_clock;
	env.ui.frame_scale = &g_globals.frame_scale;   // &DAT_00476F78
	env.ui.activation_param_a = &g_globals.lives;  // DAT_00474C70
	env.ui.activation_param_b = &g_globals.counter_474c98;
	env.ui.history_captures = &g_globals.power_474c90;
	env.ui.history_attempts = &g_globals.counter_474c9c;
	env.ui.capture_flag = &g_spell_capture_flag;   // DAT_00491FC4

	const int state = g_spell_manager.state;
	SpellCard_Dispatch(&g_spell_manager, &env);
	Log("SpellCard_Dispatch(0x0042A6A0): state %d, slot %d, record %p, "
	    "spell id %d", state, difficulty,
	    (const void*)g_spell_history[difficulty], (int)g_spell_active_id);
}
void HostReplaySeed(void* game) { (void)game; }

// Retail 0x00417800 resets the path cursor/timer pair at +0x40..+0x5C of the
// spell-practice state carried in EAX (retail dword_477704's practice block).
unsigned char g_spell_practice_state[0x60];

void HostSpellPracticeReset(void* state) {
	if (state == 0)
		return;
	PathState_Reset(state, static_cast<RecoveryWord>(
	                           reinterpret_cast<uintptr_t>(&DAT_00476f78)));
	Log("PathState_Reset(0x00417800): practice cursor rearmed "
	    "(flags 0x%X, cursor 0x%X)",
	    *reinterpret_cast<const unsigned int*>(
	        static_cast<const unsigned char*>(state) + 0x50),
	    *reinterpret_cast<const unsigned int*>(
	        static_cast<const unsigned char*>(state) + 0x40));
}
void HostResetPlayerSpawn(float* spawn, int value) {
	if (spawn != 0) Player_SetSchedulerValue(spawn, value);
}
void HostReleaseOverlayAnm(void* slots) {
	if (slots == 0) return;
	unsigned int& phase = *reinterpret_cast<unsigned int*>(
	    static_cast<unsigned char*>(slots) + 0x6fc);
	if (phase == 1) {
		AnimationManager_SetStopFrame(
		    g_pGameStateManager, DAT_00477824, 2);
		AnimationManager_SetStopFrame(
		    g_pGameStateManager, DAT_00477828, 2);
		AnimationManager_SetStopFrame(
		    g_pGameStateManager, DAT_0047782c, 2);
		DAT_00477824 = DAT_00477828 = DAT_0047782c = 0;
		phase = 2;
	}
	DAT_00491bec = 0;
}
void HostReleasePendingAnm(void* slots) {
	if (slots == 0) return;
	unsigned int& phase = *reinterpret_cast<unsigned int*>(
	    static_cast<unsigned char*>(slots) + 0x6fc);
	if (phase == 1) {
		AnimationManager_SetStopFrame(
		    g_pGameStateManager, DAT_00477824, 1);
		AnimationManager_SetStopFrame(
		    g_pGameStateManager, DAT_00477828, 1);
		AnimationManager_SetStopFrame(
		    g_pGameStateManager, DAT_0047782c, 1);
		DAT_00477824 = DAT_00477828 = DAT_0047782c = 0;
		phase = 0;
	}
	DAT_00491bec = 0;
}
void HostRequestCallbackRemoval(void* context) {
	if (context == 0) return;
	unsigned char* owner = static_cast<unsigned char*>(context);
	void* update = *reinterpret_cast<void**>(owner + 8);
	void* draw = *reinterpret_cast<void**>(owner + 0xc);
	if (update != 0)
		*reinterpret_cast<unsigned int*>(
		    static_cast<unsigned char*>(update) + 4) |= 2u;
	if (draw != 0)
		*reinterpret_cast<unsigned int*>(
		    static_cast<unsigned char*>(draw) + 4) |= 2u;
}

// -----------------------------------------------------------------------------
// Scheduler task callbacks: genuine thunks around the real stage tick.
// -----------------------------------------------------------------------------
int HostStageUpdateAdapter(void* context) {
	const int result = StageContext_Update((StageContext*)context, &g_update_env);
	g_report.last_update_result = result;
	return result;
}

int __fastcall HostStageUpdateCallback(void* owner) {
	g_report.update_ticks += 1;
	return StageTask_UpdateThunk(owner, HostStageUpdateAdapter);
}

int __fastcall HostStageDrawCallback(void* owner) {
	g_report.draw_ticks += 1;
	return StageTask_ClearCameraOnIdle((const StageContext*)owner, g_camera_words);
}

// In retail (32-bit) the StageTaskNode handed to StageContext_Enter and the
// SchedulerCallback in the run lists are the same 0x24-byte object. With
// 64-bit host pointers the two layouts no longer overlay (Enter writing
// node->context/reserved words would corrupt the callback list node), so
// the host keeps them separate: the stage code owns a real StageTaskNode
// and the scheduler runs a paired SchedulerCallback whose owner is the
// StageContext, exactly what the 0x004187C0/0x004187D0 thunks expect.
StageTaskNode g_stage_task_nodes[2];
SchedulerCallback* g_task_callbacks[2] = { 0, 0 };

StageTaskNode* HostCreateTask(int callback_index) {
	SchedulerCallback* callback = SchedulerCallback_Create(
	    callback_index == 0 ? HostStageUpdateCallback : HostStageDrawCallback);
	callback->owner = &g_context;
	g_task_callbacks[callback_index] = callback;
	std::memset(&g_stage_task_nodes[callback_index], 0,
	            sizeof(g_stage_task_nodes[callback_index]));
	Log("SchedulerCallback_Create(0x00449ED0): %s task node allocated",
	    callback_index == 0 ? "update" : "draw");
	return &g_stage_task_nodes[callback_index];
}

void HostRegisterUpdate(int priority, StageTaskNode* node, void* scheduler) {
	const int index = node == &g_stage_task_nodes[1] ? 1 : 0;
	Scheduler_RegisterPrimary(g_task_callbacks[index], priority, scheduler);
	g_report.update_task_registered = 1;
	Log("stage update task registered on the primary list "
	    "(Scheduler_RegisterPrimary 0x00449AE0, priority %d)", priority);
}

void HostRegisterDraw(int priority, StageTaskNode* node, void* scheduler) {
	const int index = node == &g_stage_task_nodes[0] ? 0 : 1;
	Scheduler_RegisterSecondary(g_task_callbacks[index], priority, scheduler);
	g_report.draw_task_registered = 1;
	Log("stage draw task registered on the secondary list "
	    "(Scheduler_RegisterSecondary 0x00449B70, priority %d)", priority);
}

// -----------------------------------------------------------------------------
// StageUpdateEnv edges (0x00418190 environment)
// -----------------------------------------------------------------------------
void HostEnterTransitionLock() {
	D3DResourceWorker_Stop();
}
// Retail 0x00404450 re-arms the bullet manager's three scheduler nodes and
// re-registers every sprite in every script bank. The host owns no parsed
// sprite banks yet, so bank_count is zero and only the node re-arm and cursor
// rewind run - which is exactly what the recovered body does for an empty
// bank table.
short g_bullet_bank_count;

void HostRegisterBulletSprite(void* pool) { (void)pool; }

void HostActivateBullets() {
	if (g_bullet_pool_slot == 0) {
		Log("BulletManager_ActivateSprites(0x00404450) skipped: no pool");
		return;
	}
	unsigned char* pool = static_cast<unsigned char*>(g_bullet_pool_slot);
	SchedulerCallback* update =
	    *reinterpret_cast<SchedulerCallback**>(pool + 8);
	SchedulerCallback* draw =
	    *reinterpret_cast<SchedulerCallback**>(pool + 0xC);
	if (update == 0 || draw == 0) {
		Log("BulletManager_ActivateSprites(0x00404450) skipped: pool "
		    "callbacks are not registered");
		return;
	}
	// Retail's overlay node lives at +0x2A40; the host pool has no third
	// node, so the draw node stands in for it and is re-armed twice rather
	// than letting the recovered body write through a null pointer.
	BulletHost host = {};
	host.bank_count = &g_bullet_bank_count;
	host.banks = 0;
	host.update = reinterpret_cast<BulletSchedulerNode*>(&update->flags);
	host.draw = reinterpret_cast<BulletSchedulerNode*>(&draw->flags);
	host.overlay = host.draw;
	host.sprite_pool = pool + 0x178;
	host.pool_base = pool + 0x60;
	BulletManager_ActivateSprites(&host, HostRegisterBulletSprite);
	*reinterpret_cast<void**>(pool + 0x10) = host.cursor;
	Log("BulletManager_ActivateSprites(0x00404450): scheduler nodes re-armed "
	    "(update flags 0x%X, draw flags 0x%X), cursor rewound to the pool base",
	    update->flags, draw->flags);
}
void HostArmPlayerTimer() {
	PlayerManager_ArmIntroTimer(g_player_manager, 0);
}
void HostStartPlayerMode() {
	PlayerManager_StartMode(g_player_manager);
}
// Retail 0x00409E50 resolves an animation handle through 0x004491C0 against
// the global game-state manager and marks the object plus its children.
// AnimationObject and AnmObject are two headers over the same retail record;
// the resolver bridges them.
AnmObject* HostResolveAnmHandle(uint32_t handle) {
	if (g_pGameStateManager == 0)
		return 0;
	return reinterpret_cast<AnmObject*>(
	    AnimationManager_Find(g_pGameStateManager, static_cast<int>(handle)));
}

// The two handle slots retail clears alongside the game thread's +0x89A4
// word. They stay zero until a stage animation claims them, and a zero
// handle resolves to nothing - the same no-op retail performs.
uint32_t g_thread_timer_handles[2];

void HostResetThreadTimer(int index) {
	if (index < 0 || index > 1)
		return;
	Anm_MarkHandleAndChildren(&g_thread_timer_handles[index],
	                          HostResolveAnmHandle);
	Log("Anm_MarkHandleAndChildren(0x00409E50): thread timer slot %d "
	    "(handle %u) marked", index, g_thread_timer_handles[index]);
}
void HostClearThreadPending() { g_thread_pending = 0; }
void HostStopPlayerRuntime() {
	if (g_bullet_pool_slot == 0)
		return;
	unsigned char* manager =
	    static_cast<unsigned char*>(g_bullet_pool_slot);
	auto retire_resource = [](void*, void* resource) {
		if (g_pGameStateManager != 0 && resource != 0)
			AnimationManager_MarkResourceForRemoval(
			    g_pGameStateManager, resource);
	};
	BulletManager_ResetPool(
	    retire_resource, manager,
	    *reinterpret_cast<void**>(manager + 0x3E0B50),
	    reinterpret_cast<Word*>(manager + 0x60), 0xF82BC,
	    reinterpret_cast<void**>(manager + 0x10), manager + 0x60,
	    reinterpret_cast<unsigned short*>(manager + 0x3E07A6));
}
// Retail 0x00424D90 runs on the pause-menu owner in ESI: the active flag at
// +0x458, three embedded frame clocks at +0x460/+0x474/+0x488, and the menu
// script handle at +0x329C. The host owns the record.
PauseMenu g_pause_menu;

void HostReleasePauseScript(float* frame_scale, void* state_manager,
                            int script) {
	(void)frame_scale;
	if (state_manager == 0 || script == 0)
		return;
	// Retail 0x004492A0 sets the animation flag on the root and its children.
	AnimationManager_SetFlag(state_manager, script, 2u);
}

void HostSetLifeIconCount(int count) {
	// Retail 0x00413790 enables the first `count` records of the fixed
	// nine-record life-icon table on the item/front manager.
	if (DAT_0047770c != 0)
		Animation_SetActiveCount(
		    reinterpret_cast<void*>(
		        static_cast<uintptr_t>(DAT_0047770c)), count);
}

void HostResetStageRuntime() {
	PauseResetEnv env = {};
	env.frame_scale = &DAT_00476f78;
	env.state_manager = g_pGameStateManager;
	env.release_script = HostReleasePauseScript;
	env.play_music = HostSetLifeIconCount;   // 0x00413790(DAT_00474C70)
	env.music_track = g_globals.lives;
	PauseMenu_ResetTimers(&g_pause_menu, &env);
	Log("PauseMenu_ResetTimers(0x00424D90): active=%d, fade/cursor/slide "
	    "clocks rearmed, script handle cleared, %d life icons enabled",
	    g_pause_menu.active, env.music_track);
}

// Retail clears the effect manager's pool arena inline: 0x873A8 dwords
// starting at DAT_00477818 + 0x14.
const unsigned int kEffectArenaDwords = 0x873A8;

void HostClearStageArena() {
	if (DAT_00477818 == 0) {
		Log("stage arena clear skipped: the effect manager is not resident");
		return;
	}
	unsigned char* arena =
	    reinterpret_cast<unsigned char*>(
	        static_cast<uintptr_t>(DAT_00477818)) + 0x14;
	std::memset(arena, 0, kEffectArenaDwords * sizeof(uint32_t));
	Log("effect arena cleared: %u dwords at DAT_00477818 + 0x14",
	    kEffectArenaDwords);
}

// Retail 0x00409F90 detaches the four aux VM slots at
// g_pGameStateManager + 0x3AD090, releases every live enemy through the
// vtable, and clears the manager's counters and node active bits.
void HostReleaseEnemyVmEntry(void* context, void* vm) {
	(void)context;
	if (vm != 0)
		*reinterpret_cast<unsigned int*>(
		    static_cast<unsigned char*>(vm) + 0x35C) |= 2u;
}

void HostReleaseEnemyNode(void* context, void* enemy) {
	(void)context;
	if (enemy != 0)
		HostFreeMem(enemy);
}

void HostResetEnemyRuntime() {
	if (g_enemy_manager_slot == 0) {
		Log("EnemyManager_ReleaseLists(0x00409F90) skipped: no manager");
		return;
	}
	unsigned char* manager =
	    static_cast<unsigned char*>(g_enemy_manager_slot);
	TeardownHooks hooks = {};
	hooks.context = g_pGameStateManager;
	hooks.release = HostReleaseEnemyNode;
	hooks.release_vm_list_entry = HostReleaseEnemyVmEntry;
	ManagerNodePair nodes = {};
	SchedulerCallback* update =
	    *reinterpret_cast<SchedulerCallback**>(manager + 8);
	SchedulerCallback* draw =
	    *reinterpret_cast<SchedulerCallback**>(manager + 0xC);
	if (update != 0) nodes.update_node_flags = &update->flags;
	if (draw != 0) nodes.render_node_flags = &draw->flags;
	void* vm_slots[4] = {};
	if (g_pGameStateManager != 0)
		std::memcpy(vm_slots,
		            static_cast<unsigned char*>(g_pGameStateManager) + 0x3AD090,
		            sizeof(vm_slots));
	EnemyManager_ReleaseLists(
	    manager, &nodes, &hooks, vm_slots, 4,
	    reinterpret_cast<void**>(manager + 0x58),
	    reinterpret_cast<int*>(manager + 0x64),
	    reinterpret_cast<int*>(manager + 0x10));
	Log("EnemyManager_ReleaseLists(0x00409F90): live list drained, counters "
	    "cleared, four aux VM slots detached");
}

// Retail 0x00417770 walks the intrusive cleanup chain, runs each node's
// cleanup and hands the storage back to the allocator. The host owns the
// chain head that stage teardown appends to.
RecoveryCleanupNode* g_cleanup_chain;

void HostReleaseCleanupChain() {
	RecoveryLinkedCleanup(&g_cleanup_chain, HostFreeMem);
	Log("RecoveryLinkedCleanup(0x00417770): cleanup chain drained (head %p)",
	    (const void*)g_cleanup_chain);
}

// Retail 0x00426F70 refreshes the four effects attached to the live player
// state. The recovered body models the four handles, their per-frame state
// words and the shot/difficulty event map; the host keeps one instance and
// feeds it the live selection.
th10::gameplay_final::AttachedEffects g_attached_effects;

void HostRunAttachedEffects() {
	g_attached_effects.difficulty = g_active_difficulty;
	g_attached_effects.shot = g_globals.character;
	th10::gameplay_final::UpdateAttachedEffects(g_attached_effects,
	                                            g_report.stage_frame);
}

void* HostPoolAlloc(uint32_t size) { return HostAlloc(size); }

// Retail snapshot record size (the same 0x1C4-byte record the spell history
// uses); the highest index the capture half touches is +0x1BC.
const unsigned int kSnapshotRecordBytes = 0x1C4;

// Retail 0x0042A450 captures or restores the per-slot game-state snapshot.
// The live block is the 0x4478-byte state published at DAT_00477834 (the
// 0x00425020 allocation); the snapshots are 0x1C4-byte records.
const int kSnapshotSlotCount = 8;
unsigned char* g_slot_snapshots[kSnapshotSlotCount];
SlotSnapshotRecordSlot g_slot_records[kSnapshotSlotCount];
SlotSnapshotOwner g_slot_owner;

void HostPrepareSnapshotSlot(void* context, int slot,
                             SlotSnapshotOwner* owner) {
	(void)owner;
	// Retail 0x0042AB20 releases the indexed linked pool before the capture.
	LinkedPool_ReleaseByIndex(context, static_cast<uint32_t>(slot));
}

int HostCaptureSnapshotSummary(void* context, int slot,
                               SlotSnapshotOwner* owner) {
	(void)owner;
	// Retail 0x0042AA50 appends one pool payload and reports its pointer.
	LinkedPoolPayload* payload = LinkedPool_AllocateAndAppend(
	    static_cast<LinkedPoolManager*>(context),
	    static_cast<uint32_t>(slot), HostPoolAlloc);
	return static_cast<int>(reinterpret_cast<uintptr_t>(payload));
}

void HostRestoreSnapshotScores(void* context, unsigned char* live,
                               unsigned char* record_block) {
	(void)context;
	if (live == 0 || record_block == 0)
		return;
	int cell[2] = {};
	std::memcpy(cell, record_block, sizeof(cell));
	// Retail 0x00428E10 stores the cell pair and refreshes the four gauges.
	Boss_SetGridCell(live, cell);
}

void HostRefreshDerivedState(void* context, unsigned char* live) {
	(void)context;
	(void)live;
	// Retail 0x00426F70; see HostRefreshSidePanel for the shared body.
	HostRunAttachedEffects();
}

void HostCommitSnapshotRestore(void* context, unsigned char* live) {
	(void)context;
	(void)live;
	HostResetStageRuntime();  // retail 0x00424D90
}

void HostResetGameplayAction() {
	unsigned char* live =
	    static_cast<unsigned char*>(g_large_resource_state);
	if (live == 0) {
		Log("SlotSnapshot_Run(0x0042A450) skipped: the 0x4478-byte live "
		    "state (DAT_00477834) is not resident");
		return;
	}
	int slot = g_globals.mode;
	if (slot < 0 || slot >= kSnapshotSlotCount)
		slot = 0;
	if (g_slot_snapshots[slot] == 0) {
		g_slot_snapshots[slot] =
		    static_cast<unsigned char*>(HostAlloc(kSnapshotRecordBytes));
		if (g_slot_snapshots[slot] != 0)
			std::memset(g_slot_snapshots[slot], 0, kSnapshotRecordBytes);
		g_slot_records[slot].record = g_slot_snapshots[slot];
	}
	if (g_slot_snapshots[slot] == 0) {
		Log("SlotSnapshot_Run(0x0042A450) skipped: snapshot allocation failed");
		return;
	}

	SlotSnapshotDefaults defaults = {};
	defaults.field_0c = static_cast<unsigned int>(g_globals.score_current);
	defaults.field_10 = static_cast<unsigned short>(g_globals.bomb_fragments);
	defaults.field_14 = static_cast<unsigned int>(g_score_gauge.target_tenth);
	defaults.field_18 = static_cast<unsigned int>(g_spell_clock.clock.frame);
	defaults.field_1c = static_cast<unsigned int>(g_globals.lives);
	defaults.field_20 = static_cast<unsigned int>(g_globals.counter_474c98);
	defaults.field_1b4 = static_cast<unsigned int>(g_globals.power_474c90);
	defaults.field_1b8 = static_cast<unsigned int>(g_globals.counter_474c9c);

	SlotSnapshotEnv env = {};
	env.live = live;
	env.slot = slot;
	env.suppress_defaults = g_globals.fresh_run == 0 ? 1 : 0;
	env.shot_type = g_globals.character;
	env.shot_variant = g_globals.stage;
	env.defaults = &defaults;

	SlotSnapshotHooks hooks = {};
	hooks.context = g_stage_state;
	hooks.prepare_slot = HostPrepareSnapshotSlot;
	hooks.capture_summary = HostCaptureSnapshotSummary;
	hooks.restore_scores = HostRestoreSnapshotScores;
	hooks.refresh_derived = HostRefreshDerivedState;
	hooks.commit_restore = HostCommitSnapshotRestore;

	g_slot_owner.snapshots = g_slot_snapshots;
	g_slot_owner.records = g_slot_records;
	SlotSnapshot_Run(&g_slot_owner, &env, &hooks);
	Log("SlotSnapshot_Run(0x0042A450): mode %d, slot %d, summary 0x%X, "
	    "pending cleared", g_slot_owner.mode, g_slot_owner.active_slot,
	    g_slot_owner.summary);
}
// ---------------------------------------------------------------------------
// Stage ECL runtime. Retail spawns the stage's controlling entity with
// Entity_Spawn(params, enemy_manager, "main") (0x0040CFB0) and ticks it every
// frame through EclVm_TickChildren (0x0044FD10), whose injected tick edge is
// the core interpreter at 0x0044E1A0. The host owns the 0x1024-byte VM record
// and the owner object whose vtable slot 0 reaches ECL_VM_Dispatch.
// ---------------------------------------------------------------------------
EclCoreVm g_ecl_vm;
// Retail's owner at vm+0x1014 is the 0x2518-byte enemy entity created by
// Entity_Spawn (0x0040CFB0): its vtable sits at +0x00, the ECL interpreter is
// embedded at +0x103C, and slot 0's thunk biases `this` by that amount before
// entering the dispatcher. ECL_VM_Dispatch then reads the VM state pointer at
// biased+0x14D8, i.e. entity+0x2514. A bare vtable-only struct is not enough:
// the bias walked off the end of it.
unsigned char g_ecl_entity[0x2518];
ECLInstructionCursor g_ecl_cursor;
ECLVMState g_ecl_state;

// The owner is consumed through TWO interfaces sharing one vtable:
//   slot 0      the core interpreter's default arm - a plain function pointer
//               taking the owner explicitly (cdecl)
//   slots 1..5  ECLVariableResolver, which ecl_vm.cpp calls as C++ virtuals
//               (thiscall, `this` in ECX)
// A one-entry table made every negative operand encoding read slot 4 or 5 off
// the end of it.
//
// The variable policy behind slots 1..4 is retail's off_46D0C0 entries
// loc_411FC0 / loc_412300 / loc_412350 / loc_4126D0: 51-case switches over
// the variable ids -10000..-9950 that read the enemy entity's own fields
// (+0x1068..+0x1160, +0x23FC, +0x2482), the player object at dword_477834,
// the game object at dword_477704 and the RNG at dword_4918B0. The bridge
// instantiates none of those, so the flat storage below stands in for them
// and is NOT retail's rule set.
float g_ecl_globals[256];
int g_ecl_int_globals[256];

int __thiscall HostEclResolveInt(void*, int variable) {
	const int slot = variable < 0 ? -variable : variable;
	return slot < 256 ? g_ecl_int_globals[slot] : 0;
}
int* __thiscall HostEclResolveIntPointer(void*, int variable) {
	const int slot = variable < 0 ? -variable : variable;
	return &g_ecl_int_globals[slot < 256 ? slot : 0];
}
float __thiscall HostEclResolveFloat(void*, int variable) {
	const int slot = variable < 0 ? -variable : variable;
	return slot < 256 ? g_ecl_globals[slot] : 0.0f;
}
float* __thiscall HostEclResolveFloatPointer(void*, int variable) {
	const int slot = variable < 0 ? -variable : variable;
	return &g_ecl_globals[slot < 256 ? slot : 0];
}
// Retail slot 5 is sub_40CC50, the scalar deleting destructor: it runs the
// entity teardown (sub_40DAE0) and frees the block when bit 0 of the flag
// byte is set. The bridge owns g_ecl_entity statically, so it must never free.

void* g_ecl_owner_vtable[6];
EclCoreHooks g_ecl_hooks;
int g_ecl_started;
int g_ecl_enabled;
int g_ecl_calls;
int g_ecl_spawns;
// Retail's async spawn (0x004500D0) allocates a 0x1024 VM record and a
// 12-byte link, pushes the link at the head of the owner's child list
// (anchor +0x1030, head +0x1034) and tail-calls the call edge. The walk is
// EclVm_TickChildren (0x0044FD10, src/script/ecl_vm_children.cpp), whose
// EclOwner models exactly those three fields, so the bridge keeps the real
// intrusive list rather than a flat pool the recovered walk cannot see.
EclOwner g_ecl_child_owner;
// The VM currently being ticked: retail reads it from owner+0x04, which the
// call edge saves and restores around each dispatch.
EclCoreVm* g_ecl_active;
int g_ecl_instructions;
int g_ecl_stopped;

void HostEclReleaseChildren() {
	EclChildLink* node = g_ecl_child_owner.anchor.next;
	while (node != 0) {
		EclChildLink* next = node->next;
		std::free(node->vm);
		std::free(node);
		node = next;
	}
	g_ecl_child_owner.anchor.next = 0;
}

// Retail's loc_40E760 thunk adds 0x103C to `this` before entering the
// dispatcher, so the recovered ECL_VM_Dispatch expects the biased pointer.
int HostEclDispatchExtended(EclCoreOwner* owner) {
	(void)owner;
	// Publish the ACTIVE VM's current instruction through the retail cursor
	// the dispatcher reads, then enter it with the biased pointer retail's
	// loc_40E760 thunk produces. Retail keeps the active VM in owner+0x04 and
	// every 0x100+ opcode is dispatched against it; publishing the root VM's
	// ip unconditionally meant a spawned enemy executed the stage script's
	// instruction instead of its own, with operands read from the wrong
	// instruction entirely.
	EclCoreVm* active = g_ecl_active != 0 ? g_ecl_active : &g_ecl_vm;
	g_ecl_cursor.instruction =
	    reinterpret_cast<ECLInstruction*>(active->ip);
	g_ecl_state.cursor = &g_ecl_cursor;
	*reinterpret_cast<ECLVMState**>(g_ecl_entity + 0x2514) = &g_ecl_state;
	return ECL_VM_Dispatch(g_ecl_entity + 0x103C);
}

// Retail resolves a call target through 0x00450470 (ECL_FindScriptLabel in
// src/script/ecl_vm.cpp) against the sorted name table 0x00450220 builds from
// the SCPT container (EclNameTable_Register in src/script/ecl_name_table.cpp),
// so the bridge registers the stage script it already loaded and searches
// that table instead of re-deriving the file layout by hand.
EclTable g_ecl_table;
EclNameEnv g_ecl_name_env;
// The object 0x00450470 searches, in retail's own shape: the entry count at
// +8 and the 8-byte {name, body} table at +140. Retail hands it over as
// dword_477704[21]; the bridge fills the two fields 0x00450220 produced.
unsigned char g_ecl_label_object[0x90];

int HostEclBuildNameTable() {
	if (g_ecl_table.entries != 0) {
		std::free(g_ecl_table.entries);
		g_ecl_table.entries = 0;
	}
	std::memset(&g_ecl_table, 0, sizeof(g_ecl_table));
	std::memset(g_ecl_label_object, 0, sizeof(g_ecl_label_object));
	if (g_enemy_ecl == 0)
		return -1;
	g_ecl_name_env.allocate = [](unsigned int size) -> void* {
		return std::malloc(size);
	};
	g_ecl_name_env.release = [](void* block) { std::free(block); };
	const int status =
	    EclNameTable_Register(&g_ecl_table, g_enemy_ecl, &g_ecl_name_env);
	if (status == 0) {
		*reinterpret_cast<int*>(g_ecl_label_object + 8) =
		    g_ecl_table.total_count;
		*reinterpret_cast<EclEntry**>(g_ecl_label_object + 0x8C) =
		    g_ecl_table.entries;
	}
	Log("EclNameTable_Register(0x00450220): %d subs registered (status %d)",
	    g_ecl_table.total_count, status);
	return status;
}

// 0x00450470 returns the sub body, i.e. the ECLH header's 16 bytes already
// skipped. A body outside the loaded image is a corrupt table, not a target.
EclCoreInstruction* HostEclFindSubBody(const char* name) {
	Byte* body = static_cast<Byte*>(
	    ECL_FindScriptLabel(g_ecl_label_object, name));
	if (body == 0 || g_enemy_ecl == 0)
		return 0;
	// Retail 0x00450470 range-tests nothing: `v3 = *(a1 + 8) - 1; if (v3 < 0)
	// return 0;` and then returns *(v7 + 8 * v4 + 4) + 16 unconditionally.
	// The bounds test that used to be here was the host's, and it was also
	// off by 16 because the returned pointer already has the ECLH skip.
	return reinterpret_cast<EclCoreInstruction*>(body);
}

// Retail 0x0044DF70, reached from opcode 0x0B. For an ECL `call` the child and
// parent are the same record. Retail copies the caller's operands into the
// callee's scratch frame, pushes the return linkage, then resolves the target
// by the name stored at instruction+0x14 and plants vm+0x04 at its entry
// (0x00450470 returns the sub body, i.e. past the 16-byte ECLH header).
// Returns 0 on success; non-zero leaves vm+0x04 untouched and stops the VM.
int HostEclStartChild(EclCoreVm* child, EclCoreVm* parent, int first_argument);

// ECL global variable storage. Retail reaches negative operand encodings
// through the owner object's ECLVariableResolver vtable (slots 4/5); that
// object is the enemy entity, whose resolver the host does not implement.
// The local case below is retail's exactly; the global case uses the host
// storage declared alongside the resolver vtable above.

// Retail 0x00450070. A clear mask bit yields null and retail stores through it
// unchecked; the host refuses that store instead of faulting.
float* HostEclResolveFloatDestination(EclCoreVm* vm, unsigned int operand) {
	// Validate with integer arithmetic before any pointer is formed: the ip
	// can leave the image mid-tick when the call/ret frame protocol desyncs,
	// and a pointer-comparison guard is free to be reordered past the load
	// that faults.
	if (vm == 0 || g_enemy_ecl == 0)
		return 0;
	const uintptr_t ip_value = reinterpret_cast<uintptr_t>(vm->ip);
	const uintptr_t image = reinterpret_cast<uintptr_t>(g_enemy_ecl);
	if (ip_value < image || ip_value - image + 16 > g_enemy_ecl_size)
		return 0;
	const EclCoreInstruction* instruction = vm->ip;
	// Retail stores through a null here unchecked; a sink keeps the host from
	// faulting on a case retail never reaches with a clear mask bit.
	static float sink;
	if ((instruction->param_mask & (1u << (operand & 31))) == 0)
		return &sink;
	int encoded = 0;
	std::memcpy(&encoded, &instruction->arguments[operand], sizeof(encoded));
	float bits = 0.0f;
	std::memcpy(&bits, &encoded, sizeof(bits));
	encoded = static_cast<int>(bits);
	if (encoded >= 0) {
		const int offset = vm->locals_offset + 8 + encoded;
		if (offset < 0 || offset + 4 > 0x1000)
			return &sink;
		return reinterpret_cast<float*>(vm->scratch + offset);
	}
	const int slot = -encoded;
	if (slot < 0 || slot >= (int)(sizeof(g_ecl_globals) / sizeof(float)))
		return &sink;
	return &g_ecl_globals[slot];
}

// Retail 0x004500D0, opcodes 0x0F/0x10:
//   v3 = operator new(0x1024); v3[1026] = 0; v3[1027] = 0;
//   v5 = operator new(0xC);
//   v4[1028] = async_id; v4[1029] = owner; *v4 = 0; v4[1] = 0;
//   *((_BYTE *)v4 + 4124) = *(_BYTE *)(*(_DWORD *)(owner + 4) + 4124);
//   *v5 = v4; v5[1] = 0; v5[2] = 0;
//   v6 = *(owner + 4148);
//   if (v6) { v5[1] = v6; *(_DWORD *)(*(owner + 4148) + 8) = v5; }
//   *(owner + 4148) = v5; v5[2] = owner + 4144;
//   return sub_44DF70(v4, *(_DWORD **)(owner + 4), first_argument);
// i.e. the child is pushed at the head of the list the tick walk reads and
// the parent is the OWNER's active VM, not the spawner's record.
int HostEclSpawnChild(EclCoreOwner* owner, int async_id, int first_argument) {
	(void)owner;
	EclCoreVm* parent =
	    static_cast<EclCoreVm*>(g_ecl_child_owner.active_vm);
	if (parent == 0)
		return -1;
	EclCoreVm* child = static_cast<EclCoreVm*>(std::malloc(sizeof(*child)));
	EclChildLink* link =
	    static_cast<EclChildLink*>(std::malloc(sizeof(*link)));
	if (child == 0 || link == 0) {
		std::free(child);
		std::free(link);
		return -1;
	}
	std::memset(child, 0, sizeof(*child));
	child->owner = parent->owner;
	child->rank_mask = parent->rank_mask;   // child+0x101C
	child->async_id = async_id;             // child+0x1010
	link->vm = child;
	link->next = 0;
	link->previous = 0;
	if (g_ecl_child_owner.anchor.next != 0) {
		link->next = g_ecl_child_owner.anchor.next;
		g_ecl_child_owner.anchor.next->previous = link;
	}
	g_ecl_child_owner.anchor.next = link;
	link->previous = &g_ecl_child_owner.anchor;
	if (HostEclStartChild(child, parent, first_argument) != 0) {
		// Retail leaves the record linked and lets the walk retire it; the
		// bridge does the same so the list stays the one 0x0044FD10 owns.
		child->ip = 0;
		return -1;
	}
	g_ecl_spawns += 1;
	return 0;
}

// Retail 0x0044DF70, transcribed from the IDA listing rather than paraphrased.
// Pointer notation there is _DWORD*: a1[1026] is child+0x1008 (scratch_top),
// and (char*)a1 + X + 8 is child->scratch + X, because scratch starts at
// child+0x08.  For an ECL `call` a1 == a2 == the same record.
int HostEclStartChild(EclCoreVm* child, EclCoreVm* parent, int first_argument) {
	if (child == 0 || parent == 0 || parent->ip == 0)
		return -1;
	const EclCoreInstruction* instruction = parent->ip;      // *v3
	const unsigned char* parent_bytes =
	    reinterpret_cast<const unsigned char*>(instruction);
	if (instruction->size <= 20)
		return -1;

	const int old_top = child->scratch_top;                  // v5 = a1[1026]
	const int frame_base = old_top == 0 ? 12 : old_top + 8;  // v7

	// --- argument copy: operands [first_argument+1, param_count) ----------
	int arg_cursor = 0;                                      // v6
	std::memcpy(&arg_cursor, parent_bytes + 16, sizeof(arg_cursor));
	arg_cursor += 4 * first_argument + 4;
	int value_cursor = arg_cursor + 4;                       // v9 / i
	int arg_index = first_argument + 1;                      // v8
	const int param_count = parent_bytes[11];                // *(*v3 + 11)
	unsigned char* destination = child->scratch + frame_base;  // v26
	while (arg_index < param_count &&
	       destination + 4 <= child->scratch + 0x1000 &&
	       17 + arg_cursor < (int)instruction->size) {
		const unsigned char source_tag = parent_bytes[16 + arg_cursor];
		const unsigned char dest_tag = parent_bytes[17 + arg_cursor];
		const unsigned char* word =
		    parent_bytes + 16 + 4 * (value_cursor >> 2);
		if (source_tag == 'f' || source_tag == 'g') {
			float raw = 0.0f;
			std::memcpy(&raw, word, sizeof(raw));
			const float resolved =
			    ECL_ResolveFloatValue(parent, arg_index, raw);
			if (dest_tag == 'f')
				std::memcpy(destination, &resolved, sizeof(resolved));
			else {
				const int truncated = (int)resolved;
				std::memcpy(destination, &truncated, sizeof(truncated));
			}
		} else {
			int raw = 0;
			std::memcpy(&raw, word, sizeof(raw));
			const int resolved = ECL_ResolveIntValue(parent, arg_index, raw);
			if (dest_tag == 'f') {
				const float widened = (float)resolved;
				std::memcpy(destination, &widened, sizeof(widened));
			} else
				std::memcpy(destination, &resolved, sizeof(resolved));
		}
		destination += 4;
		++arg_index;
		arg_cursor += 8;
		value_cursor += 8;
	}

	// --- frame linkage ----------------------------------------------------
	if (old_top == 0) {
		// Fresh record: a1[1026]=4; a1[3]=0; +=4; then scratch[8]=0; +=4.
		child->scratch_top = 4;
		*reinterpret_cast<int*>(child->scratch + 4) = 0;
		child->scratch_top = 8;
		if (child->scratch_top + 4 < 0x1000) {
			*reinterpret_cast<int*>(child->scratch + child->scratch_top) = 0;
			child->scratch_top += 4;
		}
	} else {
		// v15/v24: pop one word, then rewind to old_top and write it back at
		// scratch[old_top - 4]. Omitting this write was the desync.
		int popped = 0;                                       // v24
		const int probe = child->scratch_top - 4;             // v15
		if (probe >= 0) {
			child->scratch_top = probe;
			std::memcpy(&popped, child->scratch + probe, sizeof(popped));
		}
		child->scratch_top = old_top;                         // a1[1026] = v5
		if (old_top >= 4)
			std::memcpy(child->scratch + old_top - 4, &popped, sizeof(popped));
		if (child->scratch_top + 4 < 0x1000) {                // push *a2 (clock bits)
			std::memcpy(child->scratch + child->scratch_top,
			            &parent->time, sizeof(parent->time));
			child->scratch_top += 4;
		}
		if (child->scratch_top + 4 < 0x1000) {                // push *v3 (caller ip)
			std::memcpy(child->scratch + child->scratch_top,
			            &parent->ip, sizeof(parent->ip));
			child->scratch_top += 4;
		}
	}

	// --- retarget: owner->active_vm is set to the child for the lookup ----
	const char* target = reinterpret_cast<const char*>(parent_bytes + 20);
	EclCoreInstruction* body = HostEclFindSubBody(target);
	if (body == 0) {
		// Retail's failure tail: the CALLER's ip is cleared and -1 returned.
		Log("ecl call: sub \"%s\" unresolved; stopping caller", target);
		parent->ip = 0;
		return -1;
	}
	child->ip = body;
	child->time = 0.0f;                                       // **(v21 + 4) = 0
	g_ecl_calls += 1;
	return 0;
}

void HostStartMainEcl() {
	if (!g_ecl_enabled) {
		Log("main ECL start (0x0040CFB0): interpreter present but not armed; "
		    "pass --ecl to run stage01.ecl through EclVm_TickCore");
		return;
	}
	if (g_enemy_ecl == 0 || g_enemy_ecl_sub_offsets == 0 ||
	    g_enemy_ecl_sub_count == 0) {
		Log("main ECL start (0x0040CFB0) skipped: stage01.ecl is not resident");
		return;
	}
	if (HostEclBuildNameTable() != 0) {
		Log("main ECL start skipped: 0x00450220 rejected stage01.ecl");
		return;
	}
	HostEclReleaseChildren();
	// The entry point is the sub named "main", resolved exactly the way
	// retail's 0x00450500 resolves an interpreter's entry label.
	EclCoreInstruction* entry_body = HostEclFindSubBody("main");
	if (entry_body == 0) {
		Log("main ECL start skipped: no sub named \"main\"");
		return;
	}
	std::memset(&g_ecl_vm, 0, sizeof(g_ecl_vm));
	std::memset(g_ecl_entity, 0, sizeof(g_ecl_entity));
	// Retail off_46D0C0 order (0x0046D0C0): dispatch, int, int address,
	// float, float address, destructor.
	g_ecl_owner_vtable[0] = reinterpret_cast<void*>(HostEclDispatchExtended);
	g_ecl_owner_vtable[1] = reinterpret_cast<void*>(HostEclResolveInt);
	g_ecl_owner_vtable[2] = reinterpret_cast<void*>(HostEclResolveIntPointer);
	g_ecl_owner_vtable[3] = reinterpret_cast<void*>(HostEclResolveFloat);
	g_ecl_owner_vtable[4] = reinterpret_cast<void*>(HostEclResolveFloatPointer);
	// Slot 5 is retail's scalar deleting destructor sub_40CC50, which runs
	// sub_40DAE0 and then frees the block when bit 0 of the flag byte is set.
	// The bridge owns g_ecl_entity as static storage and never destroys it, so
	// nothing reaches this slot; it is left null rather than pointed at a body
	// that performs none of that work.
	g_ecl_owner_vtable[5] = 0;
	*reinterpret_cast<void***>(g_ecl_entity) = g_ecl_owner_vtable;
	// The ECLH block is 16 bytes; 0x00450470 already skipped it.
	g_ecl_vm.ip = entry_body;
	g_ecl_vm.owner = reinterpret_cast<EclCoreOwner*>(g_ecl_entity);
	// Retail 0x0040CFB0 derives the rank mask when it constructs the enemy
	// entity: *((_BYTE *)entity + 4132) = 1 << dword_474C74, and 4132 is
	// 0x1024 - the rank byte of the VM embedded at entity+8, i.e. vm+0x101C.
	// dword_474C74 is the difficulty word StageGlobals mirrors.
	g_ecl_vm.rank_mask =
	    // Retail is `*((_BYTE *)v5 + 4132) = 1 << dword_474C74` with no mask
	    // (th10.exe.c:21001); the & 7 was an introduced value decision.
	    static_cast<unsigned char>(1 << g_globals.difficulty);
	g_ecl_hooks = EclCoreHooks{};
	g_ecl_started = 1;
	g_ecl_hooks.start_child = HostEclStartChild;
	g_ecl_hooks.spawn_child = HostEclSpawnChild;
	g_ecl_hooks.resolve_float_destination = HostEclResolveFloatDestination;
	// Retail 0x0044FD10 walks the anchor at owner+0x1030 first, and that
	// anchor's VM is the interpreter's embedded root at owner+8.
	g_ecl_child_owner.active_vm = &g_ecl_vm;
	g_ecl_child_owner.root_vm = &g_ecl_vm;
	g_ecl_child_owner.anchor.vm = &g_ecl_vm;
	g_ecl_child_owner.anchor.next = 0;
	g_ecl_child_owner.anchor.previous = 0;
	Log("EclVm_TickCore(0x0044E1A0) armed on stage01.ecl \"main\" "
	    "(body %p, %d subs, rank mask 0x%02X)", (const void*)entry_body,
	    g_ecl_table.total_count, g_ecl_vm.rank_mask);
}

// One frame of the stage script, the tick edge EclVm_TickChildren injects.
// A VM whose ip is not inside the loaded ECL image means the call/ret frame
// protocol desynced. Retiring it loudly beats dereferencing a wild pointer,
// and it keeps the failure visible instead of turning into a page fault.
bool HostEclVmSane(const EclCoreVm* vm) {
	if (vm->ip == 0)
		return false;
	const unsigned char* ip = reinterpret_cast<const unsigned char*>(vm->ip);
	return ip >= g_enemy_ecl && ip + 16 <= g_enemy_ecl + g_enemy_ecl_size;
}

// Retail 0x0044FD10 calls sub_44E1A0(node->vm, delta) after publishing that
// VM through owner+0x04; the recovered walk keeps the publish and injects the
// tick, so this is the injected edge for both the anchor's root VM and every
// child. Returning non-zero is retail's "this VM is finished": the walk aborts
// the frame for the anchor and frees/unlinks the node for a child.
int HostEclTickListEntry(EclOwner* owner, float delta) {
	EclCoreVm* vm = static_cast<EclCoreVm*>(owner->active_vm);
	if (vm == 0)
		return -1;
	if (!HostEclVmSane(vm)) {
		Log("ecl: VM %p ip left the script image (%p); retiring",
		    (const void*)vm, (const void*)vm->ip);
		return -1;
	}
	g_ecl_active = vm;
	const EclCoreInstruction* before = vm->ip;
	const int result = EclVm_TickCore(vm, delta, &g_ecl_hooks);
	if (vm->ip != before)
		g_ecl_instructions += 1;
	return result;
}

// Retail's j__free. The anchor's VM is the interpreter's embedded root and
// the walk never hands it here, but the guard keeps a modelling slip from
// turning into a free of static storage.
void HostEclFreeChild(void* memory) {
	if (memory != 0 && memory != &g_ecl_vm)
		std::free(memory);
}

int HostEclLiveChildren() {
	int live = 0;
	for (EclChildLink* node = g_ecl_child_owner.anchor.next; node != 0;
	     node = node->next)
		live += 1;
	return live;
}

void HostTickStageEcl() {
	if (!g_ecl_started || g_ecl_stopped)
		return;
	// The whole per-frame walk is retail 0x0044FD10: anchor first (a failing
	// anchor aborts the frame with -1), then every linked child, then the
	// active-VM slot is restored to the interpreter's embedded root.
	const int result = EclVm_TickChildren(&g_ecl_child_owner, 1.0f,
	                                      HostEclTickListEntry,
	                                      HostEclFreeChild);
	g_ecl_active = static_cast<EclCoreVm*>(g_ecl_child_owner.active_vm);
	if (result != 0) {
		g_ecl_stopped = 1;
		Log("EclVm_TickChildren(0x0044FD10): stage script finished after %d "
		    "advances", g_ecl_instructions);
	}
}
// Retail 0x00413BC0 rebuilds the front/HUD state: the update and draw tasks,
// the nine life icons, the three power digits, and the animation list whose
// last two entries are linked together.
th10::player_front::Front g_front_state;

void HostInitializeStageRuntime() {
	th10::player_front::FrontInput input;
	input.lives = g_globals.lives;
	input.counter = g_globals.power_seed;
	input.mode = g_globals.mode;
	input.stage = g_globals.stage;  // dword_474C6C; InitializeFront ignores it
	input.difficulty = g_active_difficulty;
	input.special = (g_globals.game_flags & 8u) != 0;
	input.extra_overlay = (g_globals.game_flags & 0x10u) != 0;
	// Retail 0x00413BC0 pushes animation 0x4F only when all three of its
	// gates are clear (th10.exe.c:23602):
	//   if (dword_474C7C != 1 || *((_DWORD *)dword_477810 + 23) || dword_474C90)
	// dword_474C7C is the stage INDEX - off_474744[dword_474C7C] is what
	// indexes the "St1".."St6" labels - so the test is "we are on stage 1",
	// not "stage 1 was cleared", and `> 1` had it inverted. dword_477810 is a
	// manager the bridge never creates; its word is taken as clear, which is
	// stated here rather than folded into the expression.
	input.stage_one_clear = DAT_00474c7c == 1 && DAT_00474c90 == 0;
	th10::player_front::InitializeFront(g_front_state, input);
	Log("InitializeFront(0x00413BC0): %d life icons, digits %d/%d/%d, "
	    "%d animations, linked pair %d/%d",
	    static_cast<int>(std::count(g_front_state.lives.begin(),
	                                g_front_state.lives.end(), true)),
	    g_front_state.digits[0], g_front_state.digits[1],
	    g_front_state.digits[2],
	    static_cast<int>(g_front_state.animations.size()),
	    g_front_state.linked_a, g_front_state.linked_b);
}

void HostRefreshSidePanel(StageUpdateTaskPair* pair) {
	(void)pair;
	HostRunAttachedEffects();
	Log("UpdateAttachedEffects(0x00426F70): counter %d, %d events published",
	    g_attached_effects.counter,
	    static_cast<int>(g_attached_effects.events.size()));
}
// Retail 0x00420B10's injected cue edge is sub_43E460(&unk_492590, name,
// mode, value) - the same animation-manager resource registration the host
// already drives for the delayed stage effect.
void HostPlayStageCue(void* context, const char* name, int32_t mode,
                      uint32_t value) {
	AnimationManager_RegisterResource(context, 0, name, mode,
	                                  static_cast<int>(value));
}

void HostStartStageMusic() {
	// Retail 0x00418190 calls sub_420B10(0, *(dword_477848 + 36)): slot 0
	// is the stage BGM cue and the second argument is the stage row's
	// music index. The Stage 1 row (dword_477848 entry 1, 48-byte stride)
	// carries +36 = 1 and +40 = 2 in the retail image at 0x004747B8.
	if (g_pGameStateManager == 0) {
		Log("Sound_PlayDummy(0x00420B10) skipped: no animation manager");
		return;
	}
	Sound_PlayDummy(g_pGameStateManager, 0, kStageOneMusicIndex,
	                HostPlayStageCue);
	Log("Sound_PlayDummy(0x00420B10): stage cue slot 0, music index %d "
	    "marked heard; track %s @ %u Hz", kStageOneMusicIndex,
	    g_report.bgm_track[0] != 0 ? g_report.bgm_track : "(no record)",
	    g_report.bgm_rate);
}
void HostCreateDelayedStageEffect(int variant) {
	// Retail FUN_0043e460(manager, "dummy", 3|4, 0): install the dummy record
	// in the first free animation-manager slot.
	if (g_pGameStateManager == 0) {
		Log("AnimationManager_RegisterResource(0x0043E460) skipped: no "
		    "animation manager");
		return;
	}
	AnimationManager_RegisterResource(g_pGameStateManager, 0, "dummy",
	                                  variant, 0);
	Log("AnimationManager_RegisterResource(0x0043E460): dummy record "
	    "variant %d installed", variant);
}
void HostResetPlayerSpawnUpdate(StageContext* context) {
	if (context != 0) HostResetPlayerSpawn(context->spawn, 0);
}
int HostPlayerRequestsDestroy(void* player) { (void)player; return 0; }
void HostDestroyPlayer(void* player) { (void)player; }
void HostFreePlayer(void* player) { std::free(player); }
// Retail FUN_0043c8b0(5, 0x3c, 0, 0, 0) constructs the 0x44-byte overlay text
// manager and forwards the five creation arguments to its initializer
// (0x0043C970).
void* g_transition_overlay;

void HostInitializeTransitionOverlay(void* manager) {
	AsciiManagerInitHooks hooks = {};
	hooks.context = g_pGameStateManager;
	hooks.frame_speed = &DAT_00476f78;
	AsciiManager_Initialize(static_cast<AsciiManagerInitState*>(manager),
	                        g_pGameStateManager, 5, 0x3c, 0, 0, 0, &hooks);
}

void HostSpawnTransitionEffect() {
	if (g_transition_overlay != 0) {
		HostFreeMem(g_transition_overlay);
		g_transition_overlay = 0;
	}
	g_transition_overlay =
	    AsciiManager_Create(HostAlloc, HostInitializeTransitionOverlay);
	Log("AsciiManager_Create(0x0043C8B0): overlay text manager %s "
	    "(mode 5, argument 0x3C)",
	    g_transition_overlay != 0 ? "constructed" : "FAILED");
}

// Retail 0x0040AC90 stores the requested input mode on the input state,
// honoring the forced-mode bit at +0x3CC. The host owns the block.
unsigned char g_input_mode_state[0x3D0];

void HostRunTransitionAction() {
	SetInputMode(g_input_mode_state, 4);
	Log("SetInputMode(0x0040AC90): input mode %u published",
	    *reinterpret_cast<const unsigned int*>(g_input_mode_state + 0x390));
}
void HostTickGame() {}

// Retail's counter-decay arm is sub_44BF40(&dword_474C54, -1.0), i.e. the
// five-word FrameTimer embedded at &dword_474C40 + 0x14. The timer is only
// reached when dword_474C58 is positive, which in the retail image it is not;
// the speed-pointer test keeps a never-armed timer from being dereferenced.
void HostDecayCounterTimer(float delta) {
	// sub_418A00 tail-calls sub_44BF40(result + 5, -1.0), which dereferences
	// *(float **)(a1 + 12) unconditionally (th10.exe.c:67618). There is no
	// speed-pointer test in retail, so there is none here either.
	FrameTimer* timer = reinterpret_cast<FrameTimer*>(DAT_00474c54);
	FrameTimer_Advance(timer, delta);
}

void HostUpdateScoreThreshold() {
	// Retail 0x00418190 tail: sub_418A00(&dword_474C40). The argument is
	// the retail globals block itself, which the all-source image links
	// from the original .data section, so the call site is retail's.
	Recovery_DecayCounter(DAT_00474c40, HostDecayCounterTimer);
}

void HostTickStageTimer(StageContext* context) {
	// Retail 0x00418190 tail: sub_404ED0(context + 16). The five words at
	// context+0x10 are the FrameTimer that 0x00405410 armed during entry
	// (previous, current, elapsed, &flt_476F78, flags).
	FrameTimer* timer = reinterpret_cast<FrameTimer*>(context->spawn);
	FrameTimer_Tick(timer);
	g_report.stage_frame = timer->current;
	g_runtime_view.stage_frame = timer->current;
}

uint32_t ReadTimelineWord(size_t offset) {
	uint32_t value = 0;
	if (offset <= g_std_view.size &&
	    sizeof(value) <= g_std_view.size - offset)
		std::memcpy(&value, g_std_view.data + offset, sizeof(value));
	return value;
}

float ReadTimelineFloat(size_t offset) {
	const uint32_t bits = ReadTimelineWord(offset);
	float value = 0.0f;
	std::memcpy(&value, &bits, sizeof(value));
	return value;
}

void StartCameraInterpolation(Interp3F* interpolation, float current[3],
                              const StageTimelineEvent& event) {
	std::memset(interpolation, 0, sizeof(*interpolation));
	for (int axis = 0; axis < 3; ++axis) {
		interpolation->position[axis] = current[axis];
		interpolation->start[axis] = current[axis];
		interpolation->target[axis] =
		    ReadTimelineFloat(event.argument_offset + 8 + axis * 4);
	}
	interpolation->duration =
	    static_cast<int>(ReadTimelineWord(event.argument_offset));
	interpolation->mode =
	    static_cast<int>(ReadTimelineWord(event.argument_offset + 4));
	interpolation->speed = 1.0f;
}

void ApplyTimelineEvent(const StageTimelineEvent& event) {
	switch (event.opcode) {
	case 2:
		for (int axis = 0; axis < 3; ++axis)
			g_stage_camera.eye[axis] =
			    ReadTimelineFloat(event.argument_offset + axis * 4);
		g_eye_interpolating = false;
		break;
	case 3:
		StartCameraInterpolation(
		    &g_eye_interpolator, g_stage_camera.eye, event);
		g_eye_interpolating = g_eye_interpolator.duration > 0;
		break;
	case 4:
		for (int axis = 0; axis < 3; ++axis)
			g_stage_camera.target[axis] =
			    ReadTimelineFloat(event.argument_offset + axis * 4);
		g_target_interpolating = false;
		break;
	case 5:
		StartCameraInterpolation(
		    &g_target_interpolator, g_stage_camera.target, event);
		g_target_interpolating = g_target_interpolator.duration > 0;
		break;
	case 6:
		for (int axis = 0; axis < 3; ++axis)
			g_stage_camera.up[axis] =
			    ReadTimelineFloat(event.argument_offset + axis * 4);
		break;
	case 7:
		g_stage_camera.field_of_view =
		    ReadTimelineFloat(event.argument_offset);
		break;
	default:
		break;
	}
}

void TickStageCamera() {
	if (g_eye_interpolating) {
		g_eye_interpolating = Interp3F_Tick(&g_eye_interpolator) != 0;
		for (int axis = 0; axis < 3; ++axis)
			g_stage_camera.eye[axis] = g_eye_interpolator.position[axis];
	}
	if (g_target_interpolating) {
		g_target_interpolating =
		    Interp3F_Tick(&g_target_interpolator) != 0;
		for (int axis = 0; axis < 3; ++axis)
			g_stage_camera.target[axis] =
			    g_target_interpolator.position[axis];
	}
}

void BuildUpdateEnv() {
	std::memset(&g_update_env, 0, sizeof(g_update_env));
	g_update_env.globals = &g_update_globals;
	g_task_pairs[0].update = g_context.update_task;
	g_task_pairs[0].draw = g_context.draw_task;
	g_update_env.task_pairs = g_task_pairs;
	g_update_env.task_pair_count = 1;
	g_update_env.player_extra_task = 0;
	g_update_env.enter_transition_lock = HostEnterTransitionLock;
	g_update_env.activate_bullets = HostActivateBullets;
	g_update_env.arm_player_timer = HostArmPlayerTimer;
	g_update_env.start_player_mode = HostStartPlayerMode;
	g_update_env.reset_thread_timer = HostResetThreadTimer;
	g_update_env.clear_thread_pending = HostClearThreadPending;
	g_update_env.stop_player_runtime = HostStopPlayerRuntime;
	g_update_env.reset_stage_runtime = HostResetStageRuntime;
	g_update_env.clear_stage_arena = HostClearStageArena;
	g_update_env.reset_enemy_runtime = HostResetEnemyRuntime;
	g_update_env.release_cleanup_chain = HostReleaseCleanupChain;
	g_update_env.reset_gameplay_action = HostResetGameplayAction;
	g_update_env.start_main_ecl = HostStartMainEcl;
	g_update_env.initialize_stage_runtime = HostInitializeStageRuntime;
	g_update_env.refresh_side_panel = HostRefreshSidePanel;
	g_update_env.start_stage_music = HostStartStageMusic;
	g_update_env.create_delayed_stage_effect = HostCreateDelayedStageEffect;
	g_update_env.reset_player_spawn = HostResetPlayerSpawnUpdate;
	g_update_env.player_requests_destroy = HostPlayerRequestsDestroy;
	g_update_env.destroy_player = HostDestroyPlayer;
	g_update_env.free_player = HostFreePlayer;
	g_update_env.spawn_transition_effect = HostSpawnTransitionEffect;
	g_update_env.run_transition_action = HostRunTransitionAction;
	g_update_env.tick_game = HostTickGame;
	g_update_env.update_score_threshold = HostUpdateScoreThreshold;
	g_update_env.tick_stage_timer = HostTickStageTimer;
}

// -----------------------------------------------------------------------------
// StageContext_Enter driver
// -----------------------------------------------------------------------------
void HostRunStageEntry() {
	std::memset(&g_context, 0, sizeof(g_context));
	g_context.flags = 4; // entering bit (bit 2), as set by the loading owner

	std::memset(&g_entry_env, 0, sizeof(g_entry_env));
	g_entry_env.globals = &g_globals;
	g_entry_env.score_file = g_score_file;
	g_entry_env.stage_record = &g_stage_record;
	g_entry_env.stage_descriptor = g_stage_descriptor;
	g_entry_env.scheduler = g_scheduler_device;
	g_entry_env.anm_slots = g_anm_slots;
	g_entry_env.game = 0;
	g_entry_env.spell_practice_state = g_spell_practice_state;
	g_entry_env.key_buffer = 0;
	g_entry_env.sleep = HostSleep;
	g_entry_env.seed_extend_threshold = HostSeedExtendThreshold;
	g_entry_env.create_task = HostCreateTask;
	g_entry_env.register_update = HostRegisterUpdate;
	g_entry_env.register_draw = HostRegisterDraw;
	g_entry_env.replay_reset = HostReplayReset;
	g_entry_env.replay_seed = HostReplaySeed;
	g_entry_env.load_stage_script = HostLoadStageScript;
	g_entry_env.init_side_panel = HostInitSidePanel;
	g_entry_env.init_414830 = HostInitItemManager;
	g_entry_env.init_425020 = HostInitLargeResource;
	g_entry_env.init_406060 = HostInitBulletPool;
	g_entry_env.init_41aed0 = HostInitEffectManager;
	g_entry_env.create_score_manager = HostCreateScoreManager;
	g_entry_env.init_422360 = HostInitTimerState;
	g_entry_env.init_419090 = HostInitResourceState;
	g_entry_env.create_stage_state = HostCreateStageState;
	g_entry_env.spell_practice_reset = HostSpellPracticeReset;
	g_entry_env.create_enemy_manager = HostCreateEnemyManager;
	g_entry_env.create_bullet_manager = HostCreateBulletManager;
	g_entry_env.init_4056b0 = HostInitFixedState;
	g_entry_env.init_408c90 = HostInitPlayerManager;
	g_entry_env.music_reset = HostMusicReset;
	g_entry_env.music_load = HostMusicLoad;
	g_entry_env.reset_player_spawn = HostResetPlayerSpawn;
	g_entry_env.release_overlay_anm = HostReleaseOverlayAnm;
	g_entry_env.release_pending_anm = HostReleasePendingAnm;
	g_entry_env.request_callback_removal = HostRequestCallbackRemoval;

	g_report.enter_attempted = 1;
	Log("StageContext_Enter(0x00417870): running the construction chain "
	    "(stage %d, script %s)", g_stage_record.number,
	    g_stage_record.script_name);
	const int result = StageContext_Enter(&g_context, &g_entry_env);
	g_report.enter_result = result;
	if (result == 0) {
		g_update_globals.player = g_fixed_state;
		// Enter creates both task nodes disarmed (flags &= ~2u); in retail the
		// loading owner arms them once resource streaming completes. The host
		// loads synchronously inside Enter, so arm both nodes here and let
		// HostStage_RunFrames mirror the arm bit into the scheduler callbacks.
		if (g_context.update_task != 0)
			g_context.update_task->flags |= 2u;
		if (g_context.draw_task != 0)
			g_context.draw_task->flags |= 2u;
		BuildUpdateEnv();
		g_runtime_view.script = &g_stage_script;
		g_runtime_view.std_data =
		    reinterpret_cast<const unsigned char*>(g_stage_script.buffer);
		g_runtime_view.std_size = g_stage_script.cached_size;
		g_runtime_view.companion_anm_data = g_companion_anm;
		g_runtime_view.companion_anm_size = g_companion_anm_size;
		g_runtime_view.std_view = &g_std_view;
		g_runtime_view.timeline_view = &g_timeline_view;
		g_runtime_view.camera = &g_stage_camera;
		g_runtime_view.context = &g_context;
		g_runtime_view.camera_words = g_camera_words;
		g_runtime_view.stage_frame = 0;
		Log("StageContext_Enter(0x00417870) returned 0: %d factory wrappers, "
		    "%d failures, update/draw tasks registered",
		    g_report.factories_created, g_report.factory_failures);
	} else {
		Log("StageContext_Enter(0x00417870) FAILED (%d) after %d factories "
		    "(%d failures)", result, g_report.factories_created,
		    g_report.factory_failures);
	}
}

// -----------------------------------------------------------------------------
// GameModeEnv edges
// -----------------------------------------------------------------------------
void HostModeEnterCritical() {}
void HostModeLeaveCritical() {}
void* HostModeCreateLoadingOwner() { return &g_context; }
void HostModeShowFailure() { Log("mode edge: show failure"); }
void HostModeFinalizeFailure() { Log("mode edge: finalize failure"); }
void HostModeLeaveGameplay() {
	g_report.leave_gameplay_fired = 1;
	Log("GameMode_ApplyRequested(0x004218D0): menu -> gameplay dispatched "
	    "through the leave_gameplay edge; entering the stage construction chain");
	HostRunStageEntry();
}
void HostModeEnterGameplay() { Log("mode edge: enter gameplay"); }
void HostModeReleaseBullets() { Log("mode edge: release bullets"); }
void HostModePrepareRestart() { Log("mode edge: prepare restart"); }
void HostModePrepareCleanup() { Log("mode edge: prepare cleanup"); }
void HostModeCommitMenu() { Log("mode edge: commit menu"); }

} // namespace

// -----------------------------------------------------------------------------
// Public bridge API
// -----------------------------------------------------------------------------
void HostStage_SetArchiveAvailable(int available) {
	g_report.archive_available = available;
}

int HostStage_ConfirmWeapon(int character, int weapon, int difficulty) {
	const int archive_available = g_report.archive_available;
	std::memset(&g_report, 0, sizeof(g_report));
	std::memset(&g_runtime_view, 0, sizeof(g_runtime_view));
	std::memset(&g_std_view, 0, sizeof(g_std_view));
	std::memset(&g_timeline_view, 0, sizeof(g_timeline_view));
	std::memset(&g_stage_camera, 0, sizeof(g_stage_camera));
	// Retail 0x004216F0 seeds the stage/background camera block at
	// 0x00491D7C: position (0, 0, 1000) - flt_491D84 = 1000.0 - looking at
	// the origin with up = (0, 1, 0) - dword_491D98 = 1065353216 (1.0f) -
	// and dword_491DC4 = 1057360530, the raw bit pattern 0x3F060A92 (pi/6).
	// The 0.62831855f the bridge used to plant here is not in the image.
	g_stage_camera.eye[2] = 1000.0f;
	g_stage_camera.up[1] = 1.0f;
	{
		const unsigned int fov_bits = 0x3F060A92u;
		std::memcpy(&g_stage_camera.field_of_view, &fov_bits,
		            sizeof(g_stage_camera.field_of_view));
	}
	std::memset(&g_eye_interpolator, 0, sizeof(g_eye_interpolator));
	std::memset(&g_target_interpolator, 0, sizeof(g_target_interpolator));
	g_eye_interpolating = false;
	g_target_interpolating = false;
	g_companion_anm = 0;
	g_companion_anm_size = 0;
	g_report.archive_available = archive_available;
	g_owned_allocation_count = 0;
	// The scheduler section no longer needs a lazy initialiser here: it is
	// entry 0 of the retail array that 0x00438AD0 - and now the host's
	// critical_sections_init hook - initialises during boot.
	g_report.confirm_invoked = 1;
	g_report.character = character;
	g_report.weapon = weapon;
	g_report.difficulty = difficulty;
	Log("weapon confirmed: character=%d weapon=%d difficulty=%d",
	    character, weapon, difficulty);
	if (g_report.archive_available == 0) {
		Log("th10.dat is not mounted; the stage bridge stays offline");
		return -1;
	}

	// Publish the retail selection globals (dword_474C40 block).
	std::memset(&g_globals, 0, sizeof(g_globals));
	g_globals.fresh_run = 1;      // dword_491FC4: seed from the score file
	g_globals.ui_flags = 0;       // dword_491FF4: no abort bit
	g_globals.sync[0] = -1;       // dword_491C10 pair: render/loader ready
	g_globals.sync[1] = -1;
	// Retail keeps the character in dword_474C68 and the shot type in
	// dword_474C6C; the 0x00418190 tail indexes the score file with
	// 17276 * (dword_474C68 + dword_474C6C + 2 * dword_474C68), i.e.
	// 3 * character + shot. The character * 2 + weapon the bridge used to
	// publish here is not an encoding retail has.
	g_globals.character = character;  // dword_474C68
	g_globals.stage = weapon;         // dword_474C6C (shot type, 0..2)
	g_globals.difficulty = difficulty;
	g_globals.mode = 0;
	g_globals.game_flags = 0;
	g_globals.continues = 0;
	g_globals.loader_busy = 0;    // dword_494518: loader idle

	std::memset(&g_update_globals, 0, sizeof(g_update_globals));
	g_update_globals.character = g_globals.character;  // dword_474C68
	g_update_globals.stage = g_globals.stage;          // dword_474C6C
	g_update_globals.score_file = g_score_file;
	g_update_globals.player = 0;

	// Stage 1 record (retail dword_477848 row): all assets out of th10.dat.
	g_stage_record.number = 1;
	g_stage_record.script_name = "th10/stage01.std";
	g_stage_record.reserved_8 = 0;
	g_stage_record.enemy_script = (void*)"th10/stage01.ecl";
	g_stage_record.music_name = "th10/bgm/th10_00.mid";
	g_stage_record.music_loop = "th10/bgm/th10_00.mid";

	std::memset(g_stage_descriptor, 0, sizeof(g_stage_descriptor));
	std::memset(g_scheduler_device, 0, sizeof(g_scheduler_device));
	std::memset(g_camera_words, 0, sizeof(g_camera_words));
	std::memset(g_anm_slots, 0, sizeof(g_anm_slots));
	std::memset(g_score_file, 0, sizeof(g_score_file));
	// Retail 0x0042AF20 publishes the score-file image through dword_47783C;
	// 0x00420B10 latches its music-heard byte at image + 0x1D892 + index.
	DAT_0047783c = g_score_file;

	// Requested/current mode words (retail +0x38C/+0x390 of the state block).
	std::memset(&g_mode_state, 0, sizeof(g_mode_state));
	g_mode_state.current = kGameModeMenu;
	g_mode_state.requested = kGameModeGameplay;

	std::memset(&g_mode_env, 0, sizeof(g_mode_env));
	g_mode_env.enter_critical = HostModeEnterCritical;
	g_mode_env.leave_critical = HostModeLeaveCritical;
	g_mode_env.create_loading_owner = HostModeCreateLoadingOwner;
	g_mode_env.show_failure = HostModeShowFailure;
	g_mode_env.finalize_failure = HostModeFinalizeFailure;
	g_mode_env.leave_gameplay = HostModeLeaveGameplay;
	g_mode_env.enter_gameplay = HostModeEnterGameplay;
	g_mode_env.release_bullets = HostModeReleaseBullets;
	g_mode_env.prepare_restart = HostModePrepareRestart;
	g_mode_env.prepare_cleanup = HostModePrepareCleanup;
	g_mode_env.commit_menu = HostModeCommitMenu;
	g_mode_env.selected_difficulty = difficulty;
	g_mode_env.active_difficulty = &g_active_difficulty;
	g_mode_env.difficulty_table = g_difficulty_table;
	g_mode_env.difficulty_stride = sizeof(g_difficulty_table[0]);
	g_mode_env.active_difficulty_record = &g_active_difficulty_record;
	g_mode_env.exit_reason = &g_exit_reason;

	const int applied = GameMode_ApplyRequested(&g_mode_state, &g_mode_env);
	g_report.mode_apply_result = applied;
	g_report.mode_current_after = g_mode_state.current;
	return (g_report.leave_gameplay_fired != 0 && g_report.enter_result == 0)
	           ? 0
	           : -1;
}

int HostStage_RunFrames(int frames) {
	if (g_report.enter_attempted == 0 || g_report.enter_result != 0) return 0;
	for (int frame = 0; frame < frames; ++frame) {
		// Mirror each stage node's arm bit (set/cleared by the stage code)
		// into its paired scheduler callback so Scheduler_RunList honors the
		// retail arm/kill protocol across the split 64-bit layouts.
		for (int task = 0; task < 2; ++task) {
			if (g_task_callbacks[task] != 0)
				g_task_callbacks[task]->flags =
				    (g_task_callbacks[task]->flags & ~2u) |
				    (g_stage_task_nodes[task].flags & 2u);
		}
		Scheduler_RunPrimary(g_scheduler_device);   // 0x00449C00
		HostTickStageEcl();
		Scheduler_RunSecondary(g_scheduler_device); // 0x00449D40
		g_timeline_view.frame =
		    static_cast<unsigned int>(g_report.stage_frame);
		for (;;) {
			StageTimelineEvent event = {};
			const StageTimelineDecodeResult decode =
			    StageTimeline_DecodeDue(&g_timeline_view, &event);
			if (decode == kStageTimelineDecoded) {
				ApplyTimelineEvent(event);
				continue;
			}
			if (decode == kStageTimelineRejected)
				Log("timeline decoder rejected cursor 0x%X at frame %u",
				    (unsigned int)g_timeline_view.cursor,
				    g_timeline_view.frame);
			break;
		}
		TickStageCamera();
		g_report.frames_run += 1;
	}
	Log("scheduler advanced %d frames through the retail run lists: "
	    "update ticks=%d, draw ticks=%d, stage frame=%d, last update result=%d",
	    g_report.frames_run, g_report.update_ticks, g_report.draw_ticks,
		    g_report.stage_frame, g_report.last_update_result);
	g_report.owned_allocations = g_owned_allocation_count;
	g_report.timeline_decoded = g_timeline_view.stats.decoded;
	g_report.timeline_stopped_events = g_timeline_view.stats.stopped_events;
	g_report.timeline_cursor_jumps = g_timeline_view.stats.cursor_jumps;
	g_report.timeline_rejected = g_timeline_view.stats.rejected;
	g_report.timeline_budget_rejections =
	    g_timeline_view.stats.budget_rejections;
	g_report.timeline_maximum_accessed_offset =
	    g_timeline_view.stats.maximum_accessed_offset;
	if (g_ecl_enabled)
		Log("ecl: %d ticks-with-progress, %d calls, %d spawns, %d children "
		    "linked, %s (ip=%p, scratch_top=%d); bullets_active=%d",
		    g_ecl_instructions, g_ecl_calls, g_ecl_spawns,
		    HostEclLiveChildren(),
		    g_ecl_stopped ? "stopped" : "running",
		    (const void*)g_ecl_vm.ip, g_ecl_vm.scratch_top,
		    g_report.bullets_active);
	g_report.timeline_maximum_record_extent =
	    g_timeline_view.stats.maximum_record_extent;
	for (int opcode = 0; opcode < 15; ++opcode)
		g_report.timeline_opcode_histogram[opcode] =
		    g_timeline_view.stats.opcode_histogram[opcode];
	return frames;
}

static void* g_pending_effect_ring;

// Retail 0x004452F0 allocates the 0x4B0-byte ripple ring and seeds every
// segment. The bridge lives in this translation unit because effect_ring.hpp
// and effect_ring_update.hpp declare two different models of the same retail
// block under one type name and cannot be included together.
void HostStage_EnableEcl(int enabled) { g_ecl_enabled = enabled; }

void* HostStage_CreateEffectRing() {
	EffectRingHooks hooks = {};
	hooks.context = 0;
	hooks.alloc = [](void*, unsigned int size) -> void* {
		return HostAlloc(size);
	};
	hooks.rand_float = [](void*) -> float {
		return static_cast<float>(std::rand()) /
		       (static_cast<float>(RAND_MAX) + 1.0f);
	};
	hooks.rand_u16 = [](void*) -> unsigned int {
		return static_cast<unsigned int>(std::rand()) & 0xFFFFu;
	};
	hooks.polar_sample = [](void*, float radius, float* out_xy) {
		Vector2_SetAnimationPolar(reinterpret_cast<Vector2*>(out_xy),
		                          0.0f, radius);
	};
	// Retail publishes the update/draw callbacks into the owner at
	// +0x398/+0x39C. The host drives EffectRing_Update directly from the
	// ANM tick, so the bind step records the block the caller must own.
	hooks.bind_callbacks = [](void*, void* ring) {
		g_pending_effect_ring = ring;
	};
	hooks.angle_step = 0.2026834f;    // _DAT_00470B6C = 2*pi/31
	hooks.speed_scale = 0.00833333f;  // _DAT_00470C7C = 1/120
	return EffectRing_Create(&hooks);
}

const HostStageReport& HostStage_GetReport() { return g_report; }
const HostStageRuntimeView& HostStage_GetRuntimeView() { return g_runtime_view; }

int HostStage_IsActive() {
	return g_report.enter_attempted != 0 && g_report.enter_result == 0;
}
