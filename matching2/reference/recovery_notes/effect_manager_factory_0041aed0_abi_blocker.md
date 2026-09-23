# Manager factory ABI blocker: `0x0041AED0`

Date: 2026-09-23

## Scope and disposition

The live `th10.exe` function at `0x0041AED0` spans `0x0041AED0..0x0041AF88`
(185 bytes). Its Ghidra signature is `uint* __stdcall(void)`, with no entry
parameters and a pointer result in EAX. The body remains the naked assembly in
`matching2/msvc/src/game/fun_0041aed0_0041aed0.cpp`.

This is not a supported standalone ordinary-C++ conversion. Although the
factory entry itself has a conventional no-argument stack contract, its call
to `0x0041AD90` supplies the new manager in EBX. Ghidra also models that
installer as `__stdcall(void)` with an `unaff_EBX` manager live-in. Replacing
only the factory with ordinary C++ would lose this call contract. Replacing
the installer with a typed C++ function requires changing a source outside
this range and updating its other callers as well.

## Live Ghidra evidence

The factory allocates `0x21CEC0` bytes. On success it calls the standard
`__stdcall` EH vector-constructor iterator at `0x0045252D` with the array at
`manager + 0x14`, element stride `0x3F0`, count `0x896`, constructor callback
`0x0041ACF0`, and destructor callback `0x0041AD60`. It then clears
`0x873B0` dwords, sets bit 1 in the first manager word, and publishes the
pointer to `DAT_00477818`.

Before calling `0x0041AD90`, the factory saves EBX and copies the manager
pointer from ESI to EBX. The installer has no stack parameters in Ghidra's
signature; its decompilation uses `unaff_EBX` to associate two scheduler
records with the manager and store them at `manager + 8` and `manager + 0xC`.
The call is therefore a concrete private-register dependency even though the
factory's own entry is ordinary `__stdcall`.

The factory's other direct callees are `operator new` at `0x00452493`, the EH
vector-constructor iterator at `0x0045252D`, the installer at `0x0041AD90`,
the manager destructor at `0x0041ADF0`, and `free` at `0x004524A1`. Ghidra
reports direct callers `FUN_00417870` (call site `0x00417ACA`) and
`FUN_0040A350` (call site `0x0040A360`). Both call the factory without stack
arguments. The first caller checks the returned pointer during its
initialization sequence; the second includes the call in its scene
reinitialization sequence.

The destructor helper at `0x0041ADF0` already has a separate typed C++
conversion recorded in
`matching2/reference/recovery_notes/manager_teardown_candidates_00408af0_0041adf0_00422220.md`.
The array callbacks and iterator are separate manifest regions and are not
changed by this screen.

## Next conversion dependency

An ordinary-C++ rewrite needs a coupled, compiler-visible treatment of the
factory and `0x0041AD90` installer so the manager can cross their boundary as
a typed argument. The real factory callers `0x00417870` and `0x0040A350`,
the EH vector-helper/callback chain, and the factory's SEH registration frame
also need to remain visible when evaluating emitted code. This screen did not
modify source or manifest entries, and no build, probe, or test was run.
