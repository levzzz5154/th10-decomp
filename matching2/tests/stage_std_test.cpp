#include "th10/game/stage_std.hpp"

#include <cassert>
#include <cstdio>
#include <vector>

namespace {
void W16(std::vector<uint8_t>& b, size_t o, uint16_t v) {
	b[o] = static_cast<uint8_t>(v); b[o + 1] = static_cast<uint8_t>(v >> 8);
}
void W32(std::vector<uint8_t>& b, size_t o, uint32_t v) {
	for (int i = 0; i < 4; ++i) b[o + i] = static_cast<uint8_t>(v >> (i * 8));
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
} // namespace

int main() {
	TestValid();
	TestMalformed();
	std::puts("stage std raw-view tests passed");
}
