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
#include "th10/game/stage_std.hpp"
#include "th10/script/stage_ecl_load.hpp"
#include "th10/archive/resource_manager.hpp"
// windows_types.hpp defines NULL unconditionally; glibc headers included
// above already define it, so drop theirs first to stay -Werror clean.
#undef NULL
#include "th10/platform/file.hpp"

#include <cstdarg>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

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
extern "C" void __stdcall InitializeCriticalSection(void*);
unsigned int DAT_00492274[6] = {};
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
int g_anm_slots[64];
int g_thread_pending;
StageContext g_context;
StageRecord g_stage_record;
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
unsigned char* g_companion_anm;
unsigned int g_companion_anm_size;
HostStageRuntimeView g_runtime_view;

void* g_enemy_manager_slot;
void* g_effect_manager_slot;
void* g_bullet_pool_slot;
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
void* HostConstruct(void* memory) { return memory; }
void HostDestroyNoop(void* manager) { (void)manager; }
int HostInitOk() { return 0; }             // factory initializer: 0 = success
int HostStateInitOk(void* state) { (void)state; return 0; }
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
	void* manager = ItemManager_Create(HostAlloc, HostConstruct, HostInitOk,
		                                   HostDestroyNoop, HostFreeMem);
	g_item_manager = manager;
	if (manager != 0) g_report.factories_created += 1;
	else g_report.factory_failures += 1;
	Log("ItemManager_Create(0x00414830): %s",
	    manager != 0 ? "created (0x9ED0 bytes)" : "FAILED");
	return manager != 0;
}

int HostInitLargeResource() {
	void* state = Recovery_CreateLargeResourceState(HostAlloc, HostStateInitOk,
		                                                HostDestroyNoop, HostFreeMem);
	g_large_resource_state = state;
	if (state != 0) g_report.factories_created += 1;
	else g_report.factory_failures += 1;
	Log("Recovery_CreateLargeResourceState(0x00425020): %s",
	    state != 0 ? "created" : "FAILED");
	return state != 0;
}

int HostInitBulletPool() {
	void* pool = BulletManager_Create(HostAlloc, HostConstructSlots,
	                                  &g_bullet_pool_slot, HostInitOk,
	                                  HostDestroyNoop, HostFreeMem);
	if (pool != 0) g_report.factories_created += 1;
	else g_report.factory_failures += 1;
	Log("BulletManager_Create(0x00406060): %s",
	    pool != 0 ? "pool created (0x3E0B54 bytes)" : "FAILED");
	return pool != 0;
}

int HostInitEffectManager() {
	void* manager = EffectManager_Create(HostAlloc, HostConstructSlots,
	                                     &g_effect_manager_slot, HostInitOk,
	                                     HostDestroyNoop, HostFreeMem);
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
	void* state = Recovery_CreateTimerState(HostAlloc, HostStateInitOk,
		                                        HostDestroyNoop, HostFreeMem);
	g_timer_state = state;
	if (state != 0) g_report.factories_created += 1;
	else g_report.factory_failures += 1;
	Log("Recovery_CreateTimerState(0x00422360): %s",
	    state != 0 ? "created (0x2C8 bytes)" : "FAILED");
	return state != 0;
}

int HostInitResourceState() {
	void* state = Recovery_CreateResourceState(0x1A8, HostAlloc, HostStateInitOk,
		                                           HostDestroyNoop, HostFreeMem);
	g_resource_state = state;
	if (state != 0) g_report.factories_created += 1;
	else g_report.factory_failures += 1;
	Log("Recovery_CreateResourceState(0x00419090): %s",
	    state != 0 ? "created (0x1A8 bytes)" : "FAILED");
	return state != 0;
}

int HostCreateStageState() {
	void* state = Recovery_CreateHugeResourceState(HostAlloc, HostStateInitOk,
		                                               HostDestroyNoop, HostFreeMem);
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
	// Retail 0x0040AF90 (full bullet manager) is a heavy TU outside this
	// bridge's link set; host adapter records the real bullet ANM instead.
	const unsigned int size = Resource_GetFileSize("th10/bullet.anm");
	Log("host adapter for 0x0040AF90: th10/bullet.anm present in th10.dat "
	    "(%u bytes); full bullet manager is step-7 scope", size);
	return 1;
}

int HostInitFixedState() {
	void* state = Recovery_CreateFixedState(0x48, HostAlloc, HostStateInitOk,
		                                        HostDestroyNoop, HostFreeMem);
	g_fixed_state = state;
	if (state != 0) g_report.factories_created += 1;
	else g_report.factory_failures += 1;
	Log("Recovery_CreateFixedState(0x004056B0): %s",
	    state != 0 ? "created (0x48 bytes)" : "FAILED");
	return state != 0;
}

int HostInitPlayerManager() {
	void* manager = PlayerManager_Create(HostAlloc, HostConstruct, HostInitOk,
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

void HostMusicReset() {
	Log("music_reset (0x00420C00 edge): stage BGM channel cleared");
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
// Remaining stage-entry edges whose retail callees are still unrecovered.
// -----------------------------------------------------------------------------
void HostSeedExtendThreshold(int* score_seed, int amount) {
	(void)score_seed;
	Log("host adapter for 0x00418B80: extend gauge target seeded from %d", amount);
}
void HostReplayReset() { Log("host adapter: replay reset (0x0042A6A0)"); }
void HostReplaySeed(void* game) { (void)game; }
void HostSpellPracticeReset(void* state) {
	(void)state;
	Log("host adapter: spell practice reset (0x00417800 path)");
}
void HostResetPlayerSpawn(float* spawn, int value) {
	if (spawn != 0) spawn[4] = (float)value;
	Log("host adapter for 0x00405410: player spawn node armed (value %d)", value);
}
void HostReleaseOverlayAnm(void* slots) {
	(void)slots;
	Log("host adapter for 0x00421300: overlay ANM handles released");
}
void HostReleasePendingAnm(void* slots) {
	(void)slots;
	Log("host adapter for 0x00421070: pending ANM handles released");
}
void HostRequestCallbackRemoval(void* context) {
	(void)context;
	Log("host adapter for 0x00409E20: loading-callback retirement requested");
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
void HostEnterTransitionLock() { Log("host adapter: transition lock (0x0044C150)"); }
void HostActivateBullets() { Log("host adapter: bullet pool activation (0x00404450)"); }
void HostArmPlayerTimer() { Log("host adapter: player timer armed (0x00404530)"); }
void HostStartPlayerMode() { Log("host adapter: player mode start (0x004045B0)"); }
void HostResetThreadTimer(int index) {
	Log("host adapter: thread timer %d reset (0x00409E50)", index);
}
void HostClearThreadPending() { g_thread_pending = 0; }
void HostStopPlayerRuntime() { Log("host adapter: player runtime stop (0x00405ED0)"); }
void HostResetStageRuntime() { Log("host adapter: stage runtime reset (0x00424D90)"); }
void HostClearStageArena() { Log("host adapter: stage arena cleared"); }
void HostResetEnemyRuntime() { Log("host adapter: enemy runtime reset (0x00409F90)"); }
void HostReleaseCleanupChain() { Log("host adapter: cleanup chain released (0x00417770)"); }
void HostResetGameplayAction() { Log("host adapter: gameplay action reset (0x0042A450)"); }
void HostStartMainEcl() {
	Log("main ECL start requested (0x0040CFB0) - the ECL VM dispatcher is "
	    "step-6 scope; Stage 1 script bytes are already resident");
}
void HostInitializeStageRuntime() {
	Log("host adapter: stage runtime init (0x00413BC0)");
}
void HostRefreshSidePanel(StageUpdateTaskPair* pair) {
	(void)pair;
	Log("host adapter: side panel refresh (0x00426F70)");
}
void HostStartStageMusic() {
	Log("stage BGM start requested (0x00420B10): %s @ %u Hz",
	    g_report.bgm_track[0] != 0 ? g_report.bgm_track : "(no record)",
	    g_report.bgm_rate);
}
void HostCreateDelayedStageEffect(int variant) {
	Log("host adapter: delayed stage effect variant %d (0x0043E460)", variant);
}
void HostResetPlayerSpawnUpdate(StageContext* context) {
	if (context != 0) HostResetPlayerSpawn(context->spawn, 0);
}
int HostPlayerRequestsDestroy(void* player) { (void)player; return 0; }
void HostDestroyPlayer(void* player) { (void)player; }
void HostFreePlayer(void* player) { std::free(player); }
void HostSpawnTransitionEffect() { Log("host adapter: transition effect (0x0043C8B0)"); }
void HostRunTransitionAction() { Log("host adapter: transition action (0x0040AC90)"); }
void HostTickGame() {}
void HostUpdateScoreThreshold() {}
void HostTickStageTimer(StageContext* context) {
	int frame = 0;
	std::memcpy(&frame, &context->spawn[1], sizeof(frame));
	frame += 1;
	std::memcpy(&context->spawn[1], &frame, sizeof(frame));
	g_report.stage_frame = frame;
	g_runtime_view.stage_frame = frame;
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
	g_entry_env.spell_practice_state = 0;
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
	g_companion_anm = 0;
	g_companion_anm_size = 0;
	g_report.archive_available = archive_available;
	g_owned_allocation_count = 0;
#if defined(_WIN32)
	static int scheduler_critical_ready = 0;
	if (!scheduler_critical_ready) {
		InitializeCriticalSection(DAT_00492274);
		scheduler_critical_ready = 1;
	}
#endif
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
	g_globals.character = character * 2 + weapon; // retail shot-type encoding
	g_globals.stage = 0;          // Stage 1 score-record index
	g_globals.difficulty = difficulty;
	g_globals.mode = 0;
	g_globals.game_flags = 0;
	g_globals.continues = 0;
	g_globals.loader_busy = 0;    // dword_494518: loader idle

	std::memset(&g_update_globals, 0, sizeof(g_update_globals));
	g_update_globals.character = g_globals.character;
	g_update_globals.stage = 0;
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
		Scheduler_RunSecondary(g_scheduler_device); // 0x00449D40
		g_report.frames_run += 1;
	}
	Log("scheduler advanced %d frames through the retail run lists: "
	    "update ticks=%d, draw ticks=%d, stage frame=%d, last update result=%d",
	    g_report.frames_run, g_report.update_ticks, g_report.draw_ticks,
		    g_report.stage_frame, g_report.last_update_result);
	g_report.owned_allocations = g_owned_allocation_count;
	return frames;
}

const HostStageReport& HostStage_GetReport() { return g_report; }
const HostStageRuntimeView& HostStage_GetRuntimeView() { return g_runtime_view; }

int HostStage_IsActive() {
	return g_report.enter_attempted != 0 && g_report.enter_result == 0;
}
