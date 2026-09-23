# CRT x87 status and control helpers (`0x0045ED70`–`0x0045EDAA`)

Ghidra identifies three adjacent Visual Studio 2003 CRT helpers: `__statfp`,
`__clrfp`, and `__ctrlfp`. The first two now express their x87-specific
operations through the x86 CRT `_status87` and `_clear87` interfaces. The raw
control-word helper remains a naked x87 implementation because its contract is
not the same as the translated `_control87` API.

## `__statfp` at `0x0045ED70`

The 11-byte leaf has no arguments. Its `FSTSW [ESP]` sequence waits for pending
x87 exceptions, stores the x87 status word, and returns that 16-bit value
sign-extended into `EAX`. It does not clear the status word. Ghidra lists one
caller, `__raise_exc`, at `0x0045E481`; that caller tests the returned exception
bits while preparing the exception record.

The source uses `_status87()` and explicitly reproduces the retail
sign-extension of its low 16 bits. `_status87` is x87-specific on x86, whereas
`_statusfp` may combine x87 and SSE2 state. Microsoft's documentation also says
pending unmasked exceptions are checked before status is returned, matching the
waiting behavior visible in `FSTSW`.

## `__clrfp` at `0x0045ED7B`

The 12-byte leaf has no arguments. It uses non-waiting `FNSTSW [ESP]`, then
`FNCLEX`, then sign-extends the saved status word into `EAX`. It returns the
pre-clear x87 status and clears the x87 exception state. Ghidra shows a call
from `__raise_exc` at `0x0045E589`, immediately before that routine raises a
Windows exception.

The source uses `_clear87()` and preserves the low-word sign-extension. This
API is the x87-specific status retrieval-and-clear operation on x86. The
source-level call expresses the CRT operation; its exact instruction sequence
has not been checked against the Visual Studio 2003 implementation.

## `__ctrlfp` at `0x0045ED87`

The 36-byte leaf takes two 32-bit cdecl stack arguments: `new_control_word`
and `mask`. It reads the raw x87 control word, computes
`(old & ~mask) | (new & mask)`, loads the low 16 bits with `FLDCW`, and returns
the previous 16-bit word sign-extended in `EAX`. It issues no explicit
status-word clear or load; its waiting `FSTCW` behavior is retained. The caller
removes both stack arguments, confirming cdecl cleanup.

At `0x00458C4C`, `__floor_default` calls it with a full-word mask, keeps the
returned old word, then restores that word through another full-mask call at
`0x00458C96`. Other Ghidra call sites include `0x0045E937`, `0x0045E96A`, and
`0x0046514B`.

This helper edits the *raw hardware word*. The separate CRT `__control87` at
`0x0046105E` converts the x87 word to the CRT's abstract flag representation
with `__abstract_cw`, applies its abstract mask, and converts back with
`__hw_cw`. Consequently `_control87(new, mask)` cannot replace `__ctrlfp` while
preserving arbitrary raw masks and reserved bits. The C++ standard floating-
point environment also does not expose a portable way to read, merge, and load
the raw x87 control word. This source retains the observed x87 instructions and
uses a typed cdecl signature to document the ABI.

## Verification limits

Ghidra function boundaries and call sites were inspected for all three helpers.
No build, probe, or test was run; the two CRT API substitutions have not had
their emitted code checked, and the retained x87 routine remains assembly.

Microsoft API references:

- [`_status87`, `_statusfp`, `_statusfp2`](https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/status87-statusfp-statusfp2?view=msvc-170)
- [`_clear87`, `_clearfp`](https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/clear87-clearfp?view=msvc-170)
- [`_control87`, `_controlfp`, `__control87_2`](https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/control87-controlfp-control87-2?view=msvc-170)
