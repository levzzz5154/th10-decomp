# 0x0042A3E0 - state predicate: 68 bytes exact, basic-block layout short

2026-09-18. `FUN_0042a3e0` (68 bytes) is a `__thiscall` predicate: the object
arrives in **ECX** (a convention a plain translation unit expresses directly, no
cluster needed) and the result in EAX. It returns **6** when the caller is in the
right state and **1** otherwise, through five guards:

```
mov eax,[data_00477810]      ; a live object is required
test eax,eax / je fail
test byte [eax+58h],4        ; its +0x58 bit 2 must be clear
mov eax,1
jne exit                     ; 1 already in EAX
cmp [ecx+10h],eax            ; this->field_010 must be 1
jne exit
mov edx,[data_00474e30]
test dh,al                   ; its bit 8 must be set
je exit
mov ecx,[ecx+1C8h]
and ecx,80000003h            ; this->field_1C8 % 4 (signed)
jns L / dec ecx / or ecx,-4 / inc ecx
je exit
mov eax,6
exit: ret
fail: mov eax,1
      ret
```

Measured shapes, all with a plain probe:

| source shape | extent | first difference |
| --- | ---: | --- |
| five separate `if (cond) return 1;` guards | 68 | 0x42A3E7 - `74 35` (jump to the fail block) vs `75 06` |
| the same with a `result` local returned by the later guards | 68 | same |
| one merged `if (a == 0 \|\| ...) return 1;` | 62 | size |
| `if (success chain) return 6; return 1;` | 62 | size |

So the extent is only 68 when the *fail* return is a separate block, and the
remaining difference is its **layout**: retail jumps forward to a `mov eax,1;
ret` at the end of the function, while MSVC puts the first guard's return inline
right after that guard. The four spellings tried do not move it; the shape that
would is one where the first failure is laid out last, which the source ordering
has not reached yet.

## The model (verbatim, as measured)

```cpp
// 0x0042A3E0..0x0042A423: report 6 when the caller is in the right state, else 1.
// A __thiscall member: the object arrives in ECX, the result in EAX.

extern "C" void* data_00477810;
extern "C" int data_00474e30;

struct Object_0042a3e0 {
    unsigned char pad_000[0x10];
    int field_010;                     // +0x010
    unsigned char pad_014[0x1B4];
    int field_1c8;                     // +0x1C8
    __declspec(noinline) int Test();
};

struct Other_0042a3e0 {
    unsigned char pad_000[0x58];
    unsigned char field_058;           // +0x058
};

int Object_0042a3e0::Test() {
    if (data_00477810 != 0
            && (((Other_0042a3e0*)data_00477810)->field_058 & 4) == 0
            && field_010 == 1
            && (data_00474e30 & 0x100) != 0
            && (field_1c8 % 4) != 0) {
        return 6;
    }
    return 1;
}
```

## Correction: the residual is 55 bytes, not a layout nub

The probe's JSON report measures **55 differing bytes** for the two 68-byte
shapes (`different_bytes: 55`), not the two implied by "first difference at
0x42A3E7". Retail jumps forward to a `mov eax,1; ret` at the end of the function
(`74 35`), while the models lay that return out inline right after the first
guard (`75 06`) and every subsequent byte shifts. A `goto fail;` spelling
compiles to **63 bytes** instead, so no tried shape reaches both the extent and
the layout: the 68-byte shapes have the fail block inline, the 63-byte one has it
last but drops a materialized `mov eax,1` that retail keeps.
