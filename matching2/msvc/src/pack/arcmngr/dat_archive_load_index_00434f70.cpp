// 0x00434F70: open, decode and publish a DAT archive index.
// The complete Version -> Open caller graph derives the private ESI receiver.
#include "../../../layout/ltcg/archive_index_00434f70/archive.hpp"
#include "../../../layout/ltcg/archive_index_00434f70/parser.hpp"
extern "C" const char* g_dat_archive_read_mode;
#pragma code_seg(".text$a10index")
struct EncodedDatHeader {
    unsigned int magic;
    unsigned int unpacked_size;
    unsigned int stored_size;
    unsigned int entry_count;
};

__declspec(noinline) bool DatArchive::LoadIndex(const char* path) {
    unsigned char* unpacked = 0;
    if (!file)
        return false;

    unsigned char* compressed = 0;
    EncodedDatHeader header;
    if (!file->Open(path, g_dat_archive_read_mode))
        goto failure;
    if (!file->Read(&header, sizeof(header)))
        goto failure;
    DatDecrypt(reinterpret_cast<unsigned char*>(&header),
               sizeof(header), 0x1B, 0x37, 16, 16);
    if (header.magic != 0x31414854) // "THA1"
        goto failure;

    header.unpacked_size -= 123456789u;
    entry_count = static_cast<int>(header.entry_count - 135792468u);
    header.stored_size -= 987654321u;
    {
        unsigned int file_size = file->GetSize();
        unsigned int table_offset = file_size - header.stored_size;
        // Retail neither checks for unsigned subtraction wrap nor tests the
        // seek result. It proceeds with allocation and the following read.
        file->Seek(static_cast<LONG>(table_offset), 0);
        unsigned int stored_size = header.stored_size;
        compressed = static_cast<unsigned char*>(asm_malloc_00452706(stored_size));
        if (!compressed)
            goto failure;
        if (!file->Read(compressed, stored_size))
            goto failure;
        DatDecrypt(compressed, static_cast<int>(stored_size),
                   0x3E, 0x9B, 128, static_cast<int>(stored_size));
        unpacked = DecompressDatLzss_00435dc0(
            compressed, static_cast<int>(stored_size), 0, header.unpacked_size);
        if (!unpacked)
            goto failure;
        entries = BuildIndex(
            unpacked, entry_count, table_offset);
        if (!entries)
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
    delete file;
    file = 0;
    // The decoded count and any previous entries survive failures before
    // BuildIndex; a failed BuildIndex has already assigned entries = 0.
    return false;
}

#pragma code_seg()
