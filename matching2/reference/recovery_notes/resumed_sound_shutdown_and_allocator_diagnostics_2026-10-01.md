# Complete native sound shutdown and finite compiler diagnostics

Historical 3e5683c2 checkpoint: current counts and later recoveries are in [the sound/render/archive checkpoint](resumed_sound_render_and_archive_topology_2026-10-01.md).

This wave replaces Sound StopMusicWorker at 0x0043DAB0 / 176 bytes with ordinary
C++. The entire native compiler contribution matches literally. The full real
Cleanup301 caller establishes the private ESI receiver through LTCG; no dummy
receiver, synthetic compiler caller, assembly, volatile, or barrier is added.
The source preserves imported PostThreadMessageA, WaitForSingleObject, and
CloseHandle capture order, retries shutdown until the wait succeeds, closes
both handles, and invokes the actual virtual destruction slot.

The complete native Cleanup301 context differs only at byte offset 3: MOV
ESI,ECX versus original MOV ESI,EAX. Its complete source and genuine call are
retained for compiler context, while the selected Cleanup owner stays assembly.
The full Aggregate82 callee matches literally and retains its existing semantic
owner. Neither support body receives new credit. The guarded integration changes
one owner, adds its binding and native layout, and preserves the other selected
sound owners, compiler flags, address bindings, and strict complete-extent gates.

Four ordinary callback allocator models preserve the real constructor phases
and complete StageTip factory/registry caller context. Each emits 69 bytes
against the required 74. All five support bodies in each model / 697 bytes remain
exact; all 24 complete MAP functions / 3,064 native bytes and sixteen genuine
call edges are retained. Compiler scheduling hoists the flag AND and folds the
final OR into memory. The 74-byte selected allocator remains mixed C++/assembly;
no function, byte, or qualifier-removal credit is claimed.

Four MIDI models use the complete actual timer-vtable Tick entry, its genuine
private-EDI Volume callee, and the complete ResetTracks callee. Tick naturally
emits 481 bytes against 473. Volume emits 128, 128, 149, and 149 against 140,
and its natural address moves to 0x43B7B0 because Tick is oversized. All four
ResetTracks132 bodies match literally, with zero new credit. Twelve complete
natural MAP contributions / 3,006 bytes are frozen with complete native and
original payloads. Common-offset comparisons are diagnostic only; all four
unchanged strict gates reject, and both selected MIDI owners stay assembly.

The final build completes 1,874 maintained C++ sources with zero failures,
plus the two existing optional compiler inputs. The whole 487,936-byte executable
matches the oracle literally: SHA256
2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040.
All current compiler-input hashes are verified. The complete source audit checks
1,911 semantic symbol/address/extent bindings and
1,525 semantic source hashes. Six mixed
inline-assembly owners still total 4,525 bytes. Syntactically assembly-free C++
totals 1,905 owners / 101,834 bytes, or 24.676741%
of text. The finite volatile review remains 37 owners / 6,970 bytes; it is not
an exhaustive source-forcing audit and no removal credit is claimed.

Since permissions were restored, cumulative recovery is 43 complete routines /
5,898 bytes: 40 former assembly owners / 5,868 bytes and three corrected game
exception-handler library misattributions / 30 bytes. Current semantic ownership
is 1,911 / 106,359; remaining assembly 392 / 216,589; libraries 320 / 66,450;
text data 7 / 7,779; padding 1,770 / 15,495. The goal remains active.

Repeatable whole-build audit: wine_startup_diagnosis_2026_10_01/verify_wave17_build.py.
Complete-source audit: semantic_inline_owner_audit_wave17_2026_10_01/verify.py.
Finite native verifiers: native_sound_launch_stop_2026_10_01/verify_frozen.py,
native_stage_tip_callback_allocator_2026_10_01/verify.py, and
native_midi_tick_volume_2026_10_01/verify.py. These are under
matching2/build/experiments. The accompanying evidence retains current proof
hashes, complete recovered-body receipts, compiler inputs and whole-build hashes.
