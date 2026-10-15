#include "archive.hpp"
#ifndef ARCHIVE_READ_SECTION
#define ARCHIVE_READ_SECTION ".text$a00read"
#endif
#pragma code_seg(ARCHIVE_READ_SECTION)
extern "C" __declspec(noinline) unsigned char* __stdcall DatArchiveRead(
        DatArchive* archive, const char* name, unsigned char* output) {
    if (!archive->file)
        return 0;
    DatArchiveEntry* entry = ArchiveFind(archive, name);
    if (entry) {
        unsigned int stored_size = entry[1].offset - entry->offset;
        unsigned int uncompressed_size = entry->uncompressed_size;
        unsigned char* encrypted;
        if (stored_size == uncompressed_size && output)
            encrypted = output;
        else
            encrypted = static_cast<unsigned char*>(asm_malloc_00452706(stored_size));
        if (encrypted) {
            if (archive->file->Seek(static_cast<LONG>(entry->offset), 0) &&
                archive->file->Read(encrypted, stored_size)) {
                const char* stored_name = entry->name;
                int length = static_cast<int>(strlen(stored_name));
                unsigned char checksum = 0;
                const unsigned char* character = reinterpret_cast<const unsigned char*>(stored_name);
                for (int remaining = length; remaining != 0; --remaining)
                    checksum = static_cast<unsigned char>(checksum + *character++);
                unsigned char cipher_index = static_cast<unsigned char>(static_cast<int>(checksum) % 8);
                DatDecrypt(encrypted, static_cast<int>(stored_size), g_dat_read_crypt_parameters[cipher_index].key,
                           g_dat_read_crypt_parameters[cipher_index].step, g_dat_read_crypt_parameters[cipher_index].block_size, g_dat_read_crypt_parameters[cipher_index].byte_limit);
                unsigned char* result;
                if (stored_size != uncompressed_size)
                    result = DecompressDatLzss_00435dc0(encrypted, static_cast<int>(stored_size),
                                                     output, uncompressed_size);
                else
                    result = encrypted;
                if (encrypted != output && encrypted)
                    asm_free_00452422(encrypted);
                return result;
            }
            asm_free_00452422(encrypted);
        }
    }
    return 0;
}
#pragma code_seg()
