# MIDI shutdown native-LTCG exact landing

New readable inline-asm-free C++ function: ShutdownMidi_0043ae20 at0x0043AE20,129 bytes. Manager arrives inEDI, completion receivesEDX/ESI, plainRET. Source decorated symbol _ShutdownMidi_0043ae20@4 must not be mistaken for its optimized register ABI.

Previous runtime dependency43AEB0 is now recovered. Extended maintained window_midi_native cluster with shutdown and an explicitly unselected124-byte compiler context reproducing real43A9B0 load-track operations. PublicWndProc remains rooted; shutdown/completion remain private/unrooted. Schema1 driver includes the realcallback source, other two sources are separately compiled with /GL. Context code, calling conventions and outgoing opaquecall boundaries are NOT recovered game-code credit. Selected shutdown/completion bodies and their directCALL43AE48 are exact. No asmbridges/emits/outputpatching.

Shutdown followsretail: iftracks null return-1; scan32headers andcomplete existingones; killtimer ifactive; alwaysendperiod; cleartimer; reset/close/non-nullMIDIhandle thennullit; markcurrentfile_slot=-1; return0. Reuses existingMidiSequencer partialphysical layout and evidenced IAT slots.

Parent verified scratch probe all3exact; checked prior callback/completion/header byte-identical, record previous_record equals liveasmowner, scratchmanifest delta onlyshutdownrecord. Integrated onlythatrecord/source andextendedlayout/newdriver, preservingolderWIP.

Maintained probe:265-byteWindowProcedure,129-byteShutdownMidi,79-byteCompleteMidiHeader allEXACT. Final makebuild1926 maintained+10optional compiler sources, zero failures; wholeEXEexact487936bytes. Progress1838ordinaryC++regions/95619bytes;466asmregions/227431bytes. New recovery is129bytes only, not the existing344 or124-bytecontext.

Scratchevidence: /home/levzzz/.hermes/cache/scratch/midi-shutdown-native/{probe06-final,probe07-repeat,parent_verify,maintained_verify,final-disassembly.txt}. Durable reproduction is maintainedlayout/source andmakebuild. No commitmadeinthisstep; checkpoint3d2c1c11precedes thethree-window/MIDIlandings.
