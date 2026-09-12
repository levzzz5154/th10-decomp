#include "th10/script/stage_ecl_load.hpp"
#include "th10/game/registered_clock.hpp"
#include "th10/util/scalars.hpp"

#include <cmath>
#include <cstring>

namespace {



} // namespace

// 0x00403850 - stage ECL script load: records the script name in the global
// replay name sink, caches the raw file, takes a private copy, opens the
// companion archive entry named in the header, resolves the subroutine
// offset table (retail relocates it in place; the reconstruction widens it
// to host pointers), and allocates the enemy pool.
int StageScript_Load(StageScript* script, const char* path,
                     StageScriptEnv* env) {
	if (script->cached_file == 0) {
		std::strcpy(env->name_sink, path);
		script->cached_file = env->read_script_file(&script->cached_size, 0);
		if (script->cached_file == 0) return -1;
	}
	script->buffer = (char*)env->allocate(script->cached_size);
	std::memcpy(script->buffer, script->cached_file, script->cached_size);
	script->archive_entry = env->open_entry((int)(script->mode_flags & 1) + 4,
	                                        env->archive_manager,
	                                        script->buffer + 0x10);
	if (script->archive_entry == 0) {
		env->report_error(env->error_sink, env->error_text);
		return -1;
	}
	short sub_count;
	short enemy_count;
	Word anm_offset;
	Word std_offset;
	std::memcpy(&sub_count, script->buffer, sizeof(sub_count));
	std::memcpy(&enemy_count, script->buffer + 2, sizeof(enemy_count));
	std::memcpy(&anm_offset, script->buffer + 4, sizeof(anm_offset));
	std::memcpy(&std_offset, script->buffer + 8, sizeof(std_offset));
	script->anm_path = script->buffer + anm_offset;
	script->std_path = script->buffer + std_offset;
	script->sub_table =
	    (char**)env->allocate((unsigned int)sizeof(char*) * (unsigned int)sub_count);
	for (int i = 0; i < sub_count; ++i) {
		Word sub_offset;
		std::memcpy(&sub_offset, script->buffer + 0x90 + i * 4,
		            sizeof(sub_offset));
		script->sub_table[i] = script->buffer + sub_offset;
	}
	script->enemy_pool = env->allocate((unsigned int)enemy_count * 0x3ACu);
	return 0;
}
