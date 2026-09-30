# Temporary MIDI track caller: 0x0043AC90, 72 bytes exact

Recovered LoadTemporaryTrack_0043ac90 as readable C++, without inline asm, naked bodies, byte emissions or output patches. Native LTCG derives ECX manager, EAX filename, plain RET. Loads slot 31, returns -1 on load failure, ignores the parser result, frees the temporary file buffer, preserves conditional and unconditional clearing, and returns zero. Header assertions document file-buffer base +0x98 and slot 31 +0x114; the LoadTrack partial declaration matches the existing canonical declaration.

Independent temporary_track_native cluster exports only this caller. Canonical dependency copies remain compiler-only; production ownership stays with existing LoadTrack, ReleaseTracks, ParseLoadedFile and Archive_LoadFile sources. The unselected MidiStop/TextLog ABI scaffolding is inherited from the existing LoadTrack modeling context and is not credited or claimed as exact here. In particular, its 81-byte MidiStop model is NOT the maintained 129-byte ShutdownMidi landing at the same address. The exact caller/LoadTrack bytes call the separately owned real shutdown implementation in the final executable.

Parent independently re-probed scratch, integrated only the complete 43AC90 record (full previous_record and unchanged owner), its source/header and independent cluster files, then re-probed the maintained source. Compared bytes extracted from the fresh maintained native PE with the newly built whole executable:

- 0043AC90, 72 bytes: d23deacfcc37b1e4e135d6c6ba86a1ac3e840ae679bc6ef604d2eaa7ec0f2771
- 0043A9B0, 116 bytes: 3f4228ecd8f27fc1ab93c1755e6e014f21b4b9afba7bdb5b8de5a021b20691fe
- 0043AA60, 107 bytes: 7bbe1c65e3b0a7a222dd69ce9d80731dca3ff0c0f0b7b7b48c0cf2e61f0e1b8d
- 0043AAD0, 448 bytes: f877c6990142ea3f1a59d9ffad52404818e66d1845c282b97e6ac506aa070434
- 0044B360, 360 bytes: e5c582565fa1219981c8e4b4ae48b1538af2fe669f954175b390c320f45b3d9a

make build: 1925 maintained sources and 10 optional compiler sources, zero failures; whole EXE exact 487936 bytes. make progress: 1840 ordinary C++ regions / 95847 bytes; 464 assembly regions / 227203 bytes. New credit is only 72 bytes. Existing window/MIDI cluster unchanged. git diff --check passed. Not committed.

Scratch receipts: /home/levzzz/.hermes/cache/scratch/midi-temporary-track-native/{RECEIPT.md,final_native_evidence.json,final_native_disassembly.txt,parent_verify,maintained_verify}. Scratch can expire; maintained source/layout plus make build reproduce the acceptance gate. No direct retail E8 callers were reported by the child scan; no real incoming-caller recovery is claimed for its synthetic context loop.
