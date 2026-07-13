#include "dat_reader.h"
#include "th_decrypt.h"
#include "lzss.h"
#include <cstring>
#include <algorithm>
#include <stdexcept>

namespace th10 {

static constexpr uint32_t HDR_OFFSET_ADD = 123456789;
static constexpr uint32_t HDR_ZSIZE_ADD  = 987654321;
static constexpr uint32_t HDR_COUNT_ADD  = 135792468;

static const CryptParams th95_crypt_params[] = {
    { 0, 0x1b, 0x37, 0x40,  0x2800 },
    { 0, 0x51, 0xe9, 0x40,  0x3000 },
    { 0, 0xc1, 0x51, 0x80,  0x3200 },
    { 0, 0x03, 0x19, 0x400, 0x7800 },
    { 0, 0xab, 0xcd, 0x200, 0x2800 },
    { 0, 0x12, 0x34, 0x80,  0x3200 },
    { 0, 0x35, 0x97, 0x80,  0x2800 },
    { 0, 0x99, 0x37, 0x400, 0x2000 },
};

static unsigned get_crypt_param_index(const char* name) {
    unsigned char idx = 0;
    while (*name) idx += (unsigned char)*name++;
    return idx & 7;
}

static const CryptParams* get_crypt_params(const char* name) {
    return &th95_crypt_params[get_crypt_param_index(name)];
}

DatArchive::DatArchive(const std::string& path) : path_(path) {}

DatArchive::~DatArchive() { close(); }

bool DatArchive::open() {
    file_ = fopen(path_.c_str(), "rb");
    if (!file_) return false;

    uint32_t header[4];
    if (fread(header, sizeof(header), 1, file_) != 1) { close(); return false; }

    th_decrypt((uint8_t*)header, sizeof(header), 0x1b, 0x37, sizeof(header), sizeof(header));

    if (memcmp(header, "THA1", 4) != 0) { close(); return false; }

    uint32_t list_size   = header[1] - HDR_OFFSET_ADD;
    uint32_t list_zsize  = header[2] - HDR_ZSIZE_ADD;
    uint32_t entry_count = header[3] - HDR_COUNT_ADD;

    fseek(file_, 0, SEEK_END);
    long file_size = ftell(file_);

    long entry_table_start = file_size - list_zsize;
    if (entry_table_start < (long)sizeof(header)) { close(); return false; }

    std::vector<uint8_t> zdata(list_zsize);
    fseek(file_, entry_table_start, SEEK_SET);
    if (fread(zdata.data(), 1, list_zsize, file_) != list_zsize) { close(); return false; }

    th_decrypt(zdata.data(), list_zsize, 0x3e, 0x9b, 0x80, list_zsize);

    std::vector<uint8_t> list_data = lzss_decompress(zdata.data(), zdata.size(), list_size);
    if (list_data.size() < list_size) { close(); return false; }

    entries_.reserve(entry_count);

    const uint8_t* ptr = list_data.data();
    const uint8_t* end = ptr + list_data.size();

    for (uint32_t i = 0; i < entry_count && ptr < end; i++) {
        const char* name = (const char*)ptr;
        size_t name_len = strnlen(name, end - ptr);
        if (name_len == 0) break;

        size_t padded_len = name_len + (4 - name_len % 4);
        if (ptr + padded_len + 12 > end) break;

        DatEntry entry;
        entry.name = std::string(name, name_len);
        ptr += padded_len;

        entry.offset = *(uint32_t*)ptr; ptr += 4;
        entry.uncompressed_size = *(uint32_t*)ptr; ptr += 4;
        ptr += 4;
        entry.compressed_size = 0;

        entries_.push_back(entry);
    }

    for (size_t i = 0; i + 1 < entries_.size(); i++) {
        entries_[i].compressed_size = entries_[i + 1].offset - entries_[i].offset;
    }
    if (!entries_.empty()) {
        entries_.back().compressed_size = (file_size - list_zsize) - entries_.back().offset;
    }

    return true;
}

void DatArchive::close() {
    if (file_) { fclose(file_); file_ = nullptr; }
    entries_.clear();
}

int DatArchive::find_entry(const std::string& name) const {
    for (size_t i = 0; i < entries_.size(); i++)
        if (entries_[i].name == name) return (int)i;
    return -1;
}

std::vector<uint8_t> DatArchive::read_file(const std::string& name) {
    int idx = find_entry(name);
    if (idx < 0) return {};
    return read_file((size_t)idx);
}

std::vector<uint8_t> DatArchive::read_file(size_t index) {
    if (index >= entries_.size() || !file_) return {};

    const DatEntry& entry = entries_[index];
    std::vector<uint8_t> zdata(entry.compressed_size);

    fseek(file_, (long)entry.offset, SEEK_SET);
    if (fread(zdata.data(), 1, entry.compressed_size, file_) != entry.compressed_size)
        return {};

    auto params = get_crypt_params(entry.name.c_str());
    th_decrypt(zdata.data(), zdata.size(), params->key, params->step,
               params->block, params->limit);

    if (entry.compressed_size == entry.uncompressed_size) {
        return zdata;
    }

    return lzss_decompress(zdata.data(), zdata.size(), entry.uncompressed_size);
}

} // namespace th10
