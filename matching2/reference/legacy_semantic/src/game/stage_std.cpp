#include "th10/game/stage_std.hpp"

#include <cstring>

namespace {
uint16_t Read16(const uint8_t* p) {
	return static_cast<uint16_t>(p[0]) |
	       static_cast<uint16_t>(static_cast<uint16_t>(p[1]) << 8);
}
uint32_t Read32(const uint8_t* p) {
	return static_cast<uint32_t>(p[0]) |
	       (static_cast<uint32_t>(p[1]) << 8) |
	       (static_cast<uint32_t>(p[2]) << 16) |
	       (static_cast<uint32_t>(p[3]) << 24);
}
float ReadFloat(const uint8_t* p) {
	const uint32_t bits = Read32(p);
	float value;
	static_assert(sizeof(value) == sizeof(bits), "32-bit float required");
	std::memcpy(&value, &bits, sizeof(value));
	return value;
}
bool Fits(size_t offset, size_t length, size_t size) {
	return offset <= size && length <= size - offset;
}
} // namespace

bool StageStd_GetObject(const StageStdRawView* view, uint16_t index,
                        StageStdObjectView* out) {
	if (view == 0 || out == 0 || index >= view->count_00) return false;
	uint32_t begin = 0;
	if (!StageStd_GetOffset90(view, index, &begin)) return false;
	uint32_t end = view->offset_04;
	if (index + 1 < view->count_00 &&
	    !StageStd_GetOffset90(view, index + 1, &end)) return false;
	if (begin >= end || end > view->size || end - begin < 0x20) return false;
	const uint8_t* data = view->data + begin;
	out->field_00 = Read16(data);
	out->selection_group = data[2];
	out->runtime_flags = data[3];
	for (int axis = 0; axis < 3; ++axis) {
		out->position[axis] = ReadFloat(data + 4 + axis * 4);
		out->extent[axis] = ReadFloat(data + 0x10 + axis * 4);
	}
	out->data = data;
	out->offset = begin;
	out->size = end - begin;
	return true;
}

bool StageStd_GetSubrecord(const StageStdObjectView* object, uint16_t index,
                           StageStdSubrecordView* out) {
	if (object == 0 || out == 0 || object->data == 0 ||
	    object->size < 0x20) return false;
	size_t cursor = 0x1C;
	for (uint16_t current = 0;; ++current) {
		if (!Fits(cursor, 4, object->size)) return false;
		const int16_t kind =
		    static_cast<int16_t>(Read16(object->data + cursor));
		if (kind < 0) return false;
		const int16_t stride =
		    static_cast<int16_t>(Read16(object->data + cursor + 2));
		if (stride < 0x1C ||
		    !Fits(cursor, static_cast<size_t>(stride), object->size))
			return false;
		if (current == index) {
			const uint8_t* data = object->data + cursor;
			out->kind = kind;
			out->stride = stride;
			out->field_04 = Read16(data + 4);
			out->runtime_slot = Read16(data + 6);
			for (int axis = 0; axis < 3; ++axis)
				out->position[axis] = ReadFloat(data + 8 + axis * 4);
			out->size[0] = ReadFloat(data + 0x14);
			out->size[1] = ReadFloat(data + 0x18);
			out->offset = object->offset + cursor;
			return true;
		}
		cursor += static_cast<size_t>(stride);
	}
}

bool StageStd_GetPlacement(const StageStdRawView* view, uint16_t index,
                           StageStdPlacementView* out) {
	if (view == 0 || out == 0 || view->offset_04 >= view->offset_08)
		return false;
	size_t cursor = view->offset_04;
	for (uint16_t current = 0;; ++current) {
		if (!Fits(cursor, 2, view->offset_08)) return false;
		const int16_t object_index =
		    static_cast<int16_t>(Read16(view->data + cursor));
		if (object_index < 0) return false;
		if (!Fits(cursor, 16, view->offset_08)) return false;
		if (current == index) {
			out->object_index = object_index;
			out->selection_group = view->data[cursor + 2];
			out->field_03 = view->data[cursor + 3];
			for (int axis = 0; axis < 3; ++axis)
				out->position[axis] =
				    ReadFloat(view->data + cursor + 4 + axis * 4);
			out->offset = cursor;
			return true;
		}
		cursor += 16;
	}
}

bool StageStd_ParseRaw(const uint8_t* data, size_t size, StageStdRawView* out) {
	if (data == 0 || out == 0 || !Fits(0, 0x90, size)) return false;
	const uint16_t count_00 = Read16(data);
	const uint16_t count_02 = Read16(data + 2);
	const uint32_t offset_04 = Read32(data + 4);
	const uint32_t offset_08 = Read32(data + 8);
	if (count_00 == 0 || count_00 > 512 || count_02 > 4096) return false;
	if (!Fits(0x90, static_cast<size_t>(count_00) * 4, size)) return false;
	if (offset_04 >= size || offset_08 >= size) return false;
	size_t name_length = 0;
	while (name_length < 0x80 && data[0x10 + name_length] != 0)
		++name_length;
	if (name_length == 0 || name_length == 0x80) return false;
	const size_t table_end = 0x90 + static_cast<size_t>(count_00) * 4;
	for (uint16_t index = 0; index < count_00; ++index) {
		const uint32_t offset = Read32(data + 0x90 + index * 4);
		if (offset < table_end || offset >= size) return false;
	}
	out->data = data;
	out->size = size;
	out->count_00 = count_00;
	out->count_02 = count_02;
	out->offset_04 = offset_04;
	out->offset_08 = offset_08;
	out->companion_name = reinterpret_cast<const char*>(data + 0x10);
	out->companion_name_length = name_length;
	return true;
}

bool StageStd_GetOffset90(const StageStdRawView* view, uint16_t index,
                         uint32_t* out) {
	if (view == 0 || out == 0 || view->data == 0 ||
	    index >= view->count_00) return false;
	const size_t location = 0x90 + static_cast<size_t>(index) * 4;
	if (!Fits(location, 4, view->size)) return false;
	const uint32_t offset = Read32(view->data + location);
	if (offset >= view->size) return false;
	*out = offset;
	return true;
}
