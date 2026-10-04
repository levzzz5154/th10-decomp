# Exact secondary-front animation registrar, 2026-10-04

The complete 112-byte region at `0x00448B40` is readable ordinary C++. It prepends an entity to the secondary list and assigns a wrapping nonzero animation ID. The native private entry receives the manager in EDX, entity in EBX and hidden result in EAX, returning with plain RET.

The three embedded manager links are initialized through an array view (owner, next and previous), with a compile-time check that the links begin at +4. Insertion then uses the list-node view. Initializing through the cast list-node itself allowed the pinned compiler to remove the generic link branch; the array view preserves retail's complete branch and instruction schedule. No assembly, barriers, volatile reads, assumptions or output-byte patches were added.

A separate 81-byte synthetic single-object creation context establishes the entry convention. The complete 159-byte allocator is an unselected callee anchor. Neither context contribution receives recovery credit. Only the registrar's complete native body is extracted, with zero masked or changed instruction bytes.

Fresh maintained-source probe: `matching2/build/experiments/registrar_siblings_2026_10_04/front_production_probe_1/clusters/animation_register_secondary_front_00448b40/report.json`. Raw native PE bytes equal retail; SHA-256 `281e7b13dac50ecadfce65b87e4b2027cdf5c151d8d0ac09abfeb8da60b03268`. Both `make -j2` and `make EXACT=1 -j2` passed. All four registrars and the full 2,432-byte spell-card routine are exact in both outputs. The entire 487,936-byte EXACT executable equals retail, SHA-256 `2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`.

`matching2/reference/semantic_candidates/animation_register_secondary_front_00448b40/overlay/` archives all current compiler inputs. `before_exact_promotion/` retains the replaced assembly and original shared header. The adjacent evidence JSON records input hashes and executable checks.

Replay from the repository root:

```sh
python3 matching2/tools/matching/probe.py --source src/render/animation_manager_register_secondary_front_00448b40.cpp --output matching2/build/experiments/animation_register_secondary_front_00448b40_replay
```
