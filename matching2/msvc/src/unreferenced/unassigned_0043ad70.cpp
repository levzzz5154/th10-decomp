// 0x0043AD70 — restart the MIDI output of the loaded sequence.
//
// Retail enters with the sequencer in EAX (an unsaved register argument) and
// leaves with `ret`; the object's home through the body is EDI.  That home is
// not this body's free choice: the bare `call` at 0x0043AD83 names no register,
// so the callee's body is compiled into this link as an ABI anchor (bottom of
// this file) and the whole-program pass follows whichever register that body
// earns — the loaded-cursor shape below earns EDI.
extern "C" {
// The Windows Multimedia entry points.  Retail reaches each through its own
// import slot, so each declaration is bound to that slot by address (the names
// carry the slot address to keep the binding unambiguous).
__declspec(dllimport) unsigned int __stdcall midiOutReset_004662a8(void* handle);
__declspec(dllimport) unsigned int __stdcall midiOutClose_004662a4(void* handle);
__declspec(dllimport) unsigned int __stdcall midiOutOpen(
    void** handle, unsigned int device, unsigned int callback,
    unsigned int instance, unsigned int flags);
__declspec(dllimport) unsigned int __stdcall timeKillEvent_00466288(unsigned int identifier);
__declspec(dllimport) unsigned int __stdcall timeEndPeriod_00466274(unsigned int period);
__declspec(dllimport) unsigned int __stdcall timeBeginPeriod_00466278(unsigned int period);
__declspec(dllimport) unsigned int __stdcall timeSetEvent_0046628c(
    unsigned int delay, unsigned int resolution, void* procedure,
    unsigned int user, unsigned int type);

extern unsigned int g_supervisor_window;
void midi_timer_callback(void);
int __stdcall midi_read_length(const unsigned char*& cursor);
}

// 0x20-byte sequencer track record; every member up to `cursor` fixes the
// offsets the body and the anchor reach through.
struct MidiTrack_0043ad70 {
    int active;                        // +0x00
    int next_event_time;               // +0x04
    unsigned int byte_count;           // +0x08
    unsigned char running_status;      // +0x0C
    unsigned char unknown_0d[3];
    unsigned char* data;               // +0x10
    const unsigned char* cursor;       // +0x14
    const unsigned char* loop_cursor;  // +0x18
    int saved_loop_time;               // +0x1C
};

// Only the fields this unit reaches are named.
struct MidiSequencer_0043ad70 {
    unsigned char reserved_000[4];
    unsigned int frame_timer;          // +0x04: timer identifier
    unsigned int timer_period;         // +0x08: timer resolution
    unsigned char reserved_00c[4];
    int current_file_slot;             // +0x10
    unsigned char reserved_014[0x104]; // 0x14 .. 0x117
    int track_count;                   // +0x118
    unsigned char reserved_11c[0x1C];  // 0x11C .. 0x137
    MidiTrack_0043ad70* track_table;   // +0x138
    void* midi_out;                    // +0x13C
    int midi_state;                    // +0x140

    __declspec(noinline) void ResetTracks();
    __declspec(noinline) int Restart();
};

// The reopen request is an internal five-argument helper.  The callback travels
// by reference: the caller-supplied tail arguments are then evaluated before the
// inlined body's own statements, which is where retail's two constant pushes
// sit, and the callback's read stays inside the body, after the state publish.
__forceinline int OpenMidiOut(void** handle, unsigned int device,
                                       unsigned int& callback, unsigned int instance,
                                       unsigned int flags) {
    if (*handle) {
        if (*(int*)(handle + 1) == (int)device) return 0;
        midiOutReset_004662a8(*handle);
        midiOutClose_004662a4(*handle);
        *handle = 0;
    }
    *(int*)(handle + 1) = (int)device;
    return midiOutOpen(handle, device, callback, instance, flags);
}

#pragma code_seg(".text$03restart")
int MidiSequencer_0043ad70::Restart() {
    if (!track_table) return -1;
    ResetTracks();
    OpenMidiOut(&midi_out, 0xFFFFFFFFu, g_supervisor_window, 0, 0x10000u);
    if (frame_timer) timeKillEvent_00466288(frame_timer);
    timeEndPeriod_00466274(timer_period);
    frame_timer = 0;
    timeBeginPeriod_00466278(timer_period);
    frame_timer = timeSetEvent_0046628c(1, timer_period,
                                        (void*)midi_timer_callback,
                                        (unsigned int)this, 1);
    return 0;
}
#pragma code_seg()

// ABI anchor for 0x0043ACE0 (MidiSequencer::ResetTracks).  This body is not
// recovered game code: the layout places it at the retail address so the bare
// `call` above bakes retail's own displacement, and export_bodies never selects
// it.  What it earns is the register the *caller* must hold its object in: a
// records object reached through a loaded local cursor that is advanced inside a
// loop that calls out, with the object still live after that loop.
#pragma code_seg(".text$02reset")
void MidiSequencer_0043ad70::ResetTracks() {
    MidiTrack_0043ad70* track = track_table;
    while (track < track_table + track_count) {
        track->cursor = track->data;
        track->loop_cursor = track->data;
        track->active = 1;
        track->next_event_time = midi_read_length(track->cursor);
        ++track;
    }
    current_file_slot = 0;
}
#pragma code_seg()
