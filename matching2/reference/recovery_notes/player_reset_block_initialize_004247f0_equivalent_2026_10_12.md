# PlayerResetBlock::Initialize 0x004247F0 — equivalent attempt (2026-10-12)

Status: attempted and parked.  The region stays `asm`.

## What exists

A complete readable body already lives in the `large_player` cluster
(`layout/ltcg/large_player_dependencies/runtime.cpp`,
`PlayerResetBlock::Initialize`) as the anchored context of the recovered
Factory/Reset functions.  The equivalent-model attempt
(`layout/equivalent/player_reset_block_initialize_004247f0.json`,
unregistered) wired the model link with the cluster's context and symbol
coverage.

## Blocker: the model body is 187 bytes shorter

The model's `Initialize` compiles to 1248 bytes against the 1435-byte
region.  The equivalence machinery compares code at equal extent
(`retail[:code_bytes]` against `body[:model_code]`), so a shorter body
cannot be compared: the overread into the next function's code produces
unbound references and instruction garbage.

The shortfall is the same scheduling class as the label refresh 0x42E5A0:
the model's stack-frame layout, evaluation order and register homes differ
(the entry block alone shows the middle position dword kept in EDX and
never stored, versus retail reloading it through ECX into [esp+0x4c]).

## Notes for future attempts

* Bindings for this context must distinguish three address spaces: the
  model image addresses of context-defined callees (e.g. TextLog::Append at
  model 0x401c10) are NOT retail addresses — binding a model address as if
  it were retail silently corrupts every call.  `bindings` values must be
  retail addresses; the tool maps model→retail through the link map.
* The cluster's `absolute_symbols` (LargePlayerTick/Draw/Refresh/Cleanup,
  ParameterFile and scheduler externals) are all needed by the model link.
* The cluster anchors' bodies are context-defined and must NOT be bound
  absolutely (duplicate definition).
* A future lever: match the retail extent by recovering the scheduling
  (the same lever as every blocked region), or extend the equivalence tool
  to compare a declared shorter model extent against a retail prefix with
  the remainder justified — a large tool change.

## 2026-10-17: multiply operand order canonicalized; parked

The ten x87 operand-order hunks (`fld [esi+0xN]; fmul [0x470b44]` in retail
versus the hoisted `fld [0x470b44]` plus `fmul [esi+0xN]` in the model, the
four `(int)(field*flt_100)` bound words) do not move when the multiplies are
spelled `flt_100*field`: the compiler canonicalizes the memory-operand
product either way, exactly the `msvc-c2-oper-order-mechanism` rule (the
swap moves codegen only register-register). Retail's per-statement global
reload is the CSE decision, not the source operand order.

Region stays equivalent (217 differing bytes). The scheduling lever named in
the note above remains the route.
