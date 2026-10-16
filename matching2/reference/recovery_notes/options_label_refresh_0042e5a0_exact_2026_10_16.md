# Options label refresh 0x0042E5A0: byte-exact (2026-10-16)

Follows `options_label_refresh_0042e5a0_equivalent_2026_10_12.md`. The
3,999-byte refresh is now selected by the LTCG cluster
`msvc/build_support/layout/ltcg/options_label_refresh.json` from
`msvc/src/game/title/options_label_refresh.cpp`; the equivalent layout, its
context file and the assembly region (`build_support/exact/game/title/fun.cpp`)
are gone. `make EXACT=1` is unchanged (`2f14760b6fbbf575`); byte-exact rose
from 72.7% to 74.0% of the recovered bytes.

## The last residual (1,203 -> 1,204 of 1,204)

The equivalent model differed only in where `mov esi,[g_sprt_ctrl]` sat:
offset 0xA in the model, 0x7F in retail (after the music attenuation block,
just before the first label lookup). The source declared the manager local at
the top of the function; declaring it after the volume block matches. The
linked model was then identical to retail in all 3,999 bytes, not just
instruction-equivalent.

## Promotion

The equivalent rig was the difficulty cluster's context plus a context file
with the complete refresh (`TH10_FULL_OPTIONS_REFRESH`) and the real bodies of
0x0043E460 (`AnimationManager9::RegisterResource`, queue in EAX, name in EDX)
and 0x0043E5A0 (`Resource2::ConfigureObject`). The new cluster reproduces it:

- cloned from `difficulty_select_update.json`: its eight selected screens
  become anchors, its additional sources get one-line wrappers in
  `options_label_refresh_dependencies/`, and the driver includes the donor
  driver plus the refresh source;
- the two real callee bodies are anchors at their retail addresses
  (`#define code_seg(name)` wrappers, as for the donor's own src anchors);
- the donor's 0x0043E460 anchor is the music room's
  `RecoveryMusicResourceQueue::RegisterResource` stand-in, whose LTCG
  convention (ECX queue) is not retail's. Both bodies must exist, as in the
  rig, so the stand-in is parked as an anchor at 0x00401000 through the new
  `TH10_MUSIC_QUEUE_REGISTER_SECTION` macro in
  `recovery_script_executor_caller_433ef0.cpp` (default unchanged for the
  other clusters that include it).

Rewriting the stand-in into the AnimationManager9 shape instead moved the
refresh to 940/1,204 (queue in EDX, name in EDI): LTCG conventions depend on
every visible caller, so keep both bodies.

The first probe reported EXACT; no anchor size needed changing.
