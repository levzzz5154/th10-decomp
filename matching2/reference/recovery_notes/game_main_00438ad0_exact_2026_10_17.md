# GameMain 0x00438AD0: byte-exact (2026-10-17)

Follows `game_main_00438ad0_equivalent_2026_10_12.md`. The 1,389-byte WinMain
is now selected by the LTCG cluster
`msvc/build_support/layout/ltcg/game_main.json` from
`src/core/main/game_main.cpp`; the assembly region, the equivalent layout and
its context copies are gone. `make EXACT=1` is unchanged (`2f14760b6fbbf575`).

## What the cluster reproduces

The equivalent rig compiled the model with fifteen recovered callee sources so
the whole-program link derived their private register conventions. The cluster
keeps that shape:

- fourteen callee bodies are plain anchors at their retail addresses
  (one-line `#define code_seg(name)` wrappers in
  `layout/ltcg/game_main_dependencies/`, rig input order preserved);
- the strings `th10.cfg` / `./log.txt` / `log` and `BASE` are data aliases,
  the float pool (60.0 / 1.0 / 0.01) sits in the compiler's own pool pinned by
  `constants`, and the double zero is a data alias;
- the remaining rig bindings are `relative_code`/`data` absolute symbols
  (pushed function pointers such as `StartupDialog_Procedure` and
  `Sound_InitThread` need `data`, called ones `relative_code`).

## The three /EHsc callees: shaped stand-ins, not ordinary sources

Retail calls `??0SprtCtrl@@QAE@XZ` (0x00438C56), `??1FuncCtrlDestroyView`
(0x00438DAA) and `??1AnimationManagerStorage` (0x00438DF7) with the receiver
pushed and RET4: the private whole-program convention. The recorded method
wanted these bodies visible through `ordinary_sources` (the title_teardown
pattern). That cannot work here, measured:

- ordinary sources compile without `/GL`, so the bodies keep their declared
  thiscall convention: the model call sites became `mov ecx,eax` / `mov
  esi,eax` instead of retail's `push eax`, and 2-4 instructions drifted per
  site (the ordinary prototype reached the byte comparison before failing);
- the ordinary machinery is the only way to declare a `/EHsc` body's complete
  unwind group, and it is hard-wired to non-`/GL` objects (the section rename
  reads COFF section headers; generated anchors must originate from the
  ordinary object);
- the real `/GL` bodies therefore cannot be compiled here at all: their
  funclets merge into one `.text$x` contribution of eleven static functions
  that no declaration slot accepts without region ownership, and the owning
  clusters (`anm_storage_construct`, `anm_storage_destructor`, `d3d_destroy`)
  must keep that ownership to export their own groups.

The cluster instead carries shaped stand-ins
(`layout/ltcg/game_main_dependencies/eh_call_standins.cpp`, the
`item_manager_create` precedent). The flex-params entry scan only promotes a
parameter that the callee's **entry block** loads into a register; a stand-in
that first calls, then passes its receiver on, never presents such a load:

- both destructors reduce to `push 0; call MayThrow; jmp MayThrow`: the tail
  jump passes the receiver through its own stack slot and the callee's RET4
  becomes theirs;
- the constructor only touches its receiver for the implicit EAX result.

With those three call sites right the model is byte-identical in all 1,389
bytes; the probe reports EXACT and the full gates pass.

## Other levers that were on the table

- `/EHsc` + `throw()` on the three stack-`new` constructors compiles
  GameMain2 identically to the plain no-EH compile (no handler, no states) —
  useful if an exception cluster ever needs a non-EH selected function.
- With the real `/GL` bodies visible (a throwaway experiment, all inputs in
  rig order) GameMain2's codegen matched retail exactly as well; only the
  call-displacement fields of the layout's drifted anchors differed. The
  stand-ins reach the same bytes without owning the unwind groups.
