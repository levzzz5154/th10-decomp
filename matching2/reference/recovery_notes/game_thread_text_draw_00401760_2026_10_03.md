# Text queue draws 0x00401760 / 0x00401A50 / 0x00401520 (2026-10-03)

All three are byte-exact in the LTCG cluster
`layout/ltcg/anm_batch_flush_00442f50.json`:

- `GameThreadText_DrawRecords_00401760` (`src/game/fun_00401760_00401760.cpp`)
- `GameThreadText::DrawLateRecords` at 0x00401A50
  (`src/game/fun_00401a50_00401a50.cpp`)
- `GameThreadText_DrawLateTask_00401520`
  (`src/game/game_thread_run_queue_leaf_00401520.cpp`)

Types are in `include/th10/game/game_thread_text.hpp`.

## Stack-slot order: what c2.dll does

The models were stuck on the order of two stack slots (the cursor `x`/`y`
against the parameter home). Traced in c2.dll with the PDB names:

- `AddStackElement` keeps the locals sorted by size, then by plain reference
  count: every reference adds 1, and an element only moves up past elements
  with a strictly smaller count.
- `ColorStackElements` gives parameter homes the first colours; each local then
  takes the first colour it does not interfere with. A local initialised before
  the parameter's first use interferes with the home and cannot share it.

So the slot order is a function of how many times the source mentions each
local, not of declaration order.

## The fix

The original handles the space character as its own branch with a second
`x += advance`:

    if (*text == ' ') {
        x += advance;
    } else {
        ...draw the glyph...
        x += advance;
    }

The optimiser merges the two additions, so the code is the same size, but the
extra reference to `x` changes its place in the sorted list. It also changes
register allocation so the receiver lands in EBX as in retail.

Other details that mattered: `int in_game_view = 1;` is the first statement of
0x00401760; the inline float setters (`GlyphSetScale`, `GlyphSetSpriteSize`)
also set `flags |= 8`; the sprite pointer is stored to the glyph first and the
size read back through it.
