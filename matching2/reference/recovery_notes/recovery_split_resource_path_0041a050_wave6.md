# 0x0041A050 `Recovery_SplitResourcePath` (75 B) + its callee 0x0041A0A0 `Recovery_TrimWhitespace` (114 B) — **both EXACT**

2026-09-19, wave 6. The assigned region `0x0041A050..0x0041A09A` (75 bytes,
`asm_Recovery_SplitResourcePath_0041a050`) is recovered as readable C++ and is
**byte-identical to retail, 0 differing bytes**. It is not landable alone: its
two `TrimWhitespace` calls go to a callee whose argument and result live in
**EAX**, and `ltcg_cluster_lessons.md` rule 12 applies — an opaque binding keeps
the *declared* convention, so that helper had to be co-compiled in the same
native-LTCG cluster. The co-compiled helper `0x0041A0A0`
(`asm_Recovery_TrimWhitespace_0041a0a0`, 114 bytes) also measures **EXACT**, so
the cluster lands 189 bytes in total.

```
$ python3 matching2/tools/matching/probe.py \
      --source src/game/recovery_split_resource_path_0041a050.cpp \
      --source src/game/recovery_trim_whitespace_0041a0a0.cpp \
      --project /tmp/srp/verify/msvc --output /tmp/srp/verify/out --show 30
0x0041a050      75 bytes  _SplitResourcePath_0041a050@12  EXACT
0x0041a0a0     114 bytes  ?TrimWhitespace_0041a0a0@@YGPADPAD@Z  EXACT
EXACT
```

Byte proof against `matching2/build/oracle/th10.exe` (bodies read out of the
cluster PE built from the landed copy):

```
0x0041a050   75 SplitResourcePath_0041a050   emitted sha256 86d92d58e0bb915764a334daf6d36e41117fb109fc4502bea024d6aad099051f
                                             retail  sha256 86d92d58e0bb915764a334daf6d36e41117fb109fc4502bea024d6aad099051f
0x0041a0a0  114 TrimWhitespace_0041a0a0      emitted sha256 d89633e4e144ce1a0e5bea319c03283d1159e93e689cb7c2a10c8c8aab609514
                                             retail  sha256 d89633e4e144ce1a0e5bea319c03283d1159e93e689cb7c2a10c8c8aab609514
```

## What the listing calls

| callee | how it is reached |
| --- | --- |
| `0x00452730` | the CRT **first-occurrence byte search** (`strchr` shape: forward dword scan with the `7EFEFEFFh`/`81010100h` zero-byte trick, returns the pointer of the *first* match, `0` on NUL). Bound opaquely through the layout's `absolute_symbols` as `_asm_FUN_00452730_00452730` under a non-CRT prototype name so `/Oi` cannot turn it into an intrinsic. `match_crt.py` matches the real `strrchr` at `0x00452930`, not this one. |
| `0x0041A0A0` | `TrimWhitespace`, **argument and result in EAX** (every one of its ten retail call sites materialises the string in EAX and reads the result back from EAX). No prototype produces an EAX argument, so it is co-compiled as a selected cluster function and the whole-program pass derives the convention from its only cluster caller. |

## Retail

```
41a050  8b d7              mov  edx,edi                  ; key buffer (destination)
41a052  2b d0              sub  edx,eax                  ;   delta form of the inlined strcpy
41a054  8a 08              mov  cl,[eax]                 ;   line
41a056  88 0c 02           mov  [edx+eax],cl
41a059  40                 inc  eax
41a05a  84 c9              test cl,cl
41a05c  75 f6              jne  41a054
41a05e  6a 3a              push 3Ah                      ; strchr(key, ':')
41a060  57                 push edi
41a061  e8 ca d6 03 00     call 0x00452730
41a066  83 c4 08           add  esp,8
41a069  85 c0              test eax,eax
41a06b  75 07              jne  41a074
41a06d  8b c7              mov  eax,edi
41a06f  e9 2c 00 00 00     jmp  0x0041a0a0              ; return TrimWhitespace(key)
41a074  56                 push esi
41a075  8d 48 01           lea  ecx,[eax+1]
41a078  8b f3              mov  esi,ebx                  ; value buffer (destination)
41a07a  2b f1              sub  esi,ecx                  ;   delta form again
41a07c  8d a4 24 00 00 00 00  lea esp,[esp+0]            ; 16-byte loop alignment
41a080  8a 11              mov  dl,[ecx]
41a082  88 14 0e           mov  [esi+ecx],dl
41a085  41                 inc  ecx
41a086  84 d2              test dl,dl
41a088  75 f6              jne  41a080
41a08a  88 10              mov  [eax],dl                 ; *colon = 0
41a08c  8b c7              mov  eax,edi
41a08e  e8 0d 00 00 00     call 0x0041a0a0              ; TrimWhitespace(key), result dropped
41a093  8b c3              mov  eax,ebx
41a095  5e                 pop  esi
41a096  e9 05 00 00 00     jmp  0x0041a0a0              ; return TrimWhitespace(value)
```

Both copies are the `/Oi` inline `strcpy` delta loop, both `TrimWhitespace` exits
are tail jumps, and the second copy's loop is 16-byte aligned — all of it falls
out of the model below.

## The source (0x41A050)

`src/game/recovery_split_resource_path_0041a050.cpp` (whole file):

```cpp
// 0x0041A050..0x0041A09A: Recovery_SplitResourcePath
//
// Copy the line into the key buffer, split it at the first colon, move the
// value into the value buffer and trim both halves.  Retail passes the line in
// EAX, the value destination in EBX and the key destination in EDI, and every
// exit is a tail jump into the trim helper at 0x0041A0A0, so the model is
// compiled as a native-LTCG cluster together with that helper.
#include <string.h>

// 0x00452730: the CRT first-occurrence byte search (strchr shape), bound to the
// retail address by the layout.  The custom name keeps /Oi from inlining it.
extern "C" char* __cdecl asm_FUN_00452730_00452730(const char* text, int ch);

// 0x0041A0A0: co-compiled whitespace trim (argument and result in EAX).
char* TrimWhitespace_0041a0a0(char* text);

#pragma code_seg(".text$01split")
extern "C" __declspec(noinline) char* __stdcall SplitResourcePath_0041a050(char* line, char* value, char* key) {
    strcpy(key, line);
    char* colon = asm_FUN_00452730_00452730(key, ':');
    if (colon == 0) {
        return TrimWhitespace_0041a0a0(key);
    }
    strcpy(value, colon + 1);
    *colon = 0;
    TrimWhitespace_0041a0a0(key);
    return TrimWhitespace_0041a0a0(value);
}
#pragma code_seg()
```

`asm_FUN_00452730_00452730` is *declared*, never defined here, and the custom
name matters: `strchr` from `<string.h>` is an `/Oi` intrinsic and would be
inlined. The declaration order also matters for the emitted bytes — `(text, ch)`
with `__cdecl` pushes the character first, exactly like retail.

## The source (0x41A0A0) and the one construct that made it match

`src/game/recovery_trim_whitespace_0041a0a0.cpp` (whole file):

```cpp
// 0x0041A0A0..0x0041A111: Recovery_TrimWhitespace
//
// Strip leading and trailing spaces, tabs, newlines and carriage returns from a
// NUL-terminated string, in place.  Retail receives and returns the string
// pointer in EAX; the model is co-compiled in the 0x0041A050 cluster so the
// whole-program pass derives that convention from its only caller.
//
// The leading shift is a written-out byte loop (`for`), which is what produces
// retail's `test/jle` guard plus the single `rep movsb`; the same code spelled
// as memmove emits a call and as memcpy the movsd/movsb pair.
#include <string.h>

#pragma code_seg(".text$02trim")
char* __stdcall TrimWhitespace_0041a0a0(char* text) {
    while (*text == ' ' || *text == '\t' || *text == '\n' || *text == '\r') {
        int length = (int)strlen(text);
        for (int index = 0; index < length; ++index) {
            text[index] = text[index + 1];
        }
    }
    int length = (int)strlen(text);
    for (int index = length - 1; index >= 0; --index) {
        char c = text[index];
        if (c != ' ' && c != '\t' && c != '\n' && c != '\r') break;
        text[index] = 0;
    }
    return text;
}
#pragma code_seg()
```

The legacy semantic reconstruction guessed the shift as
`memmove(text, text + 1, strlen(text + 1) + 1)`. That guess cannot reproduce the
bytes, and neither can any of its neighbours, because retail's shift is

```
41a0c0  mov dl,[ecx] / inc ecx / test dl,dl / jne        ; inline strlen, scan starts at text
41a0c7  sub ecx,esi          ; ecx = strlen(text)
41a0c9  test ecx,ecx
41a0cb  jle 41a0a2           ; signed "empty" guard
41a0cd  lea esi,[eax+1]
41a0d0  mov edi,eax
41a0d2  rep movsb            ; one byte-wise movs, no movsd half
```

i.e. the **compiler's loop-idiom recognition of a written-out byte loop**, with
the `for (index = 0; index < length; ++index)` entry test surviving as the
`test/jle` guard and the count arriving in ECX through the inlined `strlen(text)`
(the scan from `text` rather than `text + 1` is what the `strlen(text)` spelling
gives, and `strlen(text) == strlen(text + 1) + 1` here). Measured, one compile
each with the cluster's own flags (`/nologo /c /O2 /Gz /MT /Gy /G6 /GF /GS /Zl`):

| spelling of the shift | emitted |
| --- | --- |
| `memmove(text, text+1, strlen(text+1)+1)` | `push`×3 / `call _memmove` / `add esp,0xc` |
| `#pragma intrinsic(memmove)` + that call | warning **C4163 : not available as an intrinsic function**; still a call |
| `__movsb(...)` | warning **C4163**; the 13.10 toolkit ships no `intrin.h` |
| `memcpy(text, text+1, strlen(text+1)+1)` | strlen + `shr ecx,2` / `rep movsl` / `and ecx,3` / `rep movsb` |
| `memcpy(text, text+1, strlen(text))` | same `movsd/movsb` pair, no guard |
| `memcpy` with an `int`, `char`, `short` or `unsigned short` count | same `movsd/movsb` pair, no guard |
| `strncpy(text, text+1, strlen(text))` | `call _strncpy` |
| `strcpy(text, text+1)` / hand-written NUL loop | the `strcpy` delta loop |
| **`for (i = 0; i < strlen(text); ++i) text[i] = text[i+1]`** | **retail's block, byte for byte** |

A `/GL` object linked with `link /LTCG` against `libcmt.lib` does not inline the
`memmove` either (measured: the call survives), so the difference is the source
construct, not the linker pass; the trap is that `strlen(text+1)+1` and
`strlen(text)` compile differently even though they are equal at run time.

## Layout `matching2/msvc/layout/ltcg/split_resource_path_0041a050.json`

```json
{
  "schema_version": 1,
  "name": "split_resource_path_0041a050",
  "source": "src/game/recovery_split_resource_path_0041a050.cpp",
  "additional_sources": ["src/game/recovery_trim_whitespace_0041a0a0.cpp"],
  "driver": "layout/ltcg/split_resource_path_0041a050_context.cpp",
  "headers": [],
  "image_base": "0x00400000",
  "description": "Resource-path splitter and its trim helper linked with native LTCG so the pass selects retail's EAX/EBX/EDI register convention.",
  "functions": [
    {"name": "SplitResourcePath_0041a050", "symbol": "_SplitResourcePath_0041a050@12", "section": ".text$01split",
     "address": "0x0041A050", "size": 75,
     "actual_abi": "line in EAX; value in EBX; key in EDI; plain RET through tail jumps",
     "source": "src/game/recovery_split_resource_path_0041a050.cpp"},
    {"name": "TrimWhitespace_0041a0a0", "symbol": "?TrimWhitespace_0041a0a0@@YGPADPAD@Z", "section": ".text$02trim",
     "address": "0x0041A0A0", "size": 114,
     "actual_abi": "text in EAX; result in EAX; plain RET",
     "source": "src/game/recovery_trim_whitespace_0041a0a0.cpp"}
  ],
  "context": {"symbol": "SplitResourcePathCompilerContext@16", "section": ".text$04context",
              "address": "0x0041A120", "size": 96,
              "description": "Synthetic array-walking caller that establishes the observed register convention; not recovered game code."},
  "gaps": [
    {"section": ".text$00layout", "address": "0x00401000", "size": 102480},
    {"section": ".text$03layout", "address": "0x0041A112", "size": 14}
  ],
  "constants": [],
  "absolute_symbols": [
    {"symbol": "_asm_FUN_00452730_00452730", "address": "0x00452730", "kind": "relative_code"}
  ]
}
```

Three details that cost a probe each:

* `context.symbol` is spelled **without** the leading underscore
  (`SplitResourcePathCompilerContext@16`); LINK re-decorates `/ENTRY:` names, so
  `_SplitResourcePathCompilerContext@16` becomes `__SplitResourcePathCompilerContext@16`
  and the link dies with `LNK2001: unresolved external symbol`. The loader
  matches the map's `_`-prefixed spelling afterwards.
* The first gap is `0x41A050 - 0x401000 = 102480` bytes, not the `73744` the
  address arithmetic first suggests; with the wrong value every section lands
  0x7000 too low and the probe reports "image base or entry address differs".
* `.text$02trim` must sort *after* `.text$01split` and before the `.text$03layout`
  gap, since cluster sections are placed in name order.

## Driver `matching2/msvc/layout/ltcg/split_resource_path_0041a050_context.cpp`

```cpp
// Compiler context only; never selected as recovered game code.
// The array-walking caller is what makes the whole-program pass pick the
// observed retail convention for the 0x0041A050 body: line in EAX, value in
// EBX, key in EDI, with the trim helper at 0x0041A0A0 reached in EAX.
#include "../../src/game/recovery_split_resource_path_0041a050.cpp"

#pragma code_seg(".text$04context")
extern "C" __declspec(noinline) int __stdcall SplitResourcePathCompilerContext(
        char** lines, char** values, char** keys, int count) {
    int total = 0;
    while (count--) {
        total += (int)SplitResourcePath_0041a050(*lines++, *values++, *keys++);
    }
    return total;
}
#pragma code_seg()
```

`__declspec(noinline)` on the modelled function is mandatory here as everywhere:
without it the pass inlined `SplitResourcePath_0041a050` into the context, its
section came out 0 bytes long and the map had no such symbol.

## Registers: what retail's callers use, and what the emitted body keeps

* `0x0041A050` has exactly one call site, `0x00419BF4` in the naked parser
  (`src/game/stage_tip_parser.cpp`): `mov eax,esi` (the line cursor),
  `mov esi,[esp+18h]` / `mov edi,esi` (the key buffer) and **EBX** — the third
  0x1000-byte buffer allocated at `0x004199C0` — as the value buffer. After the
  call the parser reads EDI (the `repe cmpsb` against `"MSG"` at `0x0046D610`)
  and EBX (`strchr(value, ',')` at `0x00419C0C`). The emitted body reads
  EAX/EBX/EDI and writes none of them: **kept**.
* `0x0041A0A0`'s nine call sites in the parser (`0x00419A3E`, `0x00419A45`,
  `0x00419A86`, `0x00419A8D`, `0x00419C24`, `0x00419C2B`, `0x00419DEC`,
  `0x00419E15`, `0x00419E2C`) plus the two inside this cluster all set **EAX**
  immediately before the call and consume the result in EAX (`push eax` at
  `0x00419E31`).
  The emitted body receives and returns the pointer in EAX, and saves/restores
  ESI and EDI (pushed at entry, popped shrink-wrapped around the trailing loop
  exactly as retail does): **kept**. It clobbers only ECX and EDX.
* The emitted `SplitResourcePath` keeps ESI live across the `strchr` call only
  after `push esi` at the same point retail does, and the `strchr` argument is
  materialised as `push 3Ah / push edi` — EDI never moves into ECX, so no
  caller-visible register is disturbed.
* Because the `SplitResourcePath` body never writes EBX/EDI/EBP and ends in two
  tail jumps, its declared `__stdcall` cleanup never materialises; there is no
  `ret n` in the region, as in retail.

## Landing

The two regions are byte-exact, but **`register_cluster.py` cannot register this
layout**: its per-function check requires every selected function's region to be
owned by the layout's own `source`, and `0x0041A0A0` is owned by the
`additional_sources` entry `src/game/recovery_trim_whitespace_0041a0a0.cpp`. This
is the same shape as `layout/ltcg/effect_pool_update_batch.json` (two sources,
two regions), which was registered by writing the region records directly. The
payload is therefore staged the way the wave-5 0x41C290 landing staged its own:

```
matching2/build/waves/results10/SplitResourcePath/
  apply_package.py     # copies the payload, rewrites both region records under the
                       # manifest lock, appends the layout to ltcg_clusters, and
                       # lets load_cluster reject the candidate before it is written
  payload/src/game/recovery_split_resource_path_0041a050.cpp   (rewritten: was the naked body)
  payload/src/game/recovery_trim_whitespace_0041a0a0.cpp       (rewritten: was the naked body)
  payload/layout/ltcg/split_resource_path_0041a050.json        (new)
  payload/layout/ltcg/split_resource_path_0041a050_context.cpp (new)
  probe.txt, bytes.txt
```

Manifest effect (both records keep their `previous_record`, so either record can
be restored by hand; note that `register_cluster.py --unregister` alone restores
only the layout's primary-source region, `0x0041A050`, and leaves `0x0041A0A0`
semantic — measured, so an undo has to rewrite that record from its
`previous_record` too):

```text
0x0041A050  kind semantic  symbol _SplitResourcePath_0041a050@12
            name semantic_SplitResourcePath_0041a050_0041a050  (source unchanged)
0x0041A0A0  kind semantic  symbol ?TrimWhitespace_0041a0a0@@YGPADPAD@Z
            name semantic_TrimWhitespace_0041a0a0_0041a0a0      (source unchanged)
ltcg_clusters += "layout/ltcg/split_resource_path_0041a050.json"
```

Verified end to end on a throwaway copy of the *maintained* tree
(`cp -a matching2/msvc /tmp/srp/verify/msvc`, then `apply_package.py`):

```
$ python3 matching2/build/waves/results10/SplitResourcePath/apply_package.py /tmp/srp/verify/msvc
landing applied to /tmp/srp/verify/msvc
$ python3 -c "from matching2.tools.matching.build_msvc import validate_project; ..."
/tmp/srp/verify/msvc OK regions= 4425 units= 2394
$ probe --source <both sources> --project /tmp/srp/verify/msvc   ->  EXACT (both regions)
```

No `make`/`build_msvc.py` was run (single-build rule); the probe and
`validate_project` are the evidence. The `translation_units` list is unchanged by
this landing, because both files already own regions. The 0x41A0A0 flip keeps the
naked callers working the same way the 0x41C030 flip did: they all reference
`_asm_Recovery_TrimWhitespace_0041a0a0`, which the manifest's `symbols` table
still binds to `0x0041A0A0`.

## Note on the maintained manifest

The staged package was never applied to `matching2/msvc`; all iterations ran in
`/tmp/srp/msvc` and the landing proof in `/tmp/srp/verify/msvc`. The maintained
`regions.json` was not edited by any tool other than the package's own
`apply_package.py` (run against a copy only).
