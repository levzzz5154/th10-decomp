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

struct StageStdObjectView {
	uint16_t field_00;
	uint8_t selection_group;
	uint8_t runtime_flags;
	float position[3];
	float extent[3];
	const uint8_t* data;
	size_t offset;
	size_t size;
};

struct StageStdSubrecordView {
	int16_t kind;
	int16_t stride;
	uint16_t field_04;
	uint16_t runtime_slot;
	float position[3];
	float size[2];
	size_t offset;
};

struct StageStdPlacementView {
	int16_t object_index;
	uint8_t selection_group;
	uint8_t field_03;
	float position[3];
	size_t offset;
};

bool StageStd_GetObject(const StageStdRawView* view, uint16_t index,
                        StageStdObjectView* out);
bool StageStd_GetSubrecord(const StageStdObjectView* object, uint16_t index,
                           StageStdSubrecordView* out);
bool StageStd_GetPlacement(const StageStdRawView* view, uint16_t index,
                           StageStdPlacementView* out);
