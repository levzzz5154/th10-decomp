# Front/HUD initializer 0x00413BC0: byte-exact ordinary C++

`msvc/src/game/front_initialize_00413bc0.cpp` now supplies the complete front
initializer in ordinary C++. All 1,965 retail bytes match, including native
compiler alignment inside the routine. Native LTCG derives its private EDI
receiver and plain RET from the member source and complete helper graph.
The selected symbol is `?Initialize@FrontInitialization_00413bc0@@QAEXXZ`.
No inline assembly, adapter, output edits, masks, or oracle build input are used.

The initializer marks its update and draw tasks, conditionally registers two
persistent objects, loads 42 animation slots in the retail bank order, sets
the life-icon flags, configures the three power digits, registers the normal
or special front objects and the conditional captions, initializes the stage
heading, and sets the selected animation tree's frame-control word to three.
It finishes by clearing the word at front +0x9E90.

The selected body was separated from the still-assembly movement routine at
0x004250B0 in `src/game/player_front_runtime.cpp`. That movement source and
its existing 1,656-byte selected extent remain unchanged in behavior. The
manifest retains the initializer's previous assembly record and adds the new
source to the explicit translation-unit list.

## Complete native graph and boundaries

`msvc/layout/ltcg/front_initialize_00413bc0.json` compiles the initializer with
complete pool allocation, primary-back registration, public resource
initialization, sprite configuration, entity initialization, preserving script
initialization, and the regular script loader. The public resource initializer
uses the existing rooted-helper mechanism. Inline registration and animation
tree operations in the checked header supply the full list insertion, ID
increment, lookup and child traversal visible in the retail caller.

The 19-byte `_FrontCompilerContext@0` entry is explicitly compiler-only: it
calls the global front's initializer and returns one. It receives no game-code
credit. It is not a replacement for the real stage or sprite-viewer callers;
the native EDI entry matches their existing calls. The selected body contains
no bridge to translate registers.

The complete entity initializer has two logical declarations in this graph.
Pool allocation calls the compiler-visible one-argument stdcall declaration.
LoadScript calls the established public fastcall declaration from `entity.hpp`,
with an unused leading argument and the object in EDX. That public symbol is
bound to the same native 0x00401DE0 entry emitted by the complete initializer.
Both contracts are checked against the same exact 273-byte native body; no
second implementation or shim is emitted. Keeping this public declaration
opaque to LoadScript preserves its observed call-clobber boundary.

Calling the compiler-visible one-argument initializer directly inside
LoadScript makes C2 retain the object in EDX and coalesce other inputs. The
initial diagnostic then emits a 197-byte loader and a 1,979-byte front body.
The public edge restores the exact 203-byte loader, including resource in ECX,
object in EAX and script index in EBX. This removes the bulk of the caller's
register mismatches without changing any helper's behavior.

Six unselected helpers match their entire raw native retail bodies:
registration 118, allocation 161, public resource initialization 217,
Entity_Init 273, preserving script initialization 194, and LoadScript 203 bytes.
The complete 356-byte ConfigureObject body differs only at the two addresses
of its verified 1/256 constant, six bytes total. Native layout places that
constant at 0x0044C000 rather than 0x00470B7C. This helper is unselected and
its existing production owner is retained. The relocated diagnostic compares
all seven helper bodies exactly.

## Source-shape and behavior evidence

Experiments and receipts are under
`matching2/build/experiments/front_initialize_native_2026_10_06/`.

- The allocation helper saves the flag mask in a local, applies the requested
  script offset after allocation, sets the render bucket, then commits the
  mask and initializes the resource. This preserves both the flag-store order
  and the difficulty-script additions observed in retail.
- Life icons use the complete two-loop setter, with a cached count argument
  and its explicit early exit. Reloading the global life count inside the
  loop adds a retail-absent load; flattening the setter also changes the loop
  counter allocation.
- A named returned animation ID and explicit assignment by value reproduce
  the first persistent handle's load from its stack temporary. The implicit
  assignment instead reads through the returned EAX pointer, losing two bytes
  and changing later loop alignment. The ID remains a four-byte unsigned
  value, with wrap through zero and the existing skip-zero increment.
- The first bank loop retains its separate script counter starting at 20 and
  a count of ten. Its pointer-derived score/high-score accesses match the
  original interleaved calls. Combining the counters into a count-up index
  changes the private script input and loop termination code.
- The first difficulty ID is committed by its scalar field before the inline
  frame-three lookup. The last lookup's caption ID is saved before storing
  the new difficulty-label ID. These source orderings reproduce the original
  register loads and all internal alignment.

The full machine-code audit also establishes two details absent or unclear
in the older host-oriented reconstruction. The second persistent object is
registered when its handle slot is zero, but its returned ID is not stored
back to that slot. The final frame-three tree operation uses the first
caption's ID at +0x9E50 again, after storing the newly registered label ID at
+0x9E54. Both details are deliberately preserved. Special script 113 depends
on the flag at 0x00474CA0; mode eight alone does not create it.

`scalar_caption_id/` contains the first fully exact diagnostic. Its eight
whole-function comparisons (initializer plus seven helpers) all have zero
byte differences. `explicit_id_assignment/` has the correct 1,965-byte extent
but four instruction hunks, so it is not claimed as exact. A discarded
explicit output-pointer registration form changes both the register boundary
and helper extent; it is retained as a negative experiment only.

The production fixed-address probe in `fixed_probe/` passes the existing
native address, entry, origin, complete-contribution and byte checks. Type
names are specific to this front graph. Formatting and removal of unused
interface declarations were subsequently verified by both full builds.
`final-native-helper-audit.json` records independent raw native comparisons.
The selected body SHA-256 is
`513d2b620d6f816514a93548a7c0b03e068c65a0d2295a38e96336e705dc7ad9`.

## Validation, 2026-10-06

- Strict native probe: all 1,965 bytes exact.
- `make`: all 1,677 maintained units and eight existing equivalence gates pass.
- `make EXACT=1`: full executable equality passes.
- Independent equality: all 487,936 bytes match; executable SHA-256
  `2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`.
- Final native report: zero instruction edits, zero address edits, zero masks,
  and no oracle bytes used for compilation.
- Every recorded native input hash matches the current maintained file.
- `git diff --check`: passes.

Progress is 2,251 exact ordinary C++ regions / 195,685 bytes (60.9% of game
code), plus eight equivalent regions / 33,176 bytes. Combined recovery is
71.2%. There remain 63 assembly regions / 92,622 bytes. The complete readable,
byte-exact, assembly-free objective remains unfinished.
