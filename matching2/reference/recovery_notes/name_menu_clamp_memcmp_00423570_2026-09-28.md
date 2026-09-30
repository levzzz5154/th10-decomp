# Name-menu caller `00423570`: bounded clamp and comparison residual

**Not promoted.** Fresh Ghidra evidence and five complete compiler trials leave
the best full 377-byte caller at **19 differing bytes**, first at `0042362B`.
The native body starts at the original `00423570` entry and has the original
377-byte extent. Its complete SHA-256 remains
`9eda2039e947f998f8a7bd9be35fd9f56de7af84854c6686cf005602cd183a2b`.
The original 316-byte insertion remains assembly-owned and unmatched.

All work is in
`matching2/build/experiments/name_menu_clamp_memcmp_2026_09_28`. The frozen
scratch project has 4,009 input files, checked by `terminal_input_hashes.json`.
The normal final byte gate is `terminal_gate.json`; the complete MAP/PE body
checks and rejected attempts are reproduced by:

```sh
PYTHONPATH=. python3 matching2/build/experiments/name_menu_clamp_memcmp_2026_09_28/measure.py
```

The full insertion compiler context remains 321 bytes against the original
316, with 102 unmasked overlap differences, and is explicitly unselected. The
real `MenuCursor::Advance` dependency at `0044BEA0` still matches all 128 bytes.
No function extent was shortened; no comparison mask, inline assembly, address
rewrite, reference instruction, or post-emission instruction change was used.

Fresh existing-head Ghidra decompilation and complete disassembly of `00423570`,
`00421FA0`, `0044BEA0`, and genuine setter `0040AD20` are archived in the new
experiment. Bounded memory at `0046E354` confirms the blank-name comparator is
the real nine-byte global **eight spaces followed by NUL**. The caller's name
array and this global each occupy nine bytes. Changing `memcmp` to `strncmp`
or replacing the mutable global with a string literal would change behavior.

The 19 byte differences are confined to three contiguous spans:

| Retail addresses | Differing bytes | Concrete residual |
| --- | ---: | --- |
| `0042362B`–`00423635` | 11 | Retail's zero-count path stores literal zero; its positive-count path clears EAX then stores it. Current compiler uses EAX in the zero path and a literal store in the positive path. |
| `0042368A`–`0042368D` | 4 | Retail loads EDI with the blank-name pointer before ECX with the nine-byte count. |
| `0042368F`–`00423692` | 4 | Candidate loads ECX before EDI. |

The preceding note
`name_menu_preparation_00423570_2026-09-28.md` incorrectly described these
as a 12/7 split. The measured split is **11/8**, as listed above. The total
19-byte count and first difference in that note remain correct.

The genuine `0040AD20` bounded setter's request-zero specialization has the
same behavior for every signed count: zero and positive count select zero;
negative count selects `count - 1` with 32-bit wraparound. The remaining branch
bytes reflect how the compiler carries that zero through the paths, rather than
a new runtime branch or missing operation. Its complete body was inspected;
trialing a full branch-specific inlined form contracted the caller to 363 or
361 bytes, so it cannot replace the retained 377-byte candidate.

| Bounded trial | Full caller extent | Unmasked differences in original overlap |
| --- | ---: | ---: |
| Reproduced 377-byte baseline | 377 | 19 |
| Nonzero-outer clamp control flow | 377 | 41 |
| Branch-specific generic setter | 363 | 163 |
| Reversed `memcmp` operands, checking only equality | 377 | 36 |
| Genuine setter with value provenance and separate returns | 361 | 147 |
| Reuse `strcpy`'s returned destination for `memcmp` | 377 | 19, identical body |

The reversed operands preserve the equality test but changed register setup
and additional code bytes. Reusing `strcpy`'s actual returned destination is a
real dataflow alternative, yet this compiler canonicalized it to the same
377-byte body. The two immediate register loads before `REP CMPSB` are
independent; C++ expression order does not constrain their machine order.

The next lever would need evidence about the original inlining or value-lifetime
boundary of the generic cursor setter, or a genuine compiler-context difference
affecting `memcmp` register materialization. The current evidence does not
support an exact-match claim or a source spelling sweep.
