# `ScriptFileChunkContext::ParseAnimationChunk` at `0x0040D400`

This is a focused semantic model of the 239-byte retail entry. The source is
`matching2/msvc/src/unidentified/FUN_0040d400_0040d400.cpp`. The active manifest
marks the entry semantic and binds it to the C++ method
`ScriptFileChunkContext_0040d400::ParseAnimationChunk`; the old assembly row is
retained in `previous_record`.

## ABI and dispatch

The retail entry uses the ordinary x86 `__thiscall` shape: receiver in `ECX`, a
single chunk pointer at `[ESP+4]`, integer result in `EAX`, and `RET 4`. It has
no private entry-register inputs. The body saves and restores its used
nonvolatile registers.

At the time of the initial review, Ghidra did not define `0x0040D400` as a
function and reported no direct xrefs to that address. The raw bytes at the
manifest boundary match the recovered entry body. I added a function boundary
over the 239-byte span and applied the recovered `__thiscall` signature. The
caller and receiver are recoverable from the surrounding dispatch:

- Ghidra's decompilation of `0x00450220` calls the receiver's vtable slot at
  `+4` with the current script chunk table (`script + 0x24`).
- The table at `0x0046D0B4` contains `0x00450220`, `0x0040D400`, and
  `0x0040CD20` in its first three slots. This identifies `0x0040D400` as slot
  1 and `ScriptFileLoader::Load` at `0x0040CD20` as slot 2.
- `0x0040D400` calls `Recovery_LoadCachedResource` at `0x00447280` directly,
  and calls `TextLog::Append` at `0x0044B810` on resource-load failure. Ghidra
  confirms the resource helper's `__fastcall` inputs: index in `ECX`, cache in
  `EDX`, and resource name on the stack. The variadic TextLog member receives
  its object in `ECX` and the format pointer on the stack.
- For each ECLI body name, the routine calls receiver vtable slot `+8`, which
  is `ScriptFileLoader::Load`. That call uses `ECX=this`, one stack string
  argument, and the callee-cleaning `__thiscall` convention.

The source uses a local opaque-context type so this entry can be modeled
without altering the separate `ScriptFileLoader` declaration at `0x0040CD20`.
The vtable dispatch is expressed as a typed ordinary C++ `__thiscall` function
pointer.

## Behavior

The routine returns zero for a non-`ANIM` chunk. For an `ANIM` chunk, it reads
the resource count at `+4` and walks the NUL-terminated names beginning at
`+8`. Each name is loaded through `0x00447280` with resource index `i + 9` and
the cache pointer from `0x00491C10`. The returned pointer, including null, is
written to the resource table at the pointer stored in `0x00477704`, offset
`0x34 + 4*i`. If a load fails, the routine appends the fixed message at
`0x0046CB68` to the TextLog at `0x00474F70` and returns `-1`.

After the resource names, it advances to the next four-byte offset relative to
the chunk start. If that location is not an `ECLI` chunk, it returns zero. For
an `ECLI` chunk, the count at `+4` controls a second walk of NUL-terminated
script names beginning at `+8`; each is passed to vtable slot `+8` (`Load`),
and the returned load status is ignored. The routine then returns zero.

Retail performs no chunk-length or string-termination checks, so the C++ model
preserves the same unchecked reads and cursor walks. Apart from resource-table
stores, the visible side effects come from the resource loader, TextLog, and
the virtual `Load` calls.

## Evidence and limits

The old assembly body and Ghidra's raw memory at `0x0040D400` agree on the
`ANIM` test, per-resource loop, failure return, alignment, `ECLI` test, and
virtual calls. Ghidra's `0x00450220` decompilation establishes the vtable
caller and argument pointer; the raw table at `0x0046D0B4` identifies slots 1
and 2. The vtable table and the newly recognized function boundary provide the
needed entry and caller evidence for this model.

## Model status

The active manifest now marks `0x0040D400` as semantic and preserves its former
assembly row in `previous_record`. The region resolves to the C++ member symbol
for `ParseAnimationChunk`; the existing `_asm_FUN_0040d400_0040d400` absolute
alias remains available for the raw vtable entry. Ghidra now has a function
boundary over the 239-byte region and the recovered `__thiscall` prototype. The
ABI and behavior are supported by the entry bytes, vtable table, caller/callee
analysis, and the already semantic C++ implementations at `0x00447280`,
`0x0044B810`, and `0x0040CD20`. Retail byte identity and exact compiler output
remain unverified. No build, probe, or test was run.
