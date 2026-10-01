# Embedded animation child lookup and explicit position forwarding

2026-10-01. The entire function at 0x00449770..0x004497A3 is now ordinary C++
in `src/render/animation_find_embedded_child_00449770.cpp`. Its 52-byte native
MSVC contribution exactly matches retail. Two position wrappers were also
corrected to declare and forward their inherited ESI position pointer to their
real recovered callees; both original 15-byte bodies remain exact.

## One function rather than two fragments

The old partition split the lookup into 15 assembly bytes at 0x00449770,
one padding byte at 0x0044977F, and 36 assembly bytes at 0x00449780. These
three records now form one complete 52-byte semantic region. This retires
51 assembly bytes and moves the interior padding byte into its owning function.
The obsolete, unreferenced fragment sources were removed. Their old region
records are retained under `previous_records`, and their source snapshots remain
in the scratch project and version history.

The owner embeds its first link at +0x10. Each link holds an object pointer,
next and previous pointers. The loop compares the object's signed 16-bit script
index at +0x38A against the full integer selector, follows next at +4, and
returns the object's four-byte ID at +0. No match returns a zero ID. Compile-time
checks verify the ID size, script-index offset, link stride and embedded head.

Native LTCG supplies the private output buffer in EAX, owner in ECX and selector
in EDX, with plain RET. The ID record's ordinary constructor and copy produce
both return paths without a shim. The synthetic array-walking caller is a
separate unselected 52-byte compiler contribution. Layout gaps are also
unselected; no instructions, addresses or comparison bytes are rewritten.

Fresh Ghidra xrefs show that the branches into 0x00449780 and 0x00449794 originate
inside this function. No external entry reference was found. Defining the
previously unrecognized function in Ghidra made its decompilation confirm the
embedded head, signed index comparison, next traversal, EAX output and zero
fallback. Ghidra's reachable body is 44 bytes; the complete compiler contribution
also contains eight loop-alignment bytes (a seven-byte LEA and one NOP).
The native comparison includes all 52 bytes, including that alignment.

## Position wrappers and their actual callees

The existing wrappers at 0x00449650 and 0x00449660 invoked opaque declarations
that omitted their inherited position input. The new
`AnimationPositionHandle::SetPosition(position)` and
`SetTranslatedPosition(position)` explicitly take and forward that input.
The four-byte handle ID is a typed `PositionScriptId_004492f0` record.

Both wrappers now share the `position_setter_pair` native-LTCG cluster with the
actual 90-byte plain setter and 111-byte translated setter. The long-lived
position cursor establishes ESI for all four entries. The wrapper keeps its
handle in EAX, loads the ID into ECX, loads the lookup context into EDX, pushes
the ID and calls the appropriate real setter. It does not introduce a register
adapter or change its 15-byte extent. The old wrapper-only compiler context and
manifest were removed because they no longer own any functions.

The existing full 73-byte lookup model remains unselected context for the
position pair; an independent whole-body comparison again confirms it is
identical to the separately owned real lookup. The selected Find and stop/run
family remain in their own cluster and are included in the focused regression
probe. The original setter and translation semantics are unchanged.

## Verification and remaining scope

The final maintained-source probe passes 19 complete regions / 1,097 bytes:
the new lookup, both position setters and wrappers, and all fourteen functions
of the existing lookup/stop/run family. The full production build then passes
all .text and the complete 487,936-byte executable comparison. SHA-256 remains
`2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`.
The companion evidence JSON contains full native provenance, source fingerprints,
comparisons, Ghidra evidence and whole-image proof.

```sh
python3 matching2/tools/matching/probe.py \
  --source src/render/animation_find_embedded_child_00449770.cpp \
  --source src/unidentified/unassigned_anim_setters_00449.cpp \
  --source src/render/anm_propagate.cpp
make MSVC_ARGS='--jobs 32 --verify matching2/build/oracle/th10.exe'
make progress
```

Scratch evidence is in `matching2/build/experiments/embedded_child_lookup_2026_10_01`
and `matching2/build/experiments/position_wrappers_2026_10_01`. Current accounting
is 1,845 semantic regions / 96,635 bytes, 453 assembly regions / 226,263 bytes,
and 15,495 padding bytes. Semantic rendering sources still contain some inline
x87 blocks. The full no-inline-assembly decompilation objective is unfinished.
