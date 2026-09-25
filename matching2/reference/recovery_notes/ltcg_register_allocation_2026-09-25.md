# Register-allocation residuals are LTCG residuals

2026-09-25. Many regions were blocked with a "register allocation" residual even
though their entry uses the public ABI. Retail game code was compiled with `/GL`
and linked with `/LTCG`. Compiled that way, the unchanged source often allocates
exactly as retail does. The field comparison at `0x00417660`, for example, emits
`mov ecx,[ecx]; mov edx,[esp+4]` as a plain object. Under native LTCG it emits
retail's `mov edx,[ecx]; mov ecx,[esp+4]`.

## Recipe

1. The source must own only the region (`carve_region.py` if not).
2. Put the model in `.text$01accessor` with `__declspec(noinline)`.
3. Write a schema-1 driver whose `.text$03context` caller loops over the
   arguments.
4. When the entry must stay public, add the function's own symbol to `roots`.
   Otherwise LTCG may move `this` into EDX, as it did for a `0x0042A3E0`
   variant.
5. Bind external callees and data in `absolute_symbols`.

A region whose callee takes arguments in a private register belongs in the
cluster that already owns that callee. `0x00405F00` and `0x00413B50` joined
`bullet_manager_load_scripts_0040ae70` (which co-compiles `TextLog::Append`),
so their variadic logger call keeps `this` in ECX with caller cleanup.

Landed this way: `0x00404E90`, `0x00405280`, `0x00413050`, `0x00417660`,
`0x00418A50`, `0x004243E0`, `0x004245B0` (field comparisons);
`0x0044C080`, `0x0044C0B0` (strided byte sums, pointer walk plus
down-counter); `0x0042A870` (replay buffered bytes, six-byte record
difference); `0x00435280` (aligned string advance, where LTCG itself chooses
the EDX entry); `0x004198C0` (name/value lookup, key in EDX);
`0x00405F00`, `0x00413B50` (resource loaders).

## Near misses (all under native LTCG)

- `0x0042A3E0`: every instruction matches except block order. Retail places the
  null-scene `mov eax,1; ret` block after the epilogue that follows
  `mov eax,6`. Every source shape tried puts it before the epilogue.
- `0x004364F0` (memory-stream `Seek(offset, origin)`): a `switch` with `break`
  and a branchy absolute value matches except that retail cross-jumps the
  current-position success into the end-position store tail. The compiler
  duplicates that tail instead.
- `0x0043A700` (byte reverse): shifts for bytes 3 and 2 plus AH/AL for bytes 1
  and 0 match. Retail keeps a separate `push ecx` local where MSVC reuses the
  dead argument slot, even for `volatile` or union forms.
- `0x0043CB00` (removes two scheduler tasks under the lock): a
  `__forceinline` `RemoveLocked(scheduler, task)` matches except for the
  order of the two register moves before `call 0x00449F60`. Retail emits
  `mov ecx,esi; mov edx,edi`, and 40 retail call sites share that
  register-to-register order. Every C++ shape tried emits EDX first: plain
  fastcall, LTCG-private members, reversed parameters, and the same cluster
  as `Scheduler_Remove`. The same inlined pair blocks about 15 destroy
  functions (`0x00405F70`, `0x0042B570`, `0x00402440`, ...), so solving it
  would unlock a family.
- `0x0040C590`: the region also covers a separate 1-byte `ret` function at
  `0x0040C5A0` and has to be split before the comparison can land.
