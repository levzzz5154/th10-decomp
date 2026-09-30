# Exact window procedure and MIDI completion native-LTCG recovery

Selected readable C++ landings:
- 0x004390E0 WindowProcedure_004390e0,265 bytes; public Win32 stdcall, four stack parameters, RET16.
- 0x0043AEB0 CompleteMidiHeader_0043aeb0,79 bytes; native-LTCG assigns managerEDX/headerESI, plainRET. Its decorated source symbol remains _CompleteMidiHeader_0043aeb0@8; that decoration is not the actual optimized ABI.

Both are ordinary C++ without asm/naked/emitted-byte adapters. layout/ltcg/window_midi_native.json uses schema2, separately compiles the two real sources with /GL and links /LTCG. Callback is public entry/root; cleanup is deliberately not rooted. Internal CALL at0x004391BB is explicitly validated. No synthetic caller, compiler-only function anchors, opcode rewriting or oracle-driven emitted code needed.

Source reproduces switch structure: CLOSE falls through to shared success return; activation, foreground and MIDI cases break into common DefWindowProc return. Cleanup searches32 header slots, clears matching slot, unprepares with size64, frees/nulls data and freesheader, returning immediately from matching iteration. Imports and globals match retail addresses. Existing MidiSequencer opaque handle at+13C is read through its partial layout.

Parent spec review cross-checked retail callback and helper access/call structure, source contains noinlineasm, verified unique midihdr_tag definition/shared existing sequencer layout. All prior source/record owners retained; previous_record equals checkpoint record. Integration copied only two implementations, new header and native manifest, plus the selectedrecords/newsymbol/cluster registration—not the stale scratch manifest wholesale.

Verification:
1. Fresh parent scratch probe: both functions EXACT.
2. Maintained probe src/platform/fun_004390e0_004390e0.cpp:265 and79 EXACT.
3. make build:1927 maintained sources plus10 optional compiler sources, zero failures, wholeEXE exact487936 bytes.
4. New progress1837C++regions/95490bytes;467assemblyregions/227560bytes;320toolkitlibraryregions/66347bytes.

Scratch/compiler evidence: /home/levzzz/.hermes/cache/scratch/window-midi-native/{handoff.json,probe11-final,final-disassembly.txt,parent_verify,maintained_verify}. The maintained layout/source plus make build are the durable reproduction; scratch paths may expire.

The older window_procedure_004390e0.md describes an unverified inlined model and stale promotion. This verified recovery supersedes its model status and does NOT inline the completion helper into the callback. No new commit made after checkpoint3d2c1c11 in this step.
