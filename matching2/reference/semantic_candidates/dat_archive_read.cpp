// Semantic candidate for 0x00434DD0..0x00434EE8 (281 bytes).
// Retail takes name in ECX, archive/output on the stack, and RET 8.
// This conventional stdcall interface is for semantic validation; native
// LTCG must recover the entry and FindEntry/cipher call conventions.
#include "dat_archive_types.hpp"

extern "C" unsigned char* __stdcall DatArchive_Read_00434dd0(
        DatArchive* archive, const char* name, unsigned char* output) {
    if (!archive->file)
        return 0;
    DatArchiveEntry* entry = Archive_FindEntry_00434f30(archive, name);
    if (!entry)
        return 0;

    // The next record, including the final sentinel, supplies the stored end.
    unsigned int stored_size = entry[1].offset - entry->offset;
    unsigned int uncompressed_size = entry->uncompressed_size;
    unsigned char* encrypted = output;
    if (stored_size != uncompressed_size || !encrypted) {
        encrypted = static_cast<unsigned char*>(asm_malloc_00452706(stored_size));
        if (!encrypted)
            return 0;
    }

    if (!archive->file->Seek(static_cast<LONG>(entry->offset), 0) ||
        !archive->file->Read(encrypted, stored_size)) {
        // Retail releases the supplied output too when it was reused here.
        asm_free_00452422(encrypted);
        return 0;
    }

    // Use the stored entry name, including its original casing, to choose
    // the content cipher. Lookup's requested name can differ in case.
    unsigned char checksum = 0;
    const unsigned char* character =
        reinterpret_cast<const unsigned char*>(entry->name);
    while (*character)
        checksum = static_cast<unsigned char>(checksum + *character++);
    const DatCryptParameters& parameters = g_dat_read_crypt_parameters[checksum & 7];
    Dat_Decrypt_0044b0d0(encrypted, static_cast<int>(stored_size),
                       parameters.key, parameters.step,
                       parameters.block_size, parameters.byte_limit);

    unsigned char* result = encrypted;
    if (stored_size != uncompressed_size)
        result = DecompressDatLzss_00435dc0(encrypted, static_cast<int>(stored_size),
                                         output, uncompressed_size);

    // This comparison is not an ownership flag. For an uncompressed entry
    // with output == 0, retail frees encrypted and then returns that address.
    if (encrypted != output && encrypted)
        asm_free_00452422(encrypted);
    return result;
}
