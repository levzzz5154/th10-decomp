# MIDI tick C++ equivalence recovery, 2026-10-05

The 473-byte tick at `0x0043AF30` is now covered by
`layout/equivalent/midi_tick_0043af30.json`. The default build uses
`equivalent/platform/midi_tick_0043af30.cpp`; the exact build retains the
assembly owner. This is an equivalent recovery, not a byte-exact promotion.

The starting point is the complete native candidate documented in
`midi_tick_volume_2026-09-30.md`. Its fade arithmetic, x87 conversion calls,
64-bit event-time arithmetic, callback/reload behavior, loops, and ABI already
match. A volatile escaping member-function pointer in the compiler caller
keeps Tick's public ECX receiver convention while keeping the channel-volume
adjustment variable. This replaces the prior cluster's explicit public root;
the pointer and synthetic caller are not emitted into the game. Supporting
volume and reset bodies establish compiler context, and their calls in Tick
are rebound to the existing production addresses.

The current equivalence probe reports 146 instructions, 143 identical, and
one three-instruction `code-shape` difference at offset `0x100`:

```text
retail                                 C++
mov eax,[edi+0x138]                     mov ecx,[edi+0x138]
lea ecx,[eax+ebp]                       mov eax,[ecx+ebp+4]
mov eax,[ecx+4]                         add ecx,ebp
```

Let `B = mem32(EDI + 0x138)` and `O = EBP`. Both sequences perform the same
two reads, in the same order, without a write or call between them. Both
finish with `ECX = (B + O) mod 2^32` and
`EAX = mem32((B + O + 4) mod 2^32)`. Every other general-purpose register is
unchanged. The second read is the signed next-event time; subsequent CDQ
therefore produces the same EDX in both bodies.

ADD changes arithmetic flags while LEA does not. The next instructions are
`cdq; cmp edx,esi; ja ...; jb ...`. CDQ neither consumes nor changes those
flags, and CMP overwrites every arithmetic flag before either conditional
branch reads them. Thus the flag difference is dead on every path. The low
word comparison and callback receive identical values. This proof assumes
the same valid track memory required by the original routine; it does not
claim identical register snapshots at a faulting invalid-memory read.

The layout records these exact instructions, with no frame-offset allowance,
base/index allowance, or unproven branch-target exception. The existing gate
checks all remaining instructions, control-flow targets, bindings, and code
extent and rejects any drift. No equivalence-tool change was needed.

Validation: both named equivalence probes passed, followed by successful
`make` and `make EXACT=1`. The latter verified all 487936 executable bytes.
Together with the replay callback this reduced remaining assembly to 78
regions / 104539 bytes (216535 recovered bytes).
