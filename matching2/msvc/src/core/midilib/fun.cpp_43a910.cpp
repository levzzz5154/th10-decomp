#include "th10/platform/window_midi_native.hpp"
extern "C" __declspec(noinline) int ShutdownMidi(MidiSequencer*);
extern "C" unsigned int (__stdcall *IatShutdownTimeKillEvent)(unsigned int);
extern "C" unsigned int (__stdcall *IatShutdownTimeEndPeriod)(unsigned int);
extern "C" unsigned int (__stdcall *IatShutdownMidiOutReset)(void*);
extern "C" unsigned int (__stdcall *IatShutdownMidiOutClose)(void*);
// 0x0043A910: sequencer/base timer cleanup; preserve repeated retail clears
// and both timeEndPeriod calls, including after Shutdown has ended the period.
#pragma code_seg(".text$16destroy")
extern "C" __declspec(noinline) void CleanupMidi(MidiSequencer* manager) {
 unsigned int* timer=reinterpret_cast<unsigned int*>(manager->timer_storage);
 timer[0]=0x46F80C;
 ShutdownMidi(manager);
 manager->ReleaseTracks();
 unsigned char** slot=manager->file_buffers;
 int remaining=32;
 do {
  if(*slot) { crt_free(*slot); *slot=0; }
  *slot=0;
  ++slot;
 } while(--remaining);
 void** handle=reinterpret_cast<void**>(manager->unknown_13c);
 if(*handle) {
  IatShutdownMidiOutReset(*handle);
  IatShutdownMidiOutClose(*handle);
  *handle=0;
 }
 unsigned int event=timer[1];
 timer[0]=0x46F810;
 if(event) IatShutdownTimeKillEvent(event);
 unsigned int (__stdcall *endPeriod)(unsigned int)=IatShutdownTimeEndPeriod;
 endPeriod(timer[2]);
 timer[1]=0;
 endPeriod(timer[2]);
}
