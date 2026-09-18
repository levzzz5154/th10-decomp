# Binding the C++ allocator calls to retail's operator new

2026-09-18. Many remaining regions allocate (retail `push <size>; call
asm_operator_new_00452493; add esp,4`). Measured in a throwaway copy: a C++
`new T` expression emits exactly that shape, with the call targeted at
`??2@YAPAXI@Z` and a DISP32 relocation:

```
6a 44        push 0x44
e8 ..        call ??2@YAPAXI@Z
83 c4 04     add esp,4
85 c0        test eax,eax
74 ..        je   ...
```

So a region that news an object is expressible by declaring the class **without a
constructor** (with one, the compiler also emits a call to `??0T@@QAE@XZ`, a
symbol that would need its own binding; without one it emits only the allocator
call and then whatever the source does next, which in retail is an explicit
`memset`) and binding the mangled allocator name in the cluster layout:

```json
{"symbol": "??2@YAPAXI@Z", "address": "0x00452493", "kind": "relative_code"}
```

The same mechanism covers the matching deallocation: bind `??3@YAXPAX@Z` to
retail's operator delete address. This removes the "the region allocates"
obstacle from the worklist, which `screen_regions.py` had been rejecting through
its call-setup test (the `push <size>` before the call is fine, but the allocator
call chain reads a live-in register in several regions).

First candidate prepared with this in mind: `0x0043C8B0`
`AsciiManager_CreateRetail` (82 bytes) - `operator new(0x44)`, a `rep stosd` of
0x44 bytes, `[esi] |= 2`, then one further call, all through stack arguments.
