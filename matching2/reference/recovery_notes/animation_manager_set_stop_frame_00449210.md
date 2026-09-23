# Animation manager stop-frame setter at `0x00449210`

## Evidence from the live Ghidra program

The open program is `th10.exe` (`/home/levzzz/Games/TH10 - Mountain of Faith/th10.exe`, x86 little-endian, image base `0x00400000`). Ghidra identifies `0x00449210..0x00449245` as one 54-byte function. Its instructions load the script id from `[ESP+4]`, call `0x004491C0`, and return with `ret 4`.

`get_xrefs_to(0x00449210)` reports one reference: the direct call at `0x004252F3` in `FUN_004250B0`. There are no other code or data references reported. The caller writes `1` to ESI at `0x004250CF`. The branch into the call block at `0x004252D0` comes from `0x004251E0`; the intervening path does not overwrite ESI. Thus SI is one at the only observed call site.

The setter asks the finder for the object matching the stack script id. If no object is found, it returns. Otherwise it writes SI to the object's 16-bit field at `+0x304`. It reads the flag at `+0x18` before writing that field; when the flag is nonzero it returns. When it is zero, it walks child-list entries from `+0x14`, writing the same 16-bit value to each entry's object at `+0x304`.

## Finder ABI and behavior

Ghidra disassembles `0x004491C0..0x00449208` as 73 bytes. The caller leaves the lookup context in EDX and pushes the script id. The finder copies `[ESP+4]` into ECX, walks the primary bucket at context offset `0x72DAD4`, then the secondary bucket at `0x72DADC`, and compares the id in the first word of each registered object. It returns the matching object in EAX or null and uses `ret 4`. This calling shape can be expressed with x86 `__fastcall`: a dummy/live ECX parameter, lookup context in EDX, and the id as the third (stack) parameter. The setter preserves the incoming ECX value when calling this helper; the helper overwrites ECX from its stack id before using it.

The finder has many direct callers throughout the program, including this setter. The setter itself has only the one call reference above. Ghidra presents ECX, EDX, and the stack word as the setter's three fastcall parameters; disassembly shows that ECX is only carried into the finder, EDX is the lookup context, the stack word is the script id, and SI is an additional private live-in.

## Source model and limits

The C++ source models the reachable behavior with stop frame `1`, because that is the value at the only observed caller. SI is an incoming private live-in, not a normal C++ parameter, so this source does not model arbitrary SI values or prove behavior for unobserved entry paths. The ordinary fastcall parameters retain the observed register/stack positions: an unused ECX live-in, context in EDX, and script id on the stack.

No build, probe, or test was run for this audit. Exact LTCG output for the new fastcall source is therefore unverified. An earlier source comment recorded a failed 65-byte standalone cdecl candidate against this 54-byte retail extent; that result does not validate the new signature or caller-specialized frame value.

## Symbol integration

The source's canonical C-linkage x86 fastcall symbol is
`@AnimationManager_SetStopFrame_00449210@12`. The manifest now marks the
54-byte entry semantic under that symbol and records the former ASM row as
`previous_record`. It also keeps the raw entry name
`_asm_AnimationManager_SetStopFrame_00449210` and the decorated legacy
spellings `_asm_AnimationManager_SetStopFrame_00449210@4` and
`@asm_AnimationManager_SetStopFrame_00449210@4` mapped to the same address.
The source provides linker fallbacks from all three legacy spellings to the
canonical implementation. The shared header still declares the raw entry as
an untyped cdecl symbol for existing assembly callers. The function has now
been added to `layout/ltcg/stop_at_frame_pair_0040c480.json` in
`.text$55stopframe`; the gap before it and the following synthetic
context/gap were adjusted to keep the listed spans contiguous. A static
JSON/range check confirms no overlap. Generated code and final address
placement remain unverified because no build was run.
