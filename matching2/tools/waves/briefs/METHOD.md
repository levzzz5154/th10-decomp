# Wave 3 — replace inline assembly with readable, byte-exact C++

Repo root: `/home/levzzz/Games/th10Decomp`. Working dir for every command: repo root.

The project builds Touhou 10 (`th10.exe`) with MSVC 13.10.6030 under Wine and must
reproduce the retail `.text` byte for byte. Compiled assembly is kept in
`matching2/msvc/src/**` as `__declspec(naked)` bodies (`asm_<Name>_<addr>`), and the
manifest `matching2/msvc/regions.json` records which symbol owns each address range.
Your job: replace assigned `__declspec(naked)` bodies with ordinary C++ that MSVC
compiles to exactly the retail bytes, and change the region's `symbol` to the name
MSVC emits.

## Ground rules

- Only edit the files listed in your own brief plus files under
  `matching2/build/waves/results3/<AGENT>/`. Never edit another agent's file.
- C++98 only (no `auto`, no range-for, no `//` comments are fine, no C++11 library).
  Match the surrounding file's style; the existing recovered code is the reference.
- NEVER leave a unit in a state where the source is converted but its manifest
  region is still `asm`: that breaks the full build. Either the probe reports EXACT
  (then keep the file and write your proposal JSON) or you restore the pristine copy.
- Do not run `make`, `build_msvc.sh`, linters or any whole-project command. The
  per-unit probe is your only gate. Keep scratch files in `/tmp/<AGENT>/`.

## Per-region workflow

1. Read the current file and locate your region's naked body.
2. Gather retail evidence for the exact address range:
   - `python3 matching2/tools/waves/reference.py --source <src>` — source, retail
     disassembly at real addresses, Ghidra/IDA excerpts, referenced symbol names.
   - `ida/th10.exe.c` — IDA listing; sections start with
     `//----- (0040B940) ----------------------------------------` followed by the demangled
     prototype.
   - `decompiled/ghidra_augmented/functions/<8-hex-addr>.c` — Ghidra pseudocode when present.
   - `decompiled/ghidra_augmented/index.tsv` — address index.
   - Callee prototypes: `grep -n "^// 0x\|extern \"C\"" matching2/msvc/src/...` and the
     headers under `matching2/msvc/include/`.
3. Write the C++ body. The compiler decides the instruction selection, so the real
   work is expressing the *same source-level shape* retail had: struct offsets,
   field order, signed/unsigned, `float` vs `double`, pointer arithmetic, loop form,
   and declaration order (statement order changes register allocation).
4. Build a proposal JSON at
   `matching2/build/waves/results3/<AGENT>/<unit-stem>.json`:
   ```json
   {"regions":[{"name":"semantic_<Name>_<addr>","source":"src/game/foo.cpp",
                "symbol":"<decorated or plain name MSVC emits>","address":"0x0040B940",
                "size":99,"kind":"semantic","owner":"0x0040B940"}]}
   ```
   `kind` becomes `semantic`; `name` keeps the existing region name with the `asm_`
   prefix replaced by `semantic_`. `symbol` is what the object defines — for a
   `__cdecl`/`extern "C"` function that is the plain name with MSVC's decoration; the
   probe accepts an exact object symbol or a unique substring, so `Foo_Bar_0040b940`
   works and is preferred. Include one entry per region you convert in that unit.
5. Probe the unit:
   ```sh
   python3 matching2/tools/matching/probe.py --source <src> \
     --proposal matching2/build/waves/results3/<AGENT>/<unit-stem>.json \
     --write-proposal /tmp/<AGENT>/<unit-stem>.resolved.json \
     --json --project matching2/msvc \
     --output matching2/build/waves/probe3/<AGENT> \
     > /tmp/<AGENT>/<unit-stem>.report.json
   python3 -c "import json;r=json.load(open('/tmp/<AGENT>/<unit-stem>.report.json'));print(r['exact'],[ (x['region'],x.get('detail') or x.get('first_difference')) for x in r['regions']])"
   ```
   The probe prints per-region `EXACT` / `DIFFERENT`, the first differing byte, the
   expected and actual instruction, and any relocation whose bound address is wrong.
   Exit status 1 means NOT EXACT.
6. Missing linker bindings (`__real@<bits>`, `__imp__Name@N`, `_data_<addr>` reported
   unbound in the relocation list) are not your bug: bind them with
   ```sh
   python3 matching2/tools/waves/bind_relocations.py --source <src> \
     --proposal matching2/build/waves/results3/<AGENT>/<unit-stem>.json --apply
   ```
   It only adds names to `matching2/msvc/regions.json`. Several agents may run it at
   once and one write can be lost; if a name is still unbound afterwards, run it
   again (up to 5 times) and re-probe. Report any name that will not stick.
7. Iterate until every region the probe lists for that unit is `EXACT`.

## Failure policy

If, after a genuine effort, the unit still reports NOT EXACT:

- Restore the pristine file: `cp matching2/build/waves/backup3/<src> matching2/msvc/<src>`
  (only that file) unless part of your earlier work on that file is already EXACT —
  in that case keep the file and simply report the region that resists.
- Delete the proposal JSON for regions you did not convert.
- Report the blocking difference precisely: address, differing byte offset,
  expected vs actual instruction, the C++ variant that came closest, and the
  smallest source change that would explain it. Another agent picks this up later,
  so make the finding actionable, not a summary.

## Report format (your final yield)

Prose, terse:

```
AGENT <id>
EXACT: src/a.cpp 0x40b940 (99B), src/a.cpp 0x412db0 (50B), ...
REVERTED: src/b.cpp (still differs at 0x41adf0 +0x12: expected 8b 45 08, actual 8b 4d 08)
BLOCKED: src/c.cpp 0x405620 — reason, closest variant, next idea
BINDINGS: names added, any that would not stick
```

The parent reconciles the manifest and runs the whole-image build; do not attempt it.
