#include "th10/game/stage_std.hpp"

#include <cassert>
#include <cstring>
#include <cstdio>
#include <vector>

namespace {
void W16(std::vector<uint8_t>& b, size_t o, uint16_t v) {
	b[o] = static_cast<uint8_t>(v); b[o + 1] = static_cast<uint8_t>(v >> 8);
}
void W32(std::vector<uint8_t>& b, size_t o, uint32_t v) {
	for (int i = 0; i < 4; ++i) b[o + i] = static_cast<uint8_t>(v >> (i * 8));
}
void WF(std::vector<uint8_t>& b, size_t o, float v) {
	uint32_t bits = 0;
	static_assert(sizeof(bits) == sizeof(v), "32-bit float required");
	std::memcpy(&bits, &v, sizeof(bits));
	W32(b, o, bits);
}
std::vector<uint8_t> Valid() {
	std::vector<uint8_t> b(0xC0, 0);
	W16(b, 0, 2); W16(b, 2, 19); W32(b, 4, 0xA0); W32(b, 8, 0xB0);
	b[0x10] = 's'; b[0x11] = 't'; b[0x12] = 'g';
	W32(b, 0x90, 0xA0); W32(b, 0x94, 0xB0);
	return b;
}
void TestValid() {
	std::vector<uint8_t> b = Valid(); StageStdRawView v = {};
	assert(StageStd_ParseRaw(b.data(), b.size(), &v));
	assert(v.count_00 == 2 && v.count_02 == 19);
	assert(v.companion_name_length == 3);
	uint32_t offset = 0;
	assert(StageStd_GetOffset90(&v, 0, &offset) && offset == 0xA0);
	assert(StageStd_GetOffset90(&v, 1, &offset) && offset == 0xB0);
	assert(!StageStd_GetOffset90(&v, 2, &offset));
}
void TestMalformed() {
	StageStdRawView v = {};
	std::vector<uint8_t> b = Valid();
	assert(!StageStd_ParseRaw(b.data(), 0x8F, &v));
	W16(b, 0, 13); assert(!StageStd_ParseRaw(b.data(), b.size(), &v));
	b = Valid(); W32(b, 4, 0xC0);
	assert(!StageStd_ParseRaw(b.data(), b.size(), &v));
	b = Valid(); W32(b, 0x90, 0xFFFFFFFFu);
	assert(!StageStd_ParseRaw(b.data(), b.size(), &v));
	b = Valid(); for (size_t i = 0x10; i < 0x90; ++i) b[i] = 'x';
	assert(!StageStd_ParseRaw(b.data(), b.size(), &v));
	b = Valid(); b[0x10] = 0;
	assert(!StageStd_ParseRaw(b.data(), b.size(), &v));
	b = Valid(); W32(b, 0x94, 0x94);
	assert(!StageStd_ParseRaw(b.data(), b.size(), &v));
}
void TestGeometryViews() {
	std::vector<uint8_t> b(0x110, 0);
	W16(b, 0, 1); W16(b, 2, 1);
	W32(b, 4, 0xD0); W32(b, 8, 0xF0);
	b[0x10] = 's'; W32(b, 0x90, 0x94);
	W16(b, 0x94, 4); b[0x96] = 2; b[0x97] = 1;
	WF(b, 0x98, 10.0f); WF(b, 0x9C, 20.0f); WF(b, 0xA0, 30.0f);
	WF(b, 0xA4, 40.0f); WF(b, 0xA8, 50.0f); WF(b, 0xAC, 60.0f);
	W16(b, 0xB0, 3); W16(b, 0xB2, 0x1C); W16(b, 0xB4, 7);
	W16(b, 0xB6, 9); WF(b, 0xB8, 1.0f); WF(b, 0xBC, 2.0f);
	WF(b, 0xC0, 3.0f); WF(b, 0xC4, 4.0f); WF(b, 0xC8, 5.0f);
	W16(b, 0xCC, 0xFFFF); W16(b, 0xCE, 4);
	W16(b, 0xD0, 0); b[0xD2] = 2; b[0xD3] = 8;
	WF(b, 0xD4, 100.0f); WF(b, 0xD8, 200.0f); WF(b, 0xDC, 300.0f);
	W16(b, 0xE0, 0xFFFF);
	StageStdRawView raw = {};
	assert(StageStd_ParseRaw(b.data(), b.size(), &raw));
	StageStdObjectView object = {};
	assert(StageStd_GetObject(&raw, 0, &object));
	assert(object.field_00 == 4 && object.selection_group == 2);
	assert(object.position[1] == 20.0f && object.extent[2] == 60.0f);
	StageStdSubrecordView subrecord = {};
	assert(StageStd_GetSubrecord(&object, 0, &subrecord));
	assert(subrecord.kind == 3 && subrecord.stride == 0x1C);
	assert(subrecord.field_04 == 7 && subrecord.runtime_slot == 9);
	assert(subrecord.position[2] == 3.0f && subrecord.size[1] == 5.0f);
	assert(!StageStd_GetSubrecord(&object, 1, &subrecord));
	StageStdPlacementView placement = {};
	assert(StageStd_GetPlacement(&raw, 0, &placement));
	assert(placement.object_index == 0 && placement.selection_group == 2);
	assert(placement.position[1] == 200.0f);
	assert(!StageStd_GetPlacement(&raw, 1, &placement));
}
} // namespace

int main() {
	TestValid();
	TestMalformed();
	TestGeometryViews();
	std::puts("stage std raw-view tests passed");
}
