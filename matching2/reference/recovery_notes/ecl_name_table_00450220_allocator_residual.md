# 0x00450220 — ECL name table: recovered structure, allocator residual

2026-09-15. `ScriptFileLoader::Parse` (589 bytes, `src/script/ecl_name_table.cpp`)
was attacked from the wave-8 note that had no measurement. The whole source
structure is now recovered and **the first 20 instructions reproduce retail
byte for byte**; the residual is MSVC's stack/register home assignment, not the
algorithm, the types or the statement order. Nothing was landed: the region is
still `asm_` in the manifest and the whole executable still passes the
487,936-byte hash gate.

## What the function is

`int __thiscall ScriptFileLoader::Parse(char* data)` — `this` in ECX, one stack
argument, `ret 4`. The manifest's `load_archive_file` LTCG cluster already
names the retail symbol `?Parse@ScriptFileLoader@@QAEHPAD@Z`, and the two
function-pointer tables at `0x46D0B4` (`Parse`, `0x40D400`, `Load`) and
`0x46D0F0` (`Parse`, `0x40C810`) confirm the name; `0x40D400` tests the
`'ANIM'` magic on the chunk table `Parse` passes it (`script + 0x24`), so the
virtual/dispatch slot 1 is the object-chunk loader. Because the address escapes
through those tables, retail's ABI is the public one — the native-LTCG route
cannot change it (see below).

The SCPT container (`default.ecl`, `stage01.ecl` in `extracted/th10_dat/`):
`+0x00 'SCPT'`, `+0x04` version `1`, `+0x06` chunk-table length, `+0x08` header
size `0x24`, `+0x10` sub count; the sub offset dwords start at
`0x24 + *(unsigned short*)(data+6)` and the sub names follow that table.
`Parse` registers the file, appends its sub names to the sorted
`{const char* name; int body;}` table (`file_count` at `+0x04`, `name_count` at
`+0x08`, `files[32]` at `+0x0C`, `entries` at `+0x8C`), filling it directly on
the first registration and merging each later name into sorted position.

## The source shape that reproduces retail's control flow

- **Two separate header validations, not one `&&`**: the test block is
  `jne fail; cmp word; je body` with the failure block *inline* between them
  (`mov [eax],0; or eax,-1; pop ebx; add esp,0x10; ret 4`). A single
  `if (magic != X || version != 1)` produces `jne`/`jne` to a failure block
  placed after the body (measured: 51 instruction-prefix bytes differ, the
  fail block moves). Splitting the checks (`if (magic != ...) { ...; return -1; }`
  followed by `if (version != 1) { ...; return -1; }`) makes MSVC tail-merge the
  two identical failure blocks and emit retail's layout exactly.
- Every use of the current script goes through `files[file_count]` (an in-class
  `Current()` accessor produces the same plain load chain), which is why retail
  re-loads `[ebx+4]` and `[ebx+edx*4+0Ch]` several times and reloads the script
  pointer (`mov eax,[eax]`) after the validation.
- Both loops walk the offsets and names cursors (`*cursor` + `++cursor` in the
  source): a variant that indexes (`offsets[index]`) does not reproduce retail's
  memory read-modify-write cursor.
- The search is the intrinsic-inline `strcmp` (2-byte unrolled, `sbb eax,eax;
  sbb eax,-1`) and the name length is the intrinsic-inline `strlen`
  (`sub eax,edx; lea ecx,[edi+eax+1]`); both come for free from `/Oi` with
  `<string.h>`.

## Measured blocker: MSVC's home assignment

Retail's frame is exactly `0x10` and holds `names` (`[esp+0x10]`), `merged`
(`[esp+0x14]`), the search walker (`[esp+0x18]`) and the merge index
(`[esp+0x1C]`); the offsets cursor lives in the argument home (`[esp+0x24]`,
the `data` parameter's slot, free after the array store). Ninety candidate
variants were compiled through `probe.py`'s own compile path and none of the
plain-`/O2` shapes lands both facts at once:

| variant family | extent | frame | note |
| --- | ---: | --- | --- |
| indexed cursors, single `names` | 549 | `0xC` | search walker in ECX, offsets indexed |
| walking offsets cursor | 547 | `0xC` | search walker memory-homed, offsets in a register |
| 120 prologue statement permutations | 523–539 | `0xC` | frame invariant to statement order |
| extra live cursor / base pointer | 577 | `0x10` | frame right, cursors walked, walker still in a register |
| `unsigned char` live across the merge loop | 589 | `0x10` | **size, frame and all five slots match retail** |

The last row is the diagnostic that matters: adding one more live value to the
merge loop — or reserving a byte register there — makes MSVC home the search
walker in memory and walk the offsets cursor in the argument home, i.e. it
reproduces retail exactly, including the extent. But that variable has no
faithful source counterpart (the same effect could not be reproduced with
function-scope counters, a second index, or a struct field), so it cannot be
landed as a byte shim. Two further retail-only instructions are equally
unexplained: a redundant `test ebp,ebp; je` around the `free` call (every
`if (old != 0) { free(old); }` spelling is folded away by the optimizer) and the
`mov edx,[esp+0x14]` re-load of `merged` after that call.

Instruction-sequence similarity of the closest honest variant is 0.78 with a
29-instruction identical run inside the search loop; differing bytes are
dominated by the address shift from the one-slot frame difference
(`tools/waves/shape.py` reports the register-normalised figure).

## LTCG route measured, does not apply

The native-LTCG cluster path was exercised end to end for this region
(provisional schema-1 cluster: gap `0x401000..0x450220`, function at
`0x450220`, synthetic caller, `entry_malloc_00452706`/`entry_free_00452422`
bound as absolute `relative_code` symbols):

- unrooted `/GL` + `/LTCG`: 546 bytes, `sub esp,0x10`, but LINK 7.1 moves
  `this` to EBX (private convention) — retail's `mov ebx,ecx` prologue is lost;
- rooted (`/INCLUDE:` the function, which forces the public ECX convention):
  byte-identical to the plain `/O2` body (549 bytes).

So for a function whose ABI is already the C++ default, the LTCG scope changes
nothing; the lever documented in `wave8_large_region_blockers.md` applies to
regions whose *entry register* is not expressible, not to allocator residuals.

A second configuration rules out the remaining variant of that idea: a schema-2
batch holding the *real* caller, `ScriptFileLoader::Load` at `0x0040CD20`
(recovered C++, 95 bytes) with `Parse` as its declared internal callee at
`0x0040CD6A`, both compiled `/GL` into one native `/LTCG` link (gaps
`0x401000..0x40CD20` and `0x40CD7F..0x450220`, `_Archive_LoadFile@12` and
`_data_00497c38` bound absolutely). Unrooted, `Parse` is again 546 bytes with
`this` moved to EBX — and `Load` shrinks to 94 bytes. Rooting `Parse` restores
`Load` to its exact 95 bytes and leaves `Parse` at 549, i.e. byte-identical to
the plain `/O2` body. Caller visibility, scope size and rooting therefore do not
move this function's home assignment; only the source shape does.

## Next experiments

1. Find the *faithful* source construct that reserves a byte register (or one
   more live value) across the merge loop. Retail's own byte-register evidence
   is `cl` used only inside the two inline loops, and its frame has no spare
   slot, so the pressure is a side effect of a value this reconstruction does
   not model. Candidates not yet tried: a `char`/`bool`-typed loop-carried flag
   that is *read* in the merge body, and a `unsigned short` local for the header
   counters.
2. Explain the redundant `test ebp,ebp; je` around `free`: it implies the source
   tests the old table pointer twice with an intervening call, which MSVC 13.10
   only keeps when it cannot prove the second test redundant.
3. If a legitimate shape is found, the region is one `probe.py --proposal` run
   away from landing: `symbol ?Parse@ScriptFileLoader@@QAEHPAD@Z`,
   `src/script/ecl_name_table.cpp`, `0x00450220`, 589 bytes, section
   `.text$02names`.
