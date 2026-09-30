# Complete GCC x87 bodies: two polar setters and `__frnd`

The installed MinGW GCC 16.2.0 produces assembly-free C++ bodies containing
`FSINCOS` and `FRNDINT`. None of these three complete routines is yet byte exact.
The two 30-byte polar setters are now measured at **one differing byte each**;
the 17-byte rounding helper still has a stack-frame residual. No maintained
source, layout, manifest, build framework, or executable was changed.

All evidence is retained in
`matching2/build/experiments/gcc_x87_full_bodies_2026_09_28`. Fresh Ghidra function,
disassembly, decompilation, xref, raw-memory, and complete caller listings are in
`ghidra_fresh.json`, `ghidra_memory.json`, and `ghidra_callers.json`. Raw Ghidra
bytes agree with the immutable retail oracle at all three addresses.

## Full 30-byte polar setters

Both `0041BEB0..0041BECD` and `004458B0..004458CD` receive the destination in ECX,
the angle and scale as two stack floats, and return with `RET 8`. They load the
angle once, execute `FSINCOS`, multiply the extended cosine by scale, store the
binary32 x component, then multiply the extended sine and store binary32 y.
There is no intermediate rounding of the sine or cosine to float or double.

Fresh callers confirm the ABI. At `0041BD93` the item allocator forms ECX from
the live item in EDX; after calling `0041BEB0` it uses that same EDX. The callee
does preserve EDX. The GCC preservation flag below expresses this observed
constraint rather than assuming all conventional caller-saved registers may
be overwritten.

The final complete candidates are `final_polar_41beb0.cpp` and
`final_polar_4458b0.cpp`. They use `__builtin_sincosl` with long double results,
multiply those results by the original float scale, and convert only at each
destination store. Private volatile receiver, angle, and scale views retain the
observed home and read ordering. They contain no assembly, naked functions,
encoded instructions, oracle-derived code, helper stubs, or register-assembly
constraints.

`final_polar_probe.py` independently recompiles both functions with the installed
driver and compares every byte through the compiler's RET against each original
30-byte body. The selected flags are:

```text
-Oz -mfpmath=387 -mno-sse -mno-sse2 -funsafe-math-optimizations
-mpreferred-stack-boundary=2 -mincoming-stack-boundary=2
-fomit-frame-pointer -fcall-saved-edx
-fno-asynchronous-unwind-tables -fno-unwind-tables -fno-exceptions
-fno-rtti -fno-stack-protector -fno-ident -ffunction-sections
-falign-functions=1 -falign-jumps=1 -falign-loops=1 -falign-labels=1
```

The result for each function is exactly **30 instruction bytes**, in a genuine
**32-byte COFF contribution with two trailing NOP padding bytes**. All sections,
relocations, command arguments, source hashes, object hashes, and individual
differences are recorded in `final_polar_probe.json`; padding is separate from
the body and is never counted as recovered instructions. There are no
relocations in either function section.

```text
retail: 51890c248b0424d9442408d9fbd84c240cd918d84c240cd9580459c20800
GCC:    50890c248b0424d9442408d9fbd84c240cd918d84c240cd9580459c20800
```

The sole residual is the first instruction: retail `PUSH ECX` versus GCC
`PUSH EAX`. The subsequent 29 bytes match, including the receiver reload into
EAX, `FSINCOS`, both memory `FMUL`s and `FSTP`s, `POP ECX`, and `RET 8`. This is
stronger than an intrinsic demonstration, but it does **not** permit promotion:
the whole original body is the required comparison scope.

The direct model is 24 bytes and loads scale into an x87 register once. A private
volatile scale view produces the retail multiply/store sequence in 22 bytes.
Adding the observed receiver home and ordering produces the 30-byte residual
above. `polar_results.json` retains 30 measured model/profile combinations;
`polar_order_results.json` retains 12 focused ordering/preservation comparisons.

The version-matching [GCC 16.2 i386 backend](https://github.com/gcc-mirror/gcc/blob/releases/gcc-16.2.0/gcc/config/i386/i386.md#L24515)
selects `FSINCOS` through `sincosxf3` under its fancy-x87 and unsafe-math conditions.
Its [stack-adjustment peephole](https://github.com/gcc-mirror/gcc/blob/releases/gcc-16.2.0/gcc/config/i386/i386.md#L29380)
uses a clobbered scratch register for a PUSH and explicitly excludes the
alternative of pushing an already live register. In this member ABI ECX is
live on entry, whereas EAX is available as scratch. That explains the measured
one-byte residual; it is an inference from the primary backend and actual
output, not a proof that all possible compiler contexts are exhausted.

An additional useful lever must change legitimate compiler register selection
or stack allocation while retaining the ECX member ABI. Rewriting the initial
byte, masking it, changing the entry convention, or emitting that byte from C++
data would not meet the goal.

## Complete 17-byte `__frnd`

Fresh Ghidra establishes `0045EBBA..0045EBCA` as ordinary cdecl with a **double
stack argument**, rather than an ST0-input private entry. The only xref is
`00458CBF` in `__floor_default`; the full caller listing and callee memory are
retained. The helper loads its stack double, rounds under the current x87 mode,
spills to binary64, reloads that rounded double into ST0, and returns:

```text
5151dd44240cd9fcdd1c24dd04245959c3
```

The complete source model uses `__builtin_rint` plus a volatile double local to
retain the binary64 spill/reload. The separately owned `frnd_trials` branch
measured 274 combinations, including 164 valid source candidates with the known
four-byte incoming alignment, and found zero exact bodies. Diagnostic variants
that omit the spill, change the operation or signature, or assume stronger
incoming alignment are identified in `frnd_trials/measured_residual.json` and
do not count as faithful candidates.

The representative `preserve_014` uses `-Oz`, four-byte stack boundaries,
omit-frame-pointer, and observed EAX/EDX preservation. GCC emits the correct
FRNDINT and binary64 spill/reload, but realigns ESP to eight bytes and retains an
EBP frame. Its 22-byte body and 24-byte COFF contribution are:

```text
5589e583e4f883ec08dd4508d9fcdd1c24dd0424c9c3
```

The two trailing NOPs are recorded separately. A 19-byte body needs stronger
incoming alignment, which the retail caller evidence does not establish.
Aligned typedefs, packed spill storage, both ABI selectors, and alignment and
register-preservation flags do not yield the retail two-PUSH/two-POP frame.
`frnd_trials/README.md` gives the scripts, exact commands, hashes, full sections,
disassemblies, and faithful-versus-diagnostic classifications.

The next concrete lever is a backend capable of a legitimate four-byte-aligned
binary64 spill with the observed frame. An exact replacement still requires
compiling and comparing all 17 original bytes, without masking or rewriting.

## Compiler identity and retained proof

Installed driver: `/usr/bin/i686-w64-mingw32-g++`, reported GCC 16.2.0.

```text
driver SHA256:  0bf6128d4f161da3a8a9a9b480bbdaa4b403ebd2b65035e9819035284559f6cd
cc1plus SHA256: 1b0d277fb325f46537ae645118bbeb81804beee8f46a72b57c4195d95aeab76a
```

The actual backend is `/usr/lib/gcc/i686-w64-mingw32/16.2.0/cc1plus`. Primary
release sources and their hashes are retained as `gcc16_2_i386.md`,
`gcc16_2_i386.cc`, and `backend_primary_sources.json`; these explain the patterns
but do not substitute for measurement of the installed binary. The final polar
body SHA256 is `a94aa9141bf2dbfdd494b7b101b7f1880629870c9902218abb1e5613783ed493`;
both retail polar bodies hash to
`ee204b7afd1b942c09db2fb55b55a65701e35832fd7d1b7a039a1b854eaeca35`.

This work establishes compiler capability and measured complete-body residuals.
It recovers zero exact regions, changes zero maintained executable inputs, and
leaves the full readable, byte-matching, assembly-free C++ objective active.
