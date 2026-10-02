# Pause menu opening at `0x004231D0`

The complete 411-byte opening routine is maintained ordinary C++ in `src/game/pause_result_open.cpp`. Its literal native SHA256 is `1ffe7019866cdcdd637767683745a622a8119e9695bccad454c048592928e8a8`. The real Player updater supplies the menu pointer in EDI; incoming ECX is not an input. The complete true updater and its animation/item/movement graph derive this private convention naturally.

The opening operation handles replay cancellation, enters phase six, resets its timer, marks the game paused, creates cursor and background animations, registers their returned four-byte IDs, binds the cursor sprite, loads and records music, and saves/replaces the frame speed. The shared inline opening body uses animation128 and clears the result flag here; the separately compiled result opener uses129 and sets it. Named aggregate IDs have distinct real lifetimes, and bit30 uses a scoped VM flag view. Shared Entity and global headers remain unchanged.

The real standard resource initializer is imported through its proven thiscall boundary, resource ECX plus object/index on the stack and RET8. ItemCreateOffset returns its genuine aggregate; it has no explicit invented return-home parameter. All compiler-visible private helpers are complete ordinary C++, with no ASM, artificial volatile/barrier, fake input, synthetic edge, mask or byte reconstruction.

All 34 complete native contributions were independently checked; nineteen match literally. The complete Player context is2860 versus retail3112, and complete Movement is1652 versus retail1656. These and all other context/helpers receive zero recovery credit. Fifteen complete nonmatches remain:

- Secondary: native117 / retail118; 38 prefix differences and 1 bytes of length difference.
- input_mode: native29 / retail37; 19 prefix differences and 8 bytes of length difference.
- movement: native1652 / retail1656; 1403 prefix differences and 4 bytes of length difference.
- primary_back: native117 / retail118; 38 prefix differences and 1 bytes of length difference.
- load_script: native197 / retail203; 165 prefix differences and 6 bytes of length difference.
- translated: native120 / retail111; 48 prefix differences and 9 bytes of length difference.
- ItemSpawn: native803 / retail819; 756 prefix differences and 16 bytes of length difference.
- ItemConfigure: native200 / retail202; 177 prefix differences and 2 bytes of length difference.
- ItemCreateOffset: native116 / retail118; 80 prefix differences and 2 bytes of length difference.
- CollisionActivate: native198 / retail199; 103 prefix differences and 1 bytes of length difference.
- CollisionCheck: native260 / retail260; 8 prefix differences and 0 bytes of length difference.
- PolarAdvance: native168 / retail171; 29 prefix differences and 3 bytes of length difference.
- FrameTimer_Tick: native72 / retail72; 3 prefix differences and 0 bytes of length difference.
- ConfigureObject: native356 / retail356; 6 prefix differences and 0 bytes of length difference.
- PlayerUpdateContext: native2860 / retail3112; 2631 prefix differences and 252 bytes of length difference.

The package installs32files and reuses15 unchanged headers, including four views shared with ResultOpen. Only the411-byte owner is newly semantic. Frozen manifests, independent reviews, native PE/MAP proofs, current input hashes and fresh maintained probe are under `matching2/build/experiments/pause_result_open_pair_20261002/`.

Fresh maintained probes and the whole-EXE gate pass. All 487,936 output bytes are literally equal to the supported executable, SHA256 `2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`; masks and instruction/address-operand changes are zero. The batch adds 1,985 selected asm-free C++ bytes: 1,975 previously ASM plus the proven 10-byte game handler formerly classified as library. Verified asm-free totals are 2,116 regions / 141,337 bytes, 43.7385% of 323,141 project-owned bytes. Six mixed semantic bodies still contain 4,525 ASM bytes and are excluded. Existing Entity273 and Allocate161 cleanup adds zero byte credit. The final incremental recheck reused 1,601 units and compiled three. `whole_verification.json` in each batch lab records the first full gate and final allocator recheck.
