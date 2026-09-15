# Render-state synchronization, quad appending, and primitive callers

Seven complete game functions add 1,568 bytes to the existing render cluster.
The cluster now contains 13 exact real bodies. Only ColorViewport::Draw and
ApplyDefaultViewport are rooted; the synthetic array-loop context retains the
private entry conventions of gradient and entity primitive draws.

## Connected recovery

SyncRenderState takes the manager in EAX and entity in EDI, and calls Flush with
ESI. Its seven assembly callers at the start of this batch covered 3,432 bytes.
Five of those callers are recovered here: textured strip, queued quad, solid
strip, solid fan, and textured fan. The remaining two 1,111-byte quad pipelines
still require their own source reconstruction; the private synchronization and
append boundaries are now available in the same native compiler scope.

AppendQuad takes EAX manager and EDX vertices. Six ordinary typed aggregate
assignments expand four vertices to two triangles (indices 0,1,2,1,2,3), then
advance the cursor and increment the batch count. This generates the exact
157-byte contribution, including all compiler-produced REP MOVSD copies. Its
real DrawQuad caller also reproduces the private argument transfer exactly.

Textured strip, quad, and fan callers receive their manager in ECX and entity in
EAX. The two solid primitive callers use EAX manager and EDI entity. All definitions
are visible in one /LTCG invocation, with separate /GL inputs for the helpers and
real callers; no declaration tries to encode EAX/EDI as a public C++ ABI.

## Source-shape evidence

- The initial synchronization candidate was 200 bytes because a byte cast in its
  first blend comparison generated AND AL,3. Comparing the promoted cache byte
  to the unsigned masked flags generates the retail AND EAX,3; the byte assignment
  after Flush still generates AND AL,3. The resulting complete 201 bytes match.
- The strip caller initially had 232 bytes. A combined flag guard moved its error
  block to the tail and used two long conditional branches. Two separate early
  guards produce the retail short branches and inline early return (224 bytes).
- The texture cache write must precede the device-pointer read. A const volatile
  reference for that read reproduces the retail scheduling. The cache itself and
  the bound texture remain ordinary typed fields/pointers. A volatile cache write
  alone did not resolve the ordering, and was removed from the accepted source.
- The appender, quad caller, fan caller, and both solid primitive callers matched
  their complete extents on their first source attempts once placed at the correct
  addresses. Context extents are measured from the native MAP, never counted as
  recovered bytes. The final context is 233 bytes.

## Validation

`python3 matching2/tools/matching/probe.py --source src/render/render_state_sync.cpp
--output matching2/build/probe_render_primitives` reports all 13 functions EXACT.
`make verify MSVC_ARGS='--jobs 32'` passed: all 487,936 bytes match retail.
Progress: 455 ordinary-C++ regions / 27,686 bytes; 2,130 assembly regions /
361,296 bytes. Whole executable SHA-256 remains
`2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`.

The native report records zero instruction/address changes, masked bytes, aliases,
or reference bytes used as build inputs. The shared header exposes only the
manager fields, entity fields, vertices, and device calls required by these bodies.

| Address | Function | Bytes | Native body SHA-256 |
| --- | --- | ---: | --- |
| 0x004425A0 | SyncRenderState | 201 | `6d0a04e9bbb63375722ac2cdb81f7a427270579e1f9f1088b99989e3e356ba6f` |
| 0x00444CE0 | DrawStrip | 224 | `269c0294dd452a79368aa596b9d65c823aa92e1e144fcb4681f22eb3628fa918` |
| 0x00442FE0 | AppendQuad | 157 | `f398fee15bc547def3902264a083119088f311da3a12c06eddb87c1969676914` |
| 0x00444DC0 | DrawQuad | 145 | `a244832365481c44832c2ef4010b68f67593e32cb4a595a5f69dfab1e57e7166` |
| 0x004450E0 | DrawFan | 211 | `aa6c2227b982ef48582fb151b3bac95df3c019715eccb7478655cf7cc5e52cdc` |
| 0x00444E60 | DrawSolidStrip | 315 | `586bb20b6ad7f01e12709e4db2afecb682648d4a7ccd78053b1d635b48457067` |
| 0x00444FA0 | DrawSolidFan | 315 | `534b3c68210ad967742bd8ac8cced2bacb3d53b123ed717a5e584501cbef8976` |

## 0x00445880 fan submitter: call site recovered, register roles blocked

The 25-byte submitter at `0x00445880` (`src/unidentified/FUN_00445880_00445880.cpp`)
forwards this object's `+0x358` field and the constant `0x21` to `DrawFan` at
`0x004450E0` and returns 0. Retail's call site, call shape and argument order are
reproduced exactly — the only residue is which register holds `this` while the
field is read:

```text
retail   mov eax,ecx ; mov ecx,[eax+0x358] ; push 0x21 ; push ecx ; mov ecx,[0x491C10] ; call ; xor eax,eax ; ret   (25)
compiled mov eax,[ecx+0x358] ; mov ecx,[0x491C10] ; push 0x21 ; push eax ; call ; xor eax,eax ; ret               (23)
```

Four source spellings were measured, all 23 bytes with 14 differing: the direct
member call, a `self = this` alias local, a field-pointer local, a separate
`int value = field_358;` statement, and a hoisted manager local. MSVC always
folds the field load into the member access, so retail's two-instruction
`mov eax,ecx` / indexed load does not appear. The entry is otherwise a ready
one-shot recovery once a construct with retail's register roles is found.
