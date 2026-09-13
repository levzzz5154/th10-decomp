# Joystick binding reader at 0x0044A190: reconnaissance

2026-09-13. The 833-byte `0x0044A190` is the largest remaining game region whose
own ABI is a standard one and whose callees are all expressible, so it needs no
LTCG cluster. A first model compiles to 784-800 bytes; this note records what
the disassembly fixes and the one structural difference that remains.

## Fixed by the disassembly

Entry is `unsigned short __fastcall(unsigned int flags, void* unused, int
binding_set, int device)` (`RET 8`), and both backends share the 0x6A-byte
binding table at `0x00474E30`, whose five signed 16-bit indices are `-1` when
unbound:

| binding field | WinMM button mask flag | DirectInput state bit |
| --- | --- | --- |
| `+0x58` | `0x001` | bit 7 |
| `+0x5A` | `0x002` | bit 6 |
| `+0x5C` | `0x004` | bit 5 |
| `+0x5E` | `0x008` | bit 4 |
| `+0x68` | `0x100` | bit 7 |

- **WinMM path** (`!(data_00491ff4 & 0x400)`): zero a 13-dword `JOYINFOEX`
  (`dwSize = 0x34`, `dwFlags = 0xFF`), poll it through the IAT slot bound as
  `data_00466280` with `device != 0` as the id, then derive each axis threshold
  from the per-device record at `0x004918B8 + device * 0x194`: `span = high -
  low`, `centre = (low + high) >> 1`, `band = span >> 2` (the four *dwords* at
  `+0x24/+0x28/+0x2C/+0x30` are the packed min/max word pairs). Flags
  `0x080`/`0x040` for `x > centre + band` / `x < centre - band`, `0x010`/`0x020`
  for the same on y.
- **DirectInput path**: `data_00491c3c[device]` is the device object; vtable
  `+0x64` gates it, `+0x1C` is retried up to 400 times while it returns
  `0x8007001E` (`DIERR_INPUTLOST`), and `+0x24` is called as
  `(0x110, state)` before the bindings are read out of the state bytes and the
  axes are compared against `+/-data_00491d5e` / `+/-data_00491d60` with the
  branchless `setnl`/`setle` triples.
- Every accumulation uses the same `flags |= cond ? VALUE : 0;` shape that MSVC
  compiles to the observed `neg/sbb/neg` and `sbb/and` sequences.
- `___security_cookie` (`0x00473660`) and `@__security_check_cookie@4`
  (`0x00458EA5`) are already bound in the manifest, so the /GS prologue is a
  non-issue; the raw object only shows the unresolved `ds:0` placeholder.

## The remaining difference

Retail's prologue is

```asm
push ebp / mov ebp,esp / and esp,0FFFFFFF8h / sub esp,154h
mov eax,ds:___security_cookie / xor eax,ebp / mov [esp+150h],eax
mov eax,[ebp+arg_0] / imul eax,6Ah / add eax,474E30h
push ebx / mov ebx,eax            ; binding pointer lives in EBX
mov eax,ds:data_00491ff4 / test ah,4
push esi / push edi / mov esi,ecx ; incoming flags live in ESI
```

The candidate instead keeps the binding pointer in ESI and the flags in EBX,
spills one of them, and has a 4-byte-aligned frame (0x154 without the `and
esp,-8`). Declaring the device-state buffer as an 8-byte-aligned struct
reproduced the alignment but added 8 bytes of frame. So both the local
alignment and the two callee-saved homes have to be found from the source
shape, exactly like the sprite family's x87 discipline.

## Iteration route

Plain regions do not need a cluster, but the probe insists that `--source` owns
a maintained region, and a `--proposal` record is filed under its own `source`
field, so a candidate for this function is written into
`src/platform/joystick_poll.cpp` (the region's current owner) and probed with

```sh
python3 matching2/tools/matching/probe.py --source src/platform/joystick_poll.cpp \
    --proposal <proposal.json> --output matching2/build/probe_joy
python3 matching2/build/diffunit.py --source src/platform/joystick_poll.cpp \
    --symbol "@Joystick_ReadBindings_0044a190@16" --address 0x44A190 --size 833
```

`diffunit.py` compiles the unit with the retail flags and prints an
address-aligned instruction diff of the differences, which is the fast loop for
this class of region. The model is preserved at
`matching2/build/recovery-lab/joystick-reader/`.

## Second model: 800 of 833 bytes (2026-09-13)

The model was rebuilt with the axis maths as *dword* arithmetic on the caps
record (`band = (max - min) >> 2`, `upper/lower = ((min + max) >> 1) +/- band`),
which is what retail emits — the earlier "unpack the word pair" model was wrong
and cost about 30 bytes — and with the device-state buffer hoisted to the top of
the function as `__declspec(align(8)) unsigned char state[0x110]`. That reaches
**800 of 833 bytes**; the remaining 33 are:

- the /GS machinery is present (the prologue stores `cookie ^ ebp` and every
  exit calls the check; the raw-object disassembly shows both, the check's
  target only reads as zero because it is unresolved there), so the 33 bytes
  are elsewhere;
- the two callee-saved homes (retail: binding pointer EBX, flag word ESI) and
  the resulting 8-byte frame difference.

A first micro-test showed `__declspec(align(8))` on a *plain* local array does
produce `and esp,-8`, and it does here too: with either the state buffer or the
JOYINFOEX local aligned, the frame is retail's `0x154`, the first twelve
prologue bytes match, and the /GS store and check are both emitted (the check
target disassembles as `call 0` in the raw object because the symbol is
unresolved there). The 33-byte shortfall is therefore in the body: the flag
word is spilled instead of living in ESI and the binding pointer lands in EDI
instead of EBX, and the axis/retry blocks still differ in their exact
instruction selection.

Both models are preserved (`joystick_poll.cpp` and `joystick_poll_v2.cpp` in
`matching2/build/recovery-lab/joystick-reader/`).

Two siblings in the same area remain untouched and are the same size class:
`0x0044A5F0` and `0x0044A9D0` (850 bytes each, keyboard binding readers, same
`__fastcall` shape, no private callees).
