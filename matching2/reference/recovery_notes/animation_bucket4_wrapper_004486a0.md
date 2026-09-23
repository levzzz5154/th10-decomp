# Render bucket 4 wrapper at `0x004486A0`

The live Ghidra listing contains this 15-byte body:

```text
004486a0  push edi
004486a1  mov eax, 4
004486a6  mov edi, ecx
004486a8  call 0x00448980
004486ad  pop edi
004486ae  ret
```

It takes the manager in `ECX`, preserves `EDI`, asks the semantic renderer at
`0x00448980` to render bucket 4, returns its `EAX` result, and uses a plain
`ret`. The readable model in `src/unidentified/FUN_004486a0_004486a0.cpp` is a
no-data derived view whose `RenderBucket4()` method returns `RenderBucket(4)`.
This gives the entry an ordinary `__thiscall` C++ signature while preserving
the manager's offset-zero layout.

Ghidra has no function object at this wrapper address, but its byte disassembly
and direct call reference at `0x004486a8` identify the body and target. The
related slot wrappers and their register behavior are described in
`00448980_wave12.md`. A native-LTCG context with the `0x00448980` body is still
needed to reproduce the callee's private `EDI`/`EAX` convention. No build,
probe, or test was run, so this is a semantic C++ candidate, not an exactness
claim. The manifest now records this as a semantic C++ region under `?RenderBucket4@AnimationManagerBucket4_004486A0@@QAEHXZ`. The source has the ordinary `__thiscall` entry shape; exact native-LTCG lowering and byte identity remain unverified.
