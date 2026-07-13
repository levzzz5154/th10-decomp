#pragma once
#include "th10/types.h"
#include <cstdint>
#include <string>
#include <vector>

namespace th10 {

#pragma pack(push, 1)
struct ShtPatternEntry {
	uint16_t bullet_type;    // 0x00 - bullet sprite/animation ID
	uint16_t power_level;    // 0x02 - power threshold (0=0.00, 15=4.00)
	float    offset_x;       // 0x04 - x spawn offset from player
	float    offset_y;       // 0x08 - y spawn offset from player
	float    hitbox_w;       // 0x0C - bullet hitbox width
	float    hitbox_h;       // 0x10 - bullet hitbox height
	float    angle;          // 0x14 - fire angle (radians)
	float    speed;          // 0x18 - bullet speed
	float    speed2;         // 0x1C - secondary speed / aim speed
	uint16_t bullet_count;   // 0x20 - number of bullets
	int16_t  aim_mode;       // 0x22 - 0 = fixed angle, -1 = aimed at player
	int32_t  unk1;           // 0x24
	int32_t  unk2;           // 0x28
	int32_t  unk3;           // 0x2C
	int32_t  unk4;           // 0x30
};
static_assert(sizeof(ShtPatternEntry) == 0x34, "SHT pattern entry must be 52 bytes");

struct ShtHeader {
	uint16_t count1;           // 0x00 - shot subtype/variant
	uint16_t power_levels;     // 0x02 - number of power sub-levels (10)
	float    params[67];       // 0x04 - shot parameters + vec2 pairs
};
static_assert(sizeof(ShtHeader) == 0x110, "SHT header must be 272 bytes");

struct ShtOffsetEntry {
	uint32_t offset;    // file offset to power level section
	uint32_t count;     // bullet count or flag (8 or 999 sentinel)
};
#pragma pack(pop)

struct ShtPowerLevel {
	int32_t power_index;
	std::vector<ShtPatternEntry> focused;
	std::vector<ShtPatternEntry> unfocused;
};

class ShtFile {
public:
	ShtFile() = default;

	bool open(const std::string& path);
	void close();

	const std::string& path() const { return path_; }
	const ShtHeader& header() const { return hdr_; }
	const std::vector<ShtPowerLevel>& levels() const { return levels_; }
	size_t level_count() const { return levels_.size(); }

	bool empty() const { return levels_.empty(); }

private:
	std::string              path_;
	ShtHeader                hdr_;
	std::vector<ShtPowerLevel> levels_;
};

} // namespace th10
