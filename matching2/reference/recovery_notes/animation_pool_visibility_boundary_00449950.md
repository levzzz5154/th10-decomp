# Animation pool allocation and entity initialization: measured blockers

2026-09-13 follow-up to
[`animation_pool_initializer_followup_00401de0_00449950.md`](animation_pool_initializer_followup_00401de0_00449950.md).
Both functions are still assembly. This note records what the isolated cluster
now reproduces, what it cannot, and the compiler-visibility boundary that
separates them, so the next attempt starts from the measurements instead of the
old failures.

## What the cluster now reproduces

A schema-1 batch in `matching2/build/recovery-lab/project` compiles
`AnimationPool::Allocate` (0x00449950, 161 bytes) and the entity initializer
`InitializeAnimationEntity` (0x00401DE0, 273 bytes, entity in EDX) with one
synthetic context shaped like the real retail callers: the pool comes from the
manager global and both functions are called in a loop.

- The allocator's **entry convention is reproduced**: with that context the
  native link emits `mov eax, [esi+0x3ad068]` and the rest of the non-heap path
  byte-for-byte, i.e. ESI manager exactly as all 74 retail callers assume
  (`mov esi, dword_491C10; call 0x449950`).
- Its **cursor arithmetic, busy-byte tests, claim path and tail are exact**:
  `inc eax / and eax,0x80000fff / jns / dec eax / or eax,0xfffff000 / inc eax`
  for `(slot + 1) % 4096`, the `lea` of `&objects[slot]`, and the final
  `mov eax, edi; pop edi; ret`.

## The remaining eight bytes

Retail's heap fallback is:

```asm
4499a7  test eax,eax
4499a9  je   4499bd
4499ab  mov  ecx,eax          ; this for Entity::Entity()
4499ad  call 0x402050
4499b2  mov  edx,eax          ; argument for the initializer
4499b4  mov  edi,eax          ; the object variable's home
4499b6  call 0x401de0
4499bb  jmp  4499d2
4499bd  xor  eax,eax          ; null result
4499bf  mov  edx,eax
4499c1  mov  edi,eax
4499c3  call 0x401de0
```

`new Entity` plus `InitializeAnimationEntity(0, object)` compiles to the same
control flow, but the compiler keeps `object` in **EDX** and drops both
`mov edi,eax` copies and the `push/pop edi`: 153 bytes instead of 161. The
value only has to survive the initializer call, and the initializer's body
never writes EDX, so the register is both free and provably preserved.

Measured dependence on exactly that knowledge:

| initializer as seen by the allocator's module | allocator extent | object home |
| --- | ---: | --- |
| definition compiled in the same `/GL` scope (current) | 153 | EDX |
| definition compiled in the same scope, but with a diagnostic call that clobbers EDX | 155 | callee-saved |
| declaration only; symbol bound absolutely, no IL | 163 | EDI (but `xor ecx,ecx` for the dead fastcall argument and `mov edx,edi` instead of `mov edx,eax`) |

Retail's shape needs *both* halves at once: the call site must not materialise
ECX (so the compiler must know the first fastcall register is dead, which only
IL visibility provides) and the object must still be kept in a callee-saved
register (so the caller must *not* know EDX is preserved). Retail's own build
gets that combination from its `/LTCG` module split: the initializer lands in
another module, its convention is recorded as "one argument in EDX" with no
ECX setup at any of its ten call sites, and its clobber set is unknown to the
allocator. That boundary is real in the image:

- every call site is `mov edx,<entity>; call 0x401de0` with no other setup
  (0x00401DC0, 0x00404F30, 0x0042B4D0, 0x0043E738, 0x00445900, 0x00448BB0 and
  the allocator's two paths),
- no C++ declaration on MSVC 13.10 puts a lone pointer argument in EDX: a
  `__fastcall` first register is ECX, and a stack-passed first argument (empty
  struct, float, struct by value) moves the pointer to ECX as well (measured).

The cluster machinery compiles *every* input of a batch with `/GL`, so it can
express either side of that boundary but not both. Reproducing the allocator
needs a visibility control the tool does not have (a native object inside the
batch, or a recorded cross-module convention). This is a boundary of the
mechanism, not of the source shape: the same source is exact everywhere except
the two `mov edi,eax` copies and the EDI push/pop.

## The initializer's own two sites

The 273-byte initializer reaches the correct extent with the aggregate
`PositionBits` source and matches everything except two scheduling sites:

1. after the `rep stos`, retail issues both spill reloads before the first
   store (`mov ecx,[esp+0x10]`, `mov eax,[esp+0x1c]`, then
   `mov [esi],ebx`, `mov [esi+4],ebp`, `mov [edx+0x20],ecx`, `mov [esi+8],eax`);
   the candidate stores first and loads at each use.
2. retail keeps `pop edi` until 0x00401EAD, after the end-marker/`previous_frame`
   stores; the candidate restores EDI at 0x00401E97.

Eight source shapes were probed against those sites: the aggregate restore in
the retail store order, in ascending order, and bucket-first (bucket-first gets
the first reload in place and leaves 69 differing bytes instead of 76), plus
explicit "read both spill slots into locals first" forms, a scalar
`unsigned int` triple and a struct copy. The read-first shapes compile back to
the interleaved form because both reloads come from the compiler's own spill
slots, which it may sink to their uses; the scalar triple changes the prologue
and spills (271 bytes). These are scheduler choices, not source semantics.

## What would move this

- Recover the allocator in a batch whose initializer is *native* (no IL) while
  the call site keeps the dead-argument form. That needs the dead fastcall
  argument eliminated without IL, i.e. either a new cluster field for native
  inputs plus a convention record, or the initializer body being compiled
  through a path that records "one EDX argument" for its callers.
- Or find the two `mov edi,eax` copies from the caller side: any construct that
  keeps a second value live in EDX across the call would force the same home
  retail chose, while leaving the call site untouched.

Diagnostics are retained under `matching2/build/recovery-lab/project` and the
iteration harness at `matching2/build/pipeline-lab/lab.py`
(`--project matching2/build/recovery-lab/project --manifest layout/ltcg/animation_pool.json`).
