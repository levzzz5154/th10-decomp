# EAX-entry cluster follow-up: 0x0040CDC0, 0x00418AC0, 0x00421D00, 0x0043A490, 0x0044C620

2026-09-17. Eight small regions whose retail entry keeps the object in EAX were
recovered as schema-1 native-LTCG clusters using the established recipe. Each
was verified EXACT by the per-unit probe and the whole-image build is
byte-exact across 487,936 bytes.

| region | bytes | retail shape | cluster |
|---|---:|---|---|
| `0x0040CDC0` | 23 | object in EAX, value on stack, conditional store, `RET 4` | `enemy_slot_conditional_set_0040cdc0` |
| `0x00418AC0` | 15 | object in EAX, `+0x10 = 0`, `+0x0C = 1`, plain `RET` | `state_reset_pair_00418ac0` |
| `0x00421D00` | 21 | object in EAX, `+0x38C = -2`, `+0x390 = 0`, plain `RET` | `replay_marker_clear_00421d00` |
| `0x0043A490` | 14 | object in EAX, `+0x00 = 0`, `+0x04 = 0`, plain `RET` | `sound_pair_clear_0043a490` |
| `0x0044C620` | 14 | object in EAX, `+0x04 = 0`, `+0x00 = 1.0f`, plain `RET` | `camera_pair_reset_0044c620` |
| `0x00421DE0` | 11 | object in EAX, `+0x3ADA64 = 0`, plain `RET` | `replay_slot_clear_a_00421de0` |
| `0x00421DF0` | 11 | object in EAX, `+0x3ADA70 = 0`, plain `RET` | `replay_slot_clear_b_00421df0` |
| `0x004367E0` | 11 | object in EAX, value in ECX, `+0x04 = 0`, `+0x08 = value`, plain `RET` | `resource_slot_init_004367e0` |

## Evidence

IDA prototypes (`id a/th10.exe.c`): `sub_40CDC0`, `sub_418AC0`, `sub_421D00`,
`sub_43A490`, and `sub_44C620` are all `__usercall ... @<eax>` with the object
in `result@<eax>`; `sub_40CDC0` additionally takes the stored value as an
ordinary stack parameter and cleans it with `RET 4`. None has a direct
`E8` caller or a 4-byte address reference anywhere in the image (verified by
scanning every section for the encoded target and for `call rel32` hits), so
the entry convention is enforced by the compiler context, exactly as for the
accessor family recovered before them.

The `0x0040CDC0` object layout is shared with the recovered
`EnemyState_0040cde0`: enemy pointer at `+0x3504`, mirror flag at `+0x3508`.
The store is conditional on the flag being clear, which compiles to retail's
`mov cl,[eax+3508h]; test cl,cl; jne ...; mov ecx,[esp+4];
mov [eax+3504h],ecx; ret 4` once the object is forced into EAX.

## Recipe notes (traps that cost probe cycles)

1. **The context symbol's decoration is not guessable.** A synthetic
   `int __stdcall Ctx(T** items, int count, void* value)` mangles to
   `?Ctx@@YGHPAPAUT@@HPAX@Z`, not `...PAX1@Z` (MSVC back-references apply to
   *types*, and `H` for `int` comes first). Compile the driver once without
   `/GL` and read the symbol with `i686-w64-mingw32-objdump -t`, per
   `briefs/CLUSTER.md` trap 3. The linker error for a wrong guess is
   `LNK2001 unresolved external symbol` on the `?`-name.
2. **`__declspec(noinline)` on the member is required.** Without it, `/LTCG`
   inlines the setter into the context loop, the `.text$01*` contribution
   collapses to zero length, and the image entry check fails with
   `native cluster image base or entry address differs`. The MAP then shows
   only the context in `.text$03context` and nothing in the function section.
3. **Head-gap size is `function_address - 0x401000`,** not a copy of another
   cluster's number. Reusing the neighbour's 48,608 for a function at
   `0x0040CDC0` overlaps the function extent and the loader rejects the layout
   with `cluster code/context/layout extents overlap or overflow`.
4. **Probe once, then read the context size from the generated
   `cluster.map`** (`.text$03context` length column) and the context address
   from the same file; put both in the layout and probe again. For
   `enemy_slot_conditional_set_0040cdc0` the map reports the context at
   `0x0040CDE0` with 0x27 bytes.
5. **Struct fields must be written in ascending offset order** for the
   padding-typedef arithmetic to be valid; a descending pair triggers
   `error C2118: negative subscript` on the size-check typedef.

## Accounting

Manifest SHA-256 after promotion:
`24b7a0ab98c689ed0be2b569ed2367a538b40a2b421c35ae1bb44a980d45b215`.
Ordinary C++: 475 regions / 33,257 bytes. Each promoted region keeps a
`previous_record` asm entry, so the promotion is reversible without archaeology.

Two further decoration data points for the recipe (both resolved by compiling
the driver without `/GL` and reading `objdump -t`): a context of
`(T**, int, int)` mangles `...@@HH@Z` (each scalar parameter is spelled), and
the context extent for the 3-argument store loop is 0x24 — again read from
`cluster.map`. The `0x004367E0` size-check typedef must match the *declared*
struct extent (0x0C for three ints), not any retail layout guess; a wrong
assert fails the unit with `error C2118: negative subscript` before the probe
can even place the function.
