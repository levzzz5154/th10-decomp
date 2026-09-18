# 0x00418810 - recovery offset point: 64 bytes exact, three compiler choices short

2026-09-18. `Recovery_OffsetPoint` (64 bytes) projects a point into the shared
buffer at `0x00497D80` with the stage origin added, marks the buffer initialised
and returns it. It reads its point from EAX, so it goes through the cluster path;
the model reaches **retail's exact 64-byte extent** with 30 differing bytes.

Retail:

```
8a 15 8c 7d 49 00   mov dl,[497d8ch]
b9 01 00 00 00      mov ecx,1
84 ca               test dl,cl
75 06               jne +6
09 0d 8c 7d 49 00   or  [497d8ch],ecx
d9 00               fld [eax]
d8 05 4c 0b 47 00   fadd [470b4ch]
d9 1d 80 7d 49 00   fstp [497d80h]
d9 40 04            fld [eax+4]
d8 05 48 0b 47 00   fadd [470b48h]
d9 1d 84 7d 49 00   fstp [497d84h]
8b 40 08            mov eax,[eax+8]
a3 88 7d 49 00      mov [497d88h],eax
b8 80 7d 49 00      mov eax,497d80h
c3                  ret
```

Three differences remain, each an MSVC 13.10 selection the source shape does not
steer here:

1. the flag test's operand order (`84 ca` retail, `84 d1` model) - the same
   `test dl,cl` with the ModRM fields swapped;
2. the x87 operand order (`fld [eax]` then `fadd [abs]` in retail, the absolute
   first in the model) - both `x + origin` and `origin + x` spellings produce the
   model's order, including with an `int` field so the constant lands in ECX as
   retail has it;
3. the second `fstp` is sunk below the two integer stores in the model.

The `int` field is what makes the flag half of the prologue match (`mov ecx,1`
plus `or [mem],ecx`); with an `unsigned char` field the compiler emits the byte
form and the body comes out one byte short at 63.

## The model (verbatim, as measured)

```cpp
// 0x00418810..0x0041884F: copy the point into the shared projection buffer with
// the stage origin added, marking the buffer initialised, and return it.
extern "C" int data_00497d8c;
extern "C" float data_00497d80;
extern "C" float data_00497d84;
extern "C" int data_00497d88;
extern "C" float data_00470b4c;
extern "C" float data_00470b48;

struct Recovery_00418810 {
    float x;    // +0x00
    float y;    // +0x04
    int z;      // +0x08
    __declspec(noinline) float* OffsetPoint();
};

#pragma code_seg(".text$01accessor")
float* Recovery_00418810::OffsetPoint() {
    if ((data_00497d8c & 1) == 0) {
        data_00497d8c |= 1;
    }
    data_00497d80 = x + data_00470b4c;
    data_00497d84 = y + data_00470b48;
    data_00497d88 = z;
    return (float*)0x00497D80;
}
#pragma code_seg()
```
