# Exception-frame unregister helper at `0x004630CE`

## Live Ghidra evidence

Queried the connected `th10.exe` program through Ghidra MCP. Ghidra recognizes a
function beginning at `0x004630CE`, with its last instruction at `0x0046316B`.
The disassembly extent is therefore 158 bytes (`0x9E`). The entry reads two
stack arguments and returns with plain `RET`, so the ABI is cdecl with caller
cleanup. `analyze_function_complete` reports parameters at `Stack[0x4]` and
`Stack[0x8]`, 46 instructions, and 11 call instructions. It reports no direct
callers or xrefs to the entry.

The entry at `0x004630CE` was not independently disassembled as a function in
the checked-in source; it was embedded after three other entry sequences in
the ownerless 396-byte row beginning at `0x00462FE0`. Ghidra did identify this
final entry separately. Its code tests the frame's saved-exception sentinel,
unlinks the frame, conditionally destroys the current Microsoft C++ exception
object when the unwind flag is clear and the exception record has the expected
code, parameter count, and version, then restores the saved exception and
translator fields in thread data.

Ghidra displays the function as `void` but marks its return type unresolved.
The C++ source uses `void`, matching the displayed decompilation and observed
caller-cleanup ABI. Since Ghidra found no callers or xrefs, current evidence
does not establish whether a dynamic caller observes EAX.

## Source split

`src/unidentified/unassigned_00462fe0.cpp` now retains the assembly-only prefix
through `0x004630CD` and defines the `0x004630CE` tail as ordinary C++ under the
name `CxxUnregisterExceptionObject_004630ce`. The C++ view records the frame
fields at offsets `+0`, `+4`, `+8`, and `+0xC`, and reads thread-data fields at
`+0x7C` and `+0x80`. It preserves the original repeated `getptd` reads in the
exception-record checks. The call to the naked destructor entry passes the two
stack values present in the original caller sequence.

The manifest splits the original 396-byte span into the 238-byte assembly
prefix and this 158-byte semantic tail. The raw prefix symbol remains at
`0x00462FE0`; the tail has the canonical C-linkage symbol
`_CxxUnregisterExceptionObject_004630ce`, with a typed declaration and address
macro in `include/asm_symbols.hpp`. The return type remains based on Ghidra's
void display because no caller evidence is available to resolve EAX usage.

## Nearby assembly rows reviewed

| Address | Live evidence | Reason left in assembly |
| --- | --- | --- |
| `0x00462B35` | Ghidra identifies `type_info::~type_info`, `__thiscall`; body has SEH prolog/epilog and lock/free operations. | Standard member ABI, but conversion is coupled to MSVC exception-frame behavior. |
| `0x00462B97` | No Ghidra function or xrefs at the row start. Three comparator entries use ECX as an implicit object and each ends in `RET 4`. | Owner type and member signatures are not established. |
| `0x00462E11` | Ghidra identifies CRT `TypeMatch`; body consumes implicit ESI and EDI in addition to stack data. | The displayed C signature omits live register inputs. |
| `0x00462E60` | Ghidra finds callers, but its body consumes the input pointer from EAX before checking the exception record. | Private EAX input. |
| `0x00462E7E` | Ghidra identifies `___FrameUnwindToState` with four cdecl stack parameters. Source includes the CRT SEH prolog/epilog and split control-flow tail. | Converting this safely needs the exception-registration behavior recovered with the function. |
| `0x00462F2B` | Disassembly is `mov ebx,[ebp+8]` / `mov esi,[ebp-0x1c]`. | Continuation using the preceding function's frame, not a standalone entry. |
| `0x00462F4C` | No Ghidra function or xrefs at the row start; body dereferences the input in EAX and returns its predicate in EAX. | Private EAX input. |
| `0x00462F7C` | Ghidra identifies `___DestructExceptionObject`, cdecl, with SEH prolog/epilog and an indirect member call. | Runtime EH behavior remains assembly-backed. |
| `0x00462FB0` | Instructions use EBP-relative saved state; the trailing bytes restore ESP and jump into `terminate`. | Split epilog/continuation, not a standalone function. |
| `0x00462FC1` | Ghidra identifies `AdjustPointer`; pseudocode reads hidden EAX and ECX values despite its displayed cdecl signature. | Private register inputs; callers at `0x00463415`, `0x00463494`, `0x004634D8`, and `0x004634E9` use that convention. |

No build, probe, or test was run.
