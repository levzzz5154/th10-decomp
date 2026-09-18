# Native-LTCG cluster path: three rules a new attempt must satisfy

2026-09-18. Written after four failed cluster attempts on regions whose models
were otherwise complete. Each rule below cost a full build cycle and produced a
misleading error, so they are recorded together.

## 1. The modelled source needs `#pragma code_seg`

Every cluster function must be placed in its own section, e.g.

```cpp
#pragma code_seg(".text$01accessor")
void __stdcall MyFunction(...) { ... }
#pragma code_seg()
```

Without it the function is emitted into the default `.text`, and the link map
then shows the *layout gap* starting at an offset equal to the function's size
with the function itself at the image base — and, critically, the link's entry
point collapses to `0000:00000000`.

## 2. The context symbol must be the decorated name

The schema-1 layout's `context.symbol` is passed straight to the linker as
`/ENTRY:<symbol>`; for the accessor clusters it is a member function's decorated
name. If the context is written as a free function, the layout must carry the
mangled spelling (`?ScoreCompilerContext@@YGHPAPAUScoreFile_0042acb0@@H@Z`), not
the source name. An undecorated name leaves `/ENTRY` unresolved and produces
exactly the collapsed entry point from rule 1.

## 3. The declared size must equal the emitted size

`validate_native_output` requires the function's declared `size` to equal the
section contribution length; a mismatch aborts *before* any byte comparison. For
exploration this means the layout has to be adjusted to the emitted size (or the
manifests's region size raised to match) rather than compared at retail's size;
the byte comparison against retail is then done separately.

## The misleading error

All three failures surface as

```
MAP segment 0000 has no section contribution
```

That message comes from `_segment_section` being asked for the section of
`link_map.entry_segment` — segment 0000 is the *absolute* segment, so the real
complaint is always "the entry point did not resolve". Data bindings in
`absolute_symbols` are not the cause; landed layouts bind them the same way.

## What the path is and is not good for

It is the mechanism for regions whose *entry register* is not expressible in C++
(entity in EAX, `this` in EDI, and similar) — that is how the accessor,
`copy_block` and `destroy_owned` batches landed. It is **not** a lever for
allocator-pressure residuals: for `0x0042ACB0` and the six vector polar setters
the `/GL` pass re-compiled to the same or a worse extent (282 against the plain
model's 282 with 260 differing instead of 170; 28 bytes against retail's 30), so
retail's own extent and prologue match the plain translation unit in those cases.
