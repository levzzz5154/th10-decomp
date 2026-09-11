# Native LTCG clusters

Some retail functions do not follow the MSVC C++ calling convention. Their
internal entry convention puts an argument in a register MSVC only ever assigns
to a parameter during a native `/GL` link, or keeps `this` in `ECX` for a
variadic member. No C++ prototype can declare that, so the body must be built as
a *cluster*: a native-LTCG-linked module whose synthetic caller forces the
register convention, from which the outer fixed-address link takes only the
named function's bytes.

Clusters live in the project like any recovered unit:

| Piece | Path |
|---|---|
| Recovered source (single region, single function) | `matching2/msvc/src/.../<name>.cpp` |
| Cluster layout | `matching2/msvc/layout/ltcg/<name>.json` |
| Compiler-context driver | `matching2/msvc/layout/ltcg/<name>_context.cpp` |
| Registration | the `ltcg_clusters` array in `matching2/msvc/regions.json` |

`matching2/msvc/layout/ltcg/rank_level.json` (with its `_context.cpp`) and
`matching2/tools/matching/ltcg_cluster.py` are the working reference: read both
before writing a layout.

## Layout schema (schema_version 1)

```json
{
  "schema_version": 1,
  "name": "lowercase_identifier",
  "source": "src/game/<name>.cpp",
  "driver": "layout/ltcg/<name>_context.cpp",
  "headers": [],
  "image_base": "0x00400000",
  "description": "what the source shape is and which register the convention needs",
  "functions": [
    {"name": "SourceSymbol", "symbol": "?Decorated@@YAXXZ", "section": ".text$01<tag>",
     "address": "0x00401234", "size": 42, "actual_abi": "this in EAX; plain RET"}
  ],
  "context": {
    "symbol": "?SyntheticContext@@YGHPAPAUT@@@Z", "section": ".text$03context",
    "address": "0x00401280", "size": 64,
    "description": "synthetic caller that establishes the convention; not recovered game code"
  },
  "gaps": [
    {"section": ".text$00layout", "address": "0x00401000", "size": 100},
    {"section": ".text$02layout", "address": "0x00401276", "size": 1}
  ],
  "constants": [],
  "absolute_symbols": [
    {"symbol": "_data_00474788", "address": "0x00474788", "kind": "data"}
  ]
}
```

Rules the loader enforces (`load_cluster` in `ltcg_cluster.py`) — a layout that
breaks any of them fails the whole build, so check each by hand before probing:

- `name` is a lowercase identifier; `image_base` is exactly `0x400000`.
- `source` and `driver` are project-relative `.cpp` files and must differ: the
  driver includes the source, never the other way round.
- every function has a **distinct** `.text$…` section, and `symbol`/`address`/`size`
  must equal the maintained region's `symbol`/`address`/`size` exactly;
  `regions.json` must already mark that region `kind: "semantic"` with the same
  decorated symbol, and the source must own **exactly** that one region.
- `context` has a `.text$…` section distinct from every function's, and is never
  selected as recovered code.
- `gaps` cover the rest of the image the linker would otherwise lay out itself:
  the head gap from `0x401000` up to your first selected section and a gap
  covering everything between a function's end and the next section. Every gap
  gets a distinct section.
- **no two entries may overlap or sit out of order** (functions, context,
  constants and gaps are all range-checked together). A gap that starts inside a
  function's extent is the usual mistake.
- `absolute_symbols` bind external code/data the cluster references:
  `kind: "data"` for a data address, `"relative_code"` for an external function
  (`coff_value` gets the image base subtracted automatically), `"metadata"` for
  `__fltused`-style markers with address `0`.

## Four traps, each of which costs a build

These were found the hard way; check them before the first probe.

1. **The head gap must place the function at its own address.** `.text$00layout`
   spans `0x401000` to the function's address, so its size is
   `function_address - 0x401000` — not the distance to some later section. An
   off-by-anything here puts the whole cluster at the wrong address and the load
   reports `compiler-context entry address differs`.
2. **The gap after the function must reach the context.** Context goes at
   `align16(function_address + function_size)`, and `.text$02layout` must cover
   every byte between the function's end and that address. Any uncovered hole
   fails validation.
3. **A `C` context symbol is decorated differently for `/ENTRY` and for the MAP.**
   `LINK /ENTRY:_Name@N` looks for `__Name@N` and fails; the MAP then records
   `_Name@N`. Declare the context as a plain C++ function (no `extern "C"`) and
   use its `?`-mangled name: `/ENTRY` takes a `?` name verbatim and the MAP
   records the same string, so the two agree. Compile the driver once without
   `/GL` and read the symbol with `i686-w64-mingw32-objdump -t` rather than
   guessing the decoration.
4. **Every cluster's symbol must be unique across the manifest.** Two clusters
   that both declare `?LoadValue@ObjectAccessor@@QBEHXZ` make the whole-image
   build fail with `duplicate selected symbol`. Name the type after the region
   (`ObjectAccessor_00405bb0`) so the mangled names differ.

The context's `size` is whatever the compiler emitted for that driver, which is
only knowable after a build: probe once, read `.text$03context`'s size column
from the generated `cluster.map`, put that number in the layout, and probe again.
`matching2/tools/waves/cluster_accessors.py` does exactly that loop for the
uniform accessor family and is worth reading as a worked example.

## Driver pattern

The driver includes the recovered source and imposes the convention through a
synthetic caller that the linker colours:

```cpp
// Compiler context only; never selected as recovered game code.
#include "../../src/game/<name>.cpp"

#pragma code_seg(".text$03context")
int __stdcall <Name>CompilerContext(<Owner>** items, int count) {
    while (count--) {
        (*items)-><Method>();
        ++items;
    }
    return 0;
}
#pragma code_seg()
```

The caller must be a shape whose codegen *forces* the target register. That is
the whole experiment: change the context until the emitted function matches
retail's entry. Arrays of `this`-pointers, struct-return chains, and
mixed-integer/pointer parameter lists are the levers that move a value into
`EAX`; a plain loop over `this` pointers reproduces `this in EAX`.

## Workflow

1. The region is already carved into its own single-region source (the parent
   did this). Read it, and read `matching2/tools/waves/reference.py --source
   <src>` for the retail bytes at their real addresses, plus the IDA listing
   `ida/th10.exe.c` and `decompiled/ghidra_augmented/functions/<addr>.c`.
2. Write the C++ body under `#pragma code_seg(".text$01<tag>")`, with the
   function declared `__declspec(noinline)` on its class/struct as needed.
3. Write the layout and the driver. Update `regions.json`: the region must be
   `kind: "semantic"` with the decorated symbol equal to `functions[0].symbol`.
   Add `"layout/ltcg/<name>.json"` to `ltcg_clusters`.
4. Probe:
   ```sh
   python3 matching2/tools/matching/probe.py --source <src> --json \
     --project matching2/msvc --output matching2/build/waves/probe4/<AGENT>
   ```
   The probe builds the cluster through `build_cluster` when the layout is
   registered, and compares the extracted contribution against retail.
5. Iterate on the **context caller** and the body shape until it reports EXACT.
   The `actual_abi` field is documentation for the next reader — keep it honest.

## Failure policy

If the cluster cannot be made exact: revert your layout, driver and source (the
pristine single-region source is at `matching2/build/waves/backup4/<source>`),
remove the `ltcg_clusters` entry and leave the region `kind: "asm"`. Report the
blocking difference: address, differing bytes, expected vs actual instruction,
the context shapes tried, and the closest variant.

Never leave the manifest pointing at a cluster that does not probe EXACT — that
breaks the whole-image build for every other agent.

## Report format

```
AGENT <id>
EXACT: src/... 0x401234 (42B, this in EAX) ...
REVERTED: src/... (layout removed; still differs at +0x6: expected d9 fb, actual d9 ff)
BLOCKED: src/... — context shapes tried, closest variant, next idea
```
