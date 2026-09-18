# Wave 8: six large regions, measured blockers

2026-09-13. Ten parallel agents took the largest open regions (one translation
unit each, `matching2/build/waves/briefs8/`). Four landed and are in the
manifest; the six that did not are recorded here with the measurements their
agents produced, so the next attempt starts from evidence.

## Landed

| region | bytes | how |
| --- | ---: | --- |
| `0x00443B60` | 1047 | native-LTCG cluster, source in EAX; retail's two `fsincos` sequences are inline-`__asm` blocks (MSVC never emits `fsincos` from `sinf`/`cosf`) |
| `0x0044A5F0` | 850 | plain `__fastcall`; the keyboard-mask packer, textually the same as the recovered `0x0044AD30` |
| `0x0044A9D0` | 850 | native-LTCG cluster; the plain `/O2` body differed only in a 5-byte prologue register choice (`mov esi,ecx` position), which the `/GL` path reproduces exactly |
| `0x00444240` | 818 | native-LTCG cluster, entity in EAX; D3DX project/rotation through bound thunks |

## Blocked

### `0x00403090` — 1984 bytes, `object_visibility`

The entry convention is solved and reusable: a member of the *object*
(`this` in ECX) declared `int IsCulled(const VisCamera* camera, const VisVec3&
offset, float radius_sq)` with camera in EAX, offset in EDX, radius on the
stack and `ret 4`; a synthetic pool-walker caller forces it and the first four
retail instructions then match. The value-operator idiom is also solved: the
`fstp [temp]; mov eax,[temp]; mov [dst],eax` runs appear only when the
destination is a separately declared vector assigned from a vector-valued
expression (`VisVec3 v; v = a + b;`), never from an initializer, and the same
applies to `v = this->size * 0.5f` and `position = position - eye`. The
`D3DXMatrixIdentity`, `D3DXVec3LengthSq`, `D3DXVec3ProjectArray` and
`D3DXMatrixTranslation` inlines and the eleven pooled constants
(`constant_aliases`, not `constants`) are all reproduced.

The residual is pure stack-slot packing. Retail's frame is exactly `0x12C`
bytes: four sentinel floats at `0x00`, a 12-byte vector temp at `0x10`, the
eight projected points at `0x1C`, `hw` at `0x7C`, the nine-point projected
input array at `0x80` (element 0 is never written but still passed to a call
with n=8) and the world matrix last at `0xEC`. Best candidates consume
`0x134`–`0x140`, i.e. 12–24 bytes more, which shifts every `[esp+…]` operand
even where the instruction sequence matches. Every candidate also differs in
1768 of 1984 bytes from the first two instructions on (`sub esp,0x134` against
`sub esp,0x128`). Next experiment: vary the *variable set* (drop the separate
`half` and `distance`, try `points[0]` as the half vector, try the eye as
`camera->eye_offset + camera->position`) until the frame lands on `0x12C`.

### `0x004465B0` — 1463 bytes (table folded), `transparent_pixel_fill_locked`

The cluster builds and links; the closest C++ draft emits 1377 bytes of code
against retail's 1417 with the algorithm, the EAX entry and the two-level
switch reproduced. Residuals, all measured: frame `0x3C` against retail's
`0x40` with the surface slot at `[esp+0x14]` instead of `[esp+4]` (six
declaration orders give identical frames, so the split is the optimiser's
spill pass); the zero constant lives in EBX inside the loop instead of ESI in
the prologue (turning retail's `cmp eax,esi` into `test eax,eax`); the 32bpp
alpha test is one instruction shorter (`cmp BYTE PTR [ecx+5],0` against
`mov bl,[ecx+5]; test bl,bl`); the accumulator zero-init is hoisted above the
alpha test; and the loop keeps one pointer where retail keeps two
(`edi = p`, `ecx = p-2`). The index form `PIX* p = row + x; PIX* prev = p - 1;
PIX* next = p + 1;` reproduces the whole prologue and dispatch (0.970
similarity) but loses the case bodies; the pointer form is the mirror image.
Next: the form that keeps the constant in ESI *and* yields the two-pointer
induction pair.

### `0x00436DA0` — 946 bytes, `transparent_pixel_fill`

Both paths' instruction shapes are recovered and verified — the 16bpp write is
*two* statements (`*(unsigned short*)p = (*p & 0xF00F) | ((r>>1)&0xF)<<8 |
((g>>1)&0xF)<<4;` then `*(unsigned short*)p = (*p & 0xFFF0) | ((b>>1)&0xF);`),
the neighbours are word loads tested with `(v & 0xF000u) != 0`, the loop
conditions reload the width field, and the 32bpp path uses two explicitly
incremented pointers (`p` and `c = p - 2`) rather than a derived offset, which
is what makes MSVC keep `lea ecx,[ebp-2]`. The block is MSVC's lowering of a
two-case switch. The blocker is the allocator: retail runs
`a1=esi, p=edi, j=ebp, width=edx, r=ecx, g=ebx` with a `0x14` frame and five
homes, while every candidate runs `p=ebp`, spills the width into ECX's
collision and keeps `b` in EDI with a `0x10` frame — a cascade from the first
choice. Retail's 16bpp body matches instruction-for-instruction modulo
register names. Fifteen source-shape families were swept without moving it.
The agent's suggestion, untried here: recover the same body through the native
LTCG cluster machinery, whose whole-program alias information is the one lever
the per-file path does not expose.

**Measured 2026-09-15: that lever does not apply to this region.** A provisional
schema-1 cluster was built for the draft above (gap `0x401000..0x436DA0`,
function at `0x436DA0` as `.text$01tpxfill`, a synthetic `__stdcall` caller, no
external bindings needed) and linked with native `/LTCG`. Unrooted, LINK keeps
the two stack arguments but changes the prologue anyway: `mov eax,[esp+4]`
first, frame `0x10` instead of retail's `0x14`, surface in EAX, and the body is
914 bytes — exactly the plain `/O2` body (same 914 bytes, same 806 differing
bytes, `mov eax,[esp+4]` first). Rooted (`/INCLUDE:_TransparentPixelFill_00436da0@8`,
which forces the public convention) the contribution is again 914 bytes and
byte-identical to plain `/O2`. Conclusion: for a function whose retail ABI is
already the C++ default (`__stdcall`, arguments on the stack), the whole-program
scope buys nothing here; LTCG only materialises conventions the source
declaration cannot express (compare `0x0044A9D0`, whose retail entry uses
ECX/EDX/EAX). The blocker is the same allocator home assignment as
`0x00450220`, and it needs a source-shape answer, not a compiler-scope one.

### `0x0044A190` — 833 bytes, joystick binding reader

The frame and `/GS` prologue, the three local offsets, the WinMM
`memset(13 dwords)` + `dwSize`/`dwFlags` + call sequence, the binding visit
order `0x58,0x5A,0x5E,0x5C,0x68` with the neg/sbb idioms, the caps axis maths
and the 400-iteration `Acquire` retry rotation are all reproduced. The blocker
is register allocation: retail keeps the action word in ESI (its stack slot is
allocated but never written) and *re-materialises* the fourth argument
(`mov edi,[ebp+0Ch]` before `joyGetPosEx`, a fresh `mov eax,[ebp+0Ch]` in the
caps block), while MSVC unifies the two device loads, hoists the definition to
the entry block and keeps it in ESI across the call, giving the action word a
memory home. Roughly 120 source variants plus a flag sweep
(`/G3 /G4 /G5 /GB /G6 /Ob1 /Ob2 /Og /Ot /Os /Oi /Oy /GA /Ge /Gf /Gs /Gh /GT
/GX- /GR- /GS- /GF- /Gy- /Zp1-2`) all give the same 859-byte body; a hand-built
native `/LTCG` link moved the binding to EDX and did not reproduce retail's
homes either. The missing ingredient is a source form in which MSVC reloads the
device argument across the call instead of keeping it live.

### `0x00437750` — 645 bytes, font surface blend

Retail's entry promotes three parameters (EAX row, EDX mask, ECX column,
`ret 0xC`); every candidate promotes two (EAX mask, ECX row) and leaves the
column on the stack with `ret 0x10`. Eighty-five isolated native-LTCG builds
were run: eleven synthetic caller shapes (array walk, job records, cursor walk,
promoted forwarding helper, nested loops, mask-derived row/column, …) give
byte-identical callee entry code, i.e. the caller has no influence on the
callee's internal convention; six declaration permutations, three dispatch
forms, four parameter type forms, explicit calling conventions, the
member-function form and five liveness variants all promote the same two
registers. Promotion *is* body-driven and does move when the body changes, so a
variant raising register pressure without changing the instruction sequence is
the plausible unlock — but none of the semantically faithful shapes reaches it.
Note that this function has **no caller anywhere in the image**: no direct
call, no jump, no relocation and no 32-bit address, so there is no retail
caller to drive a whole-program convention either. The semantically faithful
reconstruction, the ready layout and driver, and the measured field/vtable
maps are retained under `matching2/build/waves/results8/W809/`.

### `0x00450220` — 589 bytes, ECL name table

The agent for this region failed before producing any measurement; it is
untouched and still `asm_` in the manifest.


## Update: 0x00445880 (25 bytes) modelled, two bytes short

The "register roles" blocker for this region is resolved: the function is a plain
`__thiscall` member (ECX in, and the **sound** entry screen accepts it now that
`push` counts as a read), whose body hands `this->field_358` and the command
`0x21` to the manager:

```cpp
int Object_00445880::Run() {
    ((Manager_00445880*)data_00491c10)->Issue(field_358, 0x21);
    return 0;
}
```

with `Issue` declared as a member (ECX plus two stack arguments, callee-popped -
exactly retail's setup) and bound as `relative_code` to `0x004450E0`. The model
emits **23 bytes against retail's 25**, and the byte comparison shows the entire
difference is retail's opening `mov eax,ecx`:

```
mine: 8b 88 58 03 00 00 6a 21 51 8b 0d 10 1c 49 00 e8 .. 33 c0 c3
want: 8b c1 8b 88 58 03 00 00 6a 21 51 8b 0d 10 1c 49 00 e8 .. 33 c0 c3
```

Every other instruction - the field load, the two pushes in retail's order, the
manager load, the call and the `xor eax,eax; ret` tail - is already identical, so
the region is one instruction from landing. The copy exists so that ECX is free
for the field load. Three shapes were measured and all emit the same 23 bytes:
the plain member call, the field read into an `unsigned int` local first, and the
manager cached in a named pointer. A named `self` was tried earlier with the same
result, so the copy is an allocator choice rather than a statement-order one -
the fourth consecutive region where an MSVC register decision, not the source
shape, is what stands between the model and retail.
