# What is left, measured: 300 KB of game assembly and 54 KB of CRT

2026-09-19. `match_crt.py` was run over the whole image and the two numbers below
come from its report cross-referenced with the manifest, so the split is measured
rather than estimated.

| | regions | bytes |
|---|---:|---:|
| manifest assembly | 2,074 | 354,617 |
| of which byte-identical to a toolkit CRT member | 327 | 54,411 |
| game assembly (no CRT match) | 1,747 | 300,206 |

The CRT share is `libc.lib` 32,599 bytes, `libcmt.lib` 21,584 and `libcp.lib` 228.
Every match sits in the static CRT block that starts at `0x00452493` - the lowest
is `0x00452493`, immediately below `strrchr` at `0x00452930` - and **no** region
below that address matches a library member, so the game platform code and the CRT
do not overlap. No CRT-matching region has been recovered yet: the semantic count
inside that set is zero.

That cuts both ways for the remaining work.

- The recovery target is smaller than the raw assembly count suggests: 300,206
  bytes of game code rather than 354,617, with the CRT block excluded from the
  `--game-only` screens for the same reason it is excluded here.
- The CRT block is *not* unrecoverable - each region is byte-identical to a member
  of the exact libraries the retail binary was linked with, so its readable source
  is that member's own source. What it needs is the MSVC 13.10 CRT source, which is
  not in this repository, and a decision recorded in `match_crt.py`'s own docstring:
  rebuild the unit from the matching source, or keep the region as assembly. That
  decision belongs to the project, not to an automated pass.

The same run also confirmed that the plain-expressible veins are exhausted. With
the two screen soundness fixes made today - a memory destination's base and index
registers are reads, and the register set now covers `si`, `al`, `cl`, `dl` and the
other aliases - the `--entry none` list is four regions and the `--entry eax` list
is ten, and every one of them is either already landed or carries a measured
register-convention blocker. Anything further needs the native-LTCG cluster path,
which is proven: 241 clusters are registered and landed.
