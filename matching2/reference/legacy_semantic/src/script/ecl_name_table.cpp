#include "th10/script/ecl_name_table.hpp"
#include "th10/game/pause_result_open.hpp"
#include "th10/game/registered_clock.hpp"
#include "th10/game/result_screen_effects.hpp"
#include "th10/util/scalars.hpp"

#include <cmath>
#include <cstring>

namespace {





} // namespace

// 0x00450220 - registers an ECL script's sub names into the sorted name
// table. The first registration bulk-fills the table; later registrations
// merge each new name into sorted position (2-byte strcmp in retail).
int EclNameTable_Register(EclTable* table, Byte* script,
                          EclNameEnv* env) {
	table->files[table->file_index] = script;
	if (script == 0 || *(Word*)script != 0x54504353u ||
	    *(short*)(script + 4) != 1) {
		table->files[table->file_index] = 0;
		return -1;
	}

	Word* offsets =
	    (Word*)(script + 0x24 + *(Half*)(script + 6));
	int new_count = *(Half*)(script + 0x10);
	const char* names = (const char*)(offsets + new_count);

	EclEntry* old_entries = table->entries;
	int old_count = table->total_count;
	table->total_count += new_count;
	EclEntry* entries = (EclEntry*)env->allocate(
	    (unsigned int)table->total_count * sizeof(EclEntry));
	table->entries = entries;

	if (old_entries == 0) {
		for (int i = 0; i < table->total_count; ++i) {
			entries[i].name = names;
			entries[i].body = script + offsets[i];
			names += std::strlen(names) + 1;
		}
		return 0;
	}

	std::memcpy(entries, old_entries,
	            (unsigned int)old_count * sizeof(EclEntry));
	env->release(old_entries);

	int merged = old_count;
	for (int i = 0; i < new_count; ++i) {
		int position = 0;
		while (position < merged &&
		       std::strcmp(names, entries[position].name) > 0) {
			++position;
		}
		for (int j = table->total_count - 1; j > position; --j) {
			entries[j] = entries[j - 1];
		}
		entries[position].name = names;
		entries[position].body = script + offsets[i];
		names += std::strlen(names) + 1;
		++merged;
	}
	return 0;
}

// 0x0040CD20 - copies the script path into the shared path buffer, reads the
// file, and registers its sub names. Returns 0 on success, -1 otherwise.
int EclArchive_LoadFile(EclTable* table, const char* path,
                        EclLoadEnv* env) {
	std::strcpy(env->path_buffer, path);
	Byte* data = env->read_file(0, 0);
	int result = EclNameTable_Register(table, data, &env->table_env);
	return result < 0 ? -1 : 0;
}
