#pragma once

#include <cstddef>

// Version resource probe and version marker load (retail 0x00420100).
// --- 0x00420100: load the executable-version marker -------------------------
struct VersionMarkerEnv {
	int version;                    // retail constant 0x100
	char suffix;                    // retail constant 'a'
	const char* missing_probe_log;  // retail DAT_0046dfa0
	const char* load_failure_log;   // retail DAT_0046dfc8
	// Adapter for the archive-open operation; make its contents available
	// to load() before reporting success, not merely test file existence.
	bool (*probe)(const char* archive_name);
	unsigned char* (*load)(const char* generated_name, std::size_t* size);
	void (*log)(const char* text);
	unsigned char** published_data; // retail DAT_0049238c
	std::size_t* published_size;    // retail DAT_00492388
};

int VersionMarker_Load(VersionMarkerEnv* env);
