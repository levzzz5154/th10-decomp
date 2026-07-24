#pragma once

// Sound stream worker thread start (retail 0x0043D690).

// --- 0x0043D690 --------------------------------------------------------------
int SoundStream_StartThread(
    const char* source_name, char* name_buffer, void* device,
    void* format_block, void (*stop_previous)(void), unsigned int data_size,
    unsigned int block_align, void* (*create_event)(void), void** event_slot,
    void* (*create_thread)(void* argument, unsigned int* thread_id_out),
    void* thread_argument, void** thread_slot, unsigned int* thread_id_slot,
    int (*open_stream)(unsigned int buffer_bytes, void* event_handle));
