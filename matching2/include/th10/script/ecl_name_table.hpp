#pragma once

// ECL name table registration and archive file load (retail 0x00450220, 0x0040CD20).
#include "th10/util/scalars.hpp"

struct EclEntry {
	const char* name;
	Byte* body;
};

struct EclTable {
	int file_index;
	int total_count;
	Byte* files[8];
	EclEntry* entries;
};

struct EclNameEnv {
	void* (*allocate)(unsigned int size);
	void (*release)(void* block);
};

int EclNameTable_Register(EclTable* table, Byte* script,
                          EclNameEnv* env);

// The rows EclTable::entries holds are byte-for-byte the 8-byte
// {const char* name, void* body} rows retail 0x00450470 binary-searches; a
// lookup object with the count at +8 and this table at +140 can be handed
// straight to ECL_FindScriptLabel (th10/script/ecl.hpp).

struct EclLoadEnv {
	char* path_buffer;
	Byte* (*read_file)(unsigned int* size_out, int mode);
	EclNameEnv table_env;
};

int EclArchive_LoadFile(EclTable* table, const char* path,
                        EclLoadEnv* env);
