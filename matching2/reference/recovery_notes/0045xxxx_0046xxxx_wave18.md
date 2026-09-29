# 0x45xxxx / 0x46xxxx sweep — wave 18

2026-09-19. The block is every owner-less `asm` region in `0x00450000..0x0046FFFF`
that the fixed owner filter newly admits: 176 regions, 12,136 bytes, from
`0x004501D0` to `0x004659E0`. **17 landed (298 bytes)**; 17 attempted and dropped
with the delta below; 142 untouched, grouped at the end by what blocks them.

Everything here was measured in a throwaway copy (`/tmp/VeinBlock456/msvc`) with
`matching2/tools/matching/probe.py --source <src> --project /tmp/VeinBlock456/msvc
--output /tmp/VeinBlock456/out --show 30`, and landed through
`matching2/tools/waves/promote_scratch.py --scratch /tmp/VeinBlock456/msvc
--address <addr> --apply` (which also rewrote `translation_units`). No build was
run here; the probe is the byte gate.

## Landed — 17 regions, 298 bytes

```
004501D0        1 bytes  _unassigned_004501d0@0            EXACT
00453259       20 bytes  _unassigned_00453259              EXACT
0045326D       16 bytes  _unassigned_0045326d              EXACT
0045370E       13 bytes  _unassigned_0045370e              EXACT
0045771D       15 bytes  _unassigned_0045771d              EXACT
0045FE75        9 bytes  _unassigned_0045fe75              EXACT
00460C1E        8 bytes  _unassigned_00460c1e              EXACT
00462363       14 bytes  ?Myptr@StringBase_00462363@@QBEPBDXZ EXACT
004658C0       36 bytes  _unassigned_004658c0              EXACT
00465910       36 bytes  _unassigned_00465910              EXACT
00465940       12 bytes  _unassigned_00465940              EXACT
00465950       12 bytes  _unassigned_00465950              EXACT
00465960       52 bytes  _unassigned_00465960              EXACT
004659A0       18 bytes  _unassigned_004659a0              EXACT
004659C0       12 bytes  _unassigned_004659c0              EXACT
004659D0       12 bytes  _unassigned_004659d0              EXACT
004659E0       12 bytes  _unassigned_004659e0              EXACT
```

Each landed on its first or second body; the four that needed a second body are
called out in the text.

### 0x004501D0 — empty leaf (1 byte)

`src/unidentified/unassigned_004501d0.cpp`:

```cpp
// 0x004501D0..0x004501D0: empty leaf.
// The image holds a lone RET here; no caller and no pointer to it exists, so an
// empty function recovers it exactly.

extern "C" void unassigned_004501d0(void) {
}
```

### 0x00453259 — default pure-virtual-call handler (20 bytes)

`src/unidentified/unassigned_00453259.cpp`:

```cpp
// 0x00453259..0x0045326C: the default pure-virtual-call handler: run the
// installed handler if there is one, then report the error and abort.

extern "C" void __cdecl asm_amsg_exit_0045373d(int code);
extern "C" void* data_00477200;

extern "C" void __cdecl unassigned_00453259(void) {
    if (data_00477200 != 0)
        ((void (__cdecl*)(void))data_00477200)();
    asm_amsg_exit_0045373d(25);
}
```

`_amsg_exit` is `__cdecl` in the image (its own region pushes `[esp+4]`), so the
declaration needs the explicit `__cdecl` for the `pop ecx` cleanup; the indirect
call reproduces `call eax` verbatim.

### 0x0045326D — install the pure-virtual-call handler (16 bytes)

`src/unidentified/FUN_0045326d_0045326d.cpp`:

```cpp
// 0x0045326D..0x0045327C: install the pure-virtual-call handler, return the old one.

extern "C" void* data_00477200;

extern "C" void* __cdecl unassigned_0045326d(void* handler) {
    void* previous = data_00477200;
    data_00477200 = handler;
    return previous;
}
```

`extern "C"` and not a plain data definition: the symbol has to be the image's
own `_data_00477200`, so it is declared, never defined here.

### 0x0045370E — per-thread field store (13 bytes)

`src/unidentified/unassigned_0045370e.cpp`:

```cpp
// 0x0045370E..0x0045371A: store the argument in the per-thread data block at
// +0x14.

extern "C" void* __cdecl asm_getptd_00456357(void);

extern "C" void __cdecl unassigned_0045370e(int value) {
    *(int*)((char*)asm_getptd_00456357() + 0x14) = value;
}
```

The argument is read *after* the `getptd` call, which is what the image does —
`call getptd` / `mov ecx,[esp+4]` / `mov [eax+14h],ecx`.

### 0x0045771D — exit with the leaving flags (15 bytes)

`src/unidentified/unassigned_0045771d.cpp`:

```cpp
// 0x0045771D..0x0045772B: run the exit path with the process-leaving flags.
//
// The three pushed constants are the exit code, the "quick" flag and the
// "process" flag the retail image hands to doexit.

extern "C" void __cdecl asm_doexit_00457629(int code, int quick, int process);

extern "C" void __cdecl unassigned_0045771d(void) {
    asm_doexit_00457629(0, 1, 1);
}
```

### 0x0045FE75 — per-thread mode block (9 bytes)

`src/unidentified/unassigned_0045fe75.cpp`:

```cpp
// 0x0045FE75: the per-thread mode block, one field inside the per-thread data.

extern "C" char* __cdecl asm_getptd_00456357(void);

extern "C" char* __cdecl unassigned_0045fe75(void) {
    return asm_getptd_00456357() + 0x5C;
}
```

### 0x00460C1E — offset a pointer by the locale header (8 bytes)

`src/unidentified/unassigned_00460c1e.cpp`:

```cpp
// 0x00460C1E: offset a pointer by the size of the locale header.

extern "C" char* __cdecl unassigned_00460c1e(char* base) {
    return base + 0x20;
}
```

### 0x00462363 — `basic_string::_Myptr` (14 bytes)

`src/unidentified/unassigned_00462363.cpp`. The second body was needed: writing
the small-buffer arm first makes c2 hoist the `lea` above the branch, so the
arms have to be written in the image's order — large arm first, small arm out of
line.

```cpp
// 0x00462363: the string's own pointer: the pointer member while the string
// is large, the inline buffer otherwise.
//
// std::basic_string keeps a 16-byte buffer and the pointer in one union at
// +0x10; the capacity at +0x24 chooses between them. The image tests the
// capacity against the small-string size and leaves the buffer arm out of
// line, so the large arm is the one written first.

struct StringBase_00462363 {
    unsigned char pad_000[0x10];
    union {
        char buffer[0x10];
        char* pointer;
    } storage;                   // +0x0010
    unsigned int reserved;       // +0x0020
    unsigned int capacity;       // +0x0024
    const char* Myptr() const;
};

const char* StringBase_00462363::Myptr() const {
    if (capacity >= 0x10)
        return storage.pointer;
    return storage.buffer;
}
```

`capacity` is `unsigned`: the test is `cmp [ecx+24h],10h` + `jb`.

### 0x004658C0 — mark the onexit table live (36 bytes)

`src/unidentified/unassigned_004658c0.cpp`. The dead-looking `test al,1` after
`and eax,~1` is the image's own code, so the model has to re-read the field after
the masking store **and** keep the flagged value in a local, otherwise c2 folds
the second store away.

```cpp
// 0x004658C0: mark the onexit table live.

extern "C" int data_00474c64;
extern "C" int data_00474c60;

extern "C" void __cdecl unassigned_004658c0(void) {
    data_00474c64 &= ~1;
    if ((data_00474c64 & 1) == 0) {
        int live = data_00474c64 | 1;
        data_00474c60 = 0x476F78;
        data_00474c64 = live;
    }
}
```

### 0x00465910 — construct the global object array (36 bytes)

`src/unidentified/unassigned_00465910.cpp`. Two corrections were needed: the
iterator is `__stdcall` with five arguments (the manifest already carries
`_asm_eh_vector_constructor_iterator_0045252d@20`, i.e. `ret 14h`), so the caller
only cleans the `atexit` argument and emits `pop ecx`; and the constructor
argument has to name the real symbol, which is the mangled
`?FUN_00434c10@@YIPAHPAH@Z` — a `int* __fastcall FUN_00434c10(int*)`
declaration (a plain `unsigned int __cdecl` one mangles to a name nothing binds).

```cpp
// 0x00465910: construct the global array of twenty 16-byte objects and
// register its destructor with the runtime.
//
// The constructor iterator is the runtime's own __stdcall helper: it takes the
// array, the element size, the count and the constructor and destructor
// addresses, and cleans the five arguments itself.

extern "C" void __stdcall asm_eh_vector_constructor_iterator_0045252d(
        void* array, unsigned int size, int count,
        void (__cdecl*)(void), void (__cdecl*)(void));
extern "C" void __cdecl asm_DatArchive_Reset_00434c20(void);
extern "C" void __cdecl asm_FUN_00465a00_00465a00(void);
extern "C" int __cdecl asm_atexit_00452e0a(void (__cdecl*)(void));
extern "C" char data_004923b0[];
int* __fastcall FUN_00434c10(int* element);

extern "C" void __cdecl unassigned_00465910(void) {
    asm_eh_vector_constructor_iterator_0045252d(
        data_004923b0, 16, 20,
        (void (__cdecl*)(void))FUN_00434c10,
        asm_DatArchive_Reset_00434c20);
    asm_atexit_00452e0a(asm_FUN_00465a00_00465a00);
}
```

### 0x00465940 / 0x00465950 / 0x004659C0 / 0x004659D0 / 0x004659E0 — static destructor registrations (12 bytes each)

Five identical wrappers, one per registered destructor
(`0x465A20`, `0x465A30`, `0x465A60`, `0x465A70`, `0x465A80`). Each landed on the
first body. `src/unidentified/unassigned_00465940.cpp` (the other four differ
only in the two addresses):

```cpp
// 0x00465940: register a static destructor with the runtime's exit list.
//
// The registered function is an ordinary __cdecl void(void) in the image; the
// runtime keeps it in the atexit table and runs it from doexit.

extern "C" void __cdecl ReleaseGlobalGdiSurface_00465a20(void);
extern "C" int __cdecl asm_atexit_00452e0a(void (__cdecl*)(void));

extern "C" void __cdecl unassigned_00465940(void) {
    asm_atexit_00452e0a(ReleaseGlobalGdiSurface_00465a20);
}
```

The registered cleanup callback is now ordinary C++ in the native GDI LTCG
batch, with the same 13-byte retail body. The 12-byte registration wrapper
still points to that exact address through `_ReleaseGlobalGdiSurface_00465a20`.

### 0x00465960 — clear the onexit table (52 bytes)

`src/unidentified/unassigned_00465960.cpp`. Second body needed: the zero fill
must be a `memset` call so c2 inlines it to `xor eax,eax` / `mov ecx,11h` /
`mov edi,492548h` / `rep stosd`; a hand-written `for` loop is unrolled into
individual stores (133 bytes emitted).

```cpp
// 0x00465960: clear the onexit table, mark it in use and register the
// destructor that tears it down.

extern "C" int data_00492588;
extern "C" int data_00492548[0x11];
extern "C" void __cdecl asm_FUN_00465a50_00465a50(void);
extern "C" int __cdecl asm_atexit_00452e0a(void (__cdecl*)(void));
extern "C" void* __cdecl memset(void* destination, int value, unsigned int count);

extern "C" void __cdecl unassigned_00465960(void) {
    data_00492588 &= ~1;
    memset(data_00492548, 0, 0x44);
    data_00492548[0] |= 2;
    asm_atexit_00452e0a(asm_FUN_00465a50_00465a50);
}
```

### 0x004659A0 — fill a table with -1 (18 bytes)

`src/unidentified/unassigned_004659a0.cpp`:

```cpp
// 0x004659A0: fill one table with -1.

extern "C" int data_00492998[0x80];

extern "C" void __cdecl unassigned_004659a0(void) {
    for (int index = 0; index < 0x80; ++index)
        data_00492998[index] = -1;
}
```

## Attempted and dropped — 17 regions, 462 bytes

Every entry was probed; the size shown is what the compiler emitted against the
region's own size, followed by the byte-level reason. None is registered.

| region | size | emitted | delta |
|---|---|---|---|
| `0x0045258F` | 18 | 18 | cluster only (EAX entry). Emitted body matches except `mov ecx,[eax]` / `cmp [ecx],imm` where the image has `mov eax,[eax]` / `cmp [eax],imm` (2 bytes at +0x01). Layout also unusable: the accessor section is 16-byte aligned, so the odd address `0x45258F` cannot be hit (the section landed at `0x452590`). |
| `0x00453C3D` | 21 | 21…24 | `_heap_handle`-style select. Closest 21 bytes: `add eax,-3` / `neg` / `sbb` / `inc` / `imul [g]` where the image has `sub eax,3` / `neg` / `sbb` / `not` / `and eax,[g]`. Ternary and mask spellings give 24 bytes (`cmp` + `setcc` + `dec` + `and ecx`). |
| `0x004556C8` | 24 | 25 | `mov ecx,[eax+70h]` + `test ecx,ecx` (5 bytes) where the image compares in place: `cmp dword ptr [eax+70h],0` (4 bytes). The `void`-field and `int`-field spellings both materialise the load. |
| `0x0045570D` | 36 | 37 | `add esp,8` (3 bytes) where the image merges the two deferred cdecl cleanups into `pop ecx; pop ecx` (2 bytes). Same body otherwise, including the `esi`-held return value. |
| `0x004557C9` | 39 | 41 | `_isctype` forwarder. The two arguments are materialised into ECX/EDX (`mov` + `push`) where the image pushes straight from the frame: `push dword ptr [esp+8]` twice. Operand order is right in both. |
| `0x00457932` | 27 | 26 | The image keeps the magic in a register (`mov eax,0E06D7363h` / `cmp [esp+4],eax` / `push [esp+8]` / `push eax` / `call` / `pop ecx;pop ecx` / `ret`); c2 folds the constant into the compare and then reuses the outgoing argument slot (`cmp [esp+4],imm32` … `mov [esp+4],imm32` / `jmp`). |
| `0x00458C25` | 20 | 22 | Store of a masked select. Identical arithmetic, but c2 loads the value global into ECX before the mask (`mov ecx,[g2]` / `… / and eax,ecx`); the image folds it into the AND (`and eax,[499304h]`). Same residual as `0x0045D14C`. |
| `0x00459075` | 42 | 41 | Table scan. The loop matches byte for byte; only the post-loop re-test differs: c2 folds the scale into the addressing (`cmp ecx,[eax*8+473670h]`, 1 byte shorter), the image materialises it (`shl eax,3` / `cmp ecx,[eax+473670h]`). |
| `0x004598BC` | 34 | 32 | Frame-match decision. c2 narrows to `testb [ecx+4],6` (4 bytes) where the image keeps the dword test (`test dword ptr [ecx+4],6`, 7 bytes), and c2 sinks `mov eax,1` to the tail instead of hoisting it before the branch; the then-arm also allocates context/frame to ECX/EDX instead of EAX/EDX. |
| `0x0045A0BC` | 47 | 55 | Unlock path. Three residuals: c2 uses the immediate form (`cmp eax,imm32`) where the image materialises the base (`mov ecx,473740h` / `cmp eax,ecx`); the `/ 32` keeps the signed-division fixup (`cltd`/`and`/`add`) where the image has a bare `sar eax,5`; and the unlock call becomes a tail `jmp` with the argument written back into the incoming slot where the image does `push`/`call`/`pop ecx`. |
| `0x0045B012` | 27 | 31 | Strftime forwarder. The four arguments are hoisted into EAX/ECX/EDX and pushed from registers; the image pushes straight from the frame (`push dword ptr [esp+14h]` four times). Same residual as `0x004557C9`. A five-parameter spelling collapses to 13 bytes (c2 writes the trailing zero into the incoming argument slot and jumps). |
| `0x0045D14C` | 16 | 18 | The heap-pointer select; identical to `0x00458C25` — `mov ecx,[g2]` / `and eax,ecx` where the image folds `and eax,[4980a4h]`. Pointer, unsigned and bitwise spellings all give the register form. |
| `0x0045E894` | 32 | 32 | Table scan; extent right, 3 bytes differ. c2 hoists the parameter (`mov ecx,[esp+4]`) and compares memory against it (`cmp [eax*8+473c98h],ecx`); the image loads the entry first (`mov ecx,[eax*8+473c98h]` / `cmp ecx,[esp+4]`). Flipping the comparison in the source did not change it. |
| `0x0045F3B4` | 12 | 13 | Two forwarded constants. `push 0` / `push 1` / `call` are exact; the tail is `add esp,8` (3 bytes) where the image has `pop ecx; pop ecx` (2 bytes). Same residual as `0x0045570D`. |
| `0x004622F6` | 11 | 5 | Scalar-new forwarder. c2 turns `push [esp+4]; call new; pop ecx; ret` into `jmp new` (5 bytes), which is a valid tail call but not the image's bytes. An intermediate local does not stop it. |
| `0x00462E60` | 30 | 30 | Cluster only (EAX entry, 16-aligned). Body extent right, 4 bytes differ: `mov ecx,[eax]` / `cmp [ecx],imm` vs `mov eax,[eax]` / `cmp [eax],imm`, and `mov dword ptr [eax+84h],0` vs `and dword ptr [eax+84h],0` (same length). |
| `0x004658F0` | 26 | 24 | The state pointer is pushed (`push offset data_00491c28`) where the image loads it into ESI (`mov esi,491C28h`) before the call, i.e. the callee takes its argument in ESI — expressible only through the cluster path, and the layout machinery rejects the region anyway (see below). |

### Recurring residuals, for whoever picks these up

- **`add esp,N` vs `pop ecx` pairs** (`0x45570D`, `0x45F3B4`, `0x4557C9`,
  `0x45B012`): every one of these wrappers forwards arguments and cleans up in
  the image with one-byte pops. Nothing tried — cdecl `int`/`void` callee,
  variadic callee, statement instead of `return`, `__stdcall` callee — moved c2
  off `add esp,N` or the register-materialised push. The parallel `atexit`
  wrappers *do* emit `pop ecx` (regions landed above), so the lever exists but
  is not the callee's declared convention.
- **A loaded pointer compared in place** (`0x45258F`, `0x462E60`): the image
  reuses EAX (`mov eax,[eax]` / `cmp [eax],imm`); c2 loads into ECX and compares
  through it. This is inside a cluster, where the register file is decided by the
  whole-program pass, so it may be reachable by changing the *context* shape
  (both were probed only with an array-walk context).
- **A global folded into a bitwise operand** (`0x458C25`, `0x45D14C`): the image
  emits `… / and eax,[global]`; c2 emits `mov ecx,[global]` before the mask and
  `and eax,ecx`. `?:`, `if/else`, mask-literal, pointer and unsigned spellings
  all give the register form.

## Cluster path: two hard blockers found

Both `0x45258F` and `0x462E60` are EAX-entry regions, so they were driven
through `cluster_attempt.attempt()` (throwaway copy; layouts and drivers were
rolled back and are not registered). Two layout-level blockers came out of it,
and both are outside the model's control:

1. **The accessor section is placed on a 16-byte boundary.** `0x45258F` is odd,
   so the linker put `.text$01accessor` at `0x452590` and left `cc` at
   `0x45258F`; the declared address can never be hit. Only 16-aligned regions
   can use this path at all — of the untouched EAX/EDX-entry set that is
   `0x0045CD10` and `0x00462E60`.
2. **The emitted COMDAT can be padded past the function.** For `0x462E60` the
   linked section was 33 bytes for a 30-byte body (three trailing zero bytes),
   and `validate_native_output` refuses with *"function is not its entire
   declared compiler contribution"*. `load_cluster` also cross-checks the
   layout's size against the manifest region, so the declared size cannot be
   raised to absorb the pad. The sibling 18-byte body at `0x45258F` had no pad,
   so the padding is body-dependent and worth measuring before a future attempt.

`cluster_attempt.attempt()` also cannot converge the context address on this
block: it recomputes the second gap from the declared address, and the padding
plus 16-byte alignment of `.text$03context` makes the address drift by 16 bytes
per retry (4 attempts, then it gives up silently). Driving it by hand — writing
the layout with the gap that puts the context on its declared address — is what
showed both blockers above.

## What is left in the block — 142 regions, 11,376 bytes

### 49 candidate-shaped regions (5,643 bytes) — plain-path candidates, not attempted

```
00450560 30  00450580 43  00450610 122  004521DC 336
00452332 240  0045287B 167  00453783 89  00453A1C 127
00454479 209  00454863 91  00454C08 238  00454EB8 31
0045653E 12  004567AB 179  00456911 378  004575A1 30
004577A2 44  00457A24 24  00457A52 42  0045972A 76
0045A77E 54  0045B52A 146  0045B7E8 51  0045BD27 75
0045CD10 70  0045DC17 101  0045EBF5 63  0045EE01 28
0045F4FC 148  0045F5A1 180  004606C5 26  00460EB9 43
00461004 90  004623AA 24  004623E9 24  0046253E 252
00462640 150  004627A3 85  00462B97 86  00462CC2 62
00462D47 48  00462F4C 48  00462FE0 396  00463AAA 32
00463B1A 18  00463BC4 30  00464BCE 717  00464F00 21
00464F45 67
```

Sub-groups inside it worth knowing before starting:

- **Multi-function regions** — one manifest region holding several complete
  functions, so no single symbol can own the extent: `0x4567AB` (179 bytes, six
  `_isctype` accessors), `0x456911` (378, seven of the same), `0x45F4FC` (148,
  nine `ismbb` forwards), `0x45F5A1` (180, two), `0x45BD27` (75, three locale
  accessors), `0x45DC17` (101, two), `0x45EBF5` (63, two), `0x45B52A` (146,
  two), `0x454EB8` (31, three scalar-destructor stubs), `0x45653E` (12) and
  `0x463B1A` (18).
- **Import thunk tables** — runs of `jmp dword ptr [data_…]`, one region per run:
  `0x4521DC` (336), `0x452332` (240), `0x46253E` (252), `0x462640` (150). N
  functions in one extent; not expressible without splitting the region.
- **Derived-class constructors** — `0x4623AA`, `0x4623E9`, `0x462CC2`,
  `0x462D47`: `call` the base constructor with `this` in ECX, then
  `mov [esi],<vtable>`. Both the base constructor (`0x462327`, `0x462C12`,
  `0x462C5A`, `0x462D0B`, `0x462D24`) and the vtables (`0x46C9F4`, `0x46CA00`,
  `0x46CA70`, `0x46CA88`, `0x46CAA0`) live in other regions, so the declarations
  have to bind to those symbols — a good follow-up once the vtables are settled.
- **x87 bodies** — `0x464BCE` (717, `_pow`-style with `fprem1`/`fpatan`
  sub-blocks), `0x464F00` (21, `f2xm1`/`fscale`), `0x463BC4` (30, `fprem` loop).
  Compiler intrinsics, not C++ sources.
- **EAX/EDX-entry leaves** — `0x4575A1` (30), `0x457A24` (24), `0x45EE01` (28),
  `0x45CD10` (70), `0x462E60` (30, attempted), `0x462F4C` (48), `0x464F45` (67),
  `0x454EB8` (31). These need the cluster path, and of them only `0x45CD10` and
  `0x462E60` are 16-byte aligned (see the cluster section above).
- **Region `0x450560`/`0x450580`/`0x450700`** — ECL interpreter members whose
  `this` arrives in ESI; also cluster-only.

### 10 SEH-prolog bodies (2,214 bytes) — whole functions, compiler-owned prolog

```
004561C4 346  0045721B 53  0045E270 69  0045F7D7 579
0045FA9D 345  0045FD56 80  0045FDB8 143  0045FE87 417
00461458 81  00463170 101
```

Each starts `push N; push <scope table>; call __SEH_prolog` and ends
`call __SEH_epilog`, i.e. they are complete functions with a `__try`/`__finally`
(some with a `__except` cleanup path). They were classed as fragments by the
entry analysis only because `ebp` is established by the prolog call. A model
would have to be a real `__try` body, and the scope-table address (`0x46C5A8`,
`0x46C900`, `0x46C910`, `0x46C920`, `0x46C960`, …) is compiler-generated data
that has to bind to the image's own table — the first thing to check before
writing any body.

### 23 interiors of larger functions (349 bytes) — not regions of their own

```
004526CE 3  00452EE0 11  00453677 11  004556FB 13  004564F5 5
00456503 3  00456DFE 5  004574F5 8  00457796 3  00457A10 3
00459CAB 3  00459F12 3  0045CFAC 3  0045F7A9 3  0045FD1C 5
0046015B 8  004613E5 3  00461546 3  004621FE 3  00462F2B 6
00462FB0 17  00463509 12  00464033 215
```

Every one reads `[ebp-x]` with no `push ebp`/`mov ebp,esp` in the region, or is a
one-instruction tail (`mov ebx,[ebp+8]`, `mov esi,[ebp-24h]`, `mov esp,[ebp-18h]`).
They are the middle of a function whose other half is another region; treat the
whole function, not the fragment.

### 40 EH funclets (400 bytes) — not expressible

```
00463BB0 10  00465198 10  004651AA 10  004651BC 10  004651CE 10
00465225 10  0046523B 10  00465268 10  0046528B 10  004652D6 10
004652F9 10  0046531B 10  00465363 10  00465388 10  004653A8 10
004653CB 10  004653EB 10  0046541C 10  004654B5 10  004654CE 10
00465514 10  0046553C 10  0046556B 10  0046558B 10  004655AB 10
0046560F 10  0046562E 10  0046564B 10  0046566B 10  00465696 10
0046574E 10  004657A5 10  004657BB 10  004657E9 10  0046580B 10
0046582B 10  0046584B 10  0046586B 10  0046588B 10  004658AB 10
```

All but `0x463BB0` (`mov edx,477010h` / `jmp ctrandisp2`) are exactly
`mov eax,<type-info>` / `jmp __CxxFrameHandler`; `0x46533B` has a trailing
`int 3`. They are the compiler's per-function C++ EH handler stubs, emitted
*inside* the function that owns the handler, never as a standalone leaf, and
their type-info operand is image data.

### 7 mixed bodies (2,487 bytes) — the region boundary cuts an instruction

```
004525D0 46  00452725 11  0045F294 9  00463260 175  00463321 9
00464110 2054  00464FD5 183
```

`0x4525D0`, `0x452725`, `0x45F294` (a 5-byte `return 1` followed by a fragment),
`0x463260`, `0x463321`, `0x464110` (2,054 bytes), `0x464FD5` (183). Their source
blocks contain `TH10_REL8`/`TH10_OPERAND16` raw-byte emissions mid-instruction.

### 14 one-to-five-byte fragments (63 bytes) — dead ends

- tails only (`pop esi`, `pop ecx`, `int 3`): `0x452E59`, `0x4535ED`, `0x45375F`,
  `0x453B6A`, `0x462701`, `0x45A25C`, `0x45F3A3`, `0x46533B`.
- ends in a call or `lea esp` and has no `ret` at all: `0x453B54`, `0x4576D3`,
  `0x45BD87`, `0x46296B`, `0x463C04`.
- `0x459FAD` (236 bytes, `esi`-entry `_strtod`-style body) whose tail jumps into
  the middle of `0x456911`'s block.

## Files touched

Landing sources (17): `src/unidentified/unassigned_004501d0.cpp`,
`unassigned_00453259.cpp`, `FUN_0045326d_0045326d.cpp`,
`unassigned_0045370e.cpp`, `unassigned_0045771d.cpp`, `unassigned_0045fe75.cpp`,
`unassigned_00460c1e.cpp`, `unassigned_00462363.cpp`,
`unassigned_004658c0.cpp`, `unassigned_00465910.cpp`,
`unassigned_00465940.cpp`, `unassigned_00465950.cpp`,
`unassigned_00465960.cpp`, `unassigned_004659a0.cpp`,
`unassigned_004659c0.cpp`, `unassigned_004659d0.cpp`,
`unassigned_004659e0.cpp`.

The attempted-but-dropped sources keep their last failing body in the throwaway
copy only; nothing of them is in the tree, and their manifest records are still
`asm`. No layout, driver or cluster registration from this wave remains: both
cluster attempts were rolled back or hand-reverted in the throwaway copy, and the
maintained `regions.json` carries no entry whose layout path mentions this
wave's two names (`layout/ltcg/cxxmatch_0045258f.json`,
`layout/ltcg/cxxmatch_00462e60.json`) — those files exist only under
`/tmp/VeinBlock456/keep_*.json`.
