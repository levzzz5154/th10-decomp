# 0x0042ACB0 - score-file defaults: full model, one register short

2026-09-18. `ScoreFile_InitializeDefaultsRetail` (274 bytes, `void __stdcall
f(ScoreFile*)`) is a store filler with two loops:

- `memset(file, 0, 0x437C)` (`rep stosd`, `ecx = 0x10DF`);
- header words: `file->tag = 0x5243` (`CR`), `file->field_02 = 0`,
  `file->field_08 = 0x437C`;
- fifty high-score records of `0x18` bytes from `file + 0x10`: five stages of ten
  ranks with `score = 1000000 - rank*100000`, plus `mode = 1`, `frame = 0`,
  `zero = 0` and three values read from `data_0046E858`, `data_0046E85C` and the
  byte `data_0046E860`;
- a second table of twenty-two `0x2D0`-byte records from `file + 0x624`, each
  taking five values from the byte table at `0x004743C0` (`[i-1]`, `[i]`,
  `[i+1]`, `[i+2]`, `[i+3]` for `i = 1, 6, ... < 0x6F`) interleaved with the
  indices `i`, `i+2`, `i+2`, `i+3` - one index with strength-reduced bases.

## Measured

| model | extent | differing | first difference |
| --- | ---: | ---: | --- |
| both loops, `Entries()` cursor | 282 | 170 | 2 |
| header stores reordered, pointer-arithmetic cursor, extra end pointer, loops swapped, down-counting stage loop | 282-286 | 170-198 | 2 |

The **first sixteen instructions match retail instruction for instruction** apart
from one register: retail moves the `file` parameter into **EBP**, the model into
**ESI**, after which every displacement differs - the 170 differing bytes are the
same code with a different base register. The only other gap is the extent, eight
bytes long.

That single choice is the whole blocker: retail's loops keep six values live
(`esi` stage, `edi` cursor, `eax` store base, `edx` zero, `ecx` score, `ebx`
table reads), which pushes the parameter into EBP; the model's codegen frees a
register early. Reproducing retail's pressure is what a retry has to do.

## The model (verbatim, as measured)

```cpp
// 0x0042ACB0..0x0042ADC1: initialise the score file's default tables.
#include <string.h>

extern "C" int data_0046e858;
extern "C" int data_0046e85c;
extern "C" unsigned char data_0046e860;
extern "C" signed char data_004743c0[];

#pragma pack(push, 1)
struct ScoreEntry_0042acb0 {
    int score;                    // +0x00
    unsigned char mode;           // +0x04
    unsigned char frame;          // +0x05
    int default_a;                // +0x06
    int default_b;                // +0x0A
    unsigned char default_c;      // +0x0E
    int zero;                     // +0x10
    int extra;                    // +0x14
};
#pragma pack(pop)

struct ScoreFile_0042acb0 {
    unsigned short tag;           // +0x00
    unsigned short field_02;      // +0x02
    unsigned char pad_04[0x04];
    int field_08;                 // +0x08
    unsigned char pad_0c[0x04];
    ScoreEntry_0042acb0* Entries() {
        return (ScoreEntry_0042acb0*)((unsigned char*)this + 0x10);
    }
};

void __stdcall ScoreFile_InitializeDefaultsRetail_0042acb0(ScoreFile_0042acb0* file) {
    memset(file, 0, 0x437C);
    file->tag = 0x5243;
    file->field_02 = 0;
    file->field_08 = 0x437C;
    {
        ScoreEntry_0042acb0* entry = file->Entries();
        for (int stage = 5; stage > 0; stage--) {
            int score = 1000000;
            do {
                entry->score = score;
                entry->mode = 1;
                entry->default_a = data_0046e858;
                entry->default_b = data_0046e85c;
                entry->default_c = data_0046e860;
                entry->zero = 0;
                entry->frame = 0;
                score -= 100000;
                entry++;
            } while (score > 0);
        }
    }
    unsigned char* sub = (unsigned char*)file + 0x624;
    for (int i = 1; i < 0x6F; i += 5) {
        *(int*)(sub + 0x00) = 0;
        *(int*)(sub + 0x04) = data_004743c0[i - 1];
        *(int*)(sub + 0x90) = i;
        *(int*)(sub + 0x94) = data_004743c0[i];
        *(int*)(sub + 0x120) = i + 2;
        *(int*)(sub + 0x124) = data_004743c0[i + 1];
        *(int*)(sub + 0x1B0) = i + 2;
        *(int*)(sub + 0x1B4) = data_004743c0[i + 2];
        *(int*)(sub + 0x240) = i + 3;
        *(int*)(sub + 0x244) = data_004743c0[i + 3];
        sub += 0x2D0;
    }
}
```

## Native-LTCG route attempted and rejected

The cluster path was exercised end to end for this region in the throwaway copy
(`/tmp/w42acb0/msvc`, a synthetic context calling the function in a loop, the four
data globals bound through `absolute_symbols`). Three machinery lessons and one
measurement came out of it:

- The model source **must** carry `#pragma code_seg(".text$01accessor")`; without
  it the function is emitted into the default `.text`, the map shows
  `.text$00layout` starting at offset `0x11A` and the entry point collapses to
  `0000:00000000`, which the map validator then rejects with *"MAP segment 0000
  has no section contribution"*.
- The context symbol in the layout **must be the decorated name**
  (`?ScoreCompilerContext@@YGHPAPAUScoreFile_0042acb0@@H@Z`); an undecorated name
  leaves the linker's `/ENTRY` unresolved and produces the same collapsed entry.
- The declared function size must equal the emitted one — 282 here against the
  region's 274 — or the map validation stops before any byte comparison.

With all three fixed the cluster builds and compares: **282 bytes, 260 differing,
first difference at 0x07** (`8b` where retail has `57`, i.e. a different push
order in the prologue) — *worse* than the plain model's 170. The whole-program
pass re-allocates registers the same way for this shape, so, as with the vector
polar setters, retail's extent and prologue match the plain translation unit and
the LTCG route is not the answer for this region.
