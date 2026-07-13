#include "th10/archive/lzss.hpp"
#include "th10/archive/crypt.hpp"
#include "th10/archive/dat.hpp"
#include "th10/platform/file.hpp"

// Keep this harness free of host standard-library headers: the game headers
// intentionally model MSVC 7.1's 32-bit fundamental typedefs.
extern "C" void* malloc(unsigned long size);
extern "C" void free(void* memory);

extern "C" void* _malloc(uint32_t size) {
    return malloc((unsigned long)size);
}

extern "C" void _free(void* memory) {
    free(memory);
}

extern "C" int _stricmp(const char* left, const char* right) {
    for (;;) {
        char a = *left++;
        char b = *right++;
        if (a >= 'A' && a <= 'Z') a = (char)(a + ('a' - 'A'));
        if (b >= 'A' && b <= 'Z') b = (char)(b + ('a' - 'A'));
        if (a != b || a == 0) return (int)(uint8_t)a - (int)(uint8_t)b;
    }
}

class BitWriter {
public:
    BitWriter() : size_(0), bit_(0) {}

    void Bit(bool set) {
        if (bit_ == 0) {
            bytes_[size_++] = 0;
        }
        if (set) {
            bytes_[size_ - 1] |= (uint8_t)(0x80 >> bit_);
        }
        bit_ = (bit_ + 1) & 7;
    }

    void Bits(uint32_t value, uint32_t mask) {
        while (mask != 0) {
            Bit((value & mask) != 0);
            mask >>= 1;
        }
    }

    void Literal(uint8_t value) {
        Bit(true);
        Bits(value, 0x80);
    }

    void BackReference(uint32_t offset, uint32_t length_code) {
        Bit(false);
        Bits(offset, 0x1000);
        Bits(length_code, 8);
    }

    void End() {
        Bit(false);
        Bits(0, 0x1000);
    }

    const uint8_t* Bytes() const { return bytes_; }
    int32_t Size() const { return size_; }

private:
    uint8_t bytes_[64];
    int32_t size_;
    uint32_t bit_;
};

static bool Equal(const uint8_t* left, const char* right, uint32_t size) {
    for (uint32_t index = 0; index < size; ++index) {
        if (left[index] != (uint8_t)right[index]) {
            return false;
        }
    }
    return true;
}

static bool TestLiteralsAndAllocation() {
    BitWriter encoded;
    encoded.Literal('H');
    encoded.Literal('E');
    encoded.Literal('L');
    encoded.Literal('L');
    encoded.Literal('O');
    encoded.End();

    uint8_t* decoded = Dat_LzssDecompress(
        encoded.Bytes(), encoded.Size(), 0, 5);
    bool passed = decoded != 0 && Equal(decoded, "HELLO", 5);
    free(decoded);
    return passed;
}

static bool TestOverlappingBackReference() {
    BitWriter encoded;
    encoded.Literal('A');
    encoded.Literal('B');
    encoded.BackReference(1, 1); // four bytes copied from dictionary offset 1
    encoded.End();

    uint8_t decoded[6] = {0};
    uint8_t* result = Dat_LzssDecompress(
        encoded.Bytes(), encoded.Size(), decoded, sizeof(decoded));
    return result == decoded && Equal(decoded, "ABABAB", sizeof(decoded));
}

static bool TestRetailArchiveHeader() {
    uint8_t header[16] = {
        0x13, 0x55, 0xB3, 0xB0, 0xF0, 0xF4, 0x54, 0xD4,
        0xCB, 0xD4, 0x9F, 0x77, 0xF4, 0x8B, 0x5C, 0x00,
    };
    DatArchiveHeader decoded;
    return DatArchive_DecodeHeader(header, &decoded) &&
        decoded.magic == 0x31414854 &&
        decoded.entry_list_size == 3416 &&
        decoded.entry_list_compressed_size == 1886 &&
        decoded.entry_count == 138;
}

static bool TestRetailCryptParameterTable() {
    static const DatCryptParams expected[8] = {
        {0x1B, 0x37, 0x0040, 0x2800},
        {0x51, 0xE9, 0x0040, 0x3000},
        {0xC1, 0x51, 0x0080, 0x3200},
        {0x03, 0x19, 0x0400, 0x7800},
        {0xAB, 0xCD, 0x0200, 0x2800},
        {0x12, 0x34, 0x0080, 0x3200},
        {0x35, 0x97, 0x0080, 0x2800},
        {0x99, 0x37, 0x0400, 0x2000},
    };
    for (uint32_t index = 0; index < 8; ++index) {
        if (g_dat_crypt_params[index].key != expected[index].key ||
            g_dat_crypt_params[index].step != expected[index].step ||
            g_dat_crypt_params[index].block_size != expected[index].block_size ||
            g_dat_crypt_params[index].byte_limit != expected[index].byte_limit) {
            return false;
        }
    }
    return Dat_GetCryptParamIndex("a") == ('a' & 7) &&
        Dat_GetCryptParams("a") ==
            &g_dat_crypt_params[Dat_GetCryptParamIndex("a")];
}

static void EncryptBlockForTest(
        const uint8_t* plain,
        uint8_t* encrypted,
        uint32_t size,
        uint8_t key,
        uint8_t step) {
    uint32_t source = 0;
    for (int32_t destination = (int32_t)size - 1;
            destination >= 0; destination -= 2) {
        encrypted[source++] = plain[destination] ^ key;
        key = (uint8_t)(key + step);
    }
    for (int32_t destination = (int32_t)size - 2;
            destination >= 0; destination -= 2) {
        encrypted[source++] = plain[destination] ^ key;
        key = (uint8_t)(key + step);
    }
}

class MemoryFile : public FileInterface {
public:
    MemoryFile(uint8_t* data, uint32_t size)
        : data_(data), size_(size), position_(0) {}

    virtual BYTE Open(const char*, const char*) {
        position_ = 0;
        return 1;
    }
    virtual void Close() {}
    virtual DWORD Read(void* destination, DWORD size) {
        if (position_ + size > size_) return 0;
        uint8_t* output = (uint8_t*)destination;
        for (DWORD index = 0; index < size; ++index) {
            output[index] = data_[position_ + index];
        }
        position_ += size;
        return size;
    }
    virtual BYTE Write(const void*, DWORD) { return 0; }
    virtual DWORD Tell() const { return position_; }
    virtual DWORD GetSize() const { return size_; }
    virtual BYTE Seek(LONG distance, DWORD origin) {
        if (origin != 0 || distance < 0 || (DWORD)distance > size_) return 0;
        position_ = (DWORD)distance;
        return 1;
    }
    virtual void* ReadWhole(DWORD) { return 0; }

private:
    uint8_t* data_;
    DWORD size_;
    DWORD position_;
};

static bool TestEntryDataDecode() {
    uint8_t plain[64];
    uint8_t encrypted[64];
    uint8_t decoded[64] = {0};
    for (uint32_t index = 0; index < sizeof(plain); ++index) {
        plain[index] = (uint8_t)(index * 3 + 1);
    }
    const char* name = "a";
    const DatCryptParams* params = Dat_GetCryptParams(name);
    EncryptBlockForTest(
        plain, encrypted, sizeof(encrypted), params->key, params->step);

    DatEntry entries[2] = {
        {name, 0x20, sizeof(plain), 0},
        {0, 0x60, 0, 0},
    };
    uint8_t* result = DatArchive_DecodeEntryData(entries, encrypted, decoded);
    if (result != decoded ||
            DatEntry_GetCompressedSize(entries) != sizeof(plain)) {
        return false;
    }
    for (uint32_t index = 0; index < sizeof(plain); ++index) {
        if (decoded[index] != plain[index]) {
            return false;
        }
    }
    return true;
}

static bool TestArchiveEntryRead() {
    uint8_t plain[64];
    uint8_t file_data[96] = {0};
    uint8_t decoded[64] = {0};
    for (uint32_t index = 0; index < sizeof(plain); ++index) {
        plain[index] = (uint8_t)(0xA5 ^ index);
    }

    const char* name = "a";
    const DatCryptParams* params = Dat_GetCryptParams(name);
    EncryptBlockForTest(
        plain,
        file_data + 32,
        sizeof(plain),
        params->key,
        params->step);

    DatEntry entries[2] = {
        {name, 32, sizeof(plain), 0},
        {0, sizeof(file_data), 0, 0},
    };
    MemoryFile file(file_data, sizeof(file_data));
    DatArchive archive;
    DatArchive_Initialize(&archive);
    archive.entries = entries;
    archive.entry_count = 1;
    archive.file = &file;

    if (DatArchive_Read(&archive, "A", decoded) != decoded ||
            file.Tell() != sizeof(file_data)) {
        return false;
    }
    for (uint32_t index = 0; index < sizeof(plain); ++index) {
        if (decoded[index] != plain[index]) return false;
    }
    return true;
}

static void WriteU32(uint8_t* destination, uint32_t value) {
    destination[0] = (uint8_t)value;
    destination[1] = (uint8_t)(value >> 8);
    destination[2] = (uint8_t)(value >> 16);
    destination[3] = (uint8_t)(value >> 24);
}

static bool TestArchiveOpenAndRead() {
    uint8_t packed_entry[16] = {0};
    packed_entry[0] = 'a';
    WriteU32(packed_entry + 4, 16);
    WriteU32(packed_entry + 8, 64);

    BitWriter encoded_table;
    for (uint32_t index = 0; index < sizeof(packed_entry); ++index) {
        encoded_table.Literal(packed_entry[index]);
    }
    encoded_table.End();

    uint8_t file_data[128] = {0};
    uint8_t decoded[64] = {0};
    uint8_t asset[64];
    for (uint32_t index = 0; index < sizeof(asset); ++index) {
        asset[index] = (uint8_t)(index + 0x31);
    }

    const DatCryptParams* asset_params = Dat_GetCryptParams("a");
    EncryptBlockForTest(
        asset,
        file_data + 16,
        sizeof(asset),
        asset_params->key,
        asset_params->step);

    uint32_t table_offset = 80;
    uint32_t table_compressed_size = (uint32_t)encoded_table.Size();
    // The retail cipher deliberately leaves a trailing fragment smaller than
    // one quarter of its 0x80-byte block untouched.
    for (uint32_t index = 0; index < table_compressed_size; ++index) {
        file_data[table_offset + index] = encoded_table.Bytes()[index];
    }

    uint8_t header[16];
    WriteU32(header, 0x31414854);
    WriteU32(header + 4, 123456789 + sizeof(packed_entry));
    WriteU32(header + 8, 987654321 + table_compressed_size);
    WriteU32(header + 12, 135792468 + 1);
    EncryptBlockForTest(header, file_data, sizeof(header), 0x1B, 0x37);

    MemoryFile* file = new MemoryFile(
        file_data, table_offset + table_compressed_size);
    DatArchive archive;
    DatArchive_Initialize(&archive);
    if (!DatArchive_Open(&archive, file, "synthetic.dat")) {
        return false;
    }
    bool passed = archive.entry_count == 1 && archive.entries != 0 &&
        archive.entries[0].offset == 16 &&
        archive.entries[0].uncompressed_size == sizeof(asset) &&
        archive.entries[1].offset == table_offset &&
        DatArchive_Read(&archive, "A", decoded) == decoded;
    for (uint32_t index = 0; passed && index < sizeof(asset); ++index) {
        if (decoded[index] != asset[index]) passed = false;
    }
    DatArchive_Close(&archive);
    return passed && archive.entries == 0 && archive.filename == 0 &&
        archive.file == 0 && archive.entry_count == 0;
}

static bool TestPackedEntryTable() {
    uint8_t packed[36] = {0};
    packed[0] = 'a'; packed[1] = '.'; packed[2] = 't'; packed[3] = 'x';
    packed[4] = 't';
    WriteU32(packed + 8, 0x20);
    WriteU32(packed + 12, 3);
    WriteU32(packed + 16, 7);
    packed[20] = 'b';
    WriteU32(packed + 24, 0x30);
    WriteU32(packed + 28, 4);
    WriteU32(packed + 32, 8);

    DatEntry* entries = DatArchive_ParseEntries(packed, 2, 0x40);
    if (!entries) return false;
    DatArchiveIndex archive = {entries, 2};
    const DatEntry* found = DatArchive_FindEntry(&archive, "A.TXT");
    bool passed = found == entries && found->offset == 0x20 &&
        found->uncompressed_size == 3 && found->unknown == 7 &&
        entries[1].offset == 0x30 && entries[2].offset == 0x40 &&
        DatArchive_FindSize(&archive, "B") == 4 &&
        DatArchive_FindSize(&archive, "missing") == 0 &&
        DatArchive_FindEntry(&archive, "missing") == 0;
    DatArchive_FreeEntries(entries, 2);
    return passed;
}

int main() {
    if (!TestLiteralsAndAllocation()) {
        return 1;
    }
    if (!TestOverlappingBackReference()) {
        return 2;
    }
    if (!TestRetailArchiveHeader()) {
        return 3;
    }
    if (!TestRetailCryptParameterTable()) {
        return 4;
    }
    if (!TestEntryDataDecode()) {
        return 5;
    }
    if (!TestArchiveEntryRead()) {
        return 6;
    }
    if (!TestArchiveOpenAndRead()) {
        return 7;
    }
    if (!TestPackedEntryTable()) {
        return 8;
    }
    return 0;
}
