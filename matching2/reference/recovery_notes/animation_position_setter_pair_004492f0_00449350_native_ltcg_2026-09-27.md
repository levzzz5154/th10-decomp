# Animation position setter pair: native-LTCG EXACT

Integrated on 2026-09-27. The maintained pair probe and whole-executable
byte comparison both passed; the current addendum checkpoint records the gate.
The experiment and promotion instructions below describe the retained evidence.

Measured 2026-09-27. Both complete recovered bodies are byte exact:
`0x004492F0..0x00449349` (90 bytes) and
`0x00449350..0x004493BE` (111 bytes), **201 selected bytes total**.
All sources are ordinary readable C++; no inline assembly, naked bodies,
instruction transformations, or byte masks were used.

## Behavior and live evidence

Fresh Ghidra MCP disassembly of `th10.exe` is saved as
`ghidra_004492f0.json`, `ghidra_00449350.json`, and `ghidra_004491c0.json`.
Both setters look up the aggregate animation id through `0x004491C0` and do
nothing if no object is found. The plain setter copies the three-word position
record to object `+0x340`; the translated setter adds 224 to x and 16 to y,
then copies z. If the object's `+0x18` child flag is zero, each direct child in
the `+0x14` linked list gets the same operation. Child nodes carry the object
pointer at +0 and the next pointer at +4.

The observed private convention has the position in ESI, context in EDX, one
aggregate id on the stack, and RET 4. The first five bytes copy/push that id,
and both direct calls still target the real `0x004491C0` address. Ordinary
opaque Find declarations would clobber the desired convention.

## Compiler context

The driver holds a position cursor across calls to both siblings before
advancing it. Native LTCG selects ESI for that cursor and propagates it into
both callees. The id remains a four-byte aggregate so it stays on the stack.
The two selected setters compile as separate /GL inputs.

The full readable Find body from the maintained lookup was cloned with unique
type and class names as `position_setter_find_anchor.cpp`, included in the
context, and placed at `0x004491C0`. It is a 73-byte unselected ABI anchor,
not exported recovered code. Its complete compiled bytes also equal retail;
`comparison.json` verifies that equality independently.

The plain setter uses aggregate vector assignment, reproducing the three MOV
copies and shrink-wrapped EDI save. The translated setter uses genuine float
literals 224.0f and 16.0f, with compiler pool aliases to `0x470B4C` and
`0x470B48`; this establishes retail's FLD-position/FADD-pool operand order.
Holding `&child->object->position` in a local avoids repeatedly reloading the
child object between stores and reproduces the exact ADD +0x340 sequence.

## Promotion inputs

Copy these files from the scratch `msvc/` directory to the maintained project:

- `src/render/animation_manager_set_position_004492f0.cpp`
- `src/render/animation_manager_set_translated_position_00449350.cpp`
- `include/th10/render/position_setter_pair.hpp`
- `layout/ltcg/position_setter_pair.json`
- `layout/ltcg/position_setter_pair_context.cpp`
- `layout/ltcg/position_setter_find_anchor.cpp`

Register `layout/ltcg/position_setter_pair.json` as a new cluster. The existing
selected Find remains owned by its existing stop-frame cluster. The unique
anchor names avoid symbol ownership conflicts, and its body is never exported.
`proposal.json` supplies both exact setter symbols; preserve existing owner
metadata during registration.

## Verification

```text
python3 matching2/tools/matching/probe.py \
    --project matching2/build/experiments/position_setter_pair/msvc \
    --source src/render/animation_manager_set_position_004492f0.cpp \
    --source src/render/animation_manager_set_translated_position_00449350.cpp \
    --output matching2/build/experiments/position_setter_pair/probe_03 \
    --write-proposal matching2/build/experiments/position_setter_pair/proposal.json

0x004492f0      90 bytes  SetAnimationPosition_004492f0  EXACT
0x00449350     111 bytes  SetAnimationTranslatedPosition_00449350  EXACT
EXACT
```

The probe builds the cluster independently for each selected source, so both
whole bodies passed twice. The native report is
`probe_03/clusters/position_setter_pair/report.json`; emitted instructions are
in `disassembly.txt`. `comparison.json` records complete native-versus-retail
SHA-256 equality for both selected functions and the Find anchor. The report
records zero masked bytes, zero changed instruction bytes, and no reference
bytes used for build.

The maintained project was untouched by this experiment.
