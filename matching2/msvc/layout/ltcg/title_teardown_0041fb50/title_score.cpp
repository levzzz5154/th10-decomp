#include "title_score_archive.hpp"
#include <string.h>

// This helper intentionally leaves the shared handle unchanged, as retail
// does. A short write can therefore be followed by another write or close.
__forceinline void ScoreCloseSharedFile() {
    data_004660cc(data_00474c38);
    data_004660b4(&data_004922a4);
    --data_0049231e;
}

#pragma code_seg(".text$06score")
int ScoreArchive_0042B1E0::Save() {
    if (!file)
        return -1;

    unsigned char* work = static_cast<unsigned char*>(
        asm_malloc_00452706(0x200000));
    *reinterpret_cast<ScoreFileHeader*>(work) = *file;

    int length = sizeof(ScoreFileHeader);
    for (unsigned int index = 0; index < SCORE_RECORD_COUNT; ++index) {
        ScoreRecordSection* record = &records[index];
        if (record->header.tag == SCORE_SECTION_RECORDS) {
            record->shot_type = index;
            unsigned int sum = 0;
            const unsigned char* bytes =
                reinterpret_cast<const unsigned char*>(record) + 12;
            int count = 0xB3E;
            do {
                sum = bytes[-4] + bytes[-3] + bytes[-2] + bytes[-1]
                    + bytes[1] + bytes[0] + sum;
                bytes += 6;
            } while (--count);
            record->header.checksum = sum;
            memcpy(work + length, record, sizeof(*record));
            length += sizeof(*record);
        }
    }

    unsigned int sum = 0;
    const unsigned char* bytes =
        reinterpret_cast<const unsigned char*>(&settings) + 10;
    int count = 0x110;
    do {
        sum = bytes[-2] + bytes[-1] + bytes[1] + bytes[0] + sum;
        bytes += 4;
    } while (--count);
    settings.header.checksum = sum;
    memcpy(work + length, &settings, sizeof(settings));

    // length includes the work image's header; 0x430 is the remaining
    // settings payload after accounting for that header.
    file->decompressed_size = length + 0x430;
    unsigned char* packed = CompressScore(work + sizeof(ScoreFileHeader),
        file->decompressed_size, reinterpret_cast<int*>(&file->compressed_size));
    file->reserved_04 = file->compressed_size + sizeof(ScoreFileHeader);
    EncryptDatBuffer(packed, file->compressed_size, 0xAC, 0x35, 16,
        file->compressed_size);

    // Retail returns here without freeing either work allocation on failure.
    if (OpenSharedFileWrite(data_0046e848))
        return -1;

    unsigned int written;
    if (data_00474c38 != reinterpret_cast<void*>(-1)) {
        data_004660d4(data_00474c38, file, sizeof(ScoreFileHeader), &written, 0);
        if (written != sizeof(ScoreFileHeader))
            ScoreCloseSharedFile();
    }
    unsigned int packed_size = file->compressed_size;
    if (data_00474c38 != reinterpret_cast<void*>(-1)) {
        data_004660d4(data_00474c38, packed, packed_size, &written, 0);
        if (written != packed_size)
            ScoreCloseSharedFile();
        if (data_00474c38 != reinterpret_cast<void*>(-1))
            ScoreCloseSharedFile();
    }
    if (packed)
        asm_free_00452422(packed);
    asm_free_00452422(work);
    return 0;
}
#pragma code_seg()
