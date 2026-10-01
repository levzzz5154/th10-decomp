# Verification blocked by session restrictions

Historical checkpoint: the user subsequently enabled full access. Wine and
Ghidra now work, and fresh whole-build verification plus the archive-read
integration passed. See [the restored-permissions checkpoint](permissions_restored_and_archive_read_2026-10-01.md).

The full readable, byte-matching, assembly-free decompilation goal remains
incomplete. The current manifest is unchanged from the resource/overlay
integration checkpoint: C++ **1,868 regions / 100,461 bytes**, assembly
**432 / 222,457**, and toolkit library **323 / 66,480**. Five semantic
regions still contain six x87 assembly blocks, totaling 4,451 bytes; fully
assembly-free C++ is **1,863 regions / 96,010 bytes**. Current whole-project
byte matching remains unverified. The last whole build is historically
exact at 487,936 bytes but predates the current sources.

Wine cannot start its local server: `wineserver: bind: Operation not
permitted`. A fresh preflight failure is retained at
`matching2/build/experiments/callback_intel_dialect_2026_10_01/wine_preflight.log`.
A fresh read-only Ghidra decompilation call for `00408100` also returns
`MCP tool call requires approval, but approval policy is never`; its actual
tool response is saved as `ghidra_preflight.json` beside that log.
Neither restriction was bypassed, and no permission escalation was attempted.

The same environment restriction was confirmed in three consecutive goal
continuations: the resource/overlay integration checkpoint, the remaining
compiler-constraints follow-up, and this checkpoint. Safe retained native
proofs have been integrated; the newly investigated native alternatives
below fail the complete literal-byte gate. No current candidate is ready
for further verified integration without restoring the required tooling.
Additional uncompiled models would not establish the missing byte proof.

## Final native alternative checks

GCC's Intel assembly dialect produces the same complete seven-byte menu
callback bodies as the AT&T dialect. Both have the genuine ECX-to-EAX
bridge and correct tail-jump targets, but each still has two differing
MOV-encoding bytes (`89 C8` versus original `8B C1`). GCC itself emitted
the dialect; generated assembly was not edited. The isolated backend
adds only the dialect flag to its allowlist and leaves maintained policy
unchanged. The repeatable audit checks 458 hashes, full extents, relocation
targets, and the unchanged comparison gate.

A bounded scan examined all 100 current assembly regions of at most
64 bytes, totaling 2,094 bytes. Fifty-six are compiler-generated EH actions,
27 require owner closures exposing private ESI/EDI/EBX conventions, and
four are mixed-function or padding fragments. The remaining known
constraints and the classifications are retained in `scan.json` under
`matching2/build/experiments/native_small_function_scan_2026_10_01`.
This bounded scan does not claim that all possible C++ spellings or larger
functions have been ruled out.

Six fresh full-function native compilations of the 32-byte EAX-entry
reset at `00449A50` use unchanged pinned GCC/Clang profiles. GCC's three
typed forms emit 31/36/36 bytes; Clang emits 31/32/36. The sole 32-byte
candidate matches 21 positions and differs in register allocation and
XOR encoding. All six fail complete literal matching. A retained audit
verifies 1,263 source/framework/artifact hash records. No source, profile,
instruction, operand, or ownership in main was changed.

## Resume work

Resume in an environment where Wine can bind its local-server socket and
the read-only Ghidra MCP tools can execute. First confirm the Wine preflight
succeeds; do not run the existing full build while Wine is unavailable,
because its startup removes canonical output artifacts before compilation.

The current integration audit and whole-build requirement are documented in
[the resource/overlay checkpoint](resource_load_size_and_overlay_2026-10-01.md).
Run a fresh whole-project build into a separate output directory so that
the last verified build remains available:

```sh
make MSVC_ARGS='--jobs 32 --output matching2/build/resumed_msvc_2026_10_01 --verify matching2/build/oracle/th10.exe'
```

Preserve successful native compiler inputs, all current project hashes,
full selected extents, helper ownership and aliases, and literal equality
of the complete 487,936-byte EXE. A focused retained probe cannot certify
that current whole build.

The complete ArchiveCursor_Read202 candidate has a production project
with its context size corrected from 100 to the actual 90 bytes at
`matching2/build/experiments/archive_cursor_production_ready_2026_10_01`.
Its `run_probe.sh` contains the normal native gate. It remains assembly
in main until that gate passes.

The full UpdatePlayer223 experiment and genuine collision/lifetime/helper
closure are ready under
`matching2/build/experiments/player_update_continuation_2026_10_01`.
Its preparation audit and ten syntax/layout checks pass. Run its documented
ordinary MSVC probe; inspect complete selected, anchor, context, and data
contributions, including the previously omitted Z displacement and private
collision ABI. Syntax checks and the previous 220-byte diagnostic are
insufficient for promotion.

Continue the entire decompilation after these prerequisites are restored.
The five inline-x87 regions and remaining 432 assembly owners still require
full readable native recoveries. This checkpoint records a tooling impasse;
it does not redefine completion around the integrated subset.
