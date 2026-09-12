#pragma once

#include "th10/platform/windows_types.hpp"

struct MidiHeader {
    char* data;
    DWORD buffer_length;
    DWORD bytes_recorded;
    DWORD user;
    DWORD flags;
    MidiHeader* next;
    DWORD reserved;
    DWORD offset;
    DWORD reserved_tail[8];
};

struct MidiBufferRecord {
    BYTE reserved_header[0x10];
    void* allocation;
    BYTE tail[0x0C];
};

struct MidiManager {
    DWORD reserved_header;
    DWORD timer_event;
    DWORD timer_period;
    DWORD reserved_flags;
    int state;
    MidiHeader* active_headers[32];
    BYTE reserved_094[0x84];
    int buffer_count;
    BYTE reserved_11C[0x1C];
    MidiBufferRecord* buffers;
    HANDLE output;
};

void MidiBuffersRelease(MidiManager* manager);
int MidiManagerShutdown(MidiManager* manager);
int MidiHeaderRelease(MidiManager* manager, MidiHeader* header);
