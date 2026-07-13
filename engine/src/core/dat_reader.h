#pragma once
#include "th_decrypt.h"
#include "lzss.h"
#include "util_xor.h"
#include <vector>
#include <string>
#include <cstdio>

namespace th10 {

struct DatEntry {
    std::string name;
    uint32_t    extra;
    size_t      offset;
    size_t      compressed_size;
    size_t      uncompressed_size;
};

class DatArchive {
public:
    explicit DatArchive(const std::string& path);
    ~DatArchive();

    bool open();
    void close();

    const std::vector<DatEntry>& entries() const { return entries_; }

    std::vector<uint8_t> read_file(const std::string& name);
    std::vector<uint8_t> read_file(size_t index);

    size_t entry_count() const { return entries_.size(); }
    int    find_entry(const std::string& name) const;

private:
    bool read_header();
    bool decrypt_entry(const uint8_t* data, size_t size, std::vector<uint8_t>& out);

    std::string        path_;
    FILE*              file_ = nullptr;
    std::vector<DatEntry> entries_;
};

} // namespace th10
