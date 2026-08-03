#include "th10/archive/dat.hpp"
#include "th10/archive/crypt.hpp"
#include "th10/archive/lzss.hpp"
#include "th10/platform/file.hpp"

extern "C" int __cdecl _stricmp(const char* left, const char* right);
extern "C" void* __cdecl _malloc(uint32_t size);
extern "C" void __cdecl _free(void* memory);

#ifdef _MSC_VER
extern "C" void sub_434D10(void*);
#endif

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

// Clean reconstruction of 0x00434F70. The retail routine opens the selected
// FileInterface, decodes the 16-byte THA1 header, then reads the compressed
// entry table from the end of the file and installs the parsed entries.
bool DatArchive_LoadIndex(DatArchive* archive, const char* path) {
    if (!archive->file || !archive->file->Open(path, "r")) {
        return false;
    }

    uint8_t encrypted_header[16];
    if (archive->file->Read(encrypted_header, sizeof(encrypted_header)) !=
            sizeof(encrypted_header)) {
        return false;
    }

    DatArchiveHeader header;
    if (!DatArchive_DecodeHeader(encrypted_header, &header)) {
        return false;
    }

    uint32_t file_size = archive->file->GetSize();
    if (header.entry_list_compressed_size > file_size) {
        return false;
    }
    uint32_t table_offset = file_size - header.entry_list_compressed_size;
    if (!archive->file->Seek((LONG)table_offset, 0)) {
        return false;
    }

    uint8_t* compressed = (uint8_t*)_malloc(
        header.entry_list_compressed_size);
    if (!compressed) {
        return false;
    }
    if (archive->file->Read(
            compressed,
            header.entry_list_compressed_size) !=
            header.entry_list_compressed_size) {
        _free(compressed);
        return false;
    }

    Dat_Decrypt(
        compressed,
        header.entry_list_compressed_size,
        0x3E,
        0x9B,
        0x80,
        header.entry_list_compressed_size);
    uint8_t* packed_entries = Dat_LzssDecompress(
        compressed,
        header.entry_list_compressed_size,
        0,
        header.entry_list_size);
    _free(compressed);
    if (!packed_entries) {
        return false;
    }

    archive->entry_count = (int32_t)header.entry_count;
    archive->entries = DatArchive_ParseEntries(
        packed_entries,
        header.entry_count,
        table_offset);
    _free(packed_entries);
    if (!archive->entries) {
        archive->entry_count = 0;
        return false;
    }
    return true;
}

void DatArchive_Initialize(DatArchive* archive) {
    archive->entries = 0;
    archive->entry_count = 0;
    archive->filename = 0;
    archive->file = 0;
}

// 0x00434C20 - Thin reset entry point used by the archive owner.
#ifdef _MSC_VER
__declspec(naked) void DatArchive_Reset(DatArchive* archive) {
    __asm {
        push esi
        mov esi, ecx
        call sub_434D10
        pop esi
        ret
    }
}
#else
void DatArchive_Reset(DatArchive* archive) {
    DatArchive_Close(archive);
}
#endif

// Clean reconstruction of 0x00434D10.
void DatArchive_Close(DatArchive* archive) {
    if (archive->filename) {
        _free(archive->filename);
        archive->filename = 0;
    }
    DatArchive_FreeEntries(
        archive->entries,
        (uint32_t)archive->entry_count);
    archive->entries = 0;
    archive->entry_count = 0;
    if (archive->file) {
        delete archive->file;
        archive->file = 0;
    }
}

// File-backed form of the initialization path at 0x00434C30.
bool DatArchive_Open(
        DatArchive* archive,
        FileInterface* owned_file,
        const char* path) {
    DatArchive_Close(archive);
    archive->file = owned_file;
    if (!archive->file || !DatArchive_LoadIndex(archive, path)) {
        DatArchive_Close(archive);
        return false;
    }

    archive->filename = DuplicateString(path, StringSize(path));
    if (!archive->filename ||
            !archive->file->Open(archive->filename, "r")) {
        DatArchive_Close(archive);
        return false;
    }
    return true;
}

// Clean reconstruction of 0x00434DD0.
uint8_t* DatArchive_Read(
        DatArchive* archive,
        const char* name,
        uint8_t* output) {
    if (!archive->file) {
        return 0;
    }
    const DatEntry* entry = DatArchive_FindEntry(archive, name);
    if (!entry) {
        return 0;
    }

    uint32_t compressed_size = DatEntry_GetCompressedSize(entry);
    uint8_t* encrypted = output;
    if (compressed_size != entry->uncompressed_size || !encrypted) {
        encrypted = (uint8_t*)_malloc(compressed_size);
        if (!encrypted) {
            return 0;
        }
    }

    if (!archive->file->Seek((LONG)entry->offset, 0) ||
            archive->file->Read(encrypted, compressed_size) == 0) {
        _free(encrypted);
        return 0;
    }

    uint8_t* decoded = DatArchive_DecodeEntryData(entry, encrypted, output);
    if (encrypted != output && compressed_size != entry->uncompressed_size) {
        _free(encrypted);
    }
    return decoded;
}

// Clean reconstruction of 0x00434F30. The retail function receives archive in
// EAX and name in EBX; the typed implementation uses a conventional C++ API.
#ifdef _MSC_VER
__declspec(naked) const DatEntry* DatArchive_FindEntry(
        const DatArchiveIndex* archive, const char* name) {
    __asm {
        push edi
        mov edi, [eax]
        test edi, edi
        jnz loc_434F3B
        xor eax, eax
        pop edi
        ret
loc_434F3B:
        push esi
        mov esi, [eax+4]
        test esi, esi
        jle loc_434F5B
loc_434F43:
        mov eax, [edi]
        push eax
        push ebx
        call __stricmp
        add esp, 8
        test eax, eax
        jz loc_434F60
        dec esi
        add edi, 10h
        test esi, esi
        jg loc_434F43
loc_434F5B:
        pop esi
        xor eax, eax
        pop edi
        ret
loc_434F60:
        pop esi
        mov eax, edi
        pop edi
        ret
    }
}
#else
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
#endif

// Clean reconstruction of 0x00434EF0.
#ifdef _MSC_VER
__declspec(naked) uint32_t DatArchive_FindSize(
        const DatArchiveIndex* archive, const char* name) {
    __asm {
        push esi
        push edi
        mov edi, [eax]
        test edi, edi
        jz loc_434F18
        mov esi, [eax+4]
        test esi, esi
        jle loc_434F18
        nop
loc_434F00:
        mov eax, [edi]
        push eax
        push ebx
        call __stricmp
        add esp, 8
        test eax, eax
        jz loc_434F1D
        dec esi
        add edi, 10h
        test esi, esi
        jg loc_434F00
loc_434F18:
        pop edi
        xor eax, eax
        pop esi
        ret
loc_434F1D:
        mov eax, [edi+8]
        pop edi
        pop esi
        ret
    }
}
#else
uint32_t DatArchive_FindSize(
        const DatArchiveIndex* archive, const char* name) {
    const DatEntry* entry = DatArchive_FindEntry(archive, name);
    return entry ? entry->uncompressed_size : 0;
}
#endif

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

// Clean reconstruction of 0x004350D0. Retail allocates entry_count + 1
// records, copies each aligned packed name and its three metadata words, then
// appends a sentinel whose offset marks the end of the final data payload.
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
        entries[index].reserved_metadata = ReadU32(source + 8);
        source += 12;
    }

    entries[entry_count].name = 0;
    entries[entry_count].offset = data_end_offset;
    entries[entry_count].uncompressed_size = 0;
    entries[entry_count].reserved_metadata = 0;
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
