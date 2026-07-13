#include "th10/sht_loader.h"
#include <cstdio>
#include <cstring>

namespace th10 {

static constexpr int32_t SHT_SENTINEL = -1;

bool ShtFile::open(const std::string& path) {
	close();
	path_ = path;

	FILE* file = fopen(path.c_str(), "rb");
	if (!file) {
		return false;
	}

	fseek(file, 0, SEEK_END);
	long file_size = ftell(file);
	if (file_size < static_cast<long>(sizeof(ShtHeader)) + 8) {
		fclose(file);
		return false;
	}
	rewind(file);

	if (fread(&hdr_, sizeof(ShtHeader), 1, file) != 1) {
		fclose(file);
		return false;
	}

	if (hdr_.power_levels == 0 || hdr_.power_levels > 64) {
		fclose(file);
		return false;
	}

	uint32_t num_levels = hdr_.power_levels;
	std::vector<ShtOffsetEntry> offset_table(num_levels);
	if (fread(offset_table.data(), sizeof(ShtOffsetEntry), num_levels, file) != num_levels) {
		fclose(file);
		return false;
	}

	levels_.clear();
	levels_.reserve(num_levels);

	for (uint32_t i = 0; i < num_levels; i++) {
		uint32_t section_off = offset_table[i].offset;
		if (section_off < sizeof(ShtHeader) ||
		    section_off >= static_cast<uint32_t>(file_size)) {
			continue;
		}

		if (fseek(file, section_off, SEEK_SET) != 0) {
			break;
		}

		ShtPowerLevel level;
		level.power_index = static_cast<int32_t>(i);

		auto read_entries = [&](std::vector<ShtPatternEntry>& out) -> bool {
			while (true) {
				long cur = ftell(file);
				if (cur < 0) return false;

				int32_t sentinel_check = 0;
				if (fread(&sentinel_check, 4, 1, file) != 1) return false;

				if (sentinel_check == SHT_SENTINEL) {
					return true;
				}

				fseek(file, cur, SEEK_SET);
				ShtPatternEntry entry;
				if (fread(&entry, sizeof(ShtPatternEntry), 1, file) != 1) {
					return false;
				}
				out.push_back(entry);
			}
		};

		if (!read_entries(level.focused)) break;
		if (!read_entries(level.unfocused)) break;

		levels_.push_back(level);
	}

	fclose(file);
	return true;
}

void ShtFile::close() {
	path_.clear();
	memset(&hdr_, 0, sizeof(hdr_));
	levels_.clear();
}

} // namespace th10
