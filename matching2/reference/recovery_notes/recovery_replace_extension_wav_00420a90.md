# 0x00420A90 Recovery_ReplaceExtensionWav - nearly all readable C++

2026-09-18. From the `--entry none` prime class (no register read before writing
one). 120 bytes, two stack arguments, and the body is almost entirely
compiler-generated from ordinary C++:

```
sub esp,104h                     ; frame
mov eax,[data_00473660] / xor eax,esp / mov [esp+100h],eax    ; the /GS cookie
...inlined strcpy into the 0x100-byte buffer...
lea eax,[esp] / push 2Eh / push eax / call strrchr_00452930   ; strrchr(buffer, '.')
mov byte [eax+1],77h / [eax+2],61h / [eax+3],76h              ; ".wav"
push <out> / push 1 / lea edx,[esp+8] / mov eax,492590h
call AnimationManager_RegisterResource_0043e460
mov ecx,[esp+100h] / xor ecx,esp / mov eax,1
call security_check_cookie_00458ea5                          ; the /GS check
```

So the recovered source is:

```cpp
int Recovery_ReplaceExtensionWav_00420a90(int unused, const char* source, void* out) {
    char buffer[0x100];
    strcpy(buffer, source);                 // inlined by the compiler, delta form
    char* dot = strrchr(buffer, '.');
    dot[1] = 'w'; dot[2] = 'a'; dot[3] = 'v';
    AnimationManager_RegisterResource(0x00492590, buffer, out, 1);
    return 1;
}
```

Everything except the `RegisterResource` call is plain C++ that the compiler
generates verbatim - the inlined strcpy, the strrchr call (bindable through the
manifest's `symbols` table as `_asm_strrchr_00452930`), the three byte stores, the
`/GS` prologue and epilogue. The call itself is the obstacle: the caller sets
**EAX = 0x00492590** and **EDX = the buffer**, pushes **out** and **1**, and leaves
ECX unset, which is the same convention the two dummy registrations at
`0x00420B10`/`0x00420C00` use - and no prototype produces an argument in EAX.

Two ways forward, both already precedented in this project: declare the callee
with the closest `__fastcall` prototype and measure the delta (one probe run), or
write the call as a four-line inline `__asm` block inside otherwise readable C++,
exactly as the landed `0x00443B60` does for its `fsincos` sequences. Here the
trade is favourable - the asm would be a few lines of a body that is otherwise
pure C++ - which is why this region is recorded as an open candidate rather than a
blocked one.

The sibling `0x00420B80` (125 bytes) has the same structure - inlined strcpy,
strrchr, the three `.wav` stores - so whatever lands here lands there too.

## Measured result

Written out and probed in a throwaway copy (`cp -a matching2/msvc /tmp/ae/msvc`,
the manifest entry flipped to `semantic`, declarations of the two callees with the
asm-style symbol names, no `asm_symbols.hpp` since its `void f()` prototypes
conflict, and the function itself `extern "C"` under the name the manifest
expects). The whole body compiles and emits **121 bytes against the region's 120**,
with everything matching except two things:

```
1e: push %esi                     ; +1 byte, retail has no callee-saved use
1f: mov 0x114(%esp),%esi          ; out hoisted into ESI across the strrchr call
...
41: push %esi / 42: push $0x1     ; retail: push ecx / push $0x1
48: mov $0x492590,%ecx            ; retail: mov $0x492590,%eax
```

The push order was corrected by passing the flag third and `out` fourth (MSVC
pushes stack arguments right-to-left), which left the ESI spill as the structural
delta: retail reloads `out` from the stack after the call, where this compiler
version hoists it into a callee-saved register. That is one byte, and it is the
same class of scheduler decision as the other near-misses in this project.

The register difference is the real blocker, and it is not a size question: the
`mov` is five bytes either way, so a prototype with the resource in ECX would be
**byte-exact and semantically wrong** - `RegisterResource` reads its resource from
EAX, as the two dummy registrations at `0x00420B10`/`0x00420C00` show, and no
prototype produces an EAX argument. Landing this region therefore needs the call
expressed as an inline `__asm` block, which in turn needs a frame pointer to name
`buffer` and `out` - and the landed `0x00443B60` precedent works only because its
`fsincos` sequences address no stack slots. So the region is blocked on the same
EAX-carrying convention as `AnimationManager_RegisterResource` itself, now with a
concrete 121-byte model and the exact two-instruction delta as evidence.
