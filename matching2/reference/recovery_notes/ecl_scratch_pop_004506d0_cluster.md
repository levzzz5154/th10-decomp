# 0x004506D0 - ECL scratch pop: reconstructed, one instruction encoding short

2026-09-18. `ECL_PopScratchValue` (41 bytes) is the first region taken through the
native-LTCG cluster path with the three rules from `ltcg_cluster_lessons.md`
applied (section pragma, decorated context symbol, declared size equal to the
emitted one). The model compiles to **exactly 41 bytes, retail's extent**, in EAX
entry, with a single two-byte residual.

Retail listing:

```
8b 88 00 10 00 00   mov ecx,[eax+1000h]
83 c1 fc            add ecx,-4            <- the model emits 83 e9 04 (sub ecx,4)
8b 90 04 10 00 00   mov edx,[eax+1004h]
78 0f               js  end
89 88 00 10 00 00   mov [eax+1000h],ecx
8b 0c 01            mov ecx,[ecx+eax]
89 88 04 10 00 00   mov [eax+1004h],ecx
end:
89 90 00 10 00 00   mov [eax+1000h],edx
33 c0               xor eax,eax
c3                  ret
```

Two source facts shape the body and both were confirmed by measurement:

- the cached value must **not** be reused inside the branch — writing
  `scratch_value = <loaded>` there (instead of assigning a local and copying it
  back) is what keeps the final store single, using the original cached value in
  EDX, exactly as retail does;
- with the branch written the other way the compiler duplicates the tail and the
  function grows to 50 bytes.

The residual is the encoding of the pointer decrement. Retail's `add ecx,-4` is
not produced by any spelling tried: `x - 4`, `x + -4`, `-4 + x`, an `unsigned`
field, `+ (int)0xFFFFFFFC`, a `static const int kStep = -4`, a `char*` field
with `pointer + -4`, an `unsigned` field with `scratch_offset + 0xFFFFFFFCu`,
with `scratch_offset - 4u`, and with a signed `(int)offset >= 0` test — all
canonicalise to `sub ecx,4` (the pointer forms also change the extent, to 40 and
38 bytes). Eleven spellings now leave the region at 41 bytes with the same two
differing bytes: the opcode and the immediate's sign. Only the opcode and the immediate sign
differ, so the region sits at 41 bytes with two differing bytes.

## The model (verbatim, as measured)

```cpp
// 0x004506D0..0x004506F7: pop a value from the ECL scratch stack. The
// compiled script pointer advances by four and the cached value is refilled;
// when the pointer would go negative both fields keep the cached value. The
// virtual machine arrives in EAX, a convention only a native LTCG link chooses,
// so this region is compiled as a cluster.

struct EclVm_004506d0 {
    unsigned char pad_000[0x1000];
    unsigned int scratch_offset; // +0x1000
    int scratch_value;           // +0x1004
    __declspec(noinline) int PopScratchValue();
};

#pragma code_seg(".text$01accessor")
int EclVm_004506d0::PopScratchValue() {
    int offset = -4 + scratch_offset;
    int value = scratch_value;
    if (offset >= 0) {
        scratch_offset = offset;
        scratch_value = *(int*)((unsigned char*)this + offset);
    }
    scratch_offset = value;
    return 0;
}
#pragma code_seg()
```

## Current source candidate (2026-09-23)

`src/script/ecl_pop_scratch_value_004506d0.cpp` now retains the model above as
ordinary C++ in `EclVm_004506d0::PopScratchValue()`. The source has no inline
assembly. This edit does not change the `regions.json` record, which remains
marked ASM pending registration of the C++ symbol and its native-LTCG context.

Ghidra was rechecked at `0x004506D0`: it has two call references, both from the
interpreter at `0x0044E211` and `0x0044E453`. At the first site the caller forms
`ESI + 8` in EDI, copies that pointer to EAX, then calls; at the second it forms
`ESI + 8` directly in EAX before calling. Neither site pushes an argument. The
body returns zero in EAX and uses a plain `RET`. Ghidra's inferred
`undefined4 __stdcall PopEclScratchValue(void)` signature does not model the
live EAX receiver; the caller setup and the body's `[EAX + 0x1000]` /
`[EAX + 0x1004]` accesses establish the private ABI instead.

The maintained C++ candidate follows that EAX receiver model: it computes the
candidate offset four bytes earlier, refills the cached scratch value only when
the offset is nonnegative, restores the saved value into the offset field, and
returns zero. Exact output for this current source revision has not been
verified. The earlier measured native-LTCG version of the same model was 41
bytes, with the known decrement encoding difference (`sub ecx,4` in the
candidate versus retail's `add ecx,-4`); no build or probe was run for this
source update.
