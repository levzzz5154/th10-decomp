# Register-convention leaves through per-function LTCG clusters, 2026-09-28

**Result:** leaves that earlier notes marked blocked on their entry registers
(two to four live-in registers, often ESI/EDI/EBX) are recovered one function per
native-LTCG cluster. Each cluster is the function's readable source plus a
synthetic context that only calls it; the whole-program pass then assigns the
same private convention retail has. The whole executable stays exact.

## What decides the convention

The callee body, not the caller shape. The same body gets the same entry
registers under a loop context, a single-call context or a two-call context.
When the entry registers differ from retail, the body is what needs to change:

* Floating-point arguments never travel in integer registers. A setter that
  receives its value on the stack while the object is in EAX takes a `float`.
* A function that keeps its public `__thiscall`/`__stdcall` stack arguments
  (`RET n` with every argument on the stack) is listed in the layout's `roots`.
* A member function keeps `this` in ECX; `0x00427E20` matches only as
  `Vec2::Assign`, not as a free function with the same effect.

## Source-shape facts that mattered

* **Escaping globals.** LTCG knows when a global's address is never taken and
  then lets loads of it move past stores through pointers. Retail's
  `0x0043A4C0` reloads the window handle after storing the device number; the
  context must let `&data_00491c70` escape for the build to keep that order.
* **dllimport.** Declaring kernel32 entries `__declspec(dllimport)` (bound
  through `__imp__Name@N` absolute symbols) lets the optimizer treat the IAT
  slot as constant, so `0x00436570` keeps `GetExitCodeProcess` in ESI across
  its wait loop. A plain function-pointer global does not.
* **Store/load forwarding follows the source expression.** The animation
  registration leaves reload `node->next` right after clearing it only when the
  link is written through `&entity->node` rather than the cached `node`.
* Small orderings are visible: the order locals are declared decides their
  stack slots and registers (`0x00437590`), and the order of loop increments
  decides the register pair (`0x00437670`).
* `memset(row, 1, 4)` four times, not one 16-byte memset, gives four
  `mov [eax+disp],ecx` stores with the constant in ECX (`0x0042C8C0`).
* A trailing `C3` after a function's own `ret` is often a separate empty
  function (`0x0044DF00`); split the region there.

## Recovered this way

`0x004043D0`, `0x00412720`, `0x00412750`, `0x004015C0`, `0x00401530`,
`0x00427E20`, `0x0042AC90`, `0x0042C8C0`, `0x00436570`, `0x00436A30`,
`0x00436CA0`, `0x00436D60`, `0x00437590`, `0x00437670`, `0x00438A30`,
`0x0043A4C0`, `0x0043A590`, `0x00446530`, `0x00446570`, `0x00449700`,
`0x0044B740`, `0x0044B790`, `0x0044C000`, `0x0044D400`, `0x0044D640`,
`0x0044DBF0`, `0x0044DD40`, `0x0044DEE0`, plus the float setters and leaves
listed in the cluster layouts under `layout/ltcg/`.

## Attaching leaves to existing clusters

* A leaf whose private convention is fixed by a neighbour can join that
  neighbour's cluster as an extra translation unit (a function entry with its
  own `source`, listed under `additional_sources`) instead of getting a new
  cluster.  `0x00409270`, `0x00420D90`, `0x004243C0`, `0x004243F0`,
  `0x00447910`, `0x00449210`, `0x00449820`, `0x0044A060`, `0x0044D740` and
  `0x00450030` were recovered this way.
* The cluster link discards functions nothing calls.  Leaves with no retail
  caller need a call from the cluster context (private conventions) or an
  entry in `roots` (standard conventions); otherwise they come out 0 bytes.
* Growing the context moves every later section, so the gap after it must
  shrink by the same amount.
* A new cluster only builds as a cluster once it is listed in `regions.json`
  `ltcg_clusters` (`tools/waves/register_cluster.py --layout
  layout/ltcg/NAME.json --apply`, path relative to `msvc/`).  If it is not
  registered, the region compiles as a plain unit and fails its size check.
* Mirror a sibling's source shape.  `0x00450030` is the integer twin of
  `0x00450070`.  It matched only when the offset was read through a
  `const int&` like the float version; a plain `int` local re-associated the
  frame-address sum whatever order it was written in.

## Scheduler_Remove argument order

About fifty retail callers of `Scheduler_Remove` (0x00449F60) load its
arguments as `mov ecx,<task>; mov edx,<scheduler>`: ECX first.  A `__fastcall
(task, scheduler)` declaration always loads EDX first.  The fix is to compile
0x00449F60 inside the caller's link, declared `(Scheduler*, SchedulerTask*)`
without its address taken, so the pass gives it a private convention.  It
still puts the task in ECX (it gives the first declared parameter the second
register), and it now evaluates the arguments in ECX-first order.  Code
compiled outside that link calls the same entry through the
`__fastcall Scheduler_RemoveTask(task, scheduler)` declaration; plain units
map it with a `coff_aliases` entry (`@Scheduler_RemoveTask@8` to
`_Scheduler_Remove@8`), and clusters give it an absolute symbol.  0x00413300
was the first caller recovered this way, in the
`bullet_manager_load_scripts_0040ae70` cluster that owns 0x00449F60.
The same cluster now also holds 0x004133F0, 0x00413450, 0x0043CB00,
0x00405620, 0x0040AF00, 0x0041C1C0 and 0x00422220.  They share the inlines in
`th10/game/scheduler_remove_locked.hpp`, `th10/game/published_block.hpp` and
`th10/render/animation_mark_for_removal.hpp`.  Still open on this lever:
0x0040B7B0 needs 0x00447F70, 0x0040B3A0 and 0x00447810 in the same link;
0x00418EE0 decrements the depth byte through AL.  0x0041ADF0, 0x0042B570
and 0x00424ED0 need /GX.

## Still open

* `0x004364F0` (memory-stream seek): the body matches except that retail
  cross-jumps case 1's success into case 2's tail; 19 lines differ.
* `0x0044DE10` (archive read): only the placement of the shared
  `CO_E_NOTINITIALIZED` return differs.
* The four animation-registration leaves (`0x004489D0`, `0x00448A50`,
  `0x00448AC0`, `0x00448B40`): bodies match instruction for instruction, but
  the entity arrives in EDI instead of EBX and the id pointer on the stack
  instead of EAX.
