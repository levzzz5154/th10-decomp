#pragma once
#include "th10/types.h"
#include <cstdint>
#include <string>
#include <vector>

namespace th10 {

struct MsgInstrDecoded {
	uint16_t time;
	uint8_t  opcode;
	std::string text;
	std::vector<uint8_t> raw_data;
};

class MsgEntry {
public:
	int32_t index = -1;
	int32_t extra = 0;
	std::vector<MsgInstrDecoded> instructions;

	bool empty() const { return instructions.empty(); }
};

class MsgFile {
public:
	bool parse(const uint8_t* data, size_t size,
	           const char* encoding = "shift-jis",
	           bool is_ending = false);

	std::string dump() const;

	const std::vector<MsgEntry>& entries() const { return entries_; }
	size_t entry_count() const { return entries_.size(); }

private:
	std::vector<MsgEntry> entries_;

	static void util_xor(std::vector<uint8_t>& buf,
	                     uint8_t key = 0x77,
	                     uint8_t step1 = 7,
	                     uint8_t step2 = 16);

	static void sjis_to_utf8(std::string& out,
	                         const uint8_t* data,
	                         size_t len);

	std::string decode_instr_data(const MsgInstrDecoded& ins,
	                              bool is_ending,
	                              const char* encoding) const;
};

} // namespace th10
