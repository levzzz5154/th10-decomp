# Native game worker and genuine StageTip caller verification

Historical c72143f8 checkpoint: current counts and later Sound Stop recovery are in [the sound-shutdown checkpoint](resumed_sound_shutdown_and_allocator_diagnostics_2026-10-01.md).

This wave replaces two complete assembly routines with ordinary C++:
GameWorker at 0x0043BA90 / 83 bytes and DirectInput setup at 0x0043B8D0 / 439
bytes. Both whole native bodies match literally, adding 522 recovered bytes.
The complete worker-start186 and font781 bodies remain exact, so the native
closure selects 1,489 exact bytes. All ten complete native contributions are
measured; eight match literally. The existing unselected Surface421 / 33-byte
and Clip472 / 70-byte differences receive no recovery credit.

The underlying game-thread callback takes no arguments, returns the final flags
in EAX and ends with plain RET. The previous stdcall(void*) / RET4 declaration
was incorrect: matching an address-only caller did not prove callback cleanup.
The source now declares the actual no-argument cdecl routine and casts only at
the genuine stored callback and beginthreadex API boundary. Its complete real
InputSetup callee generates the private EAX receiver through native LTCG. Typed
COM methods preserve the actual vtable slots, error cleanup, 44-byte capabilities
object at input+0x1C, and real device/object enumeration callbacks. No dummy
inputs, inline assembly, volatile or compiler barriers are introduced.

Three existing StageTip semantic owners / 435 bytes now compile through the
complete real factory419090 and an ordinary InitializeLayout member. Genuine
factory-to-constructor and factory-to-initializer calls are verified. The
fabricated leading ECX argument and synthetic initializer caller are removed;
the three obsolete source implementations are deleted. All 36 remaining owners
in the old native cluster / 4,159 bytes still match, and the focused combined
39-owner / 4,594-byte main probe passes. The three pre-existing volatile
declarations remain: six ordinary unforced hypotheses failed, five emitting
131 bytes with 17 scheduling differences and one emitting 129. This migration
receives zero new recovery or qualifier-removal credit.

Four genuine MusicPlay compilation contexts retain all five complete native
functions and all six real call edges. The full 73-byte play routine still has
10 scheduling differences; the other four functions / 349 bytes remain exact.
The corrected models use the actual complete ScoreManager object representation.
The initial one-element array diagnostic is explicitly excluded from promotion.
MusicPlay stays in assembly with zero credit.

The final whole build completed 1,874 maintained C++ sources with zero failures,
plus the two existing optional compiler inputs. Its 487,936-byte executable
matches the oracle literally: SHA256
2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040.
All current compiler-input hashes are verified. The full-source audit checks
1,910 semantic symbol/address/complete-extent bindings and
1,524 semantic source hashes. Six mixed
semantic inline-assembly owners still total 4,525 bytes, so syntactically
assembly-free C++ totals 1,904 owners / 101,658 bytes, or 24.634092% of text.
The finite volatile review remains 37 owners /
6,970 bytes and is not an exhaustive forcing-intent audit.

Since permissions were restored, cumulative recovery is 42 complete routines /
5,722 bytes: 39 former assembly owners / 5,692 bytes and three corrected game
exception-handler library misattributions / 30 bytes. Current semantic ownership
is 1,910 / 106,183; remaining assembly 393 / 216,765; libraries 320 / 66,450;
text data 7 / 7,779; padding 1,770 / 15,495. The goal remains active.

Repeatable whole-build audit: wine_startup_diagnosis_2026_10_01/verify_wave16_build.py.
Source-body audit: semantic_inline_owner_audit_wave16_2026_10_01/verify.py.
Frozen native verifiers: native_game_worker_entry_2026_10_01/verify_frozen.py,
native_stage_tip_initializer_2026_10_01/verify.py, and
native_music_real_entry_2026_10_01/freeze_diagnostics.py. All are under
matching2/build/experiments; paths, complete-body hashes and current proof hashes
are retained in the accompanying evidence JSON.
