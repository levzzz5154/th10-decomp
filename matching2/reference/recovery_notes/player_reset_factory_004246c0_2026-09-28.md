# Player reset and its genuine allocation caller, 2026-09-28

**Disposition: unpromoted.** The complete disjoint C++ reset still emits 244
bytes with the same six register-operand differences as the previous strongest
model. Both maintained assembly bodies remain in place. No newly recovered
routines or bytes are claimed.

The new scratch is
`matching2/build/experiments/player_reset_factory_2026_09_28`; the terminal
results, all differences, source and artifact hashes are retained in
[measured_residual.json](../../build/experiments/player_reset_factory_2026_09_28/measured_residual.json).
The 2026-09-27 experiments remain unchanged.

## Genuine factory topology

Fresh live Ghidra decompilation and complete instruction listings were retained
for reset `0x4246C0`, factory `0x425020`, initializer `0x4247F0`, cleanup
`0x424ED0`, allocation `0x452493`, and free `0x4524A1`.

The whole 69-byte factory allocates uninitialized `0x4478` storage and resets it
only if allocation succeeds. The reset receives the owner in ESI, returns it in
EAX, and publishes it at `0x477834`. The factory holds that pointer in EBX and
unconditionally invokes the full 1,435-byte initializer, including after a
null allocation. On a nonzero initializer status, it invokes one-argument,
stack-based cleanup (`RET 4`) if the state exists, frees it through the cdecl
free routine, and returns null. Otherwise it returns the state.

The full source factory and prior full reset constructor were compiled in one
native LTCG cluster. The typed initializer contract was deliberately left
unresolved: the actual initializer uses a private EBX receiver and also depends
on private nested helper contracts. The native link failed on that unresolved
member. No ECX declaration was bound to the private EBX entry, no shortened
initializer was substituted, and this failure supplies **no body byte
measurement**. The initial missing shared-type compile error was corrected
before that terminal link diagnostic. The complete factory snapshot lives in
`factory_msvc`; original diagnostic logs retain their invocation paths.

## Corroborated disjoint reset layout

A second, bounded probe used the unchanged prior placement-construction
compiler entry and a new complete reset model with disjoint physical records.
Fresh Ghidra evidence for the complete pickup sweep `0x428630`, maintained
pickup instructions, and the native indicator pool type corroborate these
record bases and strides:

| Reset region | Base | Count | Stride | Flag offset |
| --- | ---: | ---: | ---: | ---: |
| Pickup records | `0x49C` | 128 | `0x5C` | `0x10` |
| Animation records | `0x32A0` | 4 | `0x98` | `0x80` |
| Indicator records visited by reset | `0x350C` | 33 | `0x6C` | `0x54` |
| Final timer | `0x430C` | 1 | `0x14` | `0x10` |

The old flags-first padding views created artificial union overlap. Real timer
records put the pickup span at `[0x49C,0x329C)` and the indicator span at
`[0x350C,0x42F8)`, disjoint from the animation and final-timer spans. Gameplay
exposes 32 indicator entries; reset clears 33 flags. The source preserves that
observed reset count without assuming all 33 records are allocatable.

Independent semantic review passed every physical range and original operation:
all preliminary flag reads/stores, the complete embedded clear, the overwritten
`0xFFFF` halfword, both counted stride loops, all four animation flags, the
complete owner clear, and final publication. Compile-time assertions verify
owner size and subobject offsets.

The normal selected-body gate emitted exactly 244 bytes, with 238 equal bytes
and six differences at `0x42473F`, `0x42474B`, `0x42474D`, `0x424766`,
`0x424771`, and `0x424773`. It still uses ECX where retail uses EDI for the first
animation flag and EDX for the third. Its SHA-256 is
`f29b52106c457aaa47b0c671f6ad3471453b83f9dbe08bde47c72120d33c930e`,
identical to the previous strongest compiled body. Instruction rewrites,
address-operand rewrites, and masked bytes are zero; reference bytes were not
used to build. Compiler entry bytes are unselected.

The remaining concrete topology lead is the complete genuine initializer and
its real private dependencies. The improved physical layout is retained as a
source model; this compiler entry does not change the residual registers.
