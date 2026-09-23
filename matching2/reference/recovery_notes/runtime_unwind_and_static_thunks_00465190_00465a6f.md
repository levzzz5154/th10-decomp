# Runtime unwind fragments and static cleanup thunks (0x00465190–0x00465A6F)

## Scope and result

Screened the assembly manifest entries at `0x00465190–0x004658B5` and
`0x004659F0–0x00465A6F`. The first span contains 102 assembly fragments: 62
`Unwind_*` entries and 40 `unassigned_*` entries. They form MSVC exception
unwind/handler support, rather than ordinary callable functions. The final
span has four assembly thunks; three were expressed as ordinary C++ in their
existing source files:

- `0x004659F0` selects the `PlatformWorker` subobject at `0x00492254`, installs
  its base vtable, and calls the typed `Stop()` method.
- `0x00465A30` now sets the global `PlatformWorker` vtable and calls its typed
  `Stop()` method.
- `0x00465A60` now calls the existing typed `DatArchive_Close()` model with
  the archive object at `0x00497990`.

The manifest now marks the three converted thunks as semantic and preserves
their previous assembly records. Their no-argument C-linkage symbols stay
bound at the same addresses. No build, probe, or test was run.

## Evidence for the exception-handler span

The current source bodies show repeated frame-dependent cleanup fragments:
they load objects from the active exception frame (`EBP`-relative locations),
then jump to destructor callbacks, the vector destructor iterator, or a C++
frame handler. The associated `unassigned_*` entries load a handler descriptor
into `EAX` and tail-jump to `CxxFrameHandler`.

Ghidra's analysis of `0x00465190` reports an `EBP-0x10` exception object,
`exception::~exception`, and a data xref from `0x00471138`. Analysis of
`0x004651E0` reports a vector-destructor call on `(EBP+4)+0x68` with fixed
element-size/count/callback arguments and a data xref from `0x00471278`. These
are runtime functionlets whose inputs are the interrupted function's saved
frame; a normal C++ entry signature would not receive that state. No row in
this span qualified as a standalone ordinary-ABI conversion.

## Evidence for the converted thunks

Ghidra disassembles `0x004659F0` as `mov EAX, 0x00491C28` followed by a tail
jump to the private helper at `0x0041FF60`. Its sole incoming reference is
that tail jump; `0x004659F0` itself is registered from `0x004658FB`. The helper
adds `0x62C` to the render-state base, installs vtable `0x004703E4`, and calls
the worker stop routine. The semantic body names the resulting worker object
directly at `0x00492254`; the private helper remains available as assembly.

Ghidra disassembly of `0x00465A30` is `push ESI; ESI=0x00474DD4; [0x00474DD4]
=0x004703E4; call 0x0044C150; pop ESI; ret`. The callee is already modeled as
`PlatformWorker::Stop()` in C++, with the matching worker layout in
`th10/platform/worker.hpp`. Ghidra records a data xref to this thunk from
`0x00465950`.

Disassembly of `0x00465A60` is `push ESI; ESI=0x00497990; call 0x00434D10;
pop ESI; ret`. `0x00434D10` already has a typed `DatArchive_Close` C++ model
that accepts this receiver explicitly. Ghidra records a data xref from
`0x004659C0`.

## Remaining thunk candidates

- `0x00465A20` sets `ESI=0x00474CB0` and calls the private-ESI font-cache
  flush at `0x00436A30`. Ghidra identifies the receiver fields and the
  `SelectObject`, `DeleteDC`, and `DeleteObject` imports. A typed expansion is
  possible, but the shared flush helper remains assembly, so it was deferred.
- `0x00465A00` and `0x00465A50` are already semantic manifest rows.
