# Execution failures in accepted equivalent replacements, 2026-10-14

The four failing C++ replacements have been repaired and re-registered.
The initial assembly rollback was a diagnostic baseline, not the final
implementation. The default build is again intended to use all 40 C++
replacement entries. No original game executable, save, replay, or configuration
was changed during the investigation. Wine runs use copied game files under
`matching2/build/behavior/game`, a separate prefix, and Xvfb display `:91`.

## Item update, 0x0041AFD0

`matching2/tests/item_update_shipped_differential.py` reuses the historical
473-case fixture, inserts the **installed, relocated item body** into a retail
image, and executes real retail collaborators. Retail against itself passes
473/473. The original default replacement fails 94 cases.

The replacement passes the SetPolar receiver in EAX at its seeking call sites;
the installed retail helper at 0x0041BEB0 receives it in ECX. The helper thus
writes a different object and leaves the intended velocity untouched. Testing
against the separately linked context helper concealed this ABI mismatch.
Targeted state-2 cases also expose planar/Z rounding and offscreen-boundary
differences. This evidence does not establish the cause of every visual item
symptom reported during gameplay.

A local C++ correction trial retaining SetPolar's public thiscall ABI and the
constructed-vector rounding boundaries fit in 2304 bytes, but failed 22 delayed
activation cases: its call to Entity_StartScript no longer supplied the entity
in ESI. That trial was not retained in maintained sources or shipped. Matching
one private convention can change others; every emitted caller must be tested
with the installed callees before registration.

The tester compares return/stack behavior, preserved registers, x87 balance,
item records, player/movement/resource memory, writable image data, score/HUD,
sound and animation observations. VM ticking, PowerChanged, allocation and
terminal conversion retain the fixture's scripted boundaries. It does not
prove full-game behavior or exercise interactions with all other replacements.

## Manager teardown, 0x00417C80

Retail ran an attract-mode demo in the isolated Wine environment. Interrupting
the original default build's demo reproduced a crash:

```
wine: Unhandled exception 0x80000003 ... at address 004180D1
```

Retail ends with `add esp,0x10; ret 4` at 0x004180CB. The installed replacement
ends with `add esp,0x10` at 0x004180CE, then falls into INT3 padding at
0x004180D1. Its layout explicitly records retail `ret 0x4` against an empty
model sequence as `code-shape`. The extraction extent was insufficient; the
historical note's claim of a harmless shorter body was incorrect.

## Options-label refresh and hint-save

A disassembly audit of the cached replacement bodies found:

* Options-label refresh, 0x0042E5A0: the extracted code ends with a partial
  `E9` jump at offset 3997. The replacement also has `ret 4` where the retail
  return form is `ret`.
* Hint-save, 0x0041A200: the extracted code ends with a partial `83`
  instruction at offset 2246.

Neither body is safe to install on the strength of its previous classification.

## Gate changes and validation

The equivalence gate now rejects differing return forms/stack cleanup even
when labeled structural, and rejects incomplete/invalid decoded instructions.
Identical return sites may still merge. Unit regressions cover the missing
return, changed cleanup, valid return merging, and cut instruction cases.

These rules do not prove ABI or behavioral equivalence. `make behavior-check`
adds the bounded shipped-item check using an interpreter with Unicorn. Fresh
registration of the item model requires executing the new bytes against the
actual callees, not citing the historical candidate's passing tests.

Local evidence is under `matching2/build/behavior/`: `th10-before.exe`,
`item-update-before.json`, `item-update-control.json`, `candidate.log`, and
the build/runtime screenshots and logs. These are generated diagnostic
artifacts, not maintained source files.

## Diagnostic baseline before the C++ repair

The fresh default build succeeds with four assembly regions (9671 bytes) and
36 registered equivalent entries. Its complete executable is byte-identical
to the four-region-restored diagnostic executable used in the runtime tests:

```
SHA-256: 3b914bf455f4e237fdb3d78b119286217810c1b4595a68aca4f0d039855df4e3
```

The final executable passes all 473 item cases; the original fails 94. All 25
equivalence unit tests pass. Runtime smoke tests pass demo interruption,
normal stage quit to menu, and 120 seconds of idle demos with two observed
natural returns to the menu. Full replay synchronization remains unverified.
`item-update-after.json`, `extraction-audit.json`, `summary.json`, and the
`restored-*.png` screenshots record these checks.

A separate copy is installed at
`/home/levzzz/Games/TH10 - Mountain of Faith/th10-restored.exe`.
The original retail and previously copied equivalent executables were not
overwritten. The isolated Wine server and Xvfb process were stopped afterward.

## C++ repair

Item update uses constructed-vector integration and a stored-Y read to retain
the retail rounding boundaries. Its context link preserves SetPolar's public
thiscall ABI and makes the initializer public so StartScript retains its entity
in ESI. The emitted body occupies 2312 bytes and passes 473/473 comparisons
against real retail callees. The context exports are not installed in the game.

Teardown reads the final flags through their dword view, shortening the
emitted epilogue enough to include its return in the fixed region. Its new
comparison has 291/309 identical instructions and no missing return.

Options-label refresh now shares its genuine name with its real caller. Its
context suppresses the historical stand-in, links the complete resource
configuration and registration models, and stops rooting the target as an
independently callable public entry. This derives the retail EDI receiver,
plain return, and correct hidden helper arguments. It matches 1203/1204 retail
instructions; the two hunks move the unchanged manager load before pure
registration/attenuation work.

Hint-save already had a complete C++ body. Extraction now stops before the
next function's map symbol instead of copying a partial WriteShared body.
That body occupies 2240 bytes; its remaining region bytes are trap padding.

All four original registration entries have been restored; the diagnostic
restored executable was never the deliverable.

## Replay submenu, 0x004236F0

Game-over confirmation jumped to 0xCCCCCCCC: the layout's `code_bytes` (3256)
left four bytes for an eight-entry jump table, so the packer kept one entry and
filled seven with CC. The retail table starts at 0x0042438C; `code_bytes` is
now 3228. `matching2/tests/replay_submenu_shipped_differential.py` covers it.

## Projectile command Tick, 0x00406D90

Found by the replay sync check: the default build faulted in the script loader
~5,766 frames into replay `th10_05`. The model passed the script to the
installed StartScript 0x00404F30 in EDI instead of EAX; see the 2026-10-14
section of `projectile_command_runtime_00406d90_2026_10_13.md`.

## Current validation

`make abi-check` checks every model's register arguments into retail code;
`make behavior-check` adds the two Unicorn differentials (item update 473/473,
replay submenu 48/48). `matching2/tests/replay_sync/` found three full replays
identical to retail frame for frame (Normal all clear, Easy all clear, Extra
clear). Live checks: stage quit and demo interruption return to the title,
options volume changes apply, game over reaches Continue / Save replay / Quit
and Quit returns to the title.
