#pragma once

#include <cstddef>
#include <cstdint>

// Bounds-checked, deliberately semantic-neutral view of the stage STD header.
// The retail loader at 0x00403850 reads these fields; meaningful names should
// be added only after their consumers have been reconstructed.
struct StageStdRawView {
	const uint8_t* data;
	size_t size;
	uint16_t count_00;
	uint16_t count_02;
	uint32_t offset_04;
	uint32_t offset_08;
	const char* companion_name;
	size_t companion_name_length;
};

bool StageStd_ParseRaw(const uint8_t* data, size_t size, StageStdRawView* out);
bool StageStd_GetOffset90(const StageStdRawView* view, uint16_t index,
                         uint32_t* out);
