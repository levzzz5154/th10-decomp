#pragma code_seg(".text$07rewind")
extern "C" __declspec(noinline) int __stdcall ArchiveRewind(MusicReadCursor* cursor, bool start) {
    if (cursor->buffered) {
        unsigned int begin = reinterpret_cast<unsigned int>(cursor->buffer_begin);
        MusicTrackRecord* record = cursor->record;
        cursor->position = reinterpret_cast<unsigned char*>(begin);
        if (record->loop_end > 0)
            cursor->memory_end = static_cast<unsigned int>(record->loop_end);
        if (start && record->loop_start > 0)
            cursor->position = reinterpret_cast<unsigned char*>(begin + static_cast<unsigned int>(record->loop_start));
        return 0;
    }
    void* file = cursor->file;
    if (!file)
        return static_cast<int>(0x800401f0u);
    if (start) {
        MusicTrackRecord* record = cursor->record;
        if (record->loop_start > 0) {
            unsigned int offset = record->file_offset + static_cast<unsigned int>(record->loop_start) + data_004977a4;
            data_004660c8(file, static_cast<int>(offset), 0, 0);
            record = cursor->record;
            cursor->file_remaining = static_cast<unsigned int>(record->loop_end) -
                static_cast<unsigned int>(record->loop_start);
            return 0;
        }
    }
    MusicTrackRecord* record = cursor->record;
    data_004660c8(file, static_cast<int>(record->file_offset + data_004977a4), 0, 0);
    cursor->file_remaining = static_cast<unsigned int>(cursor->record->loop_end);
    return 0;
}


#pragma code_seg()
