# 0x0042A990: EAX-resident record transform remains an ABI blocker

## Observed body and boundary

The live Ghidra MCP program is `th10.exe` (`x86:LE:32`, image base `0x00400000`). A raw-byte disassembly of `0x0042A980..0x0042A9DF` shows the preceding `0x0042A980..0x0042A983` routine ending in `RET`, twelve `INT3` bytes at `0x0042A984..0x0042A98F`, this six-instruction body at `0x0042A990..0x0042A9A2`, and thirteen `INT3` bytes at `0x0042A9A3..0x0042A9AF`.

| Address | Instruction | Effect |
| --- | --- | --- |
| `0042A990` | `mov ecx,[eax]` | save dword at `+0` in ECX |
| `0042A992` | `mov edx,[eax+8]` | save dword at `+8` in EDX |
| `0042A995` | `mov [eax+4],ecx` | copy dword `+0` to `+4` |
| `0042A998` | `mov [eax+0Ch],edx` | copy dword `+8` to `+0xC` |
| `0042A99B` | `mov dword ptr [eax+14h],0` | clear dword at `+0x14` |
| `0042A9A2` | `ret` | return with plain `C3` |

The checked-in augmented Ghidra export independently records `FUN_0042a990` with body `0042a990-0042a9a2` (19 bytes, six instructions) and decompiles the same three assignments through `in_EAX`. The current live MCP database does not materialize a function at this address: `get_function_by_address`, prototype lookup, and caller/callee lookup report no function. This live/export mismatch is recorded because it limits what can be attributed to a caller from the current project state.

## ABI and references

EAX is the only register used as the record base. ECX and EDX are temporary copies; the function has no stack frame or stack reads, and it returns with `RET` rather than consuming stack arguments. The body therefore requires the object/record pointer to be present in EAX on entry. This is a private register contract, not an ordinary MSVC x86 function signature: `__cdecl` and `__stdcall` arguments use the stack, and normal `__thiscall`/`__fastcall` receivers use ECX. C++ can express the three field updates, but ordinary C++ cannot make this body receive its receiver in EAX without an ABI-specific compiler context or an assembly bridge.

The live Ghidra queries returned no xrefs to or from `0x0042A990`; a program-wide instruction search also found no direct `CALL` operand naming `0042a990` across 124,648 scanned instructions. Consequently there is no direct call site here to establish the caller-side contract or source-level method name. The body-level EAX requirement is certain; whether callers reach it through an indirect path remains unresolved.

## Symbol and alias status

The augmented export names the entry `FUN_0042a990`, which is Ghidra's default address-derived name. The current manifest binds the region to `_asm_FUN_0042a990_0042a990`; no separate retail alias or external symbol was found. `layout/ltcg/accessor_0042a980.json` also assigns `0x0042A990` to `?AccessorCompilerContext@@YGHPAPAUObjectAccessor_0042a980@@HH@Z`, but its own description identifies that 36-byte section as a synthetic compiler-context caller, not recovered game code. That probe symbol is an address collision in test metadata, not an alias for the retail body.

## Decision

Keep the current naked assembly for this region. The source file records previous native-LTCG matching attempts: its no-argument member candidate placed the receiver in ECX, while the dummy-argument candidate used stack traffic and `RET 4`; neither modeled the private EAX contract. No build or compiler probe was run for this audit. A future real caller context or compiler/private-ABI anchor could reopen ordinary-C++ recovery.
