#pragma once

// Replay archive load, decipher, decompress, and stage indexing (retail 0x0042A200).
struct ReplayFileHeader {
	unsigned int magic;
	unsigned short version;
	unsigned char reserved[22];
	unsigned int packed_size;
	unsigned int unpacked_size;
};
struct ReplayFileEntry {
	short slot;
	unsigned short reserved;
	int script_count;
	int extra_size;
};
struct ReplayFileState {
	char name[256];
	ReplayFileHeader* header;
	unsigned char* decompressed;
	unsigned char* active_data;
	ReplayFileEntry* entries[8];
	unsigned char* script_data[8];
	unsigned char* script_end[8];
};
struct ReplayFileEnv {
	bool embedded_mode;
	bool (*load_source)(const char* path, bool embedded,
	                    ReplayFileHeader** header,
	                    unsigned char** payload, bool* payload_owned);
	unsigned char* (*allocate)(unsigned size);
	// Retail runs two passes with different block sizes:
	// sub_44B0D0(170, payload, size, 225, 1024, size) then
	// sub_44B0D0(61, payload, size, 122, 128, size). The block has to travel
	// with the call - without it the second pass cannot be distinguished
	// from the first and the payload never decodes.
	void (*decrypt)(unsigned char* payload, unsigned size,
	                unsigned char seed, unsigned step, unsigned block);
	void (*decompress)(const unsigned char* packed, unsigned packed_size,
	                   unsigned char* output, unsigned output_size);
	void (*release_payload)(unsigned char* payload);
};
int ReplayArchive_Load(ReplayFileState* state, const char* name,
                       ReplayFileEnv* env);
