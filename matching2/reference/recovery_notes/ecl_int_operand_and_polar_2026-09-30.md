# ECL integer operands and polar setters without inline assembly

Later checkpoint: the two float resolvers and their forwarding caller have
also been recovered without inline assembly. See
[the subsequent recovery](ecl_float_values_and_forward_2026-09-30.md).
The counts and unfinished work below describe this earlier checkpoint.

2026-09-30. The 144-byte integer operand resolver at `0x0044FDB0` is now
ordinary MSVC C++, and all eight 30-byte polar setters are C++ compiled by the
existing pinned GCC path. These nine complete functions contain no inline
assembly. The float operand/value resolvers and the renderer's other inline
x87 blocks remain unfinished.

## Integer operand resolver

Live Ghidra MCP decompilation confirms the ignored ECX input, VM in EDX,
stack-passed selector, immediate/indirect operand mask, frame-relative loads,
two-word tagged scratch pop, and external-variable virtual call. Ghidra infers
a 64-bit return from EDX remaining live on some exits; the caller contracts use
the integer value in EAX, as in the existing integer-value resolver.

The earlier model fetched the slot before testing the mask and emitted 124
bytes. Testing the mask first reproduces the register choices and saved-register
lifetime, but initially emitted 142 bytes. Expressing the scratch cursor updates
as separate field decrements and reloading each updated cursor yields retail's
`mov ecx; lea esi; test esi` guard and its subsequent `add esi,-4`. Keeping the
cursor in a local instead leaves a `sub esi,4` with two differing bytes.

The maintained function covers all paths, including returning the input
selector when the first pop underflows, interpreting only a float-tagged value
through x87 truncation, and calling the external context for selectors below
-1. The full 144-byte body is exact; its only relocation is `__ftol2` at `+0x6A`,
resolving to `0x00463B2C`. No private entry-register cluster is needed here.

Scratch reproductions and variant outputs are under
`matching2/build/experiments/ecl_int_operand_2026_09_30/`. The selected
`field_decrement.cpp` matches; `stack_reload.cpp` also matches. The native
`ecl_operand_thunks` cluster still matches with the new compiled resolver.

## Polar setters

The earlier MSVC port retained FSINCOS through inline blocks, which did not
satisfy the active no-inline-assembly objective. The current source expresses
sine and cosine with `__builtin_sincosl`, keeps the products in extended
precision until the float stores, and explicitly returns the receiver. All
seven circular setters share one definition macro; the elliptic setter uses
separate horizontal and vertical scales.

`layout/compiler/gcc_x87_polar.json` still pins the compiler, assembler, plugin
SDK, and generic word-home initialization pass. That pass changes the compiler's
RTL choice of value pushed to reserve a one-word volatile local. It has no
program-specific addresses, expected bytes, assembly strings, or emission
callbacks. The compiler's emitted assembly goes unchanged to LLVM-MC. The build
never reads the retail executable to produce code.

The eight region symbols now name GCC's member-function definitions. Existing
assembly and LTCG callers retain their fixed-address bindings. The compiler
profile, backend, pass, and tool pins themselves were not changed.

## Duplicate assembly cleanup

Twenty-seven naked copies in `bullet.cpp`, `player.cpp`, `scheduler.cpp`,
`score.cpp`, and `score_file.cpp` had no ownership in those units. Sixteen
copies (1,546 bytes) were already supplied by recovered C++; eleven more
(2,409 bytes) were supplied by assembly in their actual owning sources. All
are replaced by comments pointing at the maintained implementations. This
removes redundant scaffolding without claiming any new recovered bytes.
The five edited units retain all 12 of their selected regions byte for byte.

## Verification

The focused resolver/polar/thunk probe checks 14 complete regions, including the
unchanged integer-value resolver and ECL dispatcher in the shared unit. The
five cleanup units add 12 exact regions. The final whole-image build checks
`.text` and the entire 487,936-byte executable without masking bytes.

Manifest accounting after this recovery is 1,837 semantic regions / 95,927
bytes and 462 assembly regions / 226,970 bytes. Semantic classification still
includes the four rendering sources with inline x87 blocks; those counts do
not prove the broader no-inline-assembly objective complete.
