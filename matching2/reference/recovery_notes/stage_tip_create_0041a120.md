# Tip creation 0x0041A120 and its urgent wrapper 0x00424650

2026-10-02. Both are ordinary C++ in the new cluster
`layout/ltcg/stage_tip_create_0041a120.json`; the whole EXE is exact.

* **Convention falls out of the one real call shape.** The only caller of the
  urgent wrapper (the spell timeout at 0x004269D0) loads the manager from
  `data_00477814` and passes a literal text and a position inside its object.
  A context shaped like that call makes the pass pick retail's convention with
  no anchors: wrapper manager in ESI, creator position in EBX.
* **The game state must be reached through its address.** Declared as plain
  `extern int` globals, or as an `extern` struct used directly, the compiler
  reads `display_mode` once and reuses it across the store to the new tip.
  Retail re-reads it. Going through `GameState()` (an inline returning the
  struct's address) restores the re-read, and with it the rest of the function:
  the same change moved the freshly allocated tip from ESI to retail's EDX.
* The constructor is declared in the class and defined out of line next to the
  creator; the list walk is `StageTipNode::Append`, which materialises the list
  head before the first `next` load as retail does.
