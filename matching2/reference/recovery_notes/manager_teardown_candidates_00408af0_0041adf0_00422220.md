# Manager teardown candidates: 0x00408AF0, 0x0041ADF0, 0x00422220

Date: 2026-09-23

## Scope and result

Inspected the three Ghidra `th10.exe` functions, including boundaries,
prototypes, disassembly/decompilation, callers, callees, and xrefs. The source
work is limited to `msvc/src/game/manager_teardown.cpp`.

| Address | Ghidra body | ABI evidence | Result |
| --- | --- | --- | --- |
| `0x00408AF0` | `0x00408AF0–0x00408C81` | `__thiscall(this, manager)`, `RET 4` | Keep retail asm. The third `AnimationManager::SetFlag` call consumes `extraout_ECX`, left by the preceding callee; no ordinary-C++ value for that receiver is established. |
| `0x0041ADF0` | `0x0041ADF0–0x0041AEC7` | `__stdcall(manager)`, stack arg, `RET 4` | Converted to a typed C++ entry `BulletManager_Destroy_0041adf0`. |
| `0x00422220` | `0x00422220–0x00422356` | `__stdcall(manager)`, stack arg, `RET 4` | Converted to a typed C++ entry `PauseMenu_Destroy_00422220`. |

## Function evidence

`0x00408AF0` calls `0x004492A0` three times using resource slots at manager
`+0x768`, `+0x76C`, and `+0x770`, clearing each slot after the call. The first
receiver comes from entry ECX and the second from `[manager+0x76C]`; Ghidra
reports the third receiver as phantom `extraout_ECX`. It then removes scheduler
tasks and destroys three vectors. Ghidra lists callers `0x00408C90` and
`0x00417C80`, with additional call xrefs at `0x00408CE6`, `0x00408D21`,
`0x00408D45`, and `0x00417FEE`. The opaque third receiver is the blocker for a
faithful high-level call sequence, so this function remains asm.

`0x0041ADF0` removes non-null tasks at manager `+8` and `+0xC` from the global
scheduler under the critical section at `0x00492274`, updating
`DAT_0049231C` around each removal. It clears `DAT_00477818`, then calls the
EH vector destructor helper on `manager+0x14` with stride `0x3F0`, count
`0x896`, and callback `0x0041AD60` (`EntityAnimation_Release`). Its EH cleanup
also destroys this vector if a scheduler removal unwinds. Ghidra lists callers
`0x0040A1A0`, `0x00417C80`, and `0x0041AED0`; call xrefs include `0x0040A2C3`,
`0x00417E85`, `0x0041AF57`, `0x0041AF91`, and `0x0041AFB5`. The C++ entry
preserves the observed stdcall contract and the vector callback's ECX entity
argument. `asm_symbols.hpp` had a stale no-argument cdecl alias, which is hidden
locally in this source; the other source containing the `0x0041AF90` call now
uses the typed stdcall declaration. The manifest maps this region to its
decorated C++ symbol and keeps the old raw assembly alias.

`0x00422220` removes the two scheduler tasks at `+8/+0xC`, then destroys and
frees each non-null child pointer in the 25-slot array at `+0x1EC`. If the key
at `+0x1DC` is nonzero, it searches game-state list heads at `+0x72DAD4` and
`+0x72DADC` for the first record with a matching key. A match gets flag
`0x04000000`; when its owner at `+0x18` is null, the same flag is propagated
through the related-record list at `+0x14`. Finally it clears manager `+0x1DC`
and `DAT_00477830`. Ghidra lists callers `0x00417C80` and `0x00422360`, plus
wrapper call xrefs at `0x0042238D`, `0x004223B1`, and `0x004223D5`. The child
destructor helper at `0x004294A0` is called stdcall with one pointer, and free
at `0x004524A1` is cdecl. This source replaces the `0x00417C80` inline-asm call
with the new typed entry. The manifest now classifies the destructor regions
at `0x0041ADF0` and `0x00422220` as semantic C++ while retaining their raw
assembly aliases.

## Validation boundary

No builds, byte probes, or tests were run. The ordinary-C++ candidates are
based on the observed entry/callee contracts and behavior; compiler extent and
byte-for-byte equivalence have not been established here.
