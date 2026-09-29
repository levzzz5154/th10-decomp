# Runtime unwind fragments and static cleanup thunks (0x00465190–0x00465A6F)

## Scope and result

The `0x00465190–0x004658B5` span contains 102 assembly fragments: 62
`Unwind_*` entries and 40 `unassigned_*` entries. They form MSVC exception
unwind/handler support rather than ordinary callable functions. The final
span contains static cleanup callbacks with mixed ownership:

- `0x004659F0` is supplied by the matching `libcp.lib` toolkit object, not a
  maintained C++ conversion.
- `0x00465A30` is ordinary C++: it sets the global `PlatformWorker` vtable
  and calls its typed `Stop()` method.
- `0x00465A60` is still inline assembly. It passes the archive object at
  `0x00497990` through the callee's private ESI receiver convention.
The manifest marks `0x00465A30` semantic and preserves its previous assembly
record. This thunk uses a C++ `__cdecl void(void)` callback; the `0x00465950`
atexit registration names it directly. Native LTCG probes report EXACT for
the 23-byte callback, 12-byte registration, and adjacent 22-byte
`WorkerOwner::StopWorker`. A C++ call to the opaque archive Close helper at
`0x00465A60` instead compiled as a 5-byte tail jump, not its 13-byte
push-ESI, set-ESI, call, pop-ESI, return body; that thunk was not promoted.

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

## Evidence for the static callbacks

Ghidra disassembles `0x004659F0` as `mov EAX, 0x00491C28` followed by a tail
jump to `0x0041FF60`. The toolkit `libcp.lib` object supplies this callback;
the worker-stop helper at `0x0041FF60` is now an exact semantic C++ region.
`0x004659F0` is registered from `0x004658FB`.

Ghidra disassembly of `0x00465A30` is `push ESI; ESI=0x00474DD4; [0x00474DD4]
=0x004703E4; call 0x0044C150; pop ESI; ret`. The callee is already modeled as
`PlatformWorker::Stop()` in C++, with the matching worker layout in
`th10/platform/worker.hpp`. Ghidra records a data xref to this thunk from
`0x00465950`; its C++ atexit registration now uses the typed callback.

Disassembly of `0x00465A60` is `push ESI; ESI=0x00497990; call 0x00434D10;
pop ESI; ret`. `0x00434D10` has a typed candidate model but remains assembly
in the production manifest. Ghidra records a data xref to the thunk from
`0x004659C0`.

## GDI callback and remaining thunk

`0x00465A20` is now the ordinary C++ static-exit callback
`ReleaseGlobalGdiSurface_00465a20`: it passes the object at `0x00474CB0` in ESI
to the real C++ `ReleaseSurface_00436a30` body through native LTCG. The
callback's 13 bytes and its atexit registration at `0x00465940` match retail;
Ghidra defines the complete 13-byte callback.

`0x00465A60` still uses assembly: its `DatArchive_Close_00434D10` callee
requires a private ESI receiver and is not yet selected as C++. `0x00465A00`
and `0x00465A50` are already semantic manifest rows.
