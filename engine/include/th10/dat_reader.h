/*
 * DAT Archive Reader for TH10 format
 * Reads th10.dat archives with LZSS decompression and type-based decryption
 */
#pragma once
#include "th10/types.h"
#include <vector>
#include <string>
#include <memory>
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
    int find_entry(const std::string& name) const;

private:
    bool read_header();
    bool decrypt_entry(size_t index, std::vector<uint8_t>& data);

    std::string  path_;
    FILE*        file_ = nullptr;
    std::vector<DatEntry> entries_;
};

} // namespace th10
