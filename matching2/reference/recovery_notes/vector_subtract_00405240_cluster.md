# 0x00405240 Vector3 subtract - cluster attempt, size-exact with a role delta

2026-09-19. First cluster attempt of this session, run through
`cluster_attempt.py` against a throwaway copy (`/tmp/vsub/msvc`). The region is a
three-component float subtract, 25 bytes, and the model reaches the exact extent:

```
retail                              model (member form, v1)
fld  [edx+8]                        flds  (%ecx)
fsub [ecx+8]                        fsubs (%eax)
fld  [edx+4]                        fstps (%edx)
fsub [ecx+4]
fld  [edx]                          flds  0x4(%ecx)
fsub [ecx]                          fsubs 0x4(%eax)
fstp [eax]                          fstps 0x4(%edx)
fstp [eax+4]
fstp [eax+8]                        flds  0x8(%ecx)
ret                                 fsubs 0x8(%eax)
                                    fstps 0x8(%edx)
                                    ret
```

25 bytes identical in length, 16 differing, and the difference is two things:

- **register roles**: retail has `out` in EAX, `a` in ECX and `b` in EDX; the
  native-LTCG pass chose EDX for the walked object, ECX for the first argument and
  EAX for the second. The array-walking context that reliably yields EAX for a
  single-argument member (see the landed `accessor_00405bb0`) does not do so once
  the member takes two pointer arguments.
- **the FPU schedule**: the model computes x, y, z in ascending order with one
  `fld`/`fsub`/`fstp` triple per component; retail keeps all three values on the
  FPU stack, loading z, y, x and storing x, y, z. That is the shape a compiler
  produces for a by-value vector expression rather than three independent pointer
  stores, and it suggests the original source returned a vector or took its
  arguments by value rather than through three pointers.

Model written as a member `void Subtract(const Vector3& a, const Vector3& b)`
inside `#pragma code_seg(".text$01accessor")` with a matching `_context.cpp`
driver, and the layout bound `__fltused` as a metadata symbol exactly as the
landed floating-point layouts do - without that binding the link stops at
`unresolved external symbol __fltused`.

A second variant, a free `__fastcall(out, a, b)` walked by the same context, does
not pass the semantic validation: the native function's compiler origin differs,
i.e. the inline-agnostic whole-program pass does not keep that form intact. The
member form is the one to iterate on.

Two next levers, both cheap: make the function take or return a vector **by
value** to see whether the FPU schedule becomes retail's, and try a context whose
walked objects differ from the argument objects (for example a loop over an array
of destinations with fixed source operands) to see whether EAX moves to `out`.
