# Animation-manager create families — 1,404 bytes in sixteen regular regions

2026-09-18. A shape screen over the remaining game-code assembly (normalised
instruction text, families of two or more) found four *regular* families in the
animation manager, all still assembly:

| family | members | bytes each | shared callees | differing call |
| --- | --- | ---: | --- | --- |
| A | `0x00409E50`, `0x0040C480`, `0x0040C4D0`, `0x004243F0` | 65 | `AnimationManager_Find_004491C0` | none |
| B | `0x00448D00`, `0x00448E30`, `0x00448F60`, `0x00449090` | 73 | `FUN_00449950`, `FUN_00449870` | `RegisterPrimaryBack_004489D0` / `…PrimaryFront_00448A50` / `…SecondaryBack_00448AC0` / `…SecondaryFront_00448B40` |
| C | `0x00448D50`, `0x00448E80`, `0x00448FB0`, `0x004490E0` | 95 | `FUN_00449950`, `AnimationObject_LoadScript_0043E710` | the same four register calls |
| D | `0x00448DB0`, `0x00448EE0`, `0x00449010`, `0x00449140` | 118 | `FUN_00449950`, `AnimationObject_LoadScript_0043E710` | the same four register calls |

**1,404 bytes across sixteen regions**, and inside each family the four members
have *identical* normalised instruction text — the only difference is which
register helper the tail calls. One source shape per family, instantiated four
times with a different final call, therefore recovers a whole family at once.

## Why these need the cluster path

Every callee is assembly with a non-standard convention (`FUN_00449950`,
`FUN_00449870`, the four `Register*` helpers, `LoadScript`), so the call sites
carry registers no plain translation unit can set up; the registry
(`animation_manager_cluster_0043e460_00449950.md`) already records that region's
convention work. With the cluster machinery the shape is attractive because the
four instantiations differ by exactly one bound call target, so a single
validated model should land each family as a batch — the approach the recent
`copy_block`, `destroy_owned` and accessor batches used.

Family A is the cheapest entry point: 65 bytes, one callee, no variants — the
body reads `[eax]`, then `data_00491C10`, pushes the object, calls
`AnimationManager_Find_004491C0`, tests the result, and tails into the usual
`test eax,eax` shape.

## Family A call-site anatomy (decoded, not yet expressible)

Full listing of `0x00409E50` (65 bytes; the sibling members differ only in the
frame constant — `1`, `2`, …):

```
8b 00        mov eax,[eax]                  ; the object arrives in EAX; load its +0
8b 15 ..     mov edx,[data_00491c10]        ; argument 2 = the animation manager
50           push eax                       ; argument 3 = that loaded pointer
e8 ..        call AnimationManager_Find_004491C0
85 c0        test eax,eax
74 ..        je end
8b 50 18     mov edx,[eax+18h]              ; found->field_18
85 d2        test edx,edx
b9 01 00..   mov ecx,1                      ; the frame constant
66 89 88 ..  mov [eax+304h],cx              ; found->field_304 = frame
75 ..        jne end
8b 40 14     mov eax,[eax+14h]              ; the child chain head
85 c0        test eax,eax
74 ..        je end
             loop:                          ; walk the chain downward
8b 10        mov edx,[eax]
66 89 8a ..  mov [edx+304h],cx
8b 40 04     mov eax,[eax+4]
85 c0        test eax,eax
75 ..        jne loop
c3           ret
```

Two facts matter for whoever picks this up:

- The callee is reached with **EDX = the manager, the object on the stack, and
  ECX left as whatever the caller held** — the compiler never initialises ECX.
  A C++ call site always sets the first `__fastcall` argument, so a plain
  translation unit cannot reproduce this call; either the cluster context has to
  establish ECX (so the callee's first parameter is already live) or the region
  needs an asm shim at the call.
- The only per-member difference in the family is the immediate moved into `ECX`
  before the `mov [eax+304h],cx` store — `1` for `0x00409E50`, `2` for
  `0x0040C480`, and so on — so a single model with one constant parameter covers
  all four members.

## Families B/C/D call shapes: arguments in ESI/EDI, so they need multi-function clusters

Checked after the `0x00449590`/`0x004495E0` pair landed with the fastcall-binding
trick (declaring a callee `extern "C" __fastcall` and binding its mangled name in
the layout reproduces retail's ECX/EDX/stack call site exactly). That trick does
not reach these families. `0x00448D00`, family B:

```
56            push esi
8b 35 ..      mov esi,[data_00491c10]
e8 ..         call FUN_00449950          ; argument is in ESI - not a parameter register
8b 4c 24 10   mov ecx,[esp+10h]
8b d8         mov ebx,eax
...
51            push ecx
8b 4c 24 10   mov ecx,[esp+10h]
81 ce ..      or esi,40000000h
53            push ebx
89 43 20      mov [ebx+20h],eax
89 b3 ..      mov [ebx+35Ch],esi
e8 ..         call FUN_00449870          ; ECX plus two stack arguments
...
8b c7         mov eax,edi                ; the object lives in EDI
```

Three obstructions, each beyond a single-function source: `FUN_00449950` takes its
argument in **ESI**, `FUN_00449870` takes **ECX plus two stack arguments** (no
prototype produces that - `__fastcall` gives ECX/EDX/stack), and the object
itself is carried in **EDI**. Expressing these therefore needs a *multi-function*
cluster in which the callees are modelled in the same section so the whole-program
pass assigns those registers - the `load_archive_file` arrangement - rather than
the single-function clusters used for the accessors and the flag pair.

## The rest of the Find-calling crop lives in registers C++ cannot set

Fifty assembly files call `AnimationManager_Find_004491c0`. Screening them for
regions with at most one other callee and no x87 yielded fourteen; of those, only
the `0x00449590`/`0x004495E0` pair has an expressible call shape. The others
live-in on registers no prototype provides:

- `0x00449470`, `0x00449210`, `0x00409E50`, `0x0040C480`, `0x0040C4D0`,
  `0x004243F0`: the call leaves **ECX unset** and pushes EAX, and the body then
  reads **SI** (`mov word [eax+304h],si`), a caller-carried frame value;
- `0x004492F0`, `0x00449250`, `0x004497D0`: read **ESI**/`[esp+4]`-plus-ESI;
- `0x0042C6D0`, `0x0042C770`: index off **EDI+ESI**/`EAX+ECX` live-in values.

The pair landed because its call is `Find(field, manager, field)`: the value is
already in ECX as argument 1 and is pushed again as argument 3, which the
`extern "C" __fastcall` declaration plus an `@...@12` relative-code binding
reproduces exactly. Every other member of this crop needs a convention with two
or more live-in registers, i.e. a multi-function cluster.

## The select-sprite trio (0x449670 / 0x4496A0 / 0x4496D0)

Screening for the landed pair's exact call shape (`mov ecx,[eax]` → `mov
edx,[data_00491C10]` → `push ecx` → `call Find`) found three more regions.
`0x00449670` **landed** (36 bytes; commit `7f06edd`) with two bound callees.

- `0x004496D0` (36 bytes): reaches retail's exact extent with the same two-callee
  binding, but the two argument loads come out in the opposite order - retail
  `mov ecx,[esp+4]` then `mov edx,[eax+308h]`, the model the reverse (11 differing
  bytes, first at 0x13). Swapping the arguments in the source flips the registers
  as well (4 differing, first at 0x13), so the difference is the scheduler's
  ordering of two independent loads, not the argument mapping.
- `0x004496A0` (34 bytes): two stack parameters forwarded to the same callee; the
  cluster emits 36 bytes with 13 differing - the entry convention for a
  two-stack-argument member differs.
