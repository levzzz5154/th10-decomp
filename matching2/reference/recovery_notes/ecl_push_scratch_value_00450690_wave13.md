# 0x00450690 (64 bytes) - recovered EXACT

2026-09-19, agent `PoolRegionC`. Region `0x00450690..0x004506CF`, source
`src/script/ecl_push_scratch_value_00450690.cpp`, 64 bytes, in the 55-90 byte
band and outside the wave's reserved areas (`0x443xxx`, `0x448xxx`, `0x449xxx`,
the render batch). Work was done in `/tmp/PoolRegionC/msvc`
(`cp -a matching2/msvc`).

## Disposition

**EXACT 64/64 bytes**, landed as a single-function native-LTCG cluster (first
probe, no iteration):

```sh
python3 matching2/tools/waves/register_cluster.py \
    --project matching2/msvc \
    --layout layout/ltcg/ecl_push_scratch_value_00450690.json --apply
# registered semantic_EclFrame_PushScratchValue_00450690 as ?Push@EclFrame_00450690@@QAEHH@Z
# ltcg_clusters: 266 entries
```

Probe against the maintained tree:

```sh
python3 matching2/tools/matching/probe.py \
    --source src/script/ecl_push_scratch_value_00450690.cpp \
    --project matching2/msvc --output /tmp/PoolRegionC/mainout --show 30
0x00450690      64 bytes  ?Push@EclFrame_00450690@@QAEHH@Z  EXACT
EXACT
```

The JSON report for the same run: `"different_bytes": 0`, no failures, and the
unit's `compiler_kind` is `native-ltcg` with two `/GL` inputs (driver +
layout). `make` was not run here.

Manifest gates:

```text
build_msvc.validate_project: 4425 regions / 2395 units          OK
ltcg_cluster.load_clusters:  266 clusters loaded, none rejected OK
```

Regression check on the one unit that calls this region (it holds the naked
`call asm_ECL_PushScratchValue_00450690`, which the registration leaves bound by
the manifest's `symbols` map at `0x00450690`, so the caller is unaffected):

```sh
python3 matching2/tools/matching/probe.py --source src/script/ecl_core_interpreter.cpp \
    --project matching2/msvc --output /tmp/PoolRegionC/mainout2 --show 30
0x0044e1a0    7020 bytes  _asm_FUN_0044e1a0_0044e1a0                    EXACT
0x0044fdb0     144 bytes  _asm_ECL_ResolveIntOperand_0044fdb0           EXACT
0x0044ff00     124 bytes  ?ECL_ResolveIntValue_0044ff00@@YIHHPAUEclFrame@@HH@Z  EXACT
0x004501b0      30 bytes  _asm_ECL_SetPolarVector_004501b0               EXACT
EXACT
```

The exported body is retail's body byte for byte, nothing masked:

```text
emitted   64 bytes  sha256 5551a3f6c0ffe57d5f2ed8307d38d332e7272f8c66cbc332277ca0fa043a828e
retail    64 bytes  sha256 5551a3f6c0ffe57d5f2ed8307d38d332e7272f8c66cbc332277ca0fa043a828e
body      8b 90 00 10 00 00 03 ca 81 f9 00 10 00 00 7c 04 83 c8 ff c3 56 8d 71 04
          81 fe 00 10 00 00 89 88 00 10 00 00 7d 10 8b b0 04 10 00 00 89 34 01 83
          80 00 10 00 00 04 89 90 04 10 00 00 33 c0 5e c3
```

and `i686-w64-mingw32-objdump -d --no-show-raw-insn` over the extracted
contribution reproduces retail's listing instruction for instruction, offsets
included:

```text
  0: mov 0x1000(%eax),%edx        450690: mov    0x1000(%eax),%edx
  6: add %edx,%ecx                450696: add    %edx,%ecx
  8: cmp $0x1000,%ecx             450698: cmp    $0x1000,%ecx
  e: jl  14                       45069e: jl     0x4506a4
 10: or  $0xffffffff,%eax         4506a0: or     $0xffffffff,%eax
 13: ret                          4506a3: ret
 14: push %esi                    4506a4: push   %esi
 15: lea 0x4(%ecx),%esi           4506a5: lea    0x4(%ecx),%esi
 18: cmp $0x1000,%esi             4506a8: cmp    $0x1000,%esi
 1e: mov %ecx,0x1000(%eax)        4506ae: mov    %ecx,0x1000(%eax)
 24: jge 36                       4506b4: jge    0x4506c6
 26: mov 0x1004(%eax),%esi        4506b6: mov    0x1004(%eax),%esi
 2c: mov %esi,(%ecx,%eax,1)       4506bc: mov    %esi,(%ecx,%eax,1)
 2f: addl $0x4,0x1000(%eax)       4506bf: addl   $0x4,0x1000(%eax)
 36: mov %edx,0x1004(%eax)        4506c6: mov    %edx,0x1004(%eax)
 3c: xor %eax,%eax                4506cc: xor    %eax,%eax
 3e: pop %esi                     4506ce: pop    %esi
 3f: ret                          4506cf: ret
```

## What the region needed

The body is ordinary readable C++; the only thing no declaration can name is the
entry convention. Retail's single call site, in the ECL interpreter
(`0x0044E446`, inside the 7020-byte region `0x0044E1A0`), sets it up with the
frame in **EAX** and the byte count in **ECX**:

```text
44e437: push %ebp
44e438: mov  %esi,%edx
44e43a: call 0x44fdb0            ; returns the count
44e43f: lea  0x8(%esi),%edx      ; edx = &vm->frame
44e442: mov  %eax,%ecx           ; ECX = count
44e444: mov  %edx,%eax           ; EAX = frame
44e446: call 0x450690
```

so the convention is exactly the pair the array-walking context earns (lever 5:
the caller's shape decides the marshalling). The proof that it is not a plain
translation unit's convention is one compile away — the same source compiled
without `/GL` gives 69 bytes:

```text
  0: mov 0x1000(%ecx),%edx     <- this in ECX
  6: mov 0x4(%esp),%eax        <- count on the stack
  ...
 16: ret $0x4
 44: ret $0x4
```

Every instruction inside the two bodies is otherwise the same, so the whole
difference really is the register pair plus the `ret 4`.

The frame layout the landed body pins down (it reads `+0x1000` and `+0x1004`
through the frame pointer) agrees with the three ECL neighbours that were
already recovered:

- `EclFrame_00412a10` in `src/script/ecl_resolve_int_destination_00412a10.cpp`
  has `frame_base` at frame `+0x1004` and the value owner at frame `+0x100C`,
  and returns `frame + frame_base + displacement` — the same expression
  `0x00450070` (`src/script/ecl_resolve_float_destination_00450070.cpp`) emits
  after its `add esi,8`, and the same one `0x00450030` emits.
- `0x004506D0`'s attempt (`ecl_scratch_pop_004506d0_cluster.md`) named the same
  two fields `scratch_offset` / `scratch_value`.

So the ECL interpreter's scratch stack is: the frame object *is* the buffer,
`sp` at `+0x1000`, `frame_base` at `+0x1004`; pushing saves the old frame base
into the buffer at the new sp, then moves the frame base to the old sp. The
object the interpreter passes here is `&vm->frame`, where the vm puts its
variable table at `+0x0004` (valid mask at table `+0x0008`, displacements at
table `+0x0010`) and the frame at `+0x0008`.

## Shapes tried

Only one, and it was exact on the first probe: the faithful body, compiled in a
cluster whose synthetic caller walks an array of frame pointers. The measured
alternative is the plain `/O2` translation unit above — same extent class, wrong
ABI, 69 bytes. No statement reordering, no `volatile`, no base-pointer trick was
needed; nothing about this region is an allocator or scheduler residual.

## Regions this touches

- **The caller, `0x0044E1A0` (7020 bytes, `src/script/ecl_core_interpreter.cpp`)**,
  still an asm region, is now modellable without inventing a convention for this
  call: it can co-compile this landed body as an ABI anchor (levers 1-2) or, if
  it takes the source over, call `Push` directly and get `mov %edx,%eax / mov
  %eax,%ecx`-shaped setup for free. This landing does not by itself unblock it.
- **`0x004506D0` (41 bytes, `src/script/ecl_pop_scratch_value_004506d0.cpp`)** is
  *not* unblocked: `ecl_scratch_pop_004506d0_cluster.md` records its residual as
  the encoding of the pointer step (retail `add ecx,0FFFFFFFCh`, every spelling
  tried emitting `sub ecx,4`). This landing reproduces the same struct and the
  same semantics but adds no new lever for that two-byte difference; the one
  hint it gives is that the register form (`add %edx,%ecx` at `+0x6`) is what the
  compiler picks when the step arrives in a register, not as an immediate.
- **`0x00450030` (58 bytes, `src/script/ecl_resolve_variable_value_00450030.cpp`)**
  and the float resolvers `0x00450070` / `0x0044FE40` / `0x0044FF80` now have a
  second independent measurement of the frame layout they rely on.

## Files

sha256:

```text
3968ee11c955dff0da396ed7e6bbeadc78a0fb17df312b56fc0ec822e8861580  src/script/ecl_push_scratch_value_00450690.cpp
d1e751cf00387a6cb47aee31db3e3e0ffd281be5a48b8284da93db7e8f0ec182  layout/ltcg/ecl_push_scratch_value_00450690.json
8d79b393b70692623e07ae9d3c988b93b31fbdd76dc9211e4bb2b88e04de04e7  layout/ltcg/ecl_push_scratch_value_00450690_context.cpp
```

### `src/script/ecl_push_scratch_value_00450690.cpp`

```cpp
// 0x00450690..0x004506CF: ?ECL_PushScratchValue@@
// Reserve `size` bytes of the interpreter's scratch stack and hand the new
// frame base back. The frame rides in a buffer that starts at the object's own
// address, with the stack pointer at +0x1000 and the frame base at +0x1004;
// the previous frame base is pushed onto the buffer before the frame base
// moves to the old stack pointer. The frame arrives in EAX and the byte count
// in ECX, a convention only a native LTCG link chooses, so this region is
// compiled as a cluster.

struct EclFrame_00450690 {
    unsigned char scratch[0x1000];  // +0x0000
    int sp;                         // +0x1000
    int frame_base;                 // +0x1004
    __declspec(noinline) int Push(int size);
};
typedef char EclFrame_00450690_size_must_fit[sizeof(EclFrame_00450690) == 0x1008 ? 1 : -1];

#pragma code_seg(".text$01push")
int EclFrame_00450690::Push(int size) {
    int old = sp;
    int next = old + size;
    if (next >= 0x1000) {
        return -1;
    }
    sp = next;
    if (next + 4 < 0x1000) {
        *(int*)(scratch + next) = frame_base;
        sp = sp + 4;
    }
    frame_base = old;
    return 0;
}
#pragma code_seg()
```

### `layout/ltcg/ecl_push_scratch_value_00450690.json`

```json
{
  "schema_version": 1,
  "name": "ecl_push_scratch_value_00450690",
  "source": "src/script/ecl_push_scratch_value_00450690.cpp",
  "driver": "layout/ltcg/ecl_push_scratch_value_00450690_context.cpp",
  "headers": [],
  "image_base": "0x00400000",
  "description": "ECL scratch push compiled with native LTCG so the interpreter frame arrives in EAX and the byte count in ECX, as retail's call site in the ECL interpreter does.",
  "functions": [
    {
      "name": "EclFrame_PushScratchValue",
      "symbol": "?Push@EclFrame_00450690@@QAEHH@Z",
      "section": ".text$01push",
      "address": "0x00450690",
      "size": 64,
      "actual_abi": "frame in EAX; byte count in ECX; result in EAX; plain RET"
    }
  ],
  "context": {
    "symbol": "EclPushScratchValueContext@12",
    "section": ".text$03context",
    "address": "0x004506E0",
    "size": 42,
    "description": "Synthetic array-walking caller that establishes the observed register convention; not recovered game code."
  },
  "gaps": [
    {
      "section": ".text$00layout",
      "address": "0x00401000",
      "size": 325264
    },
    {
      "section": ".text$02layout",
      "address": "0x004506D0",
      "size": 16
    }
  ],
  "constants": [],
  "absolute_symbols": []
}
```

### `layout/ltcg/ecl_push_scratch_value_00450690_context.cpp`

```cpp
// Compiler context only; never selected as recovered game code.
#include "../../src/script/ecl_push_scratch_value_00450690.cpp"

#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) int __stdcall EclPushScratchValueContext(
        EclFrame_00450690** items, int size, int count) {
    int last = 0;
    while (count--) {
        last = (*items++)->Push(size);
    }
    return last;
}
#pragma code_seg()
```

## Tooling notes for the next reader

- The function extent is 16-byte aligned (`0x450690 + 0x40 = 0x4506D0`), so the
  usual "context at `align16(function end)`, gap covers the difference" layout
  degenerates to a **zero-length gap** and `layout.cpp` then fails with C2466.
  This layout therefore puts the context 16 bytes past the end and declares
  `.text$02layout` as 16 bytes; all three boundaries stay 16-aligned, so section
  alignment cannot shift anything either way.
- The context's declared `size` (42) is the emitted extent and is validated like
  a selected function's, so it has to be right before the first probe — or read
  back from `cluster.map`'s `.text$03context` size column afterwards.
- The driver includes the source, so the cluster's object must emit *only*
  `Push`; the layout's head gap is `0x450690 - 0x401000`.
