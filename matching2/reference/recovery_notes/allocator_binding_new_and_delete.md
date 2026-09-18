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

## First candidate: 0x0043C8B0 AsciiManager create

The full listing decodes cleanly:

```
push esi
push 44h; call operator_new_00452493; mov esi,eax; add esp,4
xor eax,eax; test esi,esi; je  fail
mov ecx,[esi+40h]; mov edx,[esp+10h]; push edi
and ecx,0FFFFFFFEh; mov [esi+40h],ecx      ; clear flag bit 0 first, then...
mov ecx,11h; mov edi,esi; rep stosd        ; ...memset the whole 0x44-byte object
mov eax,[esi]; or eax,2; mov [esi],eax     ; raise flag bit 1
push edx; push eax; push ecx
call asm_FUN_0043c970_0043c970             ; three stack arguments
mov eax,esi; pop esi; ret 14h              ; five stack arguments in total
```

So the factory takes **five** arguments (stdcall, `ret 14h`), allocates 0x44
bytes, clears them, raises flag bit 1 and forwards **three** of the arguments to
`FUN_0043c970` on the stack. Every piece is expressible: `new` with the allocator
binding above, an explicit `memset`, and both calls declared `extern "C"` with
their real stack argument counts. Two attempts with a modelled factory both
stopped at symbol resolution in the layout rather than in the code, so the model
itself has not yet been compared; the remaining work is the argument mapping
between the five parameters and the three that are forwarded.

## 0x0043C8B0 measured: 77 bytes against 82

With the model as a free `extern "C" __stdcall` factory (symbol
`_AsciiManager_CreateRetail_0043c8b0@20`), `new AsciiManager_0043c8b0` bound
through `??2@YAPAXI@Z` -> `0x00452493`, an explicit `memset(manager, 0, 0x44)`,
the dead `flags_040 &= ~1u` retail performs before that memset and
`flags_040 |= 2` after it, the cluster emits **77 bytes against retail's 82**.

Two lessons from the run, both worth keeping: the model file must carry
`#pragma code_seg(".text$01accessor")` *and* the driver's embedded copy of it must
be re-synced after every edit, or the driven source silently regresses to the
previous revision; and the dead flag clear is not optional - it accounts for nine
of the bytes.

The remaining five bytes are in the argument mapping for the three arguments
forwarded to `FUN_0043c970` (five parameters in, three forwarded), which the
listing interleaves with stack reloads.
