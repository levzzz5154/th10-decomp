#pragma once

// Stage ECL script load (retail 0x00403850).
#include "th10/util/scalars.hpp"

struct StageScript {
	char* buffer;            // +0x10, private copy of the script file
	char** sub_table;        // +0x14, resolved subroutine entry points
	char* anm_path;          // +0x18
	char* std_path;          // +0x1c
	void* archive_entry;     // +0x178
	void* enemy_pool;        // +0x17c
	Word mode_flags;   // +0x2a30, bit 0 selects the alternate archive
	Byte* cached_file; // +0x2a44
	Word cached_size;  // +0x2a48
};

struct StageScriptEnv {
	char* name_sink; // global script-name buffer for replays
	Byte* (*read_script_file)(Word* size_slot, int mode);
	void* archive_manager;
	void* (*open_entry)(int mode, void* archive_manager, const char* name);
	void (*report_error)(void* sink, const char* message);
	void* error_sink;
	const char* error_text;
	void* (*allocate)(unsigned int size);
};

int StageScript_Load(StageScript* script, const char* path,
                     StageScriptEnv* env);
