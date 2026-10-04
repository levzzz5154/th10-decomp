# Title worker body 0x0041F990 and effect buffers 0x0043DB60 — exact

2026-10-04. Both regions are ordinary C++ in the native-LTCG cluster
`layout/ltcg/title_assets_0041f990.json` (299 + 295 bytes). `make` and
`make EXACT=1` pass.

Sources: `src/game/title_assets.cpp`, `src/platform/sound_effect_buffers.cpp`,
`include/th10/app/supervisor.hpp` (new), context
`layout/ltcg/title_assets_0041f990_context.cpp`, anchors under
`layout/ltcg/title_assets_dependencies/`.

## What the earlier candidates were missing

1. **Natural source for 0x0043DB60.** The 300-byte candidate (manager in EDI,
   -1 held in EBX) came from twelve explicit `-1` stores and volatile globals.
   A plain `for (slot < 12)` loop, an `unsigned` effect index and non-volatile
   data give the EBX receiver, `or eax,-1` re-materialised after the call and
   the late `push edi`.

2. **The supervisor block is one address-taken object.** With the music volume
   as a lone `extern`, c2 forwards the stored value and emits
   `fild [esp+N]`; with the next-state word as a lone `extern`, c2 sinks
   `mov [0x491FB8],3` below the task-flag update (source order and `volatile`
   make no difference). Declared as members of `Supervisor` at 0x00491C00,
   with the block's address escaping in the context, both come out as retail:
   `fild [ebx+0x52C4]` and the store ahead of `mov esi,[esi+8]`. The same
   change moves `mov [esi+0x520C],eax` ahead of the window-handle load in the
   0x0043D690 anchor.

3. **The unread `mov [esp+4],ecx`.** 0x0041F990 keeps its ECX argument alive
   for `owner->LoadStartupResources()` (0x0041F8D0), whose body ignores the
   receiver. c2 drops the argument at the call after the allocator has homed
   it. A local struct or an address-taken parameter does not survive
   optimisation; the member call does. 0x0041F8D0 stays owned by its existing
   cluster as a free function; the anchor here is the same statements as a
   member.

4. **Failure block position.** The three failing checks sit in an inlined
   helper returning -1, so the `next_state = 3` block follows the third check
   (the `goto` spelling gives identical bytes; nested `if`s put it elsewhere).

## Still open nearby

0x0043D690 (`LaunchMusic`, anchor, 241 bytes): five instructions differ, all
one swap of ECX/EDX between the `device_owner` argument temporary and the
result temporary. Callee visibility (the complete 0x0044C8F0 model) does not
change it.
