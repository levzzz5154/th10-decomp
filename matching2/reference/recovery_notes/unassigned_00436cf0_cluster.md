# 0x00436CF0 pixel-format lookup recovery

Date: 2026-09-19
Region: `asm_unassigned_00436cf0`, `src/unidentified/unassigned_00436cf0.cpp`,
55 bytes (0x00436CF0..0x00436D27). **EXACT via the normal semantic path** (no
layout/cluster).

## Semantic model

The body is the out-of-line copy of the pixel-format walk that
`GdiSurface_Create` (0x00436AF0) inlines at 0x00436B0A before it builds the
font-atlas DIB section. Both read the table at 0x00474918 as 24-byte records
(`id`, `bits per pixel`, four colour masks) terminated by `id == -1`; the first
record's id is the 0x16 stored in the image, and the archived readable model in
`matching2/reference/legacy_semantic/src/platform/gdi_surface.cpp` supplies the
matching field use (`entry->id`, `entry->bits_per_pixel`, the four masks).

Register evidence fixes the prototype: the callee compares the searched-for id
in **EDX** (the second `__fastcall` register) and never reads ECX, whose first
use is the overwriting load of `formats[0].id`. Also, EAX is a running *index*,
not a pointer: the retail body forms `index*3` and loads through `[ecx*8+base]`,
MSVC's idiom for a 24-byte element array. The 3-byte `8d 49 00`
(`lea ecx,[ecx+0]`) at 0x00436CFD is compiler loop-alignment padding before the
16-byte-aligned loop head at 0x00436D00, so no hand-written encoding helper is
needed. There is no direct call or pointer slot to 0x00436CF0 anywhere in the
image, which is consistent with an external-linkage helper whose call sites were
all inlined; the trailing move is therefore unobservable and the free-function
API with an unnamed leading register argument is the honest model.

Retail keeps the original quirk that a missing non-`-1` id returns the address
of the terminating record (the caller's `test ecx,ecx` can never fire); the
model reproduces retail byte for byte rather than "fixing" it.

## Source (`src/unidentified/unassigned_00436cf0.cpp`)

```cpp
// 0x00436CF0..0x00436D27: GdiFormat_Find - locate a pixel-format record by id.
//
// The same walk is inlined at 0x00436B0A inside GdiSurface_Create (0x00436AF0)
// before the DIB section is built, so this address is the out-of-line copy of
// that lookup. The table at 0x00474918 holds 24-byte records terminated by an
// id of -1; its first record carries id 0x16.
//
// The retail callee takes the searched-for id in EDX, the second __fastcall
// register, and never reads ECX (its first use of ECX is the overwriting load
// of formats[0].id), so the leading register argument is left unnamed.

// Record layout shared with GdiSurface_Create: id, bits per pixel, four
// colour masks; id == -1 terminates the table.
struct GdiFormat {
    int id;
    int bits_per_pixel;
    unsigned int masks[4];
};

extern "C" unsigned char data_00474918;

extern "C" GdiFormat* __fastcall GdiFormat_Find(int unused, int id) {
    (void)unused;
    GdiFormat* formats = (GdiFormat*)&data_00474918;
    int index = 0;
    while (formats[index].id != -1 && formats[index].id != id)
        ++index;
    if (id == -1)
        return 0;
    return &formats[index];
}
```

## Manifest record

Replace the existing entry with:

```json
{
  "name": "semantic_GdiFormat_Find_00436cf0",
  "source": "src/unidentified/unassigned_00436cf0.cpp",
  "symbol": "@GdiFormat_Find@8",
  "address": "0x00436CF0",
  "size": 55,
  "kind": "semantic",
  "owner": null
}
```

## Evidence

`python3 matching2/tools/matching/probe.py --source
src/unidentified/unassigned_00436cf0.cpp --project <copy>/msvc --output <out>`
reports `0x00436cf0 55 bytes @GdiFormat_Find@8 EXACT`.

The object is instruction-for-instruction the retail body: `mov ecx,[0x474918]`
/ `xor eax,eax` / entry sentinel test / the `lea ecx,[ecx+0]` pad / index loop
with `lea ecx,[eax+eax*2]` + `mov ecx,[ecx*8+474918h]` / `cmp edx,-1` guard /
`lea eax,[eax+eax*2]` + `lea eax,[eax*8+474918h]` return. Its three `dir32`
relocations name `_data_00474918` with addend 0, which binds to 0x00474918,
matching the retail displacements. Extent 55, no differing bytes.

## Shapes tried

Two, both compiling to the exact extent: the first with the record spelled as
six named `int` fields, the final one with the legacy-aligned
`id/bits_per_pixel/masks[4]` layout. No layout JSON, cluster driver or encoding
helper is involved.
