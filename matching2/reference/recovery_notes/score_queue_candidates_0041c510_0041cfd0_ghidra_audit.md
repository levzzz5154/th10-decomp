# Score queue and projectile candidates: Ghidra audit

Live read-only audit of `th10.exe` in the Ghidra project `th10`, for remaining
assembly rows in `0x0041C000..0x0041CFFF`. No row was converted in this screen.
The `0x0041C330` EDI-input callback is covered by
`0041c480_wave8.md`; the `0x0041C760` private-register fragment already has a
source-local blocker description in `src/unidentified/FUN_0041c760_0041c760.cpp`.

## Candidate results

| Address | Current extent | Ghidra result | Screen decision |
| --- | ---: | --- | --- |
| `0x0041C510` | 153 bytes | Function `FUN_0041c510`, body `0x0041C510..0x0041C5A8`, displayed as `undefined4 __stdcall FUN_0041c510(int)` | Leave assembly: the displayed prototype omits the live-in manager in ESI; it also calls two EBX-input constructors that remain assembly. |
| `0x0041C5B0` | 202 bytes | Function `FUN_0041c5b0`, body `0x0041C5B0..0x0041C679`, displayed as `__fastcall` | Leave assembly: the object is carried in EBX, with EDX used to call `0x0041C030`, and returned through EAX. This does not match a standard standalone C++ entry ABI. |
| `0x0041C680` | 219 bytes | Function `FUN_0041c680`, body `0x0041C680..0x0041C75A`, displayed as `__fastcall` | Same private EBX object convention as `0x0041C5B0`. |
| `0x0041C8C0` | 442 bytes | No Ghidra Function object; data xref to the entry from `0x0046DA64` | Entry/return shape is a standard thiscall member, but the body calls unresolved assembly helpers `0x00404F30` and `0x0043EE30`; keep assembly pending that dependency work. |
| `0x0041CA80` | 1,272 bytes | No Ghidra Function object; data xref to the entry from `0x0046DA60` | Large table-dispatched routine. Its embedded jump table is separately represented at `0x0041CF78`, and direct dependencies include two remaining assembly rows; keep it for a broader interpreter cluster. |
| `0x0041CFD0` | 410 bytes | Function `FUN_0041cfd0`, body `0x0041CFD0..0x0041D169`, displayed as `void __fastcall FUN_0041cfd0(int)` | This is a conventional ECX-this member entry, but both call sites to `0x0041C510` rely on ESI holding `data_0047781C`; leave it with that private dependency unresolved. |

## Register and dependency evidence

At `0x0041C510`, Ghidra's first instruction reads `[ESI+0x438]`; the stack
integer is read separately from `[ESP+4]`, and the routine returns with `RET 4`.
`get_xrefs_to(0x0041C510)` reports ten call references, including the two calls
in `FUN_0041cfd0` at `0x0041D0D8` and `0x0041D14D`. It also calls
`0x0041C5B0` and `0x0041C680` after moving the allocated object from EAX into
EBX. Each constructor then uses EBX for its object state; both begin by moving
EBX to EDX for the semantic `0x0041C030` initializer and finish by returning
EBX in EAX. The `__fastcall` declarations Ghidra inferred do not describe that
object register.

For `0x0041C8C0`, Ghidra's byte listing confirms the usual thiscall shape:
`PUSH ECX; PUSH EBX; MOV EBX,ECX`, a stack argument read after the prologue,
and `RET 4` at `0x0041CA77`. The direct calls include:

- `0x00404F30`: 202-byte assembly row.
- `0x0043EE30`: 9,964-byte assembly row; Ghidra's current Function object
  reports body `0x0043EE30..0x004413A2`.
- `0x0041F800`: semantic polar-vector helper.

For `0x0041CA80`, live disassembly shows `MOV EBP,ECX` at entry, a loop back to
`0x0041CAA0`, and the common `RET` at `0x0041CF74`. The dispatch table begins at
`0x0041CF78`. The current manifest already models the following direct callees
as semantic: `0x00405410`, `0x00426660`, `0x0041F800`, and `0x0043DC90`. Its
calls to `0x00404F30` (assembly) and `0x0043DD10` (assembly) still prevent a
small isolated conversion.

`0x0041CFD0` is referenced from vtable data at `0x0046DA9C`. Its other direct
helpers `0x0041F800`, `0x0043DC90`, and `0x0044BC70` are semantic rows, but
`0x0041C510` is not. In both call sequences this function loads
`ESI = data_0047781C` and pushes the selector before calling `0x0041C510`.
The ESI state plus the nonsemantic callee means the ordinary member source
shape is not independently recoverable from this row.

## Next useful unit of work

The remaining promising unit is a linked score-object/queue recovery centered
on `0x0041C510`, with `0x0041C5B0` and `0x0041C680` as constructor dependencies
and callers such as `0x0041CFD0`. That work must account for ESI manager state
and the EBX object convention together. Separately, `0x0041C8C0` depends on the
large animation VM tick at `0x0043EE30`; `0x0041CA80` belongs with its script
dispatch table and outstanding helper cluster.

No source, header, manifest, or LTCG layout was changed by this screen; only
this audit note was added.
