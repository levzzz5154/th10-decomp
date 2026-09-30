#include "th10/platform/window_midi_native.hpp"
// Native LTCG supplies manager in EDX and header in ESI from the real callback.
#pragma code_seg(".text$20complete")
extern "C" __declspec(noinline) int CompleteMidiHeader_0043aeb0(MidiSequencer* manager, midihdr_tag* header) {
 for (int index=0; index<32; ++index) {
  if(manager->midi_headers[index] == header) {
   manager->midi_headers[index]=0;
   // The existing sequencer model leaves the output handle at +0x13C opaque.
   IatmidiOutUnprepareHeader(*reinterpret_cast<void**>(manager->unknown_13c),header,0x40);
   if(header->lpData) { entry_free_00452422(header->lpData); header->lpData=0; }
   entry_free_00452422(header); return 0;
  }
 }
 return -1;
}
