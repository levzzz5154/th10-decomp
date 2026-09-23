# Trigger activation 0x00426CF0: live Ghidra ABI audit

## Boundary and entry contract

Live Ghidra analysis of `th10.exe` identifies `FUN_00426cf0` at `0x00426CF0`
with body `0x00426CF0..0x00426F62` inclusive, 627 bytes. The last instruction
is `ret 4` at `0x00426F60`; the following text padding begins at `0x00426F63`.
This agrees with the fixed-address region's 627-byte extent in
`matching2/msvc/regions.json`.

The function takes one pointer on the stack and uses callee cleanup. Both live
callers prove this contract:

- `FUN_004266b0` calls at `0x00426761` after `push edx`; the activation return
  is not used.
- `FUN_004267f0` calls at `0x0042695B` after `push ecx`, then overwrites EAX
  with `1`.

In each case the activation callee's `ret 4` removes the pushed pointer. The
entry itself is therefore representable as a normal one-argument `__stdcall`
function. Ghidra reports 140 instructions, 12 basic blocks, and 10 static call
sites to six distinct callees.

## Observed work and state changes

Disassembly shows the entry sets the supplied object's state at `+0x458` to 4,
then creates one animation object for resource index `0x162` and 32 more for
index `0x163`. Each allocated object has `+0x20` cleared and bit 30 set in its
flags at `+0x35C`; each is initialized, registered with the primary animation
manager, and assigned a three-float position. The first position is formed
from the object's coordinates at `+0x3C0`, `+0x3C4`, and `+0x3C8`, with the
first two adjusted by the constants at `0x00470B4C` and `0x00470B48`.

The function initializes timer-like groups at `+0x474..+0x484` and
`+0x430C..+0x431C` when their bit-0 initialized flags are clear, then resets
the active fields. It sets `+0x430C` to 5, `+0x4310` to 6, and `+0x4314` to
the float value 6.0, then loads the object's script. If the global at
`0x00477810` is non-null and its `+0x58` flags lack `0x200`, it queues resource
`0x00492590`. If the global manager's count at `+0x3738` is at least 60, the
function zeros `+0x3790` and clears bit 1 in the words at `+0x378C`, `+0x0AD4`,
`+0x0E80`, `+0x15D8`, `+0x1984`, `+0x1D30`, `+0x20DC`, and `+0x2488`.

## Callee contracts visible at call sites

The important ABI evidence comes from the call-site register setup and the
callee instructions, because Ghidra's inferred prototypes do not describe all
of the live inputs:

| Callee | Observed call contract | Evidence and consequence |
| --- | --- | --- |
| `0x00449950` | Manager in ESI; allocated object returned in EAX. | Its body reads and advances the manager's pool cursor through ESI. This input register is not named by a normal MSVC x86 function declaration. |
| `0x00449870` | Resource in ECX; object and index on the stack; callee returns with `ret 8`. | This shape can be represented as a non-varargs `__thiscall` method. It is not the blocker by itself. |
| `0x004489D0` | Object in EBX, manager in EDX, output slot in EAX. | Its body links the object's embedded node into the manager list and writes the assigned handle through EAX. This three-register contract has no standard MSVC C++ calling convention. |
| `0x004492F0` | Position record in ESI, handle on the stack, and manager in EDX. | Its body passes the handle to `0x004491C0` while EDX still selects the manager's primary/secondary lists, then copies the three position words to the object and its linked children. ESI and the nested lookup's EDX input are private register inputs. |
| `0x0043DC90` | Resource manager in ECX, selector in EDI, one stack argument; callee returns with `ret 4`. | The helper reads EDI as a resource-table selector, so an ordinary `__thiscall` declaration cannot carry the full contract. |
| `0x0043E710` | Resource in ECX, object in EAX, index in EBX. | Its body consumes all three registers and returns with plain `ret`; there is no standard MSVC C++ convention for this combination. |

`0x00449870` is called once before and once in the 32-iteration loop. The
same loop invokes `0x00449950`, `0x004489D0`, and `0x004492F0` at each
iteration, so these private register contracts are part of the repeated
object-creation path, not dead or exceptional branches.

## Recovery decision

Keep the current exact naked body. Although the entry and one initializer call
have ordinary C++ calling conventions, five other helper boundaries depend
on ESI, EBX, or EDI inputs that a standalone C++ call cannot express. Replacing
the helper calls with guessed prototypes would silently change the retail
register handoffs; using assembly wrappers would violate the no-inline-asm
goal. The viable next experiment is a single native-LTCG cluster containing
callers `0x004266B0` and `0x004267F0`, this entry, and the register-sensitive
allocator, list, position, resource, and script callees, so the compiler can
choose the private ABI across the visible bodies.

No build, probe, or test was run for this audit.
