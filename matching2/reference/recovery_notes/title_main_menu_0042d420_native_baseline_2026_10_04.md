# Complete title main-menu model, 0x42D420

The complete state machine is now readable C++ in
`reference/semantic_candidates/ending_screen_0042d300/main_menu.cpp`. Live
Ghidra decompilation was checked against `src/game/title_main_menu.cpp` for
all hidden frame, index, sound, and cursor arguments. This is an unselected
compiler baseline; the 1280-byte retail owner remains assembly.

The model covers all five phases and eight selections, initialization of the
8-item cursor, disabling item 1 without play records, flag-based initial
selection, lookup/installation of slots 88 and 0, frame propagation, current
and repeated navigation input, selection-change sound 12, cancellation sound
11, confirmation sound 10, direct cancellation while already on exit, all
phase-4 timer-owner transitions, animation retirement, difficulty save/restore
at room+0x58F0, and the bounded-counter selection update at 0x40AD20. Phase 0
intentionally falls through to the first timer check. No extra bounds guards
or new menu behavior were introduced.

Three controls compile with and without /GL and link with MSVC 13.10.6030:

| Control | Dispatcher | Ending | Main menu | History helper |
| --- | ---: | ---: | ---: | ---: |
| Complete main menu / original history declaration | 1092 | 284 | 1272 | opaque |
| Correct cursor history receiver | 1092 | 284 | 1272 | opaque |
| Complete history body visible | 1092 | 284 | 1272 | 66 |

All contributions include complete generated switch tables. Retail owned
extents are dispatcher1128, ending288, and main-menu1280. Matching extent or
an eight-byte extent difference does not prove an eight-byte content mismatch.
These controls do not claim byte equality at their experimental addresses.
The ending handler retains its incoming EBX contract in the expanded graph,
but its persistent zero in ESI remains, so adding the sibling did not resolve
that scheduling/register discrepancy.

Disassembly establishes that 0x44BE20 is `MenuCursor::PushSelection`, not the
apparent no-argument score-history operation. The main-menu call explicitly
passes its cursor in EAX; the complete body saves selection and item count,
increments/clamps history depth, and clears the disabled-item count. The title
dispatcher uses the same helper. Its candidate was corrected, and the production
adapter cluster's unselected dispatcher now uses that member with the corrected
external symbol binding. The selected seven-byte adapter probe remains EXACT.
No new semantic region is claimed by this correction.

Reproduce from the repository root:

```
PYTHONPATH=. python3 matching2/reference/semantic_candidates/ending_screen_0042d300/probe_baseline.py full_script_menu_history
PYTHONPATH=. python3 matching2/reference/semantic_candidates/ending_screen_0042d300/probe_baseline.py full_script_menu_push
```

`full_script_menu` now uses the corrected candidate as well; the original
pre-correction source snapshot is retained in its archived experiment directory.
`main_menu_controls.json` records these measured builds. Commands, native
images/maps, disassembly and source snapshots are archived under
`build/experiments/ending_screen_caller_full_script_menu{,_history,_push}_2026_10_04`.

The next useful graph extension is the complete progress-record, stop-and-run,
and secondary slot-dispatch leaves. These are still opaque logical declarations
in this model and expose only public source contracts, whereas retail uses
private register inputs. Recover their actual source visibility before
attempting further count/store permutations. Preserve the exact production
adapter and the original main-menu ownership until an unmasked probe passes.

Production verification after the history-call correction: both full builds
pass. Independent cmp confirms all 487936 bytes of the exact executable.
Exact C++ and remaining assembly counts are unchanged (2192 and 126 regions).

## Visible progress and animation leaves

The next executed control replaces the logical stop/run and secondary-dispatch
names with their real typed APIs, and compiles the complete maintained
`progress.cpp`, `animation_manager_set_stop_frame_and_run_00449250.cpp`,
`game_state_dispatch_animation_slot_secondary_0042c750.cpp`, and
`animation_manager_find_004491c0.cpp`. The caller's progress view now includes
the actual six record bytes at +0x1D888. Full bodies are retained, not fabricated
stubs. The animation interpreter remains the genuine imported RET4 entry.

The visible leaves have contributions of 69 (progress), 76 (stop/run), and 27
(secondary dispatch) bytes. Disassembly confirms progress receives EAX,
stop/run receives frame DI and context EDX with its record ID on the stack, and
secondary dispatch receives state EAX / slot ECX. This restores the private
contracts on these edges. The main handler still receives a stack room in EBP,
where retail receives EBX; its 1268-byte contribution remains nonexact.

Four bounded controls were executed:

| Variant | Complete main-menu contribution | Result |
| --- | ---: | --- |
| Full visible leaves, free function | 1268 | Stack room / EBP |
| Same state machine as TitleRuntime member | 1268 | Identical body SHA256 |
| Global optimization disabled for this handler | 1632 | EBP frame, 0x34 local bytes |
| Explicit named cursor pointer | 1264 | Stack room / EBP; cursor EBX |

The member model does not change the generated handler, so receiver syntax
alone cannot resolve this private register contract. Disabling global
optimization introduces a conventional frame and is not a viable matching
configuration. Naming the cursor changes code generation and removes the
entry's persistent constant-two load, but still does not restore the retail
room or cursor registers. The dispatcher and ending contributions remain
1092 and 284 bytes in all four runs. No ownership or production code changed.

Reproduction:

```
PYTHONPATH=. python3 matching2/reference/semantic_candidates/ending_screen_0042d300/probe_baseline.py full_script_menu_leaves
PYTHONPATH=. python3 matching2/reference/semantic_candidates/ending_screen_0042d300/probe_baseline.py full_script_menu_member
PYTHONPATH=. python3 matching2/reference/semantic_candidates/ending_screen_0042d300/probe_baseline.py full_script_menu_no_global
PYTHONPATH=. python3 matching2/reference/semantic_candidates/ending_screen_0042d300/probe_baseline.py full_script_menu_cursor
```

Each compiles with and without /GL and links under the original toolkit.
`main_menu_leaf_controls.json` records full extents and body hashes. Complete
commands, objects, native maps/images, disassembly and source snapshots are
under `build/experiments/ending_screen_caller_<variant>_2026_10_04`.
These images are not executed or promoted as byte-exact application bodies.
Next investigate the room/cursor lifetime and selection-clamping source with
the now-visible real leaves; don't repeat the opaque calls, member conversion,
or disabled-global-optimization controls.

## Clamp, shared exit, and allocator tracing

Two more complete-body controls were executed with all real leaves visible.
The first uses the maintained bounded-counter clamp algorithm inline, including
its unsigned intermediate and signed comparisons, instead of the manually
expanded setter. It removes the persistent constant-two load at entry. The
second replaces the temporary exit boolean with the retail control flow: an
already-selected exit jumps directly into the confirmation switch's shared
exit case, bypassing the frame-six operation. Both retain the stack room / EBP
contract and a 1268-byte complete contribution; their body hashes are recorded
in `main_menu_clamp_controls.json`. The ending/dispatcher remain 284/1092.
No production ownership or application implementation changed.

```
PYTHONPATH=. python3 matching2/reference/semantic_candidates/ending_screen_0042d300/probe_baseline.py full_script_menu_clamp
PYTHONPATH=. python3 matching2/reference/semantic_candidates/ending_screen_0042d300/probe_baseline.py full_script_menu_direct_exit
```

The original linker was then run under winedbg/gdb with hardware breakpoints at
the previously established c2.dll Spillcosts (0x107A98EE) and ChoosePhysReg
(0x107AAC16) locations. `trace_allocation.py` captures candidate IDs, priorities,
physical choices, and best-effort symbol strings. The process exited normally;
the trace contains 2279 spill-cost observations and 485 physical choices.
Independent PE extraction confirms that all 14332 `.text` bytes are identical
between traced and ordinary links. No compiler-produced bytes were patched.

The candidate symbols retained by this /GL graph do not expose the source
room/cursor names to this trace. Therefore no particular priority or choice
is yet attributed to those variables, and the trace is not a diagnosis of the
room-register mismatch. Mapping the code-generation procedure/symbol identities
is still needed before drawing that conclusion. This limitation prevents
unsupported register-priority explanations; changing root or source receiver
syntax has already been measured without resolving it.

Commands, images/maps, disassembly, source snapshots and the full trace are
archived under `build/experiments/ending_screen_caller_full_script_menu_clamp_2026_10_04`
and the analogous `direct_exit` directory. The trace summary is also retained
beside the candidate as `allocation_trace_summary.json`.
