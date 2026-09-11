# Wave 6 — replace inline assembly with readable, byte-exact C++

Repo root: `/home/levzzz/Games/th10Decomp`. Run every command from there. C++98 only.

The project builds Touhou 10 (`th10.exe`) with MSVC 13.10.6030 under Wine and must
reproduce the retail `.text` byte for byte. Your job: replace assigned
`__declspec(naked)` bodies with ordinary C++ that MSVC compiles to exactly the
retail bytes, and flip the region in the manifest to the symbol MSVC emits.

The tree currently builds byte-exact. Anything you leave that does not probe
EXACT breaks it for every other agent, so land incrementally.

## Ground rules

- Edit only the source files in your own brief plus
  `matching2/build/waves/results6/<AGENT>/`. Scratch in `/tmp/<AGENT>/`.
- Pristine copies of your files are at `matching2/build/waves/backup6/<source>`;
  that is the only rollback you need. Never hand-revert.
- NEVER run `make`, `./matching2/build_msvc.sh`, formatters, linters or
  project-wide tests. The per-unit probe is the gate and takes seconds.
- NEVER leave a file converted while its manifest region is still `asm` — either
  probe EXACT (keep the file, keep the proposal JSON) or restore the pristine copy.
- Work in order: convert the regions that look easiest first, land them, then
  spend remaining effort on the hard one. A wave that lands three of four
  regions beats one that lands none.

## Per-region workflow

1. `python3 matching2/tools/waves/reference.py --source <src>` — the current
   source, retail disassembly at real addresses, Ghidra/IDA excerpts, and the
   name of every code and data address the function uses.
2. `ida/th10.exe.c` — IDA listing (`//----- (0040B940) ----` then the prototype).
   `decompiled/ghidra_augmented/functions/<8-hex-addr>.c` — Ghidra pseudocode.
3. Write the C++ body. Express the *same source-level shape* retail had: struct
   offsets, field order, signedness, `float` vs `double`, pointer arithmetic,
   loop form (`for`/`while`/`do-while` rotate differently), and declaration order
   — statement order decides x87 store scheduling.
4. Proposal JSON at `matching2/build/waves/results6/<AGENT>/<unit-stem>.json`:
   ```json
   {"regions":[{"name":"semantic_<Name>_<addr>","source":"src/game/foo.cpp",
                "symbol":"<symbol MSVC emits>","address":"0x0040B940",
                "size":99,"kind":"semantic","owner":"0x0040B940"}]}
   ```
   `symbol` may be an exact object symbol or a unique substring of the decorated
   one; a plain name like `Foo_Bar_0040b940` is preferred. Include one entry per
   region you convert. Leave out regions you did not convert.
5. Probe:
   ```sh
   python3 matching2/tools/matching/probe.py --source <src> \
     --proposal matching2/build/waves/results6/<AGENT>/<unit-stem>.json \
     --json --project matching2/msvc \
     --output matching2/build/waves/probe6/<AGENT> \
     > /tmp/<AGENT>/<unit-stem>.report.json
   ```
   Exit status 1 means NOT EXACT.
6. Iterate with the microscope, not by guesswork:
   ```sh
   python3 matching2/tools/waves/vdiff.py --source <src> --address 0x0040B940 \
     --proposal matching2/build/waves/results6/<AGENT>/<unit-stem>.json
   ```
   It prints retail vs compiled instruction by instruction, marks differing
   instructions with `!`, and reports `differing_bytes`. **Track that number**:
   change one thing at a time and keep whatever lowers it. Under a second per run.
7. Unbound linker names (`__real@…`, `__imp__…`, `_data_…`) are not your bug;
   bind them with
   `python3 matching2/tools/waves/bind_relocations.py --source <src> --proposal <your.json> --apply`
   and re-probe. Several agents write that file; run it again if a name does not
   stick, and report any name that never sticks.

## Jump tables are already handled

MSVC emits a `switch`'s jump table *inside the function's own section*, after the
code and its alignment padding. The manifest now records that: for every such
function the region extent already covers code + padding + table, and the table's
bytes are emitted by the region's own inline assembly. So write the `switch`
normally and the probe will compare it against the full extent. Do not try to
merge regions or change extents — a proposal cannot.

## What cannot be done, and how to tell

MSVC places call arguments only in ECX/EDX (or on the stack); never EAX, EBX,
ESI or EDI, and a 64-bit argument always goes on the stack. So:

- **Your region's own entry convention**: if the IDA prototype shows a parameter
  in EAX/EBX/ESI/EDI or EDX:EAX (`__usercall`/`__userpurge`, e.g.
  `sub_42E5A0@<eax>(int a1@<edi>)`), stop immediately, report it as needing a
  native LTCG cluster, and move to your next region. Cluster agents handle these.
- **A callee's convention**: if a direct `call` target still exists only as
  assembly and its own prototype takes a parameter in one of those registers,
  this region cannot be compiled until that callee is recovered. Recognise it by
  reading the callee's IDA prototype. Report it as blocked-by-callee and move on;
  do not spend the budget. (The dispatcher already filters most of these out; if
  you find one, it is worth reporting.)
- A region that ends in a `jmp` is a fragment of a larger function; the parent
  merges those. If you meet one, report it.

## Failure policy

If a region still reports NOT EXACT after a real effort:

- Restore that file from `matching2/build/waves/backup6/<src>` unless an earlier
  region in the same file is already EXACT — then keep the file and delete only
  the failing region's proposal entry.
- Report the blocking difference precisely: address, differing byte count,
  expected vs actual instruction, the closest variant, and the next idea. Make it
  actionable; another agent picks it up later.

## Report format (your final yield)

```
AGENT <id>
EXACT: src/a.cpp 0x40b940 (99B), src/a.cpp 0x412db0 (50B), ...
REVERTED: src/b.cpp (differs at 0x41adf0 +0x12: expected 8b 45 08, actual 8b 4d 08)
BLOCKED: src/c.cpp 0x405620 — reason, closest variant, next idea
BINDINGS: names added, any that would not stick
```

The parent reconciles the manifest and runs the whole-image build; do not attempt it.
