# 0x00405040 + 0x004050A0: the word-colour record pair, both landed as native-LTCG clusters

2026-09-19. Two regions, verified independently, in one throwaway copy
(`/tmp/wordcolor/msvc`). Both are **EXACT**:

```
0x00405040      94 bytes  ?Initialize@WordColor_00405040@@QAEPAU1@MMMMMM@Z  EXACT
0x004050a0      45 bytes  ?UpdateChannels@WordColor_004050a0@@QAEXXZ  EXACT
```

The two probe commands were

```
python3 matching2/tools/matching/probe.py --source src/game/recovery_initialize_word_color_00405040.cpp \
        --project /tmp/wordcolor/msvc --output /tmp/wordcolor/outF1 --show 30
python3 matching2/tools/matching/probe.py --source src/unidentified/unassigned_004050a0.cpp \
        --project /tmp/wordcolor/msvc --output /tmp/wordcolor/outF3 --show 30
```

and the byte equality was confirmed a second time by reading the region straight
out of each cluster's own `cluster.exe` of that same run (identical to the
oracle in both cases). The extracted contributions are exactly one function
each: `bodies.obj` for 0x405040 is a single 0x5E-byte `.r000001` holding
`?Initialize@...`, and for 0x4050A0 a single 0x2D-byte one holding
`?UpdateChannels@...`; the synthetic contexts never enter the outer link.

The two regions are consecutive in `.text` separated by two bytes of padding
(0x40509E), and they operate on **the same 0x1C-byte record**: six 32-bit
components at +0, +4, +8, +0xC, +0x10, +0x14 and four derived channel bytes at
+0x18..+0x1B. 0x405040 fills the record from six arguments and then derives the
bytes; 0x4050A0 re-derives the bytes from the four float components already in
the record. The two models share that struct layout, and nothing else.

---

# Region 1 - 0x00405040, 94 bytes, `Recovery_InitializeWordColor`

## What the region is

Retail, in order. Every `E8` here is `__ftol2` at 0x00463B2C:

```text
8B 44 24 04        mov  eax,[esp+4]          ; component 0
D9 44 24 0C        fld  dword ptr [esp+0Ch]  ; first conversion operand
8B 4C 24 08        mov  ecx,[esp+8]
8B 54 24 0C        mov  edx,[esp+0Ch]
89 06              mov  [esi],eax
8B 44 24 10        mov  eax,[esp+10h]
89 4E 04           mov  [esi+4],ecx
8B 4C 24 14        mov  ecx,[esp+14h]
89 56 08           mov  [esi+8],edx
8B 54 24 18        mov  edx,[esp+18h]
89 46 0C           mov  [esi+0Ch],eax
89 4E 10           mov  [esi+10h],ecx
89 56 14           mov  [esi+14h],edx
E8 ..              call __ftol2             ; (unsigned char)component 2
D9 44 24 10        fld  dword ptr [esp+10h] ; the *next* operand, after the call
88 46 18           mov  [esi+18h],al
E8 ..              call __ftol2
D9 44 24 14        fld  dword ptr [esp+14h]
88 46 19           mov  [esi+19h],al
E8 ..              call __ftol2
D9 44 24 18        fld  dword ptr [esp+18h]
88 46 1A           mov  [esi+1Ah],al
E8 ..              call __ftol2
88 46 1B           mov  [esi+1Bh],al
8B C6              mov  eax,esi
C2 18 00           ret  18h
```

So: six 32-bit arguments at `[esp+4]`..`[esp+18h]`, the record arriving in
**ESI**, the record returned in EAX, and `ret 18h` - a member function whose
`this` the whole-program pass moved from ECX to ESI. The stores run in ascending
address order with the loads software-pipelined (load component *n* then store
component *n-1*), the first conversion's `fld` is hoisted above every store, and
each later `fld` is scheduled between the preceding `call` and its `al` store.
That schedule is what a plain "six stores, then four casts" body produces; none
of it needed steering.

The caller, `CALL 0x00405040` at **0x00403F40** inside `region 0x00403C80`
(asm, `src/game/event_script_runtime.cpp`), pushes six values - the low dword at
`[esp+4]` is taken raw from `[edi+0x18]`, the next four are `(float)(byte)`
conversions of `[edi+0x10..0x13]` and the last is `[edi+0x14]` raw - and keeps
the 0x1C-byte destination in ESI, which is exactly the retail convention here.
Those arguments are therefore all **floats as far as this region's own code is
concerned**, and the two leading ones are stored without any conversion.

## The model (verbatim)

```cpp
// 0x00405040 (94 bytes): initialise a colour/word record from six float
// components and re-derive its four packed channel bytes.
//
// Retail, in order (D9/D8 are the x87 pair, E8 the __ftol2 conversion):
//
//   8B 44 24 04      mov  eax,[esp+4]        ; component 0
//   D9 44 24 0C      fld  dword ptr [esp+0Ch] ; first conversion operand
//   8B 4C 24 08      mov  ecx,[esp+8]
//   8B 54 24 0C      mov  edx,[esp+0Ch]
//   89 06            mov  [esi],eax
//   ...              the remaining five components, addresses ascending
//   E8 ..            call __ftol2             ; (unsigned char)component 2
//   D9 44 24 10      fld  dword ptr [esp+10h]
//   88 46 18         mov  [esi+18h],al
//   ...              components 3, 4, 5 -> [esi+19h], [esi+1Ah], [esi+1Bh]
//   8B C6            mov  eax,esi
//   C2 18 00         ret  18h
//
// The record arrives in ESI and all six components are on the stack, so the
// member is compiled as a native LTCG cluster; the arguments are floats (an
// integer first parameter makes the whole-program pass take it in EAX and the
// region then emits ret 14h).
#pragma code_seg(".text$01wordcolor")
struct WordColor_00405040 {
    float f_00;
    float f_04;
    float f_08;
    float f_0c;
    float f_10;
    float f_14;
    unsigned char b_18;
    unsigned char b_19;
    unsigned char b_1a;
    unsigned char b_1b;

    __declspec(noinline) WordColor_00405040* Initialize(float a0, float a1, float a2,
                                                       float a3, float a4, float a5);
};

WordColor_00405040* WordColor_00405040::Initialize(float a0, float a1, float a2,
                                                   float a3, float a4, float a5) {
    f_00 = a0;
    f_04 = a1;
    f_08 = a2;
    f_0c = a3;
    f_10 = a4;
    f_14 = a5;
    b_18 = (unsigned char)a2;
    b_19 = (unsigned char)a3;
    b_1a = (unsigned char)a4;
    b_1b = (unsigned char)a5;
    return this;
}
#pragma code_seg()
```

## The driver (verbatim, `layout/ltcg/word_color_00405040_context.cpp`)

```cpp
// Compiler context only; never selected as recovered game code.
// The array-walking caller is what makes the whole-program pass keep the
// record in ESI while leaving all six float arguments on the stack.
#include "../../src/game/recovery_initialize_word_color_00405040.cpp"

#pragma code_seg(".text$03context")
int __stdcall WordColorCompilerContext(WordColor_00405040** items, int count, float a0,
                                       float a1, float a2, float a3, float a4, float a5) {
    while (count--) {
        WordColor_00405040* item = *items++;
        item->Initialize(a0, a1, a2, a3, a4, a5);
    }
    return 0;
}
#pragma code_seg()
```

## The layout (verbatim, `layout/ltcg/word_color_00405040.json`)

```json
{
  "schema_version": 1,
  "name": "word_color_00405040",
  "source": "src/game/recovery_initialize_word_color_00405040.cpp",
  "driver": "layout/ltcg/word_color_00405040_context.cpp",
  "headers": [],
  "image_base": "0x00400000",
  "description": "Colour/word record initialisation compiled with native LTCG so the record stays in ESI and all six components stay on the stack.",
  "functions": [
    {
      "name": "WordColor_00405040_Initialize",
      "symbol": "?Initialize@WordColor_00405040@@QAEPAU1@MMMMMM@Z",
      "section": ".text$01wordcolor",
      "address": "0x00405040",
      "size": 94,
      "actual_abi": "record in ESI; six float arguments at [ESP+4]..[ESP+18h]; result in EAX; RET 24"
    }
  ],
  "context": {
    "symbol": "?WordColorCompilerContext@@YGHPAPAUWordColor_00405040@@HMMMMMM@Z",
    "section": ".text$03context",
    "address": "0x004050B0",
    "size": 79,
    "description": "Synthetic array-walking caller that establishes the observed register convention; not recovered game code."
  },
  "gaps": [
    {
      "section": ".text$00layout",
      "address": "0x00401000",
      "size": 16448
    },
    {
      "section": ".text$02layout",
      "address": "0x0040509E",
      "size": 18
    }
  ],
  "constants": [],
  "roots": [],
  "absolute_symbols": [
    {
      "symbol": "__ftol2",
      "address": "0x00463B2C",
      "kind": "relative_code"
    },
    {
      "symbol": "__fltused",
      "address": "0x00000000",
      "kind": "metadata"
    }
  ]
}
```

## Shapes tried

| shape | emitted | result |
|---|---:|---|
| `Initialize(int a0, float a1..a5)`, member, returns `this`, array-walking context | 90, `ret 14h` | 4 bytes short. The pass moved `a0` into **EAX** (`mov [esi],eax` reads a live-in) and dropped it from the stack, so `ret 14h`. Every other instruction - the four `__ftol2` calls, the hoisted first `fld`, the pipelined loads and stores, `mov eax,esi` - already had retail's shape. |
| `Initialize(float a0..float a5)`, member, returns `this`, same context | **94** | **EXACT** first try. |

The `int` first parameter is the only trap: an all-`float` parameter list keeps
all six arguments on the stack, which is what retail has. A free
`X* Init(X* out, ...)` form was not needed - the member form took ESI for `this`
straight away with the same array-walking context shape the landed
`FrameTimer::Advance` (`this` in ESI, float at `[ESP+4]`, `ret 4`) uses.

---

# Region 2 - 0x004050A0, 45 bytes, `UpdateChannels`

## What the region is

```text
D9 46 08           fld  dword ptr [esi+8]
E8 ..              call __ftol2
D9 46 0C           fld  dword ptr [esi+0Ch]
88 46 18           mov  [esi+18h],al
E8 ..              call __ftol2
D9 46 10           fld  dword ptr [esi+10h]
88 46 19           mov  [esi+19h],al
E8 ..              call __ftol2
D9 46 14           fld  dword ptr [esi+14h]
88 46 1A           mov  [esi+1Ah],al
E8 ..              call __ftol2
88 46 1B           mov  [esi+1Bh],al
C3                 ret
```

`this` in ESI, no arguments, no result. It is the tail half of region 1's work,
reading the components from the record instead of from the stack, with the same
load/conversion/store interleave. The region is **unreferenced**: no `E8`/`E9`
rel32, no pushed address and no data pointer in `.text`, `.rdata` or `.data`
names 0x004050A0 (only 0x00403F40 names 0x00405040), so no caller pins the
convention and the native-LTCG cluster is the only route - the same situation
`bounds_from_center_004285f0_cluster.md` documents.

## The model (verbatim)

```cpp
// 0x004050A0 (45 bytes): re-derive the packed channel bytes from the record's
// four float components; the same record 0x00405040 initialises.
//
// Retail, in order:
//
//   D9 46 08      fld  dword ptr [esi+8]
//   E8 ..         call __ftol2
//   D9 46 0C      fld  dword ptr [esi+0Ch]
//   88 46 18      mov  [esi+18h],al
//   E8 ..         call __ftol2
//   D9 46 10      fld  dword ptr [esi+10h]
//   88 46 19      mov  [esi+19h],al
//   E8 ..         call __ftol2
//   D9 46 14      fld  dword ptr [esi+14h]
//   88 46 1A      mov  [esi+1Ah],al
//   E8 ..         call __ftol2
//   88 46 1B      mov  [esi+1Bh],al
//   C3            ret
//
// Each load is scheduled after the preceding conversion and before its store,
// which is what the statement order below produces.  The record arrives in ESI
// and the function takes no arguments, so this too is a native LTCG cluster.
// The region has no reference anywhere in the image: no E8/E9 rel32, no pushed
// address and no data pointer names 0x004050A0.
#pragma code_seg(".text$01channels")
struct WordColor_004050a0 {
    float f_00;
    float f_04;
    float f_08;
    float f_0c;
    float f_10;
    float f_14;
    unsigned char b_18;
    unsigned char b_19;
    unsigned char b_1a;
    unsigned char b_1b;

    __declspec(noinline) void UpdateChannels();
};

void WordColor_004050a0::UpdateChannels() {
    b_18 = (unsigned char)f_08;
    b_19 = (unsigned char)f_0c;
    b_1a = (unsigned char)f_10;
    b_1b = (unsigned char)f_14;
}
#pragma code_seg()
```

## The driver (verbatim, `layout/ltcg/word_color_channels_004050a0_context.cpp`)

```cpp
// Compiler context only; never selected as recovered game code.
// The array-walking caller is what makes the whole-program pass keep the
// record in ESI.
#include "../../src/unidentified/unassigned_004050a0.cpp"

#pragma code_seg(".text$03context")
int __stdcall WordColorRefreshCompilerContext(WordColor_004050a0** items, int count) {
    while (count--) {
        WordColor_004050a0* item = *items++;
        item->UpdateChannels();
        item->UpdateChannels();
    }
    return 0;
}
#pragma code_seg()
```

## The layout (verbatim, `layout/ltcg/word_color_channels_004050a0.json`)

```json
{
  "schema_version": 1,
  "name": "word_color_channels_004050a0",
  "source": "src/unidentified/unassigned_004050a0.cpp",
  "driver": "layout/ltcg/word_color_channels_004050a0_context.cpp",
  "headers": [],
  "image_base": "0x00400000",
  "description": "Colour/word channel-byte refresh compiled with native LTCG so the record stays in ESI.",
  "functions": [
    {
      "name": "WordColor_004050a0_UpdateChannels",
      "symbol": "?UpdateChannels@WordColor_004050a0@@QAEXXZ",
      "section": ".text$01channels",
      "address": "0x004050A0",
      "size": 45,
      "actual_abi": "record in ESI; plain RET"
    }
  ],
  "context": {
    "symbol": "?WordColorRefreshCompilerContext@@YGHPAPAUWordColor_004050a0@@H@Z",
    "section": ".text$03context",
    "address": "0x004050E0",
    "size": 42,
    "description": "Synthetic array-walking caller that establishes the observed register convention; not recovered game code."
  },
  "gaps": [
    {
      "section": ".text$00layout",
      "address": "0x00401000",
      "size": 16544
    },
    {
      "section": ".text$02layout",
      "address": "0x004050CD",
      "size": 19
    }
  ],
  "constants": [],
  "roots": [],
  "absolute_symbols": [
    {
      "symbol": "__ftol2",
      "address": "0x00463B2C",
      "kind": "relative_code"
    },
    {
      "symbol": "__fltused",
      "address": "0x00000000",
      "kind": "metadata"
    }
  ]
}
```

Note the context size in that layout is **42** (`0x2A`), read back from the
link map; a first guess of 38 makes the loader reject the cluster with
"function is not its entire declared compiler contribution:
?WordColorRefreshCompilerContext@@...". Everything else landed first try,
including the two-call body in the context - a single call suffices to keep the
callee out of line, but the doubled call is the shape the landed
`clear_rotation_x`/`frame_timer` contexts use and it is the shape that was
verified here.

---

# Region 3 (NOT attempted) - 0x004055C0, 84 bytes, `Recovery_InstallPairSetFlags`

It does **not** share region 1's shape, so it was left alone as instructed. It
is a scheduler-callback installer, not a record filler:

```text
53 / 57 / 68 40 58 40 00 / E8 ..   push esi; push edi; push 0x405840; call 0x449ED0
8B F0                              mov  esi,eax
83 4E 04 02                        or   dword ptr [esi+4],2
A1 E4 1B 49 00                     mov  eax,[0x491BE4]
50                                 push eax
BF 11 00 00 00                     mov  edi,0x11
89 5E 20                           mov  [esi+0x20],ebx
E8 ..                              call 0x449AE0
68 50 58 40 00                     push 0x405850
89 5E 08                           mov  [ebx+8],esi
E8 ..                              call 0x449ED0
8B F0                              mov  esi,eax
83 4E 04 02                        or   dword ptr [esi+4],2
8B 0D E4 1B 49 00                  mov  ecx,[0x491BE4]
51                                 push ecx
BF 22 00 00 00                     mov  edi,0x22
89 5E 20                           mov  [esi+0x20],ebx
E8 ..                              call 0x449B70
5F / 89 5E 0C / 33 C0 / 5E / C3    pop edi; mov [ebx+0xC],esi; xor eax,eax; pop esi; ret
```

* ABI: the receiver is in **EBX** (live-in, never saved), there are no
  arguments, the result is 0 in EAX, plain `ret`. That is a cluster-shaped
  region, but with an EBX entry rather than ESI.
* `0x00449ED0` is `SchedulerCallback_Create` (`@4`, already landed in
  `src/game/scheduler.cpp`): it `malloc(0x24)`s, zeroes +0/+8/+0xC/+0x10/+0x18/+0x1C,
  sets +0x14 = self, +8 = its argument and `flags |= 1` at +4. Here it is called
  with the addresses of the two task routines `0x00405840` and `0x00405850`,
  and the caller then adds `flags |= 2` and sets `owner` at +0x20 to its own
  receiver.
* `0x00449AE0`/`0x00449B70` are the landed `Scheduler_RegisterPrimary` /
  `Scheduler_RegisterSecondary` (`src/game/scheduler_tasks.cpp`). Their private
  convention at this call site is receiver in **ESI**, one stack argument (the
  value of the global at 0x00491BE4) and a third in **EDI** - and EDI is
  genuinely read by the callee (`mov %edi,(%esi)` at 0x00449B18), so 0x11 /
  0x22 are real arguments, not dead stores.
* Because those callees must be visible to the same `/LTCG` link, an attempt
  would have to be merged into the already-registered scheduler cluster layouts
  as `additional_sources` - i.e. it is a coordination job as much as a
  modelling job, and it belongs with whoever holds `src/game/scheduler.cpp`
  and `src/game/scheduler_tasks.cpp`.

---

# Integration

**No header edit is needed for either landed region, and no `include/` change at
all.** Per region the cutover is:

| region | what to apply |
|---|---|
| 0x00405040 | rewrite `src/game/recovery_initialize_word_color_00405040.cpp` with the source above; add `layout/ltcg/word_color_00405040.json` and `layout/ltcg/word_color_00405040_context.cpp`; register the layout (it rewrites the region record to `semantic_WordColor_00405040_Initialize_00405040` = `?Initialize@WordColor_00405040@@QAEPAU1@MMMMMM@Z`, keeps `previous_record`, and appends `layout/ltcg/word_color_00405040.json` to `ltcg_clusters`). |
| 0x004050A0 | rewrite `src/unidentified/unassigned_004050a0.cpp` with the source above; add `layout/ltcg/word_color_channels_004050a0.json` and `layout/ltcg/word_color_channels_004050a0_context.cpp`; register likewise (`semantic_WordColor_004050a0_UpdateChannels_004050a0`). |

Neither source includes anything, so both layouts carry `"headers": []` and
there is no shared struct header to add: the 0x1C-byte record is declared in
each region's own source file, under the two different struct names the
existing naked sources already had.

Two things the integration must leave alone:

* The asm caller at 0x00403F40 keeps calling `asm_Recovery_InitializeWordColor_00405040`
  (`src/game/event_script_runtime.cpp`, region 0x00403C80, via
  `include/asm_symbols.hpp`). That spelling is bound absolutely in the
  manifest's `symbols` map (`"_asm_Recovery_InitializeWordColor_00405040" ->
  "0x00405040"`, plus the `@24` spellings used by
  `src/game/recovery_leaves.cpp` and `src/game/recovery_create_fixed_state_004056b0.cpp`),
  and those entries must stay, or the caller's rel32 loses its target. The
  landed `recovery_scale_color_00404da0` / `embedded_timer_reset_004050d0`
  flips work the same way.
* `_asm_unassigned_004050a0` is **not** in the `symbols` map and nothing
  references it (no caller, no data pointer), so the manifest record at
  0x004050A0 can be flipped without adding an alias.

Both layouts bind `__fltused` as a metadata symbol at 0x00000000 and `__ftol2`
as `relative_code` at 0x00463B2C; without the `__fltused` binding the link
stops at `unresolved external symbol __fltused`, exactly as the landed
floating-point layouts warn.

## Tool pitfall worth one line

`matching2/tools/waves/cluster_attempt._map_section` and `_map_offset` match the
link map with `[0-9A-F]{8}`, but `link.exe` writes the *length* column in
lowercase hex (`0000005aH .text$01accessor`). For any function whose emitted
length contains a lowercase digit the two helpers return `None`, the adaptive
retry silently no-ops and the only symptom is
`function <name> extent is outside a MAP CODE contribution` with `size=None`.
Two fixes, both in this session's sweep driver: accept `[0-9A-Fa-f]`, and make
`_map_offset` read the *offset* column (`([0-9A-Fa-f]{8})\s+[0-9A-Fa-f]{8}H\s+<name>`)
rather than the length column - as written it returns the same value as
`_map_section`, so the context-address correction would write a bogus address if
it ever fired.
