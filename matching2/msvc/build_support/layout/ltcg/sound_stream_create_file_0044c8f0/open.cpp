// Unselected native ABI anchor from src/core/zwave/archive_cursor_open.cpp. Only the
// shared type view and placement section differ.
extern "C" void* (__stdcall* imp_CreateFileA)(const char* path, unsigned long access, unsigned long share, void* security, unsigned long disposition, unsigned long flags, void* template_file);
#pragma code_seg(".text$06open")
int MusicReadCursor::Open(const char* path, MusicTrackRecord* entry, unsigned int mode) {
    MusicReadCursor* cursor = this;
    cursor->open_mode = mode;
    cursor->buffered = 0;
    if (mode == 1) {
        if (!path) return 0x80070057;
        cursor->file = imp_CreateFileA(path, 0x80000000, 1, 0, 3, 0x08000080, 0);
        if (cursor->file == (void*)-1) return 0x80004005;
        cursor->record = entry;
        if (cursor->buffered) {
            cursor->position = cursor->buffer_begin;
            if (entry->loop_end > 0) cursor->memory_end = entry->loop_end;
        } else if (cursor->file) {
            imp_SetFilePointer(cursor->file, entry->file_offset + g_bgm_data_offset, 0, 0);
            cursor->file_remaining = cursor->record->loop_end;
        }
        cursor->total_pcm_bytes = cursor->file_remaining;
    }
    return 0;
}
#pragma code_seg()
