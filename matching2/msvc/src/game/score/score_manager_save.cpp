// 0x0042B1E0: write the score manager back to scoreth10.dat.
//
// The sections are stamped with fresh checksums and gathered behind a copy of
// the file header, compressed, encrypted and written out as header plus
// packed stream. Returns -1 when there is nothing to save or the file cannot
// be opened; in the second case both work buffers are leaked, as in retail.
#include <stddef.h>
#include "th10/game/score_archive_0042b1e0.hpp"
#include <string.h>
extern "C" __declspec(dllimport) int __stdcall CloseHandle(void* handle);
extern "C" __declspec(dllimport) int __stdcall WriteFile(void* handle, const void* buffer, unsigned long size, unsigned long* written, void* overlapped);

// Closes the shared file and leaves the file lock. The handle itself is left
// as it was.
inline void File_CloseShared() {
    CloseHandle(g_file_write_handle);
    LeaveCriticalSection(&g_file_lock);
    --g_file_lock_depth;
}

// Writes one block to the shared file; a short write closes it.
inline int File_WriteShared(const void* buffer, unsigned int size) {
    unsigned long written;
    if (g_file_write_handle == (void*)-1)
        return -1;
    WriteFile(g_file_write_handle, buffer, size, &written, 0);
    if (size != written) {
        File_CloseShared();
        return -2;
    }
    return 0;
}

#pragma code_seg(".text$06score")
int ScoreArchive_0042B1E0::Save() {
    unsigned char* work;
    unsigned char* packed;
    int length;
    unsigned int i;
    int j;
    unsigned int sum;
    unsigned char* bytes;

    if (!file)
        return -1;
    work = (unsigned char*)asm_malloc_00452706(0x200000);
    *(ScoreFileHeader*)work = *file;
    length = sizeof(ScoreFileHeader);
    for (i = 0; i < SCORE_RECORD_COUNT; i++) {
        if (records[i].header.tag == SCORE_SECTION_RECORDS) {
            records[i].shot_type = i;
            sum = 0;
            bytes = (unsigned char*)&records[i].header.size;
            for (j = 0; j < sizeof(ScoreRecordSection) - offsetof(ScoreSectionHeader, size); j++)
                sum += bytes[j];
            records[i].header.checksum = sum;
            memcpy(work + length, &records[i], sizeof(ScoreRecordSection));
            length += sizeof(ScoreRecordSection);
        }
    }
    sum = 0;
    bytes = (unsigned char*)&settings.header.size;
    for (j = 0; j < sizeof(ScoreSettingsSection) - offsetof(ScoreSectionHeader, size); j++)
        sum += bytes[j];
    settings.header.checksum = sum;
    memcpy(work + length, &settings, sizeof(ScoreSettingsSection));
    length += sizeof(ScoreSettingsSection);
    file->decompressed_size = length - sizeof(ScoreFileHeader);
    packed = CompressScore(work + sizeof(ScoreFileHeader), file->decompressed_size,
                           (int*)&file->compressed_size);
    file->reserved_04 = file->compressed_size + sizeof(ScoreFileHeader);
    EncryptDatBuffer(packed, file->compressed_size, 0xAC, 0x35, 0x10, file->compressed_size);
    if (OpenSharedFileWrite(str_score_file))
        return -1;
    File_WriteShared(file, sizeof(ScoreFileHeader));
    File_WriteShared(packed, file->compressed_size);
    if (g_file_write_handle != (void*)-1)
        File_CloseShared();
    if (packed)
        asm_free_00452422(packed);
    asm_free_00452422(work);
    return 0;
}
#pragma code_seg()
