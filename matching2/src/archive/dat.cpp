#include "th10/archive/dat.hpp"
#include "th10/archive/crypt.hpp"
#include "th10/archive/lzss.hpp"

extern "C" int __cdecl _stricmp(const char* left, const char* right);
extern "C" void* __cdecl _malloc(uint32_t size);
extern "C" void __cdecl _free(void* memory);

namespace {

const uint32_t kArchiveMagic = 0x31414854; // "THA1"
const uint32_t kHeaderListSizeBias = 123456789;
const uint32_t kHeaderCompressedSizeBias = 987654321;
const uint32_t kHeaderEntryCountBias = 135792468;

uint32_t ReadU32(const uint8_t* source) {
    return (uint32_t)source[0] |
        (uint32_t)source[1] << 8 |
        (uint32_t)source[2] << 16 |
        (uint32_t)source[3] << 24;
}

uint32_t StringSize(const char* text) {
    const char* cursor = text;
    while (*cursor != 0) {
        ++cursor;
    }
    return (uint32_t)(cursor - text) + 1;
}

char* DuplicateString(const char* text, uint32_t size) {
    char* copy = (char*)_malloc(size);
    if (copy) {
        for (uint32_t index = 0; index < size; ++index) {
            copy[index] = text[index];
        }
    }
    return copy;
}

} // namespace

// Clean reconstruction of 0x00434F30. The retail function receives archive in
// EAX and name in EBX; the typed implementation uses a conventional C++ API.
const DatEntry* DatArchive_FindEntry(
        const DatArchiveIndex* archive, const char* name) {
    if (!archive->entries) {
        return 0;
    }

    const DatEntry* entry = archive->entries;
    for (int32_t remaining = archive->entry_count;
            remaining > 0; --remaining, ++entry) {
        if (_stricmp(name, entry->name) == 0) {
            return entry;
        }
    }
    return 0;
}

// Clean reconstruction of 0x00434EF0.
uint32_t DatArchive_FindSize(
        const DatArchiveIndex* archive, const char* name) {
    const DatEntry* entry = DatArchive_FindEntry(archive, name);
    return entry ? entry->uncompressed_size : 0;
}

uint32_t DatEntry_GetCompressedSize(const DatEntry* entry) {
    return entry[1].offset - entry[0].offset;
}

// Data-transforming half of 0x00434DD0. File seek/read stays outside this
// helper, making the archive cipher and decompressor independently testable.
uint8_t* DatArchive_DecodeEntryData(
        const DatEntry* entry,
        uint8_t* encrypted_data,
        uint8_t* output) {
    uint32_t compressed_size = DatEntry_GetCompressedSize(entry);
    const DatCryptParams* params = Dat_GetCryptParams(entry->name);
    Dat_Decrypt(
        encrypted_data,
        compressed_size,
        params->key,
        params->step,
        params->block_size,
        params->byte_limit);

    if (compressed_size != entry->uncompressed_size) {
        return Dat_LzssDecompress(
            encrypted_data,
            compressed_size,
            output,
            entry->uncompressed_size);
    }

    if (output && output != encrypted_data) {
        for (uint32_t index = 0; index < compressed_size; ++index) {
            output[index] = encrypted_data[index];
        }
        return output;
    }
    return encrypted_data;
}

bool DatArchive_DecodeHeader(
        uint8_t encrypted_header[16], DatArchiveHeader* header) {
    Dat_Decrypt(encrypted_header, 16, 0x1B, 0x37, 0x10, 0x10);
    header->magic = ReadU32(encrypted_header);
    if (header->magic != kArchiveMagic) {
        return false;
    }

    header->entry_list_size =
        ReadU32(encrypted_header + 4) - kHeaderListSizeBias;
    header->entry_list_compressed_size =
        ReadU32(encrypted_header + 8) - kHeaderCompressedSizeBias;
    header->entry_count =
        ReadU32(encrypted_header + 12) - kHeaderEntryCountBias;
    return true;
}

DatEntry* DatArchive_ParseEntries(
        const uint8_t* packed_entries,
        uint32_t entry_count,
        uint32_t data_end_offset) {
    DatEntry* entries = (DatEntry*)_malloc(
        (entry_count + 1) * (uint32_t)sizeof(DatEntry));
    if (!entries) {
        return 0;
    }

    const uint8_t* source = packed_entries;
    for (uint32_t index = 0; index < entry_count; ++index) {
        uint32_t name_size = StringSize((const char*)source);
        entries[index].name = DuplicateString((const char*)source, name_size);
        source += (name_size + 3) & ~3U;
        entries[index].offset = ReadU32(source);
        entries[index].uncompressed_size = ReadU32(source + 4);
        entries[index].unknown = ReadU32(source + 8);
        source += 12;
    }

    entries[entry_count].name = 0;
    entries[entry_count].offset = data_end_offset;
    entries[entry_count].uncompressed_size = 0;
    entries[entry_count].unknown = 0;
    return entries;
}

void DatArchive_FreeEntries(DatEntry* entries, uint32_t entry_count) {
    if (!entries) {
        return;
    }
    for (uint32_t index = 0; index < entry_count; ++index) {
        if (entries[index].name) {
            _free((void*)entries[index].name);
        }
    }
    _free(entries);
}
