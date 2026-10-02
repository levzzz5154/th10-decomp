# 0x00405750 player update (parked)

The anchor model in `update_player` is 218 bytes against retail's 223.

What is settled:

- `position.x + 224.0f`, `position.y + 16.0f`, `0.5f` and `1.3f` must be
  literals (bound with `data_aliases`); as `extern float` globals the operand
  order of the two additions is reversed.
- The outer shape is `if (active_state) { switch (active_state) { case 1: ... }
  timer.Tick(); }`. A flat `switch` with `case 0` emits `sub eax, 0`.

What is not: retail keeps zero in ESI for the whole function (`xor esi, esi;
cmp eax, esi`), uses it for the three comparisons and the two stores on the
miss path, and holds the manager in EBP. Every source shape tried keeps the
manager in ESI, tests with `test`, and stores the known-zero EAX on the miss
path. Tried without effect: `if`/`switch` orderings, chained and reordered
zero stores, a zero-initialised `node`, `== 0` spellings, `position.z + 0.0f`,
and a third zero store (which also used EAX).
