# Render bucket 2 wrapper at `0x00448610`

The live Ghidra listing contains this 15-byte body:

```text
00448610  push edi
00448611  mov eax, 2
00448616  mov edi, ecx
00448618  call 0x00448980
0044861d  pop edi
0044861e  ret
```

It takes the manager in `ECX`, preserves `EDI`, asks the semantic renderer at
`0x00448980` to render bucket 2, returns its `EAX` result, and uses a plain
`ret`. The readable model in `src/unidentified/FUN_00448610_00448610.cpp` is a
no-data derived view whose `RenderBucket2()` method returns `RenderBucket(2)`.
This gives the entry an ordinary `__thiscall` C++ signature while preserving
the manager's offset-zero layout.

Ghidra has no function object at this wrapper address, but its byte disassembly
and direct call reference at `0x00448618` identify the body and target. The
related slot wrappers and their register behavior are described in
`00448980_wave12.md`. A native-LTCG context with the `0x00448980` body is still
needed to reproduce the callee's private `EDI`/`EAX` convention. No build,
probe, or test was run, so this is a semantic C++ candidate, not an exactness
claim. The manifest now records this as a semantic C++ region under `?RenderBucket2@AnimationManagerBucket2_00448610@@QAEHXZ`. The source has the ordinary `__thiscall` entry shape; exact native-LTCG lowering and byte identity remain unverified.
