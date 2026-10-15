#pragma code_seg(".text$03rewind")
extern "C" __declspec(noinline) int __stdcall ArchiveRewind(MusicCursor* cursor, bool start) {
    if (cursor->buffered) {
        unsigned int begin = reinterpret_cast<unsigned int>(cursor->base);
        MusicRecord* record = cursor->record;
        cursor->position = reinterpret_cast<unsigned char*>(begin);
        if (record->end > 0)
            cursor->memory_end = static_cast<unsigned int>(record->end);
        if (start && record->start > 0)
            cursor->position = reinterpret_cast<unsigned char*>(begin + static_cast<unsigned int>(record->start));
        return 0;
    }
    void* file = cursor->file;
    if (!file)
        return static_cast<int>(0x800401f0u);
    if (start) {
        MusicRecord* record = cursor->record;
        if (record->start > 0) {
            unsigned int offset = record->offset + static_cast<unsigned int>(record->start) + g_bgm_data_offset;
            imp_SetFilePointer(file, static_cast<int>(offset), 0, 0);
            record = cursor->record;
            cursor->remaining = static_cast<unsigned int>(record->end) -
                static_cast<unsigned int>(record->start);
            return 0;
        }
    }
    MusicRecord* record = cursor->record;
    imp_SetFilePointer(file, static_cast<int>(record->offset + g_bgm_data_offset), 0, 0);
    cursor->remaining = static_cast<unsigned int>(cursor->record->end);
    return 0;
}


#pragma code_seg()
