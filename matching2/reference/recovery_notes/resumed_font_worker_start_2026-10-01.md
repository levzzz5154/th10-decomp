# Verified checkpoint: genuine worker startup and font initialization

Source-audit correction: the current assembly-free total is 1,902 regions /
101,136 bytes (24.507599%). The historical count below excluded five mixed
x87 owners but missed the 74-byte callback at 0x00449ED0, whose selected body
also contains inline assembly. Recovery credit and executable bytes are
unchanged. See [the complete source-owner audit](resumed_native_schedule_and_source_audit_2026-10-01.md).

Two complete functions are now ordinary C++: worker startup at 0x004201B0
(186 bytes) and font initialization at 0x00437A00 (781 bytes). Their complete
967 bytes match literally. The original startup function calls the font
initializer at 0x00420260; live original Ghidra analysis and the strict native
closure verify this genuine relationship and actual no-argument ABIs.

The closure retains all six complete native function contributions. Release107
and Stop101 also match exactly, preserving existing semantic owners with zero
additional credit. Surface421 differs in 33 bytes and Clip472 in 70 bytes;
both remain unselected diagnostics and their main assembly owners are unchanged.
The independent review checks all nine input files, six complete MAP boundaries,
33 provenance hashes, and ten original direct call edges.

Font initialization uses the genuine CreateFontA@56 SDK signature, fifteen font
sizes, and the original eight-byte RNG object. The RNG's first four bytes are
read through memcpy from the complete object, preserving the upper word and
generation counter. All 256 noise bytes occupy the actual surface prefix.
Clip's complete diagnostic model preserves the genuine COM signatures and
copies 80 bytes to the vertex buffer returned by Lock. Original instructions
resolve Ghidra's incorrect null-destination reconstruction.

The two address-only worker callbacks use full virtual-address linker bindings
(kind data), because their relocations are ADDR32 stores/pushes. Relative direct
call targets retain kind relative_code. Correcting these input bindings removed
three high-byte differences in startup without patching generated instructions
or address operands. No synthetic caller, helper stub, fabricated argument,
inline assembly, optimization barrier, or volatile substitute was introduced.

Since permissions were restored, 40 complete routines/5,200 bytes have been
recovered: 37 former assembly routines/5,170 bytes and three corrected game
exception handlers/30 bytes. This gain is 1.2601% of the 412,672-byte text section.
Fully assembly-free C++ covers 1,903 regions/101,210 bytes, or 24.5255%.
Semantic ownership totals 1,908 regions/105,661 bytes; five older x87 semantic
regions/4,451 bytes still contain assembly. Remaining assembly is 395 regions/
217,287 bytes; libraries 320/66,450, text data 7/7,779, padding 1,770/15,495.
The larger decompilation goal remains active and incomplete.

All 1,875 maintained sources built with zero failures. The complete 487,936-byte
executable is literally identical to the original, SHA256
2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040.
Build: matching2/build/resumed_wave14_msvc_2026_10_01.
The repeatable current whole-build and native auditors are verify_wave14_build.py
and verify_wave14_native.py under wine_startup_diagnosis_2026_10_01. Their receipts
verify current source hashes and all 40 new complete owners. The native audit
checks 59 complete bodies, with 51 literal matches/8,266 bytes; eight nonmatching
models and three other contexts remain unselected. Its 2,930 newly credited
bytes represent a historical native-cluster subset of the full 5,200-byte gain.
Compiler profiles, framework, masks, and oracle-free build inputs are unchanged.
Seven staged source files received trailing-whitespace cleanup after initial
integration. All source tokens are unchanged; the full build and its current
source-hash checks were repeated afterward. Candidate hashes and current source
hashes are recorded separately, preserving the original independent review.

Additional finite diagnostics earned zero recovery credit. Four full Stats
factory models emit 151 bytes with nine differences confined to mask/store
scheduling; eight support bodies/1,100 bytes match. Correct C++ throw contracts
restore the GameState factory's complete 151 bytes, but one generated handler
address byte still differs. Moving the factory to a separate source object
leaves the complete EH69/metadata72 contributions unchanged. The corrected
StageSlot model preserves 24.0f and all four unconditional record writes, but
constructor 666/683 and factory 142/124 remain nonmatching. Its actual ECL caller
is 14,416 bytes, so a small synthetic replacement cannot establish the missing
private helper context. These models remain isolated and unselected.

The final integration recipe, strict probe, independent review, and complete
native artifacts are frozen under native_font_worker_context_2026_10_01.
Historical wave13 receipts remain snapshots. Current proof paths and hashes
accompany this note in its evidence JSON; generated build artifacts are ignored
by the repository's existing policy.
