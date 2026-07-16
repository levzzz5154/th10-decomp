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
    BYTE unknown[0x10];
    void* allocation;
    BYTE tail[0x0C];
};

struct MidiManager {
    DWORD unknown_00;
    DWORD timer_event;
    DWORD timer_period;
    DWORD unknown_0c;
    int state;
    MidiHeader* active_headers[32];
    BYTE unknown_94[0x84];
    int buffer_count;
    BYTE unknown_11c[0x1C];
    MidiBufferRecord* buffers;
    HANDLE output;
};

void MidiBuffersRelease(MidiManager* manager);
int MidiManagerShutdown(MidiManager* manager);
int MidiHeaderRelease(MidiManager* manager, MidiHeader* header);
