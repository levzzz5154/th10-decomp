# Exact secondary-back animation registrar

The complete 118-byte region at `0x00448AC0` is ordinary C++. It appends an entity to the secondary list, assigns a wrapping nonzero animation ID, and returns that ID through its hidden result slot. Its native entry convention is manager EDX, entity EBX, result EAX, plain RET.

The maintained cluster uses a 97-byte explicitly synthetic creation loop and the complete 159-byte pool allocator as unselected compiler context. No game caller is modified. `overlay/` preserves the current complete inputs; `before_exact_promotion/` preserves the replaced assembly and prior shared header. `evidence.json` records the complete native byte gate and both executable checks.

Replay from the repository root:

```sh
python3 matching2/tools/matching/probe.py --source src/render/animation_manager_register_secondary_back_00448ac0.cpp --output matching2/build/experiments/secondary_back_replay
```

After promotion `make -j2` and `make EXACT=1 -j2` both passed. The latter executable equals the entire 487,936-byte oracle. The original spell-card and primary-back exact contributions also remain unchanged in both outputs.

Current native proof: `matching2/build/experiments/registrar_siblings_2026_10_04/production_probe/clusters/animation_register_secondary_back_00448ac0/report.json`.
