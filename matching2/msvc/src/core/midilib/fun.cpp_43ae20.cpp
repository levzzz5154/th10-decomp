#include "th10/platform/window_midi_native.hpp"
extern "C" unsigned int (__stdcall *IatShutdownTimeKillEvent)(unsigned int);
extern "C" unsigned int (__stdcall *IatShutdownTimeEndPeriod)(unsigned int);
extern "C" unsigned int (__stdcall *IatShutdownMidiOutReset)(void*);
extern "C" unsigned int (__stdcall *IatShutdownMidiOutClose)(void*);
#pragma code_seg(".text$18shutdown")
extern "C" __declspec(noinline) int ShutdownMidi(MidiSequencer* manager) {
 if (!manager->tracks) return -1;
 midihdr_tag** slot=manager->midi_headers;
 int remaining=32;
 do {
  midihdr_tag* header=*slot;
  if(header) CompleteMidiHeader2(manager,header);
  ++slot;
 } while (--remaining);
 unsigned int* timer=reinterpret_cast<unsigned int*>(manager->timer_storage);
 if(timer[1]) IatShutdownTimeKillEvent(timer[1]);
 IatShutdownTimeEndPeriod(timer[2]);
 timer[1]=0;
 void** handle=reinterpret_cast<void**>(manager->unknown_13c);
 if(*handle) {
  IatShutdownMidiOutReset(*handle);
  IatShutdownMidiOutClose(*handle);
  *handle=0;
 }
 manager->current_file_slot=-1;
 return 0;
}
