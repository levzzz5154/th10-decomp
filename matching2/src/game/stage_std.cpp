#include "th10/game/stage_std.hpp"

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
bool Fits(size_t offset, size_t length, size_t size) {
	return offset <= size && length <= size - offset;
}
} // namespace

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
