# Public animation users — 0x0040B1B0 and 0x0041FDD0

Date: 2026-09-27

## Result

`0x0040B1B0` is recovered as readable C++ without inline assembly. The
complete 147-byte body passes the normal probe with zero differing bytes
and no relocation masks. It is ready for parent integration.

`0x0041FDD0` remains unpromoted. Its complete candidate contribution is
219 bytes versus the retail 220 bytes; a raw aligned diagnostic comparison
counts 99 differing bytes including the extent difference. Its first
104-byte branch is identical to retail; the remaining allocation difference
starts in the second branch. The full 220-byte gate has not passed.

No production code or ownership records were changed by this worker. Only
this unique note was written outside the ignored scratch project.

## Live Ghidra evidence

Live Ghidra MCP decompilation at `0x0041FDD0` and dry-run disassembly of all
147 bytes at `0x0040B1B0` were queried for `th10.exe`. Ghidra has no function
record for the latter address, so its complete instruction range was read
through `disassemble_bytes`; no Ghidra mutation was needed.

`0x0040B1B0` has seven stack arguments and RET 28. It allocates an animation,
sets render bucket 15 and flag `0x40000000`, initializes the resource script
using the signed low 16 bits of the script argument, registers the object,
looks up the fresh handle, invokes an optional fastcall initializer with
object/context, stores update/draw callbacks at `+0x398`/`+0x39C`, writes the
handle through the result pointer, and returns that pointer. A missing lookup
zeros the returned handle; the callback and callback-field writes retain
the exact retail behavior afterward.

`0x0041FDD0` is a title-effect task despite the existing result-screen file
name. State fields are signature handle/resource at `+0x3DC`/`+0x3E0`,
signature/interface readiness counters at `+0x3E4`/`+0x3E8`, and frame count
at `+0x3EC`. The game-thread resource at `+0x8994` is the ASCII resource;
the cached interface handle is at `+0x89A4`. The second branch uses script 6
and position `{480.0f, 392.0f, 0.0f}`.

The Ghidra/legacy interpretation that stores the state pointer at `+0x3DC`
is incorrect: the registrar writes a handle into the reused incoming stack
argument slot, and that handle is subsequently copied to the state field.
The scratch C++ model corrects this alias interpretation.

## The register-preservation dependency that unlocked 0x0040B1B0

The existing 103-byte registrar ABI model stored one cached local ID twice.
Its generated body preserved EDX. The real registrar at `0x004489D0` reads
the counter again after writing the entity's handle and ends with
`mov edx,[edx+0x732454]`, clobbering EDX. That distinction changes a caller's
allocation even though both registrar models have the same input ABI.

The new compiler-visible registrar model retains both actual counter reads:

```cpp
*(int*)entity = *(int*)(manager_bytes + 0x732454);
*(int*)out = *(int*)(manager_bytes + 0x732454);
```

It emits a complete 114-byte anchor, placed at the real address, and produces
the correct final EDX clobber. The body is not selected as recovered game code.
This forces the wrapper to retain its manager in ESI and to copy ESI into
EDX before the registration and lookup calls, exactly as retail does.

Two volatile captures express the retail read order without extra
instructions: the output pointer is read before allocation/callback calls,
and the fresh handle is read from the reused script argument slot after
registration. They establish the early EBP output pointer and direct EDI
handle load respectively. A four-byte aggregate ID keeps the lookup's ID on
the stack and leaves its receiver unused, matching the existing exact finder.

## Complete native dependencies

The isolated normal build validates every selected contribution and every
declared anchor contribution. Fresh byte comparisons additionally verify:

| Unselected dependency | Native extent | Full retail comparison |
| --- | ---: | --- |
| Entity initializer `0x00401DE0` | 273 | exact |
| Positioned primary creator `0x00448D50` | 95 | exact |
| Animation finder `0x004491C0` | 73 | exact |
| Animation pool allocator `0x00449950` | 161 | exact |

The script-loader and primary-registrar models are complete 207-byte and
114-byte ABI anchors. Their bytes are not promoted or claimed exact. The
ordinary initializer member at `0x00449870` is bound directly by its known
ECX receiver/two-stack-argument declaration; its unrelated 217-byte recovery
residual is not introduced into this caller cluster.

## Artifacts and verification

Scratch project:
`matching2/build/experiments/animation_public_callers/msvc`.
Ready integration files:

* `src/unidentified/FUN_0040b1b0_0040b1b0.cpp`
* `include/th10/render/animation_public_callers.hpp`
* `layout/ltcg/animation_public_callers.json`
* `layout/ltcg/animation_public_callers_context.cpp`
* `layout/ltcg/animation_public_callers_anchors.cpp`

The final proposal is `proposal.json` in the lab directory. Normal probes
`attempt11.json` and `attempt12.json` are exact. Attempt 10 already produced
the same full exact 147-byte body inside the two-caller experiment, but its
overall cluster gate correctly rejected the 219-byte title contribution.
All three selected bodies are identical, SHA-256
`55713fdb6d3a26ae24ec9da3c3f2d53f565470a5de08ababebe857d8e708e41d`.

The final command was:

```sh
python matching2/tools/matching/probe.py \
  --project matching2/build/experiments/animation_public_callers/msvc \
  --source src/unidentified/FUN_0040b1b0_0040b1b0.cpp \
  --output matching2/build/experiments/animation_public_callers/attempt12 \
  --json \
  --write-proposal matching2/build/experiments/animation_public_callers/proposal.json
```

The standalone exact cluster retains the title task as an ordinary external
binding in the synthetic context. The scratch result-screen source is not
ready for integration and production must retain its assembly owner.
Its model is preserved separately in `title_candidate_219.cpp`,
`two_caller_layout.json`, and `two_caller_context.cpp`. Compact byte evidence
is in `bounded_measurements.json`; disassembly artifacts are
`exact_callbacks_disassembly.txt` and `title_residual_disassembly.txt`.

## Remaining title-task lever

The title candidate retains the whole game-thread pointer in ESI, loads the
cached scalar into EAX, and stores through `[esi+0x89A4]`. Retail keeps the
thread transiently in EAX, loads the cached scalar into ECX, materializes the
cached handle address in ESI, and finally copies the returned handle through
that address. This creates the one-byte extent difference and shifts the
remaining instructions. Typed handle records, a cached-field pointer,
volatile cached reads, a union handle, explicit memcpy, a vector constructor,
and separate/co-located `/GL` inputs did not change that allocation.

An aggregate-return or assignment topology that materializes the cached
destination address before the positioned-creator call is the next useful
lever. Repeating the now-proven allocator, finder, or registrar input ABI
does not address this remaining field-address allocation.
