# GameThread destructor and unwind handlers (2026-10-04)

The maintained destructor at `0x00401260` (467 bytes) and its compiler-generated
unwind functions at `0x004652E0` (11 bytes), `0x004652EB` (14 bytes), and
`0x004652F9` (10 bytes) now pass the exact-byte probe together.

The destructor body already matched. The unresolved issue was the slot helper's
calling convention: native LTCG privately passed its receiver in ESI, producing
a 30-byte helper and ESI-based unwind tail calls. Retail passes the receiver in
ECX and uses a 34-byte helper at `0x00401FF0`.

The compiler-only context defines `TH10_GAME_THREAD_SLOT_EXPORTED_ABI` before
including `game_thread.hpp`. That makes the inline slot destructor an exported
public ABI root in the temporary native link, preserving thiscall and producing
the expected ECX-based unwind functions. The export is not selected into the
final image. Other compiler contexts retain the ordinary declaration. The
original 34-byte anchor and following layout gap remain correct.

The native unwind map and FuncInfo bytes are checked by the cluster manifest.
No generated instruction bytes or relocation operands were rewritten, and no
comparison rule was relaxed.

Validation:

```sh
python3 matching2/tools/matching/probe.py --source src/game/destroy_game_thread_00401260.cpp
make
make EXACT=1
```
