#include "th10/msg_decoder.h"
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iconv.h>

namespace th10 {

// ----------------------------------------------------------------
// util_xor  --  ZUN's XOR cipher for 'm'-type text fields
//   key=0x77, step1=7, step2=16  (standard TH10 text params)
// ----------------------------------------------------------------
void MsgFile::util_xor(std::vector<uint8_t>& buf,
                       uint8_t key, uint8_t step1, uint8_t step2)
{
	for (size_t i = 0; i < buf.size(); ++i) {
		buf[i] ^= key;
		key   = (key   + step1) & 0xFF;
		step1 = (step1 + step2) & 0xFF;
	}
}

// ----------------------------------------------------------------
// sjis_to_utf8  --  Shift-JIS -> UTF-8 via iconv
// ----------------------------------------------------------------
void MsgFile::sjis_to_utf8(std::string& out,
                           const uint8_t* data, size_t len)
{
	if (!data || len == 0)
		return;

	iconv_t cd = iconv_open("UTF-8", "SHIFT_JIS");
	if (cd == reinterpret_cast<iconv_t>(-1)) {
		// Fallback: pass through ASCII range only
		for (size_t i = 0; i < len; ++i) {
			if (data[i] < 0x80 && data[i] != 0)
				out.push_back(static_cast<char>(data[i]));
		}
		return;
	}

	char   outbuf[4096];
	size_t in_bytes = len;
	size_t out_bytes = sizeof(outbuf);
	char*  in_ptr  = reinterpret_cast<char*>(const_cast<uint8_t*>(data));
	char*  out_ptr = outbuf;

	while (in_bytes > 0) {
		out_bytes = sizeof(outbuf);
		out_ptr = outbuf;
		size_t ret = iconv(cd, &in_ptr, &in_bytes, &out_ptr, &out_bytes);
		if (ret == static_cast<size_t>(-1)) {
			// On conversion error, skip one byte and retry
			if (errno == EILSEQ && in_bytes > 0) {
				out.append("\xEF\xBF\xBD"); // U+FFFD
				++in_ptr;
				--in_bytes;
				continue;
			}
			break;
		}
		out.append(outbuf, out_ptr - outbuf);
	}

	// Flush any remaining shift state
	out_bytes = sizeof(outbuf);
	out_ptr = outbuf;
	iconv(cd, nullptr, nullptr, &out_ptr, &out_bytes);
	out.append(outbuf, out_ptr - outbuf);

	iconv_close(cd);
}

// ----------------------------------------------------------------
// decode_instr_data  (matches Python MsgInstruction.decode logic)
// ----------------------------------------------------------------
std::string MsgFile::decode_instr_data(const MsgInstrDecoded& ins,
                                       bool is_ending,
                                       const char* encoding) const
{
	const std::vector<uint8_t>& d = ins.raw_data;
	if (d.empty())
		return {};

	// Determine format type
	uint8_t op = ins.opcode;
	char fmt = 0;  // 'm'=xor-text, 'S'=sjis-string, 0=numeric

	// Stage dialogue opcodes
	switch (op) {
	case 1:  case 2:  fmt = 'S'; break;
	case 3:  case 4:  case 5:                     break;
	case 7:  case 8:                              break;
	case 10: case 12: case 14: fmt = 'S';         break;
	case 16: case 17: fmt = 'm';                  break;
	case 18: case 19: case 20:                    break;
	case 21: case 22: case 23:                    break;
	case 25: fmt = 'S';                           break;
	}

	// Ending opcodes override
	if (is_ending) {
		switch (op) {
		case 0:                       break;
		case 3:  fmt = 'm';           break;
		case 5:  case 6: fmt = 'S';   break;
		case 7:  fmt = 'D';           break; // Sz
		case 8:  fmt = 'T';           break; // SSS
		case 9:  fmt = 'S';           break;
		case 10: fmt = 'z';           break;
		case 11:                      break;
		case 12: fmt = 'z';           break;
		case 14: fmt = 'S';           break;
		case 15: case 16: case 17:
			fmt = 'T';                break; // SSS
		}
	}

	// XOR-decrypt 'm' text
	std::vector<uint8_t> decoded;
	if (fmt == 'm') {
		decoded = d;
		util_xor(decoded);
		while (!decoded.empty() && decoded.back() == 0)
			decoded.pop_back();
		std::string out;
		sjis_to_utf8(out, decoded.data(), decoded.size());
		return out;
	}

	// Shift-JIS string (rstrip trailing nulls like Python)
	if (fmt == 'S' || fmt == 'z') {
		size_t len = d.size();
		while (len > 0 && d[len - 1] == 0)
			--len;
		std::string out;
		sjis_to_utf8(out, d.data(), len);
		return out;
	}

	// Sz: string + zero + int
	if (fmt == 'D') {
		auto nul = std::find(d.begin(), d.end(), 0);
		std::string s;
		if (nul != d.begin()) {
			sjis_to_utf8(s, d.data(), nul - d.begin());
		}
		int32_t val = 0;
		size_t off = nul - d.begin() + 1;
		if (off + 4 <= d.size())
			std::memcpy(&val, d.data() + off, 4);
		char buf[64];
		std::snprintf(buf, sizeof(buf), "%s, %d", s.c_str(), val);
		return buf;
	}

	// SSS: three null-separated strings
	if (fmt == 'T') {
		std::string out;
		size_t start = 0;
		int part = 0;
		for (size_t i = 0; i <= d.size(); ++i) {
			if (i == d.size() || d[i] == 0) {
				if (i > start) {
					if (part++ > 0) out += ", ";
					std::string s;
					sjis_to_utf8(s, d.data() + start, i - start);
					out += s;
				}
				start = i + 1;
			}
		}
		return out;
	}

	// Numeric: decode as int
	if (d.size() <= 4) {
		uint8_t buf[4] = {};
		std::memcpy(buf, d.data(), d.size());
		int32_t val = 0;
		std::memcpy(&val, buf, 4);
		char tmp[32];
		std::snprintf(tmp, sizeof(tmp), "%d", val);
		return tmp;
	}

	// Fallback: hex
	std::string hex;
	for (uint8_t b : d) {
		char h[4];
		std::snprintf(h, sizeof(h), "%02X", b);
		hex += h;
	}
	return hex;
}

// ----------------------------------------------------------------
// parse  --  read a raw MSG10 buffer
// ----------------------------------------------------------------
bool MsgFile::parse(const uint8_t* data, size_t size,
                    const char* encoding, bool is_ending)
{
	entries_.clear();

	if (!data || size < 4)
		return false;

	uint32_t entry_count;
	std::memcpy(&entry_count, data, 4);
	if (entry_count == 0 || entry_count > 9999)
		return false;

	size_t off_tab = 4;
	size_t off_tab_size = static_cast<size_t>(entry_count) * 2u * 4u;
	if (off_tab + off_tab_size > size)
		return false;

	entries_.resize(entry_count);
	for (uint32_t i = 0; i < entry_count; ++i) {
		int32_t off1, off2;
		std::memcpy(&off1, data + off_tab + i * 8, 4);
		std::memcpy(&off2, data + off_tab + i * 8 + 4, 4);
		entries_[i].index = static_cast<int32_t>(i);
		entries_[i].extra = off2;
	}

	size_t pos = off_tab + off_tab_size;
	int current_entry = -1;

	while (pos + 4 <= size) {
		uint16_t time;
		uint8_t  opcode;
		uint8_t  length;

		std::memcpy(&time,   data + pos,     2);
		opcode = data[pos + 2];
		length = data[pos + 3];
		pos += 4;

		MsgInstrDecoded ins;
		ins.time   = time;
		ins.opcode = opcode;

		if (length > 0 && pos + length <= size) {
			ins.raw_data.assign(data + pos, data + pos + length);
			pos += length;
		}

		size_t padded = (static_cast<size_t>(length) + 3u) & ~3u;
		pos += padded - length;

		// Entry boundary
		if (time == 0 && opcode == 0) {
			current_entry++;
			if (current_entry < static_cast<int>(entry_count))
				entries_[current_entry].instructions.clear();
			continue;
		}

		if (current_entry >= 0 && current_entry < static_cast<int>(entry_count)) {
			ins.text = decode_instr_data(ins, is_ending, encoding);
			entries_[current_entry].instructions.push_back(std::move(ins));
		}
	}

	return true;
}

// ----------------------------------------------------------------
// dump  --  human-readable output (matches Python dump_msg format)
// ----------------------------------------------------------------
std::string MsgFile::dump() const
{
	std::string out;

	for (const auto& entry : entries_) {
		char hdr[64];
		std::snprintf(hdr, sizeof(hdr), "entry %d (%d)\n",
		              entry.index, entry.extra);
		out += hdr;

		int16_t last_time = -1;
		for (const auto& ins : entry.instructions) {
			if (static_cast<int16_t>(ins.time) != last_time) {
				last_time = static_cast<int16_t>(ins.time);
				char tbuf[32];
				std::snprintf(tbuf, sizeof(tbuf), "@%d\n", last_time);
				out += tbuf;
			}
			out += "\t";
			out += std::to_string(ins.opcode);
			out += ";";
			out += ins.text;
			out += "\n";
		}

		out += "\n";
	}

	return out;
}

} // namespace th10
