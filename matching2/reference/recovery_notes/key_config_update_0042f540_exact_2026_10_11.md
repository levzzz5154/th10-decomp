# Key configuration screen 0x0042F540: exact (2026-10-11)

`src/game/menu_flow_updates.cpp`, cluster
`layout/ltcg/key_config_update_0042f540.json`. 880 bytes (859 of code, one
padding byte, the five-entry phase table). This replaces the earlier
"private ABI blocker" note: the room arrives in EBX by itself once the title
dispatcher stand-in and the real leaves are in one whole-program link.

## What each residual turned out to be

| residual in the first model | cause | source/context change |
| --- | --- | --- |
| room loaded from the stack into EBP, cursor pointer in EBX, `ret 4` | the two key-state words were lone externs, so their byte loads were register candidates across the `Advance` calls; restricted to EBX they added 400 to EBX in `ChoosePhysReg` and the room took EBP, which the private convention never uses for a parameter | the key state at 0x00474E30 is an object whose address is taken in the context |
| three binding loads grouped before the stores | lone externs cannot alias the room | configuration 0x00474E88 and its copy 0x00491D4C are address-taken objects (18 bytes, nine words: the copy is four dwords and a word) |
| `push esi` at entry instead of after the phase check | a `return 1` inside a phase owns its return block | every path leaves through the final `return 1`; phase 2 is an inlined `void` helper |
| context pointer in ECX for 0x00449250 | the callee's own callee (`Find`) was not visible | real `AnimationManager::Find` body in the link |
| `mov eax,[slot]; mov edx,[ctx]; push eax` | slot id copied into a local | id passed straight from the slot array |
| `cmp ecx,5; jge` | | `selection <= 4` as written in retail |
| folded item-count clamp | | inlined select-and-clamp helper on the cursor |
| `mov eax,[pressed]; test al,0xa ... test eax,0x1001` | both tests read one symbol and form one two-reference lifetime | cancel test reads the key-state member, confirm test reads the lone word `data_00474e36` |

The last row is the only one without a source-level explanation. Retail
shares the load in 0x00430320 (cancel acts at once) and does not in the
handlers where a cursor comparison sits between the two tests (0x0042D420,
0x0042D920, 0x0042F540, 0x00431EE0, 0x00432CB0, 0x00433570). In c2 the
decision is `SpillObvious` (0x107A9D71): a lifetime with fewer than two
references and no benefit is spilled, one with two references stays a
candidate. A call in the middle block splits the lifetime; nothing that
emits no code was found to do it (member/lone declarations of one type,
16/32-bit types, pointer helpers, typed helper results, split bit tests).

## Cluster

Cloned from `ending_screen_0042d300.json` (same dispatcher, same slot and
timer leaves). Additions:

- the dispatcher is its own translation unit, because it declares
  `data_00474e30` as a lone word and the screen declares the object;
- `key_config_anchors.cpp` and `animation_run_anchors.cpp` relocate the
  maintained sources with `#define code_seg(name) code_seg(".text$<addr>_fn")`;
- the link now holds three views of the lookup at 0x004491C0; the two extra
  ones are laid out in unused bytes at 0x004492F0 and 0x00449340 (anchors are
  layout only, their addresses matter only to their direct callers);
- the context function takes the address of the three objects.

## Tools

`ChoosePhysReg` and `Spillcosts` can be traced in a real LTCG link by
replaying the link command under `trace_target_globals_link.py`; dumping the
candidate hash table at 0x108827B0 at the first choice shows which
candidates are down to one register (+0x24 reference count, +0x40 benefit).
