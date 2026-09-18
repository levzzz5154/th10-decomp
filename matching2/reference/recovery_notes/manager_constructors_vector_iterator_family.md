# Manager constructors and the `_eh_vector_constructor_iterator` family

2026-09-18. Screening the remaining assembly for regions whose calls are all
expressible from C++ found **107** candidates; only five are game code, and the
two best are the manager "construct" functions:

| region | size | shape |
| --- | ---: | --- |
| `0x00408910` `PlayerManager_ConstructRetail` | 176 | `_DWORD* __stdcall f(_DWORD*)`, linear |
| `0x00402160` `ConstructGameState` | 188 | `_DWORD* __stdcall f(_DWORD*)`, linear |

`0x00408910` reads: SEH frame, then three array constructions —
`[esi+0x10]` with **2** elements, `[esi+0x778]` with **8**, `[esi+0x24D8]` with
**5**, all element size `0x3AC` (Entity's size), each through
`_eh_vector_constructor_iterator` with the constructor `0x00402050` and the
destructor `0x00401FF0` pushed as immediates — then `[esi+0x3744] &= ~1`, a
`rep stosd` of `0x3B30` bytes from the manager, `flags |= 2`,
`data_004776F4 = manager`, return the manager. `0x00402160` is the same shape
for the game state (arrays of 8 and 3 at +0x180 and +0x1F08, `[esi+0x2A2C]`,
`[esi+0x168]`).

Both land badly under the textbook spellings. Measured in a throwaway copy of
the project (`/tmp/w408910/msvc`) with a class element that has declared
constructor/destructor:

- **placement array-new** (`new (m->a) Elem[2]`): MSVC emits an *element loop*
  (`mov ecx,esi; call ctor; add esi,0x3AC; dec edi; jne`) **plus an array-new
  cookie store** (`mov [eax],2`) — not the vendor helper, and bytes retail does
  not contain.
- **placement class-new** (`new (m) Manager`): emits a call to the placement
  `operator new` before the constructor, another call retail does not contain.

The vendor helper with a `dtor, ctor, count, size, dst` push order is emitted for
a **constructor's member-array initialization**, i.e. the retail body *is* a
constructor body — but `0x00408910` reads its pointer from `[esp+0x14]`
(a stack argument, `__stdcall`) and never from ECX, so the ABI of the retail
source and the convention of a C++ constructor disagree. Resolving that
disagreement is the prerequisite for this family; the constructor and destructor
addresses the helper pushes are already landed semantic regions, so once the
source shape is found the byte gate should be reachable.

## What is already established for a retry

- Element size `0x3AC` and the constructor/destructor addresses come from the
  image; the two arrays' offsets and counts are in the listing above.
- The manager's own size is `0x3B30`; `data_004776F4` is the published pointer.
- The trailing `rep stosd` overwrites the freshly constructed arrays — the same
  dead-initialization pattern the `0x00405D00`/`0x0040A040` pair shows.
- Expressing the constructor/destructor calls needs class symbols; the landed
  ones are free `__fastcall` functions (`?Entity_Constructor@@YI...`,
  `?Entity_Destructor@@YI...`), which are machine-identical to `__thiscall`
  members with the same bodies (`this` in ECX, destructor without a return), so
  a `coff_aliases` entry can point a class's constructor/destructor at them
  without writing an address into code.

## By-value return tested and rejected

The `[esp+4]`-only read also fits a function returning the manager **by value**
(the hidden return pointer being the only stack dword). Measured: a
`Manager __stdcall f()` that builds a local and returns it compiles to a
stack-local construction plus a `rep movs` copy into the return slot, with an
`and esp,-8` frame and a `__chkstk` call — i.e. no NRVO into the hidden pointer
and nothing resembling the retail frame. Rejected.

So the family needs either the exact spelling that makes MSVC emit
`_eh_vector_constructor_iterator` for a `__stdcall` function reading its object
from the stack, or acceptance that the region is a constructor body the asm
callers reach with a non-standard entry (the addresses the helper pushes are
already landed, so the byte gate is otherwise reachable).

Re-create the scratch project with `cp -a matching2/msvc /tmp/w408910/msvc`;
all experiments above only touched that copy.
