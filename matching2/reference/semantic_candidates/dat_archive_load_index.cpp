// Semantic candidate for 0x00434F70..0x004350CD (350 bytes).
// Retail: archive in ESI, path on stack, boolean result in AL, RET 4.
// This ordinary stdcall entry exposes both parameters for behavioral tests.
#include "dat_archive_types.hpp"

extern "C" const char* g_dat_archive_read_mode;
extern "C" DatArchiveEntry* __stdcall DatArchive_BuildIndex_004350d0(
    const unsigned char* packed_records, int record_count,
    unsigned int terminal_data_offset);

struct EncodedDatHeader {
    unsigned int magic;
    unsigned int unpacked_size;
    unsigned int stored_size;
    unsigned int entry_count;
};

extern "C" bool __stdcall DatArchive_LoadIndex_00434f70(
        DatArchive* archive, const char* path) {
    if (!archive->file)
        return false;

    unsigned char* compressed = 0;
    unsigned char* unpacked = 0;
    EncodedDatHeader header;
    if (!archive->file->Open(path, g_dat_archive_read_mode))
        goto failure;
    if (!archive->file->Read(&header, sizeof(header)))
        goto failure;
    Dat_Decrypt_0044b0d0(reinterpret_cast<unsigned char*>(&header),
                       sizeof(header), 0x1B, 0x37, 16, 16);
    if (header.magic != 0x31414854) // "THA1"
        goto failure;

    header.unpacked_size -= 123456789u;
    archive->entry_count = static_cast<int>(header.entry_count - 135792468u);
    header.stored_size -= 987654321u;
    {
        unsigned int file_size = archive->file->GetSize();
        unsigned int table_offset = file_size - header.stored_size;
        // Retail neither checks for unsigned subtraction wrap nor tests the
        // seek result. It proceeds with allocation and the following read.
        archive->file->Seek(static_cast<LONG>(table_offset), 0);
        unsigned int stored_size = header.stored_size;
        compressed = static_cast<unsigned char*>(asm_malloc_00452706(stored_size));
        if (!compressed)
            goto failure;
        if (!archive->file->Read(compressed, stored_size))
            goto failure;
        Dat_Decrypt_0044b0d0(compressed, static_cast<int>(stored_size),
                           0x3E, 0x9B, 128, static_cast<int>(stored_size));
        unpacked = DecompressDatLzss_00435dc0(
            compressed, static_cast<int>(stored_size), 0, header.unpacked_size);
        if (!unpacked)
            goto failure;
        archive->entries = DatArchive_BuildIndex_004350d0(
            unpacked, archive->entry_count, table_offset);
        if (!archive->entries)
            goto failure;
    }

    asm_free_00452422(compressed);
    asm_free_00452422(unpacked);
    return true;

failure:
    if (compressed)
        asm_free_00452422(compressed);
    if (unpacked)
        asm_free_00452422(unpacked);
    delete archive->file;
    archive->file = 0;
    // The decoded count and any previous entries survive failures before
    // BuildIndex; a failed BuildIndex has already assigned entries = 0.
    return false;
}
