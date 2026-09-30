# Complete `__frnd` frame investigation with untouched LLVM COFF assembly

The complete helper at `0045EBBA..0045EBCA` remains unrecovered. The new stock
GCC/LLVM route removes GNU COFF padding but still emits **22 instruction bytes**
against the required **17 bytes**. Fresh caller evidence supports only four-byte
incoming alignment. Two narrowly scoped compiler-alignment experiments also
remain 22 bytes and are retained as unapproved diagnostic prototypes. No
maintained source, compiler profile, generic pass, manifest, framework, or
executable input was changed.

The evidence is under
`matching2/build/experiments/gcc_frnd_frame_2026_09_28`. `probe.py` reproduces all
eight bounded stock-route comparisons. `rule_probe.py` reproduces the two
separate experimental rule comparisons. Both compare the complete `.frnd`
COFF section, never truncate a section, never mask instructions, and never
rewrite compiler assembly or object bytes.

Fresh Ghidra MCP function info, the complete helper listing, its raw memory,
and the complete `__floor_default` caller are retained in `ghidra_fresh.json`.
The raw 17 bytes agree with the immutable PE oracle:

```text
5151dd44240cd9fcdd1c24dd04245959c3
```

This is ordinary cdecl with a binary64 stack argument at entry ESP+4, rounding
under the current x87 mode, a forced binary64 store/reload, ST0 return, and plain
RET. It is not an ST0-input entry. The readable selected source model keeps the
public prototype `double(double)` and uses only a private word-aligned binary64
home:

```cpp
typedef double StackDouble __attribute__((aligned(4)));
extern "C" double RoundToDouble(double value) {
    volatile StackDouble rounded = __builtin_rint(value);
    return rounded;
}
```

The source is `typed_local_only.cpp`; its section and noinline attributes merely
isolate the complete function for measurement. `__builtin_rint` is compiled
with `-frounding-math` and no unsafe-math flag. The source does not narrow or
reinterpret the public double argument. GCC [documents reduced alignment on
typedefs](https://gcc.gnu.org/onlinedocs/gcc/Common-Type-Attributes.html), and
`alignof_probe.cpp/.s` confirms that this installed compiler gives ordinary
double alignment eight and the explicit storage typedef alignment four.

The installed driver `/usr/bin/i686-w64-mingw32-g++`, its actual GCC 16.2.0
`cc1plus`, and stock `/usr/bin/llvm-mc` are hashed in `probe.json`. The route uses
GCC `-S`, then passes that generated assembly unchanged to
`llvm-mc -triple=i686-pc-windows-gnu -filetype=obj`. Assembly hashes are checked
before and after assembly. The relevant flags are `-Oz -mfpmath=387`, SSE/SSE2
disabled, preferred and incoming stack boundaries both four bytes,
omit-frame-pointer, EAX/EDX excluded from allocation, `-frounding-math`, and
exceptions, unwind tables, stack protection and compiler-identification strings
disabled. Full argv arrays, source/tool/assembly/object hashes, every COFF
section, and relocations are retained.

The complete faithful stock body is:

```text
5589e583e4f883ec08dd4508d9fcdd1c24dd0424c9c3
```

It has a **22-byte complete section, zero padding and zero relocations**. GCC
uses PUSH EBP, copies ESP to EBP, aligns ESP down to eight, allocates eight
bytes, and later uses LEAVE. The FRNDINT/FSTP/FLD operation is present, but the
retail two-PUSH/two-POP ECX frame and its argument displacement remain unmatched.
This is complete-function capability evidence, not an exact replacement.

The original plain double model, explicit aligned typedef, typed private home,
packed struct, two packed unions, and a valid bit-cast storage route are
measured separately. The first six faithful models all retain the 22-byte
frame; the bit-cast route grows to 56 bytes. Disabling scalar replacement does
not remove the frame. A targeted Intel MCU option test suppresses the normal
local-alignment policy but changes argument and return ABI to EAX:EDX and
ignores the requested regparm override. It produces 31 bytes and is explicitly
excluded as ABI-incompatible. No such profile is proposed.

`caller_alignment/alignment_conclusion.md` and `alignment_result.json` retain
the independently investigated callers and stack arithmetic. If F is ESP on
entry to `__floor_default`, the helper enters at F-32 and its argument is at
F-28; the floor dispatcher tail paths preserve entry ESP. Feasible scheduler
and rendering chains establish relative offsets but do not establish the
absolute modulo-eight residue. One bounded caller leaf has no Ghidra Function
object or known reference to its head. An apparent callback counterexample
was found to bypass the floor branches and is explicitly excluded. The evidence
proves neither an eight-byte invariant nor an actual misalignment counterexample.
Microsoft's [x86-stack discussion](https://learn.microsoft.com/en-us/cpp/build/x64-software-conventions?view=msvc-170#conflicts-with-the-x86-compiler)
describes the four-byte ABI floor. The historical 19-byte stronger-alignment
candidate therefore remains diagnostic and unpromoted.

The version-matching primary backend sources `gcc16_2_i386.cc/.h` explain the
frame. `ix86_local_alignment` promotes DF locals to 64-bit alignment even for
the explicit four-byte typedef. `ix86_minimum_alignment` has a downgrade for DI
homes but no corresponding DF exception. The retained expand RTL gives the
incoming double memory A32 and the private home A64. This is a compiler policy
difference rather than a missing FRNDINT operation.

The separate `annotations_only_honor_word_double_home.cc` prototype lowers only
the explicit private DF home's memory and declaration alignment promises to
32 bits, with no instruction, parameter, offset, or global stack-state edits.
It emits the same complete 22-byte section. An independent review explains why:
stack expansion already cached its realignment decision, and nonzero-frame
finalization does not generally clear that decision from lowered annotations.

The later `honor_word_double_home.cc` prototype also records a 32-bit maximum
for a single explicit home covering the entire eight-byte local frame, leaving
the global needed/estimated/preferred boundaries and DRAP state untouched. It
still emits 22 bytes. An observer before prologue generation finds that GCC
has restored the slot maximum to 64 despite the surviving private-home memory
accesses being A32. Both complete measurements are in `rule_probe.json`.

Neither prototype has general rule approval. The independent review found a
material provenance gap: expansion clears `DECL_USER_ALIGN`, so observing zero
after expansion cannot reject a stronger explicit source declaration alignment.
Complete allocation and reusable-slot provenance must also survive, and future
pseudo spills can legitimately require stronger alignment. See
`alignment_rule_review/review_conclusion.md`, `rtl_alignment_fields.md`, and
`primary_sources.json`. The maintained `initialize_stack_home.cc` was never
modified or weakened.

The next useful lever is a reviewed allocation-stage policy covering local,
minimum, and spill alignment consistently for explicitly word-aligned private
binary64 storage. It must retain pre-expansion declaration guarantees, preserve
the public ABI and future-spill requirements, and be tested independently before
promotion. Changing cached fields ad hoc, narrowing the public parameter,
rewriting the section, or accepting only the floating-point middle would not
satisfy the complete 17-byte goal.

This investigation promotes zero regions and removes zero maintained assembly
bytes. The full readable, byte-matching, assembly-free C++ objective remains
active.
